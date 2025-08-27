#include <fstream>
#include <iostream>

#include "JsonConfigReader.hpp"
#include "ConfigInterface.hpp"

using CMSConfig::YearConfig;
using CMSConfig::SampleConfig;

bool JsonConfigReader::open(const std::string& filePath) {
    std::ifstream ifs(filePath);
    if (!ifs.is_open()) {
        std::cerr << "Error opening file: " << filePath << "\n";
        return false;
    }

    try {
        ifs >> jsonData;
    } catch (const std::exception& ex) {
        std::cerr << "Error parsing JSON: " << ex.what() << "\n";
        return false;
    }

    configFilePath = filePath;
    return fillConfig();
}

bool JsonConfigReader::fillConfig() {
    try {
        auto& cfg = ConfigInterface::getInstance();

        // Required top-level entries
        if (!jsonData.contains("FileDescription") || jsonData.at("FileDescription").is_null()) {
            std::cerr << "Error: FileDescription is missing or null.\n";
            return false;
        }
        cfg.FileDescription = jsonData.at("FileDescription").get<std::string>();

        if (!jsonData.contains("InputPath") || jsonData.at("InputPath").is_null()) {
            std::cerr << "Error: InputPath is missing or null.\n";
            return false;
        }
        cfg.InputPath = normalizePath(jsonData.at("InputPath").get<std::string>());

        if (!jsonData.contains("OutputPath") || jsonData.at("OutputPath").is_null()) {
            std::cerr << "Error: OutputPath is missing or null.\n";
            return false;
        }
        cfg.OutputPath = normalizePath(jsonData.at("OutputPath").get<std::string>());

        // Yearly sections
        std::vector<std::string> yearKeys = {"2016PreAPV", "2016PostAPV", "2017", "2018"};
        for (const auto& yKey : yearKeys) {
            if (!jsonData.contains(yKey) || !jsonData.at(yKey).is_object()) {
                std::cerr << "Error: missing section for " << yKey << " or not an object.\n";
                return false;
            }
            const auto& yVal = jsonData.at(yKey);
            YearConfig yc{};
            if (!yVal.contains("lumi")) {
                std::cerr << "Error: " << yKey << " missing lumi.\n";
                return false;
            }
            if (yVal.at("lumi").is_null()) {
                std::cerr << "Warning: " << yKey << " lumi is null. Using 0.\n";
                yc.lumi = 0.0;
            } else {
                yc.lumi = yVal.at("lumi").get<double>();
            }

            if (!yVal.contains("samples") || !yVal.at("samples").is_object()) {
                std::cerr << "Error: " << yKey << " samples section missing or not object.\n";
                return false;
            }
            for (auto& [sKey, sVal] : yVal.at("samples").items()) {
                SampleConfig sc{};

                if (!sVal.contains("Xs")) {
                    std::cerr << "Error: sample " << sKey << " missing Xs.\n";
                    return false;
                }
                sc.Xs = sVal.at("Xs").is_null() ? (std::cerr << "Warning: sample " << sKey << " Xs is null. Using 0.\n", 0.0) : sVal.at("Xs").get<double>();

                if (!sVal.contains("BR")) {
                    std::cerr << "Error: sample " << sKey << " missing BR.\n";
                    return false;
                }
                sc.BR = sVal.at("BR").is_null() ? (std::cerr << "Warning: sample " << sKey << " BR is null. Using 0.\n", 0.0) : sVal.at("BR").get<double>();

                if (!sVal.contains("NEvt")) {
                    std::cerr << "Error: sample " << sKey << " missing NEvt.\n";
                    return false;
                }
                sc.NEvt = sVal.at("NEvt").is_null() ? (std::cerr << "Warning: sample " << sKey << " NEvt is null. Using 0.\n", 0) : sVal.at("NEvt").get<int>();

                if (!sVal.contains("Wgt")) {
                    std::cerr << "Error: sample " << sKey << " missing Wgt.\n";
                    return false;
                }
                sc.Wgt = sVal.at("Wgt").is_null() ? (std::cerr << "Warning: sample " << sKey << " Wgt is null. Using 0.\n", 0.0) : sVal.at("Wgt").get<double>();

                if (!sVal.contains("Type") || sVal.at("Type").is_null()) {
                    std::cerr << "Error: sample " << sKey << " missing Type.\n";
                    return false;
                }
                sc.Type = sVal.at("Type").get<std::string>();

                yc.samples[sKey] = sc;
            }
            cfg.years[yKey] = yc;
        }

        // noiseFilters per year
        std::vector<std::string> nfKeys = {"2016noiseFilter", "2017noiseFilter", "2018noiseFilter"};
        for (const auto& nfKey : nfKeys) {
            if (!jsonData.contains(nfKey)) {
                std::cerr << "Error: missing " << nfKey << " array.\n";
                return false;
            }
            if (!jsonData.at(nfKey).is_array()) {
                std::cerr << "Warning: " << nfKey << " is not an array. Ignored.\n";
                continue;
            }
            for (const auto& nf : jsonData.at(nfKey)) {
                if (nf.is_null()) {
                    std::cerr << "Warning: encountered null noise filter entry in " << nfKey << ".\n";
                    continue;
                }
                cfg.noiseFilters[nfKey].push_back(nf.get<std::string>());
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error filling configuration: " << ex.what() << "\n";
        return false;
    }
    return true;
}
