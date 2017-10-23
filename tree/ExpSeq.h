#ifndef EXPSEQ_H
#define EXPSEQ_H

#include "Expression.h"

class CExpSeq{
public:
    CExpSeq(std::shared_ptr<CExpSeq> prev, std::shared_ptr<IExpression> last):
        previousExp(prev),
        lastExp(last)
    {}
private:
    std::shared_ptr<CExpSeq> previousExp;
    std::shared_ptr<IExpression> lastExp;
}

#endif // EXPSEQ_H
