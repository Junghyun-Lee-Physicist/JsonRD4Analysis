#ifndef CONFIG_INTERFACE_HPP
#define CONFIG_INTERFACE_HPP

#include <string>
#include <map>

// Structure for period configuration.
struct PeriodConfig {
    int year;
    double lumi;
};

// Structure for sample configuration.
struct SampleConfig {
    double Xs;
    double BR;
    int NEvt;
    double Weight;
    //  --> If JSON Weight is null, we compute:
    //      (Xs * BR * integratedLuminosity / NEvt)
    bool isData;
};

// ConfigInterface is a singleton class that stores analysis configuration data.
// This class holds the configuration information read from the JSON file.
// It includes general configuration, period and sample information, and noise filters.
class ConfigInterface {
public:
    // Returns the singleton instance.
    static ConfigInterface& getInstance() {
        static ConfigInterface instance;
        return instance;
    }
    
    // Delete copy constructor and assignment operator.
    // These lines prevent copying of the singleton instance,
    // ensuring that only one instance exists throughout the application.
    ConfigInterface(const ConfigInterface&) = delete;
    ConfigInterface& operator=(const ConfigInterface&) = delete;
    //   --> [ delete ] operator prevent to use copy and assignment operator

    // Configuration data members.
    std::string FileDescription;
    std::string InputPath;
    std::string OutputPath;
    std::vector<std::string> noiseFilters;
    std::map<std::string, PeriodConfig> periods;
    std::map<std::string, SampleConfig> samples;
    
private:
    ConfigInterface() {}  // Private constructor to enforce singleton.
};

#endif // CONFIG_INTERFACE_HPP
