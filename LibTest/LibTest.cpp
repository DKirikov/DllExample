// LibTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdio>
#include <iostream>
#include <iomanip>


#include <windows.h>
 

#include "DinLibTest.h"



typedef int ( WINAPIV* LPFNDLLFUNC_GetLastSum ) ();
typedef int ( WINAPIV* LPFNDLLFUNC_CalculateSum ) (int, int);

int main(int argc, char* argv[])
{
  HINSTANCE hMyDLL = LoadLibraryW(L"testDinamicLibrary.dll");
 
  if (NULL == hMyDLL) 
  {
    std::cout << "LoadLibrary Error";
    std::cin.get();

    return 0;
  }
  
  ////////////////////////////////Using functions://///////////
  LPFNDLLFUNC_GetLastSum fnLastSum = (LPFNDLLFUNC_GetLastSum)GetProcAddress(hMyDLL, "GetLastSum");
  LPFNDLLFUNC_CalculateSum fnCalculateSum = (LPFNDLLFUNC_CalculateSum)GetProcAddress(hMyDLL, "CalculateSum");  

  if (NULL == fnLastSum)
  {
     std::cout << "GetProcAddress Error: fnLastSum";
     FreeLibrary( hMyDLL );
     return -1;
  }

  if (NULL == fnCalculateSum)
  {
     std::cout << "GetProcAddress Error: fnCalculateSum";
     FreeLibrary( hMyDLL );
     return -1;
  }
  
  std::cout << "Using functions:\n";
  std::cout << "last sum = " << fnLastSum() << "\n";
  std::cout << "3 + 4 = " << fnCalculateSum(3, 4) << "\n";
  std::cout << "last sum = " << fnLastSum() << "\n";
  std::cout << "1 + 2 = " << fnCalculateSum(1, 2) << "\n";
  std::cout << "last sum = " << fnLastSum() << "\n";

  ////////////////////////////////Using DinLibTest class://///////////
  ////////////////////////////////It's not recomended. Static lib is better. To find more, read an arcticle at https://rsdn.org/article/baseserv/dlluse.xml

  void (DinLibTest::*pConstructor)();
  (FARPROC &)pConstructor = GetProcAddress(hMyDLL, "??0DinLibTest@@QAE@XZ");//because ??0DinLibTest@@QAE@XZ is Constructor
  void (DinLibTest::*pDestructor)();
  (FARPROC &)pDestructor = GetProcAddress(hMyDLL, "??1DinLibTest@@QAE@XZ");//because ??1DinLibTest@@QAE@XZ is Destructor

  int (DinLibTest::*pGetA)();
  (FARPROC &)pGetA = GetProcAddress(hMyDLL, "?GetA@DinLibTest@@QAEHXZ");//because ?GetA@DinLibTest@@QAEHXZ is GetA
  void (DinLibTest::*pSetA)(int);
  (FARPROC &)pSetA = GetProcAddress(hMyDLL, "?SetA@DinLibTest@@QAEXH@Z");//because ?GetA@DinLibTest@@QAEHXZ is SetA

  //stack:
  char _c[sizeof(DinLibTest)];
  DinLibTest &c = *(DinLibTest *)_c;
  (c.*pConstructor)();
  int a = (c.*pGetA)();
  (c.*pSetA)(3);
  a = (c.*pGetA)();
  (c.*pDestructor)();

  std::cout << "\nUsing DinLibTest class:\n";
  std::cout << "a = " << a << "\n";

  //heap:
  char* _pc = new char[sizeof(DinLibTest)];
  DinLibTest *pc = (DinLibTest *)_pc;
  (pc->*pConstructor)();
  int a2 = (pc->*pGetA)();
  (pc->*pSetA)(7);
  a2 = (pc->*pGetA)();

  std::cout << "a2 = " << a2 << "\n";

  (pc->*pDestructor)();
  delete[] _pc;

  //free library
  FreeLibrary( hMyDLL );
  std::cin.get();

  return 0;
}