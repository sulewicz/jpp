#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ExceptionTester_simulateClassNotFoundException(JNIEnv *env,
                                                                                     jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object exception_tester_object = jpp_env.wrap(obj);
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