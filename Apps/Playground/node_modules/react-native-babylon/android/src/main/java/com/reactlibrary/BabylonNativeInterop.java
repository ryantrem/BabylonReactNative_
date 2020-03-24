package com.reactlibrary;

import android.content.Context;
import android.view.Surface;

public final class BabylonNativeInterop {
    // JNI interface
    static {
        System.loadLibrary("BabylonNative");
    }

    public static native void initEngine(Context appContext, long jscPtr, Surface surface);
}
