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

Cache& Env::get_cache() {
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

Object Env::wrap(Class& _class, jobject _jobject) {
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
