#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callMultiParamMethod(JNIEnv *env,
                                                                                    jclass type,
                                                                                    jobject o,
                                                                                    jboolean boolean,
                                                                                    jbyte b,
                                                                                    jchar c,
                                                                                    jshort s,
                                                                                    jint i, jlong l,
                                                                                    jfloat f,
                                                                                    jdouble d) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    class_object.call_void("multiParamMethod", jpp_env.wrap("java/lang/Object", o), boolean, b, c,
                           s, i, l, f, d);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callObjectMethod(JNIEnv *env,
                                                                                jclass type) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    jpp::Class return_class = jpp_env.find_class("java/lang/Object");
    auto ret = class_object.call_object("objectMethod", return_class);
    return env->NewLocalRef(ret.get_jobject());
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callVoidMethodNative(JNIEnv *env,
                                                                              jclass type) {

    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    class_object.call_void("voidMethod");
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callBooleanMethod(JNIEnv *env,
                                                                                 jclass type) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    return class_object.call<jboolean>("booleanMethod");
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callByteMethod(JNIEnv *env,
                                                                              jclass type) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    return class_object.call<jbyte>("byteMethod");
}

extern "C"
JNIEXPORT jchar JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callCharMethod(JNIEnv *env,
                                                                              jclass type) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    return class_object.call<jchar>("charMethod");
}

extern "C"
JNIEXPORT jshort JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callShortMethod(JNIEnv *env,
                                                                               jclass type) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    return class_object.call<jshort>("shortMethod");
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callIntMethod(JNIEnv *env,
                                                                             jclass type) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    return class_object.call<jint>("intMethod");
}

extern "C"
JNIEXPORT jlong JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callLongMethod(JNIEnv *env,
                                                                              jclass type) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    return class_object.call<jlong>("longMethod");
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callFloatMethod(JNIEnv *env,
                                                                               jclass type) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    return class_object.call<jfloat>("floatMethod");
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callDoubleMethod(JNIEnv *env,
                                                                                jclass type) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    return class_object.call<jdouble>("doubleMethod");
}
