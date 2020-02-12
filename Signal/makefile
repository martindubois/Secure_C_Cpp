
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           Signal/makefile

LIBRARIES = ../Libraries/BaseLib.a

OUTPUT = ../Binaries/Signal

SOURCES = Signal.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^
