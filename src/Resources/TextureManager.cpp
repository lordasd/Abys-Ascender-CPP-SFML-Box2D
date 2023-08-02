#include "TextureManager.h"
#include <iostream>
#include <random>

TextureManager& TextureManager::instance()
{
	static TextureManager textInstance;
	return textInstance;
}

const sf::Sprite& TextureManager::getTile(size_t id) const
{
    // Return specific tile texture
    return m_tilesMap.at(id);
}

const std::vector<sf::Sprite>& TextureManager::getAdventurerAnimation(int id) const
{
    return m_adventurerAnimation.at(id);
}

const std::vector<sf::Sprite>& TextureManager::getSkeletonMeleeAnimation(int id) const
{
    return m_skeletonMeleeAnimation.at(id);
}

const std::vector<sf::Sprite>& TextureManager::getSkeletonRangedAnimation(int id) const
{
    return m_skeletonRangedAnimation.at(id);
}

const sf::Sprite& TextureManager::getWeaponArrow() const
{
    return m_weaponArrowSprite;
}

const sf::Texture& TextureManager::getLevel1Bg() const
{
    return m_level1Bg;
}

const sf::Texture& TextureManager::getLevel2Bg() const
{
    return m_level2Bg;
}

const sf::Texture& TextureManager::getLevel3Bg() const
{
    return m_level3Bg;
}

const sf::Texture& TextureManager::getMainMenu() const
{
    return m_mainMenu;
}

const sf::Texture& TextureManager::getHelpMenu() const
{
    return m_helpMenu;
}

const sf::Texture& TextureManager::getHelpMenu2() const
{
    return m_helpMenu2;
}

const sf::Texture& TextureManager::getPauseMenu() const
{
    return m_pauseMenu;
}

const sf::Texture& TextureManager::getMenuButton(size_t index) const
{
    return m_menuButtons[index];
}

const sf::Texture& TextureManager::getSettingsMenu() const
{
    return m_settingsMenu;
}

const sf::Texture& TextureManager::getRetry() const
{
    return m_retry;
}

const sf::Texture& TextureManager::getSoundFx() const
{
    return m_soundfx;
}

const sf::Texture& TextureManager::getMusic() const
{
    return m_music;
}

const sf::Texture& TextureManager::getArrowLeft() const
{
    return m_leftArrow;
}

const sf::Texture& TextureManager::getArrowRight() const
{
    return m_rightArrow;
}

const sf::Texture& TextureManager::getBack() const
{
    return m_back;
}

const sf::Texture& TextureManager::getResume() const
{
    return m_resume;
}

const sf::Texture& TextureManager::getGameOverBackground() const
{
    return m_gameOverBackground;
}

const sf::Texture& TextureManager::getGameOverWinBackground() const
{
    return m_gameOverWinBackground;
}

const std::vector<sf::Texture>& TextureManager::getBGLayers(size_t level) const
{
    if (level == 1)
        return m_backgroundLayers;
    else if (level == 2)
        return m_backgroundLayersMossy;
    else if (level == 3)
        return m_backgroundLayersCavern;
  
    return m_backgroundLayers;
}

const sf::Font& TextureManager::getPixelFont() const
{
    return m_pixelFont;
}

const sf::Font& TextureManager::getCloisterBlackFont() const
{
    return m_cloisterBlackFont;
}

const sf::Texture& TextureManager::getPlatform() const
{
    return m_platform;
}

const sf::Texture& TextureManager::getMossyPlatform() const
{
    return m_mossyPlatform;
}

const sf::Texture& TextureManager::getCavernPlatform() const
{
    return m_cavernPlatform;
}

const sf::Texture& TextureManager::getHp() const
{
    return m_hp;
}

const sf::Texture& TextureManager::getHpFilledHeart() const
{
    return m_heart;
}

const sf::Texture& TextureManager::getHpEmptyHeart() const
{
    return m_emptyHeart;
}

const sf::Sprite& TextureManager::getRandomDrop() const
{
    // Seed the random number generator with a random device
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range of the random number
    std::uniform_int_distribution<size_t> distribution(0, 63);

    return m_foods.at(distribution(gen));
}

const sf::Texture& TextureManager::getPlus() const
{
    return m_plus;
}

const sf::Texture& TextureManager::getMinus() const
{
    return m_minus;
}

TextureManager::TextureManager()
{
    try {
        if(!m_tileset.loadFromFile("Tileset.png"))
            throw std::runtime_error("Failed to load Tileset.png");
        if (!m_tileset2.loadFromFile("Tileset2.png"))
            throw std::runtime_error("Failed to load Tileset2.png");
        if (!m_tileset3.loadFromFile("Tileset3.png"))
            throw std::runtime_error("Failed to load Tileset3.png");
        if (!m_tileset4.loadFromFile("Tileset4.png"))
            throw std::runtime_error("Failed to load Tileset4.png");
        if (!m_buildings.loadFromFile("Buildings.png"))
            throw std::runtime_error("Failed to load Buildings.png");
        if (!m_tileset4Props1.loadFromFile("Tileset4Props1.png"))
            throw std::runtime_error("Failed to load Tileset4Props1.png");
        if (!m_tileset4Props2.loadFromFile("Tileset4Props2.png"))
            throw std::runtime_error("Failed to load Tileset4Props2.png");
        if (!m_trees.loadFromFile("Trees.png"))
            throw std::runtime_error("Failed to load Trees.png");
        if (!m_adventurer.loadFromFile("adventurer.png"))
            throw std::runtime_error("Failed to load adventurer.png");
        if (!m_adverturer_run.loadFromFile("adventurer_run.png"))
            throw std::runtime_error("Failed to load adventurer_run.png");
        if (!m_level1Bg.loadFromFile("Level1bg.png"))
            throw std::runtime_error("Failed to load Level1bg.png");
        if (!m_level2Bg.loadFromFile("Level2bg.png"))
            throw std::runtime_error("Failed to load Level2bg.png");
        if (!m_level3Bg.loadFromFile("Level3bg.png"))
            throw std::runtime_error("Failed to load Level3bg.png");
        if (!m_mainMenu.loadFromFile("mainmenu.png"))
            throw std::runtime_error("Failed to load mainmenu.png");
        if (!m_helpMenu.loadFromFile("helpmenu.png"))
            throw std::runtime_error("Failed to load helpmenu.png");
        if (!m_helpMenu2.loadFromFile("helpmenu2.png"))
            throw std::runtime_error("Failed to load helpmenu2.png");
        if (!m_pauseMenu.loadFromFile("pausemenu.png"))
            throw std::runtime_error("Failed to load pausemenu.png");
        if (!m_settingsMenu.loadFromFile("settingsmenu.png"))
            throw std::runtime_error("Failed to load settingsmenu.png");
        if (!m_soundfx.loadFromFile("soundfx.png"))
            throw std::runtime_error("Failed to load soundfx.png");
        if (!m_music.loadFromFile("music.png"))
            throw std::runtime_error("Failed to load music.png");
        if (!m_newGame.loadFromFile("newgame.png"))
            throw std::runtime_error("Failed to load newgame.png");
        if (!m_continue.loadFromFile("continue.png"))
            throw std::runtime_error("Failed to load continue.png");
        if (!m_settings.loadFromFile("settings.png"))
            throw std::runtime_error("Failed to load settings.png");
        if (!m_help.loadFromFile("help.png"))
            throw std::runtime_error("Failed to load help.png");
        if (!m_exit.loadFromFile("exit.png"))
            throw std::runtime_error("Failed to load exit.png");
        if (!m_gameOverBackground.loadFromFile("gameover.png"))
            throw std::runtime_error("Failed to load gameover.png");
        if (!m_gameOverWinBackground.loadFromFile("win.png"))
            throw std::runtime_error("Failed to load win.png");
        if (!m_back.loadFromFile("back.png"))
            throw std::runtime_error("Failed to load back.png");
        if (!m_resume.loadFromFile("resume.png"))
            throw std::runtime_error("Failed to load resume.png");
        if (!m_retry.loadFromFile("retry.png"))
            throw std::runtime_error("Failed to load retry.png");
        if (!m_leftArrow.loadFromFile("left_arrow.png"))
            throw std::runtime_error("Failed to load left_arrow.png");
        if (!m_rightArrow.loadFromFile("right_arrow.png"))
            throw std::runtime_error("Failed to load right_arrow.png");
        if (!m_bgBack.loadFromFile("BGBack.png"))
            throw std::runtime_error("Failed to load BGBack.png");
        if (!m_bgFront.loadFromFile("BGFront.png"))
            throw std::runtime_error("Failed to load BGFront.png");
        if (!m_cloudsBack.loadFromFile("CloudsBack.png"))
            throw std::runtime_error("Failed to load CloudsBack.png");
        if (!m_cloudsFront.loadFromFile("CloudsFront.png"))
            throw std::runtime_error("Failed to load CloudsFront.png");
        if (!m_bgMossyBack.loadFromFile("BG_MossyBack.png"))
            throw std::runtime_error("Failed to load BG_MossyBack.png");
        if (!m_bgMossyMiddle.loadFromFile("BG_MossyMiddle.png"))
            throw std::runtime_error("Failed to load BG_MossyMiddle.png");
        if (!m_bgMossyFront.loadFromFile("BG_MossyFront.png"))
            throw std::runtime_error("Failed to load BG_MossyFront.png");
        if (!m_bgCavern1.loadFromFile("BG_Cavern1.png"))
            throw std::runtime_error("Failed to load BG_Cavern1.png");
        if (!m_bgCavern2.loadFromFile("BG_Cavern2.png"))
            throw std::runtime_error("Failed to load BG_Cavern2.png");
        if (!m_bgCavern3.loadFromFile("BG_Cavern3.png"))
            throw std::runtime_error("Failed to load BG_Cavern3.png");
        if (!m_bgCavern4.loadFromFile("BG_Cavern4.png"))
            throw std::runtime_error("Failed to load BG_Cavern4.png");
        if (!m_pixelFont.loadFromFile("pixelfont.ttf"))
            throw std::runtime_error("Failed to load pixelfont.ttf");
        if (!m_cloisterBlackFont.loadFromFile("CloisterBlack.ttf"))
            throw std::runtime_error("Failed to load pixelfont.ttf");
        if(!m_idleSkeletonMelee.loadFromFile("Idle_Skeleton_Melee.png"))
            throw std::runtime_error("Failed to load Idle_Skeleton_Melee.png");
        if (!m_walkSkeletonMelee.loadFromFile("Walk_Skeleton_Melee.png"))
            throw std::runtime_error("Failed to load Walk_Skeleton_Melee.png");
        if (!m_attackSkeletonMelee.loadFromFile("Attack_1_Skeleton_Melee.png"))
            throw std::runtime_error("Failed to load Attack_1_Skeleton_Melee.png");
        if (!m_deadSkeletonMelee.loadFromFile("Dead_Skeleton_Melee.png"))
            throw std::runtime_error("Failed to load Dead_Skeleton_Melee.png");
        if (!m_hurtSkeletonMelee.loadFromFile("Hurt_Skeleton_Melee.png"))
            throw std::runtime_error("Failed to load Hurt_Skeleton_Melee.png");
        if (!m_idleSkeletonRanged.loadFromFile("Idle_Skeleton_Ranged.png"))
            throw std::runtime_error("Failed to load Idle_Skeleton_Ranged.png");
        if (!m_walkSkeletonRanged.loadFromFile("Walk_Skeleton_Ranged.png"))
            throw std::runtime_error("Failed to load Walk_Skeleton_Ranged.png");
        if (!m_attackSkeletonRanged.loadFromFile("Shot_1_Skeleton_Ranged.png"))
            throw std::runtime_error("Failed to load Shot_1_Skeleton_Ranged.png");
        if (!m_deadSkeletonRanged.loadFromFile("Dead_Skeleton_Ranged.png"))
            throw std::runtime_error("Failed to load Dead_Skeleton_Ranged.png");
        if (!m_hurtSkeletonRanged.loadFromFile("Hurt_Skeleton_Ranged.png"))
            throw std::runtime_error("Failed to load Hurt_Skeleton_Ranged.png");
        if (!m_weaponArrow.loadFromFile("Weapon_Arrow.png"))
            throw std::runtime_error("Failed to load Weapon_Arrow.png");
        if (!m_platform.loadFromFile("platform.png"))
            throw std::runtime_error("Failed to load platform.png");
        if (!m_mossyPlatform.loadFromFile("mossyplatform.png"))
            throw std::runtime_error("Failed to load mossyplatform.png");
        if (!m_cavernPlatform.loadFromFile("cavernplatform.png"))
            throw std::runtime_error("Failed to load cavernplatform.png");
        if (!m_hp.loadFromFile("hp.png"))
            throw std::runtime_error("Failed to load hp.png");
        if (!m_heart.loadFromFile("heart.png"))
            throw std::runtime_error("Failed to load heart.png");
        if (!m_emptyHeart.loadFromFile("empty_heart.png"))
            throw std::runtime_error("Failed to load empty_heart.png");
        if (!m_food.loadFromFile("food.png"))
            throw std::runtime_error("Failed to load food.png");
        if (!m_plus.loadFromFile("plus.png"))
            throw std::runtime_error("Failed to load plus.png");
        if (!m_minus.loadFromFile("minus.png"))
            throw std::runtime_error("Failed to load minus.png");
    }
    catch (const std::exception& e) {
        std::cerr << "File loading error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    createTileMap();
    createFoods();
    createButtons();
    createBGLayers();
    createAdventurer();
    createSkeletonMelee();
    createSkeletonRanged();
}

void TextureManager::createTileMap()
{
    size_t id{ 1 };
    
    // Set map of tileset
    for (int row = 0; row < 6; ++row)
        for (int col = 0; col < 10; ++col, ++id)
            m_tilesMap[id] = sf::Sprite(m_tileset, sf::IntRect(col * 16, row * 16, 16, 16));

    // Set map of trees
    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 16; ++col, ++id)
            m_tilesMap[id] = sf::Sprite(m_trees, sf::IntRect(col * 16, row * 16, 16, 16));

    // Set map of tileset2
    for (int row = 0; row < 11; ++row)
        for (int col = 0; col < 18; ++col, ++id)
            m_tilesMap[id] = sf::Sprite(m_tileset2, sf::IntRect(col * 16, row * 16, 16, 16));

    // Set map of tileset3
    for (int row = 0; row < 34; ++row)
        for (int col = 0; col < 20; ++col, ++id)
            m_tilesMap[id] = sf::Sprite(m_tileset3, sf::IntRect(col * 16, row * 16, 16, 16));

    // Set map of tileset4
    for (int row = 0; row < 64; ++row)
        for (int col = 0; col < 64; ++col, ++id)
            m_tilesMap[id] = sf::Sprite(m_tileset4, sf::IntRect(col * 16, row * 16, 16, 16));

    // Set map of tileset4Pros1
    for (int row = 0; row < 80; ++row)
        for (int col = 0; col < 80; ++col, ++id)
            m_tilesMap[id] = sf::Sprite(m_tileset4Props1, sf::IntRect(col * 16, row * 16, 16, 16));

    // Set map of tileset4Pros2
    for (int row = 0; row < 64; ++row)
        for (int col = 0; col < 64; ++col, ++id)
            m_tilesMap[id] = sf::Sprite(m_tileset4Props2, sf::IntRect(col * 16, row * 16, 16, 16));

    // Set map of Buildings
    for (int row = 0; row < 25; ++row)
        for (int col = 0; col < 25; ++col, ++id)
            m_tilesMap[id] = sf::Sprite(m_buildings, sf::IntRect(col * 16, row * 16, 16, 16));
}

void TextureManager::createFoods()
{
    size_t id{ 0 };

    // fill the map with all foods
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j, ++id)
            m_foods[id] = { m_food, sf::IntRect(i * 16, j * 16, 16, 16) };
}

void TextureManager::createButtons()
{
    m_menuButtons.emplace_back(m_newGame);
    m_menuButtons.emplace_back(m_continue);
    m_menuButtons.emplace_back(m_settings);
    m_menuButtons.emplace_back(m_help);
    m_menuButtons.emplace_back(m_exit);
}

void TextureManager::createBGLayers()
{
    // Level 1
    m_backgroundLayers.emplace_back(m_cloudsBack);
    m_backgroundLayers.emplace_back(m_cloudsFront);
    m_backgroundLayers.emplace_back(m_bgBack);
    m_backgroundLayers.emplace_back(m_bgFront);
    // Level 2
    m_backgroundLayersMossy.emplace_back(m_bgMossyBack);
    m_backgroundLayersMossy.emplace_back(m_bgMossyMiddle);
    m_backgroundLayersMossy.emplace_back(m_bgMossyFront);
    // Level 3
    m_backgroundLayersCavern.emplace_back(m_bgCavern1);
    m_backgroundLayersCavern.emplace_back(m_bgCavern2);
    m_backgroundLayersCavern.emplace_back(m_bgCavern3);
    m_backgroundLayersCavern.emplace_back(m_bgCavern4);
}

void TextureManager::createAdventurer()
{
    // IDLE
    for(int i = 3; i < 6; ++i)
        m_adventurerAnimation[0].emplace_back(sf::Sprite(m_adventurer, sf::IntRect(i * 50, 5 * 37, 50, 37)));
    // RUN
    for (int i = 0; i < 6; ++i)
        m_adventurerAnimation[1].emplace_back(sf::Sprite(m_adverturer_run, sf::IntRect(i * 50, 0 * 37, 50, 37)));
    // JUMP
    for (int i = 0; i < 3; ++i)
        m_adventurerAnimation[2].emplace_back(sf::Sprite(m_adventurer, sf::IntRect(i * 50, 2 * 37, 50, 37)));
    // FALL
    for (int i = 1; i < 3; ++i)
        m_adventurerAnimation[3].emplace_back(sf::Sprite(m_adventurer, sf::IntRect(i * 50, 3 * 37, 50, 37)));
    // ATTACK 1
    for (int i = 0; i < 5; ++i)
        m_adventurerAnimation[4].emplace_back(sf::Sprite(m_adventurer, sf::IntRect(i * 50, 6 * 37, 50, 37)));
    // ATTACK 2
    for (int i = 5; i < 7; ++i)
        m_adventurerAnimation[4].emplace_back(sf::Sprite(m_adventurer, sf::IntRect(i * 50, 6 * 37, 50, 37)));
    for (int i = 0; i < 4; ++i)
        m_adventurerAnimation[4].emplace_back(sf::Sprite(m_adventurer, sf::IntRect(i * 50, 7 * 37, 50, 37)));
    // ATTACK 3
    for (int i = 4; i < 7; ++i)
        m_adventurerAnimation[4].emplace_back(sf::Sprite(m_adventurer, sf::IntRect(i * 50, 7 * 37, 50, 37)));
    for (int i = 0; i < 3; ++i)
        m_adventurerAnimation[4].emplace_back(sf::Sprite(m_adventurer, sf::IntRect(i * 50, 8 * 37, 50, 37)));
    // Hurt
    for (int i = 3; i < 6; ++i)
        m_adventurerAnimation[5].emplace_back(sf::Sprite(m_adventurer, sf::IntRect(i * 50, 8 * 37, 50, 37)));
    // Die
    m_adventurerAnimation[6].emplace_back(sf::Sprite(m_adventurer, sf::IntRect(6 * 50, 8 * 37, 50, 37)));
    for (int i = 0; i < 6; ++i)
        m_adventurerAnimation[6].emplace_back(sf::Sprite(m_adventurer, sf::IntRect(i * 50, 9 * 37, 50, 37)));
}

void TextureManager::createSkeletonMelee()
{
    // IDLE
    for (int i = 0; i < 7; ++i)
    {
        m_skeletonMeleeAnimation[0].emplace_back(sf::Sprite(m_idleSkeletonMelee, sf::IntRect(i * 128, 0 * 128, 128, 128)));
        m_skeletonMeleeAnimation[0].back().setScale(0.5f, 0.5f);
    }
    // Walk
    for (int i = 0; i < 7; ++i)
    {
        m_skeletonMeleeAnimation[1].emplace_back(sf::Sprite(m_walkSkeletonMelee, sf::IntRect(i * 128, 0 * 128, 128, 128)));
        m_skeletonMeleeAnimation[1].back().setScale(0.5f, 0.5f);
    }
    // Attack 1
    for (int i = 0; i < 5; ++i)
    {
        m_skeletonMeleeAnimation[4].emplace_back(sf::Sprite(m_attackSkeletonMelee, sf::IntRect(i * 128, 0 * 128, 128, 128)));
        m_skeletonMeleeAnimation[4].back().setScale(0.5f, 0.5f);
    }
    // Hurt
    for (int i = 0; i < 2; ++i)
    {
        m_skeletonMeleeAnimation[5].emplace_back(sf::Sprite(m_hurtSkeletonMelee, sf::IntRect(i * 128, 0 * 128, 128, 128)));
        m_skeletonMeleeAnimation[5].back().setScale(0.5f, 0.5f);
    }
    // Die
    for (int i = 0; i < 4; ++i)
    {
        m_skeletonMeleeAnimation[6].emplace_back(sf::Sprite(m_deadSkeletonMelee, sf::IntRect(i * 128, 0 * 128, 128, 128)));
        m_skeletonMeleeAnimation[6].back().setScale(0.5f, 0.5f);
    }
}

void TextureManager::createSkeletonRanged()
{
    // IDLE
    for (int i = 0; i < 7; ++i)
    {
        m_skeletonRangedAnimation[0].emplace_back(sf::Sprite(m_idleSkeletonRanged, sf::IntRect(i * 128, 0 * 128, 128, 128)));
        m_skeletonRangedAnimation[0].back().setScale(0.5f, 0.5f);
    }
    // Walk
    for (int i = 0; i < 8; ++i)
    {
        m_skeletonRangedAnimation[1].emplace_back(sf::Sprite(m_walkSkeletonRanged, sf::IntRect(i * 128, 0 * 128, 128, 128)));
        m_skeletonRangedAnimation[1].back().setScale(0.5f, 0.5f);
    }
    // Shot 1
    for (int i = 0; i < 15; ++i)
    {
        m_skeletonRangedAnimation[4].emplace_back(sf::Sprite(m_attackSkeletonRanged, sf::IntRect(i * 128, 0 * 128, 128, 128)));
        m_skeletonRangedAnimation[4].back().setScale(0.5f, 0.5f);
    }
    // Hurt
    for (int i = 0; i < 2; ++i)
    {
        m_skeletonRangedAnimation[5].emplace_back(sf::Sprite(m_hurtSkeletonRanged, sf::IntRect(i * 128, 0 * 128, 128, 128)));
        m_skeletonRangedAnimation[5].back().setScale(0.5f, 0.5f);
    }
    // Die
    for (int i = 0; i < 5; ++i)
    {
        m_skeletonRangedAnimation[6].emplace_back(sf::Sprite(m_deadSkeletonRanged, sf::IntRect(i * 128, 0 * 128, 128, 128)));
        m_skeletonRangedAnimation[6].back().setScale(0.5f, 0.5f);
    }

    // Sclae Arrow
    m_weaponArrowSprite.setTexture(m_weaponArrow);
    m_weaponArrowSprite.setScale(0.5f, 0.5f);
}