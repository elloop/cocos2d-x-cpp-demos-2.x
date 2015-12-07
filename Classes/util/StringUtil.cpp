#include "util/StringUtil.h"
#include <sstream>

std::string StringUtil::toString(int i)
{
    std::ostringstream oss;
    oss << i;
    return oss.str();
}

