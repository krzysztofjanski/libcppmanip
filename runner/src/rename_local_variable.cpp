#include <cppmanip/runner/CommandLineParser.hpp>
#include <iostream>
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <cppmanip/SourceReplacementSerialization.hpp>


using namespace cppmanip;
using namespace cppmanip::runner;

RenameLocalVariableRequest parseRequest(int argc, const char** argv)
{
    CommandLineParser parser;
    return parser.parseRenameLocalVariable(argc, argv);
}

const std::string REPLACEMENTS_FILE = "replacements.xml";

void saveReplacements(cppmanip::SourceReplacements replacements)
{
    std::ofstream of(REPLACEMENTS_FILE);
    boost::archive::xml_oarchive oa(of);
    oa << boost::serialization::make_nvp("replacements", replacements);
}

void renameLocalVariable(RenameLocalVariableRequest req)
{
    auto replacements = cppmanip::renameLocalVariableInFile(req);
    saveReplacements(replacements);
}

int main(int argc, const char** argv)
{
    try
    {
        auto req = parseRequest(argc, argv);
        renameLocalVariable(req);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Internal error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown internal error" << std::endl;
        return 1;
    }
    return 0;
}
