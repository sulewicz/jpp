#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ExceptionTester_simulateClassNotFoundException(JNIEnv *env,
                                                                                     jobject obj) {
    jpp::Env jpp_env(env);
    auto exception_tester_object = jpp_env.wrap(obj);
#if JPP_EXCEPTIONS_SUPPORTED
    try {
        jpp::Class invalid_class = jpp_env.find_class("not/existing/class");
    } catch (jpp::Object exception_object) {
        auto throwable_object = exception_object.cast_to(jpp_env.find_class("java/lang/Throwable"));
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#else
    jpp::Class invalid_class = jpp_env.find_class("not/existing/class");
    if (jpp_env.is_exception_pending()) {
        auto throwable_object = jpp_env.consume_exception().cast_to("java/lang/Throwable");
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#endif
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ExceptionTester_simulateNoSuchMethodError(JNIEnv *env,
                                                                                    jobject obj) {
    jpp::Env jpp_env(env);
    auto exception_tester_object = jpp_env.wrap(obj);
#if JPP_EXCEPTIONS_SUPPORTED
    try {
        exception_tester_object.call_void("noSuchMethod");
    } catch (jpp::Object exception_object) {
        auto throwable_object = exception_object.cast_to(jpp_env.find_class("java/lang/Throwable"));
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#else
    exception_tester_object.call_void("noSuchMethod");
    if (jpp_env.is_exception_pending()) {
        auto throwable_object = jpp_env.consume_exception().cast_to("java/lang/Throwable");
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#endif
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ExceptionTester_simulateNoSuchStaticMethodError(
        JNIEnv *env, jobject obj) {

    jpp::Env jpp_env(env);
    auto exception_tester_object = jpp_env.wrap(obj);
    auto& exception_tester_class = exception_tester_object.get_class();
#if JPP_EXCEPTIONS_SUPPORTED
    try {
        exception_tester_class.call_void("noSuchStaticMethod");
    } catch (jpp::Object exception_object) {
        auto throwable_object = exception_object.cast_to(jpp_env.find_class("java/lang/Throwable"));
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#else
    exception_tester_class.call_void("noSuchStaticMethod");
    if (jpp_env.is_exception_pending()) {
        auto throwable_object = jpp_env.consume_exception().cast_to("java/lang/Throwable");
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#endif
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ExceptionTester_simulateUnsupportedOperationException(
        JNIEnv *env, jobject obj) {
    jpp::Env jpp_env(env);
    auto exception_tester_object = jpp_env.wrap(obj);
#if JPP_EXCEPTIONS_SUPPORTED
    try {
        exception_tester_object.call_void("notImplemented");
    } catch (jpp::Object exception_object) {
        auto throwable_object = exception_object.cast_to(jpp_env.find_class("java/lang/Throwable"));
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#else
    exception_tester_object.call_void("notImplemented");
    if (jpp_env.is_exception_pending()) {
        auto throwable_object = jpp_env.consume_exception().cast_to("java/lang/Throwable");
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#endif
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ExceptionTester_simulateStaticUnsupportedOperationException(
        JNIEnv *env, jobject obj) {
    jpp::Env jpp_env(env);
    auto exception_tester_object = jpp_env.wrap(obj);
    auto& exception_tester_class = exception_tester_object.get_class();
#if JPP_EXCEPTIONS_SUPPORTED
    try {
        exception_tester_class.call_void("staticNotImplemented");
    } catch (jpp::Object exception_object) {
        auto throwable_object = exception_object.cast_to(jpp_env.find_class("java/lang/Throwable"));
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#else
    exception_tester_class.call_void("staticNotImplemented");
    if (jpp_env.is_exception_pending()) {
        auto throwable_object = jpp_env.consume_exception().cast_to("java/lang/Throwable");
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#endif
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ExceptionTester_throwException(JNIEnv *env, jobject obj,
                                                                     jobject aClass) {
    jpp::Env jpp_env(env);
    auto class_object = jpp_env.wrap((jclass) aClass);
    auto exception_object = class_object.create();
    jpp_env.throw_exception(exception_object);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ExceptionTester_simulateConstructorException(JNIEnv *env,
                                                                                   jobject obj,
                                                                                   jthrowable e) {
    jpp::Env jpp_env(env);
    auto exception_tester_object = jpp_env.wrap(obj);
    auto& exception_tester_class = exception_tester_object.get_class();
    auto runtime_exception_object = jpp_env.wrap(e);
#if JPP_EXCEPTIONS_SUPPORTED
    try {
        exception_tester_class.create(runtime_exception_object);
    } catch (jpp::Object exception_object) {
        auto throwable_object = exception_object.cast_to(jpp_env.find_class("java/lang/Throwable"));
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#else
    exception_tester_class.create(runtime_exception_object);
    if (jpp_env.is_exception_pending()) {
        auto throwable_object = jpp_env.consume_exception().cast_to("java/lang/Throwable");
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#endif
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ExceptionTester_simulateNoSuchConstructorException(
        JNIEnv *env, jobject obj) {
    jpp::Env jpp_env(env);
    auto exception_tester_object = jpp_env.wrap(obj);
    auto& exception_tester_class = exception_tester_object.get_class();
#if JPP_EXCEPTIONS_SUPPORTED
    try {
        exception_tester_class.create((jint) 10, (jbyte) 3);
    } catch (jpp::Object exception_object) {
        auto throwable_object = exception_object.cast_to(jpp_env.find_class("java/lang/Throwable"));
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#else
    exception_tester_class.create((jint) 10, (jbyte) 3);
    if (jpp_env.is_exception_pending()) {
        auto throwable_object = jpp_env.consume_exception().cast_to("java/lang/Throwable");
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#endif
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_ExceptionTester_safeGetItem(JNIEnv *env, jobject obj,
                                                                    jobjectArray array, jint idx) {
    jpp::Env jpp_env(env);
    auto exception_tester_object = jpp_env.wrap(obj);
    auto array_object = jpp_env.wrap(array);
#if JPP_EXCEPTIONS_SUPPORTED
    try {
        auto ret = array_object.get(idx);
        return env->NewLocalRef(ret.get_jobject());
    } catch (jpp::Object exception_object) {
        auto throwable_object = exception_object.cast_to(jpp_env.find_class("java/lang/Throwable"));
        exception_tester_object.call_void("setThrowable", throwable_object);
        return nullptr;
    }
#else
    auto ret = array_object.get(idx);
    if (jpp_env.is_exception_pending()) {
        auto throwable_object = jpp_env.consume_exception().cast_to("java/lang/Throwable");
        exception_tester_object.call_void("setThrowable", throwable_object);
        return nullptr;
    } else {
        return env->NewLocalRef(ret.get_jobject());
    }
#endif
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ExceptionTester_safeSetItem(JNIEnv *env, jobject obj,
                                                                  jobjectArray array, jint idx,
                                                                  jobject item) {
    jpp::Env jpp_env(env);
    auto exception_tester_object = jpp_env.wrap(obj);
    auto array_object = jpp_env.wrap(array);
    auto item_object = jpp_env.wrap(item);
#if JPP_EXCEPTIONS_SUPPORTED
    try {
        array_object.set(idx, item_object);
    } catch (jpp::Object exception_object) {
        auto throwable_object = exception_object.cast_to(jpp_env.find_class("java/lang/Throwable"));
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#else
    array_object.set(idx, item_object);
    if (jpp_env.is_exception_pending()) {
        auto throwable_object = jpp_env.consume_exception().cast_to("java/lang/Throwable");
        exception_tester_object.call_void("setThrowable", throwable_object);
    }
#endif
}

