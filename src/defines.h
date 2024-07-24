#ifndef _CN_DEIFNES_
#define _CN_DEIFNES_

#define VERSION "0.0a"

#include <ctype.h>
#include "c+/stdtype.h"
#include "c+/stdcolor.h"
#include "c+/stdarr.h"
#include "c+/stdstr.h"
#include "c+/stdfs.h"

#define COLOR_SPECIAL stdcolor.text.normal.magenta
#define COLOR_ERROR stdcolor.text.normal.red
#define COLOR_WARNING stdcolor.text.normal.yellow
#define COLOR_NORMAL stdcolor.reset

StdarrayNew(char*,strings)
enum binary_type{
    binary_t_import,
    binary_y_cimport,
};
typedef struct{
    enum binary_type type;
    strings values;
}binary;
StdarrayNew(binary, binaries)

#include "./logger.h"
#include "./args.h"
#include "./tokenizer.h"
#include "./binary.h"
#endif