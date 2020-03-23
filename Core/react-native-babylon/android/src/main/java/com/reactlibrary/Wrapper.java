package com.reactlibrary;

import android.content.Context;
import android.view.Surface;

public class Wrapper {
    // JNI interface
    static {
        System.loadLibrary("BabylonNativeJNI");
    }

    public static native void initEngine(Context appContext, long jscPtr, Surface surface);
}
