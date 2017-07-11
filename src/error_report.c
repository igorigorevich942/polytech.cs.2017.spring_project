/** \file error_report.c
\brief Файл, в котором реализованы функции логирования ошибок.
*/

#include "error_report.h"
#include <stdio.h>


void error_report(const char* fl_name, const char* fn_name, const char* mess)
{
    fprintf(stderr, "Error:\n");
    fprintf(stderr, "\tfile_name:%s\n", fl_name);
    fprintf(stderr, "\tfunction_name:%s\n", fn_name);
    fprintf(stderr, "\tmessage:%s\n", mess);
}
