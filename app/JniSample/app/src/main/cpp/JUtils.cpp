#include "JUtils.h"

#include "JClass.h"
#include "JObject.h"

char JUtils::to_type(jboolean) {
    return 'Z';
}

char JUtils::to_type(jbyte) {
    return 'B';
}

char JUtils::to_type(jchar) {
    return 'C';
}

char JUtils::to_type(jshort) {
    return 'S';
}

char JUtils::to_type(jint) {
    return 'I';
}

char JUtils::to_type(jlong) {
    return 'J';
}

char JUtils::to_type(jfloat) {
    return 'F';
}

char JUtils::to_type(jdouble) {
    return 'D';
}

std::string JUtils::to_type(jstring) {
    return "Ljava/lang/String;";
}

std::string JUtils::to_type(const JObject &object) {
    return to_type(*object.get_class());
}

std::string JUtils::to_type(const JClass &_class) {
    return std::string("L") + _class.get_class_name() + ';';
}
