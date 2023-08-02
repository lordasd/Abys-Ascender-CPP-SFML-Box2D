#include "SettingsState.h"

SettingsState::SettingsState()
	:	m_background(TextureManager::instance().getSettingsMenu()),
		m_soundfx(TextureManager::instance().getSoundFx()),
		m_music(TextureManager::instance().getMusic()),
		m_back(TextureManager::instance().getBack()),
		m_click(SoundManager::instance().getClick()),
		m_upSoundFx(TextureManager::instance().getPlus()),
		m_downSoundFx(TextureManager::instance().getMinus()),
		m_upMusic(TextureManager::instance().getPlus()),
		m_downMusic(TextureManager::instance().getMinus())
{
	// Set button positions
	m_soundfx.setPosition(665, 270.f);
	m_music.setPosition(665.f, 390.f);
	m_back.setPosition(WINDOW_WIDTH/2.f - 175.f, 600.f);
	m_upSoundFx.setPosition(725.f, 270.f);
	m_downSoundFx.setPosition(600.f, 270.f);
	m_upMusic.setPosition(725.f, 390.f);
	m_downMusic.setPosition(600.f, 390.f);
}

void SettingsState::handleInput(const sf::Event& event, const sf::Vector2f& mousePos)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{	// Handle button click
		if (m_soundfx.getGlobalBounds().contains(mousePos))
		{
			m_click.play();
			SoundManager::instance().muteUnmuteSoundFx();
			setVolume();
		}
		else if (m_music.getGlobalBounds().contains(mousePos))
		{
			m_click.play();
			SoundManager::instance().muteUnmuteMusic();
			setVolume();
		}
		else if (m_back.getGlobalBounds().contains(mousePos))
		{
			m_click.play();
			requestStateChange(GameStateID::Exit);
		}
		else if (m_upSoundFx.getGlobalBounds().contains(mousePos))
		{
			m_click.play();
			SoundManager::instance().fxVolumeUp();
		}
		else if (m_downSoundFx.getGlobalBounds().contains(mousePos))
		{
			m_click.play();
			SoundManager::instance().fxVolumeDown();
		}
		else if (m_upMusic.getGlobalBounds().contains(mousePos))
		{
			m_click.play();
			SoundManager::instance().musicVolumeUp();
		}
		else if (m_downMusic.getGlobalBounds().contains(mousePos))
		{
			m_click.play();
			SoundManager::instance().musicVolumeDown();
		}
	}
}

void SettingsState::update(float)
{
	m_click.setVolume(SoundManager::instance().getSoundFxVol());
}

void SettingsState::render(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_soundfx);
	window.draw(m_music);
	window.draw(m_back);
	window.draw(m_upSoundFx);
	window.draw(m_downSoundFx);
	window.draw(m_upMusic);
	window.draw(m_downMusic);
}

void SettingsState::setVolume()
{
	m_click.setVolume(SoundManager::instance().getSoundFxVol());
}
