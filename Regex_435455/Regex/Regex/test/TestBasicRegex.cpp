#include <Regex/BasicRegex.h>
#include <gtest/gtest.h>

namespace basicRegex
{

TEST(ValidateEmailTest, ValidEmail)
{
    const std::string email = "example@example.com";
    EXPECT_TRUE(validateEmail(email));
}

TEST(ValidateEmailTest, InvalidEmail)
{
    const std::string email = "example@.com";
    EXPECT_FALSE(validateEmail(email));
}

TEST(ValidateEmailTest, NoAtSymbol)
{
    const std::string email = "example.com";
    EXPECT_FALSE(validateEmail(email));
}

TEST(ValidateEmailTest, NoDomainExtension)
{
    const std::string email = "example@example";
    EXPECT_FALSE(validateEmail(email));
}

TEST(RemoveWhitespaceTest, BasicTest)
{
    const std::string text = "  This is a test  with     white spaces   ";
    const std::string expected = "Thisisatestwithwhitespaces";
    const std::string result = removeWhitespace(text);
    EXPECT_EQ(result, expected);
}

TEST(RemoveWhitespaceTest, NewlineTest)
{
    const std::string text = "This\nis\na\ntest\nwith\nnewline\ncharacters\n";
    const std::string expected = "Thisisatestwithnewlinecharacters";
    const std::string result = removeWhitespace(text);
    EXPECT_EQ(result, expected);
}

TEST(RemoveWhitespaceTest, EmptyStringTest)
{
    const std::string text{};
    const std::string expected{};
    const std::string result = removeWhitespace(text);
    EXPECT_EQ(result, expected);
}

TEST(RemoveWhitespaceTest, OnlySpacesTest)
{
    const std::string text{"    "};
    const std::string expected{};
    const std::string result = removeWhitespace(text);
    EXPECT_EQ(result, expected);
}

TEST(ExtractDomainTest, ValidEmailSimple)
{
    const std::string email = "johndoe@example.com";
    const std::string domain = extractDomain(email);
    EXPECT_EQ(domain, "example.com");
}
TEST(ExtractDomainTest, ValidEmail)
{
    const std::string email = "John Doe johndoe@example.com";
    const std::string domain = extractDomain(email);
    EXPECT_EQ(domain, "example.com");
}

TEST(ExtractDomainTest, NoDomain)
{
    const std::string email = "John Doe @johndoe";
    const std::string domain = extractDomain(email);
    EXPECT_EQ(domain, "");
}

TEST(ExtractDomainTest, InvalidEmail)
{
    const std::string email = "John@ Doe";
    const std::string domain = extractDomain(email);
    EXPECT_EQ(domain, "");
}

}  // namespace basicRegex
