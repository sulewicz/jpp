#pragma once

#include "type.h"
#include <jni.h>
#include <string>
#include <sstream>
#include <functional>

// TODO: meld with jpp:Env
namespace jpp {
    namespace common {
        template<class Type, class ... Types>
        std::string generate_signature(Type return_type, Types ... args) {
            std::ostringstream stream;
            stream << "(";
            using List= int[];
            (void) List{0, ((void) (stream << jpp::type::type_to_str(args)), 0) ...};
            stream << ")" << jpp::type::type_to_str(return_type);
            return stream.str();
        }

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
        static inline void invoke_static_method(JNIEnv *env, jclass _jclass,
                                                const char *method_name,
                                                const char *signature,
                                                std::function<void(jmethodID)> jni_call) {
            jmethodID method_id = env->GetStaticMethodID(_jclass, method_name, signature);
            if (method_id) {
                jni_call(method_id);
            }
        };

        jarray new_array(JNIEnv *env, const jclass &_class, const std::string &class_name,
                         size_t size);
    }
}
