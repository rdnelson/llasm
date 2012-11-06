SRC=main.cpp \
    InstTable.cpp \
    Parser.cpp \
    Command.cpp \
    Instruction.cpp \
    Variant.cpp

OBJ=$(SRC:%.cpp=%.o)
CC=g++
TARGET=lasm
CPPFLAGS=-Wall

debug: CPPFLAGS+=-DDEBUG -g
debug: $(TARGET)

release: CPPFLAGS+=-O2
release: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

clean:
	$(RM) *.o $(TARGET)
