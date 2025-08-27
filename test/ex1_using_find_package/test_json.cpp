// main.cpp
#include <iostream>
#include "JsonConfigReader.hpp"
#include "ConfigInterface.hpp"

int main() {
    const std::string configName = "config.json";

    // Read the JSON configuration file to fill the configuration data
    if (!JsonConfigReader::getInstance().open(configName)) {
        std::cerr << "Failed to open configure file: " << configName << std::endl;
        return 1;
    }

    // Optionally print the entire JSON structure
    JsonConfigReader::getInstance().printJsonConfig();

    // Access configuration data through the ConfigInterface singleton instance
    ConfigInterface& cfgInterFace = ConfigInterface::getInstance();

    // Print configuration information
    std::cout << "File Description: " << cfgInterFace.FileDescription << std::endl;
    std::cout << "Input Path: " << cfgInterFace.InputPath << std::endl;
    std::cout << "Output Path: " << cfgInterFace.OutputPath << std::endl;

    std::cout << "\nYears and Samples:\n";
    for (const auto& [yearName, yearCfg] : cfgInterFace.years) {
        std::cout << yearName << " lumi: " << yearCfg.lumi << std::endl;
        for (const auto& [sName, sCfg] : yearCfg.samples) {
            std::cout << "  Sample: " << sName
                      << ", Xs: " << sCfg.Xs
                      << ", BR: " << sCfg.BR
                      << ", NEvt: " << sCfg.NEvt
                      << ", Wgt: " << sCfg.Wgt
                      << ", Type: " << sCfg.Type << std::endl;
        }
    }

    std::cout << "\nNoise Filters:\n";
    for (const auto& [nfYear, filters] : cfgInterFace.noiseFilters) {
        std::cout << nfYear << ": ";
        for (const auto& f : filters) {
            std::cout << f << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
