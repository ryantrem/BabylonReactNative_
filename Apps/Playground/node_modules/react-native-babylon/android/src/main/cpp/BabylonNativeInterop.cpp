#include <jni.h>

#include <Babylon/JsRuntime.h>
#include <Babylon/NativeWindow.h>
#include <Babylon/NativeEngine.h>

#include <JavaScriptCore/JavaScript.h>

#include <android/log.h>
#include <android/looper.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <vector>

#include <unistd.h>

namespace Babylon
{
    namespace
    {
        void log(const char *str)
        {
            __android_log_print(ANDROID_LOG_VERBOSE, "BabylonNative", "%s", str);
        }

        class DispatchPayload
        {
        public:
            DispatchPayload(Napi::Env env, std::function<void(Napi::Env)> func)
                    : m_env{env}
                    , m_func{func}
            {
            }

            DispatchPayload(const DispatchPayload&) = delete;
            DispatchPayload(DispatchPayload&&) = delete;
            DispatchPayload& operator=(const DispatchPayload&) = delete;

            void Call()
            {
                m_func(m_env);
            }

        //private:
            Napi::Env m_env;
            std::function<void(Napi::Env)> m_func{};
        };

        void CheckHelloWorld(Napi::Env env)
        {
            if (env.Global().Get("helloWorld").IsUndefined())
            {
                log("helloWorld was undefined...");
            }
            else
            {
                log("helloWorld was defined, for some reason, as...");
                auto content = env.Global().Get("helloWorld").As<Napi::String>();
                log(content.Utf8Value().c_str());
                log("...so, yeah");
            }
        }

        void CheckThread(const char* prefix = "Current thread ID: ")
        {
            auto id = std::this_thread::get_id();
            std::stringstream ss{};
            ss << prefix << id;
            log(ss.str().c_str());
        }
    }

    void Initialize(JSGlobalContextRef jsContext, ANativeWindow* windowPtr)
    {
        auto width = static_cast<size_t>(ANativeWindow_getWidth(windowPtr));
        auto height = static_cast<size_t>(ANativeWindow_getHeight(windowPtr));

        log("Let's try this.");
        JSValueRef exception;
        JSEvaluateScript(jsContext, JSStringCreateWithUTF8CString("console.log(\"Hello, world!\");"), nullptr, JSStringCreateWithUTF8CString(""), 1, &exception);
        log("Did we make it?");

        CheckThread("JavaScript thread is ");
        Napi::Env env = Napi::Attach(jsContext);

        CheckHelloWorld(env);
        auto value = Napi::Value::From(env, "42");
        env.Global().Set("helloWorld", value);
        CheckHelloWorld(env);

        auto* looper = ALooper_forThread();
        assert(looper != nullptr);
        ALooper_acquire(looper);

        JsRuntime::DispatchFunctionT dispatchFunction{[env, looper](std::function<void(Napi::Env)> func)
        {
            CheckThread("Dispatch function called on thread ");

            int fileDescriptors[2];
            pipe(fileDescriptors);
            const int FD_READ = fileDescriptors[0];
            const int FD_WRITE = fileDescriptors[1];

            ALooper_addFd(looper, FD_READ, ALOOPER_POLL_CALLBACK, ALOOPER_EVENT_INPUT, [](int fd, int, void* data)
            {
                CheckThread("Looper callback called on thread ");

                log("Checkpoint 2");
                DispatchPayload* payloadPtr{};

                // TODO: Check that this actually reads the correct number of bytes.
                ssize_t bytesRead = read(fd, &payloadPtr, sizeof(decltype(payloadPtr)));
                if (bytesRead != sizeof(decltype(payloadPtr)))
                {
                    std::stringstream ss{};
                    ss << "Bytes read was " << bytesRead << " instead of " << sizeof(decltype(payloadPtr));
                    throw;
                }
                else
                {
                    log("Read the correct number of bytes!");
                }

                log("About to try dereferencing the payload pointer...");
                CheckHelloWorld(payloadPtr->m_env);
                log("Spot 1");
                payloadPtr->Call();
                log("Spot 2");
                delete payloadPtr;
                log("Spot 3");

                auto* looper = reinterpret_cast<ALooper*>(data);
                ALooper_removeFd(looper, fd);
                close(fd);

                return 0;
            }, looper);

            auto* payloadPtr = new DispatchPayload(env, std::move(func));
            if (write(FD_WRITE, &payloadPtr, sizeof(decltype(payloadPtr))) != sizeof(decltype(payloadPtr)))
            {
                throw; // Fail! Tell me what's the matter!!
            }
            close(FD_WRITE);
        } };

        JsRuntime::Initialize(env, dispatchFunction);

        // TODO: Add clean-up code. GSL final?

        dispatchFunction([windowPtr, width, height](Napi::Env env)
        {
            log("Checkpoint 4");
            auto& runtime = JsRuntime::GetFromJavaScript(env);

            std::thread{ [&runtime]() mutable
            {
                runtime.Dispatch([](Napi::Env env)
                {
                    log("Innermost dispatch!");
                    CheckHelloWorld(env);
                });
            } }.detach();

            runtime.Dispatch([windowPtr, width, height](Napi::Env env)
            {
                NativeWindow::Initialize(env, windowPtr, width, height);
            });

            InitializeNativeEngine(runtime, windowPtr, width, height);
        });

        log("Checkpoint 5");
    }
}

extern "C" JNIEXPORT void JNICALL Java_com_reactlibrary_BabylonNativeInterop_initEngine(JNIEnv* env, jclass obj, jobject appContext, jlong jscPtr, jobject surface)
{
    auto jsContext = reinterpret_cast<JSGlobalContextRef>(jscPtr);
    ANativeWindow* windowPtr = ANativeWindow_fromSurface(env, surface);
    Babylon::Initialize(jsContext, windowPtr);
}