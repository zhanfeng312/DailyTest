#!/bin/sh

docker_exec_istb3_product()
{
    #su - yang -c "$6/build_carp.sh $1 $2 $3 $4 $5"
    if [ ! -x $6/build_carp.sh ]; then
        chmod u+x $6/build_carp.sh
    fi
    $6/build_carp.sh $1 $2 $3 $4 $5 $6
}

docker_exec_shandong_product()
{
    #su - yang -c "/mnt/build_env/lingzhi_server/mstar_sdk/shandong/6a801bd_1.0.3/build_carp.sh $1 $2 $3 $4 $5 $6"
    if [ ! -x $6/build_carp.sh ]; then
        chmod u+x $6/build_carp.sh
    fi
    $6/build_carp.sh $1 $2 $3 $4 $5 $6
}

docker_exec_zibo_product()
{
    #su - yang -c "/mnt/build_env/lingzhi_server/mstar_sdk/zibo/6a801bd_1.0.3/build_carp.sh $1 $2 $3 $4 $5 $6"
    if [ ! -x $6/build_carp.sh ]; then
        chmod u+x $6/build_carp.sh
    fi
    $6/build_carp.sh $1 $2 $3 $4 $5 $6
}

docker_exec_androidTV_product()
{
    #su - yang -c "/mnt/build_env/lingzhi_server/mstar_sdk/androidTV/6a801bd_1.0.3/build_carp.sh $1 $2 $3 $4 $5 $6"
    if [ ! -x $6/build_carp.sh ]; then
        chmod u+x $6/build_carp.sh
    fi
    $6/build_carp.sh $1 $2 $3 $4 $5 $6
}

docker_exec_columbia_product()
{
    #su - yang -c "/mnt/build_env/lingzhi_server/mstar_sdk/columbia/6a801bd_1.0.3/build_carp.sh $1 $2 $3 $4 $5 $6"
    if [ ! -x $6/build_carp.sh ]; then
        chmod u+x $6/build_carp.sh
    fi
    $6/build_carp.sh $1 $2 $3 $4 $5 $6
}

docker_exec_dolby_box_product()
{
    #su - yang -c "/mnt/build_env/lingzhi_server/mstar_sdk/dolby_box/6a801bd_1.0.3/build_carp.sh $1 $2 $3 $4 $5 $6"
    if [ ! -x $6/build_carp.sh ]; then
        chmod u+x $6/build_carp.sh
    fi
    $6/build_carp.sh $1 $2 $3 $4 $5 $6
}

docker_exec_etv_product()
{
    #su - yang -c "/mnt/build_env/lingzhi_server/mstar_sdk/etv/6a801bd_1.0.3/build_carp.sh $1 $2 $3 $4 $5 $6"
    if [ ! -x $6/build_carp.sh ]; then
        chmod u+x $6/build_carp.sh
    fi
    $6/build_carp.sh $1 $2 $3 $4 $5 $6
}

if [ "x${3}" = "xlocal_compile" ]; then

    groupadd -g $2 yang
    useradd -u $1 -g $2 yang

    chown $1:$2 /home/yang -R

    su - yang -c "chmod 700 /home/yang/.ssh"

    exec bash -c "su yang"
else
    code=${3} #istb3/lotus
    Product=${5} #服务器编译时指定的产品

    #调用docker前，需要获取到svn代码的下载目录，因为build_carp.sh会从该目录copy代码到Android编译目录 $8

    echo "start call docker_env compile product $Product, code is ${code}"
    if [ "x${code}" = "xistb3" ]; then
       docker_exec_istb3_product $3 $4 $5 $6 $7 $8
    else
        case $Product in
            android | android-tmall_box | android-xiamen_box | android-heilj_box | android-taiwan_box | android-xian_box | android-houma_box | android-common_box | android-linyi_6015c)
                docker_exec_shandong_product $3 $4 $5 $6 $7 $8
                ;;
            android-zibo | android-zibo_tv | android-zibo_box_zhihui)
                docker_exec_zibo_product $3 $4 $5 $6 $7 $8
                ;;
            androidTV        | android-worldcup    | android-costdown   | android-heilj_tv  | android-taiwan_tv   |   android-jinan_tv | android-english_tv  | android-common_tv  | android-houma_box_6012c1 | android-6012c1  | android-jiningdangyuan_6012c1 | android-zibo_6012c1_zhihui  | android-xiangtan_6012c1  | android-xian_6012c1 | android-linyi_6012c1 | android-english_6012c1 | android-sanzhouxunchi_6012c1 | android-jiningjinxiang_6012c1 | android-yantai_6012c1 | android-jinan_6012c1 | android-thirdparty)
                docker_exec_androidTV_product $3 $4 $5 $6 $7 $8
                ;;
            android-columbia | android-englishott)
                docker_exec_columbia_product $3 $4 $5 $6 $7 $8
                ;;
            android-Dolby_box)
                docker_exec_dolby_box_product $3 $4 $5 $6 $7 $8
                ;;
            android-wasu_ETV_box)
                docker_exec_etv_product $3 $4 $5 $6 $7 $8
                ;;
        esac
    fi
fi

