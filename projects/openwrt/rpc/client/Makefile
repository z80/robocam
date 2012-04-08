
TARGET=client
OBJECTS=main.o interface.o
CXXFLAGS:=-I./src -I. -I../../build/icee/cppe/include -DICEE_PURE_CLIENT $(CXXFLAGS)
LIBS:=-lpthread -lrt -L../../build/icee/cppe/lib -lIceE -lIceEC

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFAGS) -o $@ $(OBJECTS) $(LIBS)
	
clean:
	rm -f *.o *.cpp *.h $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< 

interface.o: interface.cpp
main.o: main.cpp interface.cpp

main.cpp:
	cp ./src/main.cpp ./

interface.cpp:
	../../build/icee/cpp/bin/slice2cppe ../common/interface.ice

interface.h:
	../../build/icee/cpp/bin/slice2cppe ../common/interface.ice


	


