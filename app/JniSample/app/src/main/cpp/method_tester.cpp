#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callMultiParamMethodNative(JNIEnv *env,
                                                                              jobject obj,
                                                                              jobject o,
                                                                              jboolean boolean,
                                                                              jbyte b, jchar c,
                                                                              jshort s, jint i,
                                                                              jlong l, jfloat f,
                                                                              jdouble d) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    method_tester_object.call_void("multiParamMethod", jpp_env.wrap("java/lang/Object", o), boolean,
                                   b, c,
                                   s, i, l, f, d);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callObjectMethodNative(JNIEnv *env,
                                                                          jobject obj) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    jpp::Class return_class = jpp_env.find_class("java/lang/Object");
    auto ret = method_tester_object.call_object("objectMethod", return_class);
    return env->NewLocalRef(ret.get_jobject());
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callVoidMethodNative(JNIEnv *env,
                                                                        jobject obj) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    method_tester_object.call_void("voidMethod");
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callBooleanMethodNative(JNIEnv *env,
                                                                           jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jboolean>("booleanMethod");
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callByteMethodNative(JNIEnv *env,
                                                                        jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jbyte>("byteMethod");
}

extern "C"
JNIEXPORT jchar JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callCharMethodNative(JNIEnv *env,
                                                                        jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jchar>("charMethod");
}

extern "C"
JNIEXPORT jshort JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callShortMethodNative(JNIEnv *env,
                                                                         jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jshort>("shortMethod");
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callIntMethodNative(JNIEnv *env,
                                                                       jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jint>("intMethod");
}

extern "C"
JNIEXPORT jlong JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callLongMethodNative(JNIEnv *env,
                                                                        jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jlong>("longMethod");
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callFloatMethodNative(JNIEnv *env,
                                                                         jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jfloat>("floatMethod");
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callDoubleMethodNative(JNIEnv *env,
                                                                          jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jdouble>("doubleMethod");
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callGetClassNative(JNIEnv *env,
                                                                      jobject obj) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return env->NewLocalRef(method_tester_object.get_jclass());
}
