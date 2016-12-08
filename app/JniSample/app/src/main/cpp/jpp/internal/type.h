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

        const char *type_to_str(const jboolean &);
        const char *type_to_str(const jbyte &);
        const char *type_to_str(const jchar &);
        const char *type_to_str(const jshort &);
        const char *type_to_str(const jint &);
        const char *type_to_str(const jlong &);
        const char *type_to_str(const jfloat &);
        const char *type_to_str(const jdouble &);
        const char *type_to_str(const void *);
        std::string type_to_str(const jstring &);
        std::string type_to_str(const Object &);
        std::string type_to_str(const AbstractArray &);
        std::string type_to_str(const Class &);
    }
}