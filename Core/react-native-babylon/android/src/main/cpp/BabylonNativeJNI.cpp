#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_reactlibrary_Wrapper_initEngine(JNIEnv* env, jobject obj, jobject assetMgr, jobject appContext);
}

JNIEXPORT void JNICALL Java_com_reactlibrary_Wrapper_initEngine(JNIEnv* env, jobject obj, jobject assetMgr, jobject appContext)
{
}