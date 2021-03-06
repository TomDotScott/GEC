﻿#include "Enemy.h"
#include "../Graphics/TextureManager.h"

Enemy::Enemy(const eEntityType type,
             const int         entityID,
             const Vector2&    startingPosition,
             const Vector2&    size,
             const eDirection  startDir,
             const bool        canAvoidEdges
) :
	Entity(type,
	       entityID,
	       size,
	       startDir,
	       startingPosition,
	       {-100.f, 0}
	      ),
	m_canAvoidEdges(canAvoidEdges),
	m_isFalling(false) {}

void Enemy::Render(TextureManager& textureManager, const float playerOffset)
{
	if (GetCurrentAnimationState() != eAnimationState::e_Ended)
	{
		textureManager.DrawSprite(GetCurrentAnimationFrameIdentifier(), {
			                          m_position.x + (static_cast<float>(constants::k_screenWidth) / 2.f) -
			                          playerOffset,
			                          m_position.y
		                          }, m_currentDirection == eDirection::e_Right);
	}
}

bool Enemy::CanAvoidEdges() const
{
	return m_canAvoidEdges;
}

void Enemy::SetIsFalling(const bool isFalling)
{
	if (!isFalling)
	{
		m_velocity.y = 0.f;
	}
	m_isFalling = isFalling;
}

void Enemy::CheckSnailShellCollisions(const CollisionBoxes& snailShellCollisionBoxes)
{
	if (m_currentEntityState == eEntityState::e_Alive)
	{
		const auto& currentCollisionBoxes = GenerateCollisionBoxes();
		if (currentCollisionBoxes.m_globalBounds.Overlapping(snailShellCollisionBoxes.m_globalBounds))
		{
			if (currentCollisionBoxes.m_leftCollisionBox.Overlapping(snailShellCollisionBoxes.m_rightCollisionBox) ||
			    currentCollisionBoxes.m_rightCollisionBox.Overlapping(snailShellCollisionBoxes.m_leftCollisionBox))
			{
				m_currentEntityState = eEntityState::e_ProjectileHit;
				SetAnimationIndex(static_cast<int>(m_currentEntityState));
				PlaySFX("Entity_Shell_Hit");
			}
		}
	}
}

void Enemy::Move(const float deltaTime)
{
	m_position = m_position + m_velocity * deltaTime;
}
