#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callMultiParamMethodNative(JNIEnv *env,
                                                                                    jclass type,
                                                                                    jobject o,
                                                                                    jboolean boolean,
                                                                                    jbyte b,
                                                                                    jchar c,
                                                                                    jshort s,
                                                                                    jint i, jlong l,
                                                                                    jfloat f,
                                                                                    jdouble d,
                                                                                    jstring str) {
    jpp::Class class_object(env, type);
    jpp::Class object_class(env, "java/lang/Object");
    jpp::Class string_class(env, "java/lang/String");
    class_object.call_void("multiParamMethod", jpp::Object(&object_class, o), boolean, b, c,
                           s, i, l, f, d, jpp::Object(&string_class, str));
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callObjectMethodNative(JNIEnv *env,
                                                                                jclass type) {
    jpp::Class return_class(env, "java/lang/Object");
    jpp::Class class_object(env, type);
    auto ret = class_object.call_object("objectMethod", return_class);
    return env->NewLocalRef(ret.get_jobject());
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callVoidMethodNative(JNIEnv *env,
                                                                              jclass type) {

    jpp::Class class_object(env, type);
    class_object.call_void("voidMethod");
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callBooleanMethodNative(JNIEnv *env,
                                                                                 jclass type) {
    jpp::Class class_object(env, type);
    return class_object.call<jboolean>("booleanMethod");
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callByteMethodNative(JNIEnv *env,
                                                                              jclass type) {
    jpp::Class class_object(env, type);
    return class_object.call<jbyte>("byteMethod");
}

extern "C"
JNIEXPORT jchar JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callCharMethodNative(JNIEnv *env,
                                                                              jclass type) {
    jpp::Class class_object(env, type);
    return class_object.call<jchar>("charMethod");
}

extern "C"
JNIEXPORT jshort JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callShortMethodNative(JNIEnv *env,
                                                                               jclass type) {
    jpp::Class class_object(env, type);
    return class_object.call<jshort>("shortMethod");
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callIntMethodNative(JNIEnv *env,
                                                                             jclass type) {
    jpp::Class class_object(env, type);
    return class_object.call<jint>("intMethod");
}

extern "C"
JNIEXPORT jlong JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callLongMethodNative(JNIEnv *env,
                                                                              jclass type) {
    jpp::Class class_object(env, type);
    return class_object.call<jlong>("longMethod");
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callFloatMethodNative(JNIEnv *env,
                                                                               jclass type) {
    jpp::Class class_object(env, type);
    return class_object.call<jfloat>("floatMethod");
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_org_coderoller_jnisample_testers_StaticMethodTester_callDoubleMethodNative(JNIEnv *env,
                                                                                jclass type) {
    jpp::Class class_object(env, type);
    return class_object.call<jdouble>("doubleMethod");
}
