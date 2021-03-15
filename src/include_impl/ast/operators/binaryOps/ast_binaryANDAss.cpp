#include "ast/operators/binaryOps/ast_binaryANDAss.hpp"

void BinaryANDAss::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary ANDAss [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+ "  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

