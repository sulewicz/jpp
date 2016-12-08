package org.coderoller.jnisample.testers;

public class FieldTester {
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
    private Object[] mObjectArray = null;
    private byte[] mByteArray = null;

    // Methods used for actual testing.

    public native Object setAndGetObjectField(Object o);

    public native boolean setAndGetBooleanField(boolean b);

    public native byte setAndGetByteField(byte b);

    public native char setAndGetCharField(char c);

    public native short setAndGetShortField(short s);

    public native int setAndGetIntField(int i);

    public native long setAndGetLongField(long l);

    public native float setAndGetFloatField(float f);

    public native double setAndGetDoubleField(double d);

    public native Object[] setAndGetObjectArrayField(Object[] o);

    public native byte[] setAndGetByteArrayField(byte[] b);
}
