#pragma once

#include <jni.h>
#include "JUtils.h"
#include "JObject.h"

class JClass {
public:
    JClass(JNIEnv *env, const char *class_name);
    JClass(const JClass& other);
    ~JClass();

    bool is_valid() const;
    const char *get_class_name() const;
    JNIEnv *get_env() const;
    jclass get_jclass() const;

    template<class ... Types>
    JObject construct(Types ... args) {
        auto signature = JUtils::generate_void_signature(args...);
        return do_construct(signature.c_str(), args...);
    }

private:
    JObject do_construct(const char *signature, ...);

    JNIEnv * const m_env;
    jclass m_jclass = nullptr;
    const char *m_class_name;
};
