#ifndef ast_binaryORAss_hpp
#define ast_binaryORAss_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryORAss
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif

