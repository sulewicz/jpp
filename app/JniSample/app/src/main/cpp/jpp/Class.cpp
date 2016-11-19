#include "Class.h"

using namespace jpp;

Class::Class(JNIEnv *env, const char *className) : m_env(env), m_class_name(className) {
    jclass _class = m_env->FindClass(m_class_name);
    if (_class != nullptr) {
        m_jclass = (jclass) m_env->NewGlobalRef(_class);
    }
}

Class::Class(const Class &other) : m_env(other.m_env), m_class_name(other.m_class_name) {
    if (other.is_valid()) {
        m_jclass = (jclass) m_env->NewGlobalRef(other.m_jclass);
    }
}

Class::~Class() {
    if (is_valid()) {
        m_env->DeleteGlobalRef(m_jclass);
        m_jclass = nullptr;
    }
}

bool Class::is_valid() const {
    return m_jclass != nullptr;
}

const char *Class::get_class_name() const {
    return m_class_name;
}

JNIEnv *Class::get_env() const {
    return m_env;
}

jclass Class::get_jclass() const {
    return m_jclass;
}

Object Class::do_construct(const char *signature, ...) {
    jobject result = nullptr;
    jmethodID method_id = m_env->GetMethodID(m_jclass,  "<init>", signature);
    if (method_id) {
        va_list vl;
        va_start(vl, signature);
        result = m_env->NewObjectV(m_jclass, method_id, vl);
        va_end(vl);
    }
    return Object(this, result);
}
