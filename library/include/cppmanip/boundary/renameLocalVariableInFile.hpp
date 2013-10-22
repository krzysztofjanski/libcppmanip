#ifndef CPPMANIP_RENAME_LOCAL_VARIABLE_IN_FILE_HPP
#define CPPMANIP_RENAME_LOCAL_VARIABLE_IN_FILE_HPP
#include "SourceReplacement.hpp"

namespace cppmanip
{
namespace boundary
{
SourceReplacements renameLocalVariableInFile(
    std::string fromName,
    std::string toName,
    SourceLocation locationOfLocalScope,
    std::string sourceFilename);
}
}

#endif//CPPMANIP_RENAME_LOCAL_VARIABLE_IN_FILE_HPP