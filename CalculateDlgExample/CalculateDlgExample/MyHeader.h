#ifdef EXPORTDLL
	#define EXPORTSYMBOL extern "C" __declspec(dllexport)
#else
	#define EXPORTSYMBOL extern "C" __declspec(dllimport)
#endif

EXPORTSYMBOL int add(int , int);
