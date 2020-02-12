
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           String_STL/makefile

OUTPUT = ../Binaries/String_STL

SOURCES = String_STL.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
