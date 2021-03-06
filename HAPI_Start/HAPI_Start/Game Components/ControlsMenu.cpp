#include "ControlsMenu.h"

#include "../Audio/SoundManager.h"
#include "../Graphics/TextureManager.h"
#include "../State System/StateManager.h"

ControlsMenu::ControlsMenu() :
	State(),
	m_backText("MAIN MENU", 
		{
		           Vector2::CENTRE.x - 2 * constants::k_spriteSheetCellSize,
		           constants::k_screenHeight - 2 * constants::k_spriteSheetCellSize
	           }
	) {}

bool ControlsMenu::Initialise(TextureManager& textureManager)
{
	return textureManager.CreateTexture("Res/Graphics/Controls_Background.tga", "Background");
}

bool ControlsMenu::Unload(TextureManager& textureManager)
{
	return textureManager.RemoveTexture("Background");
}

void ControlsMenu::Input()
{
	const HAPISPACE::HAPI_TControllerData& controllerData = HAPI.GetControllerData(0);
	if (GetKey(eKeyCode::SPACE) || GetKey(eKeyCode::ENTER) || controllerData.digitalButtons[HK_DIGITAL_A])
	{
		STATE_MANAGER.ChangeState(eState::e_MainMenu);
	}
}

void ControlsMenu::Update()
{
	SoundManager::GetInstance().UpdateMusicBufferStream();
}

void ControlsMenu::Render(TextureManager& textureManager)
{
	textureManager.DrawTexture("Background", {});
	m_backText.Render(textureManager);
	textureManager.DrawSprite("UI_Pointer", {
		                          m_backText.GetPosition().x + 5 * constants::k_spriteSheetCellSize,
		                          m_backText.GetPosition().y
	                          });
}
