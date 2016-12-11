#include "Class.h"
#include "Env.h"
#include "Object.h"
#include "Array.h"

#define VA_START va_list vl;\
    va_start(vl, signature);

#define VA_END va_end(vl);

using namespace jpp;

Class::Class(Env *env) : m_env(env) {
}

Class::Class(Env *env, jclass _class, const char *class_name) : m_env(env) {
    if (_class != nullptr) {
        m_jclass = _class;
        m_class_name = class_name;
    }
}

Class::Class(const Class &other) : m_env(other.m_env), m_jclass(other.m_jclass),
                                   m_class_name(other.m_class_name) {
}

Class::~Class() {
}

Class &Class::operator=(const Class &other) {
    m_env = other.m_env;
    m_jclass = other.m_jclass;
    m_class_name = other.m_class_name;
    return *this;
}

bool Class::operator==(const Class &other) {
    return get_env()->get_jenv()->IsSameObject(m_jclass, other.m_jclass);
}

bool Class::operator!=(const Class &other) {
    return !(*this == other);
}

Class::operator jobject() const {
    return create_local_ref();
}

jobject Class::create_local_ref() const {
    if (is_valid()) {
        return m_env->get_jenv()->NewLocalRef(m_jclass);
    } else {
        return nullptr;
    }
}

bool Class::is_valid() const {
    return m_jclass != nullptr;
}

const char *Class::get_class_name() const {
    return m_class_name;
}

std::string Class::get_signature_name() const {
    if (is_array_class()) {
        return get_class_name();
    } else {
        return std::string("L") + get_class_name() + ';';
    }
}

Env *Class::get_env() const {
    return m_env;
}

jclass Class::get_jclass() const {
    return m_jclass;
}

Class Class::get_super_class() {
    return m_env->get_superclass(*this);
}

bool Class::is_assignable_from(Class &from_class) const {
    if (is_valid() && from_class.is_valid()) {
        return m_env->get_jenv()->IsAssignableFrom(from_class.get_jclass(), m_jclass);
    }
    return false;
}

bool Class::is_object_class() const {
    return m_jclass != nullptr && m_class_name[0] != '[';
}

bool Class::is_array_class() const {
    return m_jclass != nullptr && m_class_name[0] == '[';
}

Object Class::do_create(const char *signature,
                        ...) {

    if (is_object_class()) {
        VA_START
        auto ret = get_env()->call_constructor(*this, signature, vl);
        VA_END
        return ret;
    } else {
        return get_env()->wrap(*this, nullptr);
    }
}

Object Class::do_call(const char *method_name, const char *signature,
                      ...) {
    VA_START
    auto ret = get_env()->call_static_method(*this, method_name, signature, vl);
    VA_END
    return ret;
}

void Class::do_call(void *type, const char *method_name, const char *signature, ...) {
    VA_START
    get_env()->call_static_method(*this, method_name, signature, vl, (void *) 0);
    VA_END
}

template<>
jboolean Class::do_call(jboolean, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_static_method<jboolean>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jbyte Class::do_call(jbyte, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_static_method<jbyte>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jchar Class::do_call(jchar, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_static_method<jchar>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jshort Class::do_call(jshort, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_static_method<jshort>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jint Class::do_call(jint, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_static_method<jint>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jlong Class::do_call(jlong, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_static_method<jlong>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jfloat Class::do_call(jfloat, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_static_method<jfloat>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jdouble Class::do_call(jdouble, const char *method_name, const char *signature, ...) {
    VA_START;
    auto ret = get_env()->call_static_method<jdouble>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

Object Class::do_get(const char *field_name, const char *signature) {
    auto ret = get_env()->get_static_field(*this, field_name, signature);
    return ret;
}

template<>
jboolean Class::do_get(jboolean type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_static_field<jboolean>(*this, field_name, signature);
    return ret;
}

template<>
jbyte Class::do_get(jbyte type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_static_field<jbyte>(*this, field_name, signature);
    return ret;
}

template<>
jchar Class::do_get(jchar type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_static_field<jchar>(*this, field_name, signature);
    return ret;
}

template<>
jshort Class::do_get(jshort type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_static_field<jshort>(*this, field_name, signature);
    return ret;
}

template<>
jint Class::do_get(jint type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_static_field<jint>(*this, field_name, signature);
    return ret;
}

template<>
jlong Class::do_get(jlong type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_static_field<jlong>(*this, field_name, signature);
    return ret;
}

template<>
jfloat Class::do_get(jfloat type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_static_field<jfloat>(*this, field_name, signature);
    return ret;
}

template<>
jdouble Class::do_get(jdouble type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_static_field<jdouble>(*this, field_name, signature);
    return ret;
}

void Class::do_set(const char *field_name, const char *signature, const Object& value) {
    get_env()->set_static_field(*this, field_name, signature, value);
}

template<>
void Class::do_set(const char *field_name, const char *signature, const jboolean& value) {
    get_env()->set_static_field<jboolean>(*this, field_name, signature, value);
}

template<>
void Class::do_set(const char *field_name, const char *signature, const jbyte& value) {
    get_env()->set_static_field<jbyte>(*this, field_name, signature, value);
}

template<>
void Class::do_set(const char *field_name, const char *signature, const jchar& value) {
    get_env()->set_static_field<jchar>(*this, field_name, signature, value);
}

template<>
void Class::do_set(const char *field_name, const char *signature, const jshort& value) {
    get_env()->set_static_field<jshort>(*this, field_name, signature, value);
}

template<>
void Class::do_set(const char *field_name, const char *signature, const jint& value) {
    get_env()->set_static_field<jint>(*this, field_name, signature, value);
}

template<>
void Class::do_set(const char *field_name, const char *signature, const jlong& value) {
    get_env()->set_static_field<jlong>(*this, field_name, signature, value);
}

template<>
void Class::do_set(const char *field_name, const char *signature, const jfloat& value) {
    get_env()->set_static_field<jfloat>(*this, field_name, signature, value);
}

template<>
void Class::do_set(const char *field_name, const char *signature, const jdouble& value) {
    get_env()->set_static_field<jdouble>(*this, field_name, signature, value);
}
