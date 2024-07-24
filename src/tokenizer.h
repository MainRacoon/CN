#ifndef _CN_TOKENIZER_
#define _CN_TOKENIZER_

#define SPECIAL_CHARS "!-+/*;="
#define SPECIAL_CHARS_LEN 7
strings tokenizer_tokens(char*content,u64 len){
    strings tokens = strings_new();
    u64 start = 0;
    bool isstring = false;
    char stringchar = ' ';
    char*buf = "";
    u64 buflen = 0;
    u64 par = 0;
    for (u64 i = 0; i < len; ++i) {
        if((stringchar==content[i]||!isstring)&&(content[i]=='"'||content[i]=='\'')){
            if(!streq(buf,"")&&par==0){
                strings_resize(&tokens,tokens.size+1);
                strings_append(&tokens, strcopy(buf));
                buf = "";
                buflen=0;
            }
            stringchar=content[i];
            isstring=!isstring;
            if(!isstring){
                if(par!=0){
                    buf = strconcat(buf, strlen(buf),strsubstringrange(content, len, start, i+1),i+1-start);
                    buflen+=i+1-start;
                    continue;
                }
                strings_resize(&tokens,tokens.size+1);
                strings_append(&tokens, strsubstringrange(content, len, start, i+1));
                continue;
            }
            start = i;
            continue;
        }
        if(isstring){
            if(content[i]=='\\'){
                if(i+1<len){
                    i++;
                }
            }
            continue;
        }

        if(isspace(content[i])){
            if(!streq(buf,"")&&par==0){
                strings_resize(&tokens,tokens.size+1);
                strings_append(&tokens, strcopy(buf));
                buf = "";
                buflen=0;
            }
            if(par!=0){
                if(!isspace(content[i-1])){
                    buf = strconcat(buf, buflen,&content[i],1);
                    buflen++;
                }
            }
            continue;
        }
        if(strcharIn(SPECIAL_CHARS,SPECIAL_CHARS_LEN,content[i])){
            if(par==0){
                if(!streq(buf,"")){
                    strings_resize(&tokens,tokens.size+1);
                    strings_append(&tokens, strcopy(buf));
                    buf = "";
                    buflen=0;
                }
                strings_resize(&tokens,tokens.size+1);
                strings_append(&tokens, strctcp(content[i]));
                continue;
            }

            buf = strconcat(buf, buflen,&content[i],1);
            buflen++;
            continue;
        }
        if(content[i]=='('){
            if(!streq(buf,"")){
                strings_resize(&tokens,tokens.size+1);
                strings_append(&tokens, strcopy(buf));
                buf = "";
                buflen=0;
            }
            par++;
        }else if(content[i]==')'){
            if(par==0){
                logger_error("tokenizer.h","tokenizer_tokens","Unexpected parentheses at index", strformat("%llu",i));
                exit(0);
            }
            par--;
        }
        buf = strconcat(buf, buflen,&content[i],1);
        buflen++;
    }
    if(!streq(buf,"")){
        strings_resize(&tokens,tokens.size+1);
        strings_append(&tokens, strcopy(buf));
    }
    return tokens;
}


#endif
