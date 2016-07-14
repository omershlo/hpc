#CXX=g++  -Wall -W -ansi -pedantic -O3 -m32 # -static #-pg  -g #-DNDEBUG # -falign-functions=2 #
 CXX=g++   -Wall -W -ansi -pedantic  -std=c++0x -O3 -g -finline-functions#-pg  -g  # -static #-DNDEBUG # -falign-functions=2 #
#CXX=/opt/intel//bin/icpc   -Wall -W -ansi -pedantic -O3 -std=c++0x -g# -static #-pg  -g #-DNDEBUG # -falign-functions=2 #

shaheaders=types1.h sha_utils.h sha1.h wbs.h compare.h duplicates.h  CorrectionSet.h  ReducedSha.h modifications.h solve.h check_equations.h second_corrections.h rounds_90_105.h
sha_files =sha.o sha_utils.o sha1.o neutral.o check_condition_order.o set_linear_condition.o  wbs.o compare.o first_16_rounds.o solve83.o solve84.o solve85.o solve86.o solve87.o solve88.o solve89.o solve90.o modifications.o check_equations.o update_and_test.o rounds_90_105.o#gpu.o round_90_97.o 

#shaheaders=rabbitvcs-112-types1.h sha_utils.h rabbitvcs-111-sha1.h set_linear_condition.h  wbs.h compare.h 
#sha_files =rabbitvcs-112-sha.o rabbitvcs-110-sha_utils.o sha1.o neutral.o rabbitvcs-112-check_condition_order.o rabbitvcs-111-correct.o set_linear_condition.o  rabbitvcs-110-wbs.o compare.o


all: sha 

sha: $(sha_files) $(shaheaders)
	$(CXX) $(sha_files) -o $@

clean:
	-rm -f *.o 

clobber: clean
	-rm -f sha

%.o: %.cc $(shaheaders) 
	$(CXX) -c $< -o $@
