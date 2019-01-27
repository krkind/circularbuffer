/*
 * Unit test for the circular buffer
 */

#include "circularbuffer.h"
#include "gtest/gtest.h"

namespace {

#define BUF_SIZE 7u

// The fixture for testing class Foo.
class CircularBufferTest : public ::testing::Test {
   protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    CircularBufferTest() {
        // You can do set-up work for each test here.
    }

    ~CircularBufferTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for
    // CircularBuffer.
    CircularBufferContext cb;
    uint32_t buf[BUF_SIZE + 1];
};

// Tests that the CircularBufferInit does the intialalization.
TEST_F(CircularBufferTest, Init) {
    CircularBufferInit(&cb, buf, sizeof(buf), sizeof(buf[0]));

    ASSERT_EQ(cb.buf, (uint8_t *)buf);
    ASSERT_EQ(cb.read_pos, cb.write_pos);
    ASSERT_EQ(cb.element_size, sizeof(uint32_t));
    ASSERT_EQ(cb.max_size, BUF_SIZE);
}

// Tests that CircularBufferPushBack add correct number of elements.
TEST_F(CircularBufferTest, PushBack) {
    for (uint32_t i = 0; i < BUF_SIZE; i++) {
        ASSERT_EQ(CircularBufferPushBack(&cb, &i), 0u);
    }

    ASSERT_EQ(CircularBufferSize(&cb), BUF_SIZE);
}

// Tests that CircularBufferPushBack when buffer is full.
TEST_F(CircularBufferTest, PushBackOutOfBoundary) {
    const uint32_t data = 0;

    ASSERT_EQ(CircularBufferPushBack(&cb, &data), -1);
    ASSERT_EQ(CircularBufferSize(&cb), BUF_SIZE);
}

// Tests that CircularBufferPopFront pop correct value and
// correct number of elements.
TEST_F(CircularBufferTest, PopFront) {
    uint32_t data = 0;

    for (uint8_t i = 0; i < BUF_SIZE; i++) {
        ASSERT_EQ(CircularBufferPopFront(&cb, &data), 0u);
        ASSERT_EQ(data, i);
    }

    ASSERT_EQ(CircularBufferSize(&cb), 0u);
}

// Tests that CircularBufferPopFront when buffer is empty.
TEST_F(CircularBufferTest, PopFronOutOfBoundary) {
    uint32_t data = 0;

    ASSERT_EQ(CircularBufferPopFront(&cb, &data), -1);
    ASSERT_EQ(CircularBufferSize(&cb), 0u);
}

// Tests that CircularBufferPeek return correct pointer.
TEST_F(CircularBufferTest, Peek) {
    uint32_t data[BUF_SIZE] = {0};

    // Fill the buffer
    for (uint32_t i = 0; i < BUF_SIZE; i++) {
        data[i] = 10 + i;
        ASSERT_EQ(CircularBufferPushBack(&cb, &data[i]), 0u);
    }

    // Test to peek all elements
    for (uint32_t i = 0; i < BUF_SIZE; i++) {
        uint32_t *peek;
        ASSERT_EQ(CircularBufferPeek(&cb, i, (void **)&peek), 0u);
        ASSERT_EQ(*peek, data[i]);
    }

    // Remove 2 elements and add 1 element
    for (uint32_t i = 0; i < 2; i++) {
        ASSERT_EQ(CircularBufferPopFront(&cb, &data[i]), 0u);
        data[i] = data[i + 2];
    }
    for (uint32_t i = 0; i < BUF_SIZE - 2; i++) {
        data[i] = data[i + 2];
    }
    for (uint32_t i = BUF_SIZE - 2; i < BUF_SIZE - 1; i++) {
        data[i] = 20 + i;
        ASSERT_EQ(CircularBufferPushBack(&cb, &data[i]), 0u);
    }

    // Test to peek all elements
    for (uint32_t i = 0; i < BUF_SIZE - 1; i++) {
        uint32_t *peek;
        ASSERT_EQ(CircularBufferPeek(&cb, i, (void **)&peek), 0u);
        ASSERT_EQ(*peek, data[i]);
    }

    // Fill the buffer again
    for (uint32_t i = BUF_SIZE - 1; i < BUF_SIZE; i++) {
        data[i] = 20 + i;
        ASSERT_EQ(CircularBufferPushBack(&cb, &data[i]), 0u);
    }

    // Test to peek all elements
    for (uint32_t i = 0; i < BUF_SIZE; i++) {
        uint32_t *peek;
        ASSERT_EQ(CircularBufferPeek(&cb, i, (void **)&peek), 0u);
        ASSERT_EQ(*peek, data[i]);
    }

    // Test out of boundary
    uint32_t *peek = NULL;
    ASSERT_EQ(CircularBufferPeek(&cb, BUF_SIZE, (void **)&peek), -1);
    ASSERT_TRUE(peek == NULL);
}

// Tests that CircularBufferSpace return correct value.
TEST_F(CircularBufferTest, Size) {
    ASSERT_EQ(CircularBufferSize(&cb), BUF_SIZE);
}

// Tests that CircularBufferSpace return correct value.
TEST_F(CircularBufferTest, Space) {
    uint32_t data = 0;

    for (uint32_t i = 0; i < BUF_SIZE; i++) {
        ASSERT_EQ(CircularBufferSpace(&cb), i);
        ASSERT_EQ(CircularBufferPopFront(&cb, &data), 0u);
    }

    ASSERT_EQ(CircularBufferSpace(&cb), BUF_SIZE);
}

// Tests that CircularBufferClear clears the circular buffer
TEST_F(CircularBufferTest, Clear) {
    uint32_t data = 10u;

    for (uint32_t i = 0; i < BUF_SIZE; i++) {
        ASSERT_EQ(CircularBufferPushBack(&cb, &i), 0u);
    }

    CircularBufferClear(&cb);

    ASSERT_EQ(CircularBufferSize(&cb), 0u);
    ASSERT_EQ(CircularBufferPushBack(&cb, &data), 0u);
    ASSERT_EQ(CircularBufferSize(&cb), 1u);
}

// Tests that CircularBufferClear clears the circular buffer
TEST_F(CircularBufferTest, Empty) {
    uint32_t data = 10u;

    CircularBufferClear(&cb);

    ASSERT_EQ(CircularBufferEmpty(&cb), true);
    ASSERT_EQ(CircularBufferPushBack(&cb, &data), 0u);
    ASSERT_EQ(CircularBufferEmpty(&cb), false);
    ASSERT_EQ(CircularBufferPopFront(&cb, &data), 0u);
    ASSERT_EQ(CircularBufferEmpty(&cb), true);
}

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
