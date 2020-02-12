
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           DynamicMemory/makefile

LIBRARIES = ../Libraries/BaseLib.a

OUTPUT = ../Binaries/DynamicMemory

SOURCES = DynamicMemory.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^
