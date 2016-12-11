#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_StaticFieldTester_setAndGetObjectField(JNIEnv *env,
                                                                       jclass type,
                                                                       jobject o) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    jpp::Class field_class = jpp_env.find_class("java/lang/Object");
    jpp::Object value_object = jpp_env.wrap(field_class, o);
    class_object.set("sObject", value_object);
    auto ret = class_object.get("sObject", field_class);
    return (jobject) ret;
}

template<typename Ret>
static Ret access_and_modify_field(JNIEnv *env, jclass type, const char *field_name, Ret value) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    class_object.set(field_name, value);
    auto ret = class_object.get<Ret>(field_name);
    return ret;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_StaticFieldTester_setAndGetBooleanField(JNIEnv *env,
                                                                        jclass type,
                                                                        jboolean b) {
    return access_and_modify_field(env, type, "sBoolean", b);
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_org_coderoller_jnisample_testers_StaticFieldTester_setAndGetByteField(JNIEnv *env, jclass type,
                                                                     jbyte b) {
    return access_and_modify_field(env, type, "sByte", b);
}

extern "C"
JNIEXPORT jchar JNICALL
Java_org_coderoller_jnisample_testers_StaticFieldTester_setAndGetCharField(JNIEnv *env, jclass type,
                                                                     jchar c) {
    return access_and_modify_field(env, type, "sChar", c);
}

extern "C"
JNIEXPORT jshort JNICALL
Java_org_coderoller_jnisample_testers_StaticFieldTester_setAndGetShortField(JNIEnv *env, jclass type,
                                                                      jshort s) {
    return access_and_modify_field(env, type, "sShort", s);
}

extern "C"
JNIEXPORT jint JNICALL
Java_org_coderoller_jnisample_testers_StaticFieldTester_setAndGetIntField(JNIEnv *env, jclass type,
                                                                    jint i) {
    return access_and_modify_field(env, type, "sInt", i);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_org_coderoller_jnisample_testers_StaticFieldTester_setAndGetLongField(JNIEnv *env, jclass type,
                                                                     jlong l) {
    return access_and_modify_field(env, type, "sLong", l);
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_org_coderoller_jnisample_testers_StaticFieldTester_setAndGetFloatField(JNIEnv *env, jclass type,
                                                                      jfloat f) {
    return access_and_modify_field(env, type, "sFloat", f);
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_org_coderoller_jnisample_testers_StaticFieldTester_setAndGetDoubleField(JNIEnv *env,
                                                                       jclass type,
                                                                       jdouble d) {
    return access_and_modify_field(env, type, "sDouble", d);
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_org_coderoller_jnisample_testers_StaticFieldTester_setAndGetObjectArrayField(JNIEnv *env,
                                                                            jclass type,
                                                                            jobjectArray o) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    jpp::Class field_class = jpp_env.find_array_class("java/lang/Object");
    jpp::Object value_object = jpp_env.wrap(field_class, o);
    class_object.set("sObjectArray", value_object);
    auto ret = (jpp::Array<jpp::Object>) class_object.get("sObjectArray", field_class);
    return (jobjectArray) ret.create_local_ref();
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_org_coderoller_jnisample_testers_StaticFieldTester_setAndGetByteArrayField(JNIEnv *env,
                                                                          jclass type,
                                                                          jbyteArray b) {
    jpp::Env jpp_env(env);
    jpp::Class class_object = jpp_env.wrap(type);
    jpp::Class field_class = jpp_env.find_array_class<jbyte>();
    jpp::Object value_object = jpp_env.wrap(field_class, b);
    class_object.set("sByteArray", value_object);
    auto ret = (jpp::Array<jbyte>) class_object.get("sByteArray", field_class);
    return (jbyteArray) ret.create_local_ref();
}
