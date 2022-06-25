//
// Created by Nastya on 15.05.2022.
//

#include <vector>
#include "../vector.hpp"
#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions) {
	// Expect two strings not to be equal.
	EXPECT_STRNE("hello", "world");
	// Expect equality.
	EXPECT_EQ(7 * 6, 42);
}