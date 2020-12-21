#pragma once
#include <vector>
#include "../Utilities/Vector.h"
#include "Entities/Enemies/Enemy.h"
#include "Entities/Entity.h"
#include "Entities/Player.h"

class TextureManager;
struct Tile;

struct CollisionData
{
	Tile* m_headCollision;
	Tile* m_leftCollision;
	Tile* m_rightCollision;
	Tile* m_bottomCollision;
};

class TileManager
{
public:
	TileManager();
	bool LoadLevel(const std::string& filename);
	void RenderTiles(TextureManager& textureManager, float playerOffset);
	CollisionData& CheckPlayerLevelCollisions(Player& player);
	bool ShouldLoadNextLevel() const;
	void CheckEnemyLevelCollisions(Enemy& enemy);
	void CheckFireballLevelCollisions(Fireball& fireball);
	std::vector<std::pair<eEntityType, Vector2>>& GetEntityLocations();

private:
	std::vector<std::vector<Tile>> m_levelData;
	std::vector<std::pair<eEntityType, Vector2>> m_entityLocations;
	bool m_shouldLoadNextLevel;
	CollisionData m_playerCollisionData;

	Tile* CheckPlayerHeadCollisions(Player& player, const CollisionBoxes& playerCollisionBoxes);
	Tile* CheckPlayerLeftCollisions(Player& player, const CollisionBoxes& playerCollisionBoxes);
	Tile* CheckPlayerRightCollisions(Player& player, const CollisionBoxes& playerCollisionBoxes);
	Tile* CheckPlayerBottomCollisions(Player& player, const CollisionBoxes& playerCollisionBoxes);
};

enum class eTileType
{
	e_None = -100,
	e_Air = -1,
	e_Dirt = 0,
	e_GrassLeft = 1,
	e_GrassCentre = 2,
	e_GrassRight = 3,
	e_StoneTop = 4,
	e_StoneCentre = 5,
	e_StoneLeft = 6,
	e_StoneRight = 7,
	e_Flag = 38,
	e_CoinBlock = 47,
	e_BoxedCoinBlock = 48,
	e_CrateBlock = 49,
	e_ItemBlock = 50,
	e_BrickBlock = 51,
	e_Bush = 52,
	e_ClosedDoorMid = 53,
	e_ClosedDoorTop = 54,
	e_OpenDoorMid = 55,
	e_OpenDoorTop = 56,
	e_Plant = 57,
	e_Mushroom1 = 60,
	e_Mushroom2 = 61,
	e_Rock = 62,
	e_Spikes = 63,
	e_FlagPole = 64,
	e_Slime = 65,
	e_Coin = 66,
	e_Snail = 68,
	e_RightArrow = 69,
	e_GrassCliffLeft = 70,
	e_GrassCliffRight = 71
};

inline const char* to_string(const eTileType e)
{
	switch (e)
	{
	case eTileType::e_None: return "e_None";
	case eTileType::e_Air: return "e_Air";
	case eTileType::e_Dirt: return "e_Dirt";
	case eTileType::e_GrassLeft: return "e_GrassLeft";
	case eTileType::e_GrassCentre: return "e_GrassCentre";
	case eTileType::e_GrassRight: return "e_GrassRight";
	case eTileType::e_StoneTop: return "e_StoneTop";
	case eTileType::e_StoneCentre: return "e_StoneCentre";
	case eTileType::e_StoneLeft: return "e_StoneLeft";
	case eTileType::e_StoneRight: return "e_StoneRight";
	case eTileType::e_Flag: return "e_Flag";
	case eTileType::e_CoinBlock: return "e_CoinBlock";
	case eTileType::e_BoxedCoinBlock: return "e_BoxedCoinBlock";
	case eTileType::e_CrateBlock: return "e_CrateBlock";
	case eTileType::e_ItemBlock: return "e_ItemBlock";
	case eTileType::e_BrickBlock: return "e_BrickBlock";
	case eTileType::e_Bush: return "e_Bush";
	case eTileType::e_ClosedDoorMid: return "e_ClosedDoorMid";
	case eTileType::e_ClosedDoorTop: return "e_ClosedDoorTop";
	case eTileType::e_OpenDoorMid: return "e_OpenDoorMid";
	case eTileType::e_OpenDoorTop: return "e_OpenDoorTop";
	case eTileType::e_Plant: return "e_Plant";
	case eTileType::e_Mushroom1: return "e_Mushroom1";
	case eTileType::e_Mushroom2: return "e_Mushroom2";
	case eTileType::e_Rock: return "e_Rock";
	case eTileType::e_Spikes: return "e_Spikes";
	case eTileType::e_FlagPole: return "e_FlagPole";
	case eTileType::e_Slime: return "e_Slime";
	case eTileType::e_Coin: return "e_Coin";
	case eTileType::e_Snail: return "e_Snail";
	case eTileType::e_RightArrow: return "e_RightArrow";
	case eTileType::e_GrassCliffLeft: return "e_GrassCliffLeft";
	case eTileType::e_GrassCliffRight: return "e_GrassCliffRight";
	default: return "unknown";
	}
}

struct Tile
{
	Tile(const eTileType type, const Vector2 position, const bool canCollide) :
		m_type(type),
		m_position(position),
		m_canCollide(canCollide),
		m_canBeDestroyed(true)
	{
		m_tileCollisionBox = {
			m_position,
			{m_position.x + constants::k_spriteSheetCellSize, m_position.y + constants::k_spriteSheetCellSize}
		};
	}

	friend bool operator==(Tile& lhs, Tile& rhs)
	{
		return lhs.m_type == rhs.m_type
			&& lhs.m_position == rhs.m_position
			&& lhs.m_canCollide == rhs.m_canCollide
			&& lhs.m_canBeDestroyed == rhs.m_canBeDestroyed;
	}

	friend bool operator!=(Tile& lhs, Tile& rhs)
	{
		return !(lhs == rhs);
	}

	eTileType m_type;
	Vector2 m_position;
	CollisionBox m_tileCollisionBox;
	bool m_canCollide;
	bool m_canBeDestroyed;
};
