#ifndef PRETTYPRINTER_H
#define PRETTYPRINTER_H

#include "Visitor.h"
#include <fstream>

class CPrettyprinter: public IVisitor
{
public:
    CPrettyprinter(std::string path);
    ~CPrettyprinter();
    void printEdge(const INode* from, const std::shared_ptr<INode> to);
    void printVertex(const INode *node, const std::string label);
    void printEdge(const INode* from, const std::shared_ptr<INode> to, const std::string label);
    void printEdge(std::string from, std::string to);
    void printEdge(std::string from, INode* to);
    void visit(const CBinExpression* node)  override;
    void visit(const CId* node)  override;
    void visit(const CTrue* node)  override;
    void visit(const CFalse* node)  override;
    void visit(const CClass* node)  override;
    void visit(const CMain* node)  override;
    void visit(const CMethod* node)  override;
    void visit(const CProgram* node)  override;
    void visit(const CBooleanExp* node)  override;
    void visit(const CIntegerExp* node)  override;
    void visit(const CAssignStatement* node)  override;
    void visit(const CIf* node)  override;
    void visit(const CNotExp* node)  override;
    void visit(const CCallMethod* node)  override;
    void visit(const CNewIntArray* node)  override;
    void visit(const CNewClassObject* node)  override;
    void visit(const CRandomAccessAssign* node)  override;
    void visit(const CLength* node)  override;
    void visit(const CPrintLine* node)  override;
    void visit(const CWhile* node)  override;
    void visit(const CStatements* node)  override;
    void visit(const CRandomAccess* node)  override;
    void visit(const CArg* node)  override;
    void visit(const CStatementSeq* node)  override;
    void visit(const CVariable* node)  override;
    void visit(const CThis* node) override;

private:
    std::ofstream out;

};

#endif // PRETTYPRINTER_H
