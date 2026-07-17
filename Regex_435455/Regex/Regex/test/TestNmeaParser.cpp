#include <Regex/NmeaParser.h>
#include <gtest/gtest.h>

namespace nmeaParser
{

struct TestNmeaParserParams
{
    const std::string sentence{};
    const bool valid{};
    const GpsCoordinates coordinates{};
};

class TestNmeaParser : public ::testing::TestWithParam<TestNmeaParserParams>
{};

TEST_P(TestNmeaParser, NmeaParsingTest)
{
    const auto [sentence, valid, expectedCoordinates] = GetParam();

    const auto &parsedCoordinateOpt = parseNmeaGpsCoordinates(sentence);
    EXPECT_EQ(parsedCoordinateOpt.has_value(), valid);
    if (parsedCoordinateOpt.has_value())
    {
        const auto &parsedCoordinateValue = parsedCoordinateOpt.value();
        EXPECT_NEAR(expectedCoordinates.latitude, parsedCoordinateValue.latitude, 1e-9);
        EXPECT_NEAR(expectedCoordinates.longitude, parsedCoordinateValue.longitude, 1e-9);
        EXPECT_EQ(expectedCoordinates.quality, parsedCoordinateValue.quality);
    }
}

INSTANTIATE_TEST_CASE_P(TestValidSequences,
                        TestNmeaParser,
                        ::testing::Values(TestNmeaParserParams{.sentence = "GNGGA,223831.45,4238.94181577,N,08309.18413513,W,4",
                                                               .valid = true,
                                                               .coordinates = GpsCoordinates{.latitude = 42.649030262833335,
                                                                                             .longitude = -83.15306891883333,
                                                                                             .quality = FixQuality::RTK_FIXED}},
                                          TestNmeaParserParams{.sentence = "GNGGA,223831.45,6238.94181577,S,04309.18413513,E,5",
                                                               .valid = true,
                                                               .coordinates = GpsCoordinates{.latitude = -62.649030262833335,
                                                                                             .longitude = 43.153068918833334,
                                                                                             .quality = FixQuality::RTK_FLOAT}},
                                          TestNmeaParserParams{.sentence = "GNGGA,223814.80,4238.94182389,N,08309.18413610,W,1",
                                                               .valid = true,
                                                               .coordinates = GpsCoordinates{.latitude = 42.649030398166666,
                                                                                             .longitude = -83.153068935,
                                                                                             .quality = FixQuality::GPS_FIX}}));

INSTANTIATE_TEST_CASE_P(
        TestInvalidSequences,
        TestNmeaParser,
        ::testing::Values(
                TestNmeaParserParams{.sentence = "GNGNA,223831.45,4238.94181577,N,08309.18413513,W,4", .valid = false},
                TestNmeaParserParams{.sentence = "GNGGA,22.3831.45,6238.94181577,S,04309.18413513,E,5", .valid = false},
                TestNmeaParserParams{.sentence = "GNGGA,223831.45,6238.94181.577,S,04309.18413513,E,5", .valid = false},
                TestNmeaParserParams{.sentence = "GNGGA,223831.45,6238.94181577,S,04309.18413.513,E,5", .valid = false},
                TestNmeaParserParams{.sentence = "GNGGA,223831.45,6238.94181577,G,04309.18413513,E,5", .valid = false},
                TestNmeaParserParams{.sentence = "GNGGA,223814.80,4238.94182389,N,08309.18413610,4", .valid = false}));

}  // namespace nmeaParser
