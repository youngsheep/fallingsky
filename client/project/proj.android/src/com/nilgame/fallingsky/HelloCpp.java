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
package com.nilgame.fallingsky;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.view.KeyEvent;
import android.app.AlertDialog;
import android.view.View.OnClickListener;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.widget.Toast;
import android.util.Log;

import com.sina.weibo.sdk.auth.Oauth2AccessToken;
import com.sina.weibo.sdk.auth.WeiboAuth;
import com.sina.weibo.sdk.auth.WeiboAuthListener;
import com.sina.weibo.sdk.auth.sso.SsoHandler;
import com.sina.weibo.sdk.exception.WeiboException;

public class HelloCpp extends Cocos2dxActivity{
    private static HelloCpp s_inst = null;

    public static Object getInst(){
        return s_inst;
    }

    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
                s_inst = this;
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// HelloCpp should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
        mAccessToken = AccessTokenKeeper.readAccessToken(this);
        
    	return glSurfaceView;
    }

    private void updateResultsInUi() {
        try{
        Log.e("fallingksy", "doWeiboAuth enter!");
        mWeiboAuth = new WeiboAuth(this, APP_KEY, REDIRECT_URL, SCOPE);
        mSsoHandler = new SsoHandler(HelloCpp.this, mWeiboAuth);
        mSsoHandler.authorize(new AuthListener());            
        }
        catch(Exception ex)
        {
            Log.e("fallingsky",ex.toString());
            ex.printStackTrace();
        }
    }

    public void doWeiboAuth(){
        if (mAccessToken.isSessionValid()) {
        	HelloCpp.this.OnWeiboAuth(mAccessToken.getUid(),mAccessToken.getToken());
        }
        else
        {
            Thread t = new Thread() {
                public void run() {
                    mHandler.post(mUpdateResults);
                }
            };
            t.start();        	
        }
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        
        if (mSsoHandler != null) {
            mSsoHandler.authorizeCallBack(requestCode, resultCode, data);
        }
    }

    @Override
    public boolean onKeyDown (int keyCode, KeyEvent event)
    {
        Log.e("fallingksy", "onKeyDown enter!");
    	if (keyCode == KeyEvent.KEYCODE_BACK)
    	{
    		AlertDialog.Builder adb = new AlertDialog.Builder(this);
    		adb.setPositiveButton(R.string.yes, new DialogInterface.OnClickListener() {
				@Override
				public void onClick(DialogInterface dialog, int which) {
					HelloCpp.this.finish();
				}
			});
    		adb.setNegativeButton(R.string.no, null);
    		adb.setTitle(R.string.quit_prompt);
    		adb.show();
    		return true;
    	}
    	return false;
    }

    class AuthListener implements WeiboAuthListener {
        
        @Override
        public void onComplete(Bundle values) {
            mAccessToken = Oauth2AccessToken.parseAccessToken(values);
            if (mAccessToken.isSessionValid()) {
                //updateTokenView(false);
                
                AccessTokenKeeper.writeAccessToken(HelloCpp.this, mAccessToken);
                Toast.makeText(HelloCpp.this, 
                        "auth success!", Toast.LENGTH_SHORT).show();
                        
                HelloCpp.this.OnWeiboAuth(mAccessToken.getUid(),mAccessToken.getToken());
            } else {
                String code = values.getString("code");
                String message = "auth fail!";//getString(R.string.weibosdk_demo_toast_auth_failed);
                if (code != null && code != "") {
                    message = message + "\nObtained the code: " + code;
                }
                Toast.makeText(HelloCpp.this, message, Toast.LENGTH_LONG).show();
            }
        }

        @Override
        public void onCancel() {
            Toast.makeText(HelloCpp.this, 
                    "auth cancel!", Toast.LENGTH_LONG).show();
        }

        @Override
        public void onWeiboException(WeiboException e) {
            Toast.makeText(HelloCpp.this, 
                    "Auth exception : " + e.getMessage(), Toast.LENGTH_LONG).show();
        }
    }

    private WeiboAuth mWeiboAuth;
    private SsoHandler mSsoHandler;
    private Oauth2AccessToken mAccessToken;

    final Handler mHandler = new Handler();
    final Runnable mUpdateResults = new Runnable() {
        public void run() {
            updateResultsInUi();
        }
    };

    public static final String  APP_KEY = "2698066879";
    public static final String  REDIRECT_URL = "https://api.weibo.com/oauth2/default.html";
    public static final String SCOPE = 
            "email,direct_messages_read,direct_messages_write,"
            + "friendships_groups_read,friendships_groups_write,statuses_to_me_read,"
            + "follow_app_official_microblog," + "invitation_write";


    public static native void OnWeiboAuth(String uid,String token);
    
    static {
        System.loadLibrary("cocos2dcpp");
    }   
}
