#ifndef JSON_CONFIG_READER_BASE_HPP
#define JSON_CONFIG_READER_BASE_HPP

#include <string>
#include <nlohmann/json.hpp>
// This project uses nlohmann/json (https://github.com/nlohmann/json)
// Licensed under the MIT License.

using json = nlohmann::json;

// JsonConfigReaderBase is an abstract base class for reading and saving JSON configuration files.
// All functions open(), save(), and fillConfig() are pure virtual and must be implemented by derived classes.
class JsonConfigReaderBase {
public:
    virtual ~JsonConfigReaderBase() = default;
    
    // Pure virtual functions: must be implemented in derived classes.
    virtual bool open(const std::string& filePath) = 0;
    virtual bool save(const std::string& filePath) = 0;
    virtual bool fillConfig() = 0;
    
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
    
    // Computes weight using the formula:
    // Weight = (Xs) * (BR) * (integratedLuminosity) / (NEvt)
    double computeWeight(double Xs, double BR, int NEvt, double integratedLuminosity) {
        if (NEvt == 0)
            return 0.0;
        return Xs * BR * integratedLuminosity / NEvt;
    }
    
    json jsonData;
};

#endif // JSON_CONFIG_READER_BASE_HPP
