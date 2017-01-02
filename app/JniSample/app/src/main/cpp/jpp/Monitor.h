/*
 * Copyright (C) 2017 Szymon Ulewicz.
 * Distributed under MIT license, see LICENSE file for details.
 */

#pragma once

#include <jni.h>

namespace jpp {
    class Env;

    /**
    * \brief TODO: Add documentation.
    *
    * TODO: Add documentation.
    */
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

