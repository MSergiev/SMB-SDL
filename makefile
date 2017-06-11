test: main.cpp Params.h Texture.cpp Text.cpp Sound.cpp Level.cpp Player.cpp
	g++ -o test main.cpp Params.h Texture.cpp Text.cpp Sound.cpp Level.cpp Player.cpp -lpugixml -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
