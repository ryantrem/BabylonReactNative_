#include <jni.h>

#include <android/log.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include <JavaScriptCore/JavaScript.h>

namespace Babylon
{
    namespace
    {
        void log(const char *str)
        {
            __android_log_print(ANDROID_LOG_VERBOSE, "BabylonNative", "%s", str);
        }
    }

    void Initialize(JSGlobalContextRef jsContext, ANativeWindow* windowPtr)
    {
        log("INITIALIZED");
    }
}

extern "C" JNIEXPORT void JNICALL Java_com_reactlibrary_BabylonNativeInterop_initEngine(JNIEnv* env, jclass obj, jobject appContext, jlong jscPtr, jobject surface)
{
    auto jsContext = reinterpret_cast<JSGlobalContextRef>(jscPtr);
    ANativeWindow* windowPtr = ANativeWindow_fromSurface(env, surface);
    Babylon::Initialize(jsContext, windowPtr);
}