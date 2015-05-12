CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD
OBJECTS = Main.o Animation.o AnimatedSprite.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = Animate
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LIBS}

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${DEPENDS} ${EXEC}