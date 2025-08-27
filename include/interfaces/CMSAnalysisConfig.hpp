#ifndef CMS_ANALYSIS_CONFIG_HPP
#define CMS_ANALYSIS_CONFIG_HPP

#include <map>
#include <string>
#include <vector>

namespace CMSConfig {

struct SampleConfig {
    double Xs{};
    double BR{};
    int NEvt{};
    double Wgt{};
    std::string Type;
};

struct YearConfig {
    double lumi{};
    std::map<std::string, SampleConfig> samples;
};

class CMSAnalysisConfig {
public:
    static CMSAnalysisConfig& getInstance() {
        static CMSAnalysisConfig instance;
        return instance;
    }

    CMSAnalysisConfig(const CMSAnalysisConfig&) = delete;
    CMSAnalysisConfig& operator=(const CMSAnalysisConfig&) = delete;

    std::string FileDescription;
    std::string InputPath;
    std::string OutputPath;
    std::map<std::string, std::vector<std::string>> noiseFilters;
    std::map<std::string, YearConfig> years;

private:
    CMSAnalysisConfig() = default;
};

} // namespace CMSConfig

#endif // CMS_ANALYSIS_CONFIG_HPP
