package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.ClassTester;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.io.Serializable;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
public class ClassUnitTest {
    private ClassTester mTester;

    @Before
    public void setUp() {
        mTester = new ClassTester();
    }

    @After
    public void tearDown() {
        mTester = null;
    }

    @Test
    public void testCreatingObject() throws Exception {
        Object object = mTester.createObject();
        assertNotNull(object);
        assertTrue(object instanceof Integer);
        assertEquals(3, ((Integer) object).intValue());
    }

    @Test
    public void testMultiParamConstructor() throws Exception {
        Object o = new Integer(3);
        boolean bool = true;
        byte b = (byte) 1;
        char c = (char) 2;
        short s = (short) 3;
        int i = 4;
        long l = (long) 5;
        float f = (float) 6;
        double d = (double) 7;
        String str = "test";
        ClassTester.SimpleClass simpleClass = mTester.createSimpleClass(o, bool, b, c, s, i, l, f, d, str);
        assertEquals(o, simpleClass.getObject());
        assertEquals(bool, simpleClass.isBoolean());
        assertEquals(b, simpleClass.getByte());
        assertEquals(c, simpleClass.getChar());
        assertEquals(s, simpleClass.getShort());
        assertEquals(i, simpleClass.getInt());
        assertEquals(l, simpleClass.getLong());
        assertTrue(f == simpleClass.getFloat());
        assertTrue(d == simpleClass.getDouble());
        assertEquals(str, simpleClass.getString());
    }

    @Test
    public void testSuperclassMethod() {
        assertEquals(Number.class, mTester.getSuperclass(Integer.class));
        assertNull(mTester.getSuperclass(null));
        assertNull(mTester.getSuperclass(Object.class));
        assertNull(mTester.getSuperclass(Serializable.class));
    }

    @Test
    public void testAssignableFromMethod() {
        assertTrue(mTester.checkAssignability(Number.class, Number.class));
        assertTrue(mTester.checkAssignability(Integer.class, Number.class));
        assertFalse(mTester.checkAssignability(Number.class, Integer.class));
        assertFalse(mTester.checkAssignability(null, Object.class));
        assertFalse(mTester.checkAssignability(Object.class, null));
    }

    @Test
    public void testEquality() {
        assertTrue(mTester.checkEquality(Number.class, Number.class));
        assertFalse(mTester.checkEquality(Number.class, Integer.class));
        assertFalse(mTester.checkEquality(Number.class, null));
        assertFalse(mTester.checkEquality(null, Integer.class));
        assertTrue(mTester.checkEquality(null, null));
    }
}
