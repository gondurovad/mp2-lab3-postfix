#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, cant_create_postfix_with_incorrect_brackets)
{
	ASSERT_ANY_THROW(TPostfix p("(1+1"));
}

TEST(TPostfix, cant_create_postfix_with_incorrect_operations)
{
	ASSERT_ANY_THROW(TPostfix p("1+*1"));
}

TEST(TPostfix, cant_create_postfix_with_incorrect_start)
{
	ASSERT_ANY_THROW(TPostfix p("+1+1"));
}

TEST(TPostfix, can_create_copied_postfix)
{
	string a = "1+1";
	TPostfix p(a);
	EXPECT_EQ(a, p.GetInfix());
}

TEST(TPostfix, can_get_infix)
{
	TPostfix p("1+1");
	EXPECT_EQ("1+1", p.GetInfix());
}

TEST(TPostfix, can_get_postfix)
{
	TPostfix p("1+1");
	p.ToPostfix();
	EXPECT_EQ("1 1 +", p.GetPostfix());
}

TEST(TPostfix, can_create_right_postfix)
{
	TPostfix p("1+1");
	EXPECT_EQ("1 1 +", p.ToPostfix());
}

TEST(TPostfix, can_calculate_postfix)
{
	TPostfix p("1+1");
	string st = p.ToPostfix();
	EXPECT_EQ(2, p.Calculate(st));
}
