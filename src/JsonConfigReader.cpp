
#include <nlohmann/json.hpp>
// This project uses nlohmann/json (https://github.com/nlohmann/json)
// Licensed under the MIT License.

#include <fstream>
#include <iostream>

#include "JsonConfigReader.hpp"
#include "ConfigInterface.hpp"

using json = nlohmann::json;

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
    
    // Call our own fillConfig() implementation.
    return fillConfig();
}

bool JsonConfigReader::fillConfig() {
    try {
        auto& cfgInterFace = ConfigInterface::getInstance();
        cfgInterFace.FileDescription = jsonData.at("FileDescription").get<std::string>();
        cfgInterFace.InputPath = normalizePath(jsonData.at("InputPath").get<std::string>());
        cfgInterFace.OutputPath = normalizePath(jsonData.at("OutputPath").get<std::string>());
        
        // Parse periods.
        for (auto& [key, value] : jsonData.at("periods").items()) {
            PeriodConfig p;
            p.year = value.at("year").get<int>();
            p.lumi = value.at("lumi").get<double>();
            cfgInterFace.periods[key] = p;
        }
        
        // Compute integrated luminosity as the sum of all period lumi values.
        double integratedLuminosity = 0.0;
        for (const auto& pr : cfgInterFace.periods) {
            integratedLuminosity += pr.second.lumi;
        }
        
        // Parse samples.
        for (auto& [key, value] : jsonData.at("samples").items()) {
            SampleConfig s;
            s.Xs = value.at("Xs").get<double>();
            s.BR = value.at("BR").get<double>();
            if (value.contains("NEvt") && !value.at("NEvt").is_null())
                s.NEvt = value.at("NEvt").get<int>();
            else
                s.NEvt = 0;
            
            if (value.contains("Weight") && !value.at("Weight").is_null())
                s.Weight = value.at("Weight").get<double>();
            else
                s.Weight = computeWeight(s.Xs, s.BR, s.NEvt, integratedLuminosity);
            
            s.isData = value.at("isData").get<bool>();
            cfgInterFace.samples[key] = s;
        }
        
        // Parse noiseFilters array.
        if (jsonData.contains("noiseFilters") && jsonData.at("noiseFilters").is_array()) {
            for (const auto& nf : jsonData.at("noiseFilters")) {
                cfgInterFace.noiseFilters.push_back(nf.get<std::string>());
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error filling cfgInterFaceuration: " << ex.what() << "\n";
        return false;
    }
    return true;
}

bool JsonConfigReader::save(const std::string& filePath) {
    auto& cfgInterFace = ConfigInterface::getInstance();
    json j;
    j["FileDescription"] = cfgInterFace.FileDescription;
    j["InputPath"] = cfgInterFace.InputPath;
    j["OutputPath"] = cfgInterFace.OutputPath;
    
    json jPeriods;
    for (const auto& p : cfgInterFace.periods) {
        jPeriods[p.first] = { {"year", p.second.year}, {"lumi", p.second.lumi} };
    }
    j["periods"] = jPeriods;
    
    json jSamples;
    for (const auto& s : cfgInterFace.samples) {
        jSamples[s.first] = {
            {"Xs", s.second.Xs},
            {"BR", s.second.BR},
            {"NEvt", s.second.NEvt},
            {"Weight", s.second.Weight},
            {"isData", s.second.isData}
        };
    }
    j["samples"] = jSamples;
    
    j["noiseFilters"] = cfgInterFace.noiseFilters;
    
    std::ofstream ofs(filePath);
    if (!ofs) {
        std::cerr << "Error opening file for writing: " << filePath << "\n";
        return false;
    }
    ofs << j.dump(4);
    return true;
}
