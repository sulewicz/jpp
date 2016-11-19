#pragma once

#include <jni.h>
#include <string>
#include <sstream>

namespace jpp {
    class Object;
    class Class;

    namespace utils {
        jboolean flatten(jboolean &);
        jbyte flatten(jbyte &);
        jchar flatten(jchar &);
        jshort flatten(jshort &);
        jint flatten(jint &);
        jlong flatten(jlong &);
        jfloat flatten(jfloat &);
        jdouble flatten(jdouble &);
        jstring flatten(jstring &);
        jobject flatten(Object &);
        jclass flatten(Class &);

        char to_type(jboolean &);
        char to_type(jbyte &);
        char to_type(jchar &);
        char to_type(jshort &);
        char to_type(jint &);
        char to_type(jlong &);
        char to_type(jfloat &);
        char to_type(jdouble &);
        std::string to_type(jstring &);
        std::string to_type(Object &);
        std::string to_type(Class &);

        // TODO: array

        template<class ... Types>
        std::string generate_void_signature(Types ... args) {
            std::ostringstream stream;
            stream << "(";
            using List= int[];
            (void) List{0, ((void) (stream << to_type(args)), 0) ...};
            stream << ")V";
            return stream.str();
        }

        template<class Type, class ... Types>
        std::string generate_signature(Type return_type, Types ... args) {
            std::ostringstream stream;
            stream << "(";
            using List= int[];
            (void) List{0, ((void) (stream << to_type(args)), 0) ...};
            stream << ")" << to_type(return_type);
            return stream.str();
        }
    }
}
