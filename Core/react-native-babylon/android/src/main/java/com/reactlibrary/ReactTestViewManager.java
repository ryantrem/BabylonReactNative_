package com.reactlibrary;

import androidx.annotation.NonNull;

import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;

public class ReactTestViewManager extends SimpleViewManager<ReactTestView> {

    @NonNull
    @Override
    public String getName() {
        return "ReactTestView";
    }

    @NonNull
    @Override
    protected ReactTestView createViewInstance(@NonNull ThemedReactContext reactContext) {
        return new ReactTestView(reactContext);
    }
}