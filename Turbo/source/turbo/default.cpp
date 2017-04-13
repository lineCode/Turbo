#include "turbo/default.h"

using namespace TURBO;

map<string, map<string, string>> Default::getDefaultSettings()
{
    map<string, map<string, string>> settings;

    settings["Audio"]["volume"] = "64";
    settings["Display"]["flags"] = "false";
    settings["Display"]["display_w"] = "1024";
    settings["Display"]["display_h"] = "768";

    return settings;
}