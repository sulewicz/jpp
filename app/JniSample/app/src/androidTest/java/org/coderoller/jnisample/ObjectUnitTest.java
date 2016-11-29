package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.ObjectTester;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
public class ObjectUnitTest {
    private ObjectTester mTester;

    @Before
    public void setUp() {
        mTester = new ObjectTester();
    }

    @After
    public void tearDown() {
        mTester = null;
    }

    @Test
    public void testEquality() {
        Object a = new Object();
        Object b = new Object();
        assertTrue(mTester.checkEquality(a, a));
        assertFalse(mTester.checkEquality(a, b));
        assertFalse(mTester.checkEquality(a, null));
        assertFalse(mTester.checkEquality(null, b));
        assertTrue(mTester.checkEquality(null, null));
    }
}
