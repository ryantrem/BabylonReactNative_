#include <jni.h>
#include <android/log.h>

namespace Babylon
{
    namespace
    {
        void log(const char *str)
        {
            __android_log_print(ANDROID_LOG_VERBOSE, "BabylonNative", "%s", str);
        }
    }

    void Initialize()
    {
        log("INITIALIZED");
    }
}

extern "C"
{
    JNIEXPORT void JNICALL Java_com_reactlibrary_Wrapper_initEngine(JNIEnv* env, jobject obj, jobject appContext, jlong jscPtr, jobject surface);
}

JNIEXPORT void JNICALL Java_com_reactlibrary_Wrapper_initEngine(JNIEnv* env, jobject obj, jobject appContext, jlong jscPtr, jobject surface)
{
    Babylon::Initialize();
}