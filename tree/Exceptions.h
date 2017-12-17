#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

class DeclarationException : public std::exception {
public:
    DeclarationException(const std::string& message);
    virtual ~DeclarationException() throw() {}
    virtual char const* what() const noexcept override;
private:
    std::string msgresult;
};

#endif // EXCEPTIONS_H
