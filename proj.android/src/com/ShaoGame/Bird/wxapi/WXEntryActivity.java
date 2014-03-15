package com.ShaoGame.Bird.wxapi;


import com.tencent.mm.sdk.openapi.BaseReq;
import com.tencent.mm.sdk.openapi.BaseResp;
import com.tencent.mm.sdk.openapi.ConstantsAPI;
import com.tencent.mm.sdk.openapi.ShowMessageFromWX;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.sdk.openapi.WXAPIFactory;
import com.tencent.mm.sdk.openapi.WXAppExtendObject;
import com.tencent.mm.sdk.openapi.WXMediaMessage;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class WXEntryActivity extends Activity implements IWXAPIEventHandler{
	private String WX_APPID = "wxed6feb2e2a0410f6";
	private IWXAPI api; 
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        api = WXAPIFactory.createWXAPI(this,  
        		WX_APPID, false);  
        api.handleIntent(getIntent(), this); 
    }

	@Override
	public void onReq(BaseReq arg0) {
		// TODO Auto-generated method stub
		Log.v("1111111111", "222222222");
	}

	@Override
	public void onResp(BaseResp resp) {
		// TODO Auto-generated method stub
		Log.v("3333333333333", "444444444444");
		int result = 0;  
		  
//        switch (resp.errCode) {  
//        case BaseResp.ErrCode.ERR_OK:  
//            result = R.string.errcode_success;  
//            break;  
//        case BaseResp.ErrCode.ERR_USER_CANCEL:  
//            result = R.string.errcode_cancel;  
//            break;  
//        case BaseResp.ErrCode.ERR_AUTH_DENIED:  
//            result = R.string.errcode_deny;  
//            break;  
//        default:  
//            result = R.string.errcode_unknown;  
//            break;  
//        }  
  
        Toast.makeText(this, result, Toast.LENGTH_LONG).show();  
  
        // TODO 微信分享 成功之后调用接口  
        this.finish();  
	}

	
}