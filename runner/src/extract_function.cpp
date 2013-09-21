#include "CommandLineParser.hpp"
#include <CppManip.hpp>
#include <ExtractMethodError.hpp>
#include <stdexcept>
#include <iostream>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <fstream>
#include <SourceReplacementSerialization.hpp>

const std::string REPLACEMENTS_FILE = "replacements.xml";
const std::string ERROR_FILE = "errors.xml";

void saveReplacements(SourceReplacements replacements)
{
    std::ofstream of(REPLACEMENTS_FILE);
    boost::archive::xml_oarchive oa(of);
    oa << boost::serialization::make_nvp("replacements", replacements);
}

void saveError(const std::string& error)
{
    std::ofstream of(ERROR_FILE);
    boost::archive::xml_oarchive oa(of);
    oa << boost::serialization::make_nvp("error", error);
}

int main(int argc, const char** argv)
{
    try
    {
        CommandLineParser parser;
        auto req = parser.parseExtractFunction(argc, argv);
        SourceReplacements replacements;
        try
        {
            for (auto loc : req.locations)
            {
                boost::push_back(replacements, extractFunctionInFile(loc.extractedMethodName, loc.sourceSelection, req.sourceFilename));
            }
            saveReplacements(replacements);
        }
        catch (const ExtractMethodError& e)
        {
            saveError(e.what());
        }
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
}
