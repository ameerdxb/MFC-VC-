#ifdef EXPORT_DLL
#define EXPORTSYMBOL extern "C" __declspec(dllexport)

#else
#define EXPORTSYMBOL extern "C" __declspec(dllimport)
#endif

EXPORTSYMBOL int add(int,int);
EXPORTSYMBOL int sub(int,int);