
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           Scan_0/makefile

OUTPUT = ../Binaries/Scan_0

SOURCES = Scan_0.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
