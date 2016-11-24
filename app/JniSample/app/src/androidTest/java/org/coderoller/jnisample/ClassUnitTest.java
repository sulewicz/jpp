package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.ClassTester;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
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
}
