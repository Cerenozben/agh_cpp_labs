#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace dictionary
{
// student code begin
using CustomVariant = std::variant<int, float, std::string>;
using DictionaryContainer = std::map<std::string, CustomVariant>;
struct Dictionary
{
    DictionaryContainer items_;

    static int cnt_;
    static int getObjCounter();

    Dictionary();
    Dictionary(const Dictionary &copyDictionary);
    Dictionary(Dictionary &&otherDictionary) noexcept;
    Dictionary &operator=(const Dictionary &otherDictionary);
    Dictionary &operator=(Dictionary &&otherDictionary) noexcept;
    ~Dictionary();

    Dictionary(std::initializer_list<std::pair<const std::string, CustomVariant>> initializer);
    CustomVariant &operator[](const std::string &key);

    const CustomVariant &operator[](const std::string &key) const;

    void pop(const std::string &key);
    std::vector<CustomVariant> values() const;

    std::vector<std::string> keys() const;

    Dictionary &operator+=(const Dictionary &other);
    Dictionary operator+(const Dictionary &other) const;

    std::string toJson() const;
};
// student code end

}  // namespace dictionary
