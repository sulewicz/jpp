#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_ClassTester_createObject(JNIEnv *env,
                                                                     jobject instance) {
    jpp::Env jpp_env(env);
    auto integer_class = jpp_env.find_class("java/lang/Integer");
    auto ret = integer_class.create(3);
    return env->NewLocalRef(ret.get_jobject());
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_ClassTester_createSimpleClass(JNIEnv *env,
                                                                          jobject instance,
                                                                          jobject o,
                                                                          jboolean boolean,
                                                                          jbyte b,
                                                                          jchar c, jshort s,
                                                                          jint i, jlong l,
                                                                          jfloat f, jdouble d,
                                                                          jstring str) {
    jpp::Env jpp_env(env);
    auto simple_class_class = jpp_env.find_class("org/coderoller/jnisample/testers/ClassTester$SimpleClass");
    auto ret = simple_class_class.create(jpp_env.wrap("java/lang/Object", o),
                                         boolean, b, c,
                                         s, i, l, f, d, jpp_env.wrap(str));
    return env->NewLocalRef(ret.get_jobject());
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_ClassTester_getSuperclass(JNIEnv *env, jobject instance,
                                                                      jobject _class) {
    jpp::Env jpp_env(env);
    auto passed_class = jpp_env.wrap((jclass) _class);
    auto ret = passed_class.get_super_class();
    if (ret.is_valid()) {
        return env->NewLocalRef(ret.get_jclass());
    } else {
        return nullptr;
    }
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_ClassTester_checkAssignability(JNIEnv *env,
                                                                           jobject instance,
                                                                           jobject from,
                                                                           jobject to) {
    jpp::Env jpp_env(env);
    auto from_class = jpp_env.wrap((jclass) from);
    auto to_class = jpp_env.wrap((jclass) to);
    return to_class.is_assignable_from(from_class);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_ClassTester_checkEquality(JNIEnv *env, jobject instance,
                                                                jobject first, jobject second) {
    jpp::Env jpp_env(env);
    auto first_class = jpp_env.wrap((jclass) first);
    auto second_class = jpp_env.wrap((jclass) second);
    return first_class == second_class;
}
