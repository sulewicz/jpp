#include "type.h"
#include "../Class.h"

jboolean jpp::type::flatten(jboolean &arg) {
    return arg;
}

jbyte jpp::type::flatten(jbyte &arg) {
    return arg;
}

jchar jpp::type::flatten(jchar &arg) {
    return arg;
}

jshort jpp::type::flatten(jshort &arg) {
    return arg;
}

jint jpp::type::flatten(jint &arg) {
    return arg;
}

jlong jpp::type::flatten(jlong &arg) {
    return arg;
}

jfloat jpp::type::flatten(jfloat &arg) {
    return arg;
}

jdouble jpp::type::flatten(jdouble &arg) {
    return arg;
}

jstring jpp::type::flatten(jstring &arg) {
    return arg;
}

jobject jpp::type::flatten(Object &arg) {
    return arg.get_jobject();
}

jarray jpp::type::flatten(AbstractArray &arg) {
    return arg.get_jarray();
}

jclass jpp::type::flatten(Class &arg) {
    return arg.get_jclass();
}

char jpp::type::type_to_str(jboolean &) {
    return 'Z';
}

char jpp::type::type_to_str(jbyte &) {
    return 'B';
}

char jpp::type::type_to_str(jchar &) {
    return 'C';
}

char jpp::type::type_to_str(jshort &) {
    return 'S';
}

char jpp::type::type_to_str(jint &) {
    return 'I';
}

char jpp::type::type_to_str(jlong &) {
    return 'J';
}

char jpp::type::type_to_str(jfloat &) {
    return 'F';
}

char jpp::type::type_to_str(jdouble &) {
    return 'D';
}

char jpp::type::type_to_str(void *) {
    return 'V';
}

std::string jpp::type::type_to_str(jstring &) {
    return "Ljava/lang/String;";
}

std::string jpp::type::type_to_str(Object &object) {
    return type_to_str(*object.get_class());
}

std::string jpp::type::type_to_str(AbstractArray &array) {
    return type_to_str(*array.get_class());
}

std::string jpp::type::type_to_str(Class &_class) {
    return _class.get_signature_name();
}
