#pragma once

#include <jni.h>
#include <string>
#include "internal/utils.h"
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
        bool operator==(const Class &other);
        bool operator!=(const Class &other);

        bool is_valid() const;
        const char *get_class_name() const;
        std::string get_signature_name() const;
        Env *get_env() const;
        jclass get_jclass() const;

        Class get_super_class();
        bool is_assignable_from(Class &from_class) const;

        bool is_object_class() const;
        bool is_array_class() const;

        template<class ... Types>
        Object create(Types ... args) {
            auto signature = internal::generate_signature((void *) 0, args...);
            return do_create(signature.c_str(), internal::flatten(args)...);
        }

        template<class ... Types>
        Object call_object(const char *method_name, Class &return_type, Types ... args) {
            auto signature = internal::generate_signature(return_type, args...);
            return do_call(method_name, signature.c_str(),
                           internal::flatten(args)...);
        }

        template<class ... Types>
        void call_void(const char *method_name, Types ... args) {
            auto signature = internal::generate_signature((void *) 0, args...);
            do_call((void*)0,method_name, signature.c_str(), internal::flatten(args)...);
        }

        template<class Ret, class ... Types>
        Ret call(const char *method_name, Types ... args) {
            auto signature = internal::generate_signature(Ret(), args...);
            return do_call(Ret(), method_name, signature.c_str(), internal::flatten(args)...);
        }

    private:
        Class(Env *env);
        Class(Env *env, jclass _class, const char *class_name);

        Object do_create(const char *signature, ...);

        Object do_call(const char *method_name, const char *signature,
                       ...);
        void do_call(void *type, const char *method_name, const char *signature, ...);
        template<class Ret>
        Ret do_call(Ret type, const char *method_name, const char *signature, ...);

        Env *m_env;
        jclass m_jclass = nullptr;
        const char *m_class_name;

        friend class Cache;
        friend class Env;
    };
}
