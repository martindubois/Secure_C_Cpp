
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           Scan_0_a/makefile

OUTPUT = ../Binaries/Scan_0_a

SOURCES = Scan_0_a.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
