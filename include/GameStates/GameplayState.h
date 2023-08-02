#pragma once

#include "GameState.h"
#include "GameObject.h"
#include "fstream"
#include "Config.h"
#include <sstream>
#include <box2d/box2d.h>
#include "ContactListener.h"
#include "ChainedObject.h"
#include "Ui.h"

using Objects = std::vector<std::unique_ptr<GameObject>>;

class GameplayState : public GameState {
public:
    GameplayState(bool loadLevel, const sf::View& view);

    virtual void handleInput(const sf::Event& event, const sf::Vector2f& mousePos) override;
    virtual void update(float deltaTime) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual void pause() override;
    virtual void resume() override;
    virtual void exit() override;

private:
    // Box2D variables
    std::unique_ptr<b2World> m_world;
    ContactListener m_contactListener;
    Ui m_ui;

    // Objects
    Objects m_objects;
    Objects m_chainedObjects;
    Objects m_movingPlatforms;
    Objects m_mobs;
    Objects m_drops;
    std::unique_ptr<GameObject> m_player;

    // Background textures
    std::vector<sf::RectangleShape> m_backgroundLayers;
    std::pair<sf::RectangleShape, sf::RectangleShape> m_frontClouds;
    std::pair<sf::RectangleShape, sf::RectangleShape> m_backClouds;

    size_t m_currLevel = 0;
    sf::View m_cameraView;
    sf::View m_backGroundView;
    float m_zoomLevel = 4.f;
    float m_deathElapsed{};
    bool m_showLoadingScreen = true;

    sf::Music* m_gamePlayMusic;

    void createMap(bool loadLevel);
    void readLine(const std::string& line, size_t row, bool readingFloor);
    std::unique_ptr<GameObject> gameObjectCreator(size_t id, const sf::Vector2f& position) const;
    void resetChainedObjects(std::vector<ChainedObject*>& currentChainedObjects);
    bool chainObjects(size_t id, std::vector<ChainedObject*>& currentChainedObjects, const sf::Vector2f& startPosition, const sf::Vector2f& endPosition);
    void centerCameraOnPlayer();
    void checkIfAlive(float deltaTime);
    void createBackground();
    void moveClouds(float deltaTime);
    void setNextLevel();
    void deleteAllObjects();
    void saveLevel() const;
    void setMusic();
    void drawBackground(sf::RenderWindow& window) const;
};