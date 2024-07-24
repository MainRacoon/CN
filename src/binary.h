#ifndef _CP_BINARY_
#define _CP_BINARY_
binaries binary_fromtokens(strings tokens){
    binaries output = binaries_new();
    for (u64 i = 0; i < tokens.len; ++i) {
        if(streq(tokens.array[i],"#includes")||streq(tokens.array[i],"#cincludes")){
            binary buf = {binary_t_import, strings_new()};
            if(streq(tokens.array[i],"#cincludes")){
                buf.type=binary_y_cimport;
            }
            for (i++; i < tokens.len&&!streq(tokens.array[i],"#endincl"); ++i) {
                strings_resize(&buf.values,buf.values.size+1);
                strings_append(&buf.values,strcopy(tokens.array[i]));
            }
            if(!streq(tokens.array[i],"#endincl")){
                logger_error("binary.h","binary_fromtokens","Token #endincl not found", "");
                exit(1);
            }
            binaries_resize(&output,output.size+1);
            binaries_append(&output,buf);
            continue;
        }
        if(streq(tokens.array[i],"#include")){
            if(++i<tokens.len){
                binary buf = {binary_t_import, strings_new()};
                if(streq(tokens.array[i-1],"#cinclude")){
                    buf.type=binary_y_cimport;
                }
                strings_resize(&buf.values,1);
                strings_append(&buf.values,strcopy(tokens.array[i]));
                binaries_resize(&output,output.size+1);
                binaries_append(&output,buf);
                continue;
            }
            logger_error("binary.h","binary_fromtokens","Import file for the import not found", "");
            exit(1);
        }
    }

    return output;
}

#endif
