#include <jni.h>
#include "jpp/jpp.h"

// TODO: add method for fetching class from object (after adding callObjectMethod) - constructor in Object.

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callObjectMethodNative(JNIEnv *env,
                                                                          jobject obj) {
    jpp::Class objectClass(env, "java/lang/Object");
    jpp::Class methodTesterClass(env, "org/coderoller/jnisample/testers/MethodTester");
    jpp::Object methodTesterObject(&methodTesterClass, obj);
    auto ret = methodTesterObject.call_object("objectMethod", objectClass);
    return env->NewLocalRef(ret.get_jobject());
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callVoidMethodNative(JNIEnv *env,
                                                                        jobject obj) {
    jpp::Class methodTesterClass(env, "org/coderoller/jnisample/testers/MethodTester");
    jpp::Object methodTesterObject(&methodTesterClass, obj);
    methodTesterObject.call_void("voidMethod");
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callBooleanMethodNative(JNIEnv *env,
                                                                           jobject obj) {

    jpp::Class methodTesterClass(env, "org/coderoller/jnisample/testers/MethodTester");
    jpp::Object methodTesterObject(&methodTesterClass, obj);
    return methodTesterObject.call<jboolean>("booleanMethod");
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callByteMethodNative(JNIEnv *env,
                                                                        jobject obj) {

    jpp::Class methodTesterClass(env, "org/coderoller/jnisample/testers/MethodTester");
    jpp::Object methodTesterObject(&methodTesterClass, obj);
    return methodTesterObject.call<jbyte>("byteMethod");
}

extern "C"
JNIEXPORT jchar JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callCharMethodNative(JNIEnv *env,
                                                                        jobject obj) {

    jpp::Class methodTesterClass(env, "org/coderoller/jnisample/testers/MethodTester");
    jpp::Object methodTesterObject(&methodTesterClass, obj);
    return methodTesterObject.call<jchar>("charMethod");
}

extern "C"
JNIEXPORT jshort JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callShortMethodNative(JNIEnv *env,
                                                                         jobject obj) {

    jpp::Class methodTesterClass(env, "org/coderoller/jnisample/testers/MethodTester");
    jpp::Object methodTesterObject(&methodTesterClass, obj);
    return methodTesterObject.call<jshort>("shortMethod");

}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callIntMethodNative(JNIEnv *env,
                                                                       jobject obj) {

    jpp::Class methodTesterClass(env, "org/coderoller/jnisample/testers/MethodTester");
    jpp::Object methodTesterObject(&methodTesterClass, obj);
    return methodTesterObject.call<jint>("intMethod");
}

extern "C"
JNIEXPORT jlong JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callLongMethodNative(JNIEnv *env,
                                                                        jobject obj) {

    jpp::Class methodTesterClass(env, "org/coderoller/jnisample/testers/MethodTester");
    jpp::Object methodTesterObject(&methodTesterClass, obj);
    return methodTesterObject.call<jlong>("longMethod");
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callFloatMethodNative(JNIEnv *env,
                                                                         jobject obj) {

    jpp::Class methodTesterClass(env, "org/coderoller/jnisample/testers/MethodTester");
    jpp::Object methodTesterObject(&methodTesterClass, obj);
    return methodTesterObject.call<jfloat>("floatMethod");
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callDoubleMethodNative(JNIEnv *env,
                                                                          jobject obj) {

    jpp::Class methodTesterClass(env, "org/coderoller/jnisample/testers/MethodTester");
    jpp::Object methodTesterObject(&methodTesterClass, obj);
    return methodTesterObject.call<jdouble>("doubleMethod");
}
