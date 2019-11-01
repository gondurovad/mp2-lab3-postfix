#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, cant_create_wrong_postfix)
{
	ASSERT_ANY_THROW(TPostfix p("(1+1"));
}

TEST(TPostfix, can_get_infix)
{
	TPostfix p("1+1");
	EXPECT_EQ("1+1", p.GetInfix());
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
