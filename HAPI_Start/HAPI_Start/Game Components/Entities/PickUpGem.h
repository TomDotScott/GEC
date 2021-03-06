#pragma once
#include "Entity.h"

/**
 * \brief Gems have different properties depending on their
 * type
 */
enum class ePowerUpType
{
	e_Grower,
	e_FireThrower
};

/**
 * \brief PickUpGems are generated by the various item boxes
 * around the game world and grant the player a powerup when
 * the player touches it
 */
class PickUpGem final : public Entity
{
public:
	explicit PickUpGem(int entityID, const Vector2& position, ePowerUpType powerUpType, bool visible = false);
	void     Update(float deltaTime) override;
	void     CheckEntityCollisions(Entity& other) override;

	/**
	 * \brief Initialises the gem object within the game world
	 * \param position The initial position of the gem
	 */
	void Initialise(Vector2 position);

	/**
	 * \brief Gets the current type of the gem
	 * \return The current type of the gem
	 */
	ePowerUpType GetType() const;
	
	void         SetPowerUpType(ePowerUpType type);

private:
	ePowerUpType   m_type;
	void           Move(float deltaTime) override;
	CollisionBoxes GenerateCollisionBoxes() override;
};
