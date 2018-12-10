package com.inspur.net.NetTest;

import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

import java.util.List;

public class WifiActivity extends AppCompatActivity implements OnClickListener {
    private static final String TAG = "NetTest";

    private WifiTest mWifitest;
    Button m_openWifi = null;
    Button m_startScan = null;
    Button m_getListAndConnect = null;
    Button m_getConnectInfo = null;
    Button m_closeWifi = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_wifi);

        mWifitest = new WifiTest(this);

        m_openWifi = (Button)getWindow().findViewById(R.id.bt1);
        m_openWifi.setOnClickListener(this);

        m_startScan = (Button)getWindow().findViewById(R.id.bt2);
        m_startScan.setOnClickListener(this);

        m_getListAndConnect = (Button)getWindow().findViewById(R.id.bt3);
        m_getListAndConnect.setOnClickListener(this);

        m_getConnectInfo = (Button)getWindow().findViewById(R.id.bt4);
        m_getConnectInfo.setOnClickListener(this);

        m_closeWifi = (Button)getWindow().findViewById(R.id.bt5);
        m_closeWifi.setOnClickListener(this);
    }

    @Override
    public void onClick(View v){
        switch (v.getId()){
            case R.id.bt1:
                Log.d(TAG, "bt1 clicked, start openWifi");
                mWifitest.openWifi();

                Log.d(TAG, "current wifistate is " + mWifitest.getWifiState());
                while (mWifitest.getWifiState() == WifiManager.WIFI_STATE_ENABLING){

                    Thread.currentThread();
                    try{
                        Thread.sleep(100);
                    }catch (InterruptedException ie){
                    }
                }
                Log.d(TAG, "start openWifi success");
                break;
            case R.id.bt2:
                Log.d(TAG, "bt2 clicked, startScan");
                mWifitest.startScan();
                break;
            case R.id.bt3:
                Log.d(TAG, "bt3 clicked, start getScanResult and connect Inspur-fang");
                List<ScanResult> list = mWifitest.getScanResult();
                Log.d(TAG, "getScanResult size is " + list.size());
                for (ScanResult s : list){
                    if (s.SSID.equals("Inspur-fang")){

                        String ssid = "\"" + s.SSID + "\"";
                        String pwd = "\"" + "1234567890" + "\"";
                        Log.d(TAG, "start connect Inspur-fang");
                        mWifitest.connectWifi(ssid, pwd);
                        break;
                    }
                }
                break;
            case R.id.bt4:
                Log.d(TAG, "bt5 clicked, get current wifi info");
                Log.d(TAG, "current wifi info is " + mWifitest.getConnectionInfo());
                break;
            case R.id.bt5:
                Log.d(TAG, "bt5 clicked, close wifi");
                break;
            default:
                break;
        }
    }
}
