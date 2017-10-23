#include "ClassSeq.h"

CClassSeq::CClassSeq(std::shared_ptr<CClassSeq> prev, std::shared_ptr<CClass> newClass_):
    previousClasses(prev),
    newClass(newClass_)
{}
