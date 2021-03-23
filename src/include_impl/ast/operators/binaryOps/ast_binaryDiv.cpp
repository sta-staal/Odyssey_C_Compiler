#include "ast/operators/binaryOps/ast_binaryDiv.hpp"

void BinaryDiv::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary Division [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void BinaryDiv::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  int regLeft = DoLeft(dst, context, destReg);
  int regRight = DoRight(dst, context, destReg, regLeft);

  dst << "div $" << regLeft << ", $" << regRight << std::endl;

  dst << "mflo $" << destReg << std::endl;

  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}
 
