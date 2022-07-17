#include "qsettingsjsonwrapper.h"
#include "qsettings_json.hpp"

QSettings QsettingsJSONwrapper::open(){
    return QSettings(":/settings/themes.json", JsonFormat);
}
