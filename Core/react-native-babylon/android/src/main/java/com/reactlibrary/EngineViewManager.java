package com.reactlibrary;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.facebook.react.common.MapBuilder;
import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;

import java.util.Map;

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

    @Nullable
    @Override
    public Map<String, Object> getExportedCustomDirectEventTypeConstants() {
        return MapBuilder.of(
                "viewReady",
                MapBuilder.of("registrationName", "viewReady")
        );
    }
}