
REL_PATH:=~/projects/openwrt/OpenWrt-Toolchain-brcm47xx-for-mipsel-gcc-4.3.3+cs_uClibc-0.9.30.1/toolchain-mipsel_gcc-4.3.3+cs_uClibc-0.9.30.1/usr
CC:=$(REL_PATH)/bin/mipsel-openwrt-linux-gcc
CXX:=$(REL_PATH)/bin/mipsel-openwrt-linux-g++
PATH:=$(REL_PATH)/lib:$(REL_PATH)/include:$(PATH)
INC_CXX:= $(REL_PATH)/mipsel-openwrt-linux/include/c++/4.3.3

LIBS:=-nodefaultlibs -lgcc -lc -lstdc++
#LDFLAGS:="-nostdinc++"
LDFLAGS:=
CXXFLAGS:=-I$(INC_CXX)


#all:
#	echo $(REL_PATH)
#	echo $(CC)
#	echo $(PATH)

# build helloworld executable when user executes "make"
helloworld: helloworld.o
	$(CXX) $(LDFLAGS) helloworld.o -o helloworld $(LIBS)
helloworld.o: helloworld.cpp
	$(CXX) $(CXXFLAGS) -c helloworld.cpp

# remove object files and executable when user executes "make clean"
clean:
	rm *.o helloworld
	
