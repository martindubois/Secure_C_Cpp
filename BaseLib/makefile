
# Author         Martin Dubois, P.Eng.
# Learning path  Secure C/C++
# File           BaseLib/makefile

OUTPUT = ../Libraries/BaseLib.a

SOURCES = Dump.cpp   \
          Socket.cpp \
	      Verify.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c -o $@ $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Target ==============================================================

$(OUTPUT) : $(OBJECTS)
	ar r $@ $^
	ranlib $@
