package com.inspur.net.NetTest;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends AppCompatActivity implements OnClickListener {

    private Button m_singleNetBt = null;
    private Button m_wanEthernetBt = null;
    private Button m_mediaEthernetBt = null;
    private Button m_pppoe_wanBt = null;
    private Button m_pppoe_mediaBt = null;
    private Button m_wifiBt = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        m_singleNetBt = (Button)getWindow().findViewById(R.id.bt_single_eth);
        m_singleNetBt.setOnClickListener(this);

        m_wanEthernetBt = (Button)getWindow().findViewById(R.id.bt_eth_wan);
        m_wanEthernetBt.setOnClickListener(this);

        m_mediaEthernetBt = (Button)getWindow().findViewById(R.id.bt_eth_media);
        m_mediaEthernetBt.setOnClickListener(this);

        m_pppoe_wanBt = (Button)getWindow().findViewById(R.id.bt_pppoe_wan);
        m_pppoe_wanBt.setOnClickListener(this);

        m_pppoe_mediaBt = (Button)getWindow().findViewById(R.id.bt_pppoe_media);
        m_pppoe_mediaBt.setOnClickListener(this);

        m_wifiBt = (Button)getWindow().findViewById(R.id.bt_wifi);
        m_wifiBt.setOnClickListener(this);
    }

    @Override
    public void onClick(View v){
        switch (v.getId()){
            case R.id.bt_single_eth:
                Intent intent_single_ethernet = new Intent(MainActivity.this, SingleEthernetActivity.class);
                startActivity(intent_single_ethernet);
                break;
            case R.id.bt_eth_wan:
                Intent intent_ethernet_wan_type = new Intent(MainActivity.this, EthernetWanTypeActivity.class);
                startActivity(intent_ethernet_wan_type);
                break;
            case R.id.bt_eth_media:
                Intent intent_ethernet_media_type = new Intent(MainActivity.this, EthernetMediaTypeActivity.class);
                startActivity(intent_ethernet_media_type);
                break;
            case R.id.bt_pppoe_wan:
                Intent intent_pppoe_wan = new Intent(MainActivity.this, PppoeWanTypeActivity.class);
                startActivity(intent_pppoe_wan);
                break;
            case R.id.bt_pppoe_media:
                Intent intent_pppoe_media = new Intent(MainActivity.this, PppoeMediaTypeActivity.class);
                startActivity(intent_pppoe_media);
                break;
            case R.id.bt_wifi:
                Intent intent_wifi = new Intent(MainActivity.this, WifiActivity.class);
                startActivity(intent_wifi);
                break;
            default:
                break;
        }
    }
}