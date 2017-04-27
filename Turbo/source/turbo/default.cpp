#include "turbo/default.h"

using namespace TURBO;

EXTERN::INI Default::getDefaultSettings()
{
    EXTERN::INI settings;

    settings.kvp["Audio"]["volume"] = "64";
    settings.kvp["Display"]["flags"] = "0x00000008";
    settings.kvp["Display"]["display_w"] = "1024";
    settings.kvp["Display"]["display_h"] = "768";

    return settings;
}