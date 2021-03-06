#include <cppmanip/clangutil/getStmtOffsetRange.hpp>
#include "ParsedFunction.hpp"
#include <cppmanip/boundary/ExtractMethodError.hpp>
#include <gtest/gtest.h>
#include <clang/AST/Stmt.h>

using namespace testing;

namespace cppmanip
{
namespace clangutil
{
namespace test
{

struct Stmt
{
    std::string stmt;
    std::string extraDecl;
    Stmt(const std::string& stmt) : stmt(stmt) { }
    Stmt& withExtraDecl(const std::string& decl)
    {
        extraDecl = decl;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& os, const Stmt& s)
{
    os << "\"" << s.stmt << "\"";
    if (!s.extraDecl.empty())
        os << " with \"" << s.extraDecl << "\"";
    return os;
}

struct getStmtOffsetRangeTest : testing::TestWithParam<Stmt>
{
    std::unique_ptr<ParsedFunction> func;
    std::string extraDeclarations;
    std::string parsedSource;

    void parse(const std::string& source)
    {
        func.reset(new ParsedFunction(source));
        parsedSource = source;
    }

    void setExtraDeclarations(const std::string& decls)
    {
        extraDeclarations = decls;
    }

    ast::SourceOffsetRange getRangeFromSource(const std::string& source)
    {
        parse(source);
        return getStmtOffsetRange(func->getDecl()->getASTContext().getSourceManager(), **func->stmts());
    }

    ast::SourceOffsetRange getRangeFromStmt(const std::string& stmt)
    {
        return getRangeFromSource(extraDeclarations + " void dummy_function__() { " + stmt + "\n }"); // \n is needed because of clang bug
    }

    void expectStmtRangeIs(ast::SourceOffsetRange range, const std::string& phrase)
    {
        auto phraseOffset = parsedSource.find(phrase);
        ASSERT_EQ(ast::SourceOffsetRange(phraseOffset, phraseOffset + phrase.length()), range)
            << (*func->stmts())->getStmtClassName();
    }
};

TEST_F(getStmtOffsetRangeTest, should_handle_multiline_statements)
{
    auto range = getRangeFromSource("void dummy_function__() {\n  int\n x;\n}");
    ASSERT_EQ(ast::SourceOffsetRange(28, 35), range);
}

TEST_F(getStmtOffsetRangeTest, should_throw_an_exception_for_unknown_statement)
{
    auto source = "int dummy_function__() {\n  return 4 + 2;\n}";
    ASSERT_THROW(getRangeFromSource(source), boundary::ExtractMethodError);
}

TEST_P(getStmtOffsetRangeTest, should_find_correct_source_range_for_a_statement)
{
    setExtraDeclarations(GetParam().extraDecl);
    auto range = getRangeFromStmt(GetParam().stmt);
    expectStmtRangeIs(range, GetParam().stmt);
}

INSTANTIATE_TEST_CASE_P(
    should_find_correct_source_range_for_all_statements,
    getStmtOffsetRangeTest,
    Values(
        Stmt("int x;"),
        Stmt("int x  ;"),
        Stmt("int z = 7;"),
        Stmt("int z = f();").withExtraDecl("int f();"),
        Stmt("float f(3.0f);"),

        Stmt("f(3, 4);").withExtraDecl("void f(int, int);"),

        Stmt("o.f();").withExtraDecl("struct O { void f(); } o;"),

        Stmt("for (;;);"),
        Stmt("for (;;) f();").withExtraDecl("void f();"),
        Stmt("for (;;) { }"),
        Stmt("for (;;) int x = 3;"),

        Stmt("i += 4;").withExtraDecl("int i;"),
        Stmt("if (true) f(7);").withExtraDecl("void f(int);"),
        Stmt("{}"),
        Stmt(";"),
        Stmt("try { } catch(...) { }")
));

}
}
}
