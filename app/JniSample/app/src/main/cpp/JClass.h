#pragma once

#include <jni.h>
#include "JUtils.h"

class JClass {
public:
    JClass(JNIEnv *env, const char *className);
    JClass(const JClass& other);
    ~JClass();

    template<class ... Types>
    jobject construct(Types ... args) {
        jobject result = nullptr;
        auto signature = JUtils::generate_signature(args...);
        jmethodID methodId = m_env->GetMethodID(m_class,  "<init>", signature.c_str());
        if (methodId) {
            result = m_env->NewObject(m_class, methodId, args...);
        }
        return result;
    }

    bool is_valid() const;

private:
    JNIEnv * const m_env;
    jclass m_class = nullptr;
    const char *m_className;
};
