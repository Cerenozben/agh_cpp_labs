#include <Regex/ComplexRegex.h>
#include <gtest/gtest.h>

namespace complexRegex
{

TEST(CountMatchesTest, EmptyWords)
{
    const std::string sentence = "Windows is the worst system in the world. Ubuntu is the best system in the world.";
    EXPECT_EQ(countMatches(sentence, std::vector<std::string>{}), 0);
}

TEST(CountMatchesTest, SingleWord)
{
    const std::string sentence = "Windows is the worst system in the world. Ubuntu is the best system in the world.";
    EXPECT_EQ(countMatches(sentence, std::vector<std::string>{"system"}), 2);
    EXPECT_EQ(countMatches(sentence, std::vector<std::string>{"Windows"}), 1);
    EXPECT_EQ(countMatches(sentence, std::vector<std::string>{"the"}), 4);
    EXPECT_EQ(countMatches(sentence, std::vector<std::string>{"Orange"}), 0);
}

TEST(CountMatchesTest, MultipleWords)
{
    const std::string sentence = "Windows is the worst system in the world. Ubuntu is the best system in the world.";
    EXPECT_EQ(countMatches(sentence, std::vector<std::string>{"system", "Windows"}), 3);
    EXPECT_EQ(countMatches(sentence, std::vector<std::string>{"system", "Ubuntu"}), 3);
    EXPECT_EQ(countMatches(sentence, std::vector<std::string>{"system", "Ubuntu", "Windows", "the"}), 8);
    EXPECT_EQ(countMatches(sentence, std::vector<std::string>{"Orange", "Apple", "Banana"}), 0);
    EXPECT_EQ(countMatches(sentence, std::vector<std::string>{"system", "Orange"}), 2);
}

TEST(CatchGroupSwapTest, NoMatch)
{
    const std::string sentence = "Windows is the worst system in the world. Ubuntu is the best system in the world.";
    EXPECT_EQ(swapCatchGroups(sentence, std::regex(R"(^(Orange).*(Ubuntu).*$)")), sentence);
    EXPECT_EQ(swapCatchGroups(sentence, std::regex(R"(^([0-9]+).*([a-z]{3}).*$)")), sentence);
}

TEST(CatchGroupSwapTest, MoreThanTwoMatches)
{
    const std::string sentence = "Windows is the worst system in the world. Ubuntu is the best system in the world.";
    EXPECT_EQ(swapCatchGroups(sentence, std::regex(R"(^.*(Windows).*(system).*(world).*$)")), sentence);
}

TEST(CatchGroupSwapTest, ValidMatchFirst)
{
    const std::string sentence = "Ubuntu is the worst system in the world. Windows is the best system in the world.";
    const std::string expectedSentence = "Windows is the worst system in the world. Ubuntu is the best system in the world.";
    EXPECT_EQ(swapCatchGroups(sentence, std::regex(R"(^.*(Ubuntu).*(Windows).*$)")), expectedSentence);
}

TEST(CatchGroupSwapTest, ValidMatchSecond)
{
    const std::string sentence = "Windows is the best system in the world. Ubuntu is the worst system in the world.";
    const std::string expectedSentence = "Windows is the worst system in the world. Ubuntu is the best system in the world.";
    EXPECT_EQ(swapCatchGroups(sentence, std::regex(R"(^.*(best).*(worst).*$)")), expectedSentence);
}

TEST(CatchGroupSwapTest, ValidMatchThird)
{
    const std::string sentence = "Long number is 123456789. Short number is 357.";
    const std::string expectedSentence = "Short number is 357. Long number is 123456789.";
    EXPECT_EQ(swapCatchGroups(swapCatchGroups(sentence, std::regex(R"(^.*(Long).*(Short).*$)")),
                              std::regex(R"(^.*([0-9]{9}).*([0-9]{3}).*$)")),
              expectedSentence);
}

TEST(FillTemplateTest, TemplateSingleOccurrenceFirst)
{
    const std::string templateString = "My name is {name}. I am {years} years old.";
    const std::string expectedResult = "My name is Mike. I am 32 years old.";
    const std::map<std::string, std::string> args{{"name", "Mike"}, {"years", "32"}};
    EXPECT_EQ(fillTemplateString(templateString, args), expectedResult);
}

TEST(FillTemplateTest, TemplateSingleOccurrenceSecond)
{
    const std::string templateString = "Timestamp: {hour}:{minute}:{second} - recorded {type} packet.";
    const std::string expectedResult = "Timestamp: 22:17:33 - recorded UDP packet.";
    const std::map<std::string, std::string> args{{"hour", "22"}, {"minute", "17"}, {"second", "33"}, {"type", "UDP"}};
    EXPECT_EQ(fillTemplateString(templateString, args), expectedResult);
}

TEST(FillTemplateTest, TemplateMultipleOccurrences)
{
    const std::string templateString = "Rectangular coordinates: [({X},{Y}),({X},-{Y}),(-{X},-{Y}),(-{X},{Y})]";
    const std::string expectedResult = "Rectangular coordinates: [(2,3),(2,-3),(-2,-3),(-2,3)]";
    const std::map<std::string, std::string> args{{"X", "2"}, {"Y", "3"}};
    EXPECT_EQ(fillTemplateString(templateString, args), expectedResult);
}

TEST(FillTemplateTest, TemplateNoOccurrences)
{
    const std::string templateString = "Unmatched argument: {unmatched}";
    const std::string expectedResult = "Unmatched argument: {unmatched}";
    const std::map<std::string, std::string> args{{"X", "2"}, {"Y", "3"}, {"name", "Mike"}};
    EXPECT_EQ(fillTemplateString(templateString, args), expectedResult);
}

TEST(SortTest, NoCatchGroup)
{
    std::vector<std::string> sentences{"LOGFILE_TIME_235959_DATE_20240511_INDEX_0003.txt",
                                       "LOGFILE_TIME_213700_DATE_20240518_INDEX_0004.txt",
                                       "LOGFILE_TIME_192402_DATE_20240512_INDEX_0002.txt",
                                       "LOGFILE_TIME_173406_DATE_20240421_INDEX_0001.txt"};

    const std::vector<std::string> expectedSentences{sentences};

    std::regex noCatchGroup(R"(^LOGFILE_TIME_\d{6}_DATE_\d{8}_INDEX_\d{4}.txt$)");
    EXPECT_FALSE(sortByCatchGroupValue(sentences, noCatchGroup));
    EXPECT_EQ(sentences, expectedSentences);
}

TEST(SortTest, MultipleCatchGroups)
{
    std::vector<std::string> sentences{"LOGFILE_TIME_235959_DATE_20240511_INDEX_0003.txt",
                                       "LOGFILE_TIME_213700_DATE_20240518_INDEX_0004.txt",
                                       "LOGFILE_TIME_192402_DATE_20240512_INDEX_0002.txt",
                                       "LOGFILE_TIME_173406_DATE_20240421_INDEX_0001.txt"};

    const std::vector<std::string> expectedSentences{sentences};

    std::regex multipleCatchGroup(R"(^LOGFILE_TIME_(\d{6})_DATE_(\d{8})_INDEX_(\d{4}).txt$)");
    EXPECT_FALSE(sortByCatchGroupValue(sentences, multipleCatchGroup));
    EXPECT_EQ(sentences, expectedSentences);
}

TEST(SortTest, ValidSortByTime)
{
    std::vector<std::string> sentences{"LOGFILE_TIME_235959_DATE_20240511_INDEX_0003.txt",
                                       "LOGFILE_TIME_213700_DATE_20240518_INDEX_0004.txt",
                                       "LOGFILE_TIME_192402_DATE_20240512_INDEX_0002.txt",
                                       "LOGFILE_TIME_173406_DATE_20240421_INDEX_0001.txt"};

    const std::vector<std::string> sortedSentences{"LOGFILE_TIME_173406_DATE_20240421_INDEX_0001.txt",
                                                   "LOGFILE_TIME_192402_DATE_20240512_INDEX_0002.txt",
                                                   "LOGFILE_TIME_213700_DATE_20240518_INDEX_0004.txt",
                                                   "LOGFILE_TIME_235959_DATE_20240511_INDEX_0003.txt"};

    std::regex timeCatchGroup(R"(^LOGFILE_TIME_(\d{6})_DATE_\d{8}_INDEX_\d{4}.txt$)");
    EXPECT_TRUE(sortByCatchGroupValue(sentences, timeCatchGroup));
    EXPECT_EQ(sentences, sortedSentences);
}

TEST(SortTest, ValidSortByDate)
{
    std::vector<std::string> sentences{"LOGFILE_TIME_235959_DATE_20240511_INDEX_0003.txt",
                                       "LOGFILE_TIME_213700_DATE_20240518_INDEX_0004.txt",
                                       "LOGFILE_TIME_192402_DATE_20240512_INDEX_0002.txt",
                                       "LOGFILE_TIME_173406_DATE_20240421_INDEX_0001.txt"};

    const std::vector<std::string> sortedSentences{"LOGFILE_TIME_173406_DATE_20240421_INDEX_0001.txt",
                                                   "LOGFILE_TIME_235959_DATE_20240511_INDEX_0003.txt",
                                                   "LOGFILE_TIME_192402_DATE_20240512_INDEX_0002.txt",
                                                   "LOGFILE_TIME_213700_DATE_20240518_INDEX_0004.txt"};

    std::regex timeCatchGroup(R"(^LOGFILE_TIME_\d{6}_DATE_(\d{8})_INDEX_\d{4}.txt$)");
    EXPECT_TRUE(sortByCatchGroupValue(sentences, timeCatchGroup));
    EXPECT_EQ(sentences, sortedSentences);
}

TEST(SortTest, ValidSortByIndex)
{
    std::vector<std::string> sentences{"LOGFILE_TIME_235959_DATE_20240511_INDEX_0003.txt",
                                       "LOGFILE_TIME_213700_DATE_20240518_INDEX_0004.txt",
                                       "LOGFILE_TIME_192402_DATE_20240512_INDEX_0002.txt",
                                       "LOGFILE_TIME_173406_DATE_20240421_INDEX_0001.txt"};

    const std::vector<std::string> sortedSentences{"LOGFILE_TIME_173406_DATE_20240421_INDEX_0001.txt",
                                                   "LOGFILE_TIME_192402_DATE_20240512_INDEX_0002.txt",
                                                   "LOGFILE_TIME_235959_DATE_20240511_INDEX_0003.txt",
                                                   "LOGFILE_TIME_213700_DATE_20240518_INDEX_0004.txt"};

    std::regex timeCatchGroup(R"(^LOGFILE_TIME_\d{6}_DATE_\d{8}_INDEX_(\d{4}).txt$)");
    EXPECT_TRUE(sortByCatchGroupValue(sentences, timeCatchGroup));
    EXPECT_EQ(sentences, sortedSentences);
}

}  // namespace complexRegex