package org.coderoller.jnisample.testers;

public class CreationTester {
    static {
        System.loadLibrary("native-lib");
    }

    public Object createObject() {
        return createObjectNative();
    }

    private native Object createObjectNative();
}
