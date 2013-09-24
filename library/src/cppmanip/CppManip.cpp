#include "CppManip.hpp"
#include "ClangFunctionExtractorFactory.hpp"
#include "Renamer.hpp"

namespace cppmanip
{

SourceReplacements extractFunctionInFile(const std::string& functionName, SourceSelection selection, const std::string& filename)
{
    auto extractor = ClangFunctionExtractorFactory().createFunctionExtractor();
    return extractor->extractFunctionInFile(functionName, selection, filename);
}

SourceReplacements renameLocalVariableInFile(const RenameLocalVariableRequest& request)
{
    auto renamer = RenamerFactory().createClangRenamer();
    return renamer->renameLocalVariableInFile(request);
}

}
