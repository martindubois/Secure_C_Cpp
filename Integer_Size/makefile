
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           Integer_Size/makefile

OUTPUT = ../Binaries/Integer_Size

SOURCES = Integer_Size.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
