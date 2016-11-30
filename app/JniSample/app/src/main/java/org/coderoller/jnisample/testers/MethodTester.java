package org.coderoller.jnisample.testers;

public class MethodTester {
    static {
        System.loadLibrary("native-lib");
    }

    // All types

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

    // All array types
    private Object[] mObjectArray = null;
    private boolean[] mBooleanArray = null;
    private byte[] mByteArray = null;
    private char[] mCharArray = null;
    private short[] mShortArray = null;
    private int[] mIntArray = null;
    private long[] mLongArray = null;
    private float[] mFloatArray = null;
    private double[] mDoubleArray = null;

    // Methods invoked from native layer.

    private void multiParamMethod(Object o, boolean bool, byte b, char c, short s, int i, long l, float f, double d) {
        mObject = o;
        mBoolean = bool;
        mByte = b;
        mChar = c;
        mShort = s;
        mInt = i;
        mLong = l;
        mFloat = f;
        mDouble = d;
    }

    private void multiParamArrayMethod(Object[] o, boolean[] bool, byte[] b, char[] c, short[] s, int[] i, long[] l, float[] f, double[]
            d) {
        mObjectArray = o;
        mBooleanArray = bool;
        mByteArray = b;
        mCharArray = c;
        mShortArray = s;
        mIntArray = i;
        mLongArray = l;
        mFloatArray = f;
        mDoubleArray = d;
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

    public Object[] getObjectArray() {
        return mObjectArray;
    }

    public void setObjectArray(Object[] objectArray) {
        mObjectArray = objectArray;
    }

    public boolean[] getBooleanArray() {
        return mBooleanArray;
    }

    public void setBooleanArray(boolean[] booleanArray) {
        mBooleanArray = booleanArray;
    }

    public byte[] getByteArray() {
        return mByteArray;
    }

    public void setByteArray(byte[] byteArray) {
        mByteArray = byteArray;
    }

    public char[] getCharArray() {
        return mCharArray;
    }

    public void setCharArray(char[] charArray) {
        mCharArray = charArray;
    }

    public short[] getShortArray() {
        return mShortArray;
    }

    public void setShortArray(short[] shortArray) {
        mShortArray = shortArray;
    }

    public int[] getIntArray() {
        return mIntArray;
    }

    public void setIntArray(int[] intArray) {
        mIntArray = intArray;
    }

    public long[] getLongArray() {
        return mLongArray;
    }

    public void setLongArray(long[] longArray) {
        mLongArray = longArray;
    }

    public float[] getFloatArray() {
        return mFloatArray;
    }

    public void setFloatArray(float[] floatArray) {
        mFloatArray = floatArray;
    }

    public double[] getDoubleArray() {
        return mDoubleArray;
    }

    public void setDoubleArray(double[] doubleArray) {
        mDoubleArray = doubleArray;
    }

    // Methods used for actual testing.

    public boolean callVoidMethod() {
        callVoidMethodNative();
        boolean ret = mVoidCalled;
        mVoidCalled = false;
        return ret;
    }

    public native void callMultiParamMethod(Object o, boolean bool, byte b, char c, short s, int i, long l, float f, double d);

    public native void callMultiParamArrayMethod(Object[] o, boolean[] bool, byte[] b, char[] c, short[] s, int[] i, long[] l, float[] f,
                                                 double[] d);

    public native Object callObjectMethod();

    public native void callVoidMethodNative();

    public native boolean callBooleanMethod();

    public native byte callByteMethod();

    public native char callCharMethod();

    public native short callShortMethod();

    public native int callIntMethod();

    public native long callLongMethod();

    public native float callFloatMethod();

    public native double callDoubleMethod();

    public native Class<?> callGetClass();
}
