
COMMON_CLASS_NAME = cmnclass.1
COMMON_CLASS_VERSION = cmnclass.1.0
COMMON_CLASS_LIB_NAME = lib$(COMMON_CLASS_NAME).a
COMMON_CLASS_LIB_VERSION = lib$(COMMON_CLASS_VERSION).a



#OPTFLAGS = -O3 -fforce-addr -fomit-frame-pointer -funroll-loops -frerun-cse-after-loop -frerun-loop-opt
OPTFLAGS = -O3 -fomit-frame-pointer -funroll-loops
#OPTFLAGS = -g -Wall
CFLAGS = $(OPTFLAGS) $(CINCLUDE)
CC = g++



COMMON_CLASS_FILES = cmn_algebra.o cmn_logger.o cmn_mutex.o cmn_random.o cmn_string_proc.o cmn_utils.o

libcmnclass.a:	$(COMMON_CLASS_FILES)
		ar rcv $(COMMON_CLASS_LIB_VERSION) $(COMMON_CLASS_FILES)


#######

#  $<  : is the name of the related file that caused the action.
#  $@  : is the name of the file to be mad.

.cpp.o:
	$(CC) $(CFLAGS) -c $<


cmn_algebra.o:	cmn_algebra.h cmn_algebra.cpp
		$(CC) $(CFLAGS) -c cmn_algebra.cpp

cmn_logger.o:	cmn_logger.h cmn_logger.cpp
		$(CC) $(CFLAGS) -c cmn_logger.cpp

cmn_mutex.o:	cmn_mutex.h cmn_mutex.cpp
		$(CC) $(CFLAGS) -c cmn_mutex.cpp

cmn_random.o:	cmn_random.h cmn_random.cpp
		$(CC) $(CFLAGS) -c cmn_random.cpp

cmn_string_proc.o:	cmn_string_proc.h cmn_string_proc.cpp
			$(CC) $(CFLAGS) -c cmn_string_proc.cpp

cmn_utils.o:	cmn_utils.h cmn_utils.cpp
		$(CC) $(CFLAGS) -c cmn_utils.cpp




GLOBAL_PATH = /usr/local


installglobal:
		cp $(COMMON_CLASS_LIB_VERSION) $(GLOBAL_PATH)/lib/$(COMMON_CLASS_LIB_VERSION)
		rm -f $(GLOBAL_PATH)/lib/$(COMMON_CLASS_LIB_NAME)
		ln -s $(COMMON_CLASS_LIB_VERSION) $(GLOBAL_PATH)/lib/$(COMMON_CLASS_LIB_NAME)
		rm -rf $(GLOBAL_PATH)/include/$(COMMON_CLASS_VERSION)
		-mkdir $(GLOBAL_PATH)/include/$(COMMON_CLASS_VERSION)
		cp *.h $(GLOBAL_PATH)/include/$(COMMON_CLASS_VERSION)
		rm -f $(GLOBAL_PATH)/include/$(COMMON_CLASS_NAME)
		ln -s $(COMMON_CLASS_VERSION) $(GLOBAL_PATH)/include/$(COMMON_CLASS_NAME)


installusr:
		cp $(COMMON_CLASS_LIB_VERSION) $(HOME)/lib/$(COMMON_CLASS_LIB_VERSION)
		rm -f $(HOME)/lib/$(COMMON_CLASS_LIB_NAME)
		ln -s $(COMMON_CLASS_LIB_VERSION) $(HOME)/lib/$(COMMON_CLASS_LIB_NAME)
		rm -rf $(HOME)/include/$(COMMON_CLASS_VERSION)
		-mkdir $(HOME)/include/$(COMMON_CLASS_VERSION)
		cp *.h $(HOME)/include/$(COMMON_CLASS_VERSION)
		rm -f $(HOME)/include/$(COMMON_CLASS_NAME)
		ln -s $(COMMON_CLASS_VERSION) $(HOME)/include/$(COMMON_CLASS_NAME)



clean:
	$(RM) *.o
	$(RM) $(COMMON_CLASS_VERSION)







