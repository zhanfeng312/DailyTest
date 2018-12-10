package com.inspur.net.NetTest;

/**
 * Created by fangzhf on 2018/3/7.
 * 封装了wifi 的操作类
 */

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.util.Log;

import java.util.List;

public class WifiTest {
    private static final String TAG = "NetTest";

    private WifiManager wifiManager; //wifi对象

    public WifiTest(Context context) {
        this.wifiManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);// 获取Wifi服务
    }

    //打开wifi
    public boolean openWifi() {

        if (!wifiManager.isWifiEnabled()) {
            Log.d(TAG, "we will setWifiEnabled");
            return wifiManager.setWifiEnabled(true);
        } else {
            Log.d(TAG, "wifi has been enaled");
            return false;
        }
    }

    //获取wifi状态
    public int getWifiState(){
        return wifiManager.getWifiState();
    }

    //扫描网络
    public void startScan(){
        wifiManager.startScan();
    }

    //获取wifi列表
    public List<ScanResult> getScanResult(){
        return wifiManager.getScanResults();
    }

    //连接热点
    public void connectWifi(String SSID, String pwd) {

        //construct wifiConfiguration
        WifiConfiguration config = new WifiConfiguration();

        config.SSID = SSID;
        config.preSharedKey = pwd;
        config.hiddenSSID = true;
        config.status = WifiConfiguration.Status.ENABLED;

        int wifiId = wifiManager.addNetwork(config);

        Log.d(TAG, "wifiId is " + wifiId);

        boolean iRet = wifiManager.enableNetwork(wifiId, true);

        Log.d(TAG, "iRet is " + iRet);
    }

    //是否连接成功
    public boolean isConnected(Context context){
        ConnectivityManager connectivityManager =
                (ConnectivityManager)context.getSystemService(context.CONNECTIVITY_SERVICE);

        NetworkInfo networkInfo = connectivityManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);

        if (networkInfo.isConnected()){
            return true;
        }else{
            return false;
        }
    }

    //获取当前已连接的wifi信息
    public String getConnectionInfo(){

        WifiInfo wifiInfo =  wifiManager.getConnectionInfo();

        WifiConfiguration wifiConf = null;
        List<WifiConfiguration>  configuredNetworks = wifiManager.getConfiguredNetworks();
        if (configuredNetworks != null){
            for(WifiConfiguration conf :  configuredNetworks){
                if (conf.networkId == wifiInfo.getNetworkId()){
                    wifiConf = conf;
                    break;
                }
            }
        }

        return null;
    }
}
