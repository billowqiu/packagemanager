#include "config.h"
#include "tinyxml/tinyxml.h"
#include <iostream>

std::vector<PackageConfig> Config::package_configs_;

bool Config::Load( const std::string& config_file )
{
    //加载xml文件
    TiXmlDocument xmlDoc(config_file.c_str());
    if (!xmlDoc.LoadFile())
    {
        return false;
    }
    TiXmlNode* rootElement = xmlDoc.FirstChild("package_config");
    for (TiXmlElement* nextElement = rootElement->FirstChildElement(); nextElement;
         nextElement = nextElement->NextSiblingElement())
    {
        PackageConfig package_config;
        package_config.path = nextElement->Attribute("path");
        package_configs_.push_back(package_config);
    }

    return true;
}

bool Config::Save( const std::string& config_file )
{
    return false;
}
