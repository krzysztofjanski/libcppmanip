#include "Renamer.hpp"
#include "CppManip.hpp"

namespace cppmanip
{
    Renamer::~Renamer()
    {
    }

    struct ClangRenamer: Renamer
    {
        SourceReplacements renameLocalVariableInFile(const RenameLocalVariableRequest& request)
        {
            SourceReplacements replacements;
            return replacements;
        }
    };

    std::shared_ptr< Renamer > RenamerFactory::createClangRenamer()
    {
        return std::make_shared<ClangRenamer>();
    }
}