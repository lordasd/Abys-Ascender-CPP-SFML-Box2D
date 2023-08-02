#include "Animation.h"

Animation::Animation(const std::vector<sf::Sprite>& animation, float frameDuration, float yOffset)
	:	m_frames(animation), m_frameDuration(frameDuration), m_yOffest(yOffset) {}

void Animation::setAnimationBody(const b2Body* body)
{
    m_body = body;
}

void Animation::setAnimation(const std::vector<sf::Sprite>& animation, float interval, const Operation& operation, const Direction& direction)
{
    if (direction == Direction::Right)
        m_lookingRight = true;
    else if (direction == Direction::Left)
        m_lookingRight = false;

    if (operation != m_currOperation || direction != m_currDirection)
    {
        // Set animations
        m_frames = animation;
        // Set interval between each frame
        m_frameDuration = interval;
        // Set starting index from 0
        m_currentFrameIndex = 0;
        // Set new direction
        m_currOperation = operation;
        m_currDirection = direction;
    }

    if (!m_lookingRight)
    {
        const sf::Vector2f scale{ m_frames.back().getScale() };
        for (auto& frame : m_frames)
            frame.setScale({ scale.x < 0 ? scale.x : -scale.x, scale.y });
    }
}

int Animation::animationID(const AnimationType& type) const
{
    return static_cast<size_t>(type);
}

bool Animation::isLookingRight() const
{
    return m_lookingRight;
}

void Animation::update(float deltaTime)
{
    // Update frames - Meters -> Pixels
    for (auto& frame : m_frames)
    {
        frame.setPosition(m_body->GetPosition().x * PPM, WINDOW_HEIGHT - (m_body->GetPosition().y * PPM) - m_yOffest);
        frame.setOrigin(m_frames[m_currentFrameIndex].getLocalBounds().width / 2.f,
                        m_frames[m_currentFrameIndex].getLocalBounds().height / 2.f);
    }

    // Calculate elapsed time since last frame update
    m_elapsedTime += deltaTime;

    // Check if we need to advance the frame
    if (m_elapsedTime >= m_frameDuration)
    {
        // Reset elapsed time
        m_elapsedTime -= m_frameDuration;

        // Advance to the next frame
        m_currentFrameIndex++;

        // Reached the end of the animation, loop back to the beginning
        if (m_currentFrameIndex >= m_frames.size())
            m_currentFrameIndex = 0;
    }
}

void Animation::render(sf::RenderWindow& window) const
{
    // Draw frame
    window.draw(m_frames[m_currentFrameIndex]);
}