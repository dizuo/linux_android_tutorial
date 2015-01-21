package com.dizuo.jnidemo;

import com.dizuo.jni_demo.R;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

public class MainActivity extends Activity {

	public long nativeContext = 0;
	
	JNI mJni = new JNI();
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		nativeContext = mJni.nativeInit();
		
		if (nativeContext != 0) {
			mJni.nativeTestCallback(nativeContext);
		}
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
