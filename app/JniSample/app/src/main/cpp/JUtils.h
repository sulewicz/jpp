#pragma once

#include <jni.h>
#include <string>
#include <sstream>

class JObject;
class JClass;

namespace JUtils {
    char to_type(jboolean);

    char to_type(jbyte);

    char to_type(jchar);

    char to_type(jshort);

    char to_type(jint);

    char to_type(jlong);

    char to_type(jfloat);

    char to_type(jdouble);

    std::string to_type(jstring);

    std::string to_type(const JObject &);

    std::string to_type(const JClass &);

    // TODO: array

    template<class ... Types>
    std::string generate_signature(Types ... args) {
        std::ostringstream stream;
        stream << "(";
        using List= int[];
        (void) List{0, ((void) (stream << to_type(args)), 0) ...};
        stream << ")V";
        return stream.str();
    }

    template<class ... Types>
    std::string generate_signature(JClass *return_type, Types ... args) {
        std::ostringstream stream;
        stream << "(";
        using List= int[];
        (void) List{0, ((void) (stream << to_type(args)), 0) ...};
        stream << ")L" << to_type(*return_type) << ';';
        return stream.str();
    }
};
