#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::instance()
{
	static SoundManager soundInstance;
	return soundInstance;
}

SoundManager::SoundManager()
{
	try
	{
		if (!m_click.loadFromFile("click.wav"))
			throw std::runtime_error("Can't load click.wav");
		if (!m_mainMenuMusic.openFromFile("menu_music.wav"))
			throw std::runtime_error("Can't load menu_music.wav");
		if (!m_damagePlayer.loadFromFile("damage_player.wav"))
			throw std::runtime_error("Can't load damage_player.wav");
		if (!m_deathPlayer.loadFromFile("death_player.wav"))
			throw std::runtime_error("Can't load death_player.wav");
		if (!m_swordWooshPlayer.loadFromFile("sword_woosh_player.wav"))
			throw std::runtime_error("Can't load sword_woosh_player.wav");
		if (!m_swordHitPlayer.loadFromFile("sword_hit_player.wav"))
			throw std::runtime_error("Can't load sword_hit_player.wav");
		if (!m_jumpPlayer.loadFromFile("jump_player.wav"))
			throw std::runtime_error("Can't load jump_player.wav");
		if (!m_landPlayer.loadFromFile("land_player.wav"))
			throw std::runtime_error("Can't load land_player.wav");
		if (!m_shoutPlayer.loadFromFile("shout_player.wav"))
			throw std::runtime_error("Can't load shout_player.wav");
		if (!m_skeletonHit.loadFromFile("skeleton_hit.wav"))
			throw std::runtime_error("Can't load skeleton_hit.wav");
		if (!m_skeletonDeath.loadFromFile("skeleton_death.wav"))
			throw std::runtime_error("Can't load skeleton_death.wav");
		if (!m_gameOver.loadFromFile("game_over.wav"))
			throw std::runtime_error("Can't load game_over.wav");
		if (!m_gameOverWin.loadFromFile("win.wav"))
			throw std::runtime_error("Can't load win.wav");
		if (!m_jungleBook.openFromFile("jungle_book.wav"))
			throw std::runtime_error("Can't load jungle_book.wav");
		if (!m_whereEverYouAre.openFromFile("wherever_you_are.wav"))
			throw std::runtime_error("Can't load wherever_you_are.wav");
		if (!m_downToTheCave.openFromFile("down_to_the_cave.wav"))
			throw std::runtime_error("Can't load down_to_the_cave.wav");
		if (!m_arrowShot.loadFromFile("arrow_shot.wav"))
			throw std::runtime_error("Can't load arrow_shot.wav");
		if (!m_arrowBreak.loadFromFile("arrow_break.wav"))
			throw std::runtime_error("Can't load arrow_break.wav");
		if (!m_eat.loadFromFile("eat.wav"))
			throw std::runtime_error("Can't load eat.wav");
	}
	catch (const std::exception& e) {
		std::cerr << "File loading error: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

float SoundManager::getSoundFxVol() const
{
	return m_soundFxVol;
}

void SoundManager::muteUnmuteSoundFx()
{
	if (m_soundFxVol == 0.f)
		m_soundFxVol = 100.f;
	else m_soundFxVol = 0.f;
}

void SoundManager::muteUnmuteMusic()
{
	if (m_musicVol == 0.f)
	{
		m_musicVol = 100.f;
		m_mainMenuMusic.setVolume(100.f);
		m_jungleBook.setVolume(100.f);
		m_whereEverYouAre.setVolume(100.f);
		m_downToTheCave.setVolume(100.f);
	}
	else {
		m_musicVol = 0.f;
		m_mainMenuMusic.setVolume(0.f);
		m_jungleBook.setVolume(0.f);
		m_whereEverYouAre.setVolume(0.f);
		m_downToTheCave.setVolume(0.f);
	}
}

void SoundManager::fxVolumeUp()
{
	if (m_soundFxVol < 100.f)
		m_soundFxVol += 10.f;
}

void SoundManager::fxVolumeDown()
{
	if (m_soundFxVol > 0.f)
		m_soundFxVol -= 10.f;
}

void SoundManager::musicVolumeUp()
{
	if (m_musicVol < 100.f)
		m_musicVol += 10.f;
	m_mainMenuMusic.setVolume(m_musicVol);
	m_jungleBook.setVolume(m_musicVol);
	m_whereEverYouAre.setVolume(m_musicVol);
	m_downToTheCave.setVolume(m_musicVol);
}

void SoundManager::musicVolumeDown()
{
	if (m_musicVol > 0.f)
		m_musicVol -= 10.f;
	m_mainMenuMusic.setVolume(m_musicVol);
	m_jungleBook.setVolume(m_musicVol);
	m_whereEverYouAre.setVolume(m_musicVol);
	m_downToTheCave.setVolume(m_musicVol);
}

const sf::SoundBuffer& SoundManager::getClick() const
{
	return m_click;
}

sf::Music* SoundManager::getMainMenuMusic() const
{
	return const_cast<sf::Music*>(&m_mainMenuMusic);
}

sf::Music* SoundManager::getJungleBook() const
{
	return const_cast<sf::Music*>(&m_jungleBook);
}

sf::Music* SoundManager::getWhereEverYouAre() const
{
	return const_cast<sf::Music*>(&m_whereEverYouAre);
}

sf::Music* SoundManager::getDownToTheCave() const
{
	return const_cast<sf::Music*>(&m_downToTheCave);
}

const sf::SoundBuffer& SoundManager::getGameOverMusic() const
{
	return m_gameOver;
}

const sf::SoundBuffer& SoundManager::getGameOverWinMusic() const
{
	return m_gameOverWin;
}

const sf::SoundBuffer& SoundManager::getDamagePlayer() const
{
	return m_damagePlayer;
}

const sf::SoundBuffer& SoundManager::getDeathPlayer() const
{
	return m_deathPlayer;
}

const sf::SoundBuffer& SoundManager::getSwordWooshPlayer() const
{
	return m_swordWooshPlayer;
}

const sf::SoundBuffer& SoundManager::getSwordHitPlayer() const
{
	return m_swordHitPlayer;
}

const sf::SoundBuffer& SoundManager::getArrowShot() const
{
	return m_arrowShot;
}

const sf::SoundBuffer& SoundManager::getArrowBreak() const
{
	return m_arrowBreak;
}

const sf::SoundBuffer& SoundManager::getJumpPlayer() const
{
	return m_jumpPlayer;
}

const sf::SoundBuffer& SoundManager::getLandPlayer() const
{
	return m_landPlayer;
}

const sf::SoundBuffer& SoundManager::getShoutPlayer() const
{
	return m_shoutPlayer;
}

const sf::SoundBuffer& SoundManager::getEatPlayer() const
{
	return m_eat;
}

const sf::SoundBuffer& SoundManager::getSkeletonHit() const
{
	return m_skeletonHit;
}

const sf::SoundBuffer& SoundManager::getSkeletonDeath() const
{
	return m_skeletonDeath;
}
