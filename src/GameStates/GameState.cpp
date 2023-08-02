#include "GameState.h"

bool GameState::isStateChangeRequested() const
{
    return m_stateChangeRequested;
}

GameStateID GameState::getNextStateID() const
{
    return m_nextStateID;
}

void GameState::requestStateChange(GameStateID nextStateID)
{
    m_stateChangeRequested = true;
    m_nextStateID = nextStateID;
}

void GameState::clearStateChangeRequest()
{
    m_stateChangeRequested = false;
}

void GameState::setLoadLevel()
{   // Set boolian if needed to load level
    m_loadLevel = m_loadLevel ? false : true;
}

bool GameState::isLoadLevel() const
{
    return m_loadLevel;
}
