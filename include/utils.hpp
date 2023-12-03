#include <boost/algorithm/string/split.hpp>
#include <exception>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

namespace utils {
    namespace fs = std::filesystem;
    namespace algo = boost::algorithm;

    template <typename ConvertibleToString>
        requires std::convertible_to<ConvertibleToString, std::string>
    std::ifstream open(const ConvertibleToString& path, std::ios_base::openmode mode = std::ios_base::in) {
        std::ifstream file{path, mode};
        if (!file.is_open()) {
            std::string err{"Unable to open file "};
            err.append(path);
            throw std::runtime_error(err);
        }
        return file;
    }

    inline std::vector<std::string> splitLines(std::ifstream& file, const char& delim = '\n') {
        std::vector<std::string> tokens;
        // std::stringstream fileContents;
        // fileContents << file.rdbuf();
        //
        // algo::split(tokens, fileContents.str(), [&delim](auto c) { return c == delim; });
        std::string line;
        while (std::getline(file, line)) {
            tokens.push_back(line);
        }
        return tokens;
    }

}  // namespace utils
