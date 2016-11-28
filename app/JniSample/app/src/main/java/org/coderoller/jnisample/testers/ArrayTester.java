package org.coderoller.jnisample.testers;

public class ArrayTester {
    static {
        System.loadLibrary("native-lib");
    }

    public native Object[] createObjectArray(int size);

    public native int getObjectLength(Object[] array);

    public native Object getObjectItem(Object[] array, int idx);

    public native void setObjectItem(Object[] array, int idx, Object newItem);

    public native boolean[] createBooleanArray(int size);

    public native int getBooleanLength(boolean[] array);

    public native boolean getBooleanItem(boolean[] array, int idx);

    public native void setBooleanItem(boolean[] array, int idx, boolean newItem);

    public native byte[] createByteArray(int size);

    public native int getByteLength(byte[] array);

    public native byte getByteItem(byte[] array, int idx);

    public native void setByteItem(byte[] array, int idx, byte newItem);

    public native char[] createCharArray(int size);

    public native int getCharLength(char[] array);

    public native char getCharItem(char[] array, int idx);

    public native void setCharItem(char[] array, int idx, char newItem);

    public native short[] createShortArray(int size);

    public native int getShortLength(short[] array);

    public native short getShortItem(short[] array, int idx);

    public native void setShortItem(short[] array, int idx, short newItem);

    public native int[] createIntArray(int size);

    public native int getIntLength(int[] array);

    public native int getIntItem(int[] array, int idx);

    public native void setIntItem(int[] array, int idx, int newItem);

    public native long[] createLongArray(int size);

    public native int getLongLength(long[] array);

    public native long getLongItem(long[] array, int idx);

    public native void setLongItem(long[] array, int idx, long newItem);

    public native float[] createFloatArray(int size);

    public native int getFloatLength(float[] array);

    public native float getFloatItem(float[] array, int idx);

    public native void setFloatItem(float[] array, int idx, float newItem);

    public native double[] createDoubleArray(int size);

    public native int getDoubleLength(double[] array);

    public native double getDoubleItem(double[] array, int idx);

    public native void setDoubleItem(double[] array, int idx, double newItem);
}
