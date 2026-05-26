#include "evaluator.hh"
#include "../utils/errors.hh"

namespace ast {

int32_t Evaluator::visit(const IntegerLiteral &literal) {
  return literal.value;
}

int32_t Evaluator::visit(const StringLiteral &) {
  utils::error("cannot evaluate string literal");
}

int32_t Evaluator::visit(const BinaryOperator &binop) {
  int32_t left = binop.get_left().accept(*this);
  int32_t right = binop.get_right().accept(*this);
  switch (binop.op) {
    case o_plus:   return left + right;
    case o_minus:  return left - right;
    case o_times:  return left * right;
    case o_divide:
      if (right == 0) utils::error("division by zero");
      return left / right;
    case o_eq:  return left == right ? 1 : 0;
    case o_neq: return left != right ? 1 : 0;
    case o_lt:  return left < right  ? 1 : 0;
    case o_le:  return left <= right ? 1 : 0;
    case o_gt:  return left > right  ? 1 : 0;
    case o_ge:  return left >= right ? 1 : 0;
  }
  utils::error("unknown operator");
}

int32_t Evaluator::visit(const Sequence &seq) {
  const auto &exprs = seq.get_exprs();
  if (exprs.empty()) utils::error("cannot evaluate empty sequence");
  int32_t result = 0;
  for (auto expr : exprs)
    result = expr->accept(*this);
  return result;
}

int32_t Evaluator::visit(const Let &) {
  utils::error("cannot evaluate let expression");
}

int32_t Evaluator::visit(const Identifier &) {
  utils::error("cannot evaluate identifier");
}

int32_t Evaluator::visit(const IfThenElse &ite) {
  if (ite.get_condition().accept(*this))
    return ite.get_then_part().accept(*this);
  else
    return ite.get_else_part().accept(*this);
}

int32_t Evaluator::visit(const VarDecl &) {
  utils::error("cannot evaluate variable declaration");
}

int32_t Evaluator::visit(const FunDecl &) {
  utils::error("cannot evaluate function declaration");
}

int32_t Evaluator::visit(const FunCall &) {
  utils::error("cannot evaluate function call");
}

int32_t Evaluator::visit(const WhileLoop &) {
  utils::error("cannot evaluate while loop");
}

int32_t Evaluator::visit(const ForLoop &) {
  utils::error("cannot evaluate for loop");
}

int32_t Evaluator::visit(const Break &) {
  utils::error("cannot evaluate break");
}

int32_t Evaluator::visit(const Assign &) {
  utils::error("cannot evaluate assignment");
}

} // namespace ast
