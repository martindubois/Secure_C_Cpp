
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           BO_Dynamic/makefile

LIBRARIES = ../Libraries/BaseLib.a

OUTPUT = ../Binaries/BO_Dynamic

SOURCES = BO_Dynamic.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^
