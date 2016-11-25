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
    auto item_object = get_env()->wrap(item);
    return item_object;
}

template<>
void Array<Object>::set(size_t index, Object &item) {
    get_env()->get_jenv()->SetObjectArrayElement((jobjectArray) get_jarray(), index,
                                                 item.get_jobject());
}

template<>
jbyte Array<jbyte>::get(size_t index) {
    jbyte ret;
    get_env()->get_jenv()->GetByteArrayRegion((jbyteArray) get_jarray(), index, 1, &ret);
    return ret;
}

template<>
void Array<jbyte>::set(size_t index, jbyte &item) {
    get_env()->get_jenv()->SetByteArrayRegion((jbyteArray) get_jarray(), index, 1, &item);
}
