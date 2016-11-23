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
    private String mString = "";

    // Methods invoked from native layer.

    private void multiParamMethod(Object o, boolean bool, byte b, char c, short s, int i, long l, float f, double d, String str) {
        mObject = o;
        mBoolean = bool;
        mByte = b;
        mChar = c;
        mShort = s;
        mInt = i;
        mLong = l;
        mFloat = f;
        mDouble = d;
        mString = str;
    }

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

    @Override
    public String toString() {
        return mString;
    }

    // Helper methods used by unit tests.

    public Object getObject() {
        return mObject;
    }

    public void setObject(Object object) {
        mObject = object;
    }

    public boolean isBoolean() {
        return mBoolean;
    }

    public void setBoolean(boolean aBoolean) {
        mBoolean = aBoolean;
    }

    public byte getByte() {
        return mByte;
    }

    public void setByte(byte aByte) {
        mByte = aByte;
    }

    public char getChar() {
        return mChar;
    }

    public void setChar(char aChar) {
        mChar = aChar;
    }

    public short getShort() {
        return mShort;
    }

    public void setShort(short aShort) {
        mShort = aShort;
    }

    public int getInt() {
        return mInt;
    }

    public void setInt(int anInt) {
        mInt = anInt;
    }

    public long getLong() {
        return mLong;
    }

    public void setLong(long aLong) {
        mLong = aLong;
    }

    public float getFloat() {
        return mFloat;
    }

    public void setFloat(float aFloat) {
        mFloat = aFloat;
    }

    public double getDouble() {
        return mDouble;
    }

    public void setDouble(double aDouble) {
        mDouble = aDouble;
    }

    public String getString() {
        return mString;
    }

    public void setString(String string) {
        mString = string;
    }

    // Methods used for actual testing.

    public void callMultiParamMethod(Object o, boolean bool, byte b, char c, short s, int i, long l, float f, double d, String str) {
        callMultiParamMethodNative(o, bool, b, c, s, i, l, f, d, str);
    }

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

    public String callToString() {
        return callToStringNative();
    }

    public Class<?> callGetClass() {
        return callGetClassNative();
    }

    private native void callMultiParamMethodNative(Object o, boolean bool, byte b, char c, short s, int i, long l, float f, double d,
                                                   String str);

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

    private native String callToStringNative();

    private native Class<?> callGetClassNative();
}
