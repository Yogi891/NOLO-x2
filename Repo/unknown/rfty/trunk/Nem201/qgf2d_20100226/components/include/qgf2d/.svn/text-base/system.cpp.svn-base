#include "qgf2d/system.h"

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

namespace qgf
{
    bool initDirectory()
    {
        char buf[MAX_PATH+1];
        GetModuleFileName(NULL,buf,MAX_PATH);
        char *p = buf;
        char *lastslash=NULL;
        while(*p)
        {
            if(*p=='\\' || *p=='/')
            {
                lastslash = p;
            }
            p++;
        }
        if(lastslash)
        {
            *lastslash=0;
        }
        SetCurrentDirectory(buf);
        return true;
    }
}
