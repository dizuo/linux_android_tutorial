package com.dizuo.parking;

import com.dizuo.jni_demo.R;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;


public class MainActivity extends Activity {

	private GLSurfaceView mGLView;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		// setContentView(R.layout.activity_main);
		mGLView = new GLParkingView(this);
        setContentView(mGLView);
        mGLView.requestFocus();
        mGLView.setFocusableInTouchMode(true);
        
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

    @Override protected void onResume() {
        super.onResume();
        mGLView.onResume();
    }

    @Override protected void onPause() {
        super.onPause();
        mGLView.onPause();
    }
}

