#include "JObject.h"
#include "JClass.h"

JObject::JObject(JClass *_class, jobject object) : m_class(_class) {
    if (object != nullptr) {
        m_object = m_class->get_env()->NewGlobalRef(object);
    }
}

JObject::JObject(const JObject &other) : m_class(other.m_class) {
    if (other.is_valid()) {
        m_object = m_class->get_env()->NewGlobalRef(other.m_object);
    }
}

JObject::~JObject() {
    if (is_valid()) {
        m_class->get_env()->DeleteGlobalRef(m_object);
        m_object = nullptr;
    }
}

bool JObject::is_valid() const {
    return m_object != nullptr;
}

JClass *JObject::get_class() const {
    return m_class;
}
