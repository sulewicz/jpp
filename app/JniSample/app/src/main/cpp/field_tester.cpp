#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_FieldTester_setAndGetObjectField(JNIEnv *env,
                                                                       jobject obj,
                                                                       jobject o) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    jpp::Class field_class = jpp_env.find_class("java/lang/Object");
    jpp::Object value_object = jpp_env.wrap(field_class, o);
    method_tester_object.set("mObject", value_object);
    auto ret = method_tester_object.get("mObject", field_class);
    return env->NewLocalRef(ret.get_jobject());
}

template<typename Ret>
static Ret access_and_modify_field(JNIEnv *env, jobject obj, const char *field_name, Ret value) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    method_tester_object.set(field_name, value);
    auto ret = method_tester_object.get<Ret>(field_name);
    return ret;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_FieldTester_setAndGetBooleanField(JNIEnv *env,
                                                                        jobject obj,
                                                                        jboolean b) {
    return access_and_modify_field(env, obj, "mBoolean", b);
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_org_coderoller_jnisample_testers_FieldTester_setAndGetByteField(JNIEnv *env, jobject obj,
                                                                     jbyte b) {
    return access_and_modify_field(env, obj, "mByte", b);
}

extern "C"
JNIEXPORT jchar JNICALL
Java_org_coderoller_jnisample_testers_FieldTester_setAndGetCharField(JNIEnv *env, jobject obj,
                                                                     jchar c) {
    return access_and_modify_field(env, obj, "mChar", c);
}

extern "C"
JNIEXPORT jshort JNICALL
Java_org_coderoller_jnisample_testers_FieldTester_setAndGetShortField(JNIEnv *env, jobject obj,
                                                                      jshort s) {
    return access_and_modify_field(env, obj, "mShort", s);
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_FieldTester_setAndGetIntField(JNIEnv *env, jobject obj,
                                                                    jint i) {
    return access_and_modify_field(env, obj, "mInt", i);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_org_coderoller_jnisample_testers_FieldTester_setAndGetLongField(JNIEnv *env, jobject obj,
                                                                     jlong l) {
    return access_and_modify_field(env, obj, "mLong", l);
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_org_coderoller_jnisample_testers_FieldTester_setAndGetFloatField(JNIEnv *env, jobject obj,
                                                                      jfloat f) {
    return access_and_modify_field(env, obj, "mFloat", f);
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_org_coderoller_jnisample_testers_FieldTester_setAndGetDoubleField(JNIEnv *env,
                                                                       jobject obj,
                                                                       jdouble d) {
    return access_and_modify_field(env, obj, "mDouble", d);
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_org_coderoller_jnisample_testers_FieldTester_setAndGetObjectArrayField(JNIEnv *env,
                                                                            jobject obj,
                                                                            jobjectArray o) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    jpp::Class field_class = jpp_env.find_array_class("java/lang/Object");
    jpp::Object value_object = jpp_env.wrap(field_class, o);
    method_tester_object.set("mObjectArray", value_object);
    auto ret = (jpp::Array<jpp::Object>) method_tester_object.get("mObjectArray", field_class);
    return (jobjectArray) env->NewLocalRef(ret.get_jarray());
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_org_coderoller_jnisample_testers_FieldTester_setAndGetByteArrayField(JNIEnv *env,
                                                                          jobject obj,
                                                                          jbyteArray b) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    jpp::Class field_class = jpp_env.find_array_class<jbyte>();
    jpp::Object value_object = jpp_env.wrap(field_class, b);
    method_tester_object.set("mByteArray", value_object);
    auto ret = (jpp::Array<jbyte>) method_tester_object.get("mByteArray", field_class);
    return (jbyteArray) env->NewLocalRef(ret.get_jarray());
}
