# Abys Ascender

## Project Information
- **Developer:** David Zaydenberg

## Summary
"Abys Ascender" is a platformer game developed in C++ using SFML and Box2D. Players take on the role of an adventurer navigating mysterious lands, overcoming obstacles, and battling enemies such as skeletons. The game includes:
- Various obstacles like spikes, moving platforms, and jumping challenges.
- Three unique levels to explore.
- A built-in level builder tool for creating custom levels.

## Design Overview
The game follows a structured object-oriented design. The main components include:

### **Game Flow**
1. **Initialization:** The program initializes by setting a seed using `srand` and creating an instance of the `GameController` class.
2. **Window Management:** A `Window` class is responsible for creating and managing the render window, which is returned to the `GameController`.
3. **Main Loop:** The `GameController` runs its main loop as long as the window is open. The loop consists of three key functions:
   - `handleInput()`: Processes user input.
   - `update()`: Updates game objects and physics.
   - `render()`: Draws objects onto the screen.
4. **Game States:** The `GameController` maintains a stack of `GameStates`, executing the functions of the top state in the stack.

## Features
- **Engaging platformer gameplay** with dynamic obstacles and enemies.
- **Physics-based movement** using Box2D for realistic interactions.
- **Multiple levels** providing a progressively challenging experience.
- **Custom level builder** for players to design and play their own levels.

## Technologies Used
- **Programming Language:** C++
- **Libraries:**
  - SFML (Simple and Fast Multimedia Library) for rendering and input handling.
  - Box2D for physics simulation.

## How to Run
1. Ensure you have **C++ (G++)**, **SFML**, and **Box2D** installed.
2. Clone the repository:
   ```sh
   git clone <repository-url>
   ```
3. Navigate to the project directory:
   ```sh
   cd abys-ascender
   ```
4. Compile the project:
   ```sh
   make
   ```
5. Run the game:
   ```sh
   ./abys_ascender
   ```

## Controls
- **Arrow Keys / WASD** - Move the player
- **Space** - Jump
- **Escape** - Pause/Quit

## Future Improvements
- Adding more levels and enemies.
- Enhancing AI for enemy behaviors.
- Implementing a saving/loading system for custom levels.

## Credits
- **Developer:** David Zaydenberg
- **Libraries:** SFML, Box2D

## License
This project is for educational purposes and follows an open-source license. Feel free to contribute!

---
Enjoy the adventure in **Abys Ascender**!

