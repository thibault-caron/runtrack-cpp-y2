#include "Enemy.hpp"
#include "UIHelper.hpp"  // JOB 11 - Enhanced UI
#include <iostream>
#include <cmath>

// ========== CONSTRUCTORS & DESTRUCTOR ==========

Enemy::Enemy(double x, double y, const std::string& name, int health,
             Character* targetPlayer, int attackDamage)
    : Character(x, y, name, health),
      targetPlayer(targetPlayer),
      attackDamage(attackDamage),
      attackRange(1.0),    // Melee range
      moveSpeed(1.0)       // 1 unit per turn
{
    // Character constructor called first (position, name, health)
    // Then initialize Enemy-specific members
}

Enemy::~Enemy() {
    // No dynamic resources to clean up
    // targetPlayer is not owned by Enemy (just a reference)
}


// ========== ACCESSORS ==========

int Enemy::getAttackDamage() const {
    return attackDamage;
}

double Enemy::getAttackRange() const {
    return attackRange;
}

double Enemy::getMoveSpeed() const {
    return moveSpeed;
}

void Enemy::setTarget(Character* player) {
    this->targetPlayer = player;
}


// ========== OVERRIDE METHODS ==========

void Enemy::draw() const {
    // JOB 11: Enhanced UI with colors and health bars
    std::cout << "[ENEMY '" << UI::COLOR_BRIGHT_RED << getName() << UI::COLOR_RESET << "'] ";
    std::cout << "Pos:(" << getX() << ", " << getY() << ") ";
    std::cout << "HP: " << UI::getHealthBar(getHealth(), 100, 10, true) << " ";
    std::cout << "Dmg:" << UI::COLOR_RED << attackDamage << UI::COLOR_RESET << " ";
    
    if (isAlive()) {
        std::cout << UI::COLOR_BRIGHT_RED << "HOSTILE" << UI::COLOR_RESET;
    } else {
        std::cout << UI::COLOR_RED << "DEFEATED" << UI::COLOR_RESET;
    }
    std::cout << std::endl;
}

/**
 * AI Update - The heart of enemy behavior!
 * 
 * This implements a simple but effective AI:
 * - Calculate distance to player
 * - If too far: pathfind towards player
 * - If in range: attack player
 * 
 * This is exactly how real game AI works (Unity, Unreal, etc.)
 */
void Enemy::update() {
    // Safety checks
    if (!isAlive()) {
        std::cout << "  > " << getName() << " is dead (no AI)" << std::endl;
        return;
    }
    
    if (!targetPlayer || !targetPlayer->isAlive()) {
        std::cout << "  > " << getName() << " has no valid target" << std::endl;
        return;
    }
    
    // Calculate distance to target using inherited Vector2d method!
    double dist = distance(*targetPlayer);
    
    std::cout << "  > " << getName() << " AI: ";
    std::cout << "Distance to target = " << dist;
    
    // Decision making: Move or Attack?
    if (dist <= attackRange) {
        // In attack range - ATTACK!
        std::cout << " [IN RANGE - ATTACKING!]" << std::endl;
        attackTarget();
    } else {
        // Too far - MOVE CLOSER
        std::cout << " [MOVING CLOSER]" << std::endl;
        moveTowardsTarget();
    }
}


// ========== PRIVATE HELPER METHODS ==========

/**
 * Pathfinding: Move towards target
 * 
 * This is basic vector math pathfinding:
 * 1. Calculate direction vector (dx, dy)
 * 2. Normalize it (make length = 1)
 * 3. Scale by moveSpeed
 * 4. Add to current position
 * 
 * This is REAL game AI pathfinding!
 */
void Enemy::moveTowardsTarget() {
    // Get target position
    double targetX = targetPlayer->getX();
    double targetY = targetPlayer->getY();
    
    // Calculate direction vector
    double dx = targetX - getX();
    double dy = targetY - getY();
    
    // Calculate distance (for normalization)
    double dist = std::sqrt(dx * dx + dy * dy);
    
    // Edge case: already at target (shouldn't happen, but safe)
    if (dist < 0.0001) {
        return;
    }
    
    // Normalize direction vector (make it length = 1)
    double ndx = dx / dist;
    double ndy = dy / dist;
    
    // Move moveSpeed units in that direction
    double newX = getX() + ndx * moveSpeed;
    double newY = getY() + ndy * moveSpeed;
    
    // Update position
    setX(newX);
    setY(newY);
    
    std::cout << "    → Moved from (" << getX() - ndx * moveSpeed 
              << ", " << getY() - ndy * moveSpeed << ") to ("
              << getX() << ", " << getY() << ")" << std::endl;
}

/**
 * Attack the target player
 * 
 * Simple melee attack:
 * - Reduce target's health by attackDamage
 * - Provide feedback
 */
void Enemy::attackTarget() {
    int currentHealth = targetPlayer->getHealth();
    int newHealth = currentHealth - attackDamage;
    targetPlayer->setHealth(newHealth);
    
    std::cout << "    💥 " << getName() << " attacks " << targetPlayer->getName();
    std::cout << " for " << attackDamage << " damage! ";
    std::cout << "(HP: " << currentHealth << " → " << targetPlayer->getHealth() << ")";
    
    if (!targetPlayer->isAlive()) {
        std::cout << " [PLAYER DEFEATED!]";
    }
    
    std::cout << std::endl;
}

