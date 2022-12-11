#pragma once

#include <string>
#include <vector>

class Production
{
public:
    Production(const std::string& source, const std::vector<std::string>& destinations);

    std::string get_string() const;

    friend bool operator< (const Production& el, const Production& other);

    const std::string& source() const;
    const std::vector<std::string>& destinations() const;

private:
    std::string m_source;
    std::vector<std::string> m_destinations;
};

