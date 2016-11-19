#include <jni.h>
#include <string>

#include "jpp/jpp.h"

extern "C"
jstring
Java_org_coderoller_jnisample_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    jpp::Class listClass(env, "java/util/ArrayList");
    auto listObject = listClass.construct();

    jpp::Class integerClass(env, "java/lang/Integer");
    auto integerObject = integerClass.construct(3);

    jpp::Class stringClass(env, "java/lang/String");
    auto str = integerObject.object("toString", stringClass);

    /*auto result = listObject.boolean("add", integerObject);
    auto size = listObject.call<jint>("size");
    auto isEmpty = listObject.call<jboolean>("isEmpty");

    auto integerObject = JClass(env, "java.lang.Integer").construct(JInt(3));
    auto success = listObject.call<jboolean>("add", integerObject);*/

    jstring ret = (jstring) env->NewLocalRef(str.get_jobject());
    return ret;
}
