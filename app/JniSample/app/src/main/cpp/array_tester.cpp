#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createObjectArrayNative(JNIEnv *env,
                                                                          jobject instance,
                                                                          jint size) {
    jpp::Env jpp_env(env);
    jpp::Class item_class = jpp_env.find_class("java/lang/Object");
    auto array_object = jpp_env.create_array(size, item_class);
    return (jobjectArray) env->NewLocalRef(array_object.get_jarray());
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getObjectLengthNative(
        JNIEnv *env, jobject instance, jobjectArray array) {
    jpp::Env jpp_env(env);
    jpp::Array<jpp::Object> array_object = jpp_env.wrap(array);
    return array_object.get_length();
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getObjectItemNative(
        JNIEnv *env, jobject instance, jobjectArray array, jint idx) {
    jpp::Env jpp_env(env);
    jpp::Array<jpp::Object> array_object = jpp_env.wrap(array);
    return env->NewLocalRef(array_object.get(idx).get_jobject());
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setObjectItemNative(
        JNIEnv *env, jobject instance, jobjectArray array, jint idx, jobject newItem) {
    env->SetObjectArrayElement(array, idx, newItem);
    jpp::Env jpp_env(env);
    jpp::Array<jpp::Object> array_object = jpp_env.wrap(array);

    jpp::Object item_object = jpp_env.wrap(newItem);
    array_object.set(idx, item_object);
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createByteArrayNative(JNIEnv *env,
                                                                        jobject instance,
                                                                        jint size) {
    jpp::Env jpp_env(env);
    auto array_object = jpp_env.create_array<jbyte>(size);
    return (jbyteArray) env->NewLocalRef(array_object.get_jarray());
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getByteLengthNative(JNIEnv *env,
                                                                      jobject instance,
                                                                      jbyteArray array) {
    jpp::Env jpp_env(env);
    jpp::Array<jbyte> array_object = jpp_env.wrap(array);
    return array_object.get_length();
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getByteItemNative(JNIEnv *env,
                                                                    jobject instance,
                                                                    jbyteArray array,
                                                                    jint idx) {
    jpp::Env jpp_env(env);
    jpp::Array<jbyte> array_object = jpp_env.wrap(array);
    return array_object.get(idx);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setByteItemNative(JNIEnv *env,
                                                                    jobject instance,
                                                                    jbyteArray array,
                                                                    jint idx,
                                                                    jbyte newItem) {
    jpp::Env jpp_env(env);
    jpp::Array<jbyte> array_object = jpp_env.wrap(array);
    array_object.set(idx, newItem);
}
