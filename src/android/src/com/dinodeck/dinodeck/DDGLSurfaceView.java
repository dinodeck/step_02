package com.dinodeck.dinodeck;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

class DDGLSurfaceView extends GLSurfaceView
{
    DDRenderer mRenderer;
    DDActivity mActivity;

    public DDGLSurfaceView(Context context, DDActivity thisActivity)
    {
        super(context);
        mActivity = thisActivity;
        mRenderer = new DDRenderer(context, thisActivity);
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
