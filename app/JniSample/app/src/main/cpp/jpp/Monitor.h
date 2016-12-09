#pragma once

#include <jni.h>

namespace jpp {
    class Env;

    class Monitor {
    public:
        ~Monitor();

    private:
        Monitor(JNIEnv *jenv, jobject _jobject);

        JNIEnv *m_jenv;
        jobject m_jobject;
        friend class Env;
    };
}

