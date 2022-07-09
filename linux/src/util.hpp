#pragma once
#include "ctx.hpp"

namespace tfefs {
    static bool isExtensionSupported(const char *extlist, const char *extension)
    {
        const char *start;
        const char *where, *terminator;

        where = strchr(extension, ' ');
        if (where || *extension == '\0')
            return false;

        for (start = extlist;;)
        {
            where = strstr(start, extension);
            if (!where)
                break;
            terminator = where + strlen(extension);

            if (where == start || *(where - 1) == ' ')
                if (*terminator == ' ' || *terminator == '\0')
                    return true;

            start = terminator;
        }
        return false;
    }
}