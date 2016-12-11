#include <jni.h>
#include "jpp/jpp.h"

template<typename ArrayType, typename ItemType>
ArrayType create_array(JNIEnv *env, size_t size) {
    jpp::Env jpp_env(env);
    auto array_object = jpp_env.create_array<ItemType>(size);
    return (ArrayType) array_object.create_local_ref();
}

template<typename ArrayType>
size_t get_length(JNIEnv *env, ArrayType array) {
    jpp::Env jpp_env(env);
    auto array_object = jpp_env.wrap(array);
    return array_object.get_length();
}

template<typename ArrayType, typename ItemType>
ItemType get_item(JNIEnv *env, ArrayType array, size_t idx) {
    jpp::Env jpp_env(env);
    auto array_object = jpp_env.wrap(array);
    return array_object.get(idx);
}

template<typename ArrayType, typename ItemType>
void set_item(JNIEnv *env, ArrayType array, size_t idx, ItemType newItem) {
    jpp::Env jpp_env(env);
    auto array_object = jpp_env.wrap(array);
    array_object.set(idx, newItem);
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createObjectArray(JNIEnv *env,
                                                                    jobject instance,
                                                                    jint size) {
    jpp::Env jpp_env(env);
    jpp::Class item_class = jpp_env.find_class("java/lang/Object");
    auto array_object = jpp_env.create_array(size, item_class);
    return (jobjectArray) array_object.create_local_ref();
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getObjectLength(
        JNIEnv *env, jobject instance, jobjectArray array) {
    return get_length(env, array);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getObjectItem(
        JNIEnv *env, jobject instance, jobjectArray array, jint idx) {
    jpp::Env jpp_env(env);
    jpp::Array<jpp::Object> array_object = jpp_env.wrap(array);
    return (jobject) array_object.get(idx);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setObjectItem(
        JNIEnv *env, jobject instance, jobjectArray array, jint idx, jobject newItem) {
    env->SetObjectArrayElement(array, idx, newItem);
    jpp::Env jpp_env(env);
    jpp::Array<jpp::Object> array_object = jpp_env.wrap(array);

    jpp::Object item_object = jpp_env.wrap(newItem);
    array_object.set(idx, item_object);
}

extern "C"
JNIEXPORT jbooleanArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createBooleanArray(JNIEnv *env,
                                                                     jobject instance,
                                                                     jint size) {
    return create_array<jbooleanArray, jboolean>(env, size);
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getBooleanLength(JNIEnv *env,
                                                                   jobject instance,
                                                                   jbooleanArray array) {
    return get_length(env, array);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getBooleanItem(JNIEnv *env,
                                                                 jobject instance,
                                                                 jbooleanArray array,
                                                                 jint idx) {
    return get_item<jbooleanArray, jboolean>(env, array, idx);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setBooleanItem(JNIEnv *env,
                                                                 jobject instance,
                                                                 jbooleanArray array,
                                                                 jint idx,
                                                                 jboolean newItem) {
    set_item(env, array, idx, newItem);
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createByteArray(JNIEnv *env,
                                                                  jobject instance,
                                                                  jint size) {
    return create_array<jbyteArray, jbyte>(env, size);
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getByteLength(JNIEnv *env,
                                                                jobject instance,
                                                                jbyteArray array) {
    return get_length(env, array);
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getByteItem(JNIEnv *env,
                                                              jobject instance,
                                                              jbyteArray array,
                                                              jint idx) {
    return get_item<jbyteArray, jbyte>(env, array, idx);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setByteItem(JNIEnv *env,
                                                              jobject instance,
                                                              jbyteArray array,
                                                              jint idx,
                                                              jbyte newItem) {
    set_item(env, array, idx, newItem);
}

extern "C"
JNIEXPORT jcharArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createCharArray(JNIEnv *env,
                                                                  jobject instance,
                                                                  jint size) {
    return create_array<jcharArray, jchar>(env, size);
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getCharLength(JNIEnv *env,
                                                                jobject instance,
                                                                jcharArray array) {
    return get_length(env, array);
}

extern "C"
JNIEXPORT jchar JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getCharItem(JNIEnv *env,
                                                              jobject instance,
                                                              jcharArray array,
                                                              jint idx) {
    return get_item<jcharArray, jchar>(env, array, idx);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setCharItem(JNIEnv *env,
                                                              jobject instance,
                                                              jcharArray array,
                                                              jint idx,
                                                              jchar newItem) {
    set_item(env, array, idx, newItem);
}

extern "C"
JNIEXPORT jshortArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createShortArray(JNIEnv *env,
                                                                   jobject instance,
                                                                   jint size) {
    return create_array<jshortArray, jshort>(env, size);
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getShortLength(JNIEnv *env,
                                                                 jobject instance,
                                                                 jshortArray array) {
    return get_length(env, array);
}

extern "C"
JNIEXPORT jshort JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getShortItem(JNIEnv *env,
                                                               jobject instance,
                                                               jshortArray array,
                                                               jint idx) {
    return get_item<jshortArray, jshort>(env, array, idx);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setShortItem(JNIEnv *env,
                                                               jobject instance,
                                                               jshortArray array,
                                                               jint idx,
                                                               jshort newItem) {
    set_item(env, array, idx, newItem);
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createIntArray(JNIEnv *env,
                                                                 jobject instance,
                                                                 jint size) {
    return create_array<jintArray, jint>(env, size);
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getIntLength(JNIEnv *env,
                                                               jobject instance,
                                                               jintArray array) {
    return get_length(env, array);
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getIntItem(JNIEnv *env,
                                                             jobject instance,
                                                             jintArray array,
                                                             jint idx) {
    return get_item<jintArray, jint>(env, array, idx);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setIntItem(JNIEnv *env,
                                                             jobject instance,
                                                             jintArray array,
                                                             jint idx,
                                                             jint newItem) {
    set_item(env, array, idx, newItem);
}

extern "C"
JNIEXPORT jlongArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createLongArray(JNIEnv *env,
                                                                  jobject instance,
                                                                  jint size) {
    return create_array<jlongArray, jlong>(env, size);
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getLongLength(JNIEnv *env,
                                                                jobject instance,
                                                                jlongArray array) {
    return get_length(env, array);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getLongItem(JNIEnv *env,
                                                              jobject instance,
                                                              jlongArray array,
                                                              jint idx) {
    return get_item<jlongArray, jlong>(env, array, idx);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setLongItem(JNIEnv *env,
                                                              jobject instance,
                                                              jlongArray array,
                                                              jint idx,
                                                              jlong newItem) {
    set_item(env, array, idx, newItem);
}

extern "C"
JNIEXPORT jfloatArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createFloatArray(JNIEnv *env,
                                                                   jobject instance,
                                                                   jint size) {
    return create_array<jfloatArray, jfloat>(env, size);
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getFloatLength(JNIEnv *env,
                                                                 jobject instance,
                                                                 jfloatArray array) {
    return get_length(env, array);
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getFloatItem(JNIEnv *env,
                                                               jobject instance,
                                                               jfloatArray array,
                                                               jint idx) {
    return get_item<jfloatArray, jfloat>(env, array, idx);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setFloatItem(JNIEnv *env,
                                                               jobject instance,
                                                               jfloatArray array,
                                                               jint idx,
                                                               jfloat newItem) {
    set_item(env, array, idx, newItem);
}

extern "C"
JNIEXPORT jdoubleArray JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_createDoubleArray(JNIEnv *env,
                                                                    jobject instance,
                                                                    jint size) {
    return create_array<jdoubleArray, jdouble>(env, size);
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getDoubleLength(JNIEnv *env,
                                                                  jobject instance,
                                                                  jdoubleArray array) {
    return get_length(env, array);
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_getDoubleItem(JNIEnv *env,
                                                                jobject instance,
                                                                jdoubleArray array,
                                                                jint idx) {
    return get_item<jdoubleArray, jdouble>(env, array, idx);
}

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_ArrayTester_setDoubleItem(JNIEnv *env,
                                                                jobject instance,
                                                                jdoubleArray array,
                                                                jint idx,
                                                                jdouble newItem) {
    set_item(env, array, idx, newItem);
}
