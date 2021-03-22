#include "ast/functions/ast_functionDeclarator.hpp"

// Constructors
// Using a ParamListPtr for params to have scalability, currently will be empty for main()
FunctionDeclarator::FunctionDeclarator(NodePtr id, NodeListPtr params)
{
  branches.push_back(id);
  branches.push_back(params);
}

FunctionDeclarator::FunctionDeclarator(NodePtr id, std::vector<NodePtr> params)
  : FunctionDeclarator(id, new NodeList(params))
{}

// Should work for `main()`
FunctionDeclarator::FunctionDeclarator(NodePtr id)
  : FunctionDeclarator(id, new NodeList())
{}

// Destructor, not 100% sure if correct
FunctionDeclarator::~FunctionDeclarator()
{
  delete branches[0];
  delete branches[1];
}

//This is where things should be
NodePtr FunctionDeclarator::getIdentifier() const
{
  return branches[0];
}

NodePtr FunctionDeclarator::getParams() const
{
  return branches[1];
}

std::string FunctionDeclarator::getId() const
{
  return branches[0]->getId();
}

bool FunctionDeclarator::isFunction() const
{
  return true;
}

// Visualising
void FunctionDeclarator::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Function Declarator [" << std::endl;
  dst << indent << "Identifier: " << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "Parameters: " << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

void FunctionDeclarator::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  std::string id = branches[0]->getId();
  // Macro, check this <-(seems to be working pog)
  dst << ".globl " << id << std::endl;
  // Function label
  dst << id << ":" << std::endl;
  // Storing ra and fp, updating frame pointer
  dst << "addiu $29,$29,-8" << std::endl;
  dst << "sw $30,0($29)" << std::endl;
  dst << "sw $31,4($29)" << std::endl;
  dst << "move $30,$29" << std::endl;
  // Process params
  stackFrame newFrame;
  int paramSize = 0;
  NodePtr param = branches[1]->getNode(0);
  while(param != NULL){
    int i = 0;
    std::string var = param->getId();
    int size = param->getSize();
    newFrame.varBindings[var] = {size, paramSize+8, -1};
    if(i < 4){
      newFrame.varBindings[var].reg = i+4; // First 4 arguments stored in registers $4-$7
      dst << "sw $" << i+4 << "," << paramSize+8 << "($30)" << std::endl; // The first 4 args aren't actually stored in the right place
    }
    paramSize += size;
    context.functions[id].argSize.push_back(size);
    i++;
    param = branches[1]->getNode(i);
  }
  if(paramSize < 16 || paramSize > 0){
    paramSize = 16;
  }
  context.functions[id].size = paramSize;
  context.stack.push_back(newFrame);
  // branches[1]->generateMIPS(dst, context, destReg);
}
