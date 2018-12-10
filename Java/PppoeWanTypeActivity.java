package com.inspur.net.NetTest;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.EthernetManager;
import android.net.LinkProperties;
import android.net.NetworkAbility;
import android.net.NetworkInfo;
import android.net.NetworkUtils;
import android.net.PppoeConfiguration;
import android.net.PppoeManager;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.util.Log;
import android.widget.EditText;
import android.widget.Toast;

public class PppoeWanTypeActivity extends AppCompatActivity implements OnClickListener {

    private static final String TAG = "NetTest";

    private Button m_dial;
    private EditText m_userName, m_password;
    private MyBroadcastReceiver myBroadcastReceiver;

    private PppoeManager mPppoeManager;
    private EthernetManager mEthernetManager;
    private boolean m_first_enter_flag;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pppoe_wan_type);

        initView();
        initClickEvent();

        initBroadcastReceiver();
    }

    private void initView()
    {
        m_userName = (EditText)getWindow().findViewById(R.id.edit_userName);
        m_password = (EditText)getWindow().findViewById(R.id.edit_passwd);
        m_dial = (Button)getWindow().findViewById(R.id.bt_dial);
        mEthernetManager = null;
        mPppoeManager = null;
        m_first_enter_flag = true;
    }

    private void initClickEvent()
    {
        m_dial.setOnClickListener(this);
    }

    private void initBroadcastReceiver()
    {
        myBroadcastReceiver = new MyBroadcastReceiver();

        IntentFilter filter = new IntentFilter();
        filter.addAction("android.net.conn.CONNECTIVITY_CHANGE");

        registerReceiver(myBroadcastReceiver, filter);
    }

    @Override
    protected void onDestroy()
    {
        if(myBroadcastReceiver != null)
            unregisterReceiver(myBroadcastReceiver);
        super.onDestroy();
    }

    class MyBroadcastReceiver extends BroadcastReceiver {

        @Override
        public void onReceive(Context context, Intent intent) {

            if (m_first_enter_flag == false) {
                String action = intent.getAction();
                Log.d(TAG, "action is " + action);

                handleEvent(context, intent, action);
            }else{
                getPppoeLinkStateAndShow();
                m_first_enter_flag = false;
            }
        }
    }

    private void handleEvent(Context context, Intent intent, String action)
    {
        if (action.equals(ConnectivityManager.CONNECTIVITY_ACTION)) {

            int netType = intent.getIntExtra(ConnectivityManager.EXTRA_NETWORK_TYPE, 9);
            Log.d(TAG, "get the netType is " + netType);

            ConnectivityManager connectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
            if(connectivityManager == null){
                return ;
            }

            //get networkInfo
            NetworkInfo netInfo = connectivityManager.getNetworkInfo(netType);
            Log.d(TAG, "get the netinfo is " + netInfo);

            if(netInfo != null) {

                if (netInfo.getDetailedState() == NetworkInfo.DetailedState.CONNECTED) {
                    String ifname = getIfnameFromType(netType);
                    if (ifname.equals("ppp0")) {

                        Toast.makeText(context, "拨号成功", Toast.LENGTH_LONG).show();
                    } else {
                        //other network
                    }
                } else {
                    getmEthernetManager();
                    //get ifname status
                    int netlinkstatus = NetworkUtils.getNetlinkStatus(mEthernetManager.getNetworkAbility().getInterfaceName(NetworkAbility.NETWORK_TYPE_WAN));
                    if (netlinkstatus == 1) {
                        Toast.makeText(context, "拨号失败", Toast.LENGTH_LONG).show();
                    } else {
                        Toast.makeText(context, "网线已拔出", Toast.LENGTH_LONG).show();
                    }
                }
            }
        }
    }

    private String getIfnameFromType(int netType) {
        if (netType <= 0) {

            Log.d(TAG, "netType is illegal");
            return null;
        }

        //get connectivityManager
        ConnectivityManager connectivityManager = (ConnectivityManager) this.getSystemService(Context.CONNECTIVITY_SERVICE);
        LinkProperties linkProperties = connectivityManager.getLinkProperties(netType);

        Log.d(TAG, "linkproperties is " + linkProperties);
        return linkProperties.getInterfaceName();
    }

    private void getPppoeLinkStateAndShow()
    {
        ConnectivityManager connectivityManager = (ConnectivityManager) this.getSystemService(Context.CONNECTIVITY_SERVICE);
        if (connectivityManager == null){
            return;
        }

        //getmPppoeManager();
        //getmEthernetManager();
        //PppoeConfiguration pppoeConfiguration =  mPppoeManager.getConfig(mEthernetManager.getNetworkAbility().getInterfaceName(NetworkAbility.NETWORK_TYPE_WAN));
        //Log.d(TAG, "username is " + pppoeConfiguration.getPppoeUsername() + "passwd is " + pppoeConfiguration.getPppoePasswd());

        NetworkInfo mInfo = connectivityManager.getNetworkInfo(ConnectivityManager.TYPE_PPPOE);
        Log.d(TAG, "mInfo is " + mInfo);

        if(mInfo != null) {
            NetworkInfo.DetailedState state = mInfo.getDetailedState();
            String ifname = getIfnameFromType(ConnectivityManager.TYPE_PPPOE);
            if(ifname != null) {
                Log.d(TAG, "ifname: " + ifname + ", state: " + state);
                if (state == NetworkInfo.DetailedState.CONNECTED && ifname.equals("ppp0")){
                    Toast.makeText(this, "拨号网络已连接", Toast.LENGTH_LONG).show();
                }else{
                    Toast.makeText(this, "拨号网络未连接", Toast.LENGTH_LONG).show();
                }
            }
        } else {
            Log.d(TAG, "no avaliable network");
        }
    }

    public void onClick(View v) {

        switch (v.getId()) {
            case R.id.bt_dial:
                String username = m_userName.getText().toString();
                String passwd = m_password.getText().toString();

                Log.d(TAG, "username is " + username + ", passwd is " + passwd);

                startPppoe(username, passwd);
                break;
            default:
                break;
        }
    }

    private void getmEthernetManager()
    {
        if (mEthernetManager == null){
            mEthernetManager = (EthernetManager) this.getSystemService("inspur_ethernet");
            if (mEthernetManager == null) {
                Log.d(TAG, "failed to get inspur_ethernet, next to try " + Context.ETHERNET_SERVICE);
                mEthernetManager = (EthernetManager) this.getSystemService(Context.ETHERNET_SERVICE);
            }
        }
    }

    private void getmPppoeManager()
    {
        if (mPppoeManager == null) {
            mPppoeManager = (PppoeManager) this.getSystemService("inspur_pppoe");
            if (mPppoeManager == null) {
                Log.d(TAG, "failed to get inspur_pppoe, next to try " + Context.PPPOE_SERVICE);
                mPppoeManager = (PppoeManager) this.getSystemService(Context.PPPOE_SERVICE);
            }
        }
    }

    private void startPppoe(String userName, String passwd)
    {
        //getmPppoeManager
        getmPppoeManager();
        Log.d(TAG, "pppoemanager is " + mPppoeManager);

        //getmEthernetManager
        getmEthernetManager();
        Log.d(TAG, "ethernet manager is " + mEthernetManager);

        String ifname = mEthernetManager.getNetworkAbility().getInterfaceName(NetworkAbility.NETWORK_TYPE_WAN);
        Log.d(TAG, "get the ifname from wan type is " + ifname);

        mPppoeManager.connect(userName, passwd, ifname);
    }
}