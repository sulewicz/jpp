#include "GlobalRef.h"
#include "Class.h"
#include "Env.h"

using namespace jpp;

GlobalRef::GlobalRef() {
}

GlobalRef::GlobalRef(const GlobalRef &other) {
    if (other.is_valid()) {
        m_jenv = other.m_jenv;
        m_jobject = m_jenv->NewGlobalRef(other.m_jobject);
    }
}

GlobalRef::~GlobalRef() {
    if (is_valid()) {
        m_jenv->DeleteGlobalRef(m_jobject);
        m_jobject = nullptr;
        m_jenv = nullptr;
    }
}

bool GlobalRef::is_valid() const {
    return m_jenv != nullptr && m_jobject != nullptr;
}

void GlobalRef::wrap(const Object& object) {
    if (object.is_valid()) {
        release(*object.get_env());
        m_jenv = object.get_env()->get_jenv();
        m_jobject = m_jenv->NewGlobalRef(object.get_jobject());
    }
}

Object GlobalRef::unwrap(Env& env) {
    if (is_valid() && env.is_valid()) {
        return env.wrap(m_jobject);
    } else {
        return Object();
    }
}

void GlobalRef::release(Env& env) {
    if (env.is_valid() && is_valid()) {
        env.get_jenv()->DeleteGlobalRef(m_jobject);
        m_jobject = nullptr;
        m_jenv = nullptr;
    }
}

void GlobalRef::set_env(Env& env) {
    if (env.is_valid()) {
        m_jenv = env.get_jenv();
    }
}
