#include "stdafx.h"
#include "DinLibTest.h"

////////////////////////////////Using functions://///////////
int lastSum = 0;

int GetLastSum()
{
  return lastSum;
}

int CalculateSum(int a, int b)
{
  lastSum = a + b;
  return lastSum;
}


////////////////////////////////Using DinLibTest class://///////////
DinLibTest::DinLibTest()
{
  a = 1;
}

DinLibTest::~DinLibTest()
{
}

int DinLibTest::GetA()
{
  return a;
}

void DinLibTest::SetA(int _a)
{
  a = _a;
}