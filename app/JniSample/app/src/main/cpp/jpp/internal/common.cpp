#include "common.h"

jarray jpp::common::new_array(JNIEnv *env, const jclass &_class, const std::string &class_name,
                              size_t size) {
    switch (class_name[1]) {
        case 'Z':
            return env->NewBooleanArray(size);
        case 'B':
            return env->NewByteArray(size);
        case 'C':
            return env->NewCharArray(size);
        case 'S':
            return env->NewShortArray(size);
        case 'I':
            return env->NewIntArray(size);
        case 'J':
            return env->NewLongArray(size);
        case 'F':
            return env->NewFloatArray(size);
        case 'D':
            return env->NewDoubleArray(size);
        default: // Normal object
            return env->NewObjectArray(size, _class, nullptr);
    }
}
