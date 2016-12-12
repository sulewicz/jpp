#pragma once

#include <jni.h>

namespace jpp {
    class Env;

    /**
    * \brief TODO: Add documentation.
    *
    * TODO: Add documentation.
    */
    class JVM {
    public:
        JVM();
        JVM(JavaVM *jvm);
        ~JVM();

        bool is_valid();
        Env get_env(jint version = JNI_VERSION_1_6);
        Env attach_current_thread();
        bool detach_current_thread();
    private:
        JavaVM *m_jvm;
    };
}
