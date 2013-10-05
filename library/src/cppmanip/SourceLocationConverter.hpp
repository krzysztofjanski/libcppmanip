#ifndef CPPMANIP_1C57B55DCAEB439E9409ED2823E4F3B2_HPP
#define CPPMANIP_1C57B55DCAEB439E9409ED2823E4F3B2_HPP
#include <cppmanip/boundary/SourceLocation.hpp>
#include <string>

namespace cppmanip
{

class SourceLocationConverter
{
public:
    SourceLocationConverter(const std::string& source) : source(source) { }
    unsigned getOffsetFromLocation(boundary::SourceLocation loc) const;
private:
    std::string source;
    unsigned int calcRowOffset(unsigned int row) const;
};

}
#endif // CPPMANIP_1C57B55DCAEB439E9409ED2823E4F3B2_HPP
