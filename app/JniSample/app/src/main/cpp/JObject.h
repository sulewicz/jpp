#pragma once

#include <jni.h>

class JClass;

class JObject {
public:
    JObject(JClass *_class, jobject object);
    JObject(const JObject& other);
    ~JObject();

    bool is_valid() const;

    JClass *get_class() const;

/*    template<class ... Types>
    JObject call(const char* method_name, JClass *return_type, Types ... args) {
        jobject result = nullptr;
        auto signature = JUtils::generate_signature(return_type, args...);
        jmethodID method_id = m_class->get_env()->GetMethodID(m_class->get_jclass(), method_name, signature.c_str());
        if (method_id) {
            result = m_class->get_env()->CallObjectMethod(m_object, method_id, args...);
        }
        return JObject(m_class, result);
    }*/

private:
    JClass * const m_class;
    jobject m_object = nullptr;
};
