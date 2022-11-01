#include "Pif.h"

const std::vector<std::pair<std::string, std::string>>& Pif::get_pif() const {
    return m_pif;
}

void Pif::push(const std::string& key, const std::string& value) {
    m_pif.push_back(std::make_pair( key, value ));
}
