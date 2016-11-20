#include <jni.h>
#include "jpp/jpp.h"

extern "C"
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_CreationTester_createObjectNative(JNIEnv *env,
                                                                        jobject instance) {

    jpp::Class integerClass(env, "java/lang/Integer");
    auto integerObject = integerClass.construct(3);
    return env->NewLocalRef(integerObject.get_jobject());
}
