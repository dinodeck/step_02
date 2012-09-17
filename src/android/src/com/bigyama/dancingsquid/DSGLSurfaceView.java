package com.bigyama.dancingsquid;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class DSGLSurfaceView extends GLSurfaceView
{
    DSRenderer mRenderer;
    DSActivity mActivity;

    public DSGLSurfaceView(Context context, DSActivity thisActivity)
    {
        super(context);
        mActivity = thisActivity;
        mRenderer = new DSRenderer(context, thisActivity);
        setRenderer(mRenderer);
    }

    public void updateUI()
    {

    }

    public void gainedFocus()
    {
        super.onResume();
        if (mRenderer != null)
        {
            mRenderer.gainedFocus();
        }
    }

    public void onPause()
    {
        super.onPause();
    }
}
