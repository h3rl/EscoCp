#include <iostream>



#ifdef _DEBUG

#define _D(x) std::cout << x << std::endl;
#define STRING(x) #x

#else

#define _D(x)
#define STRING(x)

#endif // _DEBUG