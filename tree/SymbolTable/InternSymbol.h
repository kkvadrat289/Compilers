#ifndef INTERNSYMBOL_H
#define INTERNSYMBOL_H


#include <string>
#include <memory>
#include <unordered_map>

namespace STable {

enum VarType{
    T_INT,
    T_BOOL,
    T_INT_ARR,
    T_CLASS
};

class CInternSymbol {
public:
    static CInternSymbol* GetIntern(const std::string& name)
    {
        static std::unordered_map<std::string, std::unique_ptr<CInternSymbol>> strings;
        auto cached = strings.find(name);
        if (cached != strings.end()){
            return cached->second.get();
        }
        CInternSymbol* newVal = new CInternSymbol(name);
        strings[name] = std::unique_ptr<CInternSymbol>(newVal);
        return newVal;
    }

    const std::string& GetString()  {
        return body;
    }

private:
    std::string body;

    CInternSymbol(std::string name) : body(name) { }
    CInternSymbol(  CInternSymbol& ) = delete;
    void operator=( const CInternSymbol& ) = delete;
};

}


#endif // INTERNSYMBOL_H
