
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# Course         03 - Interacting with the world
# Video          04 - Files
# Example        ClientList_0_a
# File           ClientList_0_a/makefile

OUTPUT = ../Binaries/ClientList_0_a

SOURCES = ClientList_0_a.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^
