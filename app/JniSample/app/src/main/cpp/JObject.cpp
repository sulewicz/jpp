#include "JObject.h"
#include "JClass.h"

JObject::JObject(JClass *_class, jobject object) : m_class(_class) {
    if (object != nullptr) {
        m_object = m_class->get_env()->NewGlobalRef(object);
    }
}

JObject::JObject(const JObject &other) : m_class(other.m_class) {
    if (other.is_valid()) {
        m_object = m_class->get_env()->NewGlobalRef(other.m_object);
    }
}

JObject::~JObject() {
    if (is_valid()) {
        m_class->get_env()->DeleteGlobalRef(m_object);
        m_object = nullptr;
    }
}

bool JObject::is_valid() const {
    return m_object != nullptr;
}

JClass *JObject::get_class() const {
    return m_class;
}

JObject JObject::do_object(const char* method_name, const char *signature, ...) {
    jobject result = nullptr;
    jmethodID method_id = m_class->get_env()->GetMethodID(m_class->get_jclass(), method_name, signature);
    if (method_id) {
        va_list vl;
        va_start(vl, signature);
        result = m_class->get_env()->CallObjectMethodV(m_class->get_jclass(), method_id, vl);
        va_end(vl);
    }
    return JObject(m_class, result);
}

jboolean JObject::do_boolean(const char* method_name, const char *signature, ...) {
    jboolean result = false;
    jmethodID method_id = m_class->get_env()->GetMethodID(m_class->get_jclass(), method_name, signature);
    if (method_id) {
        va_list vl;
        va_start(vl, signature);
        result = m_class->get_env()->CallBooleanMethodV(m_class->get_jclass(), method_id, vl);
        va_end(vl);
    }
    return result;
}
