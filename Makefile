#!/bin/sh
.SUFFIXES: .cpp .o

ver = release 

ROOTPATH=./
LIBPATH=./
#EXEPATH=$(ROOTPATH)/exe/release/

#INCL= $(shell find $(ROOTPATH)/include -maxdepth 1 -type d | xargs -i echo -I{})
#INCL= -I$(ROOTPATH)/include -I$(ROOTPATH)/include/CDCASAdapter -I$(ROOTPATH)/include/CDCASDBAdapter -I$(ROOTPATH)/include/SoapCAS -I$(ROOTPATH)/include/CDCASLogger -I$(ROOTPATH)/include/CDCASCommon -I$(ROOTPATH)/include/DB_CAS -I$(ROOTPATH)/include/drm_include -I./
INCL= -I./
#LIBS= -lrt -lpthread -L$(LIBPATH) -llogger -lcommon -ladapter -ldbcas -lecmgcomm -lencryptclient
LIBS1=-L./ -llucene.core
CC=g++ -g
LDMFLAGS= -Wl,-rpath=./ -shared -fPIC -std=c++0x -Wno-deprecated
LDMFLAGS1= -Wl,-rpath=./ -Wl,-rpath=$(LIBPATH)

ifeq ($(on),1)
        FLAGS += -Ddebug
endif

TARGET1=liblucene.core.so
TARGET2=main
all: $(TARGET1) 
CPPS1=Lock.cpp NativeFSLock.cpp FSLockFactory.cpp  NativeFSLockFactory.cpp 
CPPS2=main.o
$(TARGET1):$(CPPS1)
	$(CC) $(CXXFLAGS) $(LDMFLAGS) $(FLAGS) $(INCL) -o $@ $^ $(LIBS)
	#cp $(TARGET1) $(EXEPATH)
$(TARGET2):$(CPPS2)
	$(CC) $(LDMFLAGS1) $(FLAGS) -o $@ $? $(LIBS1)
clean:
	rm -f *.o $(TARGET1)
show:
	echo $(LIBS)

