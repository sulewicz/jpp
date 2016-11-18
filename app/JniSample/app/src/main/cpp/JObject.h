#pragma once

#include <jni.h>
#include "JUtils.h"

class JClass;

class JObject {
public:
    JObject(JClass *_class, jobject object);
    JObject(const JObject& other);
    ~JObject();

    bool is_valid() const;

    JClass *get_class() const;
    JNIEnv *get_env() const;
    jclass get_jclass() const;
    jobject get_jobject() const;

    jobject get_local_ref() const;

    template<class ... Types>
    JObject object(const char* method_name, JClass& return_type, Types ... args) {
        auto signature = JUtils::generate_signature(return_type, args...);
        return do_object(method_name, return_type, signature.c_str(), JUtils::flatten(args)...);
    }

    template<class ... Types>
    jboolean boolean(const char* method_name, Types ... args) {
        auto signature = JUtils::generate_signature(jboolean(), args...);
        return do_boolean(method_name, signature.c_str(), JUtils::flatten(args)...);
    }

private:
    JObject do_object(const char* method_name, JClass& return_type, const char *signature, ...);
    jboolean do_boolean(const char* method_name, const char *signature, ...);

    JClass * const m_class;
    jobject m_object = nullptr;
};
