#include "Class.h"

#include <algorithm>
#include <functional>

using namespace jpp;

Class::Class(JNIEnv *env, const char *class_name) : m_env(env), m_class_name(class_name) {
    jclass _class = m_env->FindClass(m_class_name.c_str());
    if (_class != nullptr) {
        m_jclass = (jclass) m_env->NewGlobalRef(_class);
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
    Object object_instance(&object_class, object);

    // Retrieving class object
    Object class_object = object_instance.call_object("getClass", class_class);
    // Retrieving class name
    auto class_name = resolve_class_name(env, class_object);

    return Class(env, (jclass) class_object.get_jobject(), class_name.c_str());
}

std::string Class::resolve_class_name(JNIEnv *env, Object& class_object) {
    // TODO: handle arrays
    Class string_class(env, "java/lang/String");
    Object class_name_object = class_object.call_object("getName", string_class);

    std::string class_name = class_name_object.to_string();
    std::replace(class_name.begin(), class_name.end(), '.', '/');
    return class_name;
}


template<class Ret>
static inline Ret run_jni(Class *self, const char *method_name, const char *signature,
                          std::function<Ret(jmethodID)> jni_call) {
    Ret ret;
    auto env = self->get_env();
    jmethodID method_id = env->GetStaticMethodID(self->get_jclass(), method_name, signature);
    if (method_id) {
        ret = jni_call(method_id);
    }
    return ret;
};

template<>
static inline void run_jni(Class *self, const char *method_name, const char *signature,
                           std::function<void(jmethodID)> jni_call) {
    auto env = self->get_env();
    jmethodID method_id = env->GetStaticMethodID(self->get_jclass(), method_name, signature);
    if (method_id) {
        jni_call(method_id);
    }
};

Object Class::vrun(Class &return_type, const char *method_name, const char *signature, va_list vl) {
    auto ret = run_jni<jobject>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallStaticObjectMethodV(m_jclass, method_id, vl);
    });
    return Object(&return_type, ret);
}

void Class::vrun(const char *method_name, const char *signature, va_list vl) {
    run_jni<void>(this, method_name, signature, [&](jmethodID method_id) {
        get_env()->CallStaticVoidMethodV(m_jclass, method_id, vl);
    });
}

template<>
jboolean Class::vrun(jboolean, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jboolean>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallStaticBooleanMethodV(m_jclass, method_id, vl);
    });
}

template<>
jbyte Class::vrun(jbyte, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jbyte>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallStaticByteMethodV(m_jclass, method_id, vl);
    });
}

template<>
jchar Class::vrun(jchar, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jchar>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallStaticCharMethodV(m_jclass, method_id, vl);
    });
}

template<>
jshort Class::vrun(jshort, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jshort>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallStaticShortMethodV(m_jclass, method_id, vl);
    });
}

template<>
jint Class::vrun(jint, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jint>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallStaticIntMethodV(m_jclass, method_id, vl);
    });
}

template<>
jlong Class::vrun(jlong, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jlong>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallStaticLongMethodV(m_jclass, method_id, vl);
    });
}

template<>
jfloat Class::vrun(jfloat, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jfloat>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallStaticFloatMethodV(m_jclass, method_id, vl);
    });
}

template<>
jdouble Class::vrun(jdouble, const char *method_name, const char *signature, va_list vl) {
    return run_jni<jdouble>(this, method_name, signature, [&](jmethodID method_id) {
        return get_env()->CallStaticDoubleMethodV(m_jclass, method_id, vl);
    });
}
