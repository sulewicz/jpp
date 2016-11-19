#include "utils.h"
#include "../Class.h"

using namespace jpp;

jboolean utils::flatten(jboolean &arg) {
    return arg;
}

jbyte utils::flatten(jbyte &arg) {
    return arg;
}

jchar utils::flatten(jchar &arg) {
    return arg;
}

jshort utils::flatten(jshort &arg) {
    return arg;
}

jint utils::flatten(jint &arg) {
    return arg;
}

jlong utils::flatten(jlong &arg) {
    return arg;
}

jfloat utils::flatten(jfloat &arg) {
    return arg;
}

jdouble utils::flatten(jdouble &arg) {
    return arg;
}

jstring utils::flatten(jstring &arg) {
    return arg;
}

jobject utils::flatten(Object &arg) {
    return arg.get_jobject();
}

jclass utils::flatten(Class &arg) {
    return arg.get_jclass();
}

char utils::to_type(jboolean &) {
    return 'Z';
}

char utils::to_type(jbyte &) {
    return 'B';
}

char utils::to_type(jchar &) {
    return 'C';
}

char utils::to_type(jshort &) {
    return 'S';
}

char utils::to_type(jint &) {
    return 'I';
}

char utils::to_type(jlong &) {
    return 'J';
}

char utils::to_type(jfloat &) {
    return 'F';
}

char utils::to_type(jdouble &) {
    return 'D';
}

std::string utils::to_type(jstring &) {
    return "Ljava/lang/String;";
}

std::string utils::to_type(Object &object) {
    return to_type(*object.get_class());
}

std::string utils::to_type(Class &_class) {
    return std::string("L") + _class.get_class_name() + ';';
}
