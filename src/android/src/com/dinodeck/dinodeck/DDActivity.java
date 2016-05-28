package com.dinodeck.dinodeck;

import android.app.Activity;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.SystemClock;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.IOException;
import java.lang.System;


// Dinodeck activity
public class DDActivity extends Activity
{
    private static final String TAG = "ddactivity"; // used for logging
    private static DDGLSurfaceView mGLView = null;
    private static DDActivity mActivity = null;
    private Handler mUpdateTimeHandler = new Handler();
    private long mLastTimeCount;
    private float mDeltaTime;
    private Runnable mUpdateTimeTask = new Runnable()
    {
        public void run()
        {
            if (mGLView != null)
            {
                mGLView.updateUI();
            }
            mUpdateTimeHandler.postDelayed(this, 500);

            update();
        }
    };
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        Log.v(TAG, "ddactivity oncreate called");
        super.onCreate(savedInstanceState);
        mGLView = null;
        // Make activity statically available for functions
        // talking to C
        mActivity = this;
        mLastTimeCount = System.currentTimeMillis();

       // Bundle extras = this.getIntent().getExtras();

        // requiredScreenOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;
        // if(requiredScreenOrientation >= 0)
        // {
        //     setRequestedOrientation(requiredScreenOrientation);
        // }

        open_asset("settings.lua");

        this.getWindow().addFlags(
            WindowManager.LayoutParams.FLAG_FULLSCREEN |
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        nativeOnCreate();
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus)
    {
        super.onWindowFocusChanged(hasFocus);
        if(!hasFocus)
        {
            return;
        }
        // if (requiredScreenOrientation>=0)
        // {
        //     setRequestedOrientation(requiredScreenOrientation);
        // }

        if(mGLView == null)
        {
            createGLView();
        }

        if (mGLView != null)
        {
            mGLView.gainedFocus();
        }

        startTimer();
    }

    public float deltaTime()
    {
        return mDeltaTime;
    }

    public void update()
    {
        long currentTimeCount = System.currentTimeMillis();
        mDeltaTime = (currentTimeCount - mLastTimeCount) / 1000.0f;
        mLastTimeCount = currentTimeCount;
    }

    void createGLView()
    {
        Log.v(TAG, "creating GL view");
        mGLView = new DDGLSurfaceView(this, this);
        mGLView.setZOrderOnTop(false);
        setContentView(mGLView);
    }

    public void startTimer()
    {
        mUpdateTimeHandler.removeCallbacks(mUpdateTimeTask);
        mUpdateTimeHandler.postDelayed(mUpdateTimeTask, 500);
    }

    public void stopTimer()
    {
        mUpdateTimeHandler.removeCallbacks(mUpdateTimeTask);
    }

    public static boolean open_asset(String filename)
    {
        Log.v(TAG, "open_asset called" + filename);
        AssetManager am = mActivity.getAssets();
        InputStream is = null;
        try
        {
            is = am.open(filename);
            int size = is.available();
            Log.v(TAG, "open_asset success " + filename + " "
                  + size + "bytes");
            byte[] buffer = new byte[size];
            is.read(buffer);
            is.close();
            nativeIFStream( buffer, size );
            buffer = null;
            return true;
        }
        catch (IOException e)
        {
            Log.v(TAG, "open_asset fail " + filename);
            return false;
        }
        finally
        {
            try
            {
                if(is != null)
                {
                    is.close();
                }
            }
            catch (IOException e)
            {
            }
        }

    }

    public static native void nativeIFStream( byte[] buffer, int iSize );
    public native void nativeOnCreate();

    static
    {
        System.loadLibrary("dinodeck");
    }
}


