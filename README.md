### JPP - JNI on steroids.

Solving pain with JNI usage thanks to C++11 features like variadic templates.

#### How to use it

Proper documentation is still a work in progress.
Yet you can have a look at the unit tests code found in _app/JniSample/app/src/main/cpp/_, which cover all the available features.

One of the features of this library is that you no longer have to worry about specifying proper method signature manually during method lookup.
Have a look at the examples below of some of the features you can find:

**Calling a method returning a specific primitive type:**
```
private boolean booleanMethod() {
    return mBoolean;
}
```
```
JNIEXPORT jboolean JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callBooleanMethod(JNIEnv *env,
                                                                     jobject obj) {

    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    return method_tester_object.call<jboolean>("booleanMethod");
}
```

**Calling a method returning a specific object type:**
```
private Object objectMethod() {
    return mObject;
}
```
```
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callObjectMethod(JNIEnv *env,
                                                                    jobject obj) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    jpp::Class return_class = jpp_env.find_class("java/lang/Object");
    auto ret = method_tester_object.call_object("objectMethod", return_class);
    return (jobject) ret;
}
```

**Calling a void method:**
```
private void multiParamMethod(Object o, boolean bool, byte b, char c, short s, int i, long l, float f, double d) {
  ...
}
```
```
JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_MethodTester_callMultiParamMethod(JNIEnv *env,
                                                                        jobject obj,
                                                                        jobject o,
                                                                        jboolean boolean,
                                                                        jbyte b, jchar c,
                                                                        jshort s, jint i,
                                                                        jlong l, jfloat f,
                                                                        jdouble d) {
    jpp::Env jpp_env(env);
    jpp::Object method_tester_object = jpp_env.wrap(obj);
    method_tester_object.call_void("multiParamMethod", jpp_env.wrap("java/lang/Object", o), boolean,
                                   b, c,
                                   s, i, l, f, d);
}
```

**Creating simple object:**
```
JNIEXPORT jobject JNICALL
Java_org_coderoller_jnisample_testers_ClassTester_createObject(JNIEnv *env,
                                                               jobject instance) {
    jpp::Env jpp_env(env);
    auto integer_class = jpp_env.find_class("java/lang/Integer");
    auto ret = integer_class.create(3);
    return (jobject) ret;
}
```

**Performing async operation in POSIX thread and attaching it to the JVM:**
```
static jpp::JVM JVM_INSTANCE;
static jpp::GlobalRef JVM_TESTER_REFERENCE;

JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_JvmTester_cacheJvm(JNIEnv *env, jobject obj) {
    // This has to be called first so the JVM instance can be cached for usage from POSIX thread.
    if (!JVM_INSTANCE.is_valid()) {
        jpp::Env jpp_env(env);
        JVM_INSTANCE = jpp_env.get_jvm();
    }
}

JNIEXPORT void JNICALL
Java_org_coderoller_jnisample_testers_JvmTester_asyncOperation(JNIEnv *env, jobject obj) {
    jpp::Env jpp_env(env);
    auto jvm_tester_object = jpp_env.wrap(obj);
    // Storing global reference to our test object instance in which the callback method is implemented.
    JVM_TESTER_REFERENCE.wrap(jvm_tester_object);
    std::thread thread([]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (JVM_INSTANCE.is_valid() && JVM_TESTER_REFERENCE.is_valid()) {
            jpp::Env jpp_env = JVM_INSTANCE.attach_current_thread();
            if (jpp_env.is_valid()) {
                // Introducing new scope to avoid object destruction after detaching from thread.
                {
                    jpp::Object jvm_tester_object = JVM_TESTER_REFERENCE.unwrap(jpp_env);
                    JVM_TESTER_REFERENCE.release(jpp_env);

                    auto object_class = jpp_env.find_class("java/lang/Object");
                    auto result = object_class.create();
                    {
                        jpp::Monitor monitor = jpp_env.synchronize(jvm_tester_object);
                        jvm_tester_object.set("mResult", result);
                        jvm_tester_object.call_void("notifyAll");
                    }
                }
                // All objects destroyed, now we can safely detach.
                JVM_INSTANCE.detach_current_thread();
            }
        }
    });
    thread.detach();
}
```

#### How to build it

There is no fancy setup available yet (and may be never available).
Since most of the projects that require JNI development are quite specific, the easiest way to integrate this library is to simply copy the _app/JniSample/app/src/main/cpp/jpp_ directory to your project.
Please note that your project will have to support C++11 features.
Also please note that this library uses C++ exceptions by default. This allows you to catch Java exceptions as regular C++ exceptions in your code.
However if you don't need this feature, you can easily disable it by editing _jpp_config.h_ file:
```
#ifndef JPP_EXCEPTIONS_SUPPORTED
#define JPP_EXCEPTIONS_SUPPORTED 1
#endif
```

#### API reference

This is still work in progress, but you can find it [**here**](http://htmlpreview.github.io/?https://github.com/sulewicz/jpp/blob/master/doc/html/index.html).
