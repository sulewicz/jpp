#include "Object.h"
#include "Class.h"
#include <functional>

using namespace jpp;

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

template<class Ret>
static inline Ret run_jni(Object *self, const char *method_name, const char *signature,
                          std::function<Ret(jmethodID)> jni_call) {
    Ret ret;
    auto env = self->get_env();
    jmethodID method_id = env->GetMethodID(self->get_jclass(), method_name, signature);
    if (method_id) {
        ret = jni_call(method_id);
    }
    return ret;
};

template<>
static inline void run_jni(Object *self, const char *method_name, const char *signature,
                           std::function<void(jmethodID)> jni_call) {
    auto env = self->get_env();
    jmethodID method_id = env->GetMethodID(self->get_jclass(), method_name, signature);
    if (method_id) {
        jni_call(method_id);
    }
};

Object Object::vrun(Class &return_type, const char *method_name, const char *signature, va_list vl) {
    auto jni_call = [&](jmethodID method_id) {
        return get_env()->CallObjectMethodV(m_jobject, method_id, vl);
    };
    auto ret = run_jni<jobject>(this, method_name, signature, jni_call);
    return Object(m_class, ret);
}

void Object::vrun(const char *method_name, const char *signature, va_list vl) {
    auto jni_call = [&](jmethodID method_id) {
        get_env()->CallVoidMethodV(m_jobject, method_id, vl);
    };
    run_jni<void>(this, method_name, signature, jni_call);
}

template<>
jboolean Object::vrun(jboolean, const char *method_name, const char *signature, va_list vl) {
    auto jni_call = [&](jmethodID method_id) {
        return get_env()->CallBooleanMethodV(m_jobject, method_id, vl);
    };
    return run_jni<jboolean>(this, method_name, signature, jni_call);
}

template<>
jbyte Object::vrun(jbyte, const char *method_name, const char *signature, va_list vl) {
    auto jni_call = [&](jmethodID method_id) {
        return get_env()->CallByteMethodV(m_jobject, method_id, vl);
    };
    return run_jni<jbyte>(this, method_name, signature, jni_call);
}

template<>
jchar Object::vrun(jchar, const char *method_name, const char *signature, va_list vl) {
    auto jni_call = [&](jmethodID method_id) {
        return get_env()->CallCharMethodV(m_jobject, method_id, vl);
    };
    return run_jni<jchar>(this, method_name, signature, jni_call);
}
