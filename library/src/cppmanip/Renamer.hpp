#ifndef CPPMANIP_CLANG_RENAMER_HPP
#define CPPMANIP_CLANG_RENAMER_HPP

#include <cppmanip/SourceReplacement.hpp>
#include <memory>

namespace cppmanip
{
    class RenameLocalVariableRequest;

    struct Renamer
    {
        virtual ~Renamer() = 0;
        virtual SourceReplacements renameLocalVariableInFile(const RenameLocalVariableRequest& request) = 0;
    };
    
    class RenamerFactory
    {
    public:
        std::shared_ptr<Renamer> createClangRenamer();
    };
    
}

#endif//CPPMANIP_CLANG_RENAMER_HPP