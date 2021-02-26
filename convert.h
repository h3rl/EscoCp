#include <msclr\marshal_cppstd.h>
#include <string>

std::string sysToStd(System::String^ txt);
const char* sysToCstr(System::String^ txt);

#define caseStringify(x) case x: return std::string(#x).erase(0,3);
std::string vkToString(int vk);