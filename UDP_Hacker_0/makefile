
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           UDP_Hacker_0/makefile

LIBRARIES = ../Libraries/BaseLib.a

OUTPUT = ../Binaries/UDP_Hacker_0

SOURCES = UDP_Hacker_0.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^
