#include <Regex/NmeaParser.h>

#include <regex>

namespace nmeaParser
{
// student code begin
std::optional<GpsCoordinates> parseNmeaGpsCoordinates(const std::string &nmeaMessage)
{
    std::regex pattern(R"(GNGGA,\d{6}(?:\.\d+)?,(\d{2})(\d{2}(?:\.\d+)?),([NS]),(\d{3})(\d{2}(?:\.\d+)?),([EW]),([0-6]))");
    std::smatch match;

    if (std::regex_search(nmeaMessage, match, pattern) && match.size() == 8)
    {
        GpsCoordinates coords;

        double latDeg = std::stod(match[1].str());
        double latMin = std::stod(match[2].str());

        if (latDeg > 90.0 || latMin >= 60.0)
        {
            return std::nullopt;
        }

        coords.latitude = latDeg + (latMin / 60.0);

        if (match[3].str() == "S")
        {
            coords.latitude = -coords.latitude;
        }
        double lonDeg = std::stod(match[4].str());
        double lonMin = std::stod(match[5].str());

        if (lonDeg > 180.0 || lonMin >= 60.0)
        {
            return std::nullopt;
        }

        coords.longitude = lonDeg + (lonMin / 60.0);

        if (match[6].str() == "W")
        {
            coords.longitude = -coords.longitude;
        }

        int qualityVal = std::stoi(match[7].str());
        coords.quality = static_cast<FixQuality>(qualityVal);

        return coords;
    }
    return std::nullopt;
}
// student code end
}  // namespace nmeaParser