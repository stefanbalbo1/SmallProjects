#pragma once
#include <ctime>

class ReleaseCalculator
{
public:
  ReleaseCalculator() {};
  bool CalculateRelease();
  int Date2DayNumber(const std::tm& date);
  std::tm DayNumber2Date(int dayNumber);
protected:
  bool EnterDate(std::tm & date);
  bool EnterIterations(int& nIterations);
  bool OutputRelease(const std::tm& startDate, int nIterations);

};