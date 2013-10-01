#ifndef CPPMANIP_96167AD230584C3EAA5F0BF303AB37C9_HPP
#define CPPMANIP_96167AD230584C3EAA5F0BF303AB37C9_HPP
#include "FunctionExtractor.hpp"
#include "text/TextModifier.hpp"

namespace cppmanip
{

class ClangFunctionExtractor : public FunctionExtractor
{
public:
    typedef std::function<boundary::SourceReplacements()> GetReplacements;
    typedef std::function<void()> RunTranslationUnitHandler;
    ClangFunctionExtractor(RunTranslationUnitHandler runTranslationUnitHandler, GetReplacements getReplacements)
        : runTranslationUnitHandler(runTranslationUnitHandler), getReplacements(getReplacements) { }
    virtual boundary::SourceReplacements extractFunctionInFile();
private:
    const RunTranslationUnitHandler runTranslationUnitHandler;
    const GetReplacements getReplacements;
};

}
#endif // CPPMANIP_96167AD230584C3EAA5F0BF303AB37C9_HPP
