package com.reactlibrary;

import android.content.Context;
import android.content.res.AssetManager;

public class Wrapper {
    // JNI interface
    static {
        System.loadLibrary("BabylonNativeJNI");
    }

    public static native void initEngine(AssetManager assetManager, Context appContext);
}
