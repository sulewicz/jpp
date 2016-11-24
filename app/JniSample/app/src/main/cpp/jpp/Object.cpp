#include "Object.h"
#include "Class.h"

using namespace jpp;

Object::Object(Class *_class) : m_class(_class) {
}

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

std::string Object::to_string() {
    std::string ret;
    if (m_class->get_class_name() == "java/lang/String") {
        const char *native_string = get_env()->GetStringUTFChars((jstring) m_jobject, nullptr);
        ret = native_string;
        get_env()->ReleaseStringUTFChars((jstring) m_jobject, native_string);
    } else {
        Class string_class(get_env(), "java/lang/String");
        ret = call_object("toString", string_class).to_string();
    }
    return ret;
}

Object Object::run_v(Class &return_type, const char *method_name, const char *signature,
                     va_list vl) {
    auto ret = common::invoke_method<jobject>(get_env(), get_jclass(), method_name, signature,
                                              [&](jmethodID method_id) {
                                                  return get_env()->CallObjectMethodV(get_jobject(),
                                                                                      method_id,
                                                                                      vl);
                                              });
    return Object(&return_type, ret);
}

void Object::run_v(const char *method_name, const char *signature, va_list vl) {
    common::invoke_method<void>(get_env(), get_jclass(), method_name, signature,
                                [&](jmethodID method_id) {
                                    get_env()->CallVoidMethodV(get_jobject(), method_id, vl);
                                });
}

template<>
jboolean Object::run_v(jboolean, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_method<jboolean>(get_env(), get_jclass(), method_name, signature,
                                           [&](jmethodID method_id) {
                                               return get_env()->CallBooleanMethodV(get_jobject(),
                                                                                    method_id,
                                                                                    vl);
                                           });
}

template<>
jbyte Object::run_v(jbyte, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_method<jbyte>(get_env(), get_jclass(), method_name, signature,
                                        [&](jmethodID method_id) {
                                            return get_env()->CallByteMethodV(get_jobject(),
                                                                              method_id, vl);
                                        });
}

template<>
jchar Object::run_v(jchar, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_method<jchar>(get_env(), get_jclass(), method_name, signature,
                                        [&](jmethodID method_id) {
                                            return get_env()->CallCharMethodV(get_jobject(),
                                                                              method_id, vl);
                                        });
}

template<>
jshort Object::run_v(jshort, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_method<jshort>(get_env(), get_jclass(), method_name, signature,
                                         [&](jmethodID method_id) {
                                             return get_env()->CallShortMethodV(get_jobject(),
                                                                                method_id,
                                                                                vl);
                                         });
}

template<>
jint Object::run_v(jint, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_method<jint>(get_env(), get_jclass(), method_name, signature,
                                       [&](jmethodID method_id) {
                                           return get_env()->CallIntMethodV(get_jobject(),
                                                                            method_id, vl);
                                       });
}

template<>
jlong Object::run_v(jlong, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_method<jlong>(get_env(), get_jclass(), method_name, signature,
                                        [&](jmethodID method_id) {
                                            return get_env()->CallLongMethodV(get_jobject(),
                                                                              method_id, vl);
                                        });
}

template<>
jfloat Object::run_v(jfloat, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_method<jfloat>(get_env(), get_jclass(), method_name, signature,
                                         [&](jmethodID method_id) {
                                             return get_env()->CallFloatMethodV(get_jobject(),
                                                                                method_id,
                                                                                vl);
                                         });
}

template<>
jdouble Object::run_v(jdouble, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_method<jdouble>(get_env(), get_jclass(), method_name, signature,
                                          [&](jmethodID method_id) {
                                              return get_env()->CallDoubleMethodV(get_jobject(),
                                                                                  method_id,
                                                                                  vl);
                                          });
}
