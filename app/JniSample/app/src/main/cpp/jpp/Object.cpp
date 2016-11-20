#include "Object.h"
#include "Class.h"

using namespace jpp;

Object::Object(Class *_class, jobject object) : m_class(_class) {
    if (object != nullptr) {
        m_jobject = m_class->get_env()->NewGlobalRef(object);
    }
}

Object::Object(const Object &other) : m_class(other.m_class) {
    if (other.is_valid()) {
        m_jobject = m_class->get_env()->NewGlobalRef(other.m_jobject);
    }
}

Object::~Object() {
    if (is_valid()) {
        m_class->get_env()->DeleteGlobalRef(m_jobject);
        m_jobject = nullptr;
    }
}

bool Object::is_valid() const {
    return m_jobject != nullptr;
}

Class *Object::get_class() const {
    return m_class;
}

JNIEnv *Object::get_env() const {
    return m_class->get_env();
}

jclass Object::get_jclass() const {
    return m_class->get_jclass();
}

jobject Object::get_jobject() const {
    return m_jobject;
}

Object Object::run_object(const char *method_name, Class &return_type, const char *signature, ...) {
    jobject result = nullptr;
    jmethodID method_id = get_env()->GetMethodID(get_jclass(), method_name, signature);
    if (method_id) {
        va_list vl;
        va_start(vl, signature);
        result = get_env()->CallObjectMethodV(m_jobject, method_id, vl);
        va_end(vl);
    }
    return Object(&return_type, result);
}

void Object::run_void(const char *method_name, const char *signature, ...) {
    jmethodID method_id = get_env()->GetMethodID(get_jclass(), method_name, signature);
    if (method_id) {
        va_list vl;
        va_start(vl, signature);
        get_env()->CallVoidMethodV(m_jobject, method_id, vl);
        va_end(vl);
    }
}

template <>
jboolean Object::run(jboolean, const char *method_name, const char *signature, ...) {
    jboolean ret = false;
    jmethodID method_id = get_env()->GetMethodID(get_jclass(), method_name, signature);
    if (method_id) {
        va_list vl;
        va_start(vl, signature);
        ret = get_env()->CallBooleanMethodV(m_jobject, method_id, vl);
        va_end(vl);
    }
    return ret;
}

template <>
jbyte Object::run(jbyte, const char *method_name, const char *signature, ...) {
    jbyte ret = 0;
    jmethodID method_id = get_env()->GetMethodID(get_jclass(), method_name, signature);
    if (method_id) {
        va_list vl;
        va_start(vl, signature);
        ret = get_env()->CallByteMethodV(m_jobject, method_id, vl);
        va_end(vl);
    }
    return ret;
}

template <>
jchar Object::run(jchar, const char *method_name, const char *signature, ...) {
    jchar ret = 0;
    jmethodID method_id = get_env()->GetMethodID(get_jclass(), method_name, signature);
    if (method_id) {
        va_list vl;
        va_start(vl, signature);
        ret = get_env()->CallCharMethodV(m_jobject, method_id, vl);
        va_end(vl);
    }
    return ret;
}