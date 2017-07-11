#ifndef ERROR_REPORT_H
#define ERROR_REPORT_H

/** \file error_report.h
\brief Файл, в котором опеределены функции логирования ошибок.
*/

/**
Вывод сообщения об ошибки в поток stderr.
\param[in] fl_name - имя файла, в котором возникла ошибка.
\param[in] fn_name - имя функции, в которой возникла ошибка.
\param[in] mess - информационное сообщение, характеризующие ошибку.
*/
void error_report(const char* fl_name, const char* fn_name, const char* mess);

#endif // ERROR_REPORT_H

