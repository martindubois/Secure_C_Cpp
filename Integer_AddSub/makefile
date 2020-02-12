
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           Integer_AddSub/makefile

OUTPUT = ../Binaries/Integer_AddSub

SOURCES = Integer_AddSub.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
