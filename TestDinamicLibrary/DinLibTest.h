
#pragma once
#pragma pack(push,4)
 
#ifdef TESTDINAMICLIBRARY_EXPORTS
#define TESTDINAMICLIBRARY_DLL __declspec(dllexport)
#else
#define TESTDINAMICLIBRARY_DLL
#endif


extern "C" {
TESTDINAMICLIBRARY_DLL int GetLastSum();
}

extern "C" {
TESTDINAMICLIBRARY_DLL int CalculateSum(int a, int b);
}


class TESTDINAMICLIBRARY_DLL DinLibTest
{
public:
  DinLibTest();
  ~DinLibTest();

  int GetA();
  void SetA(int _a = 0);

private:
  int a;
};

extern TESTDINAMICLIBRARY_DLL int Var;
TESTDINAMICLIBRARY_DLL void Function(int, int);