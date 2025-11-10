#include "Character.hpp"
#include "UIHelper.hpp"  // JOB 11 - Enhanced UI
#include <iostream>

// ========== CONSTRUCTORS & DESTRUCTOR ==========

/**
 * Default constructor
 * Calls GameObject default constructor and sets health to 100
 */
Character::Character() : GameObject(0.0, 0.0, "Character"), health(100) {
    // GameObject constructor sets position to (0, 0) and name
    // health is initialized to 100
}

/**
 * Parameterized constructor
 */
Character::Character(double x, double y, const std::string& name, int health)
    : GameObject(x, y, name), health(health) {
    // GameObject constructor sets position and name
    // Initialize health to provided value
    
    // Ensure health is not negative
    if (this->health < 0) {
        this->health = 0;
    }
}

/**
 * Destructor
 */
Character::~Character() {
    // No dynamic resources to clean up
}


// ========== HEALTH MANAGEMENT ==========

int Character::getHealth() const {
    return health;
}

void Character::setHealth(int health) {
    // Ensure health doesn't go negative
    if (health < 0) {
        this->health = 0;
    } else {
        this->health = health;
    }
}

/**
 * Check if the character is alive
 * 
 * A character is alive if they have health points remaining (health > 0).
 * When health reaches 0, the character is considered dead.
 */
bool Character::isAlive() const {
    return health > 0;
}


// ========== OVERRIDE PURE VIRTUAL METHODS ==========

/**
 * Draw the character
 * 
 * Displays the character's name, position, health, and alive status
 */
void Character::draw() const {
    // JOB 11: Enhanced UI with colors and health bars
    std::cout << "[CHARACTER '" << UI::COLOR_BRIGHT_CYAN << getName() << UI::COLOR_RESET << "'] ";
    std::cout << "Pos:(" << getX() << ", " << getY() << ") ";
    std::cout << "HP: " << UI::getHealthBar(health, 100, 10, true) << " ";
    
    if (isAlive()) {
        std::cout << UI::COLOR_BRIGHT_GREEN << "ALIVE" << UI::COLOR_RESET;
    } else {
        std::cout << UI::COLOR_RED << "DEAD" << UI::COLOR_RESET;
    }
    std::cout << std::endl;
}

/**
 * Update the character's state
 * 
 * In a real game, this would:
 * - Process AI or player input
 * - Update animations
 * - Handle movement
 * - Check collisions
 * 
 * For this implementation, we simulate basic character logic.
 */
void Character::update() {
    if (isAlive()) {
        // Character is alive - perform updates
        std::cout << "  > Updating " << getName() << "... (alive, processing actions)" << std::endl;
    } else {
        // Character is dead - no active updates
        std::cout << "  > " << getName() << " is dead (no update)" << std::endl;
    }
}

