#include "GameOverState.h"

GameOverState::GameOverState()
	: m_gameOverSound(SoundManager::instance().getGameOverMusic()),
	m_backGround(TextureManager::instance().getGameOverBackground()),
	m_retry(TextureManager::instance().getRetry()),
	m_exit(TextureManager::instance().getMenuButton(4)),
	m_click(SoundManager::instance().getClick())
{
	m_retry.setPosition(WINDOW_HEIGHT / 2.f - 41.f, 370.f);
	m_exit.setPosition(WINDOW_WIDTH / 2.f - 175.f, 570.f);

	// Set volume for sounds
	m_click.setVolume(SoundManager::instance().getSoundFxVol());
	m_gameOverSound.setVolume(SoundManager::instance().getSoundFxVol());

	m_gameOverSound.play();
}

void GameOverState::handleInput(const sf::Event& event, const sf::Vector2f& mousePos)
{
	if (event.type == sf::Event::MouseButtonReleased)

	{
		if (m_retry.getGlobalBounds().contains(mousePos))
		{
			m_click.play();
			requestStateChange(GameStateID::Retry);
		}
		else if (m_exit.getGlobalBounds().contains(mousePos))
		{
			m_click.play();
			requestStateChange(GameStateID::Back);
		}
	}
}

void GameOverState::render(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());

	window.draw(m_backGround);
	window.draw(m_retry);
	window.draw(m_exit);
}
