// main.cpp
#include <iostream>
#include "JsonConfigReader.hpp"
#include "ConfigInterface.hpp"

int main() {
    const std::string configName = "config.json";

    if (!JsonConfigReader::getInstance().open(configName)) {
        std::cerr << "Failed to open configure file: " << configName << std::endl;
        return 1;
    }

    JsonConfigReader::getInstance().printJsonConfig();

    ConfigInterface& cfgInterFace = ConfigInterface::getInstance();

    std::cout << "File Description: " << cfgInterFace.FileDescription << std::endl;
    std::cout << "Input Path: " << cfgInterFace.InputPath << std::endl;
    std::cout << "Output Path: " << cfgInterFace.OutputPath << std::endl;

    for (const auto& [yearName, yearCfg] : cfgInterFace.years) {
        for (const auto& [sName, sCfg] : yearCfg.samples) {
            std::cout << yearName << " - " << sName
                      << ": Wgt=" << sCfg.Wgt << std::endl;
        }
    }
    return 0;
}
