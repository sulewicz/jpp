#include "Object.h"
#include "Class.h"
#include "Env.h"

using namespace jpp;

Object::Object(Class &_class) : m_class(new Class(_class)) {
}

Object::Object(Class &_class, jobject object) : m_class(new Class(_class)) {
    if (object != nullptr) {
        m_jobject = m_class->get_env()->get_jenv()->NewGlobalRef(object);
    }
}

Object::Object(const Object &other) {
    if (other.m_class != nullptr) {
        m_class = new Class(*other.m_class);
        if (other.m_jobject != nullptr) {
            m_jobject = m_class->get_env()->get_jenv()->NewGlobalRef(other.m_jobject);
        }
    }
}

Object::Object(Object &&other) : m_class(std::move(other.m_class)){
    m_class = other.m_class;
    other.m_class = nullptr;
    m_jobject = other.m_jobject;
    other.m_jobject = nullptr;
}

Object::~Object() {
    if (m_class != nullptr) {
        if (m_jobject != nullptr) {
            m_class->get_env()->get_jenv()->DeleteGlobalRef(m_jobject);
            m_jobject = nullptr;
        }

        delete m_class;
        m_class = nullptr;
    }
}

bool Object::is_valid() const {
    return m_class != nullptr && m_jobject != nullptr;
}

Class &Object::get_class() {
    return *m_class;
}

Env *Object::get_env() const {
    return m_class->get_env();
}

jclass Object::get_jclass() const {
    return m_class->get_jclass();
}

jobject Object::get_jobject() const {
    return m_jobject;
}

Object Object::run_v(Class &return_type, const char *method_name, const char *signature,
                     va_list vl) {
    auto jenv = get_env()->get_jenv();
    auto ret = common::invoke_method<jobject>(jenv, get_jclass(), method_name, signature,
                                              [&](jmethodID method_id) {
                                                  return jenv->CallObjectMethodV(get_jobject(),
                                                                                 method_id,
                                                                                 vl);
                                              });
    return Object(return_type, ret);
}

void Object::run_v(const char *method_name, const char *signature, va_list vl) {
    auto jenv = get_env()->get_jenv();
    common::invoke_method<void>(jenv, get_jclass(), method_name, signature,
                                [&](jmethodID method_id) {
                                    jenv->CallVoidMethodV(get_jobject(), method_id, vl);
                                });
}

template<>
jboolean Object::run_v(jboolean, const char *method_name, const char *signature, va_list vl) {
    auto jenv = get_env()->get_jenv();
    return common::invoke_method<jboolean>(jenv, get_jclass(), method_name, signature,
                                           [&](jmethodID method_id) {
                                               return jenv->CallBooleanMethodV(get_jobject(),
                                                                               method_id,
                                                                               vl);
                                           });
}

template<>
jbyte Object::run_v(jbyte, const char *method_name, const char *signature, va_list vl) {
    auto jenv = get_env()->get_jenv();
    return common::invoke_method<jbyte>(jenv, get_jclass(), method_name, signature,
                                        [&](jmethodID method_id) {
                                            return jenv->CallByteMethodV(get_jobject(),
                                                                         method_id, vl);
                                        });
}

template<>
jchar Object::run_v(jchar, const char *method_name, const char *signature, va_list vl) {
    auto jenv = get_env()->get_jenv();
    return common::invoke_method<jchar>(jenv, get_jclass(), method_name, signature,
                                        [&](jmethodID method_id) {
                                            return jenv->CallCharMethodV(get_jobject(),
                                                                         method_id, vl);
                                        });
}

template<>
jshort Object::run_v(jshort, const char *method_name, const char *signature, va_list vl) {
    auto jenv = get_env()->get_jenv();
    return common::invoke_method<jshort>(jenv, get_jclass(), method_name, signature,
                                         [&](jmethodID method_id) {
                                             return jenv->CallShortMethodV(get_jobject(),
                                                                           method_id,
                                                                           vl);
                                         });
}

template<>
jint Object::run_v(jint, const char *method_name, const char *signature, va_list vl) {
    auto jenv = get_env()->get_jenv();
    return common::invoke_method<jint>(jenv, get_jclass(), method_name, signature,
                                       [&](jmethodID method_id) {
                                           return jenv->CallIntMethodV(get_jobject(),
                                                                       method_id, vl);
                                       });
}

template<>
jlong Object::run_v(jlong, const char *method_name, const char *signature, va_list vl) {
    auto jenv = get_env()->get_jenv();
    return common::invoke_method<jlong>(jenv, get_jclass(), method_name, signature,
                                        [&](jmethodID method_id) {
                                            return jenv->CallLongMethodV(get_jobject(),
                                                                         method_id, vl);
                                        });
}

template<>
jfloat Object::run_v(jfloat, const char *method_name, const char *signature, va_list vl) {
    auto jenv = get_env()->get_jenv();
    return common::invoke_method<jfloat>(jenv, get_jclass(), method_name, signature,
                                         [&](jmethodID method_id) {
                                             return jenv->CallFloatMethodV(get_jobject(),
                                                                           method_id,
                                                                           vl);
                                         });
}

template<>
jdouble Object::run_v(jdouble, const char *method_name, const char *signature, va_list vl) {
    auto jenv = get_env()->get_jenv();
    return common::invoke_method<jdouble>(jenv, get_jclass(), method_name, signature,
                                          [&](jmethodID method_id) {
                                              return jenv->CallDoubleMethodV(get_jobject(),
                                                                             method_id,
                                                                             vl);
                                          });
}
