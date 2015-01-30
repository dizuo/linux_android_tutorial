package com.dizuo.parking;

// 包名com.dizuo.jni_demo.有下划线导致问题：
// 		Java_com_dizuo_jni_demo_JNI_nativeInit函数始终找不到！。！

import java.io.FileOutputStream;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.graphics.Bitmap.Config;
import android.graphics.Paint.Align;
import android.graphics.Paint.Style;
import android.util.Log;

public class JNI {
    static {
      System.loadLibrary("native");
    }
    
    public static String sTag = "dizuo";
    
    public String mDataPath = "";
    
    private Paint mTextPaint;
    
    public native long nativeInit();  
    public native void nativeDestroy(long context);    
    public native long nativeTestCallback(long context);    
    public native int nativePrepareGLData(String dir, long context);
    
    public native void nativeGLInit();
    public native void nativeGLDestroy();
    public native void nativeGLReshape(int width, int height);
    public native void nativeGLRender();
    public native void nativeGLAdjustView(float delta_angx, float delta_angy, float delta_camz);
    public native void nativeGLTrackball(int type, int ex, int ey);
    
    private void initTextPaint(int fontSize) {
        if (mTextPaint == null) {
            mTextPaint = new Paint();
            mTextPaint.setTypeface(Typeface.DEFAULT);
            mTextPaint.setAntiAlias(true);
            mTextPaint.setStyle(Style.FILL);
            mTextPaint.setTextAlign(Align.CENTER);
            mTextPaint.setLinearText(true);
        }
        mTextPaint.setTextSize(fontSize);
    }
    
    private Bitmap drawText(int fontSize, String text) {      
    	
        // 初始化画笔
        initTextPaint(fontSize);
        
        int width = (int)mTextPaint.measureText(text);
        int height = fontSize;
        
        Bitmap bm = null;
        
        boolean isTest = true;
        if (isTest) {
        	bm = Bitmap.createBitmap(width, height, Config.ARGB_8888);
        } else {
        	bm = Bitmap.createBitmap(width, height, Config.ALPHA_8);
        }
        
        bm.eraseColor(0x00000000);
        Canvas canvas = new Canvas(bm);

        float x = width / 2f;
        float y = height / 2f - (mTextPaint.descent() + mTextPaint.ascent()) / 2;

        canvas.drawText(text, x, y, mTextPaint);
        
        if (!isTest) {
        	return bm;
        }
        
        FileOutputStream out = null;
        String filename = mDataPath + "test.png";
        try {
        	out = new FileOutputStream(filename);
        	bm.compress(Bitmap.CompressFormat.PNG, 100, out);
        	
        } catch(Exception e) {
        	e.printStackTrace();
        } finally {
        	try {
        		if (out != null) {
        			out.close();
        		}
        	} catch(Exception e) {
        		e.printStackTrace();
        	}
        }   

        return bm;
    }
    
    public Object callback(int what, int arg1, String arg2) {
        Object param = null;
        
        switch(what)
        {
        case 0:
        	// param = new String("dizuo" + arg1);
        	param = drawText(arg1, arg2);
        	break;
        case 1:
        	param = new String("ryf" + arg1);
        	break;
        default:
        	param = new String(arg2);
        	break;
        }
        
        Log.i(JNI.sTag, "call java callback： " + what + ", "+ arg1 + ", " + arg2);
        
        return param;
    }
    
    // public loadBitmap
    // public writeBitmapToFile
    
    
}
