#pragma once
#include <ctime>
#include <fstream>
#include <vector>

class ReleaseCalculator
{
public:
  ReleaseCalculator() : m_iterationLengths(48,4) {};
  bool CalculateRelease();
  int Date2DayNumber(const std::tm& date);
  std::tm DayNumber2Date(int dayNumber);
  void AddDays(std::tm &date, int days);
protected:
  bool EnterDate(std::tm & date);
  bool EnterIterations(int& nIterations);
  bool OutputRelease(const std::tm& startDate, int nIterations);
  void OutputDate(std::ofstream& outputFile, std::tm date);
  std::vector<int> m_iterationLengths;

};