#pragma once

#include <vector>
#include <string>

class Pif
{
public:
    Pif() = default;
    ~Pif() = default;

    const std::vector<std::pair<std::string, std::string>>& get_pif() const;

    void push(const std::string& key, const std::string& value);

private:
    std::vector<std::pair<std::string, std::string>> m_pif;
};

