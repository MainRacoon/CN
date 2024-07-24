#include "./defines.h"



int main(int argc, char**argv){
    char*filename="main.cn",*output="a.c";
    strings dirs = args_parse(argc,argv,&output,&filename);
    u64 size = 0;
    char*content = freadAll(filename,&size);
    strings tokens = tokenizer_tokens(content,size);
    binaries bins = binary_fromtokens(tokens);

}