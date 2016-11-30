package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.StaticMethodTester;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
public class StaticMethodUnitTest {
    @Before
    public void setUp() {
        StaticMethodTester.reset();
    }

    @Test
    public void testInvokingMultiParamMethod() throws Exception {
        Object o = new Integer(3);
        boolean bool = true;
        byte b = (byte) 1;
        char c = (char) 2;
        short s = (short) 3;
        int i = 4;
        long l = (long) 5;
        float f = (float) 6;
        double d = (double) 7;
        StaticMethodTester.callMultiParamMethod(o, bool, b, c, s, i, l, f, d);
        assertEquals(o, StaticMethodTester.getObject());
        assertEquals(bool, StaticMethodTester.isBoolean());
        assertEquals(b, StaticMethodTester.getByte());
        assertEquals(c, StaticMethodTester.getChar());
        assertEquals(s, StaticMethodTester.getShort());
        assertEquals(i, StaticMethodTester.getInt());
        assertEquals(l, StaticMethodTester.getLong());
        assertTrue(f == StaticMethodTester.getFloat());
        assertTrue(d == StaticMethodTester.getDouble());
    }

    @Test
    public void testInvokingMultiArrayParamMethod() throws Exception {
        Object[] o = new Object[1];
        boolean[] bool = new boolean[2];
        byte[] b = new byte[3];
        char[] c = new char[4];
        short[] s = new short[5];
        int[] i = new int[6];
        long[] l = new long[7];
        float[] f = new float[8];
        double[] d = new double[9];
        StaticMethodTester.callMultiParamArrayMethod(o, bool, b, c, s, i, l, f, d);
        assertTrue(o == StaticMethodTester.getObjectArray());
        assertEquals(bool, StaticMethodTester.getBooleanArray());
        assertEquals(b, StaticMethodTester.getByteArray());
        assertEquals(c, StaticMethodTester.getCharArray());
        assertEquals(s, StaticMethodTester.getShortArray());
        assertEquals(i, StaticMethodTester.getIntArray());
        assertEquals(l, StaticMethodTester.getLongArray());
        assertEquals(f, StaticMethodTester.getFloatArray());
        assertEquals(d, StaticMethodTester.getDoubleArray());
    }

    @Test
    public void testReturningObject() throws Exception {
        Object o = new Integer(3);
        StaticMethodTester.setObject(o);
        assertEquals(o, StaticMethodTester.callObjectMethod());
    }

    @Test
    public void testReturningVoid() throws Exception {
        assertTrue(StaticMethodTester.callVoidMethod());
    }

    @Test
    public void testReturningBoolean() throws Exception {
        StaticMethodTester.setBoolean(true);
        assertTrue(StaticMethodTester.callBooleanMethod());
        StaticMethodTester.setBoolean(false);
        assertFalse(StaticMethodTester.callBooleanMethod());
    }

    @Test
    public void testReturningByte() throws Exception {
        StaticMethodTester.setByte(Byte.MIN_VALUE);
        assertEquals(Byte.MIN_VALUE, StaticMethodTester.callByteMethod());
    }

    @Test
    public void testReturningChar() throws Exception {
        StaticMethodTester.setChar(Character.MIN_VALUE);
        assertEquals(Character.MIN_VALUE, StaticMethodTester.callCharMethod());
    }

    @Test
    public void testReturningShort() throws Exception {
        StaticMethodTester.setShort(Short.MIN_VALUE);
        assertEquals(Short.MIN_VALUE, StaticMethodTester.callShortMethod());
    }

    @Test
    public void testReturningInt() throws Exception {
        StaticMethodTester.setInt(Integer.MIN_VALUE);
        assertEquals(Integer.MIN_VALUE, StaticMethodTester.callIntMethod());
    }

    @Test
    public void testReturningLong() throws Exception {
        StaticMethodTester.setLong(Long.MIN_VALUE);
        assertEquals(Long.MIN_VALUE, StaticMethodTester.callLongMethod());
    }

    @Test
    public void testReturningFloat() throws Exception {
        StaticMethodTester.setFloat(Float.MIN_VALUE);
        assertTrue(Float.MIN_VALUE == StaticMethodTester.callFloatMethod());
    }

    @Test
    public void testReturningDouble() throws Exception {
        StaticMethodTester.setDouble(Double.MIN_VALUE);
        assertTrue(Double.MIN_VALUE == StaticMethodTester.callDoubleMethod());
    }
}
