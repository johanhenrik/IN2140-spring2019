#include <stdio.h>

#include "logger.h"


/* ------------------------------------------------------------------------- *\
 *
 * Global variables.
 *
\* ------------------------------------------------------------------------- */
char LOGGER_DEBUG = 0;

char LOGGER_INFO = 1;

char LOGGER_ERROR = 2;

char LOGGER_OFF = 3;

char logger_level;


void log_msg(char level, char msg[]) {
	if (logger_level == LOGGER_OFF) {
		printf("Logger is turned off.\n");
		return;
	}
	if (level > logger_level) {
		return;
	}
	if (logger_level == LOGGER_DEBUG) {
		printf("DEBUG - %s\n", msg);
	} else if (logger_level == LOGGER_INFO) {
		printf("INFO - %s\n", msg);
	} else if (logger_level == LOGGER_ERROR) {
		printf("ERROR - %s\n", msg);
	}
}

void set_logger_level(char level) {
	if (level < LOGGER_DEBUG || level > LOGGER_OFF) {
		printf("Error. Illegal argument %d.\nlogger.c #set_logger_mode(char mode)"
				"\n", level);
		return;
	}
	logger_level = level;
}
