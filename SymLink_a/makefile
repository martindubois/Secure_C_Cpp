
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# Course         03 - Interacting with the world
# Video          06 - File name validation
# File           SymLink_a/makefile

OUTPUT = ../Binaries/SymLink_a

SOURCES = SymLink_a.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^
