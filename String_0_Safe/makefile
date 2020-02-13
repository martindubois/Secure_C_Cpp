
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           String_0_Safe/makefile

OUTPUT = ../Binaries/String_0_Safe

SOURCES = String_0_Safe.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
