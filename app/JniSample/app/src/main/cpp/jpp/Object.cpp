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
    auto ret = run_jni<jobject>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallObjectMethodV(m_jobject, method_id, vl);
    });
    return Object(&return_type, ret);
}

void Object::vrun(const char *method_name, const char *signature, va_list vl) {
    run_jni<void>(this, method_name, signature, [&](jmethodID method_id) {
        get_env()->CallVoidMethodV(m_jobject, method_id, vl);
    });
}

template<>
jboolean Object::vrun(jboolean, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jboolean>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallBooleanMethodV(m_jobject, method_id, vl);
    });
}

template<>
jbyte Object::vrun(jbyte, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jbyte>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallByteMethodV(m_jobject, method_id, vl);
    });
}

template<>
jchar Object::vrun(jchar, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jchar>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallCharMethodV(m_jobject, method_id, vl);
    });
}

template<>
jshort Object::vrun(jshort, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jshort>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallShortMethodV(m_jobject, method_id, vl);
    });
}

template<>
jint Object::vrun(jint, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jint>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallIntMethodV(m_jobject, method_id, vl);
    });
}

template<>
jlong Object::vrun(jlong, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jlong>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallLongMethodV(m_jobject, method_id, vl);
    });
}

template<>
jfloat Object::vrun(jfloat, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jfloat>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallFloatMethodV(m_jobject, method_id, vl);
    });
}

template<>
jdouble Object::vrun(jdouble, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jdouble>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallDoubleMethodV(m_jobject, method_id, vl);
    });
}
