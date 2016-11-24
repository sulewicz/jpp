#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_ClassTester_createObjectNative(JNIEnv *env,
                                                                     jobject instance) {

    jpp::Class integer_class(env, "java/lang/Integer");
    auto ret = integer_class.create(3);
    return env->NewLocalRef(ret.get_jobject());
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_ClassTester_createSimpleClassNative(JNIEnv *env,
                                                                          jobject instance,
                                                                          jobject o,
                                                                          jboolean boolean,
                                                                          jbyte b,
                                                                          jchar c, jshort s,
                                                                          jint i, jlong l,
                                                                          jfloat f, jdouble d,
                                                                          jstring str) {
    jpp::Class simple_class_class(env, "org/coderoller/jnisample/testers/ClassTester$SimpleClass");
    jpp::Class object_class(env, "java/lang/Object");
    jpp::Class string_class(env, "java/lang/String");
    auto ret = simple_class_class.create(jpp::Object(&object_class, o),
                                         boolean, b, c,
                                         s, i, l, f, d, jpp::Object(&string_class, str));
    return env->NewLocalRef(ret.get_jobject());
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_ClassTester_getSuperclassNative(JNIEnv *env, jobject instance,
                                                                      jobject _class) {

    jpp::Class passed_class(env, (jclass) _class);
    auto ret = passed_class.get_super_class();
    if (ret.is_valid()) {
        return env->NewLocalRef(ret.get_jclass());
    } else {
        return nullptr;
    }
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_ClassTester_checkAssignabilityNative(JNIEnv *env,
                                                                           jobject instance,
                                                                           jobject from,
                                                                           jobject to) {

    jpp::Class from_class(env, (jclass) from);
    jpp::Class to_class(env, (jclass) to);
    return to_class.is_assignable_from(from_class);
}
