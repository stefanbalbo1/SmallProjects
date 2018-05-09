#pragma once
#include <ctime>

class ReleaseCalculator
{
public:
  ReleaseCalculator() {};
  bool CalculateRelease();
protected:
  bool GetDate(std::tm & date);

};