package com.reactlibrary;

import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.babylon.GetJsGlobalContextRef;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.uimanager.events.RCTEventEmitter;

public class EngineView extends SurfaceView implements SurfaceHolder.Callback2 {
    private final ReactContext reactContext;

    public EngineView(ReactContext reactContext) {
        super(reactContext);
        this.reactContext = reactContext;
        this.getHolder().addCallback(this);
    }

    @Override
    public void surfaceRedrawNeeded(SurfaceHolder surfaceHolder) {

    }

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        Surface surface = surfaceHolder.getSurface();
        GetJsGlobalContextRef getJsGlobalContextRef = new GetJsGlobalContextRef();
        long address = reactContext.getJavaScriptContextHolder().get();
        long jsContextPtr = getJsGlobalContextRef.GetJsGlobalContextRef(address);

        this.reactContext.runOnJSQueueThread(() -> {
            BabylonNativeInterop.initEngine(this.reactContext, jsContextPtr, surface);
            this.reactContext.runOnUiQueueThread(() -> {
                WritableMap event = Arguments.createMap();
                this.reactContext.getJSModule(RCTEventEmitter.class).receiveEvent(
                        this.getId(),
                        "viewReady",
                        event
                );
            });
        });
    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int i, int i1, int i2) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {

    }
}