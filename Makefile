CC=gcc
JAVAH=javah
JAVAC=javac
CFLAGS=
JNIINC=/usr/lib/jvm/java-7-openjdk-armhf/include/
INCLUDE=$(JNIINC)
LIBS=wiringPi
OUTPUT=target/
APPINC=src/main/native/
JAVASRC=src/main/java/
CSRC=src/main/native/
CLASS_PATH = ../bin
#vpath %.class $(CLASS_PATH)

all: GPIOController

GPIOController: GPIOController.h
	$(CC) $(CFLAGS) -shared -I $(INCLUDE) -l $(LIBS) -o $(OUTPUT)libGPIOController.so $(CSRC)GPIOController.c 
GPIOController.h: GPIOController.class
	$(JAVAH) -d $(APPINC) -classpath $(OUTPUT) com.wattu.sidpi.impl.GPIOControllerImpl
GPIOController.class:
	$(JAVAC) -classpath $(OUTPUT) -d $(OUTPUT) $(JAVASRC)com/wattu/test/sidpi/impl/*.java $(JAVASRC)com/wattu/sidpi/impl/*.java $(JAVASRC)com/wattu/sidpi/console/*.java $(JAVASRC)com/wattu/sidpi/*.java
clean:
	rm -Rf $(OUTPUT)* 
	rm -Rf $(APPINC)*.h
