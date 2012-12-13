
ifeq ("$(shell whoami)", "malloy")
  CXX = clang++
else
	CXX = g++
endif
CXX_LINK = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0
LDFLAGS = `sdl-config --libs` -lSDL_ttf -lSDL_image -lexpat -lSDL_mixer

OBJS = \
	main.o \
	manager.o \
	menuManager.o \
	menu.o \
	world.o \
	viewport.o \
	gamedata.o \
	parseXML.o \
	clock.o \
	vector2f.o \
	sprite.o \
	frame.o \
	ioManager.o \
	multiFrameSprite.o \
	frameFactory.o \
	spriteManager.o \
	surfaceFactory.o \
	player.o \
	bulletFactory.o \
	collisionStrategy.o \
	explodingSprite.o \
	chunk.o \
	sound.o \

EXEC = run

# $< refers to the first dependency
%.o: %.cpp
	$(CXX_LINK) $(CXXFLAGS) -c $< -o $@

# $@ refers to the target
$(EXEC): $(OBJS)
	g++ $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.cpp
manager.o: manager.cpp manager.h gamedata.h ioManager.h sprite.h clock.h explodingSprite.h sound.h
menuManager.o: menuManager.cpp menuManager.h ioManager.h menu.h
menu.o: menu.cpp menu.h frame.h ioManager.h vector2f.h parseXML.h 
ioManager.o: ioManager.cpp ioManager.h
world.o: world.cpp world.h
viewport.o: viewport.cpp viewport.h
parseXML.o: parseXML.cpp parseXML.h
gamedata.o: gamedata.cpp gamedata.h parseXML.h
clock.o: clock.cpp clock.h
vector2f.o: vector2f.cpp vector2f.h
frame.o: frame.cpp frame.h
sprite.o: sprite.cpp sprite.h drawable.h frame.h
multiFrameSprite.o: multiFrameSprite.cpp multiFrameSprite.h drawable.h frame.h
spriteManager.o: spriteManager.cpp spriteManager.h sprite.h multiFrameSprite.h frameFactory.h
frameFactory.o: frameFactory.h	frameFactory.cpp frame.h ioManager.h gamedata.h 
surfaceFactory.o: surfaceFactory.h surfaceFactory.cpp ioManager.h gamedata.h
frame.o: frame.cpp frame.h ioManager.h
player.o: player.cpp player.h multiFrameSprite.h gamedata.h
bulletFactory.o: sprite.h frameFactory.h
collisionStrategy.o: collisionStrategy.h collisionStrategy.cpp drawable.h 
explodingSprite.o: explodingSprite.cpp explodingSprite.h chunk.h
chunk.o: chunk.cpp chunk.h sprite.h gamedata.h
sound.o: sound.cpp sound.h  

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
