#include "MainMenuButton.h"

MainMenuButton::MainMenuButton(size_t buttonNum, const sf::Vector2f& buttonPos)
	:	m_sprite(TextureManager::instance().getMenuButton(buttonNum))
{
	// Assign the correct button type and position
	switch (buttonNum)
	{
	case static_cast<size_t>(ButtonType::NewGame):
		m_sprite.setPosition(buttonPos);
		m_type = ButtonType::NewGame;
		break;
	case static_cast<size_t>(ButtonType::Continue):
		m_sprite.setPosition(buttonPos);
		m_type = ButtonType::Continue;
		break;
	case static_cast<size_t>(ButtonType::Settings):
		m_sprite.setPosition(buttonPos);
		m_type = ButtonType::Settings;
		break;
	case static_cast<size_t>(ButtonType::Help):
		m_sprite.setPosition(buttonPos);
		m_type = ButtonType::Help;
		break;
	case static_cast<size_t>(ButtonType::Exit):
		m_sprite.setPosition(buttonPos);
		m_type = ButtonType::Exit;
		break;
	default:
		break;
	}
}

void MainMenuButton::handleInput(const sf::Vector2f& mousePos)
{
	// Set clicked, if clicked
	if (m_sprite.getGlobalBounds().contains(mousePos))
		m_clicked = true;
}

void MainMenuButton::update(float)
{
	// Reset clicked for next state
	if (m_clicked)
		m_clicked = false;
}

void MainMenuButton::render(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

ButtonType MainMenuButton::getType() const
{
	return m_type;
}

bool MainMenuButton::isClicked() const
{
	return m_clicked;
}
