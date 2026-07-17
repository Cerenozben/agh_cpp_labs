#include <cstdint>  // uint32_t, uint64_t, etc.
#include <optional>
#include <string>

namespace nmeaParser
{

enum class FixQuality : uint8_t
{
    FIX_NOT_VALID = 0x00,         ///< Fix not valid
    GPS_FIX = 0x01,               ///< GPS fix
    DIFFERENTIAL_GPS_FIX = 0x02,  ///< Differential GPS fix (DGNSS), SBAS, OmniSTAR VBS, Beacon, RTX in GVBS mode
    NOT_APPLICABLE = 0x03,        ///< Not applicable
    RTK_FIXED = 0x04,             ///< RTK Fixed, xFill
    RTK_FLOAT = 0x05,             ///< RTK Float, OmniSTAR XP/HP, Location RTK, RTX
    INS_DEAD_RECKONING = 0x06,    ///< INS Dead reckoning
    INVALID = 0xff                ///< Invalid fix state (custom enumerator not defined by standard)
};

struct GpsCoordinates
{
    double latitude{};
    double longitude{};
    FixQuality quality{};

    bool operator==(const GpsCoordinates &other) const
    {
        return latitude == other.latitude && longitude == other.longitude && quality == other.quality;
    }
};

std::optional<GpsCoordinates> parseNmeaGpsCoordinates(const std::string &nmeaMessage);

}  // namespace nmeaParser
