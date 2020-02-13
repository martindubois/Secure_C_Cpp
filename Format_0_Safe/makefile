
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           Format_0_Safe/makefile

LIBRARIES = ../Libraries/BaseLib.a

OUTPUT = ../Binaries/Format_0_Safe

SOURCES = Format_0_Safe.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^
