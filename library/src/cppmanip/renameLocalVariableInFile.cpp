#include <cppmanip/boundary/renameLocalVariableInFile.hpp>

namespace cppmanip
{
namespace boundary
{

class VariableReplace
{
public:
    VariableReplace(const std::string& toName);
    SourceReplacement createSourceReplacemen(const SourceLocation& location);
private:
    std::string toName;
};

VariableReplace::VariableReplace(const std::string& toName):
    toName(toName)
{
}

struct LocalScope
{
};

LocalScope getLocalScopeAroundLocation(const SourceLocation& locationOfLocalScope)
{
    return LocalScope();
}

typedef std::vector<SourceLocation> SourceLocations;

SourceLocations findOccurrenciesOfVariableInLocalScope(const std::string& name, const LocalScope& scope)
{
    return SourceLocations();
}

// TODO whether the toName does not appear already in local scope
// TODO whether the toName does not hide something from wider scope
SourceReplacements renameLocalVariableInFile(
    std::string fromName,
    std::string toName,
    SourceLocation locationOfLocalScope,
    std::string sourceFilename)
{
    auto localScope = getLocalScopeAroundLocation(locationOfLocalScope);
    auto variableOccurrencies = findOccurrenciesOfVariableInLocalScope(fromName, localScope);
    SourceReplacements replacements;
    VariableReplace replace(toName);
    for(auto variableOccurrency : variableOccurrencies)
    {
        replacements.push_back(replace.createSourceReplacemen(variableOccurrency));
    }
    return replacements;
}
}
}