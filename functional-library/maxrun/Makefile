CXX=g++
CXXFLAGS= -std=c++11 -O0 -g -O0 -Wall -msse2 -msse -march=native -maes  #-I/home/donayam/SE-prototype/functional-library/src/ciphers/aes/tinyCrypt_without_Git/lib/include



ENC_LIBS = ../../Shared/shared_se.cpp ../src/vip-functional-library.cpp ../src/interface/interface.cpp ../src/datatypes/enc_impl.cpp ../src/interface/parameters.cpp ../src/rng/rng_interface.cpp ../src/rng/mersenne-twister-1/mersenne-twister.cpp ../src/ciphers/aes/aes_interface.cpp ../src/ciphers/xor/xor_interface.cpp

all: main #test_enc_array 

main: main.o enc_lib.o 
	$(CXX) $(CXXFLAGS)  ${ENC_LIBS} -o  main main.o 

main.o: main.cpp  ../src/datatypes/enc_lib.h 
	$(CXX) $(CXXFLAGS) -c main.cpp 




enc_lib.o: ../src/datatypes/enc_lib.h



clean:
	rm -f $(IDIR)/*.o 
	rm -f *.o $(TARGET)
	rm main 
