#ifndef JSON_CONFIG_READER_HPP
#define JSON_CONFIG_READER_HPP

#include "JsonConfigReaderBase.hpp"

// JsonConfigReader is a derived class that implements open(), save(), and fillConfig()
// for a specific JSON format.
class JsonConfigReader : public JsonConfigReaderBase {
public:
    // Returns the singleton instance for this derived class.
    static JsonConfigReader& getInstance() {
        static JsonConfigReader instance;
        return instance;
    }
    
    // Override the pure virtual functions.
    virtual bool open(const std::string& filePath) override;
    virtual bool save(const std::string& filePath) override;
    virtual bool fillConfig() override;
    
private:
    JsonConfigReader() {}  // Private constructor for singleton.
    
    // Delete copy constructor and assignment operator.
    JsonConfigReader(const JsonConfigReader&) = delete;
    JsonConfigReader& operator=(const JsonConfigReader&) = delete;
};

#endif // JSON_CONFIG_READER_HPP
