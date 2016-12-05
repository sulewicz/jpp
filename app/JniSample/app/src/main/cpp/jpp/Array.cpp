#include "Array.h"
#include "Env.h"

using namespace jpp;

AbstractArray::AbstractArray(Class &_class) : Object(_class) {

}

AbstractArray::AbstractArray(Class &_class, jarray array) : Object(_class, (jobject) array) {

}

AbstractArray::AbstractArray(const AbstractArray &other) : Object(other) {

}

AbstractArray::~AbstractArray() {

}

jarray AbstractArray::get_jarray() const {
    return (jarray) get_jobject();
}

size_t AbstractArray::get_length() const {
    if (is_valid()) {
        return get_env()->get_jenv()->GetArrayLength(get_jarray());
    } else {
        return 0;
    }
}

template<>
Object Array<Object>::get(size_t index) {
    auto item = get_env()->get_jenv()->GetObjectArrayElement((jobjectArray) get_jarray(), index);
    get_env()->check_for_exception();
    auto item_object = get_env()->wrap(item);
    return item_object;
}

template<>
void Array<Object>::set(size_t index, Object &item) {
    get_env()->get_jenv()->SetObjectArrayElement((jobjectArray) get_jarray(), index,
                                                 item.get_jobject());
    get_env()->check_for_exception();
}

template<>
jboolean Array<jboolean>::get(size_t index) {
    jboolean ret;
    get_env()->get_jenv()->GetBooleanArrayRegion((jbooleanArray) get_jarray(), index, 1, &ret);
    get_env()->check_for_exception();
    return ret;
}

template<>
void Array<jboolean>::set(size_t index, jboolean &item) {
    get_env()->get_jenv()->SetBooleanArrayRegion((jbooleanArray) get_jarray(), index, 1, &item);
    get_env()->check_for_exception();
}

template<>
jbyte Array<jbyte>::get(size_t index) {
    jbyte ret;
    get_env()->get_jenv()->GetByteArrayRegion((jbyteArray) get_jarray(), index, 1, &ret);
    get_env()->check_for_exception();
    return ret;
}

template<>
void Array<jbyte>::set(size_t index, jbyte &item) {
    get_env()->get_jenv()->SetByteArrayRegion((jbyteArray) get_jarray(), index, 1, &item);
    get_env()->check_for_exception();
}

template<>
jchar Array<jchar>::get(size_t index) {
    jchar ret;
    get_env()->get_jenv()->GetCharArrayRegion((jcharArray) get_jarray(), index, 1, &ret);
    get_env()->check_for_exception();
    return ret;
}

template<>
void Array<jchar>::set(size_t index, jchar &item) {
    get_env()->get_jenv()->SetCharArrayRegion((jcharArray) get_jarray(), index, 1, &item);
    get_env()->check_for_exception();
}

template<>
jshort Array<jshort>::get(size_t index) {
    jshort ret;
    get_env()->get_jenv()->GetShortArrayRegion((jshortArray) get_jarray(), index, 1, &ret);
    get_env()->check_for_exception();
    return ret;
}

template<>
void Array<jshort>::set(size_t index, jshort &item) {
    get_env()->get_jenv()->SetShortArrayRegion((jshortArray) get_jarray(), index, 1, &item);
    get_env()->check_for_exception();
}

template<>
jint Array<jint>::get(size_t index) {
    jint ret;
    get_env()->get_jenv()->GetIntArrayRegion((jintArray) get_jarray(), index, 1, &ret);
    get_env()->check_for_exception();
    return ret;
}

template<>
void Array<jint>::set(size_t index, jint &item) {
    get_env()->get_jenv()->SetIntArrayRegion((jintArray) get_jarray(), index, 1, &item);
    get_env()->check_for_exception();
}

template<>
jlong Array<jlong>::get(size_t index) {
    jlong ret;
    get_env()->get_jenv()->GetLongArrayRegion((jlongArray) get_jarray(), index, 1, &ret);
    get_env()->check_for_exception();
    return ret;
}

template<>
void Array<jlong>::set(size_t index, jlong &item) {
    get_env()->get_jenv()->SetLongArrayRegion((jlongArray) get_jarray(), index, 1, &item);
    get_env()->check_for_exception();
}

template<>
jfloat Array<jfloat>::get(size_t index) {
    jfloat ret;
    get_env()->get_jenv()->GetFloatArrayRegion((jfloatArray) get_jarray(), index, 1, &ret);
    get_env()->check_for_exception();
    return ret;
}

template<>
void Array<jfloat>::set(size_t index, jfloat &item) {
    get_env()->get_jenv()->SetFloatArrayRegion((jfloatArray) get_jarray(), index, 1, &item);
    get_env()->check_for_exception();
}

template<>
jdouble Array<jdouble>::get(size_t index) {
    jdouble ret;
    get_env()->get_jenv()->GetDoubleArrayRegion((jdoubleArray) get_jarray(), index, 1, &ret);
    get_env()->check_for_exception();
    return ret;
}

template<>
void Array<jdouble>::set(size_t index, jdouble &item) {
    get_env()->get_jenv()->SetDoubleArrayRegion((jdoubleArray) get_jarray(), index, 1, &item);
    get_env()->check_for_exception();
}
