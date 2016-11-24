package org.coderoller.jnisample.testers;

public class ArrayTester {
    static {
        System.loadLibrary("native-lib");
    }

    public Object[] createObjectArray(int size) {
        return createObjectArrayNative(size);
    }

    public int getObjectLength(Object[] array) {
        return getObjectLengthNative(array);
    }

    public Object getObjectItem(Object[] array, int idx) {
        return getObjectItemNative(array, idx);
    }

    public void setObjectItem(Object[] array, int idx, Object newItem) {
        setObjectItemNative(array, idx, newItem);
    }

    // TODO: add other primitives
    public byte[] createByteArray(int size) {
        return createByteArrayNative(size);
    }

    public int getByteLength(byte[] array) {
        return getByteLengthNative(array);
    }

    public byte getByteItem(byte[] array, int idx) {
        return getByteItemNative(array, idx);
    }

    public void setByteItem(byte[] array, int idx, byte newItem) {
        setByteItemNative(array, idx, newItem);
    }

    private native Object[] createObjectArrayNative(int size);

    private native int getObjectLengthNative(Object[] array);

    private native Object getObjectItemNative(Object[] array, int idx);

    private native void setObjectItemNative(Object[] array, int idx, Object newItem);

    private native byte[] createByteArrayNative(int size);

    private native int getByteLengthNative(byte[] array);

    private native byte getByteItemNative(byte[] array, int idx);

    private native void setByteItemNative(byte[] array, int idx, byte newItem);
}
