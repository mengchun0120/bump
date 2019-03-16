#ifndef INCLUDE_UTILS
#define INCLUDE_UTILS

#include <string>

namespace bump {

bool readText(std::string& text, const std::string& fileName);

void trim(char *s, int *start, size_t *len);

} // end of namespace bump

#endif
