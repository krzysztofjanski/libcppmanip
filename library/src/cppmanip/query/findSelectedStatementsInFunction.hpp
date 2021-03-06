#ifndef CPPMANIP_9F771D23280342E49A56A67096A3B6E5_HPP
#define CPPMANIP_9F771D23280342E49A56A67096A3B6E5_HPP
#include <clang/Basic/SourceManager.h>
#include <clang/AST/Stmt.h>
#include <cppmanip/ast/Statement.hpp>
#include <cppmanip/ast/Function.hpp>

namespace cppmanip
{
namespace query
{

typedef std::function<bool(ast::StatementPtr)> IsStatementSelected;
ast::ScopedStatementRange findSelectedStatementsInFunction(
    const ast::Function& decl, IsStatementSelected isSelected);

}
}
#endif // CPPMANIP_9F771D23280342E49A56A67096A3B6E5_HPP
