package com.dizuo.parking;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

import com.dizuo.jni_demo.R;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Environment;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;


public class MainActivity extends Activity {
	
	private GLSurfaceView mGLView;
	
	private String mDataDir;
	
	public JNI mJni = new JNI();
	
	public long mNativeContext = 0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		// setContentView(R.layout.activity_main);
		
		// mGLView = new GLTestView(this);
		
		if (initResourceFiles() != 0) {
        	Log.i(JNI.sTag, "initResourceFiles FAILED.");
        }
		
		mNativeContext = mJni.nativeInit();		
		if (mNativeContext != 0) {
			mJni.nativeTestCallback(mNativeContext);
		}
		
		mJni.mDataPath = mDataDir;
		mGLView = new GLParkingView(this, mJni);
		
        setContentView(mGLView);
        mGLView.requestFocus();
        mGLView.setFocusableInTouchMode(true);
        
        // �������ݺ���Դ.
        Thread workThread = new Thread( new Runnable() {
        	@Override 
        	public void run() {
        		
        		while (true) {
        			
        			Log.i(JNI.sTag, "prepare to load data");
	        		int ret = mJni.nativePrepareGLData(mDataDir, mNativeContext);	        		
	        		Log.i(JNI.sTag, "ret = " + ret);
	        		
	        		if (ret == 0 || ret < 0) {
	        			mGLView.requestRender();	        			
	        			break;
	        		}
	        		
	        		mGLView.requestRender();
        		}
        		
        		Log.i("dizuo", "exit work thread");
        	}
        });
        
        workThread.start();
        
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		mJni.nativeDestroy(mNativeContext);
	}
	
	public int initResourceFiles() {
        String sdcard_dir = getSDCardPath();
        
        Log.i(JNI.sTag, sdcard_dir);
        mDataDir = sdcard_dir + "/parking_demo/";
        File file = new File(mDataDir);
        if (!file.exists()) {
        	file.mkdir();
        }
        if (file.isDirectory())
        {
        	// copy ...
        	try {
        		String srcName = "bp.asc";
        		InputStream in = getResources().getAssets().open(srcName);
        		
        		String toFile = mDataDir + srcName; 
        		OutputStream out = new FileOutputStream(toFile);
        		
        		byte bys[] = new byte[1024];
        		int c = 0;
        		while ((c = in.read(bys)) > 0) {
        			out.write(bys, 0, c);
        		}
        		out.close();
        		in.close();
        		return 0;
        	} catch (Exception e) {
        		return -1;
        	}        
        }
        
        return -1;
	}
	
	/**
     * ��ȡ����SD��·��
     * 
     * @return
     */
    public String getSDCardPath() {
        String cmd = "cat /proc/mounts";
        Runtime run = Runtime.getRuntime();// �����뵱ǰ Java Ӧ�ó�����ص�����ʱ����
        try {
            Process p = run.exec(cmd);// ������һ��������ִ������
            BufferedInputStream in = new BufferedInputStream(p.getInputStream());
            BufferedReader inBr = new BufferedReader(new InputStreamReader(in));

            String lineStr;
            while ((lineStr = inBr.readLine()) != null) {
                // �������ִ�к��ڿ���̨�������Ϣ
                // LOG.i("CommonUtil:getSDCardPath", lineStr);
                if (lineStr.contains("sdcard")
                        && lineStr.contains(".android_secure")) {
                    String[] strArray = lineStr.split(" ");
                    if (strArray != null && strArray.length >= 5) {
                        String result = strArray[1].replace("/.android_secure", "");
                        return result;
                    }
                }
                // ��������Ƿ�ִ��ʧ�ܡ�
                if (p.waitFor() != 0 && p.exitValue() == 1) {
                    // p.exitValue()==0��ʾ����������1������������
                    // LOG.e("CommonUtil:getSDCardPath", "����ִ��ʧ��!");
                }
            }
            inBr.close();
            in.close();
        } catch (Exception e) {
            // LOG.e("CommonUtil:getSDCardPath", e.toString());

            return Environment.getExternalStorageDirectory().getPath();
        }

        return Environment.getExternalStorageDirectory().getPath();
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

