#pragma once

#include <jni.h>
#include "Object.h"

namespace jpp {
    class Class;

    class AbstractArray : public Object {
    public:
        AbstractArray(Class *_class);
        AbstractArray(Class *_class, jarray array);
        AbstractArray(const AbstractArray &other);
        ~AbstractArray();

        jarray get_jarray() const;
        size_t get_length() const;
    };

    template<class Type>
    class Array : public AbstractArray {
    public:
        Array(Class *_class) : AbstractArray(_class) {}
        Array(Class *_class, jarray array) : AbstractArray(_class, array) {}
        Array(const Array &other) : AbstractArray(other) {}
        ~Array() {}

        Type get(size_t index);
        void set(size_t index, Type& item);
    };
}
