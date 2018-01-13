package com.inspur.stbdw.network;

import java.io.IOException;
import java.lang.reflect.Method;
import java.net.InetAddress;
import java.util.ArrayList;

import android.R.integer;
import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.EthernetManager;
import android.net.IpConfiguration;
import android.net.IpConfiguration.ProxySettings;
import android.net.LinkAddress;
import android.net.IpConfiguration.IpAssignment;
import android.net.NetworkAbility;
import android.net.StaticIpConfiguration;
import android.os.Build;
import android.util.Log;
import android.widget.GridView;
import android.widget.Toast;

import com.inspur.stbdw.util.ToastUtil;
import com.inspur.stbdw.util.Tools;
import com.inspur.stbfwui.L;

public class EthernetHelper {

	/**
	 * 网卡名称 TODO　mstar是否改接口，eth0是否需要动态获取
	 */
	private static String ethString = "eth0";
	private static EthernetManager mEthManager;
	private static Context context;
	private static ConnectivityManager mConnectivityManager;

	public EthernetHelper(Context context) {
        
        this.context = context;
	}

	/*
	 * private static EthernetDevInfo getEthernetDevInfo() { return
	 * mEthManager.getSavedEthConfig(); }
	 */
	/**
	 * 
	 */
	public static String getMacAddress() {
		// return getEthernetDevInfo().getMacAddress(ethString);
		return NetUtils.subString(NetUtils.getLocalMacAddressFromIp(context));
	}

	/**
	 * 连接方式 自动手动
	 * 
	 * @return EthernetDevInfo.ETHERNET_CONN_MODE_DHCP
	 *         EthernetDevInfo.ETHERNET_CONN_MODE_MANUAL
	 */
	public static String getConnectMode(Context context, int type) {
		String modeString = "";
		mEthManager = (EthernetManager) context.getSystemService(Context.ETHERNET_SERVICE);
		try {
			modeString = mEthManager.getConfiguration(type).getIpAssignment().name();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return modeString;
	}

	/**
	 * IP地址
	 * 
	 * @return
	 */
	@SuppressLint("NewApi") public static String getIpAddress(Context context,int type) {
		/*
		 * if
		 * (mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type)
		 * ) .getAddresses().size()>0) { return
		 * mConnectivityManager.getLinkProperties
		 * (NetworkAbility.translateEthernetNetworkType(type))
		 * .getAddresses().get(0).toString(); }else { return "0.0.0.0"; }
		 */
		String ipString = "0.0.0.0";
		/* try {
			ipString = NetUtils.getLocalIpAddress();
		} catch (IOException e) {
			e.printStackTrace();
		} */
		 mConnectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
			Log.i("MARK", "getNetMask ");
			Log.i("MARKTEST", "type== "+type +"  translateEthernetNetworkType="+NetworkAbility.translateEthernetNetworkType(type));
			try {

				if (mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type))!=null) {
					if (mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type)).getLinkAddresses().size() > 0) {
						Log.i("MARK", "if ");
						String ip = mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type))
								.getLinkAddresses().get(0).toString();
						// ip2="192.168.1.149/16"
						String[] ipArrary = ip.split("/");
						ipString =ipArrary[0]; 
					} else {
						ipString = "0.0.0.0";
					}
				}
				
				
			} catch (Exception e) {

				Log.i("MARK", "Exception!! ");
				e.printStackTrace();
			} 
		 
		return ipString;
	}

	/**
	 * NetMask
	 * 
	 * @return
	 */
	@TargetApi(Build.VERSION_CODES.L)
	public static String getNetMask(Context context,int type) {
		String mask = "";
		 mConnectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
		Log.i("MARK", "getNetMask ");
		try {

			if (mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type))!=null) {

			if (mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type)).getLinkAddresses().size() > 0) {
				Log.i("MARK", "if ");
				String ip2 = mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type))
						.getLinkAddresses().get(0).toString();
				// ip2="192.168.1.149/16"
				String[] prefix = ip2.split("/");
				mask = NetUtils.getAddress(NetUtils.prefixLengthToNetmaskInt(Integer.parseInt(prefix[1])));
			} else {
				mask = "0.0.0.0";
			}
			}
		} catch (Exception e) {

			Log.i("MARK", "Exception!! ");
			e.printStackTrace();
		} 
		
		/*mEthManager = (EthernetManager) context.getSystemService(Context.ETHERNET_SERVICE);
		try {
			int prefixLength = mEthManager.getConfiguration(type).getStaticIpConfiguration().ipAddress.getNetworkPrefixLength();
			mask=NetUtils.getAddress(NetUtils.prefixLengthToNetmaskInt(prefixLength));
		} catch (Exception e) {
			e.printStackTrace();
		}*/
		return mask;
	}

	/**
	 * RouteAddr 网关
	 * 
	 * @return
	 */
	@TargetApi(Build.VERSION_CODES.L)
	public static String getRouteAddr(Context context,int type) {

		String gatetString = "0.0.0.0";
	 	mConnectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);

		try {

			if (mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type))!=null) {

			Log.i("MARK", "route size==="+mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type)).getRoutes().size());
			for (int i = 0; i < mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type)).getRoutes().size(); i++) {
				gatetString = mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type)).getRoutes()
						.get(i).toString();
				Log.i("MARK", "route  "+i+" ==="+gatetString);
			     if (gatetString.startsWith("0.0.0.0")) {
					String[] temp=gatetString.split("->");
					String[] gateway=temp[1].split("eth");
					return gateway[0].trim();
				}
			
			} 
			}
			
		 
			 
			 
			
		} catch (Exception e) {
			e.printStackTrace();
		} 
		 //	  route size===2
		 // route  0 ===192.168.1.0/24 -> 0.0.0.0 eth0
		//  route  1 ===0.0.0.0/0 -> 192.168.1.1 eth0
		// 
		
		/*mEthManager = (EthernetManager) context.getSystemService(Context.ETHERNET_SERVICE);
		try {
			gatetString = mEthManager.getConfiguration(type).getStaticIpConfiguration().gateway.toString();
 		} catch (Exception e) {
			e.printStackTrace();
		}*/
		return gatetString;

	}

	/**
	 * DNS
	 * 
	 * @return
	 */
	@TargetApi(Build.VERSION_CODES.L)
	public static String getDnsAddr(Context context,int type) {
		String dns = "";
		 mConnectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);

		try {
			if (mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type))!=null) {

			if (mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type)).getDnsServers().size() > 0) {
				dns = mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type)).getDnsServers().get(0)
						.toString();
			} else {
				dns = "0.0.0.0";
			}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		// dnsStrings="/192.168.1.254"
		if (dns.contains("/")) {
			dns = dns.substring(1);
		} 
		/*mEthManager = (EthernetManager) context.getSystemService(Context.ETHERNET_SERVICE);
		try {
			dns = mEthManager.getConfiguration(type).getStaticIpConfiguration().dnsServers.get(0).toString();
 		} catch (Exception e) {
			e.printStackTrace();
		}*/
		return dns;
	}

	/**
	 * DNS2
	 * 
	 * @return
	 */
	@TargetApi(Build.VERSION_CODES.L)
	public static String getDns2Addr(Context context,int type) {
		String dns2 = "";
		 mConnectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);

		try {
			if (mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type))!=null) {

			if (mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type)).getDnsServers().size() > 1) {
				dns2 = mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type)).getDnsServers().get(1)
						.toString();
			} else {
				dns2 = "0.0.0.0";
			}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		if (dns2.contains("/")) {
			dns2 = dns2.substring(1);
		} 
		/*mEthManager = (EthernetManager) context.getSystemService(Context.ETHERNET_SERVICE);
		try {
			dns2 = mEthManager.getConfiguration(type).getStaticIpConfiguration().dnsServers.get(1).toString();
 		} catch (Exception e) {
			e.printStackTrace();
		}*/
		return dns2;

	}

	/**
	 * 设置是否可用 TODO 传入参数与标准接口不同
	 * 
	 * @param bool
	 * @param string
	 * @throws Exception
	 */
	public static void setEnabled(boolean flag, String string) throws Exception {

		/*
		 * try { mEthManager.setEthernetEnabled(flag);; } catch (Exception e) {
		 * L.e("设置有线网络是否可用"); throw e; }
		 */
		setEnabled(flag);
	}

	public static void setEnabled(boolean flag) {

		// mEthManager.setEthernetEnabled(flag);
		// ConnectivityManager.getInstance().getNetworkInfo(NetworkAbility.translateEthernetNetworkType(type)).setIsAvailable(flag);

	}

	public static void setConnectMode(Context context, String mode,int type) {

		mEthManager = (EthernetManager) context.getSystemService(Context.ETHERNET_SERVICE);
		IpConfiguration ipconf = new IpConfiguration();
		if (mode.equals(IpAssignment.DHCP.name())) {
			ipconf.setIpAssignment(IpAssignment.DHCP);
		} else if (mode.equals(IpAssignment.STATIC.name())) {
			ipconf.setIpAssignment(IpAssignment.STATIC);
		}

		mEthManager.setConfiguration(type,ipconf);

	}

	public static void setConnectMode(Context context, IpAssignment ipAssignment,int type) {

		mEthManager = (EthernetManager) context.getSystemService(Context.ETHERNET_SERVICE);
		IpConfiguration ipconf = new IpConfiguration();
		ipconf.setIpAssignment(ipAssignment);
		mEthManager.setConfiguration(type,ipconf);

	}

	 

	public static void setDHCPConfig(Context context,int type) {
		mEthManager = (EthernetManager) context.getSystemService(Context.ETHERNET_SERVICE);
		IpConfiguration ipconf = new IpConfiguration();
		ipconf.setIpAssignment(IpAssignment.DHCP);

		mEthManager.setConfiguration(type,ipconf);
	}

	public static void setStaticConfig(Context context, String ipAddress, String netmask, String gateway, String dns1,
			String dns2,int type) {
		mEthManager = (EthernetManager) context.getSystemService(Context.ETHERNET_SERVICE);
		//mConnectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);

	
		Log.i("MARK", "setStaticConfig  00!!");
		StaticIpConfiguration staticIpConfiguration = new StaticIpConfiguration();
		Log.i("MARK", "ipAddress==" + ipAddress + " netmask==" + netmask + " gateway==" + gateway + " dns1==" + dns1
				+ " dns2==" + dns2);
		if (!Tools.matchIP(ipAddress)) {
			Toast.makeText(context, "IP 不合法", Toast.LENGTH_SHORT).show();
		}
		if (!Tools.matchIP(netmask)) {
			Toast.makeText(context, "子网掩码 不合法", Toast.LENGTH_SHORT).show();
		}
		if (!Tools.matchIP(gateway)) {
			Toast.makeText(context, "网关 不合法", Toast.LENGTH_SHORT).show();
		}
		if (!Tools.matchIP(dns1)) {
			Toast.makeText(context, "首选DNS 不合法", Toast.LENGTH_SHORT).show();
		}
		

		if (Tools.matchIP(ipAddress) && Tools.matchIP(netmask) && Tools.matchIP(gateway) && Tools.matchIP(dns1)) {
			InetAddress ip = NetUtils.intToInetAddress(NetUtils.stringToInt(ipAddress));
			InetAddress gateAddress = NetUtils.intToInetAddress(NetUtils.stringToInt(gateway));
			InetAddress dns1Address = NetUtils.intToInetAddress(NetUtils.stringToInt(dns1));
			Log.i("MARK", "if  InetAddress   ip==="+ip+"  gateAddress==="+gateAddress+"  dns1Address==="+dns1Address);
			ArrayList<InetAddress> dnsList = new ArrayList<InetAddress>();
			dnsList.add(dns1Address);
			if (Tools.matchIP(dns2)) {
				InetAddress dns2Address = NetUtils.intToInetAddress(NetUtils.stringToInt(dns2));
				dnsList.add(dns2Address);
				Log.i("MARK", "if  dns2Address==="+ dns2Address );
			}
			

			Log.i("MARK", "if  11!!");
			
			

			//ArrayList<LinkAddress> addressList = new ArrayList<LinkAddress>();
			int prefixLength = NetUtils.netmaskIntToPrefixLength(NetUtils.stringToInt(netmask));
			Log.i("MARK", "if  netmask==="+netmask+"  prefixLength==="+prefixLength);

			
			LinkAddress linkAddress = new LinkAddress(ip, prefixLength);
			//addressList.add(linkAddress);
			staticIpConfiguration.ipAddress = linkAddress;
			staticIpConfiguration.gateway = gateAddress;
			staticIpConfiguration.dnsServers.addAll(dnsList);
			
			try {
				//mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type)).setLinkAddresses(addressList);
				//mConnectivityManager.getLinkProperties(NetworkAbility.translateEthernetNetworkType(type)).setDnsServers(dnsList);
				 
				Log.i("MARK", "if  22 staticIpConfiguration=="+staticIpConfiguration);
				IpConfiguration ipconf = new IpConfiguration(IpAssignment.STATIC,ProxySettings.NONE,staticIpConfiguration,null);
				/*ipconf.setStaticIpConfiguration(staticIpConfiguration);
				Log.i("MARK", "if  33!!");
				ipconf.setIpAssignment(IpAssignment.STATIC);*/
				
				
				/*try {
					 
					Class<?> cls =  Class.forName("com.android.server.ethernet.EthernetConfigStore");
					//Object obj= c.newInstance();
					Method method = cls.getDeclaredMethod("writeIpAndProxyConfigurations", new Class[] {IpConfiguration.class});
					method.invoke(cls.newInstance(), ipconf);
					 
				} catch (Exception e) {
					e.printStackTrace();
				}*/
				// mEthernetConfigStore = new EthernetConfigStore();
				mEthManager.setConfiguration(type,ipconf);
				Log.i("MARK", "if  44  setConfiguration ipconf=="+ipconf);
			} catch (Exception e) {
				Log.i("MARK", "if  Exception!!");
				e.printStackTrace();
			}
		} else {

		}

	}

	/**
	 * 保存网络设置
	 * 
	 * @param auto
	 * @param ipAddress
	 * @param netmask
	 * @param gateway
	 * @param dns1
	 * @param dns2
	 * @throws Exception
	 */
	public static void configEthernetV4(Context context, boolean auto, String ipAddress, String netmask,
			String gateway, String dns1, String dns2,int type) throws Exception {
		 
		if (auto) {
			setDHCPConfig(context,type);
		} else {
			Log.i("MARK", "setStaticConfig!");
			setStaticConfig(context, ipAddress, netmask, gateway, dns1, dns2,type);
		}
	}
}
