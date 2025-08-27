#ifndef CONFIG_INTERFACE_HPP
#define CONFIG_INTERFACE_HPP

#include "interfaces/CMSAnalysisConfig.hpp"

// Default configuration interface for the library.
// Users can replace this alias or include a different interface header
// if their analysis requires a distinct configuration structure.
using ConfigInterface = CMSConfig::CMSAnalysisConfig;

#endif // CONFIG_INTERFACE_HPP
