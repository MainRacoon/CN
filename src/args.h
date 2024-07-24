#ifndef _CN_ARGS_
#define _CN_ARGS_

void args_help(){
    printf(""
             "-h,--help,help\t\thelp message\n"
             "-o,--output\t\tset output file name\n"
             "-I <directory>\t\tadd new directory for include search\n"
             "-v,--version\t\tprint current version\n"
             ""
             ""
             ""
             ""
             "");
}

strings args_parse(int argc, char**argv,char**output,char**filename){
    bool output_defined = false;
    bool filename_defined = false;
    strings directories = strings_new();
    strings_resize(&directories, 1);
    strings_append(&directories,"./");
    for (int i = 1; i < argc; ++i) {
        if(streq(argv[i],"-h")||streq(argv[i],"--help")||streq(argv[i],"help")){
            args_help();
            continue;
        }
        if(streq(argv[i],"-v")||streq(argv[i],"--version")){
            printf("%s<VERSION::%s>%s\n",COLOR_SPECIAL,VERSION,COLOR_NORMAL);
            continue;
        }
        if(streq(argv[i],"-o")){
            if(argc-1==i){
                logger_error("args.h","args_parse","Not enough arguments for command","");
                exit(1);
            }
            if(output_defined==true){
                logger_error("args.h","args_parse","Output file name already specified:",*output);
                exit(1);
            }
            *output=argv[++i];
            output_defined=true;
            continue;
        }
        if(streq(argv[i],"-I")){
            if(argc-1==i){
                logger_error("args.h","args_parse","Not enough arguments for command","");
                exit(1);
            }
            strings_resize(&directories,directories.size+1);
            strings_append(&directories,argv[++i]);
            continue;
        }
        if(filename_defined==true){
            logger_error("args.h","args_parse","Main file name already specified:",*output);
            exit(1);
        }
        *filename=argv[i];
        filename_defined=true;
    }
    return directories;
}



#endif