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
import android.net.PppoeManager;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.util.Log;
import android.widget.EditText;

public class PppoeMediaTypeActivity extends AppCompatActivity implements OnClickListener {

    private static final String TAG = "NetTest";

    private Button m_dial;
    private EditText m_userName, m_password;
    private MyBroadcastReceiver myBroadcastReceiver;

    private PppoeManager mPppoeManager;
    private EthernetManager mEthernetManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pppoe_media_type);

        initView();
        initClickEvent();

        initBroadcastReceiver();
    }

    private void initView()
    {
        m_userName = (EditText)getWindow().findViewById(R.id.edit_userName);
        m_password = (EditText)getWindow().findViewById(R.id.edit_passwd);
        m_dial = (Button)getWindow().findViewById(R.id.bt_dial);
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

            String action = intent.getAction();
            Log.d(TAG, "action is " + action);

            if (action.equals(ConnectivityManager.CONNECTIVITY_ACTION)) {

                int netType = intent.getIntExtra(ConnectivityManager.EXTRA_NETWORK_TYPE, 9);
                ConnectivityManager connectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);

                NetworkInfo mInfo = connectivityManager.getNetworkInfo(netType);
                Log.d(TAG, "get the mInfo is " + mInfo);
                LinkProperties linkProperties = connectivityManager.getLinkProperties(netType);
                Log.d(TAG, "get the linkProperties is " + linkProperties);

                if (mInfo != null && mInfo.isConnected()){

                    Log.d(TAG, "connected");
                }else{

                    Log.d(TAG, "disconnected");
                }
            }
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

    private void startPppoe(String userName, String passwd)
    {
        //get pppoemanager
        mPppoeManager = (PppoeManager)this.getSystemService("inspur_pppoe");
        if(mPppoeManager == null) {
            Log.d(TAG, "failed to get inspur_pppoe, next to try " + Context.PPPOE_SERVICE);
            mPppoeManager = (PppoeManager)this.getSystemService(Context.PPPOE_SERVICE);
        }

        Log.d(TAG, "get the pppoemanager is " + mPppoeManager);

        mEthernetManager = (EthernetManager)this.getSystemService("inspur_ethernet");
        if (mEthernetManager == null) {
            Log.d(TAG, "failed to get inspur_ethernet, next to try " + Context.ETHERNET_SERVICE);
            mEthernetManager = (EthernetManager)this.getSystemService(Context.ETHERNET_SERVICE);
        }

        Log.d(TAG, "get the ethernet manager is " + mEthernetManager);

        String ifname =  mEthernetManager.getNetworkAbility().getInterfaceName(NetworkAbility.NETWORK_TYPE_MEDIA);

        mPppoeManager.connect(userName, passwd, ifname);
    }
}