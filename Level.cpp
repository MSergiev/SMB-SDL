#include "Level.h"

Level::Level(){
	animationTimer = SDL_GetTicks();
	bgColor = {0, 0, 0, 0};
	for (int i = 0; i < MHEIGHT; ++i)
	   layout.push_back(std::vector<Block>(MLENGTH, Block()));	
	generate();
}

void Level::generate() 
{
	pugi::xml_document doc;
	pugi::xml_parse_result res = doc.load_file("Levels.xml");
	if(!res) { cerr << "ERROR: " << res.description() << endl; return; }
	pugi::xml_node levels = doc.first_child();
	for(pugi::xml_node level = levels.first_child(); level; level = level.next_sibling()){
		pugi::xml_attribute attr = level.first_attribute(); //Level info
		this->world = attr.as_int();
		attr = attr.next_attribute();
		this->level = attr.as_int();
		pugi::xml_node data = level.first_child(); //Level length
			attr = data.first_attribute();
			length = attr.as_int();

		data = data.next_sibling(); //Palette
			attr = data.first_attribute();
			palette = attr.as_int();

		data = data.next_sibling(); //Background data
			attr = data.first_attribute();
			if(attr.as_int() == 1) bgColor = {107, 140, 255, 255};
			else if(attr.as_int() == 2 ) bgColor = {255, 0, 0, 255};
			else bgColor = {0, 0, 0, 255};
			attr = attr.next_attribute();
			this->bgRepeat = attr.as_int();

		data = data.next_sibling(); //Generate background scenery
			for(int i = 0; i < length; i+=bgRepeat){
				pugi::xml_node env = data.first_child(); //Clouds
				for(pugi::xml_node sub = env.first_child(); sub; sub = sub.next_sibling()){
					attr = sub.first_attribute();
					int x = attr.as_int();
					attr = attr.next_attribute();
					int y = attr.as_int();
					attr = attr.next_attribute();
					int count = attr.as_int();
					layout[LHEIGHT-y][x+i] = Block(true, true, 0, 20, NOTHING, false, false);
					layout[LHEIGHT-y+1][x+i] = Block(true, true, 0, 21, NOTHING, false, false);
					for(int j = 0; j < count; j++){
						layout[LHEIGHT-y][x+1+i+j] = Block(true, true, 1, 20, NOTHING, false, false);
						layout[LHEIGHT-y+1][x+1+i+j] = Block(true, true, 1, 21, NOTHING, false, false);
					}
					layout[LHEIGHT-y][x+1+i+count] = Block(true, true, 2, 20, NOTHING, false, false);
					layout[LHEIGHT-y+1][x+1+i+count] = Block(true, true, 2, 21, NOTHING, false, false);
				}
				env = env.next_sibling(); //Bushes
				for(pugi::xml_node sub = env.first_child(); sub; sub = sub.next_sibling()){
					attr = sub.first_attribute();
					int x = attr.as_int();
					attr = attr.next_attribute();
					int y = attr.as_int();
					attr = attr.next_attribute();
					int count = attr.as_int();
					layout[LHEIGHT-y][x+i] = Block(true, true, 11, 9, NOTHING, false, false);
					for(int j = 0; j < count; j++)
						layout[LHEIGHT-y][x+1+i+j] = Block(true, true, 12, 9, NOTHING, false, false);
					layout[LHEIGHT-y][x+1+i+count] = Block(true, true, 13, 9, NOTHING, false, false);
				}
				env = env.next_sibling(); //Hills
				for(pugi::xml_node sub = env.first_child(); sub; sub = sub.next_sibling()){
					attr = sub.first_attribute();
					int x = attr.as_int();
					attr = attr.next_attribute();
					int y = attr.as_int();
					layout[LHEIGHT-y][x+i+2] = Block(true, true, 9, 8, NOTHING, false, false);
					layout[LHEIGHT-y+1][x+i+1] = Block(true, true, 8, 8, NOTHING, false, false);
					layout[LHEIGHT-y+1][x+i+2] = Block(true, true, 8, 9, NOTHING, false, false);
					layout[LHEIGHT-y+1][x+i+3] = Block(true, true, 10, 8, NOTHING, false, false);
					layout[LHEIGHT-y+2][x+i] = Block(true, true, 8, 8, NOTHING, false, false);
					layout[LHEIGHT-y+2][x+i+1] = Block(true, true, 8, 9, NOTHING, false, false);
					layout[LHEIGHT-y+2][x+i+2] = Block(true, true, 9, 9, NOTHING, false, false);
					layout[LHEIGHT-y+2][x+i+3] = Block(true, true, 10, 9, NOTHING, false, false);
					layout[LHEIGHT-y+2][x+i+4] = Block(true, true, 10, 8, NOTHING, false, false);
				}
			}

		data = data.next_sibling(); //Generate floor
			for(pugi::xml_node sub = data.first_child(); sub; sub = sub.next_sibling()){
				attr = sub.first_attribute();
				int from = attr.as_int();
				attr = attr.next_attribute();
				int length = attr.as_int();
				for(int i = from; i < from+length; ++i){
					layout[LHEIGHT+1][i] = Block(true, false, 0, 0, NOTHING, true, false);
					layout[LHEIGHT][i] = Block(true, false, 0, 0, NOTHING, true, false);
				}
			}

		data = data.next_sibling(); //Generate ceiling
			for(pugi::xml_node sub = data.first_child(); sub; sub = sub.next_sibling()){
				attr = sub.first_attribute();
				int from = attr.as_int();
				attr = attr.next_attribute();
				int length = attr.as_int();
				for(int i = from; i < from+length; ++i){
					layout[0][i] = Block(true, false, 1, 0, NOTHING, true, false);
					layout[1][i] = Block(true, false, 1, 0, NOTHING, true, false);
				}
			}
		data = data.next_sibling(); //Generate pipes
			for(pugi::xml_node sub = data.first_child(); sub; sub = sub.next_sibling()){
				attr = sub.first_attribute();
				int x = attr.as_int();
				attr = attr.next_attribute();
				int height = attr.as_int();
				layout[LHEIGHT-height][x-1] = Block(true, false, 0, 8, NOTHING, false, false);
				layout[LHEIGHT-height][x] = Block(true, false, 1, 8, NOTHING, false, false);
				for(int i = 1; i < height; ++i){
					layout[LHEIGHT-i][x-1] = Block(true, false, 0, 9, NOTHING, false, false);
					layout[LHEIGHT-i][x] = Block(true, false, 1, 9, NOTHING, false, false);
				}
			}

		data = data.next_sibling(); //Generate bricks
			for(pugi::xml_node sub = data.first_child(); sub; sub = sub.next_sibling()){
				attr = sub.first_attribute();
				int x = attr.as_int();
				attr = attr.next_attribute();
				int y = attr.as_int();
				layout[LHEIGHT-y+1][x] = Block(true, false, 1, 0, NOTHING, true, false);

			}

		data = data.next_sibling(); //Generate platforms 
			for(pugi::xml_node sub = data.first_child(); sub; sub = sub.next_sibling()){
				attr = sub.first_attribute();
				int x = attr.as_int();
				attr = attr.next_attribute();
				int y = attr.as_int();
				attr = attr.next_attribute();
				int length = attr.as_int();
				for(int i = x; i < x+length; ++i)
					layout[LHEIGHT-y+1][i] = Block(true, false, 0, 1, NOTHING, false, false);
			}

		data = data.next_sibling(); //Generate question blocks 
			for(pugi::xml_node sub = data.first_child(); sub; sub = sub.next_sibling()){
				attr = sub.first_attribute();
				int x = attr.as_int();
				attr = attr.next_attribute();
				int y = attr.as_int();
				attr = attr.next_attribute();
				int contains = attr.as_int();
				layout[LHEIGHT-y+1][x] = Block(true, false, 24, 0, static_cast<Item>(contains), false, true, 3, 1, 0);
			}

		data = data.next_sibling(); //Generate hidden blocks
		data = data.next_sibling(); //Generate enemies
		data = data.next_sibling(); //Generate end of stage
			attr = data.first_attribute();
			flagpole = attr.as_int();
			length = flagpole*16+128;
			createFlagpole();
			createCastle(5);
	}
}

void Level::render(int scroll)
{
	bool animate = (SDL_GetTicks()-animationTimer >= 500);
	SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	//SDL_RenderClear(mTileset.mRenderer);
		for(int i = 0; i < MHEIGHT; ++i){
			for(int j = 0; j < MLENGTH; ++j){
				if(layout[i][j].exists){
					if(layout[i][j].animated && animate){
						layout[i][j].texX+=layout[i][j].nextFrameX;
						if(layout[i][j].texX - layout[i][j].initX >= layout[i][j].frames) layout[i][j].texX=layout[i][j].initX;
						layout[i][j].texY+=layout[i][j].nextFrameY;
						if(layout[i][j].texY - layout[i][j].initY >= layout[i][j].frames) layout[i][j].texY=layout[i][j].initY;
						animationTimer = SDL_GetTicks();	
					}
					SDL_Rect tmp = {layout[i][j].texX*16,(layout[i][j].texY+palette*2)*16, 16, 16};
					tileset->render((j*16)-scroll, ZERO-(LHEIGHT-i)*16, &tmp);
				}
			}
		}
}

void Level::toTXT(){
	std::ofstream file("layout.txt");
	file << "Existing blocks: " << endl;
	for(int i = 0; i < MHEIGHT; ++i){
		for(int j = 0; j < MLENGTH; ++j){
			file << (!layout[i][j].exists?" ":"H");
		}	
		file << endl;
	}	
	file << "\nBreakable blocks: " << endl;
	for(int i = 0; i < MHEIGHT; ++i){
		for(int j = 0; j < MLENGTH; ++j){
			file << (!layout[i][j].breakable?" ":"H");
		}	
		file << endl;
	}
	file << "\nImpassable blocks: " << endl;
	for(int i = 0; i < MHEIGHT; ++i){
		for(int j = 0; j < MLENGTH; ++j){
			file << (layout[i][j].passThrough?" ":"H");
		}	
		file << endl;
	}
	file.close();
}

void Level::createFlagpole()
{
	layout[LHEIGHT-1][flagpole] = Block(true, false, 0, 1, NOTHING, false, false);
		for(int i = 0; i < 9; ++i)
			layout[LHEIGHT-i-2][flagpole] = Block(true, true, 16, 11, NOTHING, false, false);
		layout[LHEIGHT-11][flagpole] = Block(true, true, 16, 10, NOTHING, false, false);
}

void Level::createCastle(int height)
{   if(height==11){	
	layout[LHEIGHT-height+10][flagpole+4] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+10][flagpole+4+1] = Block(true, true, 2, 0, NOTHING, false, false);		
	layout[LHEIGHT-height+10][flagpole+4+2] = Block(true, true, 13, 1, NOTHING, false, false);
	layout[LHEIGHT-height+10][flagpole+4+3] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+10][flagpole+4+4] = Block(true, true, 13, 1, NOTHING, false, false);
	layout[LHEIGHT-height+10][flagpole+4+5] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+10][flagpole+4+6] = Block(true, true, 13, 1, NOTHING, false, false);
	layout[LHEIGHT-height+10][flagpole+4+7] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+10][flagpole+4+8] = Block(true, true, 2, 0, NOTHING, false, false);
	}
	if(height>=10){
	layout[LHEIGHT-height+9][flagpole+4] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+9][flagpole+4+1] = Block(true, true, 2, 0, NOTHING, false, false);		
	layout[LHEIGHT-height+9][flagpole+4+2] = Block(true, true, 12, 1, NOTHING, false, false);
	layout[LHEIGHT-height+9][flagpole+4+3] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+9][flagpole+4+4] = Block(true, true, 12, 1, NOTHING, false, false);
	layout[LHEIGHT-height+9][flagpole+4+5] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+9][flagpole+4+6] = Block(true, true, 12, 1, NOTHING, false, false);
	layout[LHEIGHT-height+9][flagpole+4+7] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+9][flagpole+4+8] = Block(true, true, 2, 0, NOTHING, false, false);
	}
	if(height>=9){
	layout[LHEIGHT-height+8][flagpole+4] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+8][flagpole+4+1] = Block(true, true, 2, 0, NOTHING, false, false);		
	layout[LHEIGHT-height+8][flagpole+4+2] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+8][flagpole+4+3] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+8][flagpole+4+4] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+8][flagpole+4+5] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+8][flagpole+4+6] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+8][flagpole+4+7] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+8][flagpole+4+8] = Block(true, true, 2, 0, NOTHING, false, false);
	}
	if(height>=8){
	layout[LHEIGHT-height+7][flagpole+4] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+7][flagpole+4+1] = Block(true, true, 2, 0, NOTHING, false, false);		
	layout[LHEIGHT-height+7][flagpole+4+2] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+7][flagpole+4+3] = Block(true, true, 13, 1, NOTHING, false, false);
	layout[LHEIGHT-height+7][flagpole+4+4] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+7][flagpole+4+5] = Block(true, true, 13, 1, NOTHING, false, false);
	layout[LHEIGHT-height+7][flagpole+4+6] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+7][flagpole+4+7] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+7][flagpole+4+8] = Block(true, true, 2, 0, NOTHING, false, false);
	}
	if(height>=7){
	layout[LHEIGHT-height+6][flagpole+4] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+6][flagpole+4+1] = Block(true, true, 2, 0, NOTHING, false, false);		
	layout[LHEIGHT-height+6][flagpole+4+2] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+6][flagpole+4+3] = Block(true, true, 12, 1, NOTHING, false, false);
	layout[LHEIGHT-height+6][flagpole+4+4] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+6][flagpole+4+5] = Block(true, true, 12, 1, NOTHING, false, false);
	layout[LHEIGHT-height+6][flagpole+4+6] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+6][flagpole+4+7] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+6][flagpole+4+8] = Block(true, true, 2, 0, NOTHING, false, false);
	}
	if(height>=6){
	layout[LHEIGHT-height+5][flagpole+4] = Block(true, true, 11, 0, NOTHING, false, false);
	layout[LHEIGHT-height+5][flagpole+4+1] = Block(true, true, 11, 0, NOTHING, false, false);	
	layout[LHEIGHT-height+5][flagpole+4+2] = Block(true, true, 11, 1, NOTHING, false, false);
	layout[LHEIGHT-height+5][flagpole+4+3] = Block(true, true, 11, 1, NOTHING, false, false);
	layout[LHEIGHT-height+5][flagpole+4+4] = Block(true, true, 11, 1, NOTHING, false, false);
	layout[LHEIGHT-height+5][flagpole+4+5] = Block(true, true, 11, 1, NOTHING, false, false);
	layout[LHEIGHT-height+5][flagpole+4+6] = Block(true, true, 11, 1, NOTHING, false, false);
	layout[LHEIGHT-height+5][flagpole+4+7] = Block(true, true, 11, 0, NOTHING, false, false);
	layout[LHEIGHT-height+5][flagpole+4+8] = Block(true, true, 11, 0, NOTHING, false, false);
	}
	if(height>=5){
	layout[LHEIGHT-height+4][flagpole+4+2] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+4][flagpole+4+3] = Block(true, true, 2, 0, NOTHING, false, false);		
	layout[LHEIGHT-height+4][flagpole+4+4] = Block(true, true, 13, 1, NOTHING, false, false);
	layout[LHEIGHT-height+4][flagpole+4+5] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+4][flagpole+4+6] = Block(true, true, 2, 0, NOTHING, false, false);
	}
	if(height>=4){
	layout[LHEIGHT-height+3][flagpole+4+2] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+3][flagpole+4+3] = Block(true, true, 2, 0, NOTHING, false, false);		
	layout[LHEIGHT-height+3][flagpole+4+4] = Block(true, true, 12, 1, NOTHING, false, false);
	layout[LHEIGHT-height+3][flagpole+4+5] = Block(true, true, 2, 0, NOTHING, false, false);
	layout[LHEIGHT-height+3][flagpole+4+6] = Block(true, true, 2, 0, NOTHING, false, false);
	}
	if(height>=3){
	layout[LHEIGHT-height+2][flagpole+4+2] = Block(true, true, 11, 0, NOTHING, false, false);
	layout[LHEIGHT-height+2][flagpole+4+3] = Block(true, true, 11, 1, NOTHING, false, false);	
	layout[LHEIGHT-height+2][flagpole+4+4] = Block(true, true, 11, 1, NOTHING, false, false);
	layout[LHEIGHT-height+2][flagpole+4+5] = Block(true, true, 11, 1, NOTHING, false, false);
	layout[LHEIGHT-height+2][flagpole+4+6] = Block(true, true, 11, 0, NOTHING, false, false);
	}
	if(height>=2){
	layout[LHEIGHT-height+1][flagpole+4+3] = Block(true, true, 12, 0, NOTHING, false, false);
	layout[LHEIGHT-height+1][flagpole+4+4] = Block(true, true, 13, 0, NOTHING, false, false);
	layout[LHEIGHT-height+1][flagpole+4+5] = Block(true, true, 14, 0, NOTHING, false, false);
	}
	if(height>=1){
	layout[LHEIGHT-height][flagpole+4+3] = Block(true, true, 11, 0, NOTHING, false, false);		
	layout[LHEIGHT-height][flagpole+4+4] = Block(true, true, 11, 0, NOTHING, false, false);
	layout[LHEIGHT-height][flagpole+4+5] = Block(true, true, 11, 0, NOTHING, false, false);	
	}
}

Level::~Level() {}
