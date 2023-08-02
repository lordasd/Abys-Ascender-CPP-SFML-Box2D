#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Config.h"

class TextureManager{
public:
	static TextureManager& instance();
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	void operator=(const TextureManager&) = delete;

	const sf::Sprite& getTile(size_t id) const;
	const std::vector<sf::Sprite>& getAdventurerAnimation(int id) const;
	const std::vector<sf::Sprite>& getSkeletonMeleeAnimation(int id) const;
	const std::vector<sf::Sprite>& getSkeletonRangedAnimation(int id) const;
	const sf::Sprite& getWeaponArrow() const;
	const sf::Texture& getLevel1Bg() const;
	const sf::Texture& getLevel2Bg() const;
	const sf::Texture& getLevel3Bg() const;
	const sf::Texture& getMainMenu() const;
	const sf::Texture& getHelpMenu() const;
	const sf::Texture& getHelpMenu2() const;
	const sf::Texture& getPauseMenu() const;
	const sf::Texture& getMenuButton(size_t index) const;
	const sf::Texture& getSettingsMenu() const;
	const sf::Texture& getRetry() const;
	const sf::Texture& getSoundFx() const;
	const sf::Texture& getMusic() const;
	const sf::Texture& getArrowLeft() const;
	const sf::Texture& getArrowRight() const;
	const sf::Texture& getBack() const;
	const sf::Texture& getResume() const;
	const sf::Texture& getGameOverBackground() const;
	const sf::Texture& getGameOverWinBackground() const;
	const std::vector<sf::Texture>& getBGLayers(size_t level) const;
	const sf::Font& getPixelFont() const;
	const sf::Font& getCloisterBlackFont() const;
	const sf::Texture& getPlatform() const;
	const sf::Texture& getMossyPlatform() const;
	const sf::Texture& getCavernPlatform() const;
	const sf::Texture& getHp() const;
	const sf::Texture& getHpFilledHeart() const;
	const sf::Texture& getHpEmptyHeart() const;
	const sf::Sprite& getRandomDrop() const;
	const sf::Texture& getPlus() const;
	const sf::Texture& getMinus() const;

private:
	TextureManager();
	void createTileMap();
	void createFoods();
	void createButtons();
	void createBGLayers();
	void createAdventurer();
	void createSkeletonMelee();
	void createSkeletonRanged();

	// Foreground
	sf::Texture m_tileset;
	sf::Texture m_tileset2;
	sf::Texture m_tileset3;
	sf::Texture m_tileset4;
	sf::Texture m_buildings;
	sf::Texture m_tileset4Props1;
	sf::Texture m_tileset4Props2;
	sf::Texture m_trees;
	std::unordered_map<size_t, sf::Sprite> m_tilesMap;
	sf::Texture m_platform;
	sf::Texture m_mossyPlatform;
	sf::Texture m_cavernPlatform;
	// ---------------------------------------------

	// Background
	sf::Texture m_bgBack;
	sf::Texture m_bgFront;
	sf::Texture m_cloudsBack;
	sf::Texture m_cloudsFront;
	std::vector<sf::Texture> m_backgroundLayers;
	sf::Texture m_bgMossyBack;
	sf::Texture m_bgMossyMiddle;
	sf::Texture m_bgMossyFront;
	std::vector<sf::Texture> m_backgroundLayersMossy;
	sf::Texture m_level1Bg;
	sf::Texture m_level2Bg;
	sf::Texture m_level3Bg;
	sf::Texture m_bgCavern1;
	sf::Texture m_bgCavern2;
	sf::Texture m_bgCavern3;
	sf::Texture m_bgCavern4;
	std::vector<sf::Texture> m_backgroundLayersCavern;

	// ---------------------------------------------

	// Character
	sf::Texture m_adventurer;
	sf::Texture m_adverturer_run;
	std::unordered_map<int, std::vector<sf::Sprite>> m_adventurerAnimation;
	// ---------------------------------------------

	// Skeleton Melee
	sf::Texture m_idleSkeletonMelee;
	sf::Texture m_walkSkeletonMelee;
	sf::Texture m_attackSkeletonMelee;
	sf::Texture m_deadSkeletonMelee;
	sf::Texture m_hurtSkeletonMelee;
	std::unordered_map<int, std::vector<sf::Sprite>> m_skeletonMeleeAnimation;
	// ---------------------------------------------
	
	// Skeleton Ranged
	sf::Texture m_idleSkeletonRanged;
	sf::Texture m_walkSkeletonRanged;
	sf::Texture m_attackSkeletonRanged;
	sf::Texture m_deadSkeletonRanged;
	sf::Texture m_hurtSkeletonRanged;
	sf::Texture m_weaponArrow;
	sf::Sprite m_weaponArrowSprite;
	std::unordered_map<int, std::vector<sf::Sprite>> m_skeletonRangedAnimation;
	// ---------------------------------------------

	// Menu
	sf::Texture m_mainMenu;
	sf::Texture m_helpMenu;
	sf::Texture m_helpMenu2;
	sf::Texture m_pauseMenu;
	sf::Texture m_settingsMenu;
	sf::Texture m_soundfx;
	sf::Texture m_music;
	sf::Texture m_newGame;
	sf::Texture m_continue;
	sf::Texture m_settings;
	sf::Texture m_help;
	sf::Texture m_exit;
	sf::Texture m_resume;
	sf::Texture m_retry;
	sf::Texture m_gameOverBackground;
	sf::Texture m_gameOverWinBackground;
	std::vector<sf::Texture> m_menuButtons;
	sf::Texture m_back;
	sf::Texture m_leftArrow;
	sf::Texture m_rightArrow;
	sf::Texture m_plus;
	sf::Texture m_minus;
	// ---------------------------------------------

	// Gui
	sf::Texture m_hp;
	sf::Texture m_heart;
	sf::Texture m_emptyHeart;
	//----------------------------------------------

	// Fonts
	sf::Font m_pixelFont;
	sf::Font m_cloisterBlackFont;
	//----------------------------------------------

	// Drops
	sf::Texture m_food;
	std::unordered_map<size_t, sf::Sprite> m_foods;
	//----------------------------------------------
};