#include "Env.h"
#include "Cache.h"
#include "Class.h"
#include "Object.h"

#include <algorithm>

using namespace jpp;

static Cache GLOBAL_CACHE;

Env::Env(JNIEnv *jenv) : m_jenv(jenv), m_cache(GLOBAL_CACHE) {

}

Env::Env(JNIEnv *jenv, Cache &cache) : m_jenv(jenv), m_cache(cache) {

}

Env::~Env() {

}

Cache &Env::get_cache() {
    return m_cache;
}

JNIEnv *Env::get_jenv() {
    return m_jenv;
}

Class Env::find_class(const char *name) {
    auto _jclass = m_jenv->FindClass(name);
    auto ret = m_cache.add_class(this, name, _jclass);
    return ret;
}

Class Env::wrap(jclass _jclass) {
    if (_jclass != nullptr) {
        if (m_get_name_method_id == nullptr) {
            auto class_class = find_class("java/lang/Class");
            m_get_name_method_id = m_jenv->GetMethodID(class_class.get_jclass(), "getName",
                                                       "()Ljava/lang/String;");
        }
        jstring jni_name = (jstring) m_jenv->CallObjectMethod(_jclass, m_get_name_method_id);
        const char *native_string = m_jenv->GetStringUTFChars((jstring) jni_name,
                                                              nullptr);
        std::string class_name = native_string;
        std::replace(class_name.begin(), class_name.end(), '.', '/');

        Class ret = m_cache.get_class(this, class_name.c_str());
        if (!ret.is_valid()) {
            ret = m_cache.add_class(this, class_name.c_str(), _jclass);
        }
        m_jenv->ReleaseStringUTFChars((jstring) jni_name, native_string);
        return ret;
    } else {
        return Class(this);
    }
}

Object Env::wrap(jobject _jobject) {
    if (_jobject != nullptr) {
        jclass _jclass = m_jenv->GetObjectClass(_jobject);
        Class _class = wrap(_jclass);
        return Object(_class, _jobject);
    } else {
        Class _class(this);
        return Object(_class);
    }
}

Object Env::wrap(const char *name, jobject _jobject) {
    Class _class = find_class(name);
    return Object(_class, _jobject);
}

Object Env::wrap(Class &_class, jobject _jobject) {
    return Object(_class, _jobject);
}

Array<Object> Env::wrap(jobjectArray _jobjectArray) {
    Class _class = wrap(m_jenv->GetObjectClass(_jobjectArray));
    return Array<Object>(_class, _jobjectArray);
}

Array<jbyte> Env::wrap(jbyteArray _jbyteArray) {
    Class _class = wrap(m_jenv->GetObjectClass(_jbyteArray));
    return Array<jbyte>(_class, _jbyteArray);
}

Array<Object> Env::create_array(size_t size, Class& element_class) {
    return wrap(m_jenv->NewObjectArray(size, element_class.get_jclass(), nullptr));
}

template<>
Array<jbyte> Env::create_array(size_t size, jbyte* type) {
    return wrap(m_jenv->NewByteArray(size));
}

Class Env::get_superclass(Class &_class) {
    if (_class.is_valid()) {
        auto _jclass = _class.get_jclass();
        auto jsuper_class = m_jenv->GetSuperclass(_jclass);
        auto super_class = wrap(jsuper_class);
        return super_class;
    } else {
        return Class(this);
    }
}

jmethodID Env::find_method_id(Class &_class, const char *name, const char *signature) {
    return m_jenv->GetMethodID(_class.get_jclass(), name, signature);
}

Object Env::call_method(Object &object, const char *method_name,
                        const char *signature, va_list vl) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    jobject ret = m_jenv->CallObjectMethodV(object.get_jobject(), method_id, vl);
    return wrap(ret);
}

void Env::call_method(Object &object, const char *method_name,
                      const char *signature, va_list vl, void *type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    m_jenv->CallVoidMethodV(object.get_jobject(), method_id, vl);
}

template<>
jboolean Env::call_method(Object &object, const char *method_name,
                          const char *signature, va_list vl, jboolean type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    return m_jenv->CallBooleanMethodV(object.get_jobject(), method_id, vl);
}

template<>
jbyte Env::call_method(Object &object, const char *method_name,
                       const char *signature, va_list vl, jbyte type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    return m_jenv->CallByteMethodV(object.get_jobject(), method_id, vl);
}

template<>
jchar Env::call_method(Object &object, const char *method_name,
                       const char *signature, va_list vl, jchar type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    return m_jenv->CallCharMethodV(object.get_jobject(), method_id, vl);
}

template<>
jshort Env::call_method(Object &object, const char *method_name,
                        const char *signature, va_list vl, jshort type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    return m_jenv->CallShortMethodV(object.get_jobject(), method_id, vl);
}

template<>
jint Env::call_method(Object &object, const char *method_name,
                      const char *signature, va_list vl, jint type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    return m_jenv->CallIntMethodV(object.get_jobject(), method_id, vl);
}

template<>
jlong Env::call_method(Object &object, const char *method_name,
                       const char *signature, va_list vl, jlong type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    return m_jenv->CallLongMethodV(object.get_jobject(), method_id, vl);
}

template<>
jfloat Env::call_method(Object &object, const char *method_name,
                        const char *signature, va_list vl, jfloat type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    return m_jenv->CallFloatMethodV(object.get_jobject(), method_id, vl);
}

template<>
jdouble Env::call_method(Object &object, const char *method_name,
                         const char *signature, va_list vl, jdouble type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    return m_jenv->CallDoubleMethodV(object.get_jobject(), method_id, vl);
}


jmethodID Env::find_static_method_id(Class &_class, const char *name, const char *signature) {
    return m_jenv->GetStaticMethodID(_class.get_jclass(), name, signature);
}

Object Env::call_static_method(Class &_class, const char *method_name,
                               const char *signature, va_list vl) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    jobject ret = m_jenv->CallStaticObjectMethodV(_class.get_jclass(), method_id, vl);
    return wrap(ret);
}

void Env::call_static_method(Class &_class, const char *method_name,
                             const char *signature, va_list vl, void *type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    m_jenv->CallStaticVoidMethodV(_class.get_jclass(), method_id, vl);
}

template<>
jboolean Env::call_static_method(Class &_class, const char *method_name,
                                 const char *signature, va_list vl, jboolean type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    return m_jenv->CallStaticBooleanMethodV(_class.get_jclass(), method_id, vl);
}

template<>
jbyte Env::call_static_method(Class &_class, const char *method_name,
                              const char *signature, va_list vl, jbyte type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    return m_jenv->CallStaticByteMethodV(_class.get_jclass(), method_id, vl);
}

template<>
jchar Env::call_static_method(Class &_class, const char *method_name,
                              const char *signature, va_list vl, jchar type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    return m_jenv->CallStaticCharMethodV(_class.get_jclass(), method_id, vl);
}

template<>
jshort Env::call_static_method(Class &_class, const char *method_name,
                               const char *signature, va_list vl, jshort type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    return m_jenv->CallStaticShortMethodV(_class.get_jclass(), method_id, vl);
}

template<>
jint Env::call_static_method(Class &_class, const char *method_name,
                             const char *signature, va_list vl, jint type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    return m_jenv->CallStaticIntMethodV(_class.get_jclass(), method_id, vl);
}

template<>
jlong Env::call_static_method(Class &_class, const char *method_name,
                              const char *signature, va_list vl, jlong type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    return m_jenv->CallStaticLongMethodV(_class.get_jclass(), method_id, vl);
}

template<>
jfloat Env::call_static_method(Class &_class, const char *method_name,
                               const char *signature, va_list vl, jfloat type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    return m_jenv->CallStaticFloatMethodV(_class.get_jclass(), method_id, vl);
}

template<>
jdouble Env::call_static_method(Class &_class, const char *method_name,
                                const char *signature, va_list vl, jdouble type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    return m_jenv->CallStaticDoubleMethodV(_class.get_jclass(), method_id, vl);
}
