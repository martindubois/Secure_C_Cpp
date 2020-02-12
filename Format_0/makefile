
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           Format_0/makefile

LIBRARIES = ../Libraries/BaseLib.a

OUTPUT = ../Binaries/Format_0

SOURCES = Format_0.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^
