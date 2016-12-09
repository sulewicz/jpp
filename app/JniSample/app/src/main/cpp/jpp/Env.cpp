#include "jpp_config.h"
#include "Env.h"
#include "Cache.h"
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

bool Env::is_exception_pending() {
    return m_jenv->ExceptionCheck();
}

Object Env::consume_exception() {
    jthrowable _jthrowable = m_jenv->ExceptionOccurred();
    m_jenv->ExceptionClear();
    return wrap(_jthrowable);
}

void Env::cancel_exception() {
    m_jenv->ExceptionClear();
}

void Env::check_for_exception() {
#if JPP_EXCEPTIONS_SUPPORTED
    if (m_jenv->ExceptionCheck()) {
        jthrowable _jthrowable = m_jenv->ExceptionOccurred();
        m_jenv->ExceptionClear();
        throw wrap(_jthrowable);
    }
#endif
}

bool Env::throw_exception(Object &exception) {
    if (exception.is_instance_of(find_class("java/lang/Throwable"))) {
        m_jenv->Throw((jthrowable) exception.get_jobject());
        return true;
    } else {
        return false;
    }
}

Class Env::find_class(const char *class_name) {
    Class ret = m_cache.get_class(this, class_name);
    if (!ret.is_valid()) {
        auto _jclass = m_jenv->FindClass(class_name);
        check_for_exception();
        ret = m_cache.add_class(this, class_name, _jclass);
    }
    return ret;
}

Class Env::find_array_class(const char *class_name) {
    return find_array_class(1, class_name);
}

Class Env::find_array_class(int dim, const char *class_name) {
    auto signature = std::string(dim, '[') + 'L' + class_name + ';';
    return find_class(signature.c_str());
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

Array<Object> Env::wrap(jobjectArray _jarray) {
    Class _class = wrap(m_jenv->GetObjectClass(_jarray));
    return Array<Object>(_class, _jarray);
}

Array<jboolean> Env::wrap(jbooleanArray _jarray) {
    Class _class = wrap(m_jenv->GetObjectClass(_jarray));
    return Array<jboolean>(_class, _jarray);
}

Array<jbyte> Env::wrap(jbyteArray _jarray) {
    Class _class = wrap(m_jenv->GetObjectClass(_jarray));
    return Array<jbyte>(_class, _jarray);
}

Array<jchar> Env::wrap(jcharArray _jarray) {
    Class _class = wrap(m_jenv->GetObjectClass(_jarray));
    return Array<jchar>(_class, _jarray);
}

Array<jshort> Env::wrap(jshortArray _jarray) {
    Class _class = wrap(m_jenv->GetObjectClass(_jarray));
    return Array<jshort>(_class, _jarray);
}

Array<jint> Env::wrap(jintArray _jarray) {
    Class _class = wrap(m_jenv->GetObjectClass(_jarray));
    return Array<jint>(_class, _jarray);
}

Array<jlong> Env::wrap(jlongArray _jarray) {
    Class _class = wrap(m_jenv->GetObjectClass(_jarray));
    return Array<jlong>(_class, _jarray);
}

Array<jfloat> Env::wrap(jfloatArray _jarray) {
    Class _class = wrap(m_jenv->GetObjectClass(_jarray));
    return Array<jfloat>(_class, _jarray);
}

Array<jdouble> Env::wrap(jdoubleArray _jarray) {
    Class _class = wrap(m_jenv->GetObjectClass(_jarray));
    return Array<jdouble>(_class, _jarray);
}

Array<Object> Env::create_array(size_t size, Class &element_class) {
    return wrap(m_jenv->NewObjectArray(size, element_class.get_jclass(), nullptr));
}

template<>
Array<jboolean> Env::create_array(size_t size, jboolean *type) {
    return wrap(m_jenv->NewBooleanArray(size));
}

template<>
Array<jbyte> Env::create_array(size_t size, jbyte *type) {
    return wrap(m_jenv->NewByteArray(size));
}

template<>
Array<jchar> Env::create_array(size_t size, jchar *type) {
    return wrap(m_jenv->NewCharArray(size));
}

template<>
Array<jshort> Env::create_array(size_t size, jshort *type) {
    return wrap(m_jenv->NewShortArray(size));
}

template<>
Array<jint> Env::create_array(size_t size, jint *type) {
    return wrap(m_jenv->NewIntArray(size));
}

template<>
Array<jlong> Env::create_array(size_t size, jlong *type) {
    return wrap(m_jenv->NewLongArray(size));
}

template<>
Array<jfloat> Env::create_array(size_t size, jfloat *type) {
    return wrap(m_jenv->NewFloatArray(size));
}

template<>
Array<jdouble> Env::create_array(size_t size, jdouble *type) {
    return wrap(m_jenv->NewDoubleArray(size));
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
    jmethodID ret = m_jenv->GetMethodID(_class.get_jclass(), name, signature);
    check_for_exception();
    return ret;
}

Object Env::call_constructor(Class &_class, const char *signature, va_list vl) {
    jmethodID method_id = find_method_id(_class, "<init>", signature);
    if (method_id) {
        auto ret = m_jenv->NewObjectV(_class.get_jclass(), method_id, vl);
        check_for_exception();
        return Object(_class, ret);
    } else {
        return Object(_class, nullptr);
    }
}

Object Env::call_method(Object &object, const char *method_name,
                        const char *signature, va_list vl) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallObjectMethodV(object.get_jobject(), method_id, vl);
        check_for_exception();
        return wrap(ret);
    } else {
        return Object();
    }
}

void Env::call_method(Object &object, const char *method_name,
                      const char *signature, va_list vl, void *type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    if (method_id) {
        m_jenv->CallVoidMethodV(object.get_jobject(), method_id, vl);
        check_for_exception();
    }
}

template<>
jboolean Env::call_method(Object &object, const char *method_name,
                          const char *signature, va_list vl, jboolean type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallBooleanMethodV(object.get_jobject(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return false;
    }
}

template<>
jbyte Env::call_method(Object &object, const char *method_name,
                       const char *signature, va_list vl, jbyte type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallByteMethodV(object.get_jobject(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jchar Env::call_method(Object &object, const char *method_name,
                       const char *signature, va_list vl, jchar type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallCharMethodV(object.get_jobject(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jshort Env::call_method(Object &object, const char *method_name,
                        const char *signature, va_list vl, jshort type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallShortMethodV(object.get_jobject(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jint Env::call_method(Object &object, const char *method_name,
                      const char *signature, va_list vl, jint type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallIntMethodV(object.get_jobject(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jlong Env::call_method(Object &object, const char *method_name,
                       const char *signature, va_list vl, jlong type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallLongMethodV(object.get_jobject(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jfloat Env::call_method(Object &object, const char *method_name,
                        const char *signature, va_list vl, jfloat type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallFloatMethodV(object.get_jobject(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jdouble Env::call_method(Object &object, const char *method_name,
                         const char *signature, va_list vl, jdouble type) {
    jmethodID method_id = find_method_id(object.get_class(), method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallDoubleMethodV(object.get_jobject(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

jmethodID Env::find_static_method_id(Class &_class, const char *name, const char *signature) {
    jmethodID ret = m_jenv->GetStaticMethodID(_class.get_jclass(), name, signature);
    check_for_exception();
    return ret;
}

Object Env::call_static_method(Class &_class, const char *method_name,
                               const char *signature, va_list vl) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallStaticObjectMethodV(_class.get_jclass(), method_id, vl);
        check_for_exception();
        return wrap(ret);
    } else {
        return Object();
    }
}

void Env::call_static_method(Class &_class, const char *method_name,
                             const char *signature, va_list vl, void *type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    if (method_id) {
        m_jenv->CallStaticVoidMethodV(_class.get_jclass(), method_id, vl);
        check_for_exception();
    }
}

template<>
jboolean Env::call_static_method(Class &_class, const char *method_name,
                                 const char *signature, va_list vl, jboolean type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallStaticBooleanMethodV(_class.get_jclass(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return false;
    }
}

template<>
jbyte Env::call_static_method(Class &_class, const char *method_name,
                              const char *signature, va_list vl, jbyte type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallStaticByteMethodV(_class.get_jclass(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jchar Env::call_static_method(Class &_class, const char *method_name,
                              const char *signature, va_list vl, jchar type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallStaticCharMethodV(_class.get_jclass(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jshort Env::call_static_method(Class &_class, const char *method_name,
                               const char *signature, va_list vl, jshort type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallStaticShortMethodV(_class.get_jclass(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jint Env::call_static_method(Class &_class, const char *method_name,
                             const char *signature, va_list vl, jint type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallStaticIntMethodV(_class.get_jclass(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jlong Env::call_static_method(Class &_class, const char *method_name,
                              const char *signature, va_list vl, jlong type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallStaticLongMethodV(_class.get_jclass(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jfloat Env::call_static_method(Class &_class, const char *method_name,
                               const char *signature, va_list vl, jfloat type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallStaticFloatMethodV(_class.get_jclass(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jdouble Env::call_static_method(Class &_class, const char *method_name,
                                const char *signature, va_list vl, jdouble type) {
    jmethodID method_id = find_static_method_id(_class, method_name, signature);
    if (method_id) {
        auto ret = m_jenv->CallStaticDoubleMethodV(_class.get_jclass(), method_id, vl);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

jfieldID Env::find_field_id(Class &_class, const char *name, const char *signature) {
    jfieldID ret = m_jenv->GetFieldID(_class.get_jclass(), name, signature);
    check_for_exception();
    return ret;
}

Object Env::get_field(Object &object, const char *field_name, const char *signature) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetObjectField(object.get_jobject(), field_id);
        check_for_exception();
        return wrap(ret);
    } else {
        return Object();
    }
}

template<>
jboolean Env::get_field(Object &object, const char *field_name, const char *signature,
                        jboolean type) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetBooleanField(object.get_jobject(), field_id);
        check_for_exception();
        return ret;
    } else {
        return false;
    }
}

template<>
jbyte Env::get_field(Object &object, const char *field_name, const char *signature,
                     jbyte type) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetByteField(object.get_jobject(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jchar Env::get_field(Object &object, const char *field_name, const char *signature,
                     jchar type) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetCharField(object.get_jobject(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jshort Env::get_field(Object &object, const char *field_name, const char *signature,
                      jshort type) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetShortField(object.get_jobject(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jint Env::get_field(Object &object, const char *field_name, const char *signature,
                    jint type) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetIntField(object.get_jobject(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jlong Env::get_field(Object &object, const char *field_name, const char *signature,
                     jlong type) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetLongField(object.get_jobject(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jfloat Env::get_field(Object &object, const char *field_name, const char *signature,
                     jfloat type) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetFloatField(object.get_jobject(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jdouble Env::get_field(Object &object, const char *field_name, const char *signature,
                       jdouble type) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetDoubleField(object.get_jobject(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

void Env::set_field(Object &object, const char *field_name, const char *signature,
                    const Object &value) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        m_jenv->SetObjectField(object.get_jobject(), field_id, value.get_jobject());
        check_for_exception();
    }
}

template<>
void Env::set_field(Object &object, const char *field_name, const char *signature,
                    jboolean value) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        m_jenv->SetBooleanField(object.get_jobject(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_field(Object &object, const char *field_name, const char *signature,
                    jbyte value) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        m_jenv->SetByteField(object.get_jobject(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_field(Object &object, const char *field_name, const char *signature,
                    jchar value) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        m_jenv->SetCharField(object.get_jobject(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_field(Object &object, const char *field_name, const char *signature,
                    jshort value) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        m_jenv->SetShortField(object.get_jobject(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_field(Object &object, const char *field_name, const char *signature,
                    jint value) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        m_jenv->SetIntField(object.get_jobject(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_field(Object &object, const char *field_name, const char *signature,
                    jlong value) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        m_jenv->SetLongField(object.get_jobject(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_field(Object &object, const char *field_name, const char *signature,
                    jfloat value) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        m_jenv->SetFloatField(object.get_jobject(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_field(Object &object, const char *field_name, const char *signature,
                    jdouble value) {
    jfieldID field_id = find_field_id(object.get_class(), field_name, signature);
    if (field_id) {
        m_jenv->SetDoubleField(object.get_jobject(), field_id, value);
        check_for_exception();
    }
}


jfieldID Env::find_static_field_id(Class &_class, const char *name, const char *signature) {
    jfieldID ret = m_jenv->GetStaticFieldID(_class.get_jclass(), name, signature);
    check_for_exception();
    return ret;
}

Object Env::get_static_field(Class &_class, const char *field_name, const char *signature) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetStaticObjectField(_class.get_jclass(), field_id);
        check_for_exception();
        return wrap(ret);
    } else {
        return Object();
    }
}

template<>
jboolean Env::get_static_field(Class &_class, const char *field_name, const char *signature,
                               jboolean type) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetStaticBooleanField(_class.get_jclass(), field_id);
        check_for_exception();
        return ret;
    } else {
        return false;
    }
}

template<>
jbyte Env::get_static_field(Class &_class, const char *field_name, const char *signature,
                            jbyte type) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetStaticByteField(_class.get_jclass(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jchar Env::get_static_field(Class &_class, const char *field_name, const char *signature,
                            jchar type) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetStaticCharField(_class.get_jclass(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jshort Env::get_static_field(Class &_class, const char *field_name, const char *signature,
                             jshort type) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetStaticShortField(_class.get_jclass(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jint Env::get_static_field(Class &_class, const char *field_name, const char *signature,
                           jint type) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetStaticIntField(_class.get_jclass(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jlong Env::get_static_field(Class &_class, const char *field_name, const char *signature,
                            jlong type) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetStaticLongField(_class.get_jclass(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jfloat Env::get_static_field(Class &_class, const char *field_name, const char *signature,
                             jfloat type) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetStaticFloatField(_class.get_jclass(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

template<>
jdouble Env::get_static_field(Class &_class, const char *field_name, const char *signature,
                              jdouble type) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        auto ret = m_jenv->GetStaticDoubleField(_class.get_jclass(), field_id);
        check_for_exception();
        return ret;
    } else {
        return 0;
    }
}

void Env::set_static_field(Class &_class, const char *field_name, const char *signature,
                           const Object &value) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        m_jenv->SetStaticObjectField(_class.get_jclass(), field_id, value.get_jobject());
        check_for_exception();
    }
}

template<>
void Env::set_static_field(Class &_class, const char *field_name, const char *signature,
                           jboolean value) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        m_jenv->SetStaticBooleanField(_class.get_jclass(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_static_field(Class &_class, const char *field_name, const char *signature,
                           jbyte value) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        m_jenv->SetStaticByteField(_class.get_jclass(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_static_field(Class &_class, const char *field_name, const char *signature,
                           jchar value) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        m_jenv->SetStaticCharField(_class.get_jclass(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_static_field(Class &_class, const char *field_name, const char *signature,
                           jshort value) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        m_jenv->SetStaticShortField(_class.get_jclass(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_static_field(Class &_class, const char *field_name, const char *signature,
                           jint value) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        m_jenv->SetStaticIntField(_class.get_jclass(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_static_field(Class &_class, const char *field_name, const char *signature,
                           jlong value) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        m_jenv->SetStaticLongField(_class.get_jclass(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_static_field(Class &_class, const char *field_name, const char *signature,
                           jfloat value) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        m_jenv->SetStaticFloatField(_class.get_jclass(), field_id, value);
        check_for_exception();
    }
}

template<>
void Env::set_static_field(Class &_class, const char *field_name, const char *signature,
                           jdouble value) {
    jfieldID field_id = find_static_field_id(_class, field_name, signature);
    if (field_id) {
        m_jenv->SetStaticDoubleField(_class.get_jclass(), field_id, value);
        check_for_exception();
    }
}
