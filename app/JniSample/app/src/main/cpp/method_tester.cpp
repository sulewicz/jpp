#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callMultiParamMethod(JNIEnv *env,
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
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callMultiParamArrayMethod(JNIEnv *env,
                                                                             jobject obj,
                                                                             jobjectArray o,
                                                                             jbooleanArray boolean,
                                                                             jbyteArray b,
                                                                             jcharArray c,
                                                                             jshortArray s,
                                                                             jintArray i,
                                                                             jlongArray l,
                                                                             jfloatArray f,
                                                                             jdoubleArray d) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    auto object_array = jpp_env.wrap(o);
    auto boolean_array = jpp_env.wrap(boolean);
    auto byte_array = jpp_env.wrap(b);
    auto char_array = jpp_env.wrap(c);
    auto short_array = jpp_env.wrap(s);
    auto int_array = jpp_env.wrap(i);
    auto long_array = jpp_env.wrap(l);
    auto float_array = jpp_env.wrap(f);
    auto double_array = jpp_env.wrap(d);
    method_tester_object.call_void("multiParamArrayMethod", object_array, boolean_array, byte_array,
                                   char_array, short_array, int_array, long_array, float_array,
                                   double_array);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callObjectMethod(JNIEnv *env,
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
Java_org_coderoller_jnisample_testers_MethodTester_callBooleanMethod(JNIEnv *env,
                                                                     jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jboolean>("booleanMethod");
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callByteMethod(JNIEnv *env,
                                                                  jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jbyte>("byteMethod");
}

extern "C"
JNIEXPORT jchar JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callCharMethod(JNIEnv *env,
                                                                  jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jchar>("charMethod");
}

extern "C"
JNIEXPORT jshort JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callShortMethod(JNIEnv *env,
                                                                   jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jshort>("shortMethod");
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callIntMethod(JNIEnv *env,
                                                                 jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jint>("intMethod");
}

extern "C"
JNIEXPORT jlong JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callLongMethod(JNIEnv *env,
                                                                  jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jlong>("longMethod");
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callFloatMethod(JNIEnv *env,
                                                                   jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jfloat>("floatMethod");
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callDoubleMethod(JNIEnv *env,
                                                                    jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jdouble>("doubleMethod");
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callObjectArrayMethod(JNIEnv *env,
                                                                         jobject obj) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    jpp::Class return_class = jpp_env.find_array_class("java/lang/Object");
    auto ret = (jpp::Array<jpp::Object>) method_tester_object.call_object("objectArrayMethod",
                                                                          return_class);
    if (ret.get_length() > 0) {
        return (jobjectArray) env->NewLocalRef(ret.get_jarray());
    } else {
        return nullptr;
    }
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callByteArrayMethod(JNIEnv *env,
                                                                       jobject obj) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    jpp::Class return_class = jpp_env.find_array_class<jbyte>();
    auto ret = (jpp::Array<jbyte>) method_tester_object.call_object("byteArrayMethod",
                                                                    return_class);
    if (ret.get_length() > 0) {
        return (jbyteArray) env->NewLocalRef(ret.get_jarray());
    } else {
        return nullptr;
    }
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callGetClass(JNIEnv *env,
                                                                jobject obj) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return env->NewLocalRef(method_tester_object.get_jclass());
}
