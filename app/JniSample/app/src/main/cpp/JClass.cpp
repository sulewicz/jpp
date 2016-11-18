#include "JClass.h"

JClass::JClass(JNIEnv *env, const char *className) : m_env(env), m_class_name(className) {
    jclass _class = m_env->FindClass(m_class_name);
    if (_class != nullptr) {
        m_jclass = (jclass) m_env->NewGlobalRef(_class);
    }
}

JClass::JClass(const JClass &other) : m_env(other.m_env), m_class_name(other.m_class_name) {
    if (other.is_valid()) {
        m_jclass = (jclass) m_env->NewGlobalRef(other.m_jclass);
    }
}

JClass::~JClass() {
    if (is_valid()) {
        m_env->DeleteGlobalRef(m_jclass);
        m_jclass = nullptr;
    }
}

bool JClass::is_valid() const {
    return m_jclass != nullptr;
}

const char *JClass::get_class_name() const {
    return m_class_name;
}

JNIEnv *JClass::get_env() const {
    return m_env;
}

jclass JClass::get_jclass() const {
    return m_jclass;
}

JObject JClass::do_construct(const char *signature, ...) {
    jobject result = nullptr;
    jmethodID method_id = m_env->GetMethodID(m_jclass,  "<init>", signature);
    if (method_id) {
        va_list vl;
        va_start(vl, signature);
        result = m_env->NewObjectV(m_jclass, method_id, vl);
        va_end(vl);
    }
    return JObject(this, result);
}
