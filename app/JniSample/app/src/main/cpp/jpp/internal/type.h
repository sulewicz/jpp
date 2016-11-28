#pragma once

#include <jni.h>
#include <string>

namespace jpp {
    class Object;
    class Class;
    class AbstractArray;
    namespace internal {
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
        jarray flatten(AbstractArray &);
        jclass flatten(Class &);

        char type_to_str(jboolean &);
        char type_to_str(jbyte &);
        char type_to_str(jchar &);
        char type_to_str(jshort &);
        char type_to_str(jint &);
        char type_to_str(jlong &);
        char type_to_str(jfloat &);
        char type_to_str(jdouble &);
        char type_to_str(void *);
        std::string type_to_str(jstring &);
        std::string type_to_str(Object &);
        std::string type_to_str(AbstractArray &);
        std::string type_to_str(Class &);
    }
}