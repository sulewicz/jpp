#include "JUtils.h"

#include "JClass.h"
#include "JObject.h"

jboolean JUtils::flatten(jboolean &arg) {
    return arg;
}

jbyte JUtils::flatten(jbyte &arg) {
    return arg;
}

jchar JUtils::flatten(jchar &arg) {
    return arg;
}

jshort JUtils::flatten(jshort &arg) {
    return arg;
}

jint JUtils::flatten(jint &arg) {
    return arg;
}

jlong JUtils::flatten(jlong &arg) {
    return arg;
}

jfloat JUtils::flatten(jfloat &arg) {
    return arg;
}

jdouble JUtils::flatten(jdouble &arg) {
    return arg;
}

jstring JUtils::flatten(jstring &arg) {
    return arg;
}

jobject JUtils::flatten(JObject &arg) {
    return arg.get_jobject();
}

jclass JUtils::flatten(JClass &arg) {
    return arg.get_jclass();
}

char JUtils::to_type(jboolean &) {
    return 'Z';
}

char JUtils::to_type(jbyte &) {
    return 'B';
}

char JUtils::to_type(jchar &) {
    return 'C';
}

char JUtils::to_type(jshort &) {
    return 'S';
}

char JUtils::to_type(jint &) {
    return 'I';
}

char JUtils::to_type(jlong &) {
    return 'J';
}

char JUtils::to_type(jfloat &) {
    return 'F';
}

char JUtils::to_type(jdouble &) {
    return 'D';
}

std::string JUtils::to_type(jstring &) {
    return "Ljava/lang/String;";
}

std::string JUtils::to_type(JObject &object) {
    return to_type(*object.get_class());
}

std::string JUtils::to_type(JClass &_class) {
    return std::string("L") + _class.get_class_name() + ';';
}
