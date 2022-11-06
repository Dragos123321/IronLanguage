#include "Scanner.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

std::vector<std::string> split_string(const std::string& line);

Scanner::Scanner(const std::string& path, const std::string& tokens_file) : m_path{ path }
{
    std::ifstream in(tokens_file);
    std::string token;

    while (in >> token) {
        m_tokens.push_back(token);
    }
}

std::vector<std::string> operators{ "<", ">", "!", "+", "-", "*", "/" };
std::vector<std::string> keywords{ "char", "bool", "int", "uint", "string", "vec", "let", "and", "or", "if", "else", "while", "do", "for", "read", "print", "true", "false" };

void Scanner::create_intermediate_file()
{
    std::ifstream in(m_path);
    std::ofstream out(m_path + ".aux");
    std::string line;
    size_t pos = 0;

    while (std::getline(in, line, '\n')) {
        for (auto token : m_tokens) {
            if (token == ":" || std::find(keywords.begin(), keywords.end(), token) != keywords.end())
                continue;
            pos = line.find(token);
            while (pos != std::string::npos) {
                bool found_before_str = false;
                bool found_after_str = false;
                bool found_before_chr = false;
                bool found_after_chr = false;

                for (size_t i = 0; i < pos; ++i) {
                    if (line[i] == '"') {
                        found_before_str = true;
                        break;
                    }
                    if (line[i] == '\'') {
                        found_before_chr = true;
                        break;
                    }
                }

                for (size_t i = pos + 1; i < line.size(); ++i) {
                    if (line[i] == '"') {
                        found_after_str = true;
                        break;
                    }
                    if (line[i] == '\'') {
                        found_after_chr = true;
                        break;
                    }
                }

                if ((found_before_str && found_after_str) || (found_before_chr && found_after_chr)) {
                    pos += token.size();
                    pos = line.find(token, pos);
                }
                else {
                    if (token == "=") {
                        std::regex r_start("[^=<>!\+-/\*]");
                        std::regex r_end("[^=]");

                        if (pos > 0 && pos < line.size() - token.size() - 1) {
                            std::string pos_min_1 = "";
                            std::string pos_plus_1 = "";
                            pos_min_1.push_back(line[pos - 1]);
                            pos_plus_1.push_back(line[pos + 1]);

                            if (!(std::regex_match(pos_min_1, r_start) && std::regex_match(pos_plus_1, r_end))) {
                                pos += token.size();
                                pos = line.find(token, pos);
                                continue;
                            }
                        }
                        else if (pos > 0) {
                            std::string pos_min_1 = "";
                            pos_min_1.push_back(line[pos - 1]);

                            if (!std::regex_match(pos_min_1, r_start)) {
                                pos += token.size();
                                pos = line.find(token, pos);
                                continue;
                            }
                        }
                        else {
                            std::string pos_plus_1 = "";
                            pos_plus_1.push_back(line[pos + 1]);

                            if (!std::regex_match(pos_plus_1, r_end)) {
                                pos += token.size();
                                pos = line.find(token, pos);
                                continue;
                            }
                        }
                    }
                    if (std::find(operators.begin(), operators.end(), token) != operators.end()) {
                        if (pos < line.size() - 2) {
                            if (line[pos + 1] == '=') {
                                pos += 2;
                                continue;
                            }
                        }
                    }
                    line.insert(line.begin() + pos, ' ');
                    line.insert(line.begin() + pos + 1 + token.size(), ' ');

                    pos += token.size() + 2;
                    pos = line.find(token, pos);
                }
            }
        }

        out << line << '\n';
    }

    m_path += ".aux";
}

std::pair<bool, std::pair<int, std::string>> Scanner::try_parse()
{
    create_intermediate_file();
    std::ifstream in(m_path);
    std::string line;
    int line_index = 0;

    while (std::getline(in, line, '\n')) {
        std::vector<std::string> elems = split_string(line);

        for (auto el : elems) {
            if (std::find(m_tokens.begin(), m_tokens.end(), el) != m_tokens.end()) {
                m_pif.push(el, "-1");
            }
            else {
                if (el.size() < 1)
                    continue;
                if (el[el.size() - 1] == '(') {
                    el.pop_back();

                    if (!(el == "print" || el == "read" || el == "vec")) {
                        return std::make_pair(false, std::make_pair(line_index, el));
                    }

                    m_pif.push(el, "-1");
                    m_pif.push("(", "-1");
                }
                else if (el[el.size() - 1] == '[') {
                    el.pop_back();

                    std::regex regex("^([a-zA-Z]|_)[a-zA-Z_0-9]*$");

                    if (!std::regex_match(el, regex)) {
                        return std::make_pair(false, std::make_pair(line_index, el));
                    }

                    size_t nr_pif = m_symTable.add(el);

                    m_pif.push("id", std::to_string(nr_pif));
                    m_pif.push("[", "-1");
                }
                else if (el[el.size() - 1] == ';') {
                    el.pop_back();

                    if (std::find(m_tokens.begin(), m_tokens.end(), el) != m_tokens.end()) {
                        m_pif.push(el, "-1");
                        m_pif.push(";", "-1");
                        continue;
                    }

                    std::regex regex1("^-?[1-9][0-9]*|0|$");
                    std::regex regex2("^\'[a-zA-Z0-9]?\'$");
                    std::regex regex3("^\"[a-zA-Z0-9\{\}_]*\"$");
                    std::regex regex4("^([a-zA-Z]|_)[a-zA-Z_0-9]*$");

                    if (!(std::regex_match(el, regex1) ||
                        std::regex_match(el, regex2) ||
                        std::regex_match(el, regex3) ||
                        std::regex_match(el, regex4))) {
                        return std::make_pair(false, std::make_pair(line_index, el));
                    }

                    size_t nr_pif = m_symTable.add(el);

                    m_pif.push("id", std::to_string(nr_pif));
                    m_pif.push(";", "-1");
                }
                else if (el[el.size() - 1] == ':') {
                    el.pop_back();

                    std::regex regex("^([a-zA-Z]|_)[a-zA-Z_0-9]*$");

                    if (!std::regex_match(el, regex)) {
                        return std::make_pair(false, std::make_pair(line_index, el));
                    }

                    size_t nr_pif = m_symTable.add(el);

                    m_pif.push("id", std::to_string(nr_pif));
                    m_pif.push(":", "-1");
                }
                else if (el[el.size() - 1] == ',') {
                    el.pop_back();

                    if (std::find(m_tokens.begin(), m_tokens.end(), el) != m_tokens.end()) {
                        m_pif.push(el, "-1");
                        m_pif.push(";", "-1");
                        continue;
                    }

                    std::regex regex1("^-?[1-9][0-9]*|0|$");
                    std::regex regex2("^\'[a-zA-Z0-9]?\'$");
                    std::regex regex3("^\"[a-zA-Z0-9\{\}_]*\"$");
                    std::regex regex4("^([a-zA-Z]|_)[a-zA-Z_0-9]*$");

                    if (!(std::regex_match(el, regex1) || std::regex_match(el, regex2) || std::regex_match(el, regex3) || std::regex_match(el, regex4))) {
                        return std::make_pair(false, std::make_pair(line_index, el));
                    }

                    size_t nr_pif = m_symTable.add(el);

                    m_pif.push(el, std::to_string(nr_pif));
                    m_pif.push(",", "-1");
                }
                else {
                    if (std::find(m_tokens.begin(), m_tokens.end(), el) != m_tokens.end()) {
                        m_pif.push(el, "-1");
                        m_pif.push(";", "-1");
                        continue;
                    }

                    std::regex regex1("^-?[1-9][0-9]*|0|$");
                    std::regex regex2("^\'[a-zA-Z0-9]?\'$");
                    std::regex regex3("^\"[a-zA-Z0-9\{\}_]*\"$");
                    std::regex regex4("^([a-zA-Z]|_)[a-zA-Z_0-9]*$");
                    std::regex regex5("^-?[1-9][0-9]*|0\.\.([a-zA-Z]|_)[a-zA-Z_0-9]*$");

                    if (!(std::regex_match(el, regex1) || 
                          std::regex_match(el, regex2) || 
                          std::regex_match(el, regex3) || 
                          std::regex_match(el, regex4) ||
                          std::regex_match(el, regex5))) {
                        return std::make_pair( false, std::make_pair(line_index, el) );
                    }

                    size_t nr_pif = m_symTable.add(el);

                    m_pif.push("id", std::to_string(nr_pif));
                }
            }

            ++line_index;
        }
    }

    return std::make_pair( true, std::make_pair( -1, "" ) );
}

std::string Scanner::parse()
{
    auto parse_res = try_parse();

    if (parse_res.first == false) {
        return "lexical error | line: " + std::to_string(parse_res.second.first) + " error: " + parse_res.second.second;
    }
    
    std::ofstream out("../PIF.out");

    for (const auto& el : m_pif.get_pif()) {
        out << el.first << " " << el.second << '\n';
    }

    out.close();

    out.open("../ST.out");

    out << "Binary Search Tree\n";
    m_symTable.print(out);

    return "lexically correct";
}

const Pif& Scanner::get_pif() const
{
    return m_pif;
}

const SymbolTable& Scanner::get_symTable() const
{
    return m_symTable;
}

std::vector<std::string> split_string(const std::string& line) {
    std::istringstream ss(line);
    std::string current_str;
    std::vector<std::string> res;

    while (std::getline(ss, current_str, ' ')) {
        res.push_back(current_str);
    }

    return res;
}