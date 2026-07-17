#include <GdbLab/ZAlgorithm.h>

#include <string>
#include <vector>

namespace gdbLab
{
std::vector<size_t> search(const std::string &text, const std::string &pattern)
{
    // Create concatenated string "P$T"
    std::string concat = pattern + "$" + text;
    auto l = concat.length();

    // Construct Z array
    std::vector<size_t> z(l);
    getZarr(concat, z);

    std::vector<size_t> ret;
    // now looping through Z array for matching condition
    for (size_t i = 0; i < l; ++i)
    {
        if (z[i] == pattern.length())
        {
            ret.emplace_back(i - pattern.length() - 1);
        }
    }
    return ret;
}

void getZarr(std::string str, std::vector<size_t> &z)
{
    auto n{str.length()};
    size_t l{};
    size_t r{};
    size_t k{};

    l = r = 0;
    for (size_t i = 1; i < n; ++i)
    {
        if (i > r)
        {
            l = r = i;
            while (r < n && str[r - l] == str[r])
            {
                r++;
            }
            z[i] = r - l;
            r--;
        }
        else
        {
            k = i - l;
            if (z[k] < r - i + 1)  // bad
            {
                z[i] = z[k];
            }
            else
            {
                l = i;
                while (r < n && str[r - l] == str[r])
                {
                    r++;
                }
                z[i] = r - l;
                r--;
            }
        }
    }
}

}  // namespace gdbLab
