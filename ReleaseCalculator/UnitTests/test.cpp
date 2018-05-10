#include "pch.h"
#include "../ReleaseCalculator/ReleaseCalculator.h"


bool DateEqual(std::tm date1, std::tm date2)
{
  return (date1.tm_mday == date2.tm_mday && date1.tm_mon == date2.tm_mon && date1.tm_year == date2.tm_year);
}

TEST(DummyTestCase, DummuTest) 
{
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(ReleaseCalculator, Date2DayNumber)
{
  ReleaseCalculator rc;

  EXPECT_EQ(rc.Date2DayNumber(std::tm{ 0,0,0,1,3,0 }), 0);   // 1. March 0 is the base date
  EXPECT_EQ(rc.Date2DayNumber(std::tm{ 0,0,0,10,3,0 }), 9);
  EXPECT_EQ(rc.Date2DayNumber(std::tm{ 0,0,0,1,4,0 }), 31);
  EXPECT_EQ(rc.Date2DayNumber(std::tm{ 0,0,0,1,3,1 }), 365);

  EXPECT_EQ(rc.Date2DayNumber(std::tm{ 0,0,0,8,8,2019 }) - rc.Date2DayNumber(std::tm{ 0,0,0,9,5,2018 }), 456);
  EXPECT_EQ(rc.Date2DayNumber(std::tm{ 0,0,0,22,4,2017 }) - rc.Date2DayNumber(std::tm{ 0,0,0,1,1,2017 }), 111);
}

TEST(ReleaseCalculator, DayNumber2Date)
{
  ReleaseCalculator rc;
  
  EXPECT_TRUE(DateEqual(std::tm{ 0,0,0,1,3,0 }, rc.DayNumber2Date(0)));
  EXPECT_TRUE(DateEqual(std::tm{ 0,0,0,10,3,0 }, rc.DayNumber2Date(9)));
  EXPECT_TRUE(DateEqual(std::tm{ 0,0,0,1,4,0 }, rc.DayNumber2Date(31)));
  EXPECT_TRUE(DateEqual(std::tm{ 0,0,0,1,3,1 }, rc.DayNumber2Date(365)));

  EXPECT_TRUE(DateEqual(std::tm{ 0,0,0,16,7,2018 }, rc.DayNumber2Date(rc.Date2DayNumber(std::tm{ 0,0,0,18,6,2018 })+28)));
  EXPECT_TRUE(DateEqual(std::tm{ 0,0,0,9,5,2018 }, rc.DayNumber2Date(rc.Date2DayNumber(std::tm{ 0,0,0,9,5,2018 }))));
  EXPECT_TRUE(DateEqual(std::tm{ 0,0,0,14,9,1900 }, rc.DayNumber2Date(rc.Date2DayNumber(std::tm{ 0,0,0,24,2,1899 })+567)));

}
