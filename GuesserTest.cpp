/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(GuesserTest, distance)
{
	Guesser object("Secret");
	ASSERT_EQ( object.distance("Secret"), 0);
	ASSERT_EQ( object.distance("Dog"), 6);
	ASSERT_EQ( object.distance("Secrets"), 1);
	ASSERT_EQ( object.distance("Sec"), 3);
	ASSERT_EQ( object.distance("Sekret"), 1);	
}

TEST(GuesserTest, locked_out)
{
	Guesser object("Secret");
	ASSERT_FALSE(object.match("Secrettt"));
	object.match("Secret1");
	object.match("Secret2");
	object.match("Secret3");
	ASSERT_FALSE(object.match("Secret"));
}

TEST(GuesserTest, truncate_long_secret)
{
	Guesser object("This is a very long secret that should be truncated.");
	ASSERT_EQ( object.distance("This is a very long secret that "), 0);
}

TEST(GuesserTest, brute_force_lock)
{
	Guesser object("Secret");
	object.match("Secrettt");
	ASSERT_TRUE(object.match("Secret"));
}

TEST(GuesserTest, distance_two_no_lock)
{
	Guesser object("Secret");
	object.match("Secrpp");
	ASSERT_TRUE(object.match("Secret"));
}

TEST(GuesserTest, remaining_resets_on_match)
{
	Guesser object("Secret");
	object.match("Secret1");
	object.match("Secret2");
	object.match("Secret3");
	object.match("Secret");
	ASSERT_TRUE(object.match("Secret"));
}

TEST(GuesserTest, distance_capped_at_secret_length)
{
	Guesser object("Secret");
	ASSERT_EQ(object.distance("GGGGGGGGGGGGGGG"), 6);
}