#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_ObjectTester_checkEquality(JNIEnv *env, jobject instance,
                                                                 jobject first, jobject second) {

    jpp::Env jpp_env(env);
    auto first_object = jpp_env.wrap(first);
    auto second_object = jpp_env.wrap(second);
    return first_object == second_object;
}