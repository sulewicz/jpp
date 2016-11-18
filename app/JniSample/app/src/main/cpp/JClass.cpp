#include "JClass.h"

JClass::JClass(JNIEnv *env, const char *className) : m_env(env), m_className(className) {
    jclass _class = m_env->FindClass(m_className);
    if (_class != nullptr) {
        m_class = (jclass) m_env->NewGlobalRef(_class);
    }
}

JClass::JClass(const JClass &other) : m_env(other.m_env), m_className(other.m_className) {
    if (other.is_valid()) {
        m_class = (jclass) m_env->NewGlobalRef(other.m_class);
    }
}

JClass::~JClass() {
    if (is_valid()) {
        m_env->DeleteGlobalRef(m_class);
        m_class = nullptr;
    }
}

bool JClass::is_valid() const {
    return m_class != nullptr;
}
