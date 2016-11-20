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