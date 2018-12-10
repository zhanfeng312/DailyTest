package com.inspur.net.NetTest;

import android.app.AlertDialog;
import android.content.Context;
import android.net.NetworkUtils;

import java.net.Inet4Address;
import java.net.InetAddress;

/**
 * Created by fangzhf on 2018/4/27.
 * 包含一些公共接口，数字形式的ip和 String的转换、弹框显示接口
 */

public class NetworkTools {

    public static int stringToInt(String addrString) {
        try {
            if (addrString == null)
                return 0;
            String[] parts = addrString.split("\\.");
            if (parts.length != 4) {
                return 0;
            }

            int a = Integer.parseInt(parts[0]);
            int b = Integer.parseInt(parts[1]) << 8;
            int c = Integer.parseInt(parts[2]) << 16;
            int d = Integer.parseInt(parts[3]) << 24;

            return a | b | c | d;
        } catch (NumberFormatException ex) {

            return 0;
        }
    }

    public static String intToString(int ip)
    {
        return (ip & 0xFF) + "." + ((ip >> 8) & 0xFF) + "." + ((ip >> 16) & 0xFF) + "." + ((ip >> 24) & 0xFF);
    }

    public static void showMessage(Context context, String message){
        new AlertDialog.Builder(context)
                .setTitle("提示")
                .setMessage(message)
                .setPositiveButton("确定", null)
                .show();
    }
}
