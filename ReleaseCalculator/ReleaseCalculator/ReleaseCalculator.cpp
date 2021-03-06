// ReleaseCalculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "ReleaseCalculator.h"
#include <chrono>


int ReleaseCalculator::Date2DayNumber(const std::tm &date)
{
  int m = (date.tm_mon + 9) % 12; // mar=0; feb ==11
  int y = date.tm_year - m / 10;  // if jan/feb year--
  return 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (date.tm_mday - 1);
}
 
std::tm ReleaseCalculator::DayNumber2Date(int dayNumber)
{
  
  int y = (10000 * (_int64)dayNumber + 14780) / 3652425;
  int yDay = dayNumber - (365 * y + y / 4 - y / 100 + y / 400);
  if (yDay < 0)
  {
    y--;
    yDay = dayNumber - (365 * y + y / 4 - y / 100 + y / 400);
  }

  int monIdx = (100 * yDay + 52) / 3060;
  std::tm date{ 0 };
  date.tm_mon = (monIdx + 2) % 12 + 1;
  date.tm_year = y + (monIdx + 2) / 12;
  date.tm_mday = yDay - (monIdx * 306 + 5) / 10 + 1;
  return date;
}

void ReleaseCalculator::AddDays(std::tm &date, int days)
{
  date = DayNumber2Date(Date2DayNumber(date) + days);
}

bool ReleaseCalculator::EnterDate(std::tm &date)
{
  int m,d,y;
  std::cin >> m; 
  if (std::cin.get() != '/') 
  {
    std::cout << "expected /\n";
    return false;
  }
  std::cin >> d; 
  if (std::cin.get() != '/') 
  {
    std::cout << "expected /\n";
    return false;
  }
  std::cin >> y; 

  date.tm_mday = d;
  date.tm_mon = m;
  date.tm_year = y;

  return true;
}

bool ReleaseCalculator::EnterIterations(int& nIterations)
{
  std::cout << "Number of Iterations (nn): ";
  std::cin >> nIterations;
  if (nIterations < 0 || nIterations > 99)
  {
    nIterations = 0;
    return false;
  }

  char customIterationLength('n');
  std::cout << "Custom Iteration Length (y/n): ";
  std::cin >> customIterationLength;
  if (customIterationLength == 'y')
  {
    for (int i = 0; i < nIterations; i++)
    {
      std::cout << "Iteration " << i+1 << " Length in Weeks (nn): ";
      std::cin >> m_iterationLengths[i];
    }
  }

  return true;
}



void ReleaseCalculator::OutputDate(std::ofstream& outputFile, std::tm date)
{
  outputFile << date.tm_mon << "\\" << date.tm_mday << "\\" << date.tm_year << " ";
}

bool ReleaseCalculator::OutputRelease(const std::tm& startDate, int nIterations)
{
  std::ofstream file("C:\\temp\\Releaseplan.txt");
  file << "Release Date Calculator\n";
  file << "Start Date: ";
  OutputDate(file, startDate);
  file << "\n";
  std::tm date(startDate);
  file << nIterations << " Iterations\n";

  for (auto i = 0; i < nIterations; i++)
  {
    OutputDate(file, date);
    file << "Iteration " << i+1 << " Start\n";
    
    if (i == nIterations - 1)
    {
      AddDays(date, (m_iterationLengths[i] - 1) * 7);
      OutputDate(file, date);
      file << "Feature Freeze (noon)\n";

      AddDays(date, 1);
      OutputDate(file, date);
      file << "Code Freeze (noon)\n";

      AddDays(date, 3);
    }
    else
      AddDays(date, m_iterationLengths[i] * 7 - 3);

    OutputDate(file, date);
    file << "Iteration " << i+1 << " Review / End\n";

    AddDays(date, 3);
  }
  OutputDate(file, date);
  file << "Burn-In Start\n";

  AddDays(date, 1);
  OutputDate(file, date);
  file << "Beta\n";

   OutputDate(file, date);
  file << "Public Holistic\n";

  AddDays(date, 3);
  OutputDate(file, date);
  file << "Doc Freeze for Installed Help\n";

  AddDays(date, 17);
  OutputDate(file, date);
  file << "Release Candidate (RC1)\n";

  AddDays(date, 14);
  OutputDate(file, date);
  file << "Handover to Release\n";

  AddDays(date, 10);
  OutputDate(file, date);
  file << "Public Availability\n";

  file.close();
  return true;
}

bool ReleaseCalculator::CalculateRelease()
{
  std::cout << "Release Date Calculator\n";
  std::cout << "Release Start Date (MM//DD//YYYY): ";
  std::tm releaseStart { 0 };
  if (!EnterDate(releaseStart))
    return false;
  int nIterations;
  if (!EnterIterations(nIterations))
    return false;
    
  if (!OutputRelease(releaseStart, nIterations))
    return false;
  
  std::cout << "\n\nOutput written to C:\\temp\\ReleasePlan.txt\n\n";
  return true;
}


