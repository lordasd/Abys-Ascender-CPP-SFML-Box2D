#include "GameController.h"

GameController::GameController()
	:	m_window(Window()),
        m_renderWindow(m_window.getRenderedWindow()),
        m_currStateID(GameStateID::MainMenu)
{
    m_stateStack.push(std::make_unique<MainMenuState>());
}

void GameController::run()
{
    while (m_renderWindow.isOpen()) {
        float deltaTime = m_clock.getElapsedTime().asSeconds();
        m_clock.restart();

        handleInput();
        update(deltaTime);

        // Check if the state has changed
        if (m_stateChanged)
        {
            clearStateChangeRequest();
            continue; // Skip rendering for this iteration
        }

        render(m_renderWindow);
    }
}

void GameController::handleInput()
{
    for (auto event = sf::Event{}; m_renderWindow.pollEvent(event); )
    {
        auto mousePos = m_renderWindow.mapPixelToCoords
        ({ event.mouseButton.x, event.mouseButton.y });

        switch (event.type)
        {
        case sf::Event::Closed:
            m_stateStack.top()->requestStateChange(GameStateID::Exit);
            m_renderWindow.close();
            break;
        case sf::Event::MouseButtonReleased:
            // Pass the mouse button released event to the state
            m_stateStack.top()->handleInput(event, mousePos);
            break;
        case sf::Event::MouseButtonPressed:
            // Pass the mouse button pressed event to the state
            m_stateStack.top()->handleInput(event, mousePos);
            break;
        case sf::Event::KeyPressed:
            // Pass the key pressed event to the state
            m_stateStack.top()->handleInput(event, mousePos);
            break;
        case sf::Event::KeyReleased:
            // Pass the key released event to the state
            m_stateStack.top()->handleInput(event, mousePos);
            break;
        case sf::Event::MouseMoved:
            // Pass the mouse moved event to the state
            m_stateStack.top()->handleInput(event, mousePos);
            break;
        default:
            break;
        }
    }
}

void GameController::update(float deltaTime)
{
    // Update game logic
    m_stateStack.top()->update(deltaTime);

    // Check if state transition is needed
    if (m_stateStack.top()->isStateChangeRequested())
    {
        checkForLoadLevel(); // Check if needed to load level from file
        GameStateID nextStateID = m_stateStack.top()->getNextStateID();

        // Perform state transition based on the next state ID
        switch (nextStateID)
        {
        case GameStateID::Gameplay:
            pushState(std::make_unique<GameplayState>(m_levelLoadRequest, m_cameraView));
            m_levelLoadRequest = false;
            break;
        case GameStateID::MainMenu:
            pushState(std::make_unique<MainMenuState>());
            break;
        case GameStateID::PauseMenu:
            pushState(std::make_unique<PauseMenuState>());
            break;
        case GameStateID::Settings:
            pushState(std::make_unique<SettingsState>());
            break;
        case GameStateID::Loading:
            pushState(std::make_unique<LoadingState>());
            break;
        case GameStateID::GameOver:
            pushState(std::make_unique<GameOverState>());
            break;
        case GameStateID::GameWin:
            pushState(std::make_unique<GameWinState>());
            break;
        case GameStateID::Retry:
            popState(); // Exit GameOver State
            popState(); // Exit Gameplay state
            pushState(std::make_unique<GameplayState>(true, m_cameraView));
            break;
        case GameStateID::Back:
            popState(); // Exit GameOver State
            popState(); // Exit Gameplay state
            break;
        case GameStateID::Exit:
            popState();
        }

        m_stateChanged = true; // Set the state changed flag
    }
    else
        m_stateChanged = false; // Clear the state changed flag
}

void GameController::render(sf::RenderWindow& window)
{
    // Clear the window
    window.clear();

    // Render game content
    m_stateStack.top()->render(window);

    // Display the rendered frame
    window.display();
}

void GameController::pushState(std::unique_ptr<GameState> state)
{
    // Pause the current state (if any)
    if (!m_stateStack.empty())
        m_stateStack.top()->pause();

    // Set the new state as active and resume it
    m_prevStateID.push(m_currStateID); // Save current state
    m_currStateID = m_stateStack.top()->getNextStateID();
    m_stateStack.push(std::move(state));
    m_stateStack.top()->resume();
}

void GameController::popState()
{
    // Pop the current state from the stack
    if (!m_stateStack.empty()) {
        m_stateStack.top()->exit();   
        m_stateStack.pop();

        // Set the current state ID to the ID of the new top state
        if (!m_stateStack.empty())
        {
            // Get current state from prev saved
            m_currStateID = m_prevStateID.top();
            m_prevStateID.pop();
        }
        else // No more states in the stack, set the current state ID to Exit
            m_currStateID = GameStateID::Exit;
    }

    // Resume the previous state (if any)
    if (!m_stateStack.empty())
        m_stateStack.top()->resume();
}

void GameController::clearStateChangeRequest()
{
    if (!m_stateStack.empty())
        m_stateStack.top()->clearStateChangeRequest();
    else
        m_renderWindow.close(); // Close window to quit the game
}

void GameController::checkForLoadLevel()
{
    if (m_currStateID == GameStateID::MainMenu)
    {
        if (m_stateStack.top()->isLoadLevel())
        {
            m_levelLoadRequest = true;
            m_stateStack.top()->setLoadLevel(); // Turn off
        }
    }
}
