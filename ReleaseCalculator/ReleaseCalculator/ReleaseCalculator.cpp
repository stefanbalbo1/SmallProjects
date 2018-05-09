// ReleaseCalculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "ReleaseCalculator.h"
#include <chrono>

bool ReleaseCalculator::GetDate(std::tm &date)
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

bool ReleaseCalculator::CalculateRelease()
{
  std::cout << "Release Date Calculator\n";
  std::cout << "Release Date Calculator\n";
  std::cout << "Release Start Date (MM//DD//YYYY): ";
  std::tm releaseStart { 0 };
  if (!GetDate(releaseStart))
    return false;
  
  int nIterations;
  std::cout << "\n\nOutput written to C:\\temp\\ReleasePlan.txt\n\n";
  return true;
}


