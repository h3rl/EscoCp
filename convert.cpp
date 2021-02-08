#include "convert.h"

std::string sysToStd(System::String^ txt)
{
    msclr::interop::marshal_context context;
    return context.marshal_as<std::string>(txt);
}