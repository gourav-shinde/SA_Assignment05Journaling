#include "JournalCallParamDataString.h"
#include "JournalingInternal.h"
#include "JournalFile.h"


using namespace Journal;

std::string string_replace(std::string src, std::string const& target, std::string const& repl)
{
    // handle error situations/trivial cases

    if (target.length() == 0) {
        // searching for a match to the empty string will result in 
        //  an infinite loop
        //  it might make sense to throw an exception for this case
        return src;
    }

    if (src.length() == 0) {
        return src;  // nothing to match against
    }

    size_t idx = 0;

    for (;;) {
        idx = src.find(target, idx);
        if (idx == std::string::npos)  break;

        src.replace(idx, target.length(), repl);
        idx += repl.length();
    }

    return src;
}

JournalCallParamDataString::JournalCallParamDataString(std::string paramName,
    ParameterMetaType paramType, std::string value) :
    JournalCallParamData(paramName, paramType,
        JournalCallParamData::ParameterBasicType::STRING), m_value(value)
{

}

void JournalCallParamDataString::Journal()
{
    if (this->m_paramType == JournalCallParamData::ParameterMetaType::INPUT)
    {
        //There is a bug here, all \ in the string need to be replaced with \\
        // i.e. if d:\dir\some.prt  we need to actualy change this to 
        //         d:\\dir\\some.prt
        m_value = string_replace(m_value, "\\", "\\\\");
        std::string jnlString = "\"" + m_value + "\"";

        GetActiveJournalFile()->WriteToFile(jnlString);
    }
    else if (this->m_paramType == JournalCallParamData::ParameterMetaType::OUTPUT)
    {
        throw std::exception("NIY ");
    }
    else // RETURN
    {
        throw std::exception("NIY");
    }


}