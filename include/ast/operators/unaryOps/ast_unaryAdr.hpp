#ifndef ast_unaryAdr_hpp
#define ast_unaryAdr_hpp

#include "ast/operators/ast_unaryOperation.hpp"

class UnaryAdr
    : public UnaryOperation
{
public:

    using UnaryOperation::UnaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif


