#include <vector>
#include <string>

struct PackageConfig
{
    std::string path;
};

class Config
{
public:
    static std::vector<PackageConfig> package_configs_;

public:
    static bool Load(const std::string& config_file);
    static bool Save(const std::string& config_file);
};
