#include "GameplayState.h"
#include "Decoration.h"
#include "Player.h"
#include "Spikes.h"
#include "SkeletonMelee.h"
#include "SkeletonRanged.h"
#include "ElevatorPlatform.h"
#include "SidePlatform.h"
#include "Drop.h"
#include "FinishLine.h"
#include "Barrel.h"

GameplayState::GameplayState(bool loadLevel, const sf::View& view)
	: m_world(std::make_unique<b2World>(GRAVITY)), m_ui(view),
	  m_backGroundView(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT))
{
	m_world->SetContactListener(&m_contactListener);
	createMap(loadLevel);
	createBackground();

	// Set zoom on player
	m_cameraView.setSize(WINDOW_WIDTH / m_zoomLevel, WINDOW_HEIGHT / m_zoomLevel);

	setMusic();
}

void GameplayState::handleInput(const sf::Event& event, const sf::Vector2f&)
{
	auto player = static_cast<Player*>(m_player.get());

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Left && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player->getOperation() != Operation::Falling && !player->isHurt()) {
			player->setDirection(Direction::Left); player->setOperation(Operation::Run);
		}
		else if (event.key.code == sf::Keyboard::Right && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player->getOperation() != Operation::Falling && !player->isHurt()) {
			player->setDirection(Direction::Right); player->setOperation(Operation::Run);
		}
		else if (event.key.code == sf::Keyboard::Up && !player->isHurt()) {
			player->setDirection(Direction::Up);
		}
		else if (event.key.code == sf::Keyboard::Down && !player->isHurt()) {
			player->setDirection(Direction::Down);
		}
		else if (event.key.code == sf::Keyboard::Space && !player->isHurt())
			player->setOperation(Operation::Jump);
		else if (event.key.code == sf::Keyboard::LControl && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !player->isHurt())
			player->setOperation(Operation::Attack);
		else if (event.key.code == sf::Keyboard::Escape) // Pause
			requestStateChange(GameStateID::PauseMenu);
		else if (!player->isHurt())
			player->setOperation(Operation::Stay);
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !player->isHurt())
			player->setOperation(Operation::Stay); // If no button is pressed, just stay put.
	}
}

void GameplayState::update(float deltaTime)
{
	if (m_showLoadingScreen) // Show loading screen
	{
		requestStateChange(GameStateID::Loading);
		m_showLoadingScreen = false;
		return;
	}

	Player& player = static_cast<Player&>(*m_player);

	if (player.isTouchedFinishLine())
	{
		setNextLevel();
		return;
	}

	// Player and mobs check and deletion
	checkIfAlive(deltaTime);

	// Background clouds
	if(m_currLevel == 1)
		moveClouds(deltaTime);

	// Update Ui health and positions
	m_ui.update(deltaTime, player.getHealth());

	// View
	centerCameraOnPlayer();

	// Let Box2D do it's physics
	m_world->Step(FPS, VEL_ITER, POS_ITER);

	// Update all decorated objects
	for (const auto& object : m_objects)
		object->update(deltaTime);

	// Update moving platforms
	for (const auto& platform : m_movingPlatforms)
		platform->update(deltaTime);

	// Update player object
	m_player->update(deltaTime);
	
	// Update position of the player for the mobs to see
	for (const auto& mob : m_mobs)
	{
		static_cast<Mob&>(*mob.get()).setPlayerPosition(player.getBody()->GetPosition());
		mob->update(deltaTime);
	}

	// Update drop if droped
	for (const auto& drop : m_drops)
		drop->update(deltaTime);
}

void GameplayState::render(sf::RenderWindow& window)
{
	drawBackground(window);

	// Draw all objects
	for (const auto& object : m_objects)
		object->render(window);

	// Draw moving platforms
	for (const auto& platform : m_movingPlatforms)
		platform->render(window);

	// Draw player object
	m_player->render(window);
	
	// Draw all mobs
	for(const auto& mob : m_mobs)
		mob->render(window);

	for (const auto& drop : m_drops)
		drop->render(window);

	// Draw Ui
	m_ui.render(window);
}

void GameplayState::pause()
{
	m_gamePlayMusic->pause();
}

void GameplayState::resume()
{
	// Set Volume for the SoundFX
	static_cast<Player&>(*m_player.get()).setVolume();
	for(const auto& mob : m_mobs)
		static_cast<Mob&>(*mob.get()).setVolume();
	// Set music to play
	m_gamePlayMusic->play();
}

void GameplayState::exit()
{
	std::ofstream file(SAVEFILE);

	if (!file.is_open())
		throw std::runtime_error("Failed to open file");

	file << std::string("level" + std::to_string(m_currLevel) + ".txt");

	m_gamePlayMusic->stop();
}

void GameplayState::createMap(bool loadLevel)
{
	std::ifstream file;
	std::string level;

	if (loadLevel) // Load level requested from save file
	{
		file.open(SAVEFILE);
		if (!file.is_open())
			throw std::runtime_error("Failed to open save file\n");
		
		if (file >> level) // If read is success, open saved level
		{
			file.close();
			file.open(level);
		}
		else
			throw std::runtime_error("Failed to read from save file\n");
	}
	else if (m_currLevel > 1) // Just passed previous level
	{
		level = std::string("level" + std::to_string(m_currLevel) + ".txt");
		file.open(level);
	}
	else // open first level
	{
		level = LEVEL1;
		file.open(level);
	}

	if (!file.is_open())
		throw std::runtime_error("Failed to open file: " + level);

	// Save level number
	m_currLevel = std::stoul(level.substr(level.size() - DotTxt));
	m_ui.setLevel(m_currLevel);

	size_t row{};     // Row in file
	std::string line; // Line from the file

	// Reserve space to not resize each time
	m_objects.reserve(MAP_HEIGHT * MAP_WIDTH);

	bool readingChainedObjects = true;

	// Read level file
	while (std::getline(file, line))
	{
		//If a new layer identified, start over from first row
		if (line == "")
		{
			row = 0;
			readingChainedObjects = false;
		}
		else // Read full line
		{
			readLine(line, row, readingChainedObjects);
			++row;
		}
	}

	// Shrink to fit - We have a lot of blank spaces
	m_objects.shrink_to_fit();
}

void GameplayState::readLine(const std::string& line, size_t row, bool readingChainedObjects)
{
	sf::Vector2f position(0.f, WINDOW_HEIGHT - (TILE_SIZE * row));
	sf::Vector2f startPosition{};

	std::istringstream iss(line); // Read numbers

	size_t id{}; // Texture id

	bool chained = false; // Part of the chained shape
	
	std::vector<ChainedObject*> currentChainedObjects(5, nullptr);

	// Read a row of id's
	while (iss >> id)
	{
		if (chained) // Chain the apropriate shape
		{
			// Try chain the objects
			if (chainObjects(id, currentChainedObjects, startPosition, position))
			{
				resetChainedObjects(currentChainedObjects);
				chained = false; // Reset chain
			}
		}

		if (id != 0)
		{   
			if (!readingChainedObjects)
			{
				if (id == 158 || id == 174 || id == 9 || id == 10) // Moving platform
					m_movingPlatforms.emplace_back(gameObjectCreator(id, position));
				else if(id == 25) // Player
					m_player = gameObjectCreator(id, position);
				else if(id == 26 || id == 36) // Skeleton
					m_mobs.emplace_back(gameObjectCreator(id, position));
				else // Any other objects for decoration without physics
					m_objects.emplace_back(gameObjectCreator(id, position));
			}			
			else // First layer in map is the chained objects(floor/Walls/etc...)
			{
				if (!chained)
				{
					if (id == 60 || id == 61 || id == 62 || id == 77 || id == 78)
					{
						size_t index{};
						m_chainedObjects.emplace_back(gameObjectCreator(id, position));
						if (id <= 62)
							index = id - 60;  // Calculate the index based on the shape ID
						else
							index = id - 74;
						currentChainedObjects[index] = static_cast<ChainedObject*>(m_chainedObjects.back().get());
					}

					startPosition = position; // Save starting position of the chained objects
					chained = true;
				}
			}

			// Ignore ',' in the level file
			if (iss.peek() == ',')
				iss.ignore();
		}
		else
			iss.ignore(); // Ignore ','

		position.x += TILE_SIZE; // Next tile
	}
	// Last check after reaching last number
	if (chained) // Chain the apropriate shape
	{
		// Try chain the objects
		if (chainObjects(id, currentChainedObjects, startPosition, position))
		{
			resetChainedObjects(currentChainedObjects);
			chained = false; // Reset chain
		}
	}
}

std::unique_ptr<GameObject> GameplayState::gameObjectCreator(size_t id, const sf::Vector2f& position) const
{
	switch (id)
	{
	case 9: // Elevator short down
		return std::make_unique<ElevatorPlatform>(TextureManager::instance().getPlatform(), position, Direction::Down, ELEVATOR_INTERVAL, PLATFORM_VELOCITY, m_world.get());
	case 10: // Elevator long down
		return std::make_unique<ElevatorPlatform>(TextureManager::instance().getPlatform(), position, Direction::Down, ELEVATOR_INTERVAL_LONG, PLATFORM_VELOCITY, m_world.get());
	case 25: // Player
		return std::make_unique<Player>(TextureManager::instance().getAdventurerAnimation(0), IDLE2, position, CHARACTER_VELOCITY, m_world.get());
	case 26: // Skeleton Melee
		return std::make_unique<SkeletonMelee>(TextureManager::instance().getSkeletonMeleeAnimation(0), IDLE2, position, SKELETON_VELOCITY, m_world.get());
	case 36: // Skeleton Ranged
		return std::make_unique<SkeletonRanged>(TextureManager::instance().getSkeletonRangedAnimation(0), IDLE2, position, SKELETON_VELOCITY, m_world.get());
	case 50: // Spikes
		return std::make_unique<Spikes>(TextureManager::instance().getTile(id), position, m_world.get());
	case 60: // Square
		return std::make_unique<ChainedObject>(position, m_world.get());
	case 61: // Tri pointing down right
		return std::make_unique<ChainedObject>(position, m_world.get());
	case 62: // Tri pointing down left
		return std::make_unique<ChainedObject>(position, m_world.get());
	case 77: // Tri pointing up right
		return std::make_unique<ChainedObject>(position, m_world.get());
	case 78: // Tri pointing up left
		return std::make_unique<ChainedObject>(position, m_world.get());
	case 109: // Sid platform cavern starts to the left
		return std::make_unique<SidePlatform>(TextureManager::instance().getCavernPlatform(), position, SIDE_INTERVAL, PLATFORM_VELOCITY, Direction::Left, m_world.get());
	case 110: // Side platform cavern starts to the right
		return std::make_unique<SidePlatform>(TextureManager::instance().getCavernPlatform(), position, SIDE_INTERVAL, PLATFORM_VELOCITY, Direction::Right, m_world.get());
	case 125: // Elevator cavern short up
		return std::make_unique<ElevatorPlatform>(TextureManager::instance().getCavernPlatform(), position, Direction::Up, ELEVATOR_INTERVAL, PLATFORM_VELOCITY, m_world.get());
	case 126: // Elevator cavern long up
		return std::make_unique<ElevatorPlatform>(TextureManager::instance().getCavernPlatform(), position, Direction::Up, ELEVATOR_INTERVAL_LONG, PLATFORM_VELOCITY, m_world.get());
	case 140: // Elevator mossy short up
		return std::make_unique<ElevatorPlatform>(TextureManager::instance().getMossyPlatform(), position, Direction::Up, ELEVATOR_INTERVAL, PLATFORM_VELOCITY, m_world.get());
	case 141: // Elevator mossy long up
		return std::make_unique<ElevatorPlatform>(TextureManager::instance().getMossyPlatform(), position, Direction::Up, ELEVATOR_INTERVAL_LONG, PLATFORM_VELOCITY, m_world.get());
	case 157: // Side platform mossy starts to the right
		return std::make_unique<SidePlatform>(TextureManager::instance().getMossyPlatform(), position, SIDE_INTERVAL, PLATFORM_VELOCITY, Direction::Right, m_world.get());
	case 158: // Side platform starts to the right
		return std::make_unique<SidePlatform>(TextureManager::instance().getPlatform(), position, SIDE_INTERVAL, PLATFORM_VELOCITY, Direction::Right, m_world.get());
	case 173: // Side platform mossy starts to the left
		return std::make_unique<SidePlatform>(TextureManager::instance().getMossyPlatform(), position, SIDE_INTERVAL, PLATFORM_VELOCITY, Direction::Left, m_world.get());
	case 174: // Side platform starts to the left
		return std::make_unique<SidePlatform>(TextureManager::instance().getPlatform(), position, SIDE_INTERVAL, PLATFORM_VELOCITY, Direction::Left, m_world.get());
	case 960: // Finish line
		return std::make_unique<FinishLine>(position, m_world.get());
	case 15748: // Barrel
		return std::make_unique<Barrel>(TextureManager::instance().getTile(id), position, m_world.get());
	default: // Decorations (All we see in the game and can't be touched)
		return std::make_unique<Decoration>(TextureManager::instance().getTile(id), position);
	}
}

void GameplayState::resetChainedObjects(std::vector<ChainedObject*>& currentChainedObjects)
{
	// Reset all pointers of objects
	for (auto& obj : currentChainedObjects)
		obj = nullptr;
}

bool GameplayState::chainObjects(size_t id, std::vector<ChainedObject*>& currentChainedObjects, const sf::Vector2f& startPosition, const sf::Vector2f& endPosition)
{
	// Create the chain shape (floor/wall) with the positions

	for (size_t i = 0; i < currentChainedObjects.size(); ++i)
	{
		if (currentChainedObjects[i] && id != (60 + i) && id != (74 + i))
		{
			currentChainedObjects[i]->createChain(startPosition, endPosition, static_cast<Shape>(i));
			return true;
		}
	}

	return false;
}

void GameplayState::createBackground()
{
	// Get background layers
	const auto& backgroundLayers = TextureManager::instance().getBGLayers(m_currLevel);

	// Save backgroundlayers into vector
	m_backgroundLayers.reserve(4);

	if (m_currLevel == 1)
	{
		for (int i = 2; i < 4; ++i)
		{
			m_backgroundLayers.emplace_back(sf::RectangleShape(sf::Vector2f(LEVEL1_WIDTH, LEVEL1_HEIGHT)));
			m_backgroundLayers.back().setTexture(&backgroundLayers[i]);
		}
		// Set back clouds position size and texture
		m_backClouds.first.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
		m_backClouds.first.setTexture(&backgroundLayers[0]);
		m_backClouds.second.setPosition(WINDOW_WIDTH, 0.f);
		m_backClouds.second.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
		m_backClouds.second.setTexture(&backgroundLayers[0]);
		// Set front clouds position size and texture
		m_frontClouds.first.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
		m_frontClouds.first.setTexture(&backgroundLayers[1]);
		m_frontClouds.second.setPosition(WINDOW_WIDTH, 0.f);
		m_frontClouds.second.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
		m_frontClouds.second.setTexture(&backgroundLayers[1]);
	}
	else if (m_currLevel == 2)
	{
		for (int i = 0; i < 3; ++i)
		{
			m_backgroundLayers.emplace_back(sf::RectangleShape(sf::Vector2f(LEVEL2_WIDTH, LEVEL2_HEIGHT)));
			m_backgroundLayers.back().setTexture(&backgroundLayers[i]);
		}
	}
	else if (m_currLevel == 3)
	{
		for (int i = 0; i < 4; ++i)
		{
			m_backgroundLayers.emplace_back(sf::RectangleShape(sf::Vector2f(LEVEL3_WIDTH, LEVEL3_HEIGHT)));
			m_backgroundLayers.back().setTexture(&backgroundLayers[i]);
		}
	}
}

void GameplayState::centerCameraOnPlayer()
{
	// Center the camera on the player
	sf::Vector2f playerPosition = static_cast<Player*>(m_player.get())->getPosition();
	playerPosition = { std::round(playerPosition.x), std::round(playerPosition.y) };
	sf::Vector2f viewSize = m_cameraView.getSize();
	sf::Vector2f windowSize{};
	if (m_currLevel == 1)
		windowSize = sf::Vector2f(LEVEL1_WIDTH, LEVEL1_HEIGHT);
	else if (m_currLevel == 2)
		windowSize = sf::Vector2f(LEVEL2_WIDTH, LEVEL2_HEIGHT);
	else if (m_currLevel == 3)
		windowSize = sf::Vector2f(LEVEL3_WIDTH, LEVEL3_HEIGHT);

	// Calculate the bounds to keep the camera within the window borders
	sf::FloatRect cameraBounds(viewSize.x / 2.f, viewSize.y / 2.f, windowSize.x - viewSize.x, windowSize.y - viewSize.y);

	// Calculate the position to center the camera on the player
	sf::Vector2f cameraCenter;
	cameraCenter.x = std::min(std::max(playerPosition.x, cameraBounds.left), cameraBounds.left + cameraBounds.width);
	cameraCenter.y = std::min(std::max(playerPosition.y, cameraBounds.top), cameraBounds.top + cameraBounds.height);
	// Apply the calculated offset to center the camera on the player
	m_cameraView.setCenter(cameraCenter);
}

void GameplayState::checkIfAlive(float deltaTime)
{
	// Check if player is alive
	auto& player = static_cast<Player&>(*m_player.get());
	if (!player.isAlive())
	{
		m_deathElapsed += deltaTime;
		if (m_deathElapsed > 3.4f)
		{
			requestStateChange(GameStateID::GameOver);
			return;
		}
	}
	// Go over all mobs, and delete, if needed
	for (auto it = m_mobs.begin(); it != m_mobs.end();)
	{
		if (*it)
		{
			Mob* m_mob = static_cast<Mob*>(it->get());
			if (!m_mob->isAlive())
			{
				m_deathElapsed += deltaTime;
				if (m_deathElapsed > 1.6f)
				{
					sf::Vector2f pos{ m_mob->getBody()->GetPosition().x * PPM, (m_mob->getBody()->GetPosition().y * PPM) };
					m_mob->getBody()->SetAwake(false); // Set body physics false
					m_world->DestroyBody(m_mob->getBody()); // Destroy body
					it = m_mobs.erase(it); // Erase the element from the vector and advance the iterator
					// Create a drop
					m_drops.emplace_back(std::make_unique<Drop>(TextureManager::instance().getRandomDrop(), pos, DROP_INTERVAL, DROP_VELOCITY, m_world.get()));
					m_deathElapsed = 0.f;
					continue; // Skip the rest of the loop body since the iterator has been advanced
				}
			}
		}

		++it; // Increment the iterator
	}
	for (auto it = m_drops.begin(); it != m_drops.end();)
	{
		if (*it)
		{
			Drop* m_drop = static_cast<Drop*>(it->get());
			if (m_drop->needRemove())
			{
				m_drop->getBody()->SetAwake(false); // Set body physics false
				m_world->DestroyBody(m_drop->getBody()); // Destroy body
				it = m_drops.erase(it); // Erase the element from the vector and advance the iterator
				continue;
			}
		}

		++it;
	}
}

void GameplayState::moveClouds(float deltaTime)
{
	float movementSpeedFront = 50.0f; // Adjust this value to control the speed of movement
	float movementSpeedBack = 25.0f;
	float offsetFront = movementSpeedFront * deltaTime;
	float offsetBack = movementSpeedBack * deltaTime;

	// Move both backgrounds to the left
	m_frontClouds.first.move(-offsetFront, 0.f);
	m_frontClouds.second.move(-offsetFront, 0.f);
	m_backClouds.first.move(-offsetBack, 0.f);
	m_backClouds.second.move(-offsetBack, 0.f);

	// Check if the first background has moved completely out of the view
	if (m_frontClouds.first.getPosition().x + m_frontClouds.first.getGlobalBounds().width < 0)
		m_frontClouds.first.setPosition(m_frontClouds.second.getPosition().x + m_frontClouds.second.getGlobalBounds().width, 0.f);

	// Check if the second background has moved completely out of the view
	if (m_frontClouds.second.getPosition().x + m_frontClouds.second.getGlobalBounds().width < 0)
		m_frontClouds.second.setPosition(m_frontClouds.first.getPosition().x + m_frontClouds.first.getGlobalBounds().width, 0.f);

	// Check if the first background has moved completely out of the view
	if (m_backClouds.first.getPosition().x + m_backClouds.first.getGlobalBounds().width < 0)
		m_backClouds.first.setPosition(m_backClouds.second.getPosition().x + m_backClouds.second.getGlobalBounds().width, 0.f);

	// Check if the second background has moved completely out of the view
	if (m_backClouds.second.getPosition().x + m_backClouds.second.getGlobalBounds().width < 0)
		m_backClouds.second.setPosition(m_backClouds.first.getPosition().x + m_backClouds.first.getGlobalBounds().width, 0.f);
}

void GameplayState::setNextLevel()
{
	++m_currLevel;
	if (m_currLevel <= MAX_LEVEL)
	{
		saveLevel();
		deleteAllObjects();
		createMap(false);
		createBackground();
		m_gamePlayMusic->stop();
		setMusic();
		m_showLoadingScreen = true;
	}
	else // Win the game
	{
		requestStateChange(GameStateID::GameWin);
		m_currLevel = 1; // Reset to first level
	}
}

void GameplayState::deleteAllObjects()
{
	for (auto& obj : m_objects)
	{
		StaticObject& sObj = static_cast<StaticObject&>(*obj.get());
		if (sObj.hasPhysics())
		{
			sObj.getBody()->SetAwake(false); // Set body physics false
			m_world->DestroyBody(sObj.getBody()); // Destroy body
		}
	}
	m_objects.clear();

	for (auto& obj : m_chainedObjects)
	{
		StaticObject& cObj = static_cast<StaticObject&>(*obj.get());
		cObj.getBody()->SetAwake(false); // Set body physics false
		m_world->DestroyBody(cObj.getBody()); // Destroy body
	}
	m_chainedObjects.clear();

	for (auto& obj : m_movingPlatforms)
	{
		MovingObject& mObj = static_cast<MovingObject&>(*obj.get());
		mObj.getBody()->SetAwake(false); // Set body physics false
		m_world->DestroyBody(mObj.getBody()); // Destroy body
	}
	m_movingPlatforms.clear();

	for (auto& obj : m_mobs)
	{
		MovingObject& mObj = static_cast<MovingObject&>(*obj.get());
		mObj.getBody()->SetAwake(false); // Set body physics false
		m_world->DestroyBody(mObj.getBody()); // Destroy body
	}
	m_mobs.clear();

	for (auto& obj : m_drops)
	{
		MovingObject& mObj = static_cast<MovingObject&>(*obj.get());
		mObj.getBody()->SetAwake(false); // Set body physics false
		m_world->DestroyBody(mObj.getBody()); // Destroy body
	}
	m_drops.clear();

	MovingObject& player = static_cast<MovingObject&>(*m_player.get());
	player.getBody()->SetAwake(false); // Set body physics false
	m_world->DestroyBody(player.getBody()); // Destroy body
	delete(m_player.release());

	m_backgroundLayers.clear(); // Clear background
}

void GameplayState::saveLevel() const
{
	std::ofstream file(SAVEFILE);

	if (!file.is_open())
		throw std::runtime_error("Failed to open file");

	file << std::string("level" + std::to_string(m_currLevel) + ".txt");
}

void GameplayState::setMusic()
{
	if (m_currLevel == 1)
		m_gamePlayMusic = SoundManager::instance().getJungleBook();
	else if(m_currLevel == 2)
		m_gamePlayMusic = SoundManager::instance().getWhereEverYouAre();
	else
		m_gamePlayMusic = SoundManager::instance().getDownToTheCave();
	// Set music loop and turn on
	m_gamePlayMusic->setLoop(true);
	m_gamePlayMusic->play();
}

void GameplayState::drawBackground(sf::RenderWindow& window) const
{
	if (m_currLevel == 1)
	{
		// Set View for moving clouds
		window.setView(m_backGroundView);
		// Draw moving clouds
		window.draw(m_backClouds.first);
		window.draw(m_backClouds.second);
		window.draw(m_frontClouds.first);
		window.draw(m_frontClouds.second);

		// Draw background layes
		window.draw(m_backgroundLayers[0]);
		window.draw(m_backgroundLayers[1]);
	}
	else
		for (const auto& layer : m_backgroundLayers)
			window.draw(layer);

	// Set View for moving player
	window.setView(m_cameraView);
}
