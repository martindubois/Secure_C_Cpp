
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           Integer_Compare/makefile

OUTPUT = ../Binaries/Integer_Compare

SOURCES = Integer_Compare.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
