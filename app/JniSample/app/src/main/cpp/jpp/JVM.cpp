#include "JVM.h"
#include "Env.h"

using namespace jpp;

JVM::JVM() : m_jvm(nullptr) {
}

JVM::JVM(JavaVM *jvm) : m_jvm(jvm) {
}

JVM::~JVM() {
}

bool JVM::is_valid() {
    return m_jvm != nullptr;
}

Env JVM::get_env(jint version) {
    JNIEnv *jenv = nullptr;
    m_jvm->GetEnv((void **) &jenv, version);
    return Env(jenv);
}

Env JVM::attach_current_thread() {
    JNIEnv *jenv = nullptr;
    m_jvm->AttachCurrentThread(&jenv, nullptr);
    return Env(jenv);
}

bool JVM::detach_current_thread() {
    return m_jvm->DetachCurrentThread() == 0;
}
