#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_CreationTester_createObjectNative(JNIEnv *env,
                                                                        jobject instance) {

    jpp::Class integer_class(env, "java/lang/Integer");
    auto integer_object = integer_class.construct(3);
    return env->NewLocalRef(integer_object.get_jobject());
}
