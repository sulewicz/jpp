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
    private short mShort = 0;
    private int mInt = 0;
    private long mLong = 0;
    private float mFloat = 0;
    private double mDouble = 0;

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

    private short shortMethod() {
        return mShort;
    }

    private int intMethod() {
        return mInt;
    }

    private long longMethod() {
        return mLong;
    }

    private float floatMethod() {
        return mFloat;
    }

    private double doubleMethod() {
        return mDouble;
    }

    // Helper methods used by unit tests.

    public void setObject(Object o) {
        mObject = o;
    }

    public void setBoolean(boolean b) {
        mBoolean = b;
    }

    public void setByte(byte b) {
        mByte = b;
    }

    public void setChar(char c) {
        mChar = c;
    }

    public void setShort(short s) {
        mShort = s;
    }

    public void setInt(int i) {
        mInt = i;
    }

    public void setLong(long l) {
        mLong = l;
    }

    public void setFloat(float f) {
        mFloat = f;
    }

    public void setDouble(double d) {
        mDouble = d;
    }

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

    public short callShortMethod() {
        return callShortMethodNative();
    }

    public int callIntMethod() {
        return callIntMethodNative();
    }

    public long callLongMethod() {
        return callLongMethodNative();
    }

    public float callFloatMethod() {
        return callFloatMethodNative();
    }

    public double callDoubleMethod() {
        return callDoubleMethodNative();
    }

    private native Object callObjectMethodNative();

    private native void callVoidMethodNative();

    private native boolean callBooleanMethodNative();

    private native byte callByteMethodNative();

    private native char callCharMethodNative();

    private native short callShortMethodNative();

    private native int callIntMethodNative();

    private native long callLongMethodNative();

    private native float callFloatMethodNative();

    private native double callDoubleMethodNative();
}
