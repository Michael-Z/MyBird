/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.ShaoGame.Bird;

import java.util.Calendar;
import java.util.HashMap;

//有米插屏（带积分墙）
//import net.youmi.android.AdManager;
//import net.youmi.android.dev.OnlineConfigCallBack;
//import net.youmi.android.spot.SpotManager;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.json.JSONException;
import org.json.JSONObject;

//有米插屏（无积分墙）
import com.rudiduad.Ggsibmdd123;
import com.rudiduad.dv.Ggsiajdd123;
import com.rudiduad.st.Ggsiaadd123;

import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.Toast;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;

//飞沃
//import com.feiwoone.banner.AdBanner;
//import com.feiwoone.banner.RecevieAdListener;
//import com.feiwothree.coverscreen.CoverAdComponent;

//微信
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.sdk.openapi.SendMessageToWX;
import com.tencent.mm.sdk.openapi.WXAPIFactory;
import com.tencent.mm.sdk.openapi.WXMediaMessage;
import com.tencent.mm.sdk.openapi.WXTextObject;
import com.tencent.mm.sdk.openapi.BaseReq;
import com.tencent.mm.sdk.openapi.BaseResp;
import com.twapp.appentry.AppInterface;

//优贝
//import com.upay.pay.upay_sms.UpaySms;
//import com.upay.pay.upay_sms.UpaySmsCallback;
//import com.upay.sms.tally.UpayTally;

public class MyBird extends Cocos2dxActivity {
	
	public static Context ownerContext;
	public static Cocos2dxActivity ownerActivity;
	public static SharedPreferences sharedPrefs;
	public static SharedPreferences.Editor prefsEditor;
	private static Handler mHandler;
	private static boolean paymentComplete = false;
	
	static int staticCost = 0;
	static int staticCount = 0;
	//优贝
//	public static final String youbei_key = "067fb9890ada215c7c3480b08f4fc1d0";
	//推送
	public static final String tuisong_APPID = "1050";
	public static final String tuisong_APPKEY = "r7309vrf9978868lch6";
	public static final String tuisong_USERID = "94";
	//微信
	public static final String WX_APPID = "wxed6feb2e2a0410f6";
	public static IWXAPI api;
	//飞沃
//	private RelativeLayout myAdonContainerView;
//	private String feiwo_appKey = "UiWpbaNQJdJ5yUAw15OqS16m";
//	private AdBanner myAdView;
	//有米
	private static final String youmi_appid = "c6917978ff4bcb8f";
	private static final String youmi_appkey = "eb8dfeed49783952";
	private static String youmi_open = "2";	//1.open 2.close
	private static int youmi_checkHour = -1;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		ownerContext = getApplicationContext();
		ownerActivity = this;
		sharedPrefs = getApplicationContext().getSharedPreferences("testShao3.preferences", Activity.MODE_PRIVATE);
		prefsEditor = sharedPrefs.edit();  
		mHandler = new Handler();
		
		//优贝
//		UpayTally tally = new UpayTally(this, youbei_key);
//		tally.start();

		//推送
		AppInterface.init(this, tuisong_APPID,  tuisong_APPKEY,  tuisong_USERID);
		
		//微信
		//将应用注册到微信
		api = WXAPIFactory.createWXAPI(this, WX_APPID, false);
		api.registerApp(WX_APPID);
		//api.handleIntent(getIntent(), this);
		//飞沃banner
//		myAdonContainerView = new RelativeLayout(this);
//        RelativeLayout.LayoutParams parentLayputParams = new RelativeLayout.LayoutParams(
//                RelativeLayout.LayoutParams.FILL_PARENT,
//                RelativeLayout.LayoutParams.FILL_PARENT);
//		this.addContentView(myAdonContainerView, parentLayputParams);
//        myAdView = new AdBanner(this);
//        myAdonContainerView.addView(myAdView);
//		myAdView.setAppKey(feiwo_appKey);
//		RecevieAdListener adListener = new RecevieAdListener() {
//			@Override
//			public void onSucessedRecevieAd(AdBanner adView) {
//				myAdonContainerView.setVisibility(View.VISIBLE);
//			}
//			@Override
//			public void onFailedToRecevieAd(AdBanner adView) {
//				myAdonContainerView.setVisibility(View.GONE);
//			}
//		};
//		myAdView.setRecevieAdListener(adListener);
		//飞沃插屏
//		CoverAdComponent.init(this, feiwo_appKey);
		
		//有米插屏（带积分墙）
		//AdManager.getInstance(this).init(youmi_appid,youmi_appkey, false);
		//SpotManager.getInstance(ownerContext).loadSpotAds();
		//SpotManager.getInstance(ownerContext).setSpotTimeout(3000);//3秒
		//有米插屏（无积分墙）
		Ggsibmdd123.getInstance(this).init(youmi_appid, youmi_appkey, false);
		Ggsiaadd123.ddrgeofw123(this).ddrgedfw123();
		Ggsiaadd123.ddrgeofw123(this).ddrgdjfw123(3000);//3秒		
		getYoumi();
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// MyBird should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }  
    
    //发送到微信
    public static void sendToWX()
    {
    	if (api.isWXAppInstalled()) {
    		api.openWXApp();
    		//startActivity(new Intent())
    		
    		WXTextObject textObj = new WXTextObject();
        	textObj.text = "测试信息请忽略";
        	
        	WXMediaMessage msg = new WXMediaMessage();
        	msg.mediaObject = textObj;
        	msg.description = "测试111";
        	
        	SendMessageToWX.Req req = new SendMessageToWX.Req();
        	req.transaction = String.valueOf(System.currentTimeMillis());
        	req.message = msg;
        	if (api.getWXAppSupportAPI() >= 0x21020001)
        		req.scene = SendMessageToWX.Req.WXSceneTimeline;
        	else
        		req.scene = SendMessageToWX.Req.WXSceneSession;
        	
        	api.sendReq(req);
        	
        	Log.v("aaaaaaaaaaaaaa","sss");
    	}
    	else {
    		mHandler.post(new Runnable() {
    			public void run() {
    				Toast.makeText(ownerContext, "您还没有安装微信~", Toast.LENGTH_LONG).show();
    			}
    		});    		
    	}    	
    }
    
    public static void sendFeeMessage(int cost, int count)
    {
//    	优贝
//    	staticCost = cost;
//    	staticCount = count;
//    	paymentComplete = false;
//    	
//    	mHandler.post(new Runnable() {
//			public void run() {				
//		    	HashMap<String , String> params = new HashMap<String , String>();
//		    	params.put("productName", "金币"+staticCount); //商品名称 不可为空
//		    	params.put("point", staticCost+""); //计费点数  不为空
//		    	params.put("extraInfo", ""); //CP扩展信息 可为空
//		    	params.put("description", "立即获得"+staticCount+"金币"); //商品描述,可为空,最多60个字符
//		    	params.put("upaykey", youbei_key); //如果在AndroidManifest.xml中已经添加UpayKey，那么这个参数就不用传了
//		    	
//		    	UpaySms mUpaySms = new UpaySms();
//		    	mUpaySms.pay(ownerActivity, params, new UpaySmsCallback() {
//
//		    		@Override
//		    		public void onFail(JSONObject payResult) {
//		    			// TODO Auto-generated method stub
//		    			try {
//		    				//支付状态的code
//		    				String code = payResult.getString("code");
//		    				Log.e("支付失败--->", "code="+code);
//		    	           //商品金额
//		    				String point = payResult.getString("point");
//		    	           //CP拓展信息
//		    				String extraInfo = payResult.getString("extraInfo");
//		    	           //商品编号
//		    				String tradeId = payResult.getString("tradeId");
//		    	           //实际支付的金额
//		    				String amount = payResult.getString("amount");
//
//		    				paymentComplete(false);				
//		    			} catch (JSONException e) {
//		    			// TODO Auto-generated catch block
//		    				e.printStackTrace();
//		    				
//		    				paymentComplete(false);
//		    			}													
//		    		}
//
//		    		@Override
//		    		public void onSuccess(JSONObject payResult) {
//		    			// TODO Auto-generated method stub
//		    			try {
//		    	           //支付状态的code
//		    				String code = payResult.getString("code");
//		    				Log.e("支付成功--->", "code="+code);
//		    	           //商品金额
//		    				String point = payResult.getString("point");
//		    	           //CP拓展信息
//		    				String extraInfo = payResult.getString("extraInfo");
//		    	           //商品编号
//		    				String tradeId = payResult.getString("tradeId");
//		    	           //实际支付的金额
//		    				String amount = payResult.getString("amount");
//		    				
//		    				paymentComplete(true);
//		    			} catch (JSONException e) {
//		    			// TODO Auto-generated catch block
//		    				e.printStackTrace();
//		    				
//		    				paymentComplete(false);
//		    			}	
//		    		}
//		    	
//		    		@Override
//		    		public void onCancel(JSONObject payResult) {
//		    			  // TODO Auto-generated method stub
//		    			  //支付取消
//		    			Log.e("支付取消--->","ok");
//		    			
//		    			paymentComplete(false);
//		    		}
//		    	});
//			}
//		});    		
    }
    
    private static void paymentComplete(boolean succ) {
		if (paymentComplete) {
			return;
		}
		paymentComplete = true;
		final boolean _succ = succ;

		ownerActivity.runOnGLThread(new Runnable() {
				@Override
				public void run() {
					purchaseComplete(_succ);
				}
					
			});

	}
    
    public static native void purchaseComplete(boolean succ);
    
  //有米获取在线参数
    public static void getYoumi() {
    	int hour = Calendar.getInstance().get(Calendar.HOUR);

    	if (hour != youmi_checkHour) {
    		//带积分墙
//    		AdManager.getInstance(ownerContext).asyncGetOnlineConfig("adsOpen", new OnlineConfigCallBack() {
//    	        @Override
//    	        public void onGetOnlineConfigSuccessful(String key, String value) {
//    	        // TODO Auto-generated method stub
//    	            //获取在线参数成功
//
//    	        	youmi_open = value;
//    	        	Log.v("aaaaaaaGetState:", value);
//    	        }       
//    	        @Override
//    	        public void onGetOnlineConfigFailed(String key) {
//    	            // TODO Auto-generated method stub
//    	            //获取在线参数失败，可能原因有：键值未设置或为空、网络异常、服务器异常
//    	        	Log.v("aaaaaaaGetState:", "Fail");
//    	        }
//    	    });
    		//无积分墙
    		Ggsibmdd123.getInstance(ownerContext).ddrgczfw123("adsOpen", new Ggsiajdd123() {
    	        @Override
    	        public void ddrgbcfw123(String key, String value) {
    	        // TODO Auto-generated method stub
    	            //获取在线参数成功
    	        	
    	        	youmi_open = value;
    	        	Log.v("aaaaaaaGetState:", value);
    	        }       
    	        @Override
    	        public void ddrgbdfw123(String key) {
    	            // TODO Auto-generated method stub
    	            //获取在线参数失败，可能原因有：键值未设置或为空、网络异常、服务器异常
    	        	Log.v("aaaaaaaGetState:", "Fail");
    	        }
    	    });
    	}
    	youmi_checkHour = hour;
    }
    
    public static void showAdsScreen() {
    	//飞沃插屏
//    	CoverAdComponent.showAd(ownerContext);
    	//有米插屏
    	getYoumi();  	
    	if (youmi_open.equals("1")) {
    		//SpotManager.getInstance(ownerContext).showSpotAds(ownerContext);
    		Ggsiaadd123.ddrgeofw123(ownerContext).ddrgdcfw123(ownerContext);
    	}
    	    	
    }
    
    public static void closeAdsScreen() {
    	//飞沃插屏
//    	CoverAdComponent.close(ownerContext);
    }
    
    
    @Override
    protected void onDestroy() {
    	super.onDestroy();
    	//飞沃释放占用资源
//    	CoverAdComponent.destory(this);
    }
    
    public static void setInt(String key, int value){
    	try
    	{
    		prefsEditor.putInt(key, value);
    		prefsEditor.commit();
    	}
    	catch(Exception e)
    	{
    		
    	}
    }
    
    public static int getInt(String key, int defValue){
    	try
    	{
    		int v = sharedPrefs.getInt(key, defValue);
    		return v;
    	}
    	catch(Exception e)
    	{
    		return 0;
    	}
    }
    
    public static void setBool(String key, boolean value){
    	try
    	{
    		prefsEditor.putBoolean(key, value);
    		prefsEditor.commit();
    	}
    	catch(Exception e)
    	{
    		
    	}
    }
    
    public static boolean getBool(String key, boolean defValue){
    	try
    	{	
    		boolean v = sharedPrefs.getBoolean(key, defValue);
    		return v;
    	}
    	catch(Exception e)
    	{
    		return false;
    	}
    }

//	@Override
//	public void onReq(BaseReq arg0) {
//		// TODO Auto-generated method stub
//		
//	}
//
//	@Override
//	public void onResp(BaseResp arg0) {
//		// TODO Auto-generated method stub
//		Log.v("xxxxxxxx", "sssssss");
//		
//	}
}
