package com.reactlibrary;

import androidx.annotation.NonNull;

import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;

public class EngineViewManager extends SimpleViewManager<EngineView> {

    @NonNull
    @Override
    public String getName() {
        return "EngineView";
    }

    @NonNull
    @Override
    protected EngineView createViewInstance(@NonNull ThemedReactContext reactContext) {
        return new EngineView(reactContext);
    }
}