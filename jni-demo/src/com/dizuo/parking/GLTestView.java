package com.dizuo.parking;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.IntBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;

public class GLTestView extends GLSurfaceView {
	
	TestRenderer mRenderer;
	
    private final float TOUCH_SCALE_FACTOR = 180.0f / 320;
    private final float TRACKBALL_SCALE_FACTOR = 36.0f;
    private float mPreviousX;
    private float mPreviousY;
    
	
	public GLTestView(Context context)  {
		super(context);
		
		mRenderer = new TestRenderer();
		setRenderer(mRenderer);
//		setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
		setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
	}
	
    @Override public boolean onTrackballEvent(MotionEvent e) {
        mRenderer.mAngleX += e.getX() * TRACKBALL_SCALE_FACTOR;
        mRenderer.mAngleY += e.getY() * TRACKBALL_SCALE_FACTOR;
        requestRender();
        return true;
    }

    @Override public boolean onTouchEvent(MotionEvent e) {
        float x = e.getX();
        float y = e.getY();
        switch (e.getAction()) {
        case MotionEvent.ACTION_MOVE:
            float dx = x - mPreviousX;
            float dy = y - mPreviousY;
            mRenderer.mAngleX += dx * TOUCH_SCALE_FACTOR;
            mRenderer.mAngleY += dy * TOUCH_SCALE_FACTOR;
            requestRender();
        }
        mPreviousX = x;
        mPreviousY = y;
        return true;
    }
	
	private class TestRenderer implements GLSurfaceView.Renderer {
		
		Cube mCube = new Cube();
        public float mAngleX = 0;
        public float mAngleY = 0;
        
		public TestRenderer() {
		}
		
		public void onDrawFrame(GL10 gl) {

            gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            gl.glLoadIdentity();
            gl.glTranslatef(0, 0, -3.0f);
            gl.glRotatef(mAngleX, 0, 1, 0);
            gl.glRotatef(mAngleY, 1, 0, 0);

            gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
            gl.glEnableClientState(GL10.GL_COLOR_ARRAY);
            
            Log.i("dizuo", "render");
            
            mCube.draw(gl);
		}
		
		public void onSurfaceChanged(GL10 gl, int width, int height) {
			gl.glViewport(0, 0, width, height);
			
			float ratio = (float) width / height;
            gl.glMatrixMode(GL10.GL_PROJECTION);
            gl.glLoadIdentity();
            gl.glFrustumf(-ratio, ratio, -1, 1, 1, 10);
		}
		
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        	gl.glDisable(GL10.GL_DITHER);
            
            gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT,
                     GL10.GL_FASTEST);

            gl.glClearColor(1,1,1,1);
            gl.glEnable(GL10.GL_CULL_FACE);
            gl.glShadeModel(GL10.GL_SMOOTH);
            gl.glEnable(GL10.GL_DEPTH_TEST);
        }
	}
	
	class Cube
	{
	    public Cube()
	    {
	        int one = 0x10000;
	        int vertices[] = {
	                -one, -one, -one,
	                one, -one, -one,
	                one,  one, -one,
	                -one,  one, -one,
	                -one, -one,  one,
	                one, -one,  one,
	                one,  one,  one,
	                -one,  one,  one,
	        };

	        int colors[] = {
	                0,    0,    0,  one,
	                one,    0,    0,  one,
	                one,  one,    0,  one,
	                0,  one,    0,  one,
	                0,    0,  one,  one,
	                one,    0,  one,  one,
	                one,  one,  one,  one,
	                0,  one,  one,  one,
	        };

	        byte indices[] = {
	                0, 4, 5,    0, 5, 1,
	                1, 5, 6,    1, 6, 2,
	                2, 6, 7,    2, 7, 3,
	                3, 7, 4,    3, 4, 0,
	                4, 7, 6,    4, 6, 5,
	                3, 0, 1,    3, 1, 2
	        };

	        // Buffers to be passed to gl*Pointer() functions
	        // must be direct, i.e., they must be placed on the
	        // native heap where the garbage collector cannot
	        // move them.
	        //
	        // Buffers with multi-byte datatypes (e.g., short, int, float)
	        // must have their byte order set to native order

	        ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length*4);
	        vbb.order(ByteOrder.nativeOrder());
	        mVertexBuffer = vbb.asIntBuffer();
	        mVertexBuffer.put(vertices);
	        mVertexBuffer.position(0);

	        ByteBuffer cbb = ByteBuffer.allocateDirect(colors.length*4);
	        cbb.order(ByteOrder.nativeOrder());
	        mColorBuffer = cbb.asIntBuffer();
	        mColorBuffer.put(colors);
	        mColorBuffer.position(0);

	        mIndexBuffer = ByteBuffer.allocateDirect(indices.length);
	        mIndexBuffer.put(indices);
	        mIndexBuffer.position(0);
	    }

	    public void draw(GL10 gl)
	    {
	        gl.glFrontFace(GL10.GL_CW);
	        gl.glVertexPointer(3, GL10.GL_FIXED, 0, mVertexBuffer);
	        gl.glColorPointer(4, GL10.GL_FIXED, 0, mColorBuffer);
	        gl.glDrawElements(GL10.GL_TRIANGLES, 36, GL10.GL_UNSIGNED_BYTE, mIndexBuffer);
	    }

	    private IntBuffer   mVertexBuffer;
	    private IntBuffer   mColorBuffer;
	    private ByteBuffer  mIndexBuffer;
	}

	
}
