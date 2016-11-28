package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.ArrayTester;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
public class ArrayUnitTest {
    private ArrayTester mTester;

    @Before
    public void setUp() {
        mTester = new ArrayTester();
    }

    @After
    public void tearDown() {
        mTester = null;
    }

    @Test
    public void testCreatingArray() throws Exception {
        Object[] objects = mTester.createObjectArray(2);
        assertEquals(2, objects.length);

        boolean[] booleans = mTester.createBooleanArray(3);
        assertEquals(3, booleans.length);

        byte[] bytes = mTester.createByteArray(4);
        assertEquals(4, bytes.length);

        char[] chars = mTester.createCharArray(5);
        assertEquals(5, chars.length);

        short[] shorts = mTester.createShortArray(6);
        assertEquals(6, shorts.length);

        int[] ints = mTester.createIntArray(7);
        assertEquals(7, ints.length);

        long[] longs = mTester.createLongArray(8);
        assertEquals(8, longs.length);

        float[] floats = mTester.createFloatArray(9);
        assertEquals(9, floats.length);

        double[] doubles = mTester.createDoubleArray(10);
        assertEquals(10, doubles.length);
    }

    @Test
    public void testGettingItem() {
        Object[] objects = createObjectArray();
        for (int i = 0; i < objects.length; ++i) {
            assertEquals(objects[i], mTester.getObjectItem(objects, i));
        }

        boolean[] booleans = createBooleanArray();
        for (int i = 0; i < booleans.length; ++i) {
            assertEquals(booleans[i], mTester.getBooleanItem(booleans, i));
        }

        byte[] bytes = createByteArray();
        for (int i = 0; i < bytes.length; ++i) {
            assertEquals(bytes[i], mTester.getByteItem(bytes, i));
        }

        char[] chars = createCharArray();
        for (int i = 0; i < chars.length; ++i) {
            assertEquals(chars[i], mTester.getCharItem(chars, i));
        }

        short[] shorts = createShortArray();
        for (int i = 0; i < shorts.length; ++i) {
            assertEquals(shorts[i], mTester.getShortItem(shorts, i));
        }

        int[] ints = createIntArray();
        for (int i = 0; i < ints.length; ++i) {
            assertEquals(ints[i], mTester.getIntItem(ints, i));
        }

        long[] longs = createLongArray();
        for (int i = 0; i < longs.length; ++i) {
            assertEquals(longs[i], mTester.getLongItem(longs, i));
        }

        float[] floats = createFloatArray();
        for (int i = 0; i < floats.length; ++i) {
            assertTrue(floats[i] == mTester.getFloatItem(floats, i));
        }

        double[] doubles = createDoubleArray();
        for (int i = 0; i < doubles.length; ++i) {
            assertTrue(doubles[i] == mTester.getDoubleItem(doubles, i));
        }
    }

    @Test
    public void testSettingItem() {
        Object[] objects = createObjectArray();
        for (int i = 0; i < objects.length; ++i) {
            mTester.setObjectItem(objects, i, objects[(i + 1) % objects.length]);
            assertEquals(objects[(i + 1) % objects.length], mTester.getObjectItem(objects, i));
        }
        boolean[] booleans = createBooleanArray();
        for (int i = 0; i < booleans.length; ++i) {
            mTester.setBooleanItem(booleans, i, booleans[(i + 1) % booleans.length]);
            assertEquals(booleans[(i + 1) % booleans.length], mTester.getBooleanItem(booleans, i));
        }
        byte[] bytes = createByteArray();
        for (int i = 0; i < bytes.length; ++i) {
            mTester.setByteItem(bytes, i, bytes[(i + 1) % bytes.length]);
            assertEquals(bytes[(i + 1) % bytes.length], mTester.getByteItem(bytes, i));
        }
        char[] chars = createCharArray();
        for (int i = 0; i < chars.length; ++i) {
            mTester.setCharItem(chars, i, chars[(i + 1) % chars.length]);
            assertEquals(chars[(i + 1) % chars.length], mTester.getCharItem(chars, i));
        }
        short[] shorts = createShortArray();
        for (int i = 0; i < shorts.length; ++i) {
            mTester.setShortItem(shorts, i, shorts[(i + 1) % shorts.length]);
            assertEquals(shorts[(i + 1) % shorts.length], mTester.getShortItem(shorts, i));
        }
        int[] ints = createIntArray();
        for (int i = 0; i < ints.length; ++i) {
            mTester.setIntItem(ints, i, ints[(i + 1) % ints.length]);
            assertEquals(ints[(i + 1) % ints.length], mTester.getIntItem(ints, i));
        }
        long[] longs = createLongArray();
        for (int i = 0; i < longs.length; ++i) {
            mTester.setLongItem(longs, i, longs[(i + 1) % longs.length]);
            assertEquals(longs[(i + 1) % longs.length], mTester.getLongItem(longs, i));
        }
        float[] floats = createFloatArray();
        for (int i = 0; i < floats.length; ++i) {
            mTester.setFloatItem(floats, i, floats[(i + 1) % floats.length]);
            assertTrue(floats[(i + 1) % floats.length] == mTester.getFloatItem(floats, i));
        }
        double[] doubles = createDoubleArray();
        for (int i = 0; i < doubles.length; ++i) {
            mTester.setDoubleItem(doubles, i, doubles[(i + 1) % doubles.length]);
            assertTrue(doubles[(i + 1) % doubles.length] == mTester.getDoubleItem(doubles, i));
        }
    }

    @Test
    public void testGettingLength() {
        Object[] objects = createObjectArray();
        assertEquals(objects.length, mTester.getObjectLength(objects));
        boolean[] booleans = createBooleanArray();
        assertEquals(booleans.length, mTester.getBooleanLength(booleans));
        byte[] bytes = createByteArray();
        assertEquals(bytes.length, mTester.getByteLength(bytes));
        char[] chars = createCharArray();
        assertEquals(chars.length, mTester.getCharLength(chars));
        short[] shorts = createShortArray();
        assertEquals(shorts.length, mTester.getShortLength(shorts));
        int[] ints = createIntArray();
        assertEquals(ints.length, mTester.getIntLength(ints));
        long[] longs = createLongArray();
        assertEquals(longs.length, mTester.getLongLength(longs));
        float[] floats = createFloatArray();
        assertEquals(floats.length, mTester.getFloatLength(floats));
        double[] doubles = createDoubleArray();
        assertEquals(doubles.length, mTester.getDoubleLength(doubles));
    }

    private Object[] createObjectArray() {
        return new Object[]{"test1", "test2", "test3"};
    }

    private boolean[] createBooleanArray() {
        return new boolean[]{false, true, false};
    }

    private byte[] createByteArray() {
        return new byte[]{(byte) 1, (byte) 2, (byte) 3};
    }

    private char[] createCharArray() {
        return new char[]{(char) 1, (char) 2, (char) 3, (char) 4};
    }

    private short[] createShortArray() {
        return new short[]{(short) 1, (short) 2, (short) 3, (short) 4, (short) 5};
    }

    private int[] createIntArray() {
        return new int[]{1, 2, 3, 4, 5, 6};
    }

    private long[] createLongArray() {
        return new long[]{1, 2, 3, 4, 5, 6, 7};
    }

    private float[] createFloatArray() {
        return new float[]{1, 2, 3, 4, 5, 6, 7, 8};
    }

    private double[] createDoubleArray() {
        return new double[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    }

}
