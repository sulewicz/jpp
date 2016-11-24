package org.coderoller.jnisample;

import android.support.test.runner.AndroidJUnit4;

import org.coderoller.jnisample.testers.ArrayTester;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertEquals;

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

        byte[] bytes = mTester.createByteArray(3);
        assertEquals(3, bytes.length);
    }

    @Test
    public void testGettingItem() {
        // TODO: re-enable after creating cache
        /*Object[] objects = createObjectsArray();
        for (int i = 0; i < objects.length; ++i) {
            assertEquals(objects[i], mTester.getObjectItem(objects, i));
        }*/

        byte[] bytes = createBytesArray();
        for (int i = 0; i < bytes.length; ++i) {
            assertEquals(bytes[i], mTester.getByteItem(bytes, i));
        }
    }

    @Test
    public void testSettingItem() {
        // TODO: re-enable after creating cache
        /*Object[] objects = createObjectsArray();
        for (int i = 0; i < objects.length; ++i) {
            mTester.setObjectItem(objects, i, objects[(i + 1) % objects.length]);
            assertEquals(objects[(i + 1) % objects.length], mTester.getObjectItem(objects, i));
        }*/
        byte[] bytes = createBytesArray();
        for (int i = 0; i < bytes.length; ++i) {
            mTester.setByteItem(bytes, i, bytes[(i + 1) % bytes.length]);
            assertEquals(bytes[(i + 1) % bytes.length], mTester.getByteItem(bytes, i));
        }
    }

    @Test
    public void testGettingLength() {
        Object[] objects = createObjectsArray();
        assertEquals(objects.length, mTester.getObjectLength(objects));
        byte[] bytes = createBytesArray();
        assertEquals(bytes.length, mTester.getByteLength(bytes));
    }

    private Object[] createObjectsArray() {
        return new Object[]{"test1", "test2", "test3"};
    }

    private byte[] createBytesArray() {
        return new byte[]{(byte) 1, (byte) 2, (byte) 3};
    }
}
