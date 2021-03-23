#include "ast/ast_identifier.hpp"

// Constructor
Identifier::Identifier(std::string _id)
  : id(_id)
{}

// Visualising
void Identifier::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Identifier: " << id << std::endl;
}

// Codegen
void Identifier::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // Only used if identifier for variable, used in evaluation
  std::string id = getId();
  variable tmp;

  // Ensures free register is used (pretty sure this will never be used)
  if(destReg == -1){
    destReg = context.allocate();
  }

  // Finds variable
  auto it = context.stack.back().varBindings.find(id);
  if( it == context.stack.back().varBindings.end() ){
    //variable doesnt exist in current frame !! -> handle globals later
    std::cerr << "Globals not yet implemented (or code is invalid lmao)" << std::endl;
    exit(1);
  }else{
    tmp = it->second;
  }

  // Puts variable in destReg
  if(tmp.reg == -1){
    dst << "lw $" << destReg << ", " << tmp.offset << "($30)" << std::endl;
  }else{
    // This is fucking gross, will discuss with kai to fix if time allows (find register variable is stored in in higher node)
    dst << "move $" << destReg << ", $" << tmp.reg << std::endl;
  }

}

// Getting identifier (codegen helper)
std::string Identifier::getId() const
{
  if(branches.empty()) { return id; }
  else{ return branches[0]->getId(); }
}
