#ifndef ast_functionDeclarator_hpp
#define ast_functionDeclarator_hpp

#include "ast/ast_node.hpp"
#include "ast/lists/ast_nodeList.hpp"

class FunctionDeclarator
  : public Node
{
public:
  // Constructors
  FunctionDeclarator(NodePtr id, NodeListPtr params);
  FunctionDeclarator(NodePtr id, std::vector<NodePtr> params);
  // Should work for `main()`
  FunctionDeclarator(NodePtr id);

  // Destructor, not 100% sure if correct
  virtual ~FunctionDeclarator();

  //This is where things should be
  NodePtr getIdentifier() const;
  NodePtr getParams() const;

  virtual std::string getId() const override;
  virtual bool isFunction() const override;

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
