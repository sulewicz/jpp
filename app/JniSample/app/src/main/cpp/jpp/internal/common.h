#pragma once

#include <functional>

namespace jpp {
    template<class Ret>
    static inline Ret invoke_method(JNIEnv *env, jclass _jclass, const char *method_name,
                                    const char *signature,
                                    std::function<Ret(jmethodID)> jni_call) {
        Ret ret;
        jmethodID method_id = env->GetMethodID(_jclass, method_name, signature);
        if (method_id) {
            ret = jni_call(method_id);
        }
        return ret;
    };

    template<>
    static inline void invoke_method(JNIEnv *env, jclass _jclass, const char *method_name,
                                     const char *signature,
                                     std::function<void(jmethodID)> jni_call) {
        jmethodID method_id = env->GetMethodID(_jclass, method_name, signature);
        if (method_id) {
            jni_call(method_id);
        }
    };

    template<class Ret>
    static inline Ret invoke_static_method(JNIEnv *env, jclass _jclass, const char *method_name,
                                           const char *signature,
                                           std::function<Ret(jmethodID)> jni_call) {
        Ret ret;
        jmethodID method_id = env->GetStaticMethodID(_jclass, method_name, signature);
        if (method_id) {
            ret = jni_call(method_id);
        }
        return ret;
    };

    template<>
    static inline void invoke_static_method(JNIEnv *env, jclass _jclass, const char *method_name,
                                            const char *signature,
                                            std::function<void(jmethodID)> jni_call) {
        jmethodID method_id = env->GetStaticMethodID(_jclass, method_name, signature);
        if (method_id) {
            jni_call(method_id);
        }
    };

}
