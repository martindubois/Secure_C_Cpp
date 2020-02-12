
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           String_0/makefile

OUTPUT = ../Binaries/String_0

SOURCES = String_0.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
