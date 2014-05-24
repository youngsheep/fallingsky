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

import android.content.Intent;
import android.os.Bundle;
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
    	
    	return glSurfaceView;
    }

    public void doWeiboAuth(){
        Log.e("doWeiboAuth", "doWeiboAuth enter!");
        // ???å§????å¾????å¯¹è±¡
        mWeiboAuth = new WeiboAuth(this, APP_KEY, REDIRECT_URL, SCOPE);
        mSsoHandler = new SsoHandler(HelloCpp.this, mWeiboAuth);
        mSsoHandler.authorize(new AuthListener());
    }

    /**
     * å½? SSO ?????? Activity ?????ºæ?¶ï??è¯¥å?½æ?°è??è°???¨ã??
     * 
     * @see {@link Activity#onActivityResult}
     */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        
        // SSO ?????????è°?
        // ???è¦?ï¼????èµ? SSO ??»é????? Activity å¿?é¡»é????? onActivityResult
        if (mSsoHandler != null) {
            mSsoHandler.authorizeCallBack(requestCode, resultCode, data);
        }
    }

    /**
     * å¾????è®¤è???????????è°?ç±»ã??
     * 1. SSO ????????¶ï?????è¦???? {@link #onActivityResult} ä¸?è°???? {@link SsoHandler#authorizeCallBack} ???ï¼?
     *    è¯¥å??è°????ä¼?è¢???§è?????
     * 2. ??? SSO ????????¶ï??å½???????ç»???????ï¼?è¯¥å??è°?å°±ä??è¢???§è?????
     * å½????????????????ï¼?è¯·ä??å­?è¯? access_token???expires_in???uid ç­?ä¿¡æ????? SharedPreferences ä¸????
     */
    class AuthListener implements WeiboAuthListener {
        
        @Override
        public void onComplete(Bundle values) {
            // ä»? Bundle ä¸?è§£æ?? Token
            mAccessToken = Oauth2AccessToken.parseAccessToken(values);
            if (mAccessToken.isSessionValid()) {
                // ??¾ç¤º Token
                //updateTokenView(false);
                
                // ä¿?å­? Token ??? SharedPreferences
                //AccessTokenKeeper.writeAccessToken(HelloCpp.this, mAccessToken);
                Toast.makeText(HelloCpp.this, 
                        "auth success!", Toast.LENGTH_SHORT).show();
            } else {
                // å½???¨æ³¨??????åº???¨ç??åº?ç­¾å??ä¸?æ­£ç¡®??¶ï??å°±ä????¶å?? Codeï¼?è¯·ç¡®ä¿?ç­¾å??æ­£ç¡®
                String code = values.getString("code");
                String message = "auth fail!";//getString(R.string.weibosdk_demo_toast_auth_failed);
                if (code != null && code != "") {
                    message = message + "\nObtained the code: " + code;
                }
                Toast.makeText(HelloCpp.this, message, Toast.LENGTH_LONG).show();
            }
            HelloCpp.this.OnWeiboAuth(mAccessToken.getUid(),mAccessToken.getToken());
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

    /** å¾???? Web ????????¥å?£ç±»ï¼????ä¾???»é??ç­???????  */
    private WeiboAuth mWeiboAuth;
    /** æ³¨æ??ï¼?SsoHandler ä»?å½? SDK ?????? SSO ??¶æ????? */
    private SsoHandler mSsoHandler;
    /** ??·å????°ç?? Token */
    private Oauth2AccessToken mAccessToken;

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
