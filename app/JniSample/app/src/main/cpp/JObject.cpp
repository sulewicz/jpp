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

JNIEnv *JObject::get_env() const {
    return m_class->get_env();
}

jclass JObject::get_jclass() const {
    return m_class->get_jclass();
}

jobject JObject::get_jobject() const {
    return m_object;
}

jobject JObject::get_local_ref() const {
    return get_env()->NewLocalRef(m_object);
}

JObject JObject::do_object(const char* method_name, JClass& return_type, const char *signature, ...) {
    jobject result = nullptr;
    jmethodID method_id = get_env()->GetMethodID(get_jclass(), method_name, signature);
    if (method_id) {
        va_list vl;
        va_start(vl, signature);
        result = get_env()->CallObjectMethodV(m_object, method_id, vl);
        va_end(vl);
    }
    return JObject(&return_type, result);
}

jboolean JObject::do_boolean(const char* method_name, const char *signature, ...) {
    jboolean result = false;
    jmethodID method_id = get_env()->GetMethodID(get_jclass(), method_name, signature);
    if (method_id) {
        va_list vl;
        va_start(vl, signature);
        result = get_env()->CallBooleanMethodV(m_object, method_id, vl);
        va_end(vl);
    }
    return result;
}
