#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_CreationTester_createObjectNative(JNIEnv *env,
                                                                        jobject instance) {

    jpp::Class integer_class(env, "java/lang/Integer");
    auto ret = integer_class.create(3);
    return env->NewLocalRef(ret.get_jobject());
}

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_CreationTester_createSimpleClassNative(JNIEnv *env,
                                                                             jobject instance,
                                                                             jobject o,
                                                                             jboolean boolean,
                                                                             jbyte b,
                                                                             jchar c, jshort s,
                                                                             jint i, jlong l,
                                                                             jfloat f, jdouble d,
                                                                             jstring str) {
    jpp::Class simple_class_class(env, "org/coderoller/jnisample/testers/CreationTester$SimpleClass");
    jpp::Class object_class(env, "java/lang/Object");
    jpp::Class string_class(env, "java/lang/String");
    auto ret = simple_class_class.create(jpp::Object(&object_class, o),
                                         boolean, b, c,
                                         s, i, l, f, d, jpp::Object(&string_class, str));
    return env->NewLocalRef(ret.get_jobject());
}
