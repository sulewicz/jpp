#include "Class.h"
#include <algorithm>

using namespace jpp;

Class::Class(JNIEnv *env) : m_env(env) {
}

Class::Class(JNIEnv *env, const char *class_name) : m_env(env), m_class_name(class_name) {
    if (class_name != nullptr) {
        jclass _class = m_env->FindClass(m_class_name.c_str());
        if (_class != nullptr) {
            m_jclass = (jclass) m_env->NewGlobalRef(_class);
        }
    }
}

Class::Class(JNIEnv *env, jclass _class) : m_env(env) {
    if (_class != nullptr) {
        m_jclass = (jclass) m_env->NewGlobalRef(_class);
        Class class_class(env, "java/lang/Class");
        Object class_object(&class_class, m_jclass);
        m_class_name = resolve_class_name(env, class_object);
    }
}

Class::Class(const Class &other) : m_env(other.m_env), m_class_name(other.m_class_name) {
    if (other.is_valid()) {
        m_jclass = (jclass) m_env->NewGlobalRef(other.m_jclass);
    }
}

Class::Class(JNIEnv *env, jclass _class, const char *class_name) : m_env(env),
                                                                   m_class_name(class_name) {
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

const std::string &Class::get_class_name() const {
    return m_class_name;
}

std::string Class::get_signature_name() const {
    if (is_array_class()) {
        return get_class_name();
    } else {
        return std::string("L") + get_class_name() + ';';
    }
}

JNIEnv *Class::get_env() const {
    return m_env;
}

jclass Class::get_jclass() const {
    return m_jclass;
}

Class Class::get_super_class() {
    if (is_valid()) {
        return Class(m_env, m_env->GetSuperclass(m_jclass));
    } else {
        return Class(m_env);
    }
}

bool Class::is_assignable_from(Class &from_class) {
    if (is_valid() && from_class.is_valid()) {
        return m_env->IsAssignableFrom(from_class.get_jclass(), m_jclass);
    }
    return false;
}

bool Class::is_object_class() const {
    return m_jclass != nullptr && m_class_name[0] != '[';
}

bool Class::is_array_class() const {
    return m_jclass != nullptr && m_class_name[0] == '[';
}

Class Class::resolve_class(JNIEnv *env, jobject object) {
    Class class_class(env, "java/lang/Class");
    Class object_class(env, "java/lang/Object");
    Object object_instance(&object_class, object);

    // Retrieving class object
    Object class_object = object_instance.call_object("getClass", class_class);
    // Retrieving class name
    auto class_name = resolve_class_name(env, class_object);

    return Class(env, (jclass) class_object.get_jobject(), class_name.c_str());
}

std::string Class::resolve_class_name(JNIEnv *env, Object &class_object) {
    Class string_class(env, "java/lang/String");
    Object class_name_object = class_object.call_object("getName", string_class);

    std::string class_name = class_name_object.to_string();
    std::replace(class_name.begin(), class_name.end(), '.', '/');
    return class_name;
}

Object Class::do_create_v(const char *signature, va_list vl) {
    if (is_object_class()) {
        auto ret = common::invoke_method<jobject>(get_env(), get_jclass(), "<init>", signature,
                                                  [&](jmethodID method_id) {
                                                      return get_env()->NewObjectV(get_jclass(),
                                                                                   method_id,
                                                                                   vl);
                                                  });
        return Object(this, ret);
    } else {
        return Object(this);
    }
}

Object Class::run_v(Class &return_type, const char *method_name, const char *signature,
                    va_list vl) {
    auto ret = common::invoke_static_method<jobject>(get_env(), get_jclass(), method_name,
                                                     signature,
                                                     [&](jmethodID method_id) {
                                                         return get_env()->CallStaticObjectMethodV(
                                                                 get_jclass(),
                                                                 method_id,
                                                                 vl);
                                                     });
    return Object(&return_type, ret);
}

void Class::run_v(const char *method_name, const char *signature, va_list vl) {
    common::invoke_static_method<void>(get_env(), get_jclass(), method_name, signature,
                                       [&](jmethodID method_id) {
                                           get_env()->CallStaticVoidMethodV(get_jclass(), method_id,
                                                                            vl);
                                       });
}

template<>
jboolean Class::run_v(jboolean, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_static_method<jboolean>(get_env(), get_jclass(), method_name, signature,
                                                  [&](jmethodID method_id) {
                                                      return get_env()->CallStaticBooleanMethodV(
                                                              get_jclass(),
                                                              method_id,
                                                              vl);
                                                  });
}

template<>
jbyte Class::run_v(jbyte, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_static_method<jbyte>(get_env(), get_jclass(), method_name, signature,
                                               [&](jmethodID method_id) {
                                                   return get_env()->CallStaticByteMethodV(
                                                           get_jclass(),
                                                           method_id, vl);
                                               });
}

template<>
jchar Class::run_v(jchar, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_static_method<jchar>(get_env(), get_jclass(), method_name, signature,
                                               [&](jmethodID method_id) {
                                                   return get_env()->CallStaticCharMethodV(
                                                           get_jclass(),
                                                           method_id, vl);
                                               });
}

template<>
jshort Class::run_v(jshort, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_static_method<jshort>(get_env(), get_jclass(), method_name, signature,
                                                [&](jmethodID method_id) {
                                                    return get_env()->CallStaticShortMethodV(
                                                            get_jclass(),
                                                            method_id, vl);
                                                });
}

template<>
jint Class::run_v(jint, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_static_method<jint>(get_env(), get_jclass(), method_name, signature,
                                              [&](jmethodID method_id) {
                                                  return get_env()->CallStaticIntMethodV(
                                                          get_jclass(),
                                                          method_id, vl);
                                              });
}

template<>
jlong Class::run_v(jlong, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_static_method<jlong>(get_env(), get_jclass(), method_name, signature,
                                               [&](jmethodID method_id) {
                                                   return get_env()->CallStaticLongMethodV(
                                                           get_jclass(),
                                                           method_id, vl);
                                               });
}

template<>
jfloat Class::run_v(jfloat, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_static_method<jfloat>(get_env(), get_jclass(), method_name, signature,
                                                [&](jmethodID method_id) {
                                                    return get_env()->CallStaticFloatMethodV(
                                                            get_jclass(),
                                                            method_id, vl);
                                                });
}

template<>
jdouble Class::run_v(jdouble, const char *method_name, const char *signature, va_list vl) {
    return common::invoke_static_method<jdouble>(get_env(), get_jclass(), method_name, signature,
                                                 [&](jmethodID method_id) {
                                                     return get_env()->CallStaticDoubleMethodV(
                                                             get_jclass(),
                                                             method_id,
                                                             vl);
                                                 });
}
