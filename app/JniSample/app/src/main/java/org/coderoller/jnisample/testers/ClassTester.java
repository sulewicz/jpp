package org.coderoller.jnisample.testers;

public class ClassTester {
    static {
        System.loadLibrary("native-lib");
    }

    public Object createObject() {
        return createObjectNative();
    }

    public SimpleClass createSimpleClass(Object o, boolean bool, byte b, char c, short s, int i, long l, float f, double d, String str) {
        return createSimpleClassNative(o, bool, b, c, s, i, l, f, d, str);
    }

    public Class<?> getSuperclass(Class<?> _class) {
        return getSuperclassNative(_class);
    }

    public boolean checkAssignability(Class<?> from, Class<?> to) {
        return checkAssignabilityNative(from, to);
    }

    private native Object createObjectNative();

    private native SimpleClass createSimpleClassNative(Object o, boolean bool, byte b, char c, short s, int i, long l, float f, double d,
                                                       String str);

    private native Class<?> getSuperclassNative(Class<?> _class);

    private native boolean checkAssignabilityNative(Class<?> from, Class<?> to);

    public static class SimpleClass {
        private Object mObject = null;
        private boolean mBoolean = false;
        private byte mByte = 0;
        private char mChar = 0;
        private short mShort = 0;
        private int mInt = 0;
        private long mLong = 0;
        private float mFloat = 0;
        private double mDouble = 0;
        private String mString = "";

        public SimpleClass() {
        }

        public SimpleClass(Object o, boolean bool, byte b, char c, short s, int i, long l, float f, double d, String str) {
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
    }
}
