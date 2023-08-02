#include "GameWinState.h"

GameWinState::GameWinState()
	:	m_gameWinSound(SoundManager::instance().getGameOverWinMusic()),
		m_backGround(TextureManager::instance().getGameOverWinBackground()),
		m_exit(TextureManager::instance().getMenuButton(4)),
		m_click(SoundManager::instance().getClick())
{
	m_exit.setPosition(WINDOW_WIDTH / 2.f - 175.f, 570.f);

	// Set volume for sounds
	m_click.setVolume(SoundManager::instance().getSoundFxVol());
	m_gameWinSound.setVolume(SoundManager::instance().getSoundFxVol());

	m_gameWinSound.play();
}

void GameWinState::handleInput(const sf::Event& event, const sf::Vector2f& mousePos)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (m_exit.getGlobalBounds().contains(mousePos))
		{
			m_click.play();
			requestStateChange(GameStateID::Back);
		} 
	}
}

void GameWinState::render(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());

	window.draw(m_backGround);
	window.draw(m_exit);
}
