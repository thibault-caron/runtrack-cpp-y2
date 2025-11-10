#ifndef GAME_HPP
#define GAME_HPP

#include "GameManager.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Decor.hpp"
#include "Projectile.hpp"
#include "UIHelper.hpp"  // JOB 11 - Enhanced UI
#include <string>
#include <vector>

/**
 * Game - Main game controller with INTERACTIVE game loop
 * 
 * JOB 08 - INTERACTIVE MODE
 * 
 * This version adds USER INPUT to the game:
 * - Player controls movement (WASD)
 * - Player chooses to attack
 * - Player can change weapons manually
 * - View status and information
 * 
 * Input System:
 * - std::cin for text input (blocking, turn-based)
 * - Menu-driven interface
 * - Input validation
 * 
 * This demonstrates:
 * - Interactive gameplay
 * - Input handling and validation
 * - Menu systems
 * - User experience design
 * 
 * This is COMPLETE INTERACTIVE GAME ARCHITECTURE!
 */

enum class GameState {
    SETUP,      // Initializing game
    PLAYING,    // Main gameplay
    VICTORY,    // Player won
    DEFEAT,     // Player lost
    DRAW        // Turn limit reached
};

class Game {
private:
    // ========== GAME COMPONENTS ==========
    GameManager manager;     // Manages all game objects
    GameState state;         // Current game state
    
    // ========== GAME OBJECTS ==========
    Player* player;          // Player character
    
    // ========== GAME PARAMETERS ==========
    int currentTurn;         // Current turn number
    static const int MAX_TURNS = 50;  // Turn limit
    
    // ========== INTERACTIVE MODE ==========
    bool interactiveMode;    // True = player controlled, False = automated

public:
    // ========== CONSTRUCTOR & DESTRUCTOR ==========
    
    /**
     * Constructor
     * @param interactive Enable interactive mode (default: true)
     */
    Game(bool interactive = true);
    
    /**
     * Destructor
     */
    ~Game();
    
    
    // ========== MAIN GAME INTERFACE ==========
    
    /**
     * Run the complete game
     */
    void run();
    
private:
    // ========== GAME PHASES ==========
    
    /**
     * Setup phase - Initialize game world
     */
    void setup();
    
    /**
     * Main game loop
     */
    void gameLoop();
    
    /**
     * Process one turn (INTERACTIVE VERSION)
     */
    void processTurn();
    
    /**
     * Process one turn (AUTOMATED VERSION - for comparison)
     */
    void processAutomatedTurn();
    
    /**
     * Check victory/defeat conditions
     */
    void checkGameOver();
    
    
    // ========== INTERACTIVE INPUT SYSTEM ==========
    
    /**
     * Display player action menu
     * Shows available actions with clear instructions
     */
    void displayPlayerMenu();
    
    /**
     * Get validated integer input from user
     * @param min Minimum valid value
     * @param max Maximum valid value
     * @return Validated input
     * 
     * Handles invalid input gracefully with re-prompting
     */
    int getValidatedInput(int min, int max);
    
    /**
     * Get validated string input from user
     * @param validOptions Vector of valid string options
     * @return Validated input
     */
    std::string getValidatedStringInput(const std::vector<std::string>& validOptions);
    
    /**
     * Handle player's chosen action
     * @param choice Menu choice number
     */
    void handlePlayerAction(int choice);
    
    
    // ========== PLAYER ACTIONS ==========
    
    /**
     * Handle player movement (WASD controls)
     * 
     * Controls:
     * W - Move up (north)
     * A - Move left (west)
     * S - Move down (south)
     * D - Move right (east)
     * 
     * Then asks for distance to move
     */
    void handlePlayerMove();
    
    /**
     * Handle player attack
     * Attacks current target with current weapon
     */
    void handlePlayerAttack();
    
    /**
     * Handle manual weapon change
     * Allows player to select specific weapon
     */
    void handleWeaponChange();
    
    /**
     * Display detailed player status
     * Shows position, health, weapon, target info
     */
    void displayPlayerStatus();
    
    /**
     * Display game help/instructions
     */
    void displayHelp();
    
    
    // ========== DISPLAY METHODS ==========
    
    /**
     * Display game title and introduction
     */
    void displayIntro();
    
    /**
     * Display turn header
     */
    void displayTurnHeader();
    
    /**
     * Display current game state
     */
    void displayState();
    
    /**
     * Display final results
     */
    void displayResult();
    
    /**
     * Display game statistics
     */
    void displayStats();
    
    
    // ========== HELPER METHODS ==========
    
    /**
     * Count living enemies
     */
    int countLivingEnemies() const;
    
    /**
     * Get state name as string
     */
    std::string getStateName(GameState state) const;
    
    /**
     * Wait for user to press Enter
     */
    void waitForEnter();
    
    /**
     * Clear screen (cross-platform)
     */
    void clearScreen();
};

#endif // GAME_HPP
