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

    // Access configuration data through the ConfigInterface singleton instance
    ConfigInterface& cfgInterFace = ConfigInterface::getInstance();

    // Print configuration information
    std::cout << "File Description: " << cfgInterFace.FileDescription << std::endl;
    std::cout << "Input Path: " << cfgInterFace.InputPath << std::endl;
    std::cout << "Output Path: " << cfgInterFace.OutputPath << std::endl;

    std::cout << "\nPeriods:\n";
    for (const auto& entry : cfgInterFace.periods) {
        std::cout << "Period: " << entry.first 
                  << ", Year: " << entry.second.year 
                  << ", Lumi: " << entry.second.lumi << std::endl;
    }

    std::cout << "\nSamples:\n";
    for (const auto& entry : cfgInterFace.samples) {
        std::cout << "Sample: " << entry.first 
                  << ", Xs: " << entry.second.Xs 
                  << ", BR: " << entry.second.BR 
                  << ", NEvt: " << entry.second.NEvt 
                  << ", Weight: " << entry.second.Weight 
                  << ", isData: " << (entry.second.isData ? "true" : "false") << std::endl;
    }

    std::cout << "\nNoise Filters:\n";
    for (const auto& nf : cfgInterFace.noiseFilters) {
        std::cout << nf << " ";
    }
    std::cout << std::endl;

    // Save the configuration information to a new JSON file (e.g., output.json)
    if (!JsonConfigReader::getInstance().save("output.json")) {
        std::cerr << "Failed to save output.json file." << std::endl;
        return 1;
    }

    std::cout << "\nConfiguration successfully saved to output.json" << std::endl;
    return 0;
}
