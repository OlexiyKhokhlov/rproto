#include "plugin.h"
#include <plugin/module.h>

namespace
{

  typedef std::tuple
    <
      Plugin
    >
    ExportedCoClasses;
}

BOSS_DECLARE_MODULE_ENTRY_POINT("PDFiumPlugin", ExportedCoClasses)

