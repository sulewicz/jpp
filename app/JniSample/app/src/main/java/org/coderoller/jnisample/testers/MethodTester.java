package org.coderoller.jnisample.testers;

public class MethodTester {
    static {
        System.loadLibrary("native-lib");
    }

    private Object mObject = null;
    private boolean mVoidCalled = false;
    private boolean mBoolean = false;
    private byte mByte = 0;
    private char mChar = 0;

    // Methods invoked from native layer.

    private Object objectMethod() {
        return mObject;
    }

    private void voidMethod() {
        mVoidCalled = true;
    }

    private boolean booleanMethod() {
        return mBoolean;
    }

    private byte byteMethod() {
        return mByte;
    }

    private char charMethod() {
        return mChar;
    }

    // Helper methods used by unit tests.

    public void setObject(Object object) {
        mObject = object;
    }

    public void setBoolean(boolean bool) {
        mBoolean = bool;
    }

    public void setByte(byte b) {
        mByte = b;
    }

    public void setChar(char c) { mChar = c; }

    // Methods used for actual testing.

    public Object callObjectMethod() {
        return callObjectMethodNative();
    }

    public boolean callVoidMethod() {
        callVoidMethodNative();
        boolean ret = mVoidCalled;
        mVoidCalled = false;
        return ret;
    }

    public boolean callBooleanMethod() {
        return callBooleanMethodNative();
    }

    public byte callByteMethod() {
        return callByteMethodNative();
    }

    public char callCharMethod() {
        return callCharMethodNative();
    }

    private native Object callObjectMethodNative();

    private native void callVoidMethodNative();

    private native boolean callBooleanMethodNative();

    private native byte callByteMethodNative();

    private native char callCharMethodNative();
}
