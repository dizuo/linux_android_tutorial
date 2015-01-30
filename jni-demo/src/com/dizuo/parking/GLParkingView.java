package com.dizuo.parking;

import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGLConfig;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.FloatMath;
import android.util.Log;
import android.view.MotionEvent;

public class GLParkingView extends GLSurfaceView {
	
	private ParkingRenderer mRender;
	
	public JNI mJni;
	
	public GLParkingView(Context context, JNI jni) {
		super(context);
		
		mJni = jni;	
		
		mRender = new ParkingRenderer();
		setRenderer(mRender);
		setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
		// setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
		
	}
	
	private float spacing(MotionEvent event) {
		float x = event.getX(0) - event.getX(1);
		float y = event.getY(0) - event.getY(1);
		return FloatMath.sqrt(x*x + y*y);
	}
	
	@Override
	public void onPause() {
		super.onPause();
		mJni.nativeGLDestroy();
	}
	
	@Override public boolean onTouchEvent(MotionEvent e) {
		float x = e.getX();
        float y = e.getY();
        switch (e.getAction() & MotionEvent.ACTION_MASK) {
        case MotionEvent.ACTION_DOWN:
        	mJni.nativeGLTrackball(0, (int)x, (int)y);
        	mActMode = 1;
        	break;
        case MotionEvent.ACTION_UP:
        	mActMode = 0;
        	break;
        case MotionEvent.ACTION_POINTER_UP:
        	mActMode -= 1;
        	break;
        case MotionEvent.ACTION_MOVE:
        	float delta_anglex = 0;
        	float delta_angley = 0;
        	float delta_cameraz = 0;
        	
        	if (mActMode == 1) {
        		mJni.nativeGLTrackball(1, (int)x, (int)y);
	            requestRender();
        	}
        	else if (mActMode >= 2) {
        		float newDist = spacing(e);
        		if (newDist > mOldDist) {
        			delta_cameraz = 0.1f;	// zoom in
        		}
        		else if (newDist < mOldDist) {
        			delta_cameraz = -0.1f;	// zoom out
        		}
         		mJni.nativeGLAdjustView(delta_anglex, delta_angley, delta_cameraz);
                requestRender();
        	}        	
        	
            break;
        case MotionEvent.ACTION_POINTER_DOWN:
        	mOldDist = spacing(e);
        	mActMode += 1;
        	break;       	
        	
        }        
        return true;
	}
	
	class ParkingRenderer implements GLSurfaceView.Renderer {
		
		public ParkingRenderer() {
			
		}
		
		public void onSurfaceCreated(GL10 gl, EGLConfig config) {
			mJni.nativeGLInit();
		}
		
		public void onSurfaceChanged(GL10 gl, int width, int height) {
			mJni.nativeGLReshape(width, height);
		}
		
		public void onDrawFrame(GL10 gl) {
			Log.i(JNI.sTag, "render");
			
			mJni.nativeGLRender();
		}

	}
	
	private float mActMode = 0;
	private float mOldDist = 0;
	
	
}