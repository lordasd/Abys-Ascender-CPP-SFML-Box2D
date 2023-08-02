#pragma once

#include <memory>
#include <stack>
#include "Window.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "PauseMenuState.h"
#include "SettingsState.h"
#include "GameOverState.h"
#include "GameWinState.h"
#include "LoadingState.h"
#include "GameObject.h"

class GameController {
public:
	GameController();
	void run();

private:
	Window m_window;
	sf::RenderWindow& m_renderWindow;
	sf::View m_cameraView;
	std::stack<std::unique_ptr<GameState>> m_stateStack;
	std::stack<GameStateID> m_prevStateID;
	GameStateID m_currStateID;
	bool m_stateChanged = false;
	bool m_levelLoadRequest = false;
	sf::Clock m_clock;

	void handleInput();
	void update(float deltaTime);
	void render(sf::RenderWindow& window);
	void pushState(std::unique_ptr<GameState> state);
	void popState();
	void clearStateChangeRequest();
	void checkForLoadLevel();
};