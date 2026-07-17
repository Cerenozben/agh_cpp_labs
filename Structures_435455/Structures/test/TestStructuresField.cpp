
#include <Structures/Dictionary.h>
#include <gtest/gtest.h>

namespace
{
std::string demangle(const char *name);
std::string demangle(const char *name)
{
    int status = -4;
    std::unique_ptr<char, void (*)(void *)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};
    return (status == 0) ? res.get() : name;
}
}  // namespace

struct TestDerivDict : public dictionary::Dictionary
{
    auto &getItems() { return items_; };
    void addItems(const std::pair<std::string, dictionary::CustomVariant> &val) { items_.emplace(val); };
};

TEST(TestDictionary, Items)
{
    TestDerivDict testChild;
    EXPECT_EQ(
            demangle(typeid(testChild.getItems()).name()),
            "std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, std::variant<int, "
            "float, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, "
            "std::less<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const>, "
            "std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, "
            "std::variant<int, float, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > >");
}

TEST(TestDictionary, CustomVariant)
{
    EXPECT_EQ(demangle(typeid(dictionary::CustomVariant).name()),
              "std::variant<int, float, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >");
}

TEST(TestDictionary, DictionaryContainer)
{
    EXPECT_EQ(
            demangle(typeid(dictionary::DictionaryContainer).name()),
            "std::map<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, std::variant<int, "
            "float, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >, "
            "std::less<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const>, "
            "std::allocator<std::pair<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const, "
            "std::variant<int, float, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > >");
}

TEST(TestDictionary, CopyAssignmentItems)
{
    TestDerivDict testChild;
    testChild.addItems({"s", 1});
    TestDerivDict testChild2;
    testChild2 = testChild;
    testChild.addItems({"d", 2});
    EXPECT_EQ(testChild.getItems().size(), 2);
    EXPECT_EQ(testChild2.getItems().size(), 1);
    EXPECT_EQ(std::get<int>(testChild2.getItems()["s"]), 1);
}

TEST(TestDictionary, MoveAssignmentItems)
{
    TestDerivDict testChild;
    testChild.addItems({"s", 1});
    TestDerivDict testChild2;
    testChild2 = std::move(testChild);
    testChild.addItems({"d", 2});
    EXPECT_EQ(testChild.getItems().size(), 1);
    EXPECT_EQ(testChild2.getItems().size(), 1);
    EXPECT_EQ(std::get<int>(testChild2.getItems()["s"]), 1);
}

TEST(TestDictionary, CopyConstructor)
{
    TestDerivDict testChild;
    testChild.addItems({"s", 1});
    TestDerivDict testChild2{testChild};
    testChild.addItems({"d", 2});
    EXPECT_EQ(testChild.getItems().size(), 2);
    EXPECT_EQ(testChild2.getItems().size(), 1);
    EXPECT_EQ(std::get<int>(testChild2.getItems()["s"]), 1);
}

TEST(TestDictionary, MoveConstructor)
{
    TestDerivDict testChild;
    testChild.addItems({"s", 1});
    TestDerivDict testChild2{std::move(testChild)};
    testChild.addItems({"d", 2});
    EXPECT_EQ(testChild.getItems().size(), 1);
    EXPECT_EQ(testChild2.getItems().size(), 1);
    EXPECT_EQ(std::get<int>(testChild2.getItems()["s"]), 1);
}
