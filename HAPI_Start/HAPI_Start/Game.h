#pragma once
#include <array>
#include <HAPI_lib.h>
#include "Entity.h"


enum class EKeyCode {
	None = 0, LEFT = 37, UP = 38, RIGHT = 39, DOWN = 40, B = 66, C = 67, G = 71, P = 80, R = 82, S = 83, W = 87, Y = 89
};

class Game {
public:
	explicit Game(HAPISPACE::BYTE* _screen);

	void Update();
	void Render();
	void HandleInput();

	void ClearScreen(HAPISPACE::HAPI_TColour _col) const;
	void ClearScreen() const;

	void SetPixel(int _x, int _y, HAPISPACE::HAPI_TColour _colour) const;
	void SetPixel(int _x, int _y, int _value) const;

private:
	bool GetKey(EKeyCode _keyCode);

	HAPISPACE::BYTE* m_screen;
	
	Entity m_testTexture;
	Entity m_testBackground;
};