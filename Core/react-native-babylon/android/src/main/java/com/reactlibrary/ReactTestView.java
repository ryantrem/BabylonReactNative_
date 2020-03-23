package com.reactlibrary;

import androidx.appcompat.widget.AppCompatTextView;

import com.babylon.GetJsGlobalContextRef;
import com.facebook.react.bridge.ReactContext;

public class ReactTestView extends AppCompatTextView {
    private final ReactContext reactContext;

    public ReactTestView(ReactContext reactContext) {
        super(reactContext);
        this.reactContext = reactContext;
        this.setText("this is a native test component");

        GetJsGlobalContextRef getJsGlobalContextRef = new GetJsGlobalContextRef();
        long address = reactContext.getJavaScriptContextHolder().get();
        long ptr = getJsGlobalContextRef.GetJsGlobalContextRef(address);
        System.out.println(ptr);

        BabylonNativeInterop.initEngine(reactContext, ptr, null);
    }
}
