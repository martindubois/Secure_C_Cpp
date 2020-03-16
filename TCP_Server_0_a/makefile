
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# Course         03 - Interacting with the world
# Video          07 - Sockets
# File           TCP_Server_0_a/makefile

LIBRARIES = ../Libraries/BaseLib.a

OUTPUT = ../Binaries/TCP_Server_0_a

SOURCES = TCP_Server_0_a.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^
