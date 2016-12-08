#pragma once

#include <jni.h>
#include "internal/utils.h"

namespace jpp {
    class Env;
    class Class;

    class Object {
    public:
        Object(const Object &other);
        Object(Object &&other);
        ~Object();

        bool operator==(const Object &other);
        bool operator!=(const Object &other);

        bool is_valid() const;

        Class &get_class() const;
        Env *get_env() const;
        jclass get_jclass() const;
        jobject get_jobject() const;

        bool is_instance_of(const Class &other);
        Object cast_to(const Class &other);
        Object cast_to(const char *class_name);

        template<class ... Types>
        Object call_object(const char *method_name, Class &return_type, Types ... args) {
            auto signature = internal::generate_signature(return_type, args...);
            return do_call(method_name, signature.c_str(),
                           internal::flatten(args)...);
        }

        template<class ... Types>
        void call_void(const char *method_name, Types ... args) {
            auto signature = internal::generate_signature((void *) 0, args...);
            do_call((void *) 0, method_name, signature.c_str(), internal::flatten(args)...);
        }

        template<class Ret, class ... Types>
        Ret call(const char *method_name, Types ... args) {
            auto signature = internal::generate_signature(Ret(), args...);
            return do_call(Ret(), method_name, signature.c_str(), internal::flatten(args)...);
        }

        Object get(const char *field_name, Class &field_type) {
            return do_get(field_name, internal::type_to_str(field_type).c_str());
        }

        template<class Ret>
        Ret get(const char *field_name) {
            return do_get(Ret(), field_name, internal::type_to_str(Ret()));
        }

        void set(const char *field_name, const Object& value) {
            return do_set(field_name, internal::type_to_str(value.get_class()).c_str(), value);
        }

        template<class Type>
        void set(const char *field_name, const Type& value) {
            return do_set(field_name, internal::type_to_str(value), value);
        }

    protected:
        Object();
        Object(const Class &_class);
        Object(const Class &_class, jobject object);

    private:
        Object do_call(const char *method_name, const char *signature,
                       ...);
        void do_call(void *type, const char *method_name, const char *signature, ...);
        template<class Ret>
        Ret do_call(Ret type, const char *method_name, const char *signature, ...);

        Object do_get(const char *field_name, const char *signature);
        template<class Ret>
        Ret do_get(Ret type, const char *field_name, const char *signature);

        void do_set(const char *field_name, const char *signature, const Object& value);
        template<class Type>
        void do_set(const char *field_name, const char *signature, const Type& value);

        Class *m_class = nullptr;
        jobject m_jobject = nullptr;
        friend class Env;
    };
}
