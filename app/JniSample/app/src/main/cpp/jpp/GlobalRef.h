#pragma once

#include <jni.h>
#include "Object.h"

namespace jpp {
    class Object;
    class Class;
    class Env;

    class GlobalRef {
    public:
        GlobalRef();
        GlobalRef(const GlobalRef& object);
        ~GlobalRef();

        bool is_valid() const;

        void wrap(const Object& object);
        Object unwrap(Env& env);
        void release(Env& env);
        void set_env(Env& env);

    private:
        JNIEnv *m_jenv = nullptr;
        jobject m_jobject = nullptr;
    };
}
