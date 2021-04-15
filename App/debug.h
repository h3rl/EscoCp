#include <iostream>



#ifdef _DEBUG

#define _D(x) std::cout << x << std::endl;
#define STRING(x) #x

#else

#define _D(x)
#define STRING(x)

#endif // _DEBUG

#ifdef DEBUG_EXTRA_INFO

#define _P(x) _D(x) 

#else

#define _P(x)

#endif // DEBUG_EXTRA_INFO


void createDbgConsole();
void _S(const char* txt);
void _S(std::string txt);
void _E(const char* txt);
void _E(std::string txt);

std::string stringifyStance(int stance);