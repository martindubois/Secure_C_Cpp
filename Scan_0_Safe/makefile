
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           Scan_0_Safe/makefile

OUTPUT = ../Binaries/Scan_0_Safe

SOURCES = Scan_0_Safe.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
