package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.CreationTester;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
public class CreationUnitTest {
    private CreationTester mTester;

    @Before
    public void setUp() {
        mTester = new CreationTester();
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
}
