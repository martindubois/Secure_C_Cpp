
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           BO_Local/makefile

LIBRARIES = ../Libraries/BaseLib.a

OUTPUT = ../Binaries/BO_Local

SOURCES = BO_Local.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^
