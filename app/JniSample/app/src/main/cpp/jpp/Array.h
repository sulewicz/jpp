#pragma once

#include <jni.h>
#include "Object.h"

namespace jpp {
    class Class;
    class Env;

    class AbstractArray : public Object {
    public:
        AbstractArray(const AbstractArray &other);
        ~AbstractArray();

        jarray get_jarray() const;
        size_t get_length() const;

    protected:
        AbstractArray(Class &_class);
        AbstractArray(Class &_class, jarray array);
    };

    template<class Type>
    class Array : public AbstractArray {
    public:
        Array(const Array &other) : AbstractArray(other) { }

        Array(const Object &other) : AbstractArray(other.get_class(),
                                                   (jarray) other.get_jobject()) { }

        ~Array() { }

        Type get(size_t index);
        void set(size_t index, Type &item);

    protected:
        Array(Class &_class) : AbstractArray(_class) { }

        Array(Class &_class, jarray array) : AbstractArray(_class, array) { }

        friend class Env;
        friend class Class;
    };
}
