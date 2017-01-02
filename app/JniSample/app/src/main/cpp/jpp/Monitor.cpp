/*
 * Copyright (C) 2017 Szymon Ulewicz.
 * Distributed under MIT license, see LICENSE file for details.
 */

#include "Monitor.h"

using namespace jpp;

Monitor::Monitor(JNIEnv *jenv, jobject _jobject) {
    m_jenv = jenv;
    m_jobject = _jobject;
    if (m_jenv != nullptr && m_jobject != nullptr) {
        m_jenv->MonitorEnter(m_jobject);
    }
}

Monitor::~Monitor() {
    if (m_jenv != nullptr && m_jobject != nullptr) {
        m_jenv->MonitorExit(m_jobject);
    }
}
