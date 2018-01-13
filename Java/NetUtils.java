package com.inspur.stbdw.network;

import java.io.IOException;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Enumeration;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.LinearGradient;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.PorterDuffXfermode;
import android.graphics.Bitmap.Config;
import android.graphics.PorterDuff.Mode;
import android.graphics.Shader.TileMode;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

import android.net.wifi.WifiManager;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

/**
 * the util class give some mothod to use
 * 
 * @author zlding
 * 
 */
public class NetUtils {
	// 鎶婁竴涓瓧绗︿覆杞寲鎴恑p鍦板潃 鍗虫槸鍊� 鐨� 褰㈠紡
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

	// 鍒ゆ柇鏄笉鏄痠p鍦板潃
	public static boolean isIpAddress(String value) {
		int start = 0;
		int end = value.indexOf('.');
		int numBlocks = 0;

		while (start < value.length()) {
			if (end == -1) {
				end = value.length();
			}

			try {
				int block = Integer.parseInt(value.substring(start, end));
				if ((block > 255) || (block < 0)) {
					return false;
				}
			} catch (NumberFormatException e) {
				return false;
			}

			numBlocks++;

			start = end + 1;
			end = value.indexOf('.', start);
		}
		Log.i("MARK", "numBlocks == 4 ==" + (numBlocks == 4));

		return numBlocks == 4;
	}
	
	 
	/**
	 * 鑾峰彇ip鍦板潃
	 * 
	 * @throws IOException
	 * 
	 */
	public static String getLocalIpAddress() throws IOException {
		String ip;
		try {
			for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();) {
				NetworkInterface intf = en.nextElement();
				for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) {
					InetAddress inetAddress = enumIpAddr.nextElement();
					if (!inetAddress.isLoopbackAddress()) {

						ip = inetAddress.getHostAddress();
						if (ip.length() > 13) {
							continue;
						}

						Log.i("MARK", "getLocalIpAddress ip==" + ip);
						return ip;
					}
				}
			}
		} catch (SocketException ex) {
			Log.e("WifiPreference IpAddress", ex.toString());
		}
		return "0.0.0.0";
	}

	public static String getLocalEthIpAddress() {
		String ip;
		try {
			for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();) {

				NetworkInterface intf = en.nextElement();
				if (intf.getName().toLowerCase().equals("eth0")) {
					for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) {
						InetAddress inetAddress = enumIpAddr.nextElement();
						if (!inetAddress.isLoopbackAddress()) {
							ip = inetAddress.getHostAddress();
							if (ip.length() > 13) {
								continue;
							}
							Log.i("MARK", "eth0 getLocalIpAddress ip==" + ip);
							return ip;
						}
					}
				}
			}
		} catch (SocketException ex) {
		}
		return "0.0.0.0";
	}

	// 閫氳繃ip鍦板潃鑾峰彇鏈湴mac
	public static String getLocalMacAddressFromIp(Context context) {
		 
		String mac_s = "";
		try {
			byte[] mac;
			Log.i("MARK", "InetAddress.getByName(getLocalIpAddress()) ==" + InetAddress.getByName(getLocalIpAddress()));
			NetworkInterface ne = NetworkInterface.getByInetAddress(InetAddress.getByName(getLocalIpAddress()));
			mac = ne.getHardwareAddress();
			mac_s = byte2hex(mac);
		} catch (Exception e) {
			e.printStackTrace();
		}
		Log.i("MARK", "mac_s==" + mac_s);
		return mac_s;
	}

	public static String byte2hex(byte[] b) {
		StringBuffer hs = new StringBuffer(b.length);
		String stmp = "";
		int len = b.length;
		for (int n = 0; n < len; n++) {
			stmp = Integer.toHexString(b[n] & 0xFF);
			if (stmp.length() == 1)
				hs = hs.append("0").append(stmp);
			else {
				hs = hs.append(stmp);
			}
		}
		return String.valueOf(hs);

	}

	public static String subString(String string) {
		String[] s = new String[6];
		if (null != string && string.length() > 6) {
			string = string.toUpperCase();
			s[0] = (String) string.subSequence(0, 2);
			s[1] = (String) string.subSequence(2, 4);
			s[2] = (String) string.subSequence(4, 6);
			s[3] = (String) string.subSequence(6, 8);
			s[4] = (String) string.subSequence(8, 10);
			s[5] = (String) string.subSequence(10, 12);
			return s[0] + ":" + s[1] + ":" + s[2] + ":" + s[3] + ":" + s[4] + ":" + s[5];
		}
		 //return "cd:19:a0:cc:dd:f5".toUpperCase();
		  return "";
	}

	public static String[] resolutionIP(String ip) {
		return ip.split("\\.");
	}

	/**
	 * string to ip
	 * 
	 * @param addr
	 * @return
	 */
	public static String getAddress(int addr) {
		return intToInetAddress(addr).getHostAddress();
	}

	public static InetAddress intToInetAddress(int hostAddress) {
		byte[] addressBytes = { (byte) (0xff & hostAddress), (byte) (0xff & (hostAddress >> 8)),
				(byte) (0xff & (hostAddress >> 16)), (byte) (0xff & (hostAddress >> 24)) };

		try {
			return InetAddress.getByAddress(addressBytes);
		} catch (UnknownHostException e) {
			throw new AssertionError();
		}
	}

	/**
	 * get the info if ethernet is connect
	 * 
	 * @param context
	 * @return
	 */
	public static boolean checkEthernet(Context context) {
		ConnectivityManager conn = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo networkInfo = conn.getNetworkInfo(ConnectivityManager.TYPE_ETHERNET);
		Log.i("MARK", "networkInfo.isConnected()==" + networkInfo.isConnected());
		return networkInfo.isConnected();
	}

	/**
	 * get the info if wifi is connect
	 * 
	 * @param wifiManager
	 * @return
	 */
	public static boolean IsWifiConn(WifiManager wifiManager) {
		if (wifiManager != null && WifiManager.WIFI_STATE_ENABLED == wifiManager.getWifiState()) {
			return (wifiManager.getConnectionInfo().getIpAddress() != 0);
		}
		return false;
	}

	/**
	 * get the state if pppoe is connect
	 * 
	 * @param context
	 * @return
	 */
	public static boolean isPppoeConn(Context context) {
		// PppoeManager mPppoeManager = (PppoeManager)
		// context.getSystemService(Context.PPPOE_SERVICE);
		// return mPppoeManager.getPppoeState() == 1;
		return false;
	}

	public static int prefixLengthToNetmaskInt(int prefixLength) throws IllegalArgumentException {
		if (prefixLength < 0 || prefixLength > 32) {
			throw new IllegalArgumentException("Invalid prefix length (0 <= prefix <= 32)");
		}
		int value = 0xffffffff << (32 - prefixLength);
		return Integer.reverseBytes(value);
	}

	 public static int netmaskIntToPrefixLength(int netmask)
	  {
	    return Integer.bitCount(netmask);
	  }
	/*
	 * 鏂囧瓧鍊掑奖娓愬彉
	 */
	public static void setTextShader(TextView textView, int flag) {
		String color1 = "#004e5565";
		String color2 = "#ffaeb3be";
		String color3 = "#ffffffff";
		String color4 = "#ff6e7584";
		String color5 = "#004a4f5b";
		LinearGradient shaders = null;
		if (flag == 0) {
			shaders = new LinearGradient(0, 0, 0, textView.getTextSize() + 10, Color.parseColor(color1),
					Color.parseColor(color2), TileMode.CLAMP);
		} else if (flag == 1) {
			shaders = new LinearGradient(0, 0, 0, textView.getTextSize() + 10, Color.parseColor(color4),
					Color.parseColor(color5), TileMode.CLAMP);
		} else {
			shaders = new LinearGradient(0, 0, 0, textView.getTextSize() + 10, Color.parseColor(color3),
					Color.parseColor(color3), TileMode.CLAMP);
		}
		textView.getPaint().setShader(shaders);
		textView.setText(textView.getText().toString());
	}

	/*
	 * 鍥剧墖鍊掑奖娓愬彉
	 */
	public static Bitmap reflected(View view, int flag) {
		// 鏁翠綋鐨勬姇褰�
		view.buildDrawingCache();
		Bitmap originalImage = view.getDrawingCache();
		if (null == originalImage) {
			return null;
		}

		int width = originalImage.getWidth();
		int height = originalImage.getHeight();

		Bitmap bitmapWithReflection = Bitmap.createBitmap(width, height, Config.ARGB_8888);
		Canvas canvas = new Canvas(bitmapWithReflection);

		Matrix matrix = new Matrix();
		matrix.preScale(1, 1);

		Bitmap reflectionImage = Bitmap.createBitmap(originalImage, 0, 0, width, height, matrix, false);
		canvas.drawBitmap(reflectionImage, 0, 0, null);

		// 绾挎�ф笎鍙�
		Paint paint = new Paint();
		LinearGradient shader = null;
		if (flag == 0) {
			shader = new LinearGradient(0, 0, 0, height, 0x00000000, 0x66ffffff, TileMode.MIRROR);
		} else {
			shader = new LinearGradient(0, 0, 0, height, 0x66ffffff, 0x00000000, TileMode.MIRROR);
		}
		paint.setShader(shader);
		paint.setXfermode(new PorterDuffXfermode(Mode.DST_IN));
		canvas.drawRect(0, 0, width, height, paint);
		canvas.save();
		canvas = null;
		return bitmapWithReflection;
	}
}
