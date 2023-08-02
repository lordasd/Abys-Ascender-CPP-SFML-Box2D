OOP 2 - Project 2 - Abys Ascender
-------------------
Name: David Zaydenberg
-------------------
Summary:

"Abys Ascender" is a platformer game developed in C++ using SFML and Box2D.
As an adventurer, players embark on a journey through mysterious lands,
encountering enemies such as skeletons that must be defeated to progress.
The game features various obstacles like spikes, moving platforms,
and jumping challenges. It offers three levels for players to explore,
along with a built-in level builder tool for creating custom levels.

-------------------
Design:

The program starts by setting a seed using srand and creates an instance of the GameController class.
A Window class is responsible for creating a render window and returning it to the GameController.
The GameController then runs its main loop as long as the window is open.
It consists of three main functions: handleInput, update, and render.
The GameController maintains a stack of GameStates and executes the functions of the top state in the stack (input, update, and render).

The handleInput function listens for mouse clicks, key presses and releases,
and mouse movements, and sends the input to the current state.
The update function calculates the delta time and passes it to the current state for updating its logic.
It also checks if a new state change is requested, and if so,
it pushes or pops the requested state onto or from the stack, allowing for the entry or exit of a new game state.

The render function clears the window, sets the current state as the active state,and lets the state draw all the required objects.
Finally, the GameController displays the resulting image on the window.

Each game state operates with its own set of three functions: handleInput, update, and render.
These functions handle the specific logic and rendering for each state. The MainMenuState is the initial state set when the program starts.
Users can interact with buttons in the main menu, which updates the logic accordingly.
Clicking "New Game" starts the game from the beginning (level 1) and removes the current save from the save file.
The "Settings" state allows users to adjust sound management settings such as volume control for sound effects and music.
The "Help" window provides information on how to play the game and offers some context.

When the player chooses to start a new game or continue a saved game, the GameController creates a new instance of the GamePlayState.
It initializes the physics engine (Box2D) and sets the gravity. Additionally, it sets up a contact listener to handle collisions between objects.
The current level map is loaded from a file, with each layer containing the necessary information to create the game objects,
including their unique identifiers. Objects can be either static or moving, depending on their IDs.
The first layer typically represents the floor/walls using ChainedObjects, which are rectangles with physics properties.
The camera (sf::View) follows the player and keeps them in focus. Music plays continuously in the background, changing according to the current level.

In the GamePlayState's handleInput function, the player's key presses, releases,
and mouse movements are detected to determine the appropriate player actions and directions.
All objects, such as generic objects, moving platforms, player, mobs, drops, and UI, are then updated accordingly.
The rendering process involves drawing all the objects after their update.

The update function is also responsible for updating the physics simulation by stepping the world in Box2D.
Collision detection between different objects is handled by the ContactListener in Box2D. When a collision occurs,
the ContactListener processes the collision by identifying the involved objects and sending them to the appropriate collision handling functions.
Similarly, when a collision ends, the ContactListener signals the end of the collision for further processing.
All collision handling functions are defined in the CollisionHandling.cpp file using a HitMap, which maps pairs of object types to specific collision handling functions.
Runtime type identification (typeid) is used to perform the lookup and handle collisions accordingly.

There are two main categories of objects in the game: static objects and moving objects.
Static objects, such as Barrel, ChainedObject, Spikes, and FinishLine, are immovable, while the Barrel can be moved by pushing.
Decoration objects hold sprites without any physics properties, making them non-collidable.

Moving objects include Mobs, Platforms, and Weapons. Mobs have dynamic bodies and exhibit different behaviors based on their MobState.
There are two types of skeleton mobs: SkeletonMelee (warrior) and SkeletonRanged (archer).
They can be in one of three states: RoamingState (roaming/walking left or right), ChasingState (chasing the player), or AttackingState (attacking the player).
The state transitions depend on the distance between the mob and the player.
Weapons are projectiles with specific lifetimes, shapes, and sizes. They can be swords or arrows.
When a projectile is shot, it gets destroyed if it collides with any object before its time limit expires.

Platforms are moving objects with kinetic bodies that the player can stand on and move along with.
The UI is created in the GamePlayState and controlled through virtual functions for updating and rendering.

TextureManager and SoundManager are singleton classes responsible for providing resources such as textures and sounds to the game.
Each character that requires sounds, such as hurt, hit, or death sounds, utilizes the SoundManager.

When the player dies or falls off the map, the game transitions to the GameOverState.
In this state, the player has the option to retry the current level or exit the game.
If the player chooses to exit, the level number is saved.
When all levels are completed (3 levels in this case), the game transitions to the GameWinState.

-------------------
Files:

main.cpp - Sets random seed, creates a Controller and runs the game

GameController.cpp/h - Runs main loop for handling input, updating and rendering the game and
switches between game states.

Window.cpp/h - Create a window, sets FPS limit, and returns an sf::RenderWindow.

Config.h - Has all the consts relevant for the program(descriptions in file).

Animation.cpp/h - Responsible animating all animated objects

TextureManager.cpp/h - Singelton class that loads all textures in game into sf::Textures/Sprites
or data structures like unordered map and lets you get the textures

SoundManager.cpp/h - Singelton class that loads all sounds and music and lets you get them

GameState.cpp/h - Base class for all states of the game
(Gameplay, MainMenu, PauseMenu, Settings, GameOver, Loading, Retry, Back, Exit)
Responsible for pure virtual functions like handleInput, update, render, pause, resume, and exit.

MainMenuState.cpp/h - Responsible for the main menu of the game. has 5 buttons(MainMenuButton class)
which are NewGame, Continue, Settings, Help, and Exit. Menu has 2 "states", menu, and
the help page. (There are no special functionalities, so I decided not to add it as class)

MainMenuButton.cpp/h - The button in main menu. has an enum class of ButtonType { NewGame, Continue, Settings, Help, Exit, None};
and acts as the required button. has the sprite and the functionality of it self.

SettingsState.cpp/h - Has settings for volume of the soundfx and music(volume up/down/mute)

LoadingState.cpp/h - Show loading screen between levels with a picure

PauseMenuState.cpp/h - Pausing the game and letting to choose from 3 buttons: Resume, Settings, Exit.

GameOverState.cpp/h - When dying, this state apears and lets you choose to exit or retry the current level.

GameWinState.cpp/h - When finishing all levels, you win the game, and the save level resets to 1.

GameplayState.cpp/h - Responsible for the gameplay. Creating the map(reading from a file),
iterating over all the game objects, zooming on the player, deleting objects when needed and interacting
with the UI class(holds a UI member). Handling the input for the player and applying it on him. Also an escape
button for pausing the game.

Ui.cpp/h - Responsible for the UI in the gameplay(updating and rendering). hp, and level.

ContactListener.cpp/h - A derived class from b2ContactListener, a Box2D class which listens for fixture
contacts and let us handle it when deriving from it. So the class reinterprets the objects into
GameObjects and sends them to process the collision. (BeginContact and EndContact)

CollisionHandling.h - has a struct for handling UnknownCollision exceptions.
CollisionHandling.cpp - Has a hitmap of all possible GameObject collisions and a reference to the apropriate
fucntions for handling the collisions

CollisionEndHandling.cpp - Exactly the same, but when the collision ends(Bodies leave each other)

GameObject.cpp/h - Base class for all game objects that are created in the game. Holds the sprite and position.
Responsible for the Update and render pure virtual functions.

StaticObject.cpp/h - Base class for all static objects and do not move by their own. May have physics meaning
it has a b2Body for simulating physics. Overriding update and render functions.

ChainedObject.cpp/h - Derived from StaticObject. (Doesn't need to be updated)
ChainedShape which is created from vertecies to create a rectangle shape for the floor/wall.

Barrel.cpp/h - Derived from StaticObject. Box object which is just for the enviorment to interact with.

Spikes.cpp/h - Derived from StaticObject. Spikes to get hurt if touched.

FinishLine.cpp/h - Derived from StaticObject. If touched, moving to the next level

Decoration.cpp/h - Derived from StaticObject. No physics, just for looks(sprite).

MovingObject.cpp/h - Base class for all moving objects. It has a b2Body for simulating physics,
and b2World* if needed to remove a body from the world(Weapon most likely).
moving object has a direction, velocity, and a damping factor for stoping.
Also has a counter for the amount of current collision for the logic of being on the groud vs not.

Drop.cpp/h - Is a drop that drops from an enemie after defeated and it's a kinematic body, and it just
moves up and down with physics. pickup of the drop for now gives health, but it can act like a base class
for other kinds of drops that may be implemented in the game.

Operation.h - has 2 enum classes (Operation and Direction)
Operation has - Run, Jump, Stay, Falling, Attack, Hurt, Die.
Direction has - Left, Right, Up, Down.

MovingPlatform.cpp/h - Derived from MovingObject. Base class for different moving platforms(which are kimenatic bodies).
Holds the b2ChainShape(built from vertecies). Has elapsedTime, and interval for the moving part.

SidePlatform.cpp/h - Derived from MovingPlatfrom and is set for a moving platform that moves to the sides.

ElevatorPlatform.cpp/h - Derived from MovingPlatfrom and is set for a moving platform that moves to up and down.

MovingCharacter.cpp/h - Derived from MovingObject. Responsible for player and other moving characters
like enemies and such. Has an animation, operation, health, jump force and a boolian for if the character
is on the ground.

Player.cpp/h - Derived from MovingCharacter. Body of the player is created here.
Has different boolians and timers for calculating when, and what happend and for the delays.
The update override, implements all operations that the player can do like, run, jump, get hurt, attack and die...
And also update the animation. Has all sounds for the player
Has a vector of GameObjects which are sword objects(His weapon). Because weapons are projectiles, so they have physics
and the needs to be removed after specific time, so in the update, we update the weapons first for any changes.

Mob.cpp/h - Derived from MovingCharacter. Base class for all mobs. Overriding the render and attack virtual functions.
Has a vector of unique_ptr of weapons projectiles which can be sword/arrow/etc...(Depending on the enemy).
Has damage value, attackSound and timer for attack and cooldown for attack. Has update function for updating the 
weapons(If there are some in the world at the same time). Has a MobState member for all 3 states that a mob can be:
(Roaming, Chasing, Attacking).

SkeletonMelee.cpp/h - Skeleton warrior mob derives from Mob class. Holds a sword as a weapon.
Has apropriate sounds and in the update function it changes the MobState if needed.
Also, getting hurt and dying is taken care in the update function.

SkeletonRanged.cpp/h - Skeleton archer mob derives from Mob class. Holds a bow and arrow as a weapon.
Has apropriate sounds and in the update function it changes the MobState if needed.
Also, getting hurt and dying is taken care in the update function.

MobState.h - Base class for 3 states: RoamingState, ChasingState, AttackingState.
Has a direction, and a pure virtual function for udpate that gets a Mob reference to update the apropriate mob.

RoamingState.cpp/h - Mob just randomly walk right and left, and sometimes stays.
Gets appropriate animation in the constructor

ChasingState.cpp/h - Mob chasing the player. Gets appropriate animation in the constructor

AttackingState.cpp/h - Mob attacking the player with cooldown and timer.
Gets appropriate animation in the constructor

Weapon.cpp/h - Deriving from MovingObject. Base class for all types of weapons in the game.
Weapons are projectiles which has different sizes of bodies and have different life times,
speed, and accuracy. Disappearing right after hitting, or lifetime expires. Overriding update and render functions.

Sword.cpp/h - Sword weapon derived from Weapon class. creates a body and sets the position near the character,
and ready to be thrown.

Arrow.cpp/h - Arrow weapon derived from Weapon class. creates a body and sets the position near the character,
and ready to be thrown.

-------------------
DataStructure:

TextureManager holds some data structures for all the sprites and tiles for the game.
std::vector<sf::Texture> for a seiries of the same category sprites.

std::unordered_map<size_t, sf::Sprite> for the Tile map - A map that holds all of the textures,
that the map is built with. Each object created, has and ID for a specific sprite.

std::unordered_map<int, std::vector<sf::Sprite>> - For animations of each type of object, for example
the player has run, jump hurt, die. each one has a unique id to the vector for sprites(animation).

And another std::unordered_map<int, std::vector<sf::Sprite>> for all the food drops that are droping randomly
from the mobs.

HitMap = std::map<Key, HitFunctionPtr> - For the map of handling collision functions.
Key = std::pair<std::type_index, std::type_index> - 2 GameObjects that are parsed into their downcasted classes.
HitFunctionPtr = void (*)(GameObject&, GameObject&) - Pointer to the apropriate handling collision function

std::stack<std::unique_ptr<GameState>> m_stateStack - Stack of game states that are allocated, so the current 
state is at work.

std::stack<GameStateID> m_prevStateID - Holds a stack of gamestates id's and the top one is the last one that was
on, so it will help manage and change the id's.

Objects = std::vector<std::unique_ptr<GameObject>>
Objects m_objects - All objects which are not needed to specifecly take care(Decoration, spikes, barrel...).
Objects m_chainedObjects - All the floor/wall objects - Doesn't needs to be updated
Objects m_movingPlatforms - For all moving platforms.
Objects m_mobs - All mobs in the game.
Objects m_drops - All the drop that are droped that can be removed.
std::vector<sf::RectangleShape> m_backgroundLayers - Vector of all the background layers.
Objects m_weaponProjectiles - all weapon classes that are alive for a limited time/ until hit.

-------------------
Algorithms:
No algorithms, but the map creating part could be mentioned. Reading from an xml file of numbers >= 0 and ','.
Reaing each row, and analyzing it. for each id, create the apropriate object.
Each chunk of numbers, is a layer of drawing. meaning the first one belongs to the floor/walls. Meaning that
all objects are inserted in order of the drawing. a floor/wall is created a a big long as possible chunk.
if it has the same id all along the row, it will create the chained shape only after if encounters a different
id. It creates a chainedshape out of 4 vertecies. I gets first and last position and thus creats 4 vertecies and
loops it so it creates a rectangle shape like.

-------------------
Bugs: None
-------------------
Notes: 

The level design is created by me.
I used a program called Tiled, that allowed me to import different png's and use it as tiles to create my own map.
I export it to xml/tmx file, and copy paste all the layers of the level into the file my program will read.

I tried to make the game sort of realistic, so it's not your typical platformer game, meaning You can't really move
while jumping and doing activities at the same time which are not really suppose to be done in reality.

Games design - Implemented the State design, when each state of the game is it's own unique class and operates on it's
own. The states are stacked up in a stack, so we can stack up states and return to the old ones without removing/deleting
information that we could have needed.

The whole game runs on HandlCollision, Update(deltaTime), and Render(RenderWindow) pure virtual functions, so it is
generic and purpose specific. Game controller calls the apropriate function in the state.

Each progressions in levels, the level is saved in a file, and can be continued from the main menu by pressing continue.
If New Game is pressed, the saved progress is removed.

-------------------