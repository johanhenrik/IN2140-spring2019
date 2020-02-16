#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "logger.h"

int main(int argc, char *argv[]) {
	/*
	 * Setting this illegal value as logger level should fail.
	 */
	set_logger_level(-50);

	/*
	 * Turning the logger off and logging should not work.
	 */
	 set_logger_level(LOGGER_OFF);
	 log_msg(LOGGER_ERROR, "Trying to log, when the logger is turned off.");

	/*
	 * I set the logger level to LOGGER_ERROR and writes an error message to the
	 * console output.
	 */
	 set_logger_level(LOGGER_ERROR);
	 log_msg(LOGGER_ERROR, "Logging now, with the level set at error.");

	if (argc > 1) {
		printf("ARgument is = %s\n", argv[1]);
		if (streq(argv[1], "-log")) {
			printf("Logging..\n");
		}
		if (argc > 3) {
			printf("ARgument is = %s\n", argv[1]);
			if (streq(argv[1], "-log")) {
				printf("Logging..\n");
			}
		}
	}

}
