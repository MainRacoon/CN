#ifndef _CN_LOGGER
#define _CN_LOGGER

void logger_error(char*file,char*function,char*action, char*additional){
    printf("%s<Error> %s::%s\t%s %s%s",COLOR_ERROR,file,function,action,additional,COLOR_NORMAL);
}

void logger_warning(char*file,char*function,char*action,char*additional){
    printf("%s<Warning> %s::%s\t%s %s%s",COLOR_WARNING,file,function,action,additional,COLOR_NORMAL);
}
#endif
