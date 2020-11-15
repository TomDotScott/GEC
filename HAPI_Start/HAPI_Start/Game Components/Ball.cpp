﻿#include "Ball.h"
#include <iostream>

#include "../Graphics/Graphics.h"

Ball::Ball(const std::string& textureFilename, const std::string& textureIdentifier, const Vector2 position, const Vector2 velocity) :
	Entity(textureFilename,
		textureIdentifier,
		Vector2(32, 32),
		position,
		velocity,
		{ 0.1f, 0.1f }),
	m_speedMultiplier(20.f),
	m_livesRemaining(5) {
}

Ball::Ball(const std::string& spriteSheetIdentifier, const Vector2 position, const Vector2 velocity) :
	Entity(spriteSheetIdentifier,
		Vector2(constants::k_spriteSheetCellWidth, constants::k_spriteSheetCellWidth),
		position,
		velocity,
		{ 0.1f, 0.1f }),
	m_speedMultiplier(20.f),
	m_livesRemaining(5) {
}

void Ball::Update(const float deltaTime) {
	Move(deltaTime);
}

int Ball::GetLivesRemaining() const {
	return m_livesRemaining;
}

void Ball::Move(const float deltaTime) {

	const BoundsRectangle bounds = GetGlobalBounds();
	if (bounds.TOP_LEFT.x < 1 || bounds.BOTTOM_RIGHT.x > constants::k_screenWidth - 1) {
		m_velocity.x *= -1;
	}
	if (bounds.TOP_LEFT.y < 1) {
		m_velocity.y *= -1;
	}

	if (bounds.BOTTOM_RIGHT.y > constants::k_screenHeight + m_size.y * 2) {
		Reset();
	}

	m_position = m_position + (m_velocity * (deltaTime / 1000.f)) * m_speedMultiplier;
}

void Ball::CheckCollisions(const BoundsRectangle other, const Vector2 otherPosition) {
	if (Entity::CheckCollisions(other)) {
		const float hitFactor = HitFactor(otherPosition);
		Vector2 direction(1, hitFactor);
		direction.Normalised();
		m_velocity = direction * m_speedMultiplier;
	}
}

void Ball::Reset() {
	m_position = { Vector2::CENTRE };
	m_velocity = { 0, m_speedMultiplier };
	m_livesRemaining -= 1;
}

float Ball::HitFactor(const Vector2 hitPosition) const {
	// ||  1 <- at the top of the racket
	// ||
	// ||  0 <- at the middle of the racket
	// ||
	// || -1 <- at the bottom of the racket
	return(m_position.y - hitPosition.y) / m_size.y;
}