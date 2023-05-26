#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

namespace Utils
{
    std::vector<uint8_t> String2Vec(const std::string &s)
    {
        std::vector<uint8_t> ret(s.size());
        for (int i = 0; i < s.size(); ++i)
        {
            ret[i] = *reinterpret_cast<const uint8_t*>(s.data() + i);
        }
        return ret;
    }

    std::string String2Hex(const std::string &s, int column = 16)
    {
        std::string ret;
        auto vec = String2Vec(s);
        std::ostringstream stream;
        for (int i = 0; i < s.size(); ++i)
        {
            stream << "0x" << std::hex << int(vec[i]);
            ret += stream.str();
            stream.clear();
            if ((i + 1) % column)
            {
                ret += " ";
            }
            else
            {
                ret += "\n";
            }
        }
        return ret;
    }
}