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

Object Object::do_object(const char* method_name, Class& return_type, const char *signature, ...) {
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

jboolean Object::do_boolean(const char* method_name, const char *signature, ...) {
    jboolean result = false;
    jmethodID method_id = get_env()->GetMethodID(get_jclass(), method_name, signature);
    if (method_id) {
        va_list vl;
        va_start(vl, signature);
        result = get_env()->CallBooleanMethodV(m_jobject, method_id, vl);
        va_end(vl);
    }
    return result;
}
