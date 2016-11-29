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

        Class &get_class();
        Env *get_env() const;
        jclass get_jclass() const;
        jobject get_jobject() const;

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

    protected:
        Object(Class &_class);
        Object(Class &_class, jobject object);

    private:
        Object do_call(const char *method_name, const char *signature,
                              ...);
        void do_call(void *type, const char *method_name, const char *signature, ...);
        template<class Ret>
        Ret do_call(Ret type, const char *method_name, const char *signature, ...);

        Class *m_class = nullptr;
        jobject m_jobject = nullptr;
        friend class Env;
    };
}
