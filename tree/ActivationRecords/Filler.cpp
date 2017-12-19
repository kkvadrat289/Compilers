#include "Filler.h"

#include <iostream>
#include "assert.h"
#include "X86MiniJavaFrame.h"

namespace Records {

void FrameFiller::Fill()
{
    assert(!filled);
    auto classNames = table->GetClassesNames();
    for(auto className : classNames) {
        Position position;
        table->AddNewClass(className->GetString());
        auto classInfo = table->getClassInfo(className->GetString());
        auto methods = classInfo->GetMethods();
        for(auto method: methods) {
            auto methodInfo = table->GetMethodInfo(method->GetString(), position);
            std::unique_ptr<IFrame> frame(new X86MiniJavaFrame());
            STable::CVariableInfo thisVariable("this", classInfo->GetTypeInfo(), position);
            frame->AddFormal(thisVariable);
            auto argNames = methodInfo->GetArgs();
            for (auto name : argNames) {
                frame->AddFormal(*name);
            }
            auto localNames = methodInfo->GetVars();
            for(auto name : localNames) {
                frame->AddLocal(*name);
            }
            frame->AddAddressExit();
            frame->AddAddressReturnValue(methodInfo->GetReturnType()->GetType());
            std::cout << methodInfo->GetName()->GetString() << std::endl;
            auto activation = frame->FindLocalOrFormal(STable::CInternSymbol::GetIntern("this"));
            std::cout << "this ";
            activation->print(frame->FP());
            for( auto name: argNames) {
                auto activation = frame->FindLocalOrFormal(name);
                std::cout << name->GetString() << " ";
                activation->print(Temp(0));
            }
            std::cout << "FP: " << frame->FP().GetAddress() << std::endl;
            for( auto name: localNames) {
                auto activation = frame->FindLocalOrFormal(name);
                std::cout << name->GetString() << " ";
                activation->print(frame->FP());
            }
            std::cout << "SP: " << frame->SP().GetAddress() << std::endl;
            std::cout << "Return address: ";
            frame->ReturnAddress()->print(Temp(0));
            std::cout << "Exit address: ";
            frame->ExitAddress()->print(Temp(0));
        }
        table->FreeLastScope();
    }
    filled = true;
}

}
