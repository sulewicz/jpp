#include <jni.h>
#include <string>

#include "JClass.h"

extern "C"
jstring
Java_org_coderoller_jnisample_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello;

    JClass listClass(env, "java/util/ArrayList");
    auto listObject = listClass.construct();

    JClass integerClass(env, "java/lang/Integer");
    auto integerObject = integerClass.construct(3);

    /*auto size = listObject.call<jint>("size");
    auto isEmpty = listObject.call<jboolean>("isEmpty");

    auto integerObject = JClass(env, "java.lang.Integer").construct(JInt(3));
    auto success = listObject.call<jboolean>("add", integerObject);*/

    return env->NewStringUTF(hello.c_str());
}
