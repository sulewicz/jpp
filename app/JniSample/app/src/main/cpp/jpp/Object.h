#pragma once

#include <jni.h>
#include "internal/utils.h"

namespace jpp {
    class Class;

    class Object {
    public:
        Object(Class *_class, jobject object);
        Object(const Object &other);
        ~Object();

        bool is_valid() const;

        Class *get_class() const;
        JNIEnv *get_env() const;
        jclass get_jclass() const;
        jobject get_jobject() const;

        /*template<class ... Types>
        Object object(const char *method_name, Class &return_type, Types ... args) {
            auto signature = utils::generate_signature(return_type, args...);
            return do_object(method_name, return_type, signature.c_str(), utils::flatten(args)...);
        }

        template<class ... Types>
        jboolean boolean(const char *method_name, Types ... args) {
            auto signature = utils::generate_signature(jboolean(), args...);
            return do_boolean(method_name, signature.c_str(), utils::flatten(args)...);
        }*/
        /*template<class ... Types>
        Object call(const char *method_name, Class &return_type, Types ... args) {
            auto signature = utils::generate_signature(return_type, args...);
            return return_object(method_name, return_type, signature.c_str(), utils::flatten(args)...);
        }*/

        template<class ... Types>
        Object call_object(const char *method_name, Class &return_type, Types ... args) {
            auto signature = utils::generate_signature(return_type, args...);
            return run_object(method_name, return_type, signature.c_str(), utils::flatten(args)...);
        }

        template<class ... Types>
        void call_void(const char *method_name, Types ... args) {
            auto signature = utils::generate_signature((void*)0, args...);
            run_void(method_name, signature.c_str(), utils::flatten(args)...);
        }

        template<class Ret, class ... Types>
        Ret call(const char *method_name, Types ... args) {
            auto signature = utils::generate_signature(Ret(), args...);
            return run(Ret(), method_name, signature.c_str(), utils::flatten(args)...);
        }

    private:
        Object run_object(const char *method_name, Class &return_type, const char *signature, ...);
        void run_void(const char *method_name, const char *signature, ...);
        template<class Ret>
        Ret run(Ret, const char *method_name, const char *signature, ...);

        Class *const m_class;
        jobject m_jobject = nullptr;
    };
}
