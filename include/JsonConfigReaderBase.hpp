#ifndef JSON_CONFIG_READER_BASE_HPP
#define JSON_CONFIG_READER_BASE_HPP

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
// This project uses nlohmann/json (https://github.com/nlohmann/json)
// Licensed under the MIT License.

// Use ordered_json to preserve the input order when printing the configuration.
using json = nlohmann::ordered_json;

// JsonConfigReaderBase is an abstract base class for reading JSON configuration files.
// Derived classes must implement open() and fillConfig().
class JsonConfigReaderBase {
public:
    virtual ~JsonConfigReaderBase() = default;

    // Pure virtual functions: must be implemented in derived classes.
    virtual bool open(const std::string& filePath) = 0;
    virtual bool fillConfig() = 0;

    // Utility: print the entire loaded JSON configuration.
    // The JSON will be dumped in the same order as in the file thanks to
    // nlohmann::ordered_json.
    void printJsonConfig(std::ostream& os = std::cout) const {
        os << "---------------------\n";
        os << "[printJsonConfig activated]\n";
        os << "Below is the "
           << (configFilePath.empty() ? "<no file loaded>" : configFilePath)
           << " content:\n\n";
        os << jsonData.dump(4) << '\n';
        os << "---------------------\n";
    }

protected:
    // Protected helper functions for path processing.
    virtual std::string trim(const std::string& s) const {
        const std::string whitespace = " \t\n\r";
        size_t start = s.find_first_not_of(whitespace);
        size_t end = s.find_last_not_of(whitespace);
        if (start == std::string::npos || end == std::string::npos)
            return "";
        return s.substr(start, end - start + 1);
    }

    virtual std::string normalizePath(const std::string& path) const {
        std::string result = trim(path);
        while (result.find("//") != std::string::npos) {
            result.replace(result.find("//"), 2, "/");
        }
        return result;
    }

    std::string configFilePath{};  // path of the loaded configuration file
    json jsonData;
};

#endif // JSON_CONFIG_READER_BASE_HPP
