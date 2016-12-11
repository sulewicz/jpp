#include <jni.h>
#include "jpp/jpp.h"

#include <thread>

static jpp::JVM JVM_INSTANCE;
static jpp::GlobalRef JVM_TESTER_REFERENCE;

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_JvmTester_cacheJvm(JNIEnv *env, jobject obj) {
    if (!JVM_INSTANCE.is_valid()) {
        jpp::Env jpp_env(env);
        JVM_INSTANCE = jpp_env.get_jvm();
    }
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_JvmTester_createObjectFromCachedJvm(JNIEnv *env,
                                                                          jobject obj) {
    if (JVM_INSTANCE.is_valid()) {
        jpp::Env jpp_env = JVM_INSTANCE.get_env();
        if (jpp_env.is_valid()) {
            auto object_class = jpp_env.find_class("java/lang/Object");
            auto ret = object_class.create();
            return (jobject) ret;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_JvmTester_asyncOperation(JNIEnv *env, jobject obj) {
    jpp::Env jpp_env(env);
    auto jvm_tester_object = jpp_env.wrap(obj);
    JVM_TESTER_REFERENCE.wrap(jvm_tester_object);
    std::thread thread([]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (JVM_INSTANCE.is_valid() && JVM_TESTER_REFERENCE.is_valid()) {
            jpp::Env jpp_env = JVM_INSTANCE.attach_current_thread();
            if (jpp_env.is_valid()) {
                // Introducing new scope to avoid object destruction after detaching from thread.
                {
                    jpp::Object jvm_tester_object = JVM_TESTER_REFERENCE.unwrap(jpp_env);
                    JVM_TESTER_REFERENCE.release(jpp_env);

                    auto object_class = jpp_env.find_class("java/lang/Object");
                    auto result = object_class.create();
                    {
                        jpp::Monitor monitor = jpp_env.synchronize(jvm_tester_object);
                        jvm_tester_object.set("mResult", result);
                        jvm_tester_object.call_void("notifyAll");
                    }
                }
                // All objects destroyed, now we can safely detach.
                JVM_INSTANCE.detach_current_thread();
            }
        }
    });
    thread.detach();
}
