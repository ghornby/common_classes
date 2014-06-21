LIBRARY_ROOT_PATH = $(HOME)

COMMON_CLASSES_VERSION = cmnclass.1
COMMON_CLASSES_LIB_NAME = lib$(COMMON_CLASSES_VERSION).a
COMMON_CLASSES_INC_PATH = $(LIBRARY_ROOT_PATH)/include/$(COMMON_CLASSES_VERSION)/


PROJECT_INCLUDES = \
		-I$(COMMON_CLASSES_INC_PATH)



#OPTFLAGS = -Wall -O3 -march=i686 -fforce-addr -fomit-frame-pointer -funroll-loops -frerun-cse-after-loop -frerun-loop-opt -falign-functions=4
#OPTFLAGS = -Wall -O2 -march=i686 -fforce-addr -fomit-frame-pointer -funroll-loops -frerun-cse-after-loop -frerun-loop-opt -falign-functions=4
#OPTFLAGS = -Wall -O2 -fforce-addr -fomit-frame-pointer -funroll-loops -frerun-cse-after-loop -frerun-loop-opt -falign-functions=4
OPTFLAGS = -g -Wall


CFLAGS = $(OPTFLAGS) $(PROJECT_INCLUDES)


CC = g++


LINK =  -L$(LIBRARY_ROOT_PATH)/lib \
	-l$(COMMON_CLASSES_VERSION) \
	-lm -lstdc++ -lgmp -lgmpxx -pthread

TARGETS = \
	rand1




all:	$(TARGETS)


clean:
	$(RM) *.o
	$(RM) $(TARGETS)


main.o:		main.cpp
		$(CC) $(CFLAGS) -c main.cpp

rand1:		main.o
		$(CC) $(CFLAGS) main.o $(LINK) -o rand1
