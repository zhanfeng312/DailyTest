package com.inspur.net.NetTest;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.EthernetManager;
import android.net.IpConfiguration;
import android.net.LinkAddress;
import android.net.LinkProperties;
import android.net.NetworkAbility;
import android.net.NetworkUtils;
import android.net.RouteInfo;
import android.net.StaticIpConfiguration;
import android.os.SystemProperties;
import android.util.Log;

import java.lang.reflect.Method;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

/*
    封装了Ethernet的常用接口
 */
public class EthernetHelper {

    private static final String TAG = "NetTest";

    public static final String ETHERNET_CONN_MODE_DHCP = "DHCP";
    public static final String ETHERNET_CONN_MODE_MANUAL = "STATIC";

    private static EthernetManager mEthManager;

    private static ConnectivityManager mConnectivityManager;

    public static void setDhcpConfig(Context context)
    {
        try {
            Log.d(TAG, "start setDhcpConfig");

            mEthManager = (EthernetManager)context.getSystemService("inspur_ethernet");
            if (mEthManager == null) {
                Log.d(TAG, "failed to get inspur_ethernet, next to try " + Context.ETHERNET_SERVICE);
                mEthManager = (EthernetManager)context.getSystemService(Context.ETHERNET_SERVICE);
            }

            Log.d(TAG, "setDhcpConfig ethernetManager is " + mEthManager);

            IpConfiguration ipConfiguration = new IpConfiguration();
            ipConfiguration.setIpAssignment(IpConfiguration.IpAssignment.DHCP);

            mEthManager.setConfiguration(ipConfiguration);

        }catch (Exception e){

            e.printStackTrace();
            Log.d(TAG, "setDhcpConfig failed");
            return;
        }
    }

    public static void setDhcpConfig(Context context, int type){

        try {
            Log.d(TAG, "start setDhcpConfig with type = " + type);

            mEthManager = (EthernetManager)context.getSystemService("inspur_ethernet");
            if (mEthManager == null) {
                Log.d(TAG, "failed to get inspur_ethernet, next to try " + Context.ETHERNET_SERVICE);
                mEthManager = (EthernetManager)context.getSystemService(Context.ETHERNET_SERVICE);
            }

            Log.d(TAG, "setDhcpConfig with type ethernetManager is " + mEthManager);

            IpConfiguration ipConfiguration = new IpConfiguration();
            ipConfiguration.setIpAssignment(IpConfiguration.IpAssignment.DHCP);

            mEthManager.setConfiguration(type, ipConfiguration);

        }catch (Exception e){

            e.printStackTrace();
            Log.d(TAG, "setDhcpConfig with type failed");
            return;
        }
    }

    public static void setStaticConfig(Context context, String ip, String mask, String gateway, String dns)
    {
        try {
            Log.d(TAG, "start setStaticConfig");

            mEthManager = (EthernetManager)context.getSystemService("inspur_ethernet");
            if (mEthManager == null) {
                Log.d(TAG, "failed to get inspur_ethernet, next to try " + Context.ETHERNET_SERVICE);
                mEthManager = (EthernetManager)context.getSystemService(Context.ETHERNET_SERVICE);
            }

            Log.d(TAG, "setStaticConfig ethernetManager is " + mEthManager);

            StaticIpConfiguration staticIpConfiguration = new StaticIpConfiguration();

            //ip mask
            InetAddress inetAddress = NetworkUtils.numericToInetAddress(ip);
            int prefixLength = NetworkUtils.netmaskIntToPrefixLength(NetworkTools.stringToInt(mask));
            LinkAddress linkAddress = new LinkAddress(inetAddress, prefixLength);

            //gateway
            InetAddress gatewayAddress = NetworkUtils.numericToInetAddress(gateway);

            //dns
            ArrayList<InetAddress> dnsList = new ArrayList<InetAddress>();
            dnsList.add(NetworkUtils.numericToInetAddress(dns));

            staticIpConfiguration.ipAddress = linkAddress;
            staticIpConfiguration.gateway = gatewayAddress;
            staticIpConfiguration.dnsServers.addAll(dnsList);

            IpConfiguration ipConfiguration = new IpConfiguration(IpConfiguration.IpAssignment.STATIC,
                             IpConfiguration.ProxySettings.NONE,staticIpConfiguration,null);

            mEthManager.setConfiguration(ipConfiguration);

            NetworkTools.showMessage(context,"静态IP设置成功");
        }catch(Exception e){

            e.printStackTrace();
            Log.d(TAG, "setStaticConfig failed");
            return ;
        }
    }

    public static void setStaticConfig(Context context, int type, String ip, String mask, String gateway, String dns){

        try {
            Log.d(TAG, "start setStaticConfig with type = " + type);

            mEthManager = (EthernetManager)context.getSystemService("inspur_ethernet");
            if (mEthManager == null) {
                Log.d(TAG, "failed to get inspur_ethernet, next to try " + Context.ETHERNET_SERVICE);
                mEthManager = (EthernetManager)context.getSystemService(Context.ETHERNET_SERVICE);
            }

            Log.d(TAG, "setStaticConfig with type ethernetManager is " + mEthManager);

            StaticIpConfiguration staticIpConfiguration = new StaticIpConfiguration();

            //ip mask
            InetAddress inetAddress = NetworkUtils.numericToInetAddress(ip);
            int prefixLength = NetworkUtils.netmaskIntToPrefixLength(NetworkTools.stringToInt(mask));
            LinkAddress linkAddress = new LinkAddress(inetAddress, prefixLength);

            //gateway
            InetAddress gatewayAddress = NetworkUtils.numericToInetAddress(gateway);

            //dns
            ArrayList<InetAddress> dnsList = new ArrayList<InetAddress>();
            dnsList.add(NetworkUtils.numericToInetAddress(dns));

            staticIpConfiguration.ipAddress = linkAddress;
            staticIpConfiguration.gateway = gatewayAddress;
            staticIpConfiguration.dnsServers.addAll(dnsList);

            IpConfiguration ipConfiguration = new IpConfiguration(IpConfiguration.IpAssignment.STATIC,
                             IpConfiguration.ProxySettings.NONE,staticIpConfiguration,null);

            mEthManager.setConfiguration(type, ipConfiguration);

            NetworkTools.showMessage(context,"静态IP设置成功");
        }catch(Exception e){

            e.printStackTrace();
            Log.d(TAG, "setStaticConfig with type failed");
            return ;
        }
    }

    public static String getConnectModeWithNoType(Context context)
    {
        String modeString = "";

        EthernetManager ethernetManager = (EthernetManager)context.getSystemService("inspur_ethernet");
        if (ethernetManager == null) {
            Log.d(TAG, "failed to get inspur_ethernet, next to try " + Context.ETHERNET_SERVICE);
            ethernetManager = (EthernetManager)context.getSystemService(Context.ETHERNET_SERVICE);
        }

        try{
            modeString = ethernetManager.getConfiguration().getIpAssignment().name();
        }catch (Exception e){
            e.printStackTrace();
        }

        Log.d(TAG, "get the connect mode is " + modeString);

        return modeString;
    }

    public static String getConnectModeWithType(Context context, int type) {

        String modeString = "";

        EthernetManager ethernetManager = (EthernetManager)context.getSystemService("inspur_ethernet");
        if (ethernetManager == null) {
            Log.d(TAG, "failed to get inspur_ethernet, next to try " + Context.ETHERNET_SERVICE);
            ethernetManager = (EthernetManager)context.getSystemService(Context.ETHERNET_SERVICE);
        }

        try {
            modeString = ethernetManager.getConfiguration(type).getIpAssignment().name();
        }catch (Exception e){
            e.printStackTrace();
        }

        Log.d(TAG, "get the connect mode is " + modeString);

        return modeString;
    }

    public static String getMac(){

        //get prop value
        String macString = SystemProperties.get("ro.mac0", "");
        if (true == macString.equals("") || macString == null){

            return "ff:ff:ff:ff:ff:ff";
        }else{
            return macString;
        }
    }

    private static String getIpAddressWithEthernetType(Context context, int ethernet_type){

        String ipAddress = "0.0.0.0";
        mConnectivityManager = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
        if (mConnectivityManager == null){
            Log.d(TAG, "mConnectivityManager is null");
            return ipAddress;
        }

        LinkProperties linkProperties =  mConnectivityManager.getLinkProperties(ethernet_type);
        if (linkProperties == null){

            Log.d(TAG, "linkProperties is null");
            return ipAddress;
        }

        //Log.d(TAG, "getIpAddress linkProperties is " + linkProperties);

        try{
            Class<?> c = Class.forName("android.net.LinkProperties");
            Method method = c.getMethod("getLinkAddresses");

            String str = method.getReturnType().toString();
            List<LinkAddress> list_addr = null;
            if (str.equals("interface java.util.Collection")){

                Object object = method.invoke(linkProperties);
                Collection coll = (Collection)object;

                list_addr = new ArrayList(coll);
            }else{

                list_addr = new ArrayList(mConnectivityManager.getLinkProperties(ethernet_type).getLinkAddresses());
            }

            if(list_addr.size() <= 0) {

                Log.e(TAG, "failed to get ipaddr");
                return ipAddress;
            }

            for(LinkAddress linkAddress : list_addr) {
                if(linkAddress.getAddress() instanceof Inet4Address) {

                    InetAddress inetAddress = linkAddress.getAddress();
                    ipAddress = inetAddress.getHostAddress();
                    Log.d(TAG, "getIpAddress ip is " + ipAddress);
                    break;
                }
            }
        }catch(Exception e){
            e.printStackTrace();
            return ipAddress;
        }

        return ipAddress;
    }

    public static String getIpAddress(Context context, int type) {

        int ethernet_type = 0;

        if (type == -1){

            ethernet_type = ConnectivityManager.TYPE_ETHERNET;
        }else if (type >= NetworkAbility.NETWORK_TYPE_WAN && type < NetworkAbility.NETWORK_TYPE_MAX){

            ethernet_type = NetworkAbility.translateEthernetNetworkType(type);
        }else{

            return null;
        }

        return getIpAddressWithEthernetType(context, ethernet_type);
    }

    public static String getNetMaskWithEthernetType(Context context, int ethernet_type) {

        String NetMask = "0.0.0.0";

        mConnectivityManager = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
        if (mConnectivityManager == null){
            Log.d(TAG, "m_connectivityManager is null");
            return NetMask;
        }

        LinkProperties linkProperties = mConnectivityManager.getLinkProperties(ethernet_type);
        if (linkProperties == null){

            Log.d(TAG, "linkProperties is null");
            return NetMask;
        }

        //Log.d(TAG, "getNetMask linkProperties is " + linkProperties);

        try{
            Class<?> c = Class.forName("android.net.LinkProperties");
            Method method = c.getMethod("getLinkAddresses");

            String str = method.getReturnType().toString();
            List<LinkAddress> list_NetMask = null;
            if (str.equals("interface java.util.Collection")){

                Object object = method.invoke(linkProperties);
                Collection coll = (Collection)object;

                list_NetMask = new ArrayList(coll);

            }else{
                list_NetMask = new ArrayList(mConnectivityManager.getLinkProperties(ethernet_type).getLinkAddresses());
            }

            if(list_NetMask.size() <= 0) {

                Log.e(TAG, "failed to get NetMask");
                return NetMask;
            }

            for(LinkAddress linkAddress : list_NetMask) {
                if(linkAddress.getAddress() instanceof Inet4Address) {

                    int prefixLength = linkAddress.getNetworkPrefixLength();
                    NetMask = NetworkTools.intToString(NetworkUtils.prefixLengthToNetmaskInt(prefixLength));
                    Log.d(TAG, "getNetMask NetMask is " + NetMask);
                    break;
                }
            }
        }catch(Exception e){
            e.printStackTrace();
            return NetMask;
        }

        return NetMask;
    }

    public static String getNetMask(Context context, int type) {

        int ethernet_type = 0;

        if (type == SingleEthernetActivity.singleEthernetType) {

            ethernet_type = ConnectivityManager.TYPE_ETHERNET;
        } else if (type >= NetworkAbility.NETWORK_TYPE_WAN && type < NetworkAbility.NETWORK_TYPE_MAX) {

            ethernet_type = NetworkAbility.translateEthernetNetworkType(type);
        } else {

            return null;
        }

        return getNetMaskWithEthernetType(context, ethernet_type);
    }

    public static String getGateWayWithEthernetType(Context context, int ethernet_type){

        String gateWay = "0.0.0.0";
        mConnectivityManager = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
        if (mConnectivityManager == null){
            Log.d(TAG, "m_connectivityManager is null");
            return gateWay;
        }

        LinkProperties linkProperties = mConnectivityManager.getLinkProperties(ethernet_type);
        if (linkProperties == null){

            Log.d(TAG, "linkProperties is null");
            return gateWay;
        }

        //Log.d(TAG, "getGateWay linkProperties is " + linkProperties);

        try{
            Class<?> c = Class.forName("android.net.LinkProperties");
            Method method = c.getMethod("getRoutes");

            String str = method.getReturnType().toString();
            List<RouteInfo> list_routeInfo = null;
            if (str.equals("interface java.util.Collection")){

                Object object = method.invoke(linkProperties);
                Collection coll = (Collection)object;

                list_routeInfo = new ArrayList(coll);

            }else{
                list_routeInfo = new ArrayList(mConnectivityManager.getLinkProperties(ethernet_type).getRoutes());
            }

            if(list_routeInfo.size() <= 0) {

                Log.e(TAG, "failed to get NetMask");
                return gateWay;
            }

            for(RouteInfo routeInfo : list_routeInfo){

                InetAddress inetAddress = routeInfo.getGateway();
                if(inetAddress instanceof Inet4Address) {
                    String tmp_gateway = inetAddress.getHostAddress();
                    if(routeInfo.isDefaultRoute() || !tmp_gateway.equals("0.0.0.0")) {
                        gateWay = tmp_gateway;
                        Log.d(TAG, "getGateway gateway is " + gateWay);
                        break;
                    }
                }
            }

        }catch(Exception e){
            e.printStackTrace();
            return gateWay;
        }

        return gateWay;
    }

    public static String getGateWay(Context context, int type)
    {
        int ethernet_type = 0;

        if (type == SingleEthernetActivity.singleEthernetType) {

            ethernet_type = ConnectivityManager.TYPE_ETHERNET;

        } else if (type >= NetworkAbility.NETWORK_TYPE_WAN && type < NetworkAbility.NETWORK_TYPE_MAX) {

            ethernet_type = NetworkAbility.translateEthernetNetworkType(type);
        } else {

            return null;
        }

        return getGateWayWithEthernetType(context, ethernet_type);
    }


    //TODO: 完善此接口，有时需要获取两个dns
    private static String getDnsWithEthernetType(Context context, int ethernet_type){

        String dns = "0.0.0.0";
        mConnectivityManager = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
        if (mConnectivityManager == null){
            Log.d(TAG, "m_connectivityManager is null");
            return dns;
        }

        LinkProperties linkProperties = mConnectivityManager.getLinkProperties(ethernet_type);
        if (linkProperties == null){

            Log.d(TAG, "linkProperties is null");
            return dns;
        }

        //Log.d(TAG, "getDns linkProperties is " + linkProperties);

        try{
            Class<?> c = Class.forName("android.net.LinkProperties");
            Method method = c.getMethod("getDnsServers");

            String str = method.getReturnType().toString();
            List<InetAddress> list_dns = null;
            if (str.equals("interface java.util.Collection")){

                Object object = method.invoke(linkProperties);
                Collection coll = (Collection)object;

                list_dns = new ArrayList(coll);

            }else{
                list_dns = mConnectivityManager.getLinkProperties(ethernet_type).getDnsServers();
            }

            if(list_dns.size() <= 0) {

                Log.e(TAG, "failed to get NetMask");
                return dns;
            }

            for (InetAddress inetAddress : list_dns){

                if (inetAddress instanceof Inet4Address){

                    dns = inetAddress.getHostAddress();
                    Log.d(TAG, "getDns dns is " + dns);
                    break;
                }
            }

        }catch(Exception e){
            e.printStackTrace();
            return dns;
        }

        return dns;
    }

    public static String getDns(Context context, int type)
    {
        int ethernet_type = 0;

        if (type == SingleEthernetActivity.singleEthernetType) {

            ethernet_type = ConnectivityManager.TYPE_ETHERNET;
        } else if (type >= NetworkAbility.NETWORK_TYPE_WAN && type < NetworkAbility.NETWORK_TYPE_MAX) {

            ethernet_type = NetworkAbility.translateEthernetNetworkType(type);
        } else {

           return null;
        }

        return getDnsWithEthernetType(context, ethernet_type);
    }
}
