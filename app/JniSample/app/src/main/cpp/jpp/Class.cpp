#include "Class.h"

#include <algorithm>

using namespace jpp;

Class::Class(JNIEnv *env, const char *class_name) : m_env(env), m_class_name(class_name) {
    jclass _class = m_env->FindClass(m_class_name.c_str());
    if (_class != nullptr) {
        m_jclass = (jclass) m_env->NewGlobalRef(_class);
    }
}

Class::Class(const Class &other) : m_env(other.m_env), m_class_name(other.m_class_name) {
    if (other.is_valid()) {
        m_jclass = (jclass) m_env->NewGlobalRef(other.m_jclass);
    }
}

Class::Class(JNIEnv *env, jclass _class, const char *class_name) : m_env(env), m_class_name(class_name) {
    if (_class != nullptr) {
        m_jclass = (jclass) m_env->NewGlobalRef(_class);
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

const std::string& Class::get_class_name() const {
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

Class Class::resolve_class(JNIEnv *env, jobject object) {
    // TODO: handle arrays
    Class class_class(env, "java/lang/Class");
    Class object_class(env, "java/lang/Object");
    Class string_class(env, "java/lang/String");
    Object object_instance(&object_class, object);

    // Retrieving class object
    Object class_object = object_instance.call_object("getClass", class_class);
    // Retrieving class name
    Object class_name_object = class_object.call_object("getName", string_class);

    std::string class_name = class_name_object.to_string();
    std::replace(class_name.begin(), class_name.end(), '.', '/');

    return Class(env, (jclass) class_object.get_jobject(), class_name.c_str());
}
