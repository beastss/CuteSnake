package org.cocos2dx.lib;

import java.security.MessageDigest;

import com.umeng.analytics.game.UMGameAgent;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.os.Handler;
import android.telephony.TelephonyManager;
import android.util.Base64;
import android.util.Log;
import android.widget.Toast;

public class PayAndroidApi {
	private static final String LOG_TAG = "PayAndroidApi";

	public static PayAndroidApi actInstance = null;// ���嵥��
	public static Context mContext = null;// ���嵥��
	private static boolean mbDebug = true;
	protected static Handler sMainThreadHandler = null;
	private DongXinPush mPush;
	public static Object rtnActivity() {
		return actInstance;
	}	

	ExternSdkInterface sdkObj;

	public PayAndroidApi(Context context) {
		mContext = context;
		actInstance = this;
		init();
		if (null == sMainThreadHandler) {
			sMainThreadHandler = new Handler();
		}
	}

	private void init() {
		sdkObj = new TemplateSdk(mContext);
		mPush = new DongXinPush(mContext);
	}

	int itemId = 0;
	public void Purchase(int id) {
		itemId = id;
		runOnMainThread(new Runnable() {
			@Override
			public void run() {
				sdkObj.purchase(itemId);
			}
		});

	}

	public void exitGame() {
		sdkObj.exitGame();
	}
	
	public void startGame()
	{
		sdkObj.startGame();
	}

	public static void runOnMainThread(Runnable r) {
		if (null == sMainThreadHandler)
			return;
		sMainThreadHandler.post(r);
	}
	
	int toastIndex = 0;
	public void showToast(int index) {
		toastIndex = index;
		runOnMainThread(new Runnable() {
			@Override
			public void run() {
				String text = sdkObj.getTextByIndex(toastIndex);
				Toast.makeText(mContext, text, Toast.LENGTH_LONG).show();
			}
		});
	}
	
	static String toastText;
	public static void showToast(String text){
		toastText = text;
		runOnMainThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(mContext, toastText, Toast.LENGTH_LONG).show();
			}
		});
	}

	public void startStage(int stage)
	{
		Log.d(LOG_TAG, "startStage....");
		String str = "level_";
		str += stage;
		UMGameAgent.startLevel(str);
	}
	
	public void endStage(int stage, boolean win)
	{
		Log.d(LOG_TAG, "startStage...d");
		String str = "level_";
		str += stage;
		if(win)
		{
			UMGameAgent.finishLevel(str);
		}
		else
		{
			UMGameAgent.failLevel(str);
		}
	}
	
	public boolean isForBusiness()
	{
		return mPush.isBusinessMode();
	}
	
	public String getVerName() {
		String version = "V1.0.0";
		try {
			PackageManager manager = mContext.getPackageManager();
			PackageInfo info = manager.getPackageInfo(
					mContext.getPackageName(), 0);
			version = info.versionName;
			return version;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return version;
	}

	protected static void LogD(String msg) {
		if (mbDebug) {
			Log.d(LOG_TAG, msg);
		}
	}

	protected void LogE(String msg) {
		if (mbDebug) {
			Log.e(LOG_TAG, msg);
		}
	}
	
}
