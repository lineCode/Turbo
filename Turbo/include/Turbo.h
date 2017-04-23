#ifndef TURBO_H_INCLUDED
#define TURBO_H_INCLUDED

#include "system/system.h"
#include "gui/gui_widget.h"
#include "audio/audio.h"
#include "script/Turbo_script.h"

using UTILS::LOG_TYPE;
using GUI::Color;

namespace TURBO
{
    const LOG_TYPE      TURBO_LOGGING           = LOG_TYPE::VERBOSE;

    const Color         TRANSPARENT	            = {0x00, 0x00, 0x00, 0x00};
    const Color         BLACK			        = {0x00, 0x00, 0x00, 0xFF};
    const Color         RED			            = {0xFF, 0x00, 0x00, 0xFF};
    const Color         GREEN                   = {0x00, 0xFF, 0x00, 0xFF};
    const Color         BLUE			        = {0x00, 0x00, 0xFF, 0xFF};
    const Color         WHITE			        = {0xFF, 0xFF, 0xFF, 0xFF};
    const Color         YELLOW		            = {0xFF, 0xFF, 0x00, 0xFF};
    const Color         MAGENTA		            = {0xFF, 0x00, 0xFF, 0xFF};
    const Color         CYAN			        = {0x00, 0xFF, 0xFF, 0xFF};
}

#endif // TURBO_H_INCLUDED
