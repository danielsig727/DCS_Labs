CXX = gcc
CXXFLAG = -g -O2 -fopenmp#-DOUTPUT_ALL
LDFLAG = -lpthread -lrt -fopenmp
INCLUDE = .
OBJ = DCS09.exe

all: lib main
	$(CXX) -o $(OBJ) *.o  $(LDFLAG)
	@echo 
	@echo "Compilation done. Execute $(OBJ) if you please :)"
	@echo 

lib:
	$(CXX) $(CXXFLAG) -c D_Circuit.c
	$(CXX) $(CXXFLAG) -c D_Parser.c
	$(CXX) $(CXXFLAG) -c D_Hash.c
	


main:
	$(CXX) $(CXXFLAG) -c main.c
			
clean:
	rm -rf *.o $(OBJ)
	rm -rf *.log	

help:
	@echo "Available targets:"
	@echo "    all(default): Compile the program."
	@echo "    clean       : Cleanup objects and executables"

run:
	for i in 1 2 3 4 5; do \
	 ./DCS09.exe input$$i.ckt pattern$$i.vcd ; \
	 done
