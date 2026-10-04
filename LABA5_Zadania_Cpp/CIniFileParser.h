#pragma once

#include <string>
#include <unordered_map>

//---------------------------------------------------------------------------------------------------------------------

class CIniFileParser
{
private:
    using string = std::string;
    using MVariables = std::unordered_map<string, string>;  // {variable_name, value}
    using MData = std::unordered_map<string, MVariables>;   // {section_name, section_values}

    MData m_data{};                                         // ini file data stored in maps for easy lookup
    bool m_valid{false};                                    // file exists and file has been read and main data is valid

    const string* Find(const string& section, const string& variable) const;

public:
    explicit CIniFileParser(const string& fileName);

    bool IsValid() const;
    bool HasSection(const string& section) const;
    bool HasVariable(const string& section, const string& variable) const;
    
    string GetVariable(const string& section, const string& variable) const;
    const MVariables& GetVariables(const string& section) const;
};

//---------------------------------------------------------------------------------------------------------------------
