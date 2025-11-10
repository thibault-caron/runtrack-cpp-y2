#include "Projectile.hpp"
#include "UIHelper.hpp"  // JOB 11 - Enhanced UI
#include <iostream>

// ========== CONSTRUCTORS & DESTRUCTOR ==========

Projectile::Projectile(double x, double y, const std::string& name,
                       int damage, GameObject* owner, Character* target)
    : GameObject(x, y, name),
      damage(damage),
      owner(owner),
      target(target),
      hasHit(false)
{
    // GameObject constructor sets position and name
    // Initialize projectile-specific members
}

Projectile::~Projectile() {
    // No dynamic resources to clean up
}


// ========== ACCESSORS ==========

int Projectile::getDamage() const {
    return damage;
}

GameObject* Projectile::getOwner() const {
    return owner;
}

Character* Projectile::getTarget() const {
    return target;
}

bool Projectile::getHasHit() const {
    return hasHit;
}

bool Projectile::isExpired() const {
    return hasHit;  // Projectile expires after hitting
}


// ========== OVERRIDE PURE VIRTUAL METHODS ==========

void Projectile::draw() const {
    // JOB 11: Enhanced UI with colors
    std::cout << "[PROJECTILE '" << UI::COLOR_BRIGHT_YELLOW << getName() << UI::COLOR_RESET << "'] ";
    std::cout << "Pos:(" << getX() << ", " << getY() << ") ";
    std::cout << "Dmg:" << damage << " ";
    
    if (hasHit) {
        std::cout << "Status: " << UI::COLOR_GREEN << "HIT" << UI::COLOR_RESET;
    } else {
        std::cout << "Status: " << UI::COLOR_YELLOW << "FLYING" << UI::COLOR_RESET;
    }
    
    if (target) {
        std::cout << " → " << target->getName();
    }
    
    std::cout << std::endl;
}

/**
 * Update the projectile
 * 
 * INSTANT HIT MODEL (as per your design choice):
 * - Projectile immediately checks if it hits target
 * - If yes: deal damage and mark as expired
 * - If no: mark as expired anyway (missed)
 * 
 * This makes bow attacks feel different from melee:
 * - Explicit projectile object
 * - Visual feedback
 * - Can be extended to multi-turn flight later
 */
void Projectile::update() {
    if (hasHit) {
        // Already hit, nothing to do
        return;
    }
    
    // Check if we hit the target
    if (checkHit()) {
        // HIT! Deal damage
        dealDamage();
        hasHit = true;
    } else {
        // Missed or target unreachable
        std::cout << "    💨 " << getName() << " misses its target" << std::endl;
        hasHit = true;  // Expired anyway
    }
}


// ========== PROJECTILE-SPECIFIC METHODS ==========

/**
 * Check if projectile hit the target
 * 
 * For INSTANT HIT model:
 * - Projectile spawns at owner's position
 * - Immediately checks if it would hit target
 * - Uses collision detection (distance check)
 * 
 * This represents the arrow flying and hitting instantly
 * (or missing if target is too far or invalid)
 */
bool Projectile::checkHit() {
    // Safety checks
    if (!target) {
        return false;  // No target
    }
    
    if (!target->isAlive()) {
        return false;  // Target already dead
    }
    
    // For instant hit model, we assume projectile reaches target
    // In reality, bow has Range=4, so we could check:
    // if (distance(*target) <= 4.0) { hit! }
    
    // But for simplicity (as per your design), we always hit if target exists and alive
    return true;
}

/**
 * Deal damage to target
 * 
 * Applies projectile damage to the character.
 * Provides visual feedback (arrow hitting).
 */
void Projectile::dealDamage() {
    if (!target || !target->isAlive()) {
        return;
    }
    
    int currentHealth = target->getHealth();
    int newHealth = currentHealth - damage;
    target->setHealth(newHealth);
    
    std::cout << "    🎯 " << getName() << " HITS " << target->getName() << "! ";
    std::cout << "Deals " << damage << " damage ";
    std::cout << "(HP: " << currentHealth << " → " << target->getHealth() << ")";
    
    if (!target->isAlive()) {
        std::cout << " [DEFEATED!]";
    }
    
    std::cout << std::endl;
}

