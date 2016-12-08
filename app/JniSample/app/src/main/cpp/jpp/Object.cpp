#include "Object.h"
#include "Class.h"
#include "Env.h"

#define VA_START va_list vl;\
    va_start(vl, signature);

#define VA_END va_end(vl);

using namespace jpp;

Object::Object() {
}

Object::Object(const Class &_class) : m_class(new Class(_class)) {
}

Object::Object(const Class &_class, jobject object) : m_class(new Class(_class)) {
    if (object != nullptr) {
        m_jobject = m_class->get_env()->get_jenv()->NewLocalRef(object);
    }
}

Object::Object(const Object &other) {
    if (other.m_class != nullptr) {
        m_class = new Class(*other.m_class);
        if (other.m_jobject != nullptr) {
            m_jobject = m_class->get_env()->get_jenv()->NewLocalRef(other.m_jobject);
        }
    }
}

Object::Object(Object &&other) : m_class(std::move(other.m_class)) {
    m_class = other.m_class;
    other.m_class = nullptr;
    m_jobject = other.m_jobject;
    other.m_jobject = nullptr;
}

Object::~Object() {
    if (m_class != nullptr) {
        if (m_jobject != nullptr) {
            m_class->get_env()->get_jenv()->DeleteLocalRef(m_jobject);
            m_jobject = nullptr;
        }

        delete m_class;
        m_class = nullptr;
    }
}

bool Object::operator==(const Object &other) {
    return get_env()->get_jenv()->IsSameObject(m_jobject, other.m_jobject);
}

bool Object::operator!=(const Object &other) {
    return !(*this == other);
}

bool Object::is_valid() const {
    return m_class != nullptr && m_jobject != nullptr;
}

Class &Object::get_class() const {
    return *m_class;
}

Env *Object::get_env() const {
    return m_class->get_env();
}

jclass Object::get_jclass() const {
    return m_class->get_jclass();
}

jobject Object::get_jobject() const {
    return m_jobject;
}

bool Object::is_instance_of(const Class &other) {
    return is_valid() && get_env()->get_jenv()->IsInstanceOf(m_jobject, other.get_jclass());
}

Object Object::cast_to(const Class &other) {
    if (is_instance_of(other)) {
        return Object(other, m_jobject);
    } else {
        return Object(*m_class);
    }
}

Object Object::cast_to(const char *class_name) {
    Class other = get_env()->find_class(class_name);
    return cast_to(other);
}

Object Object::do_call(const char *method_name, const char *signature,
                       ...) {
    VA_START
    auto ret = get_env()->call_method(*this, method_name, signature, vl);
    VA_END
    return ret;
}

void Object::do_call(void *type, const char *method_name, const char *signature, ...) {
    VA_START
    get_env()->call_method(*this, method_name, signature, vl, (void *) 0);
    VA_END
}

template<>
jboolean Object::do_call(jboolean, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_method<jboolean>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jbyte Object::do_call(jbyte, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_method<jbyte>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jchar Object::do_call(jchar, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_method<jchar>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jshort Object::do_call(jshort, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_method<jshort>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jint Object::do_call(jint, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_method<jint>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jlong Object::do_call(jlong, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_method<jlong>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jfloat Object::do_call(jfloat, const char *method_name, const char *signature, ...) {
    VA_START
    auto ret = get_env()->call_method<jfloat>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

template<>
jdouble Object::do_call(jdouble, const char *method_name, const char *signature, ...) {
    VA_START;
    auto ret = get_env()->call_method<jdouble>(*this, method_name, signature, vl);
    VA_END
    return ret;
}

Object Object::do_get(const char *field_name, const char *signature) {
    auto ret = get_env()->get_field(*this, field_name, signature);
    return ret;
}

template<>
jboolean Object::do_get(jboolean type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_field<jboolean>(*this, field_name, signature);
    return ret;
}

template<>
jbyte Object::do_get(jbyte type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_field<jbyte>(*this, field_name, signature);
    return ret;
}

template<>
jchar Object::do_get(jchar type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_field<jchar>(*this, field_name, signature);
    return ret;
}

template<>
jshort Object::do_get(jshort type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_field<jshort>(*this, field_name, signature);
    return ret;
}

template<>
jint Object::do_get(jint type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_field<jint>(*this, field_name, signature);
    return ret;
}

template<>
jlong Object::do_get(jlong type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_field<jlong>(*this, field_name, signature);
    return ret;
}

template<>
jfloat Object::do_get(jfloat type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_field<jfloat>(*this, field_name, signature);
    return ret;
}

template<>
jdouble Object::do_get(jdouble type, const char *field_name, const char *signature) {
    auto ret = get_env()->get_field<jdouble>(*this, field_name, signature);
    return ret;
}

void Object::do_set(const char *field_name, const char *signature, const Object& value) {
    get_env()->set_field(*this, field_name, signature, value);
}

template<>
void Object::do_set(const char *field_name, const char *signature, const jboolean& value) {
    get_env()->set_field<jboolean>(*this, field_name, signature, value);
}

template<>
void Object::do_set(const char *field_name, const char *signature, const jbyte& value) {
    get_env()->set_field<jbyte>(*this, field_name, signature, value);
}

template<>
void Object::do_set(const char *field_name, const char *signature, const jchar& value) {
    get_env()->set_field<jchar>(*this, field_name, signature, value);
}

template<>
void Object::do_set(const char *field_name, const char *signature, const jshort& value) {
    get_env()->set_field<jshort>(*this, field_name, signature, value);
}

template<>
void Object::do_set(const char *field_name, const char *signature, const jint& value) {
    get_env()->set_field<jint>(*this, field_name, signature, value);
}

template<>
void Object::do_set(const char *field_name, const char *signature, const jlong& value) {
    get_env()->set_field<jlong>(*this, field_name, signature, value);
}

template<>
void Object::do_set(const char *field_name, const char *signature, const jfloat& value) {
    get_env()->set_field<jfloat>(*this, field_name, signature, value);
}

template<>
void Object::do_set(const char *field_name, const char *signature, const jdouble& value) {
    get_env()->set_field<jdouble>(*this, field_name, signature, value);
}
