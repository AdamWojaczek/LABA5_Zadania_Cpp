#include "CIniFileParser.h"

#include <fstream>
#include "StrUtils.h"

//---------------------------------------------------------------------------------------------------------------------

CIniFileParser::CIniFileParser(const string& filepath)
{
    m_valid = false;
    bool error = false;
    
    std::ifstream file(filepath);

    if (!file)
        error = true;
    else
    {
        string line, currentSection;
        unsigned int sectionUnnamedVariableCounter = 0;

        while (std::getline(file, line) && !error)
        {
            StrUtils::StrTrim(line);
            if (!line.empty() && (line.front() != ';'))
            {
                if ((line.front() == '[') && (line.back() == ']'))
                {
                    currentSection = StrUtils::StrTrim(line.substr(1, line.size() - 2));
                    if (currentSection.empty())
                        error = true;
                    else
                    {
                        m_data[currentSection];
                        sectionUnnamedVariableCounter = 0;
                    }
                }
                else if (!currentSection.empty())
                {
                    const auto separator = line.find('=');
                    if (separator != string::npos)
                    {
                        string name = StrUtils::StrTrim(line.substr(0, separator));
                        string value = StrUtils::StrTrim(line.substr(separator + 1));
                        if (name.empty())
                            error = true;
                        else
                            m_data[currentSection][name] = value;
                    }
                    else
                        m_data[currentSection][StrUtils::UIntToStr(++sectionUnnamedVariableCounter)] = line;
                }
            }
        }
    }

    m_valid = !error;
}

//---------------------------------------------------------------------------------------------------------------------

bool CIniFileParser::IsValid() const
{
    return m_valid;
}

//---------------------------------------------------------------------------------------------------------------------

const std::string* CIniFileParser::Find(const string& section, const string& variable) const
{
    const string* result = nullptr;

    const auto sectionIter = m_data.find(section);
    if (sectionIter != m_data.end())
    {
        const auto variableIter = sectionIter->second.find(variable);   
        if (variableIter != sectionIter->second.end())
            result = &variableIter->second;
    }

    return result;
}

//---------------------------------------------------------------------------------------------------------------------

bool CIniFileParser::HasSection(const string& section) const
{
    return (m_data.find(section) != m_data.end());
}

//---------------------------------------------------------------------------------------------------------------------

bool CIniFileParser::HasVariable(const string& section, const string& variable) const
{
    return Find(section, variable);
}

//---------------------------------------------------------------------------------------------------------------------

std::string CIniFileParser::GetVariable(const string& section, const string& variable) const
{
    const string* value = Find(section, variable);
    return value ? *value : "";
}

//---------------------------------------------------------------------------------------------------------------------

auto CIniFileParser::GetVariables(const string& section) const -> const MVariables&
{
    static const MVariables emptyVariables{};
    
    const auto variables = m_data.find(section);
    if (variables != m_data.end())
        return variables->second;
    
    return emptyVariables;
}   

//---------------------------------------------------------------------------------------------------------------------
