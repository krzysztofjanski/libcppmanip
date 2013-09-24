#ifndef CPPMANIP_B7961154F94A4B4090C2B1E100230246_HPP
#define CPPMANIP_B7961154F94A4B4090C2B1E100230246_HPP
#include <string>
#include <cppmanip/SourceSelection.hpp>
#include <cppmanip/SourceReplacement.hpp>
#include <cppmanip/ExtractMethodError.hpp>

namespace cppmanip
{

struct RenameLocalVariableRequest
{
    std::string sourceFilename;
    std::string nameFrom;
    std::string nameTo;
    SourceLocation locationOfLocalScope;
};

SourceReplacements extractFunctionInFile(const std::string& functionName, SourceSelection selection, const std::string& filename);
SourceReplacements renameLocalVariableInFile(const RenameLocalVariableRequest& request);

}
#endif // CPPMANIP_B7961154F94A4B4090C2B1E100230246_HPP
