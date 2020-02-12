
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           Integer_Div_se/makefile

OUTPUT = ../Binaries/Integer_Div_se

SOURCES = Integer_Div_se.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
