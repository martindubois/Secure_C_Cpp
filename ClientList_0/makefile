
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# Course         03 - Interacting with the world
# Video          04 - Files
# Example        ClientList_0
# File           ClientList_0/makefile

OUTPUT = ../Binaries/ClientList_0

SOURCES = ClientList_0.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS) $(LIBRARIES)
	g++ -o $@ $^
