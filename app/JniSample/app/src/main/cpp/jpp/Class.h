#pragma once

#include <jni.h>
#include <string>
#include "internal/common.h"
#include "Object.h"
#include "Array.h"

namespace jpp {
    class Env;
    class Cache;

    class Class {
    public:
        Class(const Class &other);
        ~Class();

        Class &operator=(const Class &other);

        bool is_valid() const;
        const char *get_class_name() const;
        std::string get_signature_name() const;
        Env *get_env() const;
        jclass get_jclass() const;

        Class get_super_class();
        bool is_assignable_from(Class &from_class);

        bool is_object_class() const;
        bool is_array_class() const;

        template<class ... Types>
        Object create(Types ... args) {
            auto signature = common::generate_signature((void *) 0, args...);
            return do_create(signature.c_str(), type::flatten(args)...);
        }

        template<class Type>
        Array<Type> create_array(size_t size) {
            if (is_array_class()) {
                jarray array = do_create_array(size);
                return Array<Type>(*this, array);
            } else {
                return Array<Type>(*this, nullptr);
            }
        }

        template<class ... Types>
        Object call_object(const char *method_name, Class &return_type, Types ... args) {
            auto signature = common::generate_signature(return_type, args...);
            return run_object(return_type, method_name, signature.c_str(),
                              type::flatten(args)...);
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

    private:
        Class(Env *env);
        Class(Env *env, jclass _class, const char *class_name);

        Object do_create(const char *signature, ...);
        Object run_object(Class &return_type, const char *method_name, const char *signature, ...);
        void run_void(const char *method_name, const char *signature, ...);

        template<class Ret>
        inline Ret run(Ret type, const char *method_name, const char *signature, ...) {
            va_list vl;
            va_start(vl, signature);
            auto ret = run_v(type, method_name, signature, vl);
            va_end(vl);
            return ret;
        }

        jarray do_create_array(size_t size);
        Object do_create_v(const char *signature, va_list vl);
        Object run_v(Class &return_type, const char *method_name, const char *signature,
                     va_list vl);
        void run_v(const char *method_name, const char *signature, va_list vl);
        template<class Ret>
        Ret run_v(Ret, const char *method_name, const char *signature, va_list vl);

        Env *m_env;
        jclass m_jclass = nullptr;
        const char *m_class_name;

        friend class Cache;
        friend class Env;
    };
}
