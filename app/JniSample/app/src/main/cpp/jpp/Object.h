#pragma once

#include <jni.h>
#include "internal/common.h"

namespace jpp {
    class Env;
    class Class;

    class Object {
    public:
        Object(const Object &other);
        Object(Object &&other);
        ~Object();

        bool is_valid() const;

        Class &get_class();
        Env *get_env() const;
        jclass get_jclass() const;
        jobject get_jobject() const;

        template<class ... Types>
        Object call_object(const char *method_name, Class &return_type, Types ... args) {
            auto signature = common::generate_signature(return_type, args...);
            return run_object(return_type, method_name, signature.c_str(), type::flatten(args)...);
        }

        template<class ... Types>
        void call_void(const char *method_name, Types ... args) {
            auto signature = common::generate_signature((void *) 0, args...);
            run_void(method_name, signature.c_str(), type::flatten(args)...);
        }

        template<class Ret, class ... Types>
        Ret call(const char *method_name, Types ... args) {
            auto signature = common::generate_signature(Ret(), args...);
            return run(Ret(), method_name, signature.c_str(), type::flatten(args)...);
        }

    protected:
        Object(Class &_class);
        Object(Class &_class, jobject object);

    private:
        inline Object run_object(Class &return_type, const char *method_name, const char *signature,
                                 ...) {
            va_list vl;
            va_start(vl, signature);
            auto ret = run_v(return_type, method_name, signature, vl);
            va_end(vl);
            return ret;
        }

        inline void run_void(const char *method_name, const char *signature, ...) {
            va_list vl;
            va_start(vl, signature);
            run_v(method_name, signature, vl);
            va_end(vl);
        }

        template<class Ret>
        inline Ret run(Ret type, const char *method_name, const char *signature, ...) {
            va_list vl;
            va_start(vl, signature);
            auto ret = run_v(type, method_name, signature, vl);
            va_end(vl);
            return ret;
        }

        Object run_v(Class &return_type, const char *method_name, const char *signature,
                     va_list vl);
        void run_v(const char *method_name, const char *signature, va_list vl);
        template<class Ret>
        Ret run_v(Ret, const char *method_name, const char *signature, va_list vl);


        Class *m_class = nullptr;
        jobject m_jobject = nullptr;
        friend class Env;
    };
}
