#pragma once

#include <SFML/Audio.hpp>

class SoundManager {
public:
	static SoundManager& instance();
	~SoundManager() = default;
	SoundManager(const SoundManager&) = delete;
	void operator=(const SoundManager&) = delete;

	float getSoundFxVol() const;
	void muteUnmuteSoundFx();
	void muteUnmuteMusic();
	void fxVolumeUp();
	void fxVolumeDown();
	void musicVolumeUp();
	void musicVolumeDown();

	const sf::SoundBuffer& getClick() const;

	// Music
	sf::Music* getMainMenuMusic() const;
	sf::Music* getJungleBook() const;
	sf::Music* getWhereEverYouAre() const;
	sf::Music* getDownToTheCave() const;
	const sf::SoundBuffer& getGameOverMusic() const;
	const sf::SoundBuffer& getGameOverWinMusic() const;
	//---------------------

	// Player sounds
	const sf::SoundBuffer& getDamagePlayer() const;
	const sf::SoundBuffer& getDeathPlayer() const;
	const sf::SoundBuffer& getJumpPlayer() const;
	const sf::SoundBuffer& getLandPlayer() const;
	const sf::SoundBuffer& getShoutPlayer() const;
	const sf::SoundBuffer& getEatPlayer() const;
	//----------------------

	// Skeleton sounds
	const sf::SoundBuffer& getSkeletonHit() const;
	const sf::SoundBuffer& getSkeletonDeath() const;
	//----------------------

	// Weapon sounds
	const sf::SoundBuffer& getSwordWooshPlayer() const;
	const sf::SoundBuffer& getSwordHitPlayer() const;
	const sf::SoundBuffer& getArrowShot() const;
	const sf::SoundBuffer& getArrowBreak() const;
	//----------------------

private:
	SoundManager();

	float m_soundFxVol = 100.f;
	float m_musicVol = 100.f;

	sf::SoundBuffer m_click;

	// MainMenu Music
	sf::Music m_mainMenuMusic;
	//----------------------

	// Gameplay Music
	sf::SoundBuffer m_gameOver;
	sf::SoundBuffer m_gameOverWin;
	sf::Music m_jungleBook;
	sf::Music m_whereEverYouAre;
	sf::Music m_downToTheCave;
	//----------------------

	// Player sounds
	sf::SoundBuffer m_damagePlayer;
	sf::SoundBuffer m_deathPlayer;
	sf::SoundBuffer m_jumpPlayer;
	sf::SoundBuffer m_landPlayer;
	sf::SoundBuffer m_shoutPlayer;
	sf::SoundBuffer m_eat;
	//----------------------

	// Skeleton sounds
	sf::SoundBuffer m_skeletonHit;
	sf::SoundBuffer m_skeletonDeath;
	//----------------------

	// Weapon sounds
	sf::SoundBuffer m_swordWooshPlayer;
	sf::SoundBuffer m_swordHitPlayer;
	sf::SoundBuffer m_arrowShot;
	sf::SoundBuffer m_arrowBreak;
	//----------------------
};