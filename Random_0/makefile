
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           Random_0/makefile

OUTPUT = ../Binaries/Random_0

SOURCES = Random_0.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
