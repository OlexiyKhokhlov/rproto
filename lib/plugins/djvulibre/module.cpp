#include "djvuplugin.h"
#include <plugin/module.h>

namespace
{

  typedef std::tuple
    <
      DjVuPlugin
    >
    ExportedCoClasses;
}

BOSS_DECLARE_MODULE_ENTRY_POINT("DjVuPlugin", ExportedCoClasses)
