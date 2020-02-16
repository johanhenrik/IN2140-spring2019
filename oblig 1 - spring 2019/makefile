###############################################################################
#	makefile.
#
#			
#
###############################################################################
oblig.o:
	gcc -I header/ -o oblig.out source/oblig.c source/hexreader.c source/router.c source/test.c source/util.c

10_routers: oblig.o
	./oblig.out "10_routers_10_edges" "commands_10_routers.txt"

50_routers: oblig.o
	./oblig.out "50_routers_150_edges" "commands_50_routers.txt"

test: oblig.o
	./oblig.out

valgrind: oblig.o
	valgrind --leak-check=full ./oblig.out

valgrind_10: oblig.o
	valgrind --leak-check=full ./oblig.out "10_routers_10_edges" "commands_10_routers.txt"

valgrind_50: oblig.o
	valgrind --leak-check=full ./oblig.out "50_routers_150_edges" "commands_50_routers.txt"
