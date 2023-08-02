#include "LoadingState.h"

LoadingState::LoadingState()
{
	std::ifstream file(SAVEFILE);

	if (!file.is_open())
		throw std::runtime_error("Failed to open file");

	std::string level;
	file >> level;

	size_t levelNum = std::stoul(level.substr(level.size() - DotTxt));
	if (levelNum == 1)
		m_background.setTexture(TextureManager::instance().getLevel1Bg());
	else if (levelNum == 2)
		m_background.setTexture(TextureManager::instance().getLevel2Bg());
	else if(levelNum == 3)
		m_background.setTexture(TextureManager::instance().getLevel3Bg());
}

void LoadingState::update(float deltaTime)
{
	m_elapsedTime += deltaTime;

	if (m_elapsedTime > 3.f)
		requestStateChange(GameStateID::Exit);
}

void LoadingState::render(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());
	window.draw(m_background);
}