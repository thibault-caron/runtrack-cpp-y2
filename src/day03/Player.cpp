#include "Player.hpp"
#include "UIHelper.hpp"  // JOB 11 - Enhanced UI
#include <iostream>

// ========== CONSTRUCTORS & DESTRUCTOR ==========

Player::Player(double x, double y, const std::string& name, int health)
    : Character(x, y, name, health),
      bow(),           // Default construct Bow
      spear(),         // Default construct Spear
      sword(),         // Default construct Sword
      currentWeapon(&bow),  // Start with Bow
      currentTarget(nullptr)
{
    // Character constructor called first
    // Then all weapons are constructed (composition)
    // Start with Bow equipped (beginning of cycle)
}

Player::~Player() {
    // No manual cleanup needed:
    // - bow, spear, sword are automatic (not pointers)
    // - currentWeapon is just a pointer (doesn't own)
    // - currentTarget is just a reference (doesn't own)
}


// ========== WEAPON MANAGEMENT ==========

Weapon* Player::getCurrentWeapon() const {
    return currentWeapon;
}

/**
 * Switch weapon in cycle: Bow → Spear → Sword → Bow
 * 
 * This is elegant because:
 * - No memory allocation/deallocation (just pointer change)
 * - Fast (O(1) operation)
 * - Safe (all weapons always exist)
 * 
 * This is the Strategy Pattern - changing strategy at runtime!
 */
void Player::switchWeapon() {
    // Determine next weapon in cycle
    if (currentWeapon == &bow) {
        currentWeapon = &spear;
        std::cout << "    🔄 Switched to Spear (Range:" << spear.getRange() 
                  << ", Power:" << spear.getPower() << ")" << std::endl;
    } else if (currentWeapon == &spear) {
        currentWeapon = &sword;
        std::cout << "    🔄 Switched to Sword (Range:" << sword.getRange() 
                  << ", Power:" << sword.getPower() << ")" << std::endl;
    } else {  // currentWeapon == &sword
        currentWeapon = &bow;
        std::cout << "    🔄 Switched to Bow (Range:" << bow.getRange() 
                  << ", Power:" << bow.getPower() << ")" << std::endl;
    }
}

/**
 * Equip specific weapon by name
 * Useful for manual weapon selection
 */
bool Player::equipWeapon(const std::string& weaponName) {
    if (weaponName == "Bow") {
        currentWeapon = &bow;
        return true;
    } else if (weaponName == "Spear") {
        currentWeapon = &spear;
        return true;
    } else if (weaponName == "Sword") {
        currentWeapon = &sword;
        return true;
    }
    return false;  // Invalid weapon name
}


// ========== TARGET MANAGEMENT ==========

void Player::setTarget(Character* target) {
    this->currentTarget = target;
}

Character* Player::getTarget() const {
    return currentTarget;
}


// ========== OVERRIDE METHODS ==========

void Player::draw() const {
    // JOB 11: Enhanced UI with colors and health bars
    std::cout << UI::STYLE_BOLD << "[PLAYER '" << UI::COLOR_BRIGHT_GREEN 
              << getName() << UI::COLOR_RESET << UI::STYLE_BOLD << "']" << UI::COLOR_RESET << " ";
    std::cout << "Pos:(" << getX() << ", " << getY() << ") ";
    std::cout << "HP: " << UI::getHealthBar(getHealth(), 100, 12, true) << " ";
    std::cout << "Weapon: " << UI::COLOR_YELLOW << currentWeapon->getName() << UI::COLOR_RESET;
    std::cout << " (R:" << currentWeapon->getRange() 
              << ", P:" << currentWeapon->getPower() << ")";
    std::cout << std::endl;
}

/**
 * Player Update - Turn-based combat
 * 
 * Assignment specification:
 * "À chaque tour, le joueur doit attaquer avant de changer d'arme"
 * (Each turn, player must attack before changing weapon)
 * 
 * Implementation:
 * 1. Attack current target with current weapon
 * 2. Switch to next weapon in cycle
 * 
 * This is classic turn-based RPG combat!
 */
void Player::update() {
    // Safety checks
    if (!isAlive()) {
        std::cout << "  > " << getName() << " is dead (cannot act)" << std::endl;
        return;
    }
    
    std::cout << "  > " << getName() << "'s turn:" << std::endl;
    
    // Step 1: Attack with current weapon
    if (currentTarget && currentTarget->isAlive()) {
        std::cout << "    ⚔️  Attacking " << currentTarget->getName() 
                  << " with " << currentWeapon->getName() << ":" << std::endl;
        std::cout << "    ";
        currentWeapon->attack(*currentTarget);
    } else {
        std::cout << "    ⚠️  No valid target to attack" << std::endl;
    }
    
    // Step 2: Switch weapon (as per assignment)
    switchWeapon();
}

