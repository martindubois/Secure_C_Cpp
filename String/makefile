
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           String/makefile

OUTPUT = ../Binaries/String

SOURCES = String.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
