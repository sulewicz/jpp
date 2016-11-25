#include "Cache.h"
#include "Env.h"

using namespace jpp;

Cache::Cache() {
}

Cache::~Cache() {
}

Class Cache::get_class(Env *env, const char *class_name) {
    auto search = m_jclass_cache.find(class_name);
    if (search != m_jclass_cache.end()) {
        return Class(env, search->second, search->first.c_str());
    } else {
        return Class(env);
    }
}

Class Cache::add_class(Env *env, const char *class_name, jclass _jclass) {
    if (_jclass != nullptr) {
        // Creating global reference, delete on removal.
        _jclass = (jclass) env->get_jenv()->NewGlobalRef(_jclass);
    }
    auto result = m_jclass_cache.emplace(
            std::make_pair(std::string(class_name), _jclass));
    auto &entry = result.first;
    return Class(env, entry->second, entry->first.c_str());
}

void Cache::clear(Env *env) {
    auto jenv = env->get_jenv();
    for (auto entry : m_jclass_cache) {
        jenv->DeleteGlobalRef(entry.second);
    }
    m_jclass_cache.clear();
}