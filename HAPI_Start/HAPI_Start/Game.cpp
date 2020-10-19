#include "Game.h"
#include "Constants.h"
Game::Game(HAPISPACE::BYTE* _screen) :
	m_screen(_screen),
	m_player1(nullptr),
	m_player2(nullptr) {
	m_player1 = new Player("Data/playerSprite.tga", {
		100,
		constants::k_screenHeight / 2},
		ePlayerNumber::ePlayerOne);
	m_player2 = new Player("Data/alphaThing.tga", {
		constants::k_screenWidth - 100,
		constants::k_screenHeight / 2 },
		ePlayerNumber::ePlayerTwo);

}

void Game::Update() {
	HandleInput();
	m_player1->Update();
	m_player2->Update();
}

void Game::Render() const {
	ClearScreen();
	m_player1->Render(m_screen);
	m_player2->Render(m_screen);
}

void Game::HandleInput() {
	// Player One Controls
	if (GetKey(EKeyCode::W)) {
		m_player1->SetDirection(eDirection::eUp);
	} else if (GetKey(EKeyCode::S)) {
		m_player1->SetDirection(eDirection::eDown);
	} else {
		m_player1->SetDirection(eDirection::eNone);
	}
	// Player Two Controls
	if (GetKey(EKeyCode::UP)) {
		m_player2->SetDirection(eDirection::eUp);
	} else if (GetKey(EKeyCode::DOWN)) {
		m_player2->SetDirection(eDirection::eDown);
	} else {
		m_player2->SetDirection(eDirection::eNone);
	}
}

void Game::ClearScreen(HAPISPACE::HAPI_TColour _col) const {
	for (int i = 0; i < constants::k_screenWidth * constants::k_screenHeight; i++) {
		memcpy(m_screen + 4 * i, &_col, 4);
	}
}

void Game::ClearScreen() const {
	memset(m_screen, 0, static_cast<size_t>(constants::k_screenWidth * constants::k_screenHeight * 4));
}

void Game::SetPixel(const int _x, const int _y, const HAPISPACE::HAPI_TColour _colour) const {
	m_screen[constants::k_screenWidth * _x + _y] = _colour.red;
	m_screen[constants::k_screenWidth * _x + _y + 1] = _colour.green;
	m_screen[constants::k_screenWidth * _x + _y + 2] = _colour.blue;
	m_screen[constants::k_screenWidth * _x + _y + 3] = _colour.alpha;
}

void Game::SetPixel(const int _x, const int _y, const int _value) const {
	m_screen[constants::k_screenWidth * _x + _y] = _value;
}

bool Game::GetKey(const EKeyCode _keyCode) {
	return HAPI.GetKeyboardData().scanCode[static_cast<int>(_keyCode)] ? true : false;
}
