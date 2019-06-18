#!/system/bin/sh

ETHERNET_INTERFACE_NAME=rndis0
WIFI_INTERFACE_NAME=wlan0
ETHERNET_INTERFACE_IP=192.0.2.111
WIFI_STATIC_ROUTE_FILE_PATH="/system/bin/public_static_route.dat"
#ETHERNET_STATIC_ROUTES_WITHOUT_MASK=""

ETHERNET_WAIT_TIMEOUT_S=900 #60s
PREF_VALUE=10
ADVANCED_ROUTER_ROUTE_ID=1

AWK_CMD=awk
IP_CMD=ip
WC_CMD=wc
IFCONFIG_CMD="busybox ifconfig"
ROUTE_CMD="busybox route"
NDC_CMD=/system/bin/ndc

ETHERNET_INTERFACE_GW=${ETHERNET_INTERFACE_IP%.*}.1
WIFI_INTERFACE_GW=
PREV_WIFI_CONNECT_STATUS=0
CUR_WIFI_CONNECT_STATUS=0
WIFI_RESULT_PROP="dhcp.wlan0.result"
WIFI_GATEWAY_PROP="dhcp.wlan0.gateway"
WIFI_DNS1_PROP='dhcp.wlan0.dns1'
WIFI_DNS2_PROP='dhcp.wlan0.dns2'

verify_static_routes() {
    routelist=$(${IP_CMD} route list table 1 | awk '{print $1}' -)
    for item in ${ETHERNET_STATIC_ROUTES}; do
        echo "item:${item}"
        echo ${routelist} | grep ${item} 1>/dev/null
        if [ $? -ne 0 ]; then
            #echo "add to static table :${item} ${ETHERNET_INTERFACE_GW} ${ETHERNET_INTERFACE_NAME} ${ADVANCED_ROUTER_ROUTE_ID}" >>/dev/console
            #echo "${IP_CMD} route add ${item} via ${ETHERNET_INTERFACE_GW} dev ${ETHERNET_INTERFACE_NAME} table ${ADVANCED_ROUTER_ROUTE_ID}" >> /dev/console
            ${IP_CMD} route add ${item} via ${ETHERNET_INTERFACE_GW} dev ${ETHERNET_INTERFACE_NAME} table ${ADVANCED_ROUTER_ROUTE_ID}
        fi
    done
}

set_wifi_dns_route() {
    if [[ $# -lt 1 ]]; then
        echo "argument is null, usage:$0 wifi_dns_prop"
        return -1
    fi

    local result=$(getprop ${1})
    if [ -n "${result}" ]; then
        ${IP_CMD} route add ${result} via ${WIFI_INTERFACE_GW} dev ${WIFI_INTERFACE_NAME} table ${ADVANCED_ROUTER_ROUTE_ID}
    fi

    return 0
}

set_wifi_static_routes() {
    # mxp, 20180626, please see NatController.cpp, we auto add this ip rule, in netd
    #local item=
    #${IP_CMD} rule add from all table ${ADVANCED_ROUTER_ROUTE_ID} pref ${PREF_VALUE} || return 1
    #echo "try to set static route " >> /dev/console
    ${IP_CMD} route add ${WIFI_INTERFACE_GW%.*}.0/24 dev ${WIFI_INTERFACE_NAME} table ${ADVANCED_ROUTER_ROUTE_ID}
    set_wifi_dns_route ${WIFI_DNS1_PROP}
    set_wifi_dns_route ${WIFI_DNS2_PROP}
    while read item; do
        #echo "try to set static route ${item}" >> /dev/console
        ${IP_CMD} route add ${item} via ${WIFI_INTERFACE_GW} dev ${WIFI_INTERFACE_NAME} table ${ADVANCED_ROUTER_ROUTE_ID}
    done <${WIFI_STATIC_ROUTE_FILE_PATH}

    #for item in ${ETHERNET_STATIC_ROUTES_WITHOUT_MASK};do
    #    ${IP_CMD} route add ${item} via ${ETHERNET_INTERFACE_GW} dev ${ETHERNET_INTERFACE_NAME} table ${ADVANCED_ROUTER_ROUTE_ID}
    #done

    return 0
}

del_wifi_static_routes() {
    ${IP_CMD} route flush table ${ADVANCED_ROUTER_ROUTE_ID}
}

set_usb_interface_up() {
    local index=0
    while [ ${index} -lt ${ETHERNET_WAIT_TIMEOUT_S} ]; do
        ${IFCONFIG_CMD} ${ETHERNET_INTERFACE_NAME} ${ETHERNET_INTERFACE_IP} up
        if [ $? -eq 0 ]; then
            echo "we will enable ethernet, add rndis default gw"
            ${ROUTE_CMD} add default gw ${ETHERNET_INTERFACE_GW}
            setprop inspur.net.dns.extra ${ETHERNET_INTERFACE_GW}
            local try_times=0
            local max_try_times=20
            while [ $try_times -lt $max_try_times ]; do
                echo "try times is $try_times" >> /dev/console
                enable_ethernet_dns
                if [ $? -eq 0 ]; then
                    break
                else
                    sleep 0.5
                    let try_times++
                fi
            done
            return 0
        fi
        let index++
        sleep 0.3
    done

    echo "wait ${ETHERNET_INTERFACE_NAME} failed"
    return 1
}

enable_ethernet_dns() {
    ${NDC_CMD} resolver flushif ${ETHERNET_INTERFACE_NAME} || return 1
    ${NDC_CMD} resolver flushdefaultif || return 1
    ${NDC_CMD} resolver setdefaultif ${ETHERNET_INTERFACE_NAME} || return 1
    ${NDC_CMD} resolver setifdns ${ETHERNET_INTERFACE_NAME} "" ${ETHERNET_INTERFACE_GW} || return 1
    return 0
}

check_and_update() {
    local wifi_result=$(getprop $WIFI_RESULT_PROP)
    #echo "ddd$wifi_result" >> /dev/console
    if [[ "x$wifi_result" == "xok" ]]; then
        CUR_WIFI_CONNECT_STATUS=1
    else
        CUR_WIFI_CONNECT_STATUS=0
    fi

    if [[ "x${PREV_WIFI_CONNECT_STATUS}" == "x0" && "x${CUR_WIFI_CONNECT_STATUS}" == "x1" ]]; then

        echo "we will add wifi static route and local route in table 1"
        WIFI_INTERFACE_GW=$(getprop ${WIFI_GATEWAY_PROP})
        set_wifi_static_routes

        #framework will set default dns for system
    elif [[ "x${PREV_WIFI_CONNECT_STATUS}" == "x1" && "x${CUR_WIFI_CONNECT_STATUS}" == "x0" ]]; then

        echo "we will del wifi static route"
        del_wifi_static_routes
    else
        echo "do nothing"
    fi

    ${ROUTE_CMD} -n | grep "^0.0.0.0.*${WIFI_INTERFACE_NAME}$" 1>/dev/null 2>&1
    if [ $? -eq 0 ]; then
        echo "we will del wifi default route and local route"
        ${ROUTE_CMD} del default gw ${WIFI_INTERFACE_GW}
        ${ROUTE_CMD} del -net ${WIFI_INTERFACE_GW%.*}.0/24 dev ${WIFI_INTERFACE_NAME}
        ${ROUTE_CMD} del -host ${WIFI_INTERFACE_GW} dev ${WIFI_INTERFACE_NAME}
    fi

    PREV_WIFI_CONNECT_STATUS=${CUR_WIFI_CONNECT_STATUS}
}

set_usb_interface_up || exit 0
sleep 1
# check again, make sure that rndis is up
HAVE_NET=$(busybox ifconfig | grep "rndis")
if [ "${HAVE_NET}" == "" ]; then
    echo "rndis maybe down, revoke up"
    set_usb_interface_up
fi

checkTime=0
maxTime=20
while [ 1 ]; do
    #echo "check ....." >> /dev/console
    if [ ${checkTime} -gt ${maxTime} ]; then
        echo "do nothing"
    else
        checkTime=$((${checkTime} + 1))
    fi

    check_and_update
    sleep 2

done
