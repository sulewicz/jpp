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

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_ObjectTester_isInstanceOf(JNIEnv *env, jobject instance,
                                                                jobject _jobject, jobject _jclass) {

    jpp::Env jpp_env(env);
    auto object = jpp_env.wrap(_jobject);
    auto _class = jpp_env.wrap((jclass) _jclass);
    return object.is_instance_of(_class);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_ObjectTester_castTo(JNIEnv *env, jobject instance,
                                                          jobject _jobject,
                                                          jobject _jclass) {

    jpp::Env jpp_env(env);
    auto object = jpp_env.wrap(_jobject);
    auto _class = jpp_env.wrap((jclass) _jclass);
    if (object.cast_to(_class)) {
        return object.get_class() == _class;
    } else {
        return false;
    }
}
