package com.dizuo.jnidemo;

// ����com.dizuo.jni_demo.���»��ߵ������⣺
// 		Java_com_dizuo_jni_demo_JNI_nativeInit����ʼ���Ҳ���������

import android.util.Log;

public class JNI {
    static {
      System.loadLibrary("native");
    }
    
    public native long nativeInit();
    
    public native long nativeTestCallback(long context);
    
    public Object callback(int what, int arg1, String arg2) {
        Object param = null;
        
        switch(what)
        {
        case 0:
        	param = new String("dizuo" + arg1);
        	break;
        case 1:
        	param = new String("ryf" + arg1);
        	break;
        default:
        	param = new String(arg2);
        	break;
        }
        
        Log.i("dizuo", "call java callback�� " + what + ", "+ arg1 + ", " + arg2);
        
        return param;
    }
    
    // public loadBitmap
    // public writeBitmapToFile
    
    
}
