
EMBEDDED=no

ifeq ($(EMBEDDED),yes)
	libs=$(libs_for_gcc)
	REL_PATH:=~/projects/openwrt/OpenWrt-Toolchain-brcm47xx-for-mipsel-gcc-4.3.3+cs_uClibc-0.9.30.1/toolchain-mipsel_gcc-4.3.3+cs_uClibc-0.9.30.1/usr
	CC:=$(REL_PATH)/bin/mipsel-openwrt-linux-gcc
	CXX:=$(REL_PATH)/bin/mipsel-openwrt-linux-g++
	AR:=$(REL_PATH)/bin/mipsel-openwrt-linux-ar
	INC_CXX:=$(REL_PATH)/mipsel-openwrt-linux/include/c++/4.3.3
	PATH:=$(REL_PATH)/lib:$(REL_PATH)/include:$(INC_CXX):$(PATH)
endif


TARGET=server
OBJECTS=main.o interface.o server_i.o camera_i.o
ifeq ($(EMBEDDED),yes)
	CXXFLAGS:=-I./src -I. -I../../build/icee/cppe/include -I$(INC_CXX) $(CXXFLAGS)
	LIBS:=-lpthread -lrt -L../../build/emb/cppe/lib -lIceE -lIceEC
else
	CXXFLAGS:=-I./src -I. -I../../build/icee/cppe/include $(CXXFLAGS)
	LIBS:=-lpthread -lrt -L../../build/icee/cppe/lib -lIceE -lIceEC
endif

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFAGS) -o $@ $(OBJECTS) $(LIBS)
	
clean:
	rm -f *.o *.cpp *.h $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< 

interface.o: interface.cpp
main.o: main.cpp interface.cpp
server_i.o: server_i.cpp
camera_i.o: camera_i.cpp

main.cpp:
	cp ./src/main.cpp ./

server_i.cpp:
	cp ./src/server_i.cpp ./

camera_i.cpp:
	cp ./src/camera_i.cpp ./

interface.cpp:
	../../build/icee/cpp/bin/slice2cppe ../common/interface.ice

interface.h:
	../../build/icee/cpp/bin/slice2cppe ../common/interface.ice


	


