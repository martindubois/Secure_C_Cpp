
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# Course         05 - Random number generation
# Video          03 - Better random
# File           Random_0_a/makefile

OUTPUT = ../Binaries/Random_0_a

SOURCES = Random_0_a.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	g++ -o $@ $^
