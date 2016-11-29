package org.coderoller.jnisample.testers;

public class ObjectTester {
    public native boolean checkEquality(Object first, Object second);
    public native boolean isInstanceOf(Object object, Class<?> _class);
    public native boolean castTo(Object o, Class<?> otherClass);
}
