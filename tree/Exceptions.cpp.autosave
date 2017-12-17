#include "Exceptions.h"


char const * DeclarationException::what() const noexcept{
    return msgresult.c_str();
}

DeclarationException::DeclarationException(const std::string& message){
    msgresult = message;
}
