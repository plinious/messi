#ifndef _MESSI_COMMON_TYPES_H
#define _MESSI_COMMON_TYPES_H

#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <unordered_map>

#include <algorithm>

#define MESSI_NAMESPACE_START namespace messi {
#define MESSI_NAMESPACE_END }

#define DO_NOTHING()

#include "GlobalConst.h"

typedef std::vector<std::string> Strings;
typedef std::set<std::string> StringSet;
typedef std::map<std::string, std::string> StringMap;
typedef std::unordered_map<std::string, std::string> StringHashMap;

typedef unsigned char BYTE;

#define InfoLog(s) { std::cout << s << std::endl;}
#define WarnLog(s) { std::cout << s << std::endl;}

#endif // _MESSI_COMMON_TYPES_H

