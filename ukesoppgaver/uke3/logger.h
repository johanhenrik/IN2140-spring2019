// #pragma once
#ifndef __LOGGER_H__
#define __LOGGER_H__

extern char LOGGER_DEBUG;

extern char LOGGER_ERROR;

extern char LOGGER_INFO;

extern char LOGGER_OFF;

void log_msg(char type, char msg[]);

void set_logger_level(char mode);

#endif
