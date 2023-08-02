#include "Ui.h"

Ui::Ui(const sf::View& view)
	:	m_hp(TextureManager::instance().getHp()),
		m_heart(TextureManager::instance().getHpFilledHeart()),
		m_emptyHeart(TextureManager::instance().getHpEmptyHeart()),
		m_font(TextureManager::instance().getPixelFont()), m_view(view)
{
	m_level.setFont(m_font);
	m_level.setString("Level 1");
	m_level.setPosition(WINDOW_WIDTH - 90.f, 5.f);
	m_level.setCharacterSize(30U);
	m_level.setScale(0.3f, 0.3f);
	m_hp.setPosition(5.f, 5.f);
	m_health.reserve(6);

	// Initialize with full hearts
	// Adjust heartPosition to position the hearts relative to the HP logo
	float startX = 25.f;
	float startY = 5.f;
	float xPos = startX; // Starting X position of the hearts
	float yPos = startY; // Starting Y position of the hearts
	float heartSpacingX = 11.f;

	for (size_t i = 0; i < 6; ++i)
	{
		m_health.emplace_back(m_heart);
		m_health.back().setPosition(xPos, yPos);

		xPos += heartSpacingX; // Move to the next column
	}
}

void Ui::update(float, size_t healthAmount)
{
	m_hpAmount = healthAmount;

	size_t index{};
	for (; index < m_hpAmount; ++index) // Set full hearts
		m_health[index].setTexture(*m_heart.getTexture());
	for (; index < 6; ++index) // Set empty heart
		m_health[index].setTexture(*m_emptyHeart.getTexture());
}

void Ui::render(sf::RenderWindow& window)
{
	setSpritePositions(window);

	// Draw HP logo
	window.draw(m_hp);

	// Draw all hearts
	for (const auto& heart : m_health)
		window.draw(heart);

	// Draw level text
	window.draw(m_level);
}

void Ui::setLevel(size_t level)
{
	m_level.setString("Level " + std::to_string(level));
}

void Ui::setSpritePositions(sf::RenderWindow& window)
{
	sf::Vector2f viewCenter = window.getView().getCenter();
	sf::Vector2f viewSize = window.getView().getSize();

	// Update the positions of UI elements based on view movement
	sf::Vector2f offset(viewCenter.x - (viewSize.x / 2.f), viewCenter.y - (viewSize.y / 2.f));

	sf::Vector2f hpPosition = sf::Vector2f(5.f, 5.f) + offset;
	m_hp.setPosition(hpPosition);

	sf::Vector2f levelPosition = sf::Vector2f(205.f, 5.f) + offset;
	m_level.setPosition(levelPosition);

	// Update the positions of hearts in m_health
	float startX = 25.f + offset.x;
	float startY = 5.f + offset.y;
	float xPos = startX;
	float yPos = startY;
	float heartSpacingX = 11.f;

	for (size_t i = 0; i < m_health.size(); ++i)
	{
		m_health[i].setPosition(xPos, yPos);
		xPos += heartSpacingX;
	}
}
