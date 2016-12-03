#include "level.h"
#include "graphics.h"
#include <SDL.h>
#include "globals.h"
#include "tinyxml2.h"
#include <sstream>
#include <algorithm>
#include <cmath>
#include "utile.h"
#include "slope.h"

using namespace tinyxml2;

Level::Level()
{
	
}
//Note to self
//Colon after class declaration means
//Initialising member variables before the body of the constructor executes.
Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &_graphics) :
_mapName(mapName), _spawnPoint(spawnPoint), _size(Vector2(0, 0))
{
	this->loadMap(mapName, _graphics);
}

Level::~Level()
{

}


//****************************************************************************//
//very important
//review multiple times if needed
//****************************************************************************//
void Level::loadMap(std::string mapName, Graphics &_graphics)
{
	//Parse the .tmx file
	XMLDocument doc;	//entire XML doc
	std::stringstream ss;
	ss << mapName << ".tmx";
	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");	//selects the first child element from the doc variable

	//Get width and height of the whole map and store it in the _size
	int width;
	int height;
	mapNode->QueryIntAttribute("width", &width); //will search for the "width" element and then store it in our width variable
	mapNode->QueryIntAttribute("height", &height);
	this->_size = Vector2(width, height); //at this point we have the size of our map

	//Get width and height of the tiles and store it in our tilesize variable
	int tileWidth;
	int tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth); //will search for the "width" element and then store it in our width variable
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->_tileSize = Vector2(tileWidth, tileHeight); //at this piont we have the size our our tiles

	//Load the tilesets
	XMLElement *pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != NULL)
	{
		while (pTileset)
		{
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");	//gets us the attribute (source) of the child element (image). think of linked lists
			char* path;
			std::stringstream ss;
			ss << source;
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture *tex = SDL_CreateTextureFromSurface(_graphics.getRenderer(), _graphics.loadImage(ss.str()));
			this->_tilesets.push_back(Tileset(tex, firstgid));
			//Tilesets are loaded
			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	//Loading the layers
	XMLElement *pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != NULL)
	{
		while (pLayer)
		{
			//Loading the data element
			XMLElement *pData = pLayer->FirstChildElement("data");
			if (pData!=NULL)
			{
				while (pData)
				{
					//Loading the tile element
					XMLElement *pTile = pData->FirstChildElement("tile");
					if (pTile != NULL)
					{
						int tileCoutner = 0;
						while (pTile)
						{
							//Build each individual tile here
							//If gid=0 no tile should be drawn. Continue loop
							if (pTile->IntAttribute("gid") == 0)
							{
								tileCoutner++;
								if (pTile->NextSiblingElement("tile"))
								{
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else
								{
									break;
								}
							}
							//get the tileset for this specific gid
							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							for (int i= 0; i < this->_tilesets.size(); i++)
							{
								//not sure I understand this
								if (this->_tilesets[i].FirstGid <= gid)
								{
									//This is the tileset we want
									tls = this->_tilesets.at(i);
									break;
								}
							}

							if (tls.FirstGid == -1)
							{
								//No tileset was found for this gid
								tileCoutner++;
								if (pTile->NextSiblingElement("tile"))
								{
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else
								{
									break;
								}
							}

							//Get the position of the tile in the level
							int xx = 0;
							int yy = 0;
							xx = tileCoutner % width;	//which gid we're on % width
							xx *= tileWidth; //times that by 16 and this gives us the x cord to place the tile on the map
							yy += tileHeight *(tileCoutner / width);	//gives us the y cord to place the tile on the map
							Vector2 finalTilePosition = Vector2(xx, yy);

							//Calcualte the position of the tile in the tileset
							int tilesetWidth;
							int tilesetHeight;
							SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
							int tsxx = gid % (tilesetWidth / tileWidth) - 1; //(first gid) 34 % (256/16) -1 = 1 
							tsxx *= tileWidth; // 1*16
							int tsyy = 0;
							int amount = (gid / (tilesetWidth / tileWidth));
							tsyy = tileHeight * amount;
							Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);

							//Build the actual tile and add it to the level's tile list
							Tile tile(tls.Texture, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
							this->_tileList.push_back(tile);
							tileCoutner++;

							pTile = pTile->NextSiblingElement("tile");
							
						}
					}
					pData = pData->NextSiblingElement("data");
				}
			}
			pLayer = pLayer->NextSiblingElement("layer");
		}
	}

	//Parse out the collisions 
	XMLElement *pObjectGroup = mapNode->FirstChildElement("objectgroup");
	if (pObjectGroup != NULL)
	{
		while (pObjectGroup)
		{
			const char* name = pObjectGroup->Attribute("name");
			std::stringstream ss;
			ss << name;
			if (ss.str() == "collisions")
			{
				XMLElement *pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL)
				{
					while (pObject)
					{
						float x;
						float y;
						float width;
						float height;
						//get the values of each from the current pObject
						x = pObject->FloatAttribute("x");
						y = pObject->FloatAttribute("y"); 
						width = pObject->FloatAttribute("width");
						height = pObject->FloatAttribute("height");
						//add this new collision rectangle to the collsion rectangle vector
						this->_collisionRects.push_back(Rectangle(
							std::ceil(x)*globals::SPRITE_SCALE,
							std::ceil(y)*globals::SPRITE_SCALE,
							std::ceil(width)*globals::SPRITE_SCALE,
							std::ceil(height)*globals::SPRITE_SCALE));

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			//other object groups go here with an else if (ss.str()=="whatever")
			else if (ss.str() == "slopes")
			{
				XMLElement *pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL)
				{
					while (pObject)
					{
						std::vector<Vector2> points; //holds all points in slope
						Vector2 p1;
						p1 = Vector2(std::ceil(pObject->FloatAttribute("x")), std::ceil(pObject->FloatAttribute("y"))); //p1 is just the x and y value of each object in the XML
						XMLElement *pPolyline = pObject->FirstChildElement("polyline");
						if (pPolyline != NULL)
						{
							std::vector<std::string> pairs;
							const char* pointString = pPolyline->Attribute("points");
							std::stringstream ss;
							ss << pointString;
							Utile::split(ss.str(), pairs, ' '); //split will get all of the pairs for us
							//Now we have each of the pairs. Loop through the list of pairs and split them into Vector2s and
							//then store them in our points vector
							for (int i = 0; i < pairs.size(); i++)
							{
								//need to review this
								std::vector<std::string> ps;
								Utile::split(pairs.at(i), ps, ',');
								points.push_back(Vector2(std::stoi(ps.at(0)), stoi(ps.at(1)))); //only using 2 points because each slope only has 2 points

							}
						}

						for (int i = 0; i < points.size(); i += 2) //ep 11 @ 51 mins
						{
							this->_slopes.push_back(Slope
								(Vector2((p1.x + points.at(i < 2 ? i : i - 1).x)*globals::SPRITE_SCALE, 
										 (p1.y + points.at(i < 2 ? i : i - 1).y)*globals::SPRITE_SCALE),
								 Vector2((p1.x + points.at(i < 2 ? i + 1 : i).x)*globals::SPRITE_SCALE,
										 (p1.y + points.at(i < 2 ? i + 1 : i).y)*globals::SPRITE_SCALE)));
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			else if (ss.str() == "spawnpoints"){
				XMLElement *pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL)
				{
					while (pObject)
					{
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						const char* name = pObject->Attribute("name");
						//get the values for x, y, and name
						std::stringstream ss;
						ss << name;
						//check if "name" is player. checks if we're parsing the right information
						if (ss.str() == "player")
						{
							//set the spawn point eqaul to the XML information just parsed
							this->_spawnPoint = Vector2(std::ceil(x)*globals::SPRITE_SCALE, std::ceil(y)*globals::SPRITE_SCALE);
						}
						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
		}
	}
}

void Level::update(int elaspedTime)
{
	
}

//returns every collision rectangle we're colliding with
std::vector<Rectangle> Level::checkTileCollision(const Rectangle &other)
{
	std::vector<Rectangle> others;
	for (int i = 0; i < this->_collisionRects.size(); i++)
	{
		//if one of the collisionrects collides with &other. add it to the other list
		if (this->_collisionRects.at(i).colidesWith(other))
		{
			others.push_back(this->_collisionRects.at(i));
		}
	}
	return others;
}

std::vector<Slope> Level::checkSlopeCollision(const Rectangle &other)
{
	std::vector<Slope>others;
	for (int i = 0; i < this->_slopes.size(); i++)
	{
		if (this->_slopes.at(i).collidesWith(other))
		{
			others.push_back(this->_slopes.at(i));
		}
	}
	return others;
}
 
void Level::draw(Graphics &_grahpics)
{
	for (int i = 0; i < this->_tileList.size(); i++)
	{
		this->_tileList.at(i).draw(_grahpics);
	}
}

const Vector2 Level::getPlayerSpawnPonit()const
{
	return this->_spawnPoint;
}
