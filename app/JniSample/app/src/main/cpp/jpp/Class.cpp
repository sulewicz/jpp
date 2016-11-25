#include "Class.h"
#include "Env.h"
#include "Object.h"
#include "Array.h"

using namespace jpp;

Class::Class(Env *env) : m_env(env) {
}

Class::Class(Env *env, jclass _class, const char *class_name) : m_env(env) {
    if (_class != nullptr) {
        m_jclass = _class;
        m_class_name = class_name;
    }
}

Class::Class(const Class &other) : m_env(other.m_env), m_jclass(other.m_jclass),
                                   m_class_name(other.m_class_name) {
}

Class &Class::operator=(const Class &other) {
    m_env = other.m_env;
    m_jclass = other.m_jclass;
    m_class_name = other.m_class_name;
    return *this;
}

Class::~Class() {
}

bool Class::is_valid() const {
    return m_jclass != nullptr;
}

const char *Class::get_class_name() const {
    return m_class_name;
}

std::string Class::get_signature_name() const {
    if (is_array_class()) {
        return get_class_name();
    } else {
        return std::string("L") + get_class_name() + ';';
    }
}

Env *Class::get_env() const {
    return m_env;
}

jclass Class::get_jclass() const {
    return m_jclass;
}

Class Class::get_super_class() {
    return m_env->get_superclass(*this);
}

bool Class::is_assignable_from(Class &from_class) {
    if (is_valid() && from_class.is_valid()) {
        return m_env->get_jenv()->IsAssignableFrom(from_class.get_jclass(), m_jclass);
    }
    return false;
}

bool Class::is_object_class() const {
    return m_jclass != nullptr && m_class_name[0] != '[';
}

bool Class::is_array_class() const {
    return m_jclass != nullptr && m_class_name[0] == '[';
}

Object Class::do_create(const char *signature,
                        ...) {
    va_list vl;
    va_start(vl, signature);
    auto ret = do_create_v(signature, vl);
    va_end(vl);
    return ret;
}

Object Class::run_object(Class &return_type, const char *method_name, const char *signature,
                         ...) {
    va_list vl;
    va_start(vl, signature);
    auto&& ret = run_v(return_type, method_name, signature, vl);
    va_end(vl);
    return ret;
}

void Class::run_void(const char *method_name, const char *signature, ...) {
    va_list vl;
    va_start(vl, signature);
    run_v(method_name, signature, vl);
    va_end(vl);
}

jarray Class::do_create_array(size_t size) {
    return common::new_array(m_env->get_jenv(), m_jclass, m_class_name, size);
}

Object Class::do_create_v(const char *signature, va_list vl) {
    if (is_object_class()) {
        auto jenv = m_env->get_jenv();
        auto ret = common::invoke_method<jobject>(jenv, get_jclass(), "<init>", signature,
                                                  [&](jmethodID method_id) {
                                                      return jenv->NewObjectV(get_jclass(),
                                                                              method_id,
                                                                              vl);
                                                  });
        return m_env->wrap(*this, ret);
    } else {
        return m_env->wrap(*this, nullptr);
    }
}

Object Class::run_v(Class &return_type, const char *method_name, const char *signature,
                    va_list vl) {
    auto jenv = m_env->get_jenv();
    auto ret = common::invoke_static_method<jobject>(jenv, get_jclass(), method_name,
                                                     signature,
                                                     [&](jmethodID method_id) {
                                                         return m_env->get_jenv()->CallStaticObjectMethodV(
                                                                 get_jclass(),
                                                                 method_id,
                                                                 vl);
                                                     });
    return m_env->wrap(return_type, ret);
}

void Class::run_v(const char *method_name, const char *signature, va_list vl) {
    auto jenv = m_env->get_jenv();
    common::invoke_static_method<void>(jenv, get_jclass(), method_name, signature,
                                       [&](jmethodID method_id) {
                                           m_env->get_jenv()->CallStaticVoidMethodV(get_jclass(),
                                                                                   method_id,
                                                                                   vl);
                                       });
}

template<>
jboolean Class::run_v(jboolean, const char *method_name, const char *signature, va_list vl) {
    auto jenv = m_env->get_jenv();
    return common::invoke_static_method<jboolean>(jenv, get_jclass(), method_name, signature,
                                                  [&](jmethodID method_id) {
                                                      return m_env->get_jenv()->CallStaticBooleanMethodV(
                                                              get_jclass(),
                                                              method_id,
                                                              vl);
                                                  });
}

template<>
jbyte Class::run_v(jbyte, const char *method_name, const char *signature, va_list vl) {
    auto jenv = m_env->get_jenv();
    return common::invoke_static_method<jbyte>(jenv, get_jclass(), method_name, signature,
                                               [&](jmethodID method_id) {
                                                   return m_env->get_jenv()->CallStaticByteMethodV(
                                                           get_jclass(),
                                                           method_id, vl);
                                               });
}

template<>
jchar Class::run_v(jchar, const char *method_name, const char *signature, va_list vl) {
    auto jenv = m_env->get_jenv();
    return common::invoke_static_method<jchar>(jenv, get_jclass(), method_name, signature,
                                               [&](jmethodID method_id) {
                                                   return jenv->CallStaticCharMethodV(
                                                           get_jclass(),
                                                           method_id, vl);
                                               });
}

template<>
jshort Class::run_v(jshort, const char *method_name, const char *signature, va_list vl) {
    auto jenv = m_env->get_jenv();
    return common::invoke_static_method<jshort>(jenv, get_jclass(), method_name, signature,
                                                [&](jmethodID method_id) {
                                                    return m_env->get_jenv()->CallStaticShortMethodV(
                                                            get_jclass(),
                                                            method_id, vl);
                                                });
}

template<>
jint Class::run_v(jint, const char *method_name, const char *signature, va_list vl) {
    auto jenv = m_env->get_jenv();
    return common::invoke_static_method<jint>(jenv, get_jclass(), method_name, signature,
                                              [&](jmethodID method_id) {
                                                  return jenv->CallStaticIntMethodV(
                                                          get_jclass(),
                                                          method_id, vl);
                                              });
}

template<>
jlong Class::run_v(jlong, const char *method_name, const char *signature, va_list vl) {
    auto jenv = m_env->get_jenv();
    return common::invoke_static_method<jlong>(jenv, get_jclass(), method_name, signature,
                                               [&](jmethodID method_id) {
                                                   return jenv->CallStaticLongMethodV(
                                                           get_jclass(),
                                                           method_id, vl);
                                               });
}

template<>
jfloat Class::run_v(jfloat, const char *method_name, const char *signature, va_list vl) {
    auto jenv = m_env->get_jenv();
    return common::invoke_static_method<jfloat>(jenv, get_jclass(), method_name, signature,
                                                [&](jmethodID method_id) {
                                                    return jenv->CallStaticFloatMethodV(
                                                            get_jclass(),
                                                            method_id, vl);
                                                });
}

template<>
jdouble Class::run_v(jdouble, const char *method_name, const char *signature, va_list vl) {
    auto jenv = m_env->get_jenv();
    return common::invoke_static_method<jdouble>(jenv, get_jclass(), method_name, signature,
                                                 [&](jmethodID method_id) {
                                                     return jenv->CallStaticDoubleMethodV(
                                                             get_jclass(),
                                                             method_id,
                                                             vl);
                                                 });
}
