package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.FieldTester;
import org.coderoller.jnisample.testers.StaticFieldTester;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
public class StaticFieldUnitTest {
    @Before
    public void setUp() {
        StaticFieldTester.reset();;
    }

    @Test
    public void testAccessingObject() throws Exception {
        Object o = new Integer(3);
        assertEquals(o, StaticFieldTester.setAndGetObjectField(o));
    }

    @Test
    public void testAccessingBoolean() throws Exception {
        assertTrue(StaticFieldTester.setAndGetBooleanField(true));
        assertFalse(StaticFieldTester.setAndGetBooleanField(false));
    }

    @Test
    public void testAccessingByte() throws Exception {
        assertEquals(Byte.MIN_VALUE, StaticFieldTester.setAndGetByteField(Byte.MIN_VALUE));
    }

    @Test
    public void testAccessingChar() throws Exception {
        assertEquals(Character.MIN_VALUE, StaticFieldTester.setAndGetCharField(Character.MIN_VALUE));
    }

    @Test
    public void testAccessingShort() throws Exception {
        assertEquals(Short.MIN_VALUE, StaticFieldTester.setAndGetShortField(Short.MIN_VALUE));
    }

    @Test
    public void testAccessingInt() throws Exception {
        assertEquals(Integer.MIN_VALUE, StaticFieldTester.setAndGetIntField(Integer.MIN_VALUE));
    }

    @Test
    public void testAccessingLong() throws Exception {
        assertEquals(Long.MIN_VALUE, StaticFieldTester.setAndGetLongField(Long.MIN_VALUE));
    }


    @Test
    public void testAccessingFloat() throws Exception {
        assertTrue(Float.MIN_VALUE == StaticFieldTester.setAndGetFloatField(Float.MIN_VALUE));
    }

    @Test
    public void testAccessingDouble() throws Exception {
        assertTrue(Double.MIN_VALUE == StaticFieldTester.setAndGetDoubleField(Double.MIN_VALUE));
    }

    @Test
    public void testAccessingObjectArray() throws Exception {
        Object[] o = new Object[] { "a", 2, "c" };
        assertTrue(o == StaticFieldTester.setAndGetObjectArrayField(o));
    }

    @Test
    public void testAccessingByteArray() throws Exception {
        byte[] b = new byte[] { (byte) 1, (byte) 2 };
        assertTrue(b == StaticFieldTester.setAndGetByteArrayField(b));
    }
}
