package com.inspur.net.NetTest;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.NetworkAbility;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.Toast;


public class EthernetMediaTypeActivity extends AppCompatActivity implements OnClickListener, OnCheckedChangeListener {
    private static final String TAG = "NetTest";

    public static final int UNKNOWN_MODE = -1;
    public static final int DHCP_MODE = 0;
    public static final int STATIC_MODE = 1;

    private Button m_btOK;
    private RadioButton m_radioDhcp, m_radioStatic;
    private TextView m_textMac;
    private EditText m_EditIP, m_EditMask, m_EditGateway, m_EditDNS;
    private MyBroadcastReceiver myBroadcastReceiver;

    private int m_NetType;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ethernet_wan_type);

        //找到控件
        initView();

        //设置点击事件
        initClickEvent();

        //初始化动态广播
        initBroadcastReceiver();

        //getMac
        m_textMac.setText(EthernetHelper.getMac());

        m_NetType = UNKNOWN_MODE;
    }

    private void initView()
    {
        m_textMac = (TextView)getWindow().findViewById(R.id.textViewMac);

        m_radioDhcp = (RadioButton)getWindow().findViewById(R.id.radioBt_dhcp);
        m_radioStatic = (RadioButton)getWindow().findViewById(R.id.radioBt_static);

        m_EditIP = (EditText)getWindow().findViewById(R.id.editTextIp);
        m_EditMask = (EditText)getWindow().findViewById(R.id.editTextMask);
        m_EditGateway = (EditText)getWindow().findViewById(R.id.editTextGateWay);
        m_EditDNS = (EditText)getWindow().findViewById(R.id.editTextDns);

        m_btOK = (Button)getWindow().findViewById(R.id.btOK);
    }

    private void initClickEvent()
    {
        m_btOK.setOnClickListener(this);
        m_radioDhcp.setOnCheckedChangeListener(this);
        m_radioStatic.setOnCheckedChangeListener(this);
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

            if (intent.getAction().equals(ConnectivityManager.CONNECTIVITY_ACTION)) {

                int netType = intent.getIntExtra(ConnectivityManager.EXTRA_NETWORK_TYPE, 9);
                ConnectivityManager connectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);

                NetworkInfo mInfo = connectivityManager.getNetworkInfo(netType);

                if (mInfo != null && mInfo.isConnected()){

                    Log.d(TAG, "connected");

                    //Toast.makeText(context, "网络连接成功", Toast.LENGTH_LONG).show();

                    String ethernet_mode = EthernetHelper.getConnectModeWithType(context, NetworkAbility.NETWORK_TYPE_MEDIA);
                    updateAddressGetWay(ethernet_mode);

                    m_EditIP.setText(EthernetHelper.getIpAddress(context, NetworkAbility.NETWORK_TYPE_MEDIA));
                    m_EditMask.setText(EthernetHelper.getNetMask(context, NetworkAbility.NETWORK_TYPE_MEDIA));
                    m_EditGateway.setText(EthernetHelper.getGateWay(context, NetworkAbility.NETWORK_TYPE_MEDIA));
                    m_EditDNS.setText(EthernetHelper.getDns(context, NetworkAbility.NETWORK_TYPE_MEDIA));
                }else{

                    //Toast.makeText(context, "网络断开", Toast.LENGTH_LONG).show();
                    m_EditIP.setText("");
                    m_EditMask.setText("");
                    m_EditGateway.setText("");
                    m_EditDNS.setText("");
                }
            }
        }
    }


    @Override
    public void onCheckedChanged(CompoundButton buttonView, boolean isChecked){

        if (isChecked) {
            switch (buttonView.getId()) {
                case R.id.radioBt_dhcp:
                    m_NetType = DHCP_MODE;

                    m_EditIP.setFocusable(false);
                    m_EditIP.setFocusableInTouchMode(false);

                    m_EditMask.setFocusable(false);
                    m_EditMask.setFocusableInTouchMode(false);

                    m_EditGateway.setFocusable(false);
                    m_EditGateway.setFocusableInTouchMode(false);

                    m_EditDNS.setFocusable(false);
                    m_EditDNS.setFocusableInTouchMode(false);

                    break;
                case R.id.radioBt_static:
                    m_NetType = STATIC_MODE;

                    m_EditIP.setFocusableInTouchMode(true);
                    m_EditIP.setFocusable(true);

                    m_EditMask.setFocusableInTouchMode(true);
                    m_EditMask.setFocusable(true);

                    m_EditGateway.setFocusableInTouchMode(true);
                    m_EditGateway.setFocusable(true);

                    m_EditDNS.setFocusableInTouchMode(true);
                    m_EditDNS.setFocusable(true);

                    m_EditIP.requestFocus();
                    break;
            }
        }
    }

    @Override
    public void onClick(View v){

        switch (v.getId()){
            case R.id.btOK:
                if (m_NetType == DHCP_MODE) {

                    Log.d(TAG, "current mode is dhcp!");
                    EthernetHelper.setDhcpConfig(this, NetworkAbility.NETWORK_TYPE_MEDIA);
                }else if (m_NetType == STATIC_MODE){

                    Log.d(TAG, "current mode is static!");
                    String ip = m_EditIP.getText().toString();
                    String mask = m_EditMask.getText().toString();
                    String gateway = m_EditGateway.getText().toString();
                    String dns = m_EditDNS.getText().toString();

                    if (ip.length() > 0 && mask.length() > 0 && gateway.length() > 0 && dns.length() > 0) {

                        EthernetHelper.setStaticConfig(this, NetworkAbility.NETWORK_TYPE_MEDIA, ip, mask, gateway, dns);
                    }
                    else {

                        NetworkTools.showMessage(this, "输入信息非法");
                    }
                }else{
                    NetworkTools.showMessage(this,"请选择地址类型");
                }
                break;
            default:
                break;
        }
    }

    private void updateAddressGetWay(String mode) {

        if (mode.equals(EthernetHelper.ETHERNET_CONN_MODE_DHCP)){

            m_radioDhcp.setChecked(true);
        }else if(mode.equals(EthernetHelper.ETHERNET_CONN_MODE_MANUAL)){

            m_radioStatic.setChecked(true);
        }else{
            ;
        }
    }

}