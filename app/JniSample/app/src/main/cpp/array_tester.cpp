#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createObjectArrayNative(JNIEnv *env,
                                                                          jobject instance,
                                                                          jint size) {
    jpp::Class array_class(env, "[Ljava/lang/Object;");
    auto array_object = array_class.create_array<jpp::Object>(size);
    return (jobjectArray) env->NewLocalRef(array_object.get_jarray());
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getObjectLengthNative(
        JNIEnv *env, jobject instance, jobjectArray array) {
    jpp::Class array_class = jpp::Class::resolve_class(env, array);
    jpp::Array<jpp::Object> array_object(&array_class, array);
    return array_object.get_length();
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getObjectItemNative(
        JNIEnv *env, jobject instance, jobjectArray array, jint idx) {
    jpp::Class array_class = jpp::Class::resolve_class(env, array);
    jpp::Array<jpp::Object> array_object(&array_class, array);
    return env->NewLocalRef(array_object.get(idx).get_jobject());
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setObjectItemNative(
        JNIEnv *env, jobject instance, jobjectArray array, jint idx, jobject newItem) {
    env->SetObjectArrayElement(array, idx, newItem);
    jpp::Class array_class = jpp::Class::resolve_class(env, array);
    jpp::Array<jpp::Object> array_object(&array_class, array);

    jpp::Class item_class = jpp::Class::resolve_class(env, newItem);
    jpp::Object item_object(&item_class, newItem);
    array_object.set(idx, item_object);
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createByteArrayNative(JNIEnv *env,
                                                                        jobject instance,
                                                                        jint size) {
    jpp::Class array_class(env, "[B");
    auto array_object = array_class.create_array<jbyte>(size);
    return (jbyteArray) env->NewLocalRef(array_object.get_jarray());
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getByteLengthNative(JNIEnv *env,
                                                                      jobject instance,
                                                                      jbyteArray array) {
    jpp::Class array_class = jpp::Class::resolve_class(env, array);
    jpp::Array<jbyte> array_object(&array_class, array);
    return array_object.get_length();
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getByteItemNative(JNIEnv *env,
                                                                    jobject instance,
                                                                    jbyteArray array,
                                                                    jint idx) {
    jpp::Class array_class = jpp::Class::resolve_class(env, array);
    jpp::Array<jbyte> array_object(&array_class, array);
    return array_object.get(idx);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setByteItemNative(JNIEnv *env,
                                                                    jobject instance,
                                                                    jbyteArray array,
                                                                    jint idx,
                                                                    jbyte newItem) {
    jpp::Class array_class = jpp::Class::resolve_class(env, array);
    jpp::Array<jbyte> array_object(&array_class, array);
    array_object.set(idx, newItem);
}
