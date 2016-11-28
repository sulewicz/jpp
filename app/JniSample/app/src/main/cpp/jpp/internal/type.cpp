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

char internal::type_to_str(jboolean &) {
    return 'Z';
}

char internal::type_to_str(jbyte &) {
    return 'B';
}

char internal::type_to_str(jchar &) {
    return 'C';
}

char internal::type_to_str(jshort &) {
    return 'S';
}

char internal::type_to_str(jint &) {
    return 'I';
}

char internal::type_to_str(jlong &) {
    return 'J';
}

char internal::type_to_str(jfloat &) {
    return 'F';
}

char internal::type_to_str(jdouble &) {
    return 'D';
}

char internal::type_to_str(void *) {
    return 'V';
}

std::string internal::type_to_str(jstring &) {
    return "Ljava/lang/String;";
}

std::string internal::type_to_str(Object &object) {
    return type_to_str(object.get_class());
}

std::string internal::type_to_str(AbstractArray &array) {
    return type_to_str(array.get_class());
}

std::string internal::type_to_str(Class &_class) {
    return _class.get_signature_name();
}
