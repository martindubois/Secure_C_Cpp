
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           BO_Global/makefile

LIBRARIES = ../Libraries/BaseLib.a

OUTPUT = ../Binaries/BO_Global

SOURCES = BO_Global.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^
