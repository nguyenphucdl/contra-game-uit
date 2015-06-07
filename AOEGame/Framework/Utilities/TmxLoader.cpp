#include "TmxLoader.h"

#include "../Renderer/Texture/TextureManager.h"
#include "../GameObjects/Components/StaticComponent.h"
#include "../GameObjects/Components/CollisionComponent.h"
#include "../EventManager/EventManager.h"
#include "../Collision/CollisionManager.h"
#include "../Utilities/Utils.h"
#include "../Quadtree/QuadtreeLoader.h"

namespace Framework
{
	TmxLoader::TmxLoader(std::string file)
		: m_file(file)
		, m_scaleRatio(1.0f)
	{		
		m_tileSets = new vector<TileSet*>();
		m_basePath = Utils::getPathOfFile(file);
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

	float TmxLoader::GetScaleRatio()
	{
		return m_scaleRatio;
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

			std::string texturePath = imageSourceName;
			if (Utils::isPath(m_basePath))
				texturePath = m_basePath + "\\" + imageSourceName;

			//Register texture
			RegisterTexture(texturePath);

			
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
		if (objectLayer != NULL)
		{
			xml_node<> *objectNode;
			vector<GameObject*>* gameObjects = new vector<GameObject*>();
			std::tr1::unordered_map<ObjectId, GameObject*>* m_objectHashTable = new std::tr1::unordered_map<ObjectId, GameObject*>();

			objectNode = objectLayer->first_node("object");
			for (objectNode = objectLayer->first_node("object"); objectNode; objectNode = objectNode->next_sibling())
			{
				
				int id = atoi(objectNode->first_attribute("id")->value());
				int type = atoi(objectNode->first_attribute("type")->value());
				GameObject* gameObj = new GameObject(id);
				gameObj->SetType(type);

				if (type)//Switch Type
				{

				}
				gameObj->AddComponent<StaticComponent>();
				gameObj->AddComponent<CollisionComponent>();

				StaticComponent* pStaticComponent = component_cast<StaticComponent>(gameObj);
				CollisionComponent* pStaticCollisionComponent = component_cast<CollisionComponent>(gameObj);
				if (pStaticComponent && pStaticCollisionComponent)
				{
					int x = atoi(objectNode->first_attribute("x")->value());
					int y = atoi(objectNode->first_attribute("y")->value());
					int width = atoi(objectNode->first_attribute("width")->value());
					int height = atoi(objectNode->first_attribute("height")->value());


					int mapWidth = m_tileMap->GetWidth() * m_tileMap->GetTileWidth();
					int mapHeight = m_tileMap->GetHeight() * m_tileMap->GetTileHeight();

					int screenWidth = GameConfig::GetSingletonPtr()->GetInt(ConfigKey::GAME_WIDTH);
					int screenHeight = GameConfig::GetSingletonPtr()->GetInt(ConfigKey::GAME_HEIGHT);

					//float scaleRatio = 1.0f;
					bool isHorizDirection = (mapWidth > mapHeight) ? true : false;
					if (isHorizDirection)
					{
						m_scaleRatio = (float)screenHeight / (float)mapHeight;
					}
					else
					{
						m_scaleRatio = (float)screenWidth / (float)mapWidth;
					}

					//float scaleRatio = (float)screenHeight / (float)mapHeight;
					D3DXMATRIX transform_scale;
					D3DXMatrixAffineTransformation2D(&transform_scale, m_scaleRatio, NULL, NULL, NULL);

					D3DXVECTOR4 pointOrigin, resultTrans;
					pointOrigin.x = x;
					pointOrigin.y = y;

					D3DXVec4Transform(&resultTrans, &pointOrigin, &transform_scale);

					RECT bound;
					bound.left = resultTrans.x;
					bound.right = resultTrans.x + width * m_scaleRatio;
					bound.top = resultTrans.y;
					bound.bottom = resultTrans.y + height * m_scaleRatio;
					

					Vector3 translation(resultTrans.x, resultTrans.y, 1.0f);
					pStaticComponent->SetTranslation(translation);
					pStaticComponent->SetSize(width * m_scaleRatio, height * m_scaleRatio);
					//pStaticComponent->Initialize();

					pStaticCollisionComponent->AttachRenderable(&pStaticComponent->GetRenderable());
					//pStaticCollisionComponent->Initialize(); Delay initilize 
					
					//CollisionManager::GetSingletonPtr()->AddObjectToBin(0, pStaticCollisionComponent);

				}
				gameObjects->push_back(gameObj);
				m_objectHashTable->insert(make_pair(id, gameObj));
			}
			m_tileMap->SetObjects(m_objectHashTable);

		}
		
		QuadtreeLoader* quadtreeLoader = new QuadtreeLoader(m_file);
		quadtreeLoader->SetScaleRatio(m_scaleRatio);
		bool res = quadtreeLoader->Load();
		if (!res)
		{
			throw new GameError(GameErrorNS::FATAL_ERROR, "Cannot load Quadtree!");
		}
		m_tileMap->SetQuadTree(quadtreeLoader->GetQuadTree());

		return true;
	}
}