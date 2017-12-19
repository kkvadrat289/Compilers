#include "PrettyPrinter.h"

CPrettyprinter::CPrettyprinter(std::string path){
    out.open(path);
    out << "digraph g {\n" /*<< "graph [ rankdir = LR ];" << */ << "\n";
}
CPrettyprinter::~CPrettyprinter(){
    out << "}";
    out.close();
}
void CPrettyprinter::visit(const CProgram* node) {
    this->printVertex(node, "Program: " + std::to_string(node->pos.Line) + " lines");
    node->main->accept(this);
    printEdge(node, node->main);
    for (auto el : node->classes){
        el->accept(this);
        printEdge(node, el);
    }
}
void CPrettyprinter::visit(const CMain* node)  {
    printVertex(node, "Main: " + std::to_string(node->pos.Line) );
    node->id->accept(this);
    printEdge(node, node->id);
    node->paramId->accept(this);
    printEdge(node, node->paramId, "paramId");
    for (auto statement : node->statements){
        statement->accept(this);
        printEdge(node, statement, "st"); //заимплементить для statement
    }
}
void CPrettyprinter::visit(const CClass* node)  {
    printVertex(node, "Class: " + std::to_string(node->pos.Line));
    node->id->accept(this);
    printEdge(node, node->id);
    for (auto method : node->methods){
        method->accept(this);
        printEdge(node, method);
    }
}
void CPrettyprinter::visit(const CId* node) {
    printVertex(node, "id:" + node->name + " : " + std::to_string(node->pos.Line));
}
void CPrettyprinter::visit(const CPrintLine* node) {
    printVertex(node, "println: " + std::to_string(node->pos.Line));
    node->object->accept(this);
    printEdge(node, node->object);
}
void CPrettyprinter::visit(const CCallMethod* node)  {
    printVertex(node, "callMethod:  " + std::to_string(node->pos.Line));
    node->id->accept(this);
    printEdge(node, node->id);
    node->expression->accept(this);
    printEdge(node, node->expression, "object");
    for (auto param : node->params){
        param->accept(this);
        printEdge(node, param, "param");
    }
}
void CPrettyprinter::visit(const CIntegerExp* node)  {
    printVertex(node, "int " + std::to_string(node->val) + " : " + std::to_string(node->pos.Line));

}
//проблемы с less
void CPrettyprinter::visit(const CBinExpression* node){
    printVertex(node, node->label +": " + std::to_string(node->pos.Line));
    node->left->accept(this);
    node->right->accept(this);
    printEdge(node, node->left, "left");
    printEdge(node, node->right, "right");
}
void CPrettyprinter::visit(const CTrue* node)  {
    printVertex(node, "True: " + std::to_string(node->pos.Line));
}
void CPrettyprinter::visit(const CFalse* node)  {
    printVertex(node, "False: " + std::to_string(node->pos.Line));
}


void CPrettyprinter::visit(const CMethod* node)  {
    printVertex(node, "method " + node->type->label + ": " + std::to_string(node->pos.Line));
    node->id->accept(this);
    printEdge(node, node->id);
    for (auto var : node->vars){
        var->accept(this);
        printEdge(node, var, "var");
    }
    for (auto statement : node->statements){
        statement->accept(this);
        printEdge(node, statement);
    }
    for (auto arg : node->params){
        arg->accept(this);
        printEdge(node, arg, "arg");
    }

    node->res->accept(this);
    printEdge(node, node->res, "return");
}

void CPrettyprinter::visit(const CBooleanExp* node) {
    printVertex(node, "bool " + std::to_string(node->val) + ": " + std::to_string(node->pos.Line));
}
void CPrettyprinter::visit(const CAssignStatement* node)  {
    printVertex(node, "=:  " + std::to_string(node->pos.Line));
    node->left->accept(this);
    node->right->accept(this);
    printEdge(node, node->left, "left");
    printEdge(node, node->right, "right");
}
void CPrettyprinter::visit(const CIf* node) {
    printVertex(node, "If:  " + std::to_string(node->pos.Line));
    node->cond->accept(this);
    printEdge(node, node->cond, "condition");
    node->ifFalse->accept(this);
    printEdge(node, node->ifFalse, "false");
    node->ifTrue->accept(this);
    printEdge(node, node->ifTrue, "true");
}

void CPrettyprinter::visit(const CNotExp* node) {
    printVertex(node, "NotExpression:  " + std::to_string(node->pos.Line));
    node->right->accept(this);
    printEdge(node, node->right);
}
void CPrettyprinter::visit(const CNewIntArray* node)  {
    printVertex(node, "new int[]: " + std::to_string(node->pos.Line));
    node->size->accept(this);
    printEdge(node, node->size, "size");
}
void CPrettyprinter::visit(const CNewClassObject* node)  {
    printVertex(node, "new:  " + std::to_string(node->pos.Line));
    node->id->accept(this);
    printEdge(node, node->id);
}
void CPrettyprinter::visit(const CRandomAccessAssign* node)  {
    printVertex(node, "=: " + std::to_string(node->pos.Line));
    node->id->accept(this);
    printEdge(node, node->id, "array");
    node->position->accept(this);
    printEdge(node, node->position, "position");
    node->expression->accept(this);
    printEdge(node, node->expression);
}
void CPrettyprinter::visit(const CLength* node)  {
    printVertex(node, "getLength:  " + std::to_string(node->pos.Line));
    node->object->accept(this);
    printEdge(node, node->object, "object");
}
void CPrettyprinter::visit(const CStatements* node)  {
    printVertex(node, "statements:  " + std::to_string(node->pos.Line));
    for (auto statement : node->statements){
        statement->accept(this);
        printEdge(node, statement);
    }
}
void CPrettyprinter::visit(const CRandomAccess* node) {
    printVertex(node, "AccessToPosition:  " + std::to_string(node->pos.Line));
    node->object->accept(this);
    node->position->accept(this);
    printEdge(node, node->object, "object");
    printEdge(node, node->position, "position");
}

void CPrettyprinter::visit(const CArg* node) {
    printVertex(node, node->type->label + ": " + std::to_string(node->pos.Line));
    node->id->accept(this);
    printEdge(node, node->id);
}
void CPrettyprinter::visit(const CStatementSeq* node) {}
void CPrettyprinter::visit(const CVariable* node)  {
    printVertex(node, node->type->label +" "+ node->id->name);
    //node->id->accept(this);

}
void CPrettyprinter::visit(const CThis* node) {
    printVertex(node, "this");
}
void CPrettyprinter::visit(const CWhile* node) {
    printVertex(node, "while");
    node->cond->accept(this);
    printEdge(node, node->cond, "condition");
    node->action->accept(this);
    printEdge(node, node->action, "action");
}

void CPrettyprinter::printEdge(const INode* from, const std::shared_ptr<INode> to){
    out << "\tnode" << from << "->" << "node" << to << "\n";
}

void CPrettyprinter::printVertex(const INode* node, const std::string label){
    out << "\tnode" << node << "[label=\"" << label << "\"]\n";
}

void CPrettyprinter::printEdge(const INode* from, const std::shared_ptr<INode> to, std::string label){
    out << "\tnode" << from << "->" << "node" << to << "[label=\"" << label << "\"]\n";
}

void CPrettyprinter::printEdge(std::string from, std::string to){
    out << "\t" << from << "->" << to << "\n";
}
void CPrettyprinter::printEdge(std::string from, INode* to){
    out << "\t"<< from << "->" << "node" << to << "\n";
}
