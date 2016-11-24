#include "Array.h"
#include "Class.h"

using namespace jpp;

AbstractArray::AbstractArray(Class *_class) : Object(_class) {

}

AbstractArray::AbstractArray(Class *_class, jarray array) : Object(_class, (jobject) array) {

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
        return get_env()->GetArrayLength(get_jarray());
    } else {
        return 0;
    }
}

template<>
Object Array<Object>::get(size_t index) {
    // TODO: THIS IS BAD, INTRODUCE CLASS CACHE ASAP (via JniEnv)
    // Keep item class in Array
    auto item = get_env()->GetObjectArrayElement((jobjectArray) get_jarray(), index);
    auto item_class = Class::resolve_class(get_env(), item);
    return Object(&item_class, item);
}

template<>
void Array<Object>::set(size_t index, Object &item) {
    get_env()->SetObjectArrayElement((jobjectArray) get_jarray(), index, item.get_jobject());
}

template<>
jbyte Array<jbyte>::get(size_t index) {
    jbyte ret;
    get_env()->GetByteArrayRegion((jbyteArray) get_jarray(), index, 1, &ret);
    return ret;
}

template<>
void Array<jbyte>::set(size_t index, jbyte &item) {
    get_env()->SetByteArrayRegion((jbyteArray) get_jarray(), index, 1, &item);
}
