OBJS=../src/Dvector.o ../src/Height.o ../src/GerstnerWave.o ../src/GerstnerWaveModel.o ../src/Ocean.o ../src/WaveModel.o test_tp4_catch.o
CXX=g++
CXXFLAGS=-Wall -g -std=c++11
TEST_EXEC=test_tp4_catch

$(TEST_EXEC):$(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o:%.cxx
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(TEST_EXEC)
