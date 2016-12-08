#include "type.h"
#include "../Class.h"
#include "../Object.h"
#include "../Array.h"

using namespace jpp;

jboolean internal::flatten(jboolean &arg) {
    return arg;
}

jbyte internal::flatten(jbyte &arg) {
    return arg;
}

jchar internal::flatten(jchar &arg) {
    return arg;
}

jshort internal::flatten(jshort &arg) {
    return arg;
}

jint internal::flatten(jint &arg) {
    return arg;
}

jlong internal::flatten(jlong &arg) {
    return arg;
}

jfloat internal::flatten(jfloat &arg) {
    return arg;
}

jdouble internal::flatten(jdouble &arg) {
    return arg;
}

jstring internal::flatten(jstring &arg) {
    return arg;
}

jobject internal::flatten(Object &arg) {
    return arg.get_jobject();
}

jarray internal::flatten(AbstractArray &arg) {
    return arg.get_jarray();
}

jclass internal::flatten(Class &arg) {
    return arg.get_jclass();
}

const char *internal::type_to_str(const jboolean &) {
    return "Z";
}

const char *internal::type_to_str(const jbyte &) {
    return "B";
}

const char *internal::type_to_str(const jchar &) {
    return "C";
}

const char *internal::type_to_str(const jshort &) {
    return "S";
}

const char *internal::type_to_str(const jint &) {
    return "I";
}

const char *internal::type_to_str(const jlong &) {
    return "J";
}

const char *internal::type_to_str(const jfloat &) {
    return "F";
}

const char *internal::type_to_str(const jdouble &) {
    return "D";
}

const char *internal::type_to_str(const void *) {
    return "V";
}

std::string internal::type_to_str(const jstring &) {
    return "Ljava/lang/String;";
}

std::string internal::type_to_str(const Object &object) {
    return type_to_str(object.get_class());
}

std::string internal::type_to_str(const AbstractArray &array) {
    return type_to_str(array.get_class());
}

std::string internal::type_to_str(const Class &_class) {
    return _class.get_signature_name();
}
