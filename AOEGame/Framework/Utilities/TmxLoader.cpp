#include "TmxLoader.h"

#include "../Renderer/Texture/TextureManager.h"
#include "../GameObjects/Components/StaticComponent.h"

namespace Framework
{
	TmxLoader::TmxLoader(std::string file)
		: m_file(file)
	{		
		m_tileSets = new vector<TileSet*>();
	}

	TmxLoader::~TmxLoader()
	{
	}

	bool TmxLoader::_checkValid()
	{
		return true;
	}

	bool TmxLoader::_parseMap()
	{
		return true;
	}

	TileMap* TmxLoader::GetTileMap()
	{
		return m_tileMap;
	}

	bool TmxLoader::Load()
	{
		// check file valid

		// Read the xml file into a vector
		ifstream theFile(m_file.c_str());
		if(theFile.fail())
			return false;
		vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
		buffer.push_back('\0');
		// Parse the buffer using the xml file parsing library into doc 
		m_doc.parse<0>(&buffer[0]);
		m_rootNode = m_doc.first_node("map");
		if(m_rootNode == NULL)
			return false;

		// Parse map elements		
		int tileWidth = atoi(m_rootNode->first_attribute("tilewidth")->value());
		int tileHeight = atoi(m_rootNode->first_attribute("tileheight")->value());
		int width = atoi(m_rootNode->first_attribute("width")->value());
		int height = atoi(m_rootNode->first_attribute("height")->value());
		std::string orientation = m_rootNode->first_attribute("orientation")->value();

		m_tileMap = new TileMap(tileWidth, tileHeight, width, height);

		// Parse Tilesets elements
		int firstgid, tileSetWidth, tileSetHeight, dimensionX, dimensionY;
		string tileSetName, imageSourceName;
		for(xml_node<> * tileSetNode = m_rootNode->first_node("tileset"); tileSetNode; 
			tileSetNode = tileSetNode->next_sibling("tileset"))
		{
			firstgid = atoi(tileSetNode->first_attribute("firstgid")->value());
			tileSetWidth = atoi(tileSetNode->first_attribute("tilewidth")->value());
			tileSetHeight = atoi(tileSetNode->first_attribute("tileheight")->value());
			tileSetName = tileSetNode->first_attribute("name")->value();

			xml_node<> * imageNode = tileSetNode->first_node("image");
			imageSourceName = imageNode->first_attribute("source")->value();
			dimensionX = (atoi(imageNode->first_attribute("width")->value()) / tileSetWidth);
			dimensionY = (atoi(imageNode->first_attribute("height")->value()) / tileSetHeight);
			//Register texture
			RegisterTexture(imageSourceName);

			
			TileSet* tileSet = new TileSet(firstgid, tileSetWidth, tileSetHeight, imageSourceName, dimensionX, dimensionY, tileSetName);
			
			m_tileSets->push_back(tileSet);
		}

		//Parse map data
		xml_node<> *mapLayer = m_rootNode->first_node("layer");
		string mapLayerName = mapLayer->first_attribute("name")->value();
		int mapLayerWidth = atoi(mapLayer->first_attribute("width")->value());
		int mapLayerHeight = atoi(mapLayer->first_attribute("height")->value());
		// Allocate mapdata
		/*int** mapData = new int*[mapLayerHeight];
		for(int i =0; i < mapLayerHeight; i++)
			mapData[i] = new int[mapLayerWidth];*/
		vector<int>* mapData = new vector<int>();
		xml_node<> * data = mapLayer->first_node("data");
		xml_node<> * tileNode;
		for(tileNode = data->first_node("tile"); tileNode; tileNode = tileNode->next_sibling())
		{
			mapData->push_back(atoi(tileNode->first_attribute("gid")->value()));
		}

		m_tileMap->SetTileSets(m_tileSets);
		m_tileMap->SetMapData(mapData);

		// Parse object group
		xml_node<> *objectLayer = m_rootNode->first_node("objectgroup");
		xml_node<> *objectNode;
		vector<GameObject*> gameObjects;
		objectNode = objectLayer->first_node("object");
		for (objectNode = objectLayer->first_node("object"); objectNode; objectNode = objectNode->next_sibling())
		{
			GameObject* gameObj = new GameObject();
			gameObj->AddComponent<StaticComponent>();
			StaticComponent* pStaticComponent = component_cast<StaticComponent>(gameObj);
			if (pStaticComponent)
			{
				int x = atoi(objectNode->first_attribute("x")->value());
				int y = atoi(objectNode->first_attribute("y")->value());
				int width = atoi(objectNode->first_attribute("width")->value());
				int height = atoi(objectNode->first_attribute("height")->value());

				
				int mapWidth = m_tileMap->GetWidth() * m_tileMap->GetTileWidth();
				int mapHeight = m_tileMap->GetHeight() * m_tileMap->GetTileHeight();

				int screenWidth = GameConfig::GetSingletonPtr()->GetInt(ConfigKey::GAME_WIDTH);
				int screenHeight = GameConfig::GetSingletonPtr()->GetInt(ConfigKey::GAME_HEIGHT);

				float scaleRatio = (float)screenHeight / (float)mapHeight;
				D3DXMATRIX transform_scale;
				D3DXMatrixAffineTransformation2D(&transform_scale, scaleRatio, NULL, NULL, NULL);

				D3DXVECTOR4 pointOrigin, resultTrans;
				pointOrigin.x = x;
				pointOrigin.y = y;
				
				D3DXVec4Transform(&resultTrans, &pointOrigin, &transform_scale);

				RECT bound;
				bound.left = resultTrans.x;
				bound.right = resultTrans.x + width * scaleRatio;
				bound.top = resultTrans.y;
				bound.bottom = resultTrans.y + height * scaleRatio;
				pStaticComponent->SetBound(bound);

				pStaticComponent->Initialize();
			}
			gameObjects.push_back(gameObj);
		}
		m_tileMap->SetObjects(&gameObjects);
		return true;
	}
}