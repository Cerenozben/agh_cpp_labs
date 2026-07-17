#include <Structures/Dictionary.h>

#include <cstdint>
#include <iostream>
#include <sstream>

namespace dictionary
{
// student code begin

int Dictionary::cnt_ = 0;
int Dictionary::getObjCounter()
{
    return cnt_;
}
Dictionary::Dictionary() : items_()
{
    cnt_++;
    std::cout << "default constructor\n";
}
Dictionary::Dictionary(const Dictionary &copyDictionary) : items_(copyDictionary.items_)
{
    cnt_++;
    std::cout << "copy constructor \n";
}
Dictionary::Dictionary(Dictionary &&otherDictionary) noexcept : items_(std::move(otherDictionary.items_))
{
    cnt_++;
    std::cout << "move constructor\n";
}
Dictionary &Dictionary::operator=(const Dictionary &otherDictionary)
{
    (void)otherDictionary;
    std::cout << "copy assignment \n";
    return *this;
}
Dictionary::~Dictionary()
{
    cnt_--;
    std::cout << "destructor\n";
}
Dictionary::Dictionary(std::initializer_list<std::pair<const std::string, CustomVariant>> initializer) : items_(initializer)
{
    cnt_++;
}
CustomVariant &Dictionary::operator[](const std::string &key)
{
    return items_[key];
}

const CustomVariant &Dictionary::operator[](const std::string &key) const
{
    return items_.at(key);
}

void Dictionary::pop(const std::string &key)
{
    items_.erase(key);
}
std::vector<CustomVariant> Dictionary::values() const
{
    std::vector<CustomVariant> valueList;
    for (const auto &entry : items_)
    {
        valueList.push_back(entry.second);
    }
    return valueList;
}
std::vector<std::string> Dictionary::keys() const
{
    std::vector<std::string> keysList;
    for (const auto &entry : items_)
    {
        keysList.push_back(entry.first);
    }
    return keysList;
}
Dictionary &Dictionary::operator+=(const Dictionary &other)
{
    for (const auto &entry : other.items_)
    {
        items_[entry.first] = entry.second;
    }
    return *this;
}
Dictionary Dictionary::operator+(const Dictionary &other) const
{
    Dictionary result = *this;
    result += other;
    return result;
}
std::string Dictionary::toJson() const
{
    std::string jsonStr = "{";
    bool isFirst = true;

    for (const auto &entry : items_)
    {
        if (!isFirst)
        {
            jsonStr += ",";
        }

        jsonStr += "\"" + entry.first + "\":";

        if (std::holds_alternative<int>(entry.second))
        {
            jsonStr += std::to_string(std::get<int>(entry.second));
        }
        else if (std::holds_alternative<float>(entry.second))
        {
            jsonStr += std::to_string(std::get<float>(entry.second));
        }
        else if (std::holds_alternative<std::string>(entry.second))
        {
            jsonStr += "\"" + std::get<std::string>(entry.second) + "\"";
        }

        isFirst = false;
    }

    jsonStr += "}";
    return jsonStr;
}
// student code end

}  // namespace dictionary