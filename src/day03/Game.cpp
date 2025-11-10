#include "Game.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>
#include <sstream>  // For string stream in UI

// ========== CONSTRUCTOR & DESTRUCTOR ==========

Game::Game(bool interactive) 
    : state(GameState::SETUP),
      player(nullptr),
      currentTurn(0),
      interactiveMode(interactive)
{
    std::cout << "[Game] Game instance created" << std::endl;
    if (interactiveMode) {
        std::cout << "[Game] Interactive mode ENABLED" << std::endl;
    } else {
        std::cout << "[Game] Automated mode" << std::endl;
    }
}

Game::~Game() {
    std::cout << "[Game] Game instance destroyed" << std::endl;
}


// ========== MAIN GAME INTERFACE ==========

void Game::run() {
    displayIntro();
    
    setup();
    
    state = GameState::PLAYING;
    gameLoop();
    
    displayResult();
}


// ========== GAME PHASES ==========

void Game::setup() {
    std::cout << "\n[SETUP] Initializing game world..." << std::endl;
    
    // Create player at origin
    player = manager.createObject<Player>(0.0, 0.0, "Hero", 80);
    std::cout << "  ✓ Created player: " << player->getName() 
              << " (HP: " << player->getHealth() << ")" << std::endl;
    
    // Create enemies at various distances
    Enemy* enemy1 = manager.createObject<Enemy>(5.0, 0.0, "Goblin", 25, player, 6);
    std::cout << "  ✓ Created enemy: " << enemy1->getName() 
              << " (HP: " << enemy1->getHealth() << ", Distance: " << player->distance(*enemy1) << ")" << std::endl;
    
    Enemy* enemy2 = manager.createObject<Enemy>(10.0, 0.0, "Orc", 35, player, 8);
    std::cout << "  ✓ Created enemy: " << enemy2->getName() 
              << " (HP: " << enemy2->getHealth() << ", Distance: " << player->distance(*enemy2) << ")" << std::endl;
    
    Enemy* enemy3 = manager.createObject<Enemy>(8.0, 6.0, "Troll", 40, player, 10);
    std::cout << "  ✓ Created enemy: " << enemy3->getName() 
              << " (HP: " << enemy3->getHealth() << ", Distance: " << player->distance(*enemy3) << ")" << std::endl;
    
    // Set player's initial target
    player->setTarget(enemy1);
    std::cout << "  ✓ Player targeting: " << enemy1->getName() << std::endl;
    
    // Create decorative objects
    manager.createObject<Decor>(3.0, 3.0, "Ancient Tree");
    manager.createObject<Decor>(-2.0, 4.0, "Boulder");
    manager.createObject<Decor>(7.0, -3.0, "Ruins");
    std::cout << "  ✓ Created 3 decorative objects" << std::endl;
    
    std::cout << "\n[SETUP] World initialized with " << manager.size() << " objects" << std::endl;
    
    if (interactiveMode) {
        std::cout << "\n💡 TIP: Type 'h' during game for help!" << std::endl;
    }
    
    waitForEnter();
}

void Game::gameLoop() {
    std::cout << "\n╔════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║          GAME STARTED - GOOD LUCK!             ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
    
    while (state == GameState::PLAYING) {
        currentTurn++;
        
        displayTurnHeader();
        
        if (interactiveMode) {
            processTurn();  // Interactive mode
        } else {
            processAutomatedTurn();  // Automated mode
        }
        
        checkGameOver();
        
        if (currentTurn >= MAX_TURNS && state == GameState::PLAYING) {
            std::cout << "\n⏰ Turn limit reached! Game ends in a draw." << std::endl;
            state = GameState::DRAW;
        }
    }
}

void Game::processTurn() {
    // Display current state
    displayState();
    
    std::cout << "\n┌─────────────────────────────────────┐" << std::endl;
    std::cout << "│         YOUR TURN - HERO            │" << std::endl;
    std::cout << "└─────────────────────────────────────┘" << std::endl;
    
    // Player phase (interactive)
    bool turnEnded = false;
    while (!turnEnded && player && player->isAlive()) {
        displayPlayerMenu();
        int choice = getValidatedInput(1, 6);
        
        if (choice == 5) {
            // Pass turn
            turnEnded = true;
        } else if (choice == 6) {
            // Help
            displayHelp();
        } else {
            handlePlayerAction(choice);
            turnEnded = true;  // One action per turn
        }
    }
    
    // Check if player's target is dead and switch to next enemy
    if (player && player->getTarget() && !player->getTarget()->isAlive()) {
        std::cout << "\n  ℹ️  Current target defeated, looking for new target..." << std::endl;
        
        for (size_t i = 0; i < manager.size(); i++) {
            if (Enemy* enemy = dynamic_cast<Enemy*>(manager.getObject(i))) {
                if (enemy->isAlive()) {
                    player->setTarget(enemy);
                    std::cout << "  ℹ️  New target: " << enemy->getName() << std::endl;
                    break;
                }
            }
        }
    }
    
    // Enemy phase
    std::cout << "\n┌─────────────────────────────────────┐" << std::endl;
    std::cout << "│         ENEMY TURN                  │" << std::endl;
    std::cout << "└─────────────────────────────────────┘" << std::endl;
    
    for (size_t i = 0; i < manager.size(); i++) {
        if (Enemy* enemy = dynamic_cast<Enemy*>(manager.getObject(i))) {
            enemy->update();
        }
    }
    
    // Cleanup phase
    std::cout << "\n[CLEANUP PHASE]" << std::endl;
    
    // Remove dead characters
    size_t removedDead = manager.removeDeadObjects();
    if (removedDead > 0) {
        std::cout << "  🗑️  Removed " << removedDead << " dead object(s)" << std::endl;
    }
    
    // Remove expired projectiles (JOB 10)
    size_t removedProjectiles = manager.removeExpiredProjectiles();
    if (removedProjectiles > 0) {
        std::cout << "  🏹 Removed " << removedProjectiles << " expired projectile(s)" << std::endl;
    }
    
    if (removedDead == 0 && removedProjectiles == 0) {
        std::cout << "  ✓ No objects to remove" << std::endl;
    }
    
    if (state == GameState::PLAYING) {
        waitForEnter();
    }
}

void Game::processAutomatedTurn() {
    displayState();
    
    std::cout << "\n┌─────────────────────────────────────┐" << std::endl;
    std::cout << "│         ACTIONS THIS TURN           │" << std::endl;
    std::cout << "└─────────────────────────────────────┘" << std::endl;
    
    std::cout << "\n[PLAYER PHASE]" << std::endl;
    if (player && player->isAlive()) {
        player->update();
        
        if (player->getTarget() && !player->getTarget()->isAlive()) {
            std::cout << "  ℹ️  Current target defeated, looking for new target..." << std::endl;
            
            for (size_t i = 0; i < manager.size(); i++) {
                if (Enemy* enemy = dynamic_cast<Enemy*>(manager.getObject(i))) {
                    if (enemy->isAlive()) {
                        player->setTarget(enemy);
                        std::cout << "  ℹ️  New target: " << enemy->getName() << std::endl;
                        break;
                    }
                }
            }
        }
    }
    
    std::cout << "\n[ENEMY PHASE]" << std::endl;
    for (size_t i = 0; i < manager.size(); i++) {
        if (Enemy* enemy = dynamic_cast<Enemy*>(manager.getObject(i))) {
            // Store old position in case we need to revert due to collision
            double oldX = enemy->getX();
            double oldY = enemy->getY();
            
            // Enemy AI determines new position
            enemy->update();
            
            // Check if new position causes collision (JOB 09)
            double newX = enemy->getX();
            double newY = enemy->getY();
            
            // If position changed, check for collision
            if (oldX != newX || oldY != newY) {
                // Temporarily move back to check collision from old position
                enemy->setX(oldX);
                enemy->setY(oldY);
                
                if (!manager.canMoveTo(enemy, newX, newY)) {
                    // Collision detected! Stay at old position
                    std::cout << "    ⚠️  " << enemy->getName() << " blocked by collision" << std::endl;
                } else {
                    // No collision, move to new position
                    enemy->setX(newX);
                    enemy->setY(newY);
                }
            }
        }
    }
    
    std::cout << "\n[CLEANUP PHASE]" << std::endl;
    
    // Remove dead characters
    size_t removedDead = manager.removeDeadObjects();
    if (removedDead > 0) {
        std::cout << "  🗑️  Removed " << removedDead << " dead object(s)" << std::endl;
    }
    
    // Remove expired projectiles (JOB 10)
    size_t removedProjectiles = manager.removeExpiredProjectiles();
    if (removedProjectiles > 0) {
        std::cout << "  🏹 Removed " << removedProjectiles << " expired projectile(s)" << std::endl;
    }
    
    if (removedDead == 0 && removedProjectiles == 0) {
        std::cout << "  ✓ No objects to remove" << std::endl;
    }
    
    std::cout << std::endl;
}

void Game::checkGameOver() {
    if (!player || !player->isAlive()) {
        state = GameState::DEFEAT;
        return;
    }
    
    int livingEnemies = countLivingEnemies();
    if (livingEnemies == 0) {
        state = GameState::VICTORY;
        return;
    }
    
    state = GameState::PLAYING;
}


// ========== INTERACTIVE INPUT SYSTEM ==========

void Game::displayPlayerMenu() {
    std::cout << "\n╔═══════════════════════════════════╗" << std::endl;
    std::cout << "║       CHOOSE YOUR ACTION          ║" << std::endl;
    std::cout << "╠═══════════════════════════════════╣" << std::endl;
    std::cout << "║ [1] Move (WASD)                   ║" << std::endl;
    std::cout << "║ [2] Attack " << std::left << std::setw(23);
    if (player->getTarget()) {
        std::cout << ("(" + player->getTarget()->getName() + ")");
    } else {
        std::cout << "(No target)";
    }
    std::cout << " ║" << std::endl;
    std::cout << "║ [3] Change Weapon ";
    std::cout << "(" << player->getCurrentWeapon()->getName() << ")";
    for (int i = player->getCurrentWeapon()->getName().length(); i < 11; i++) std::cout << " ";
    std::cout << "║" << std::endl;
    std::cout << "║ [4] View Status                   ║" << std::endl;
    std::cout << "║ [5] Pass Turn                     ║" << std::endl;
    std::cout << "║ [6] Help                          ║" << std::endl;
    std::cout << "╚═══════════════════════════════════╝" << std::endl;
    std::cout << "Your choice: ";
}

int Game::getValidatedInput(int min, int max) {
    int choice;
    while (true) {
        std::cin >> choice;
        
        if (std::cin.fail() || choice < min || choice > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "❌ Invalid input! Please enter a number between " 
                      << min << " and " << max << ": ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

std::string Game::getValidatedStringInput(const std::vector<std::string>& validOptions) {
    std::string input;
    while (true) {
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        // Convert to lowercase for comparison
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
        
        // Check if input is valid
        for (const auto& option : validOptions) {
            std::string lowerOption = option;
            std::transform(lowerOption.begin(), lowerOption.end(), lowerOption.begin(), ::tolower);
            if (input == lowerOption) {
                return input;
            }
        }
        
        std::cout << "❌ Invalid input! Valid options: ";
        for (size_t i = 0; i < validOptions.size(); i++) {
            std::cout << validOptions[i];
            if (i < validOptions.size() - 1) std::cout << ", ";
        }
        std::cout << "\nTry again: ";
    }
}

void Game::handlePlayerAction(int choice) {
    switch (choice) {
        case 1:
            handlePlayerMove();
            break;
        case 2:
            handlePlayerAttack();
            break;
        case 3:
            handleWeaponChange();
            break;
        case 4:
            displayPlayerStatus();
            break;
        default:
            std::cout << "Invalid action!" << std::endl;
    }
}


// ========== PLAYER ACTIONS ==========

void Game::handlePlayerMove() {
    std::cout << "\n🚶 MOVEMENT" << std::endl;
    std::cout << "Current position: (" << player->getX() << ", " << player->getY() << ")" << std::endl;
    std::cout << "\nDirection:" << std::endl;
    std::cout << "  [W] Up (North)" << std::endl;
    std::cout << "  [A] Left (West)" << std::endl;
    std::cout << "  [S] Down (South)" << std::endl;
    std::cout << "  [D] Right (East)" << std::endl;
    std::cout << "Choice: ";
    
    std::string direction = getValidatedStringInput({"w", "a", "s", "d"});
    
    std::cout << "Distance to move: ";
    double distance;
    while (true) {
        std::cin >> distance;
        if (std::cin.fail() || distance <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "❌ Invalid! Enter positive number: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    
    double oldX = player->getX();
    double oldY = player->getY();
    double newX = oldX;
    double newY = oldY;
    
    if (direction == "w") {
        newY += distance;
        std::cout << "→ Attempting to move UP (North)" << std::endl;
    } else if (direction == "s") {
        newY -= distance;
        std::cout << "→ Attempting to move DOWN (South)" << std::endl;
    } else if (direction == "a") {
        newX -= distance;
        std::cout << "→ Attempting to move LEFT (West)" << std::endl;
    } else if (direction == "d") {
        newX += distance;
        std::cout << "→ Attempting to move RIGHT (East)" << std::endl;
    }
    
    // COLLISION DETECTION (JOB 09)
    if (manager.canMoveTo(player, newX, newY)) {
        // Movement is valid - no collisions!
        player->setX(newX);
        player->setY(newY);
        std::cout << "  ✅ Moved from (" << oldX << ", " << oldY << ") to (" 
                  << newX << ", " << newY << ")" << std::endl;
    } else {
        // Movement blocked by collision!
        GameObject* blocking = manager.getBlockingObject(player, newX, newY);
        std::cout << "  ❌ COLLISION! Movement blocked by " << blocking->getName() << std::endl;
        std::cout << "  You remain at (" << oldX << ", " << oldY << ")" << std::endl;
    }
}

void Game::handlePlayerAttack() {
    if (!player->getTarget()) {
        std::cout << "❌ No target selected!" << std::endl;
        return;
    }
    
    if (!player->getTarget()->isAlive()) {
        std::cout << "❌ Target is already dead!" << std::endl;
        return;
    }
    
    std::cout << "\n⚔️  ATTACK" << std::endl;
    
    // JOB 10: Special handling for Bow (creates projectile)
    if (player->getCurrentWeapon()->getName() == "Bow") {
        std::cout << "🏹 Firing arrow at " << player->getTarget()->getName() << "!" << std::endl;
        
        // Create arrow projectile at player's position
        Projectile* arrow = manager.createObject<Projectile>(
            player->getX(),
            player->getY(),
            "Arrow",
            player->getCurrentWeapon()->getPower(),  // Bow power = 1
            player,
            player->getTarget()
        );
        
        std::cout << "    💨 Arrow flies through the air..." << std::endl;
        
        // Immediately process the arrow (instant hit model)
        arrow->update();
        
        // Note: Arrow will be cleaned up automatically by smart pointer
        // We could remove it immediately or let cleanup phase handle it
        
    } else {
        // Melee weapons (Spear, Sword) use direct attack
        std::cout << "Attacking " << player->getTarget()->getName() 
                  << " with " << player->getCurrentWeapon()->getName() << "!" << std::endl;
        std::cout << "    ";
        player->getCurrentWeapon()->attack(*player->getTarget());
    }
}

void Game::handleWeaponChange() {
    std::cout << "\n🗡️  CHANGE WEAPON" << std::endl;
    std::cout << "Current weapon: " << player->getCurrentWeapon()->getName() << std::endl;
    std::cout << "\nAvailable weapons:" << std::endl;
    std::cout << "  [1] Bow    (Range: 4, Power: 1)" << std::endl;
    std::cout << "  [2] Spear  (Range: 2, Power: 2)" << std::endl;
    std::cout << "  [3] Sword  (Range: 1, Power: 4)" << std::endl;
    std::cout << "Choice: ";
    
    int weaponChoice = getValidatedInput(1, 3);
    
    switch (weaponChoice) {
        case 1:
            player->equipWeapon("Bow");
            std::cout << "→ Equipped Bow" << std::endl;
            break;
        case 2:
            player->equipWeapon("Spear");
            std::cout << "→ Equipped Spear" << std::endl;
            break;
        case 3:
            player->equipWeapon("Sword");
            std::cout << "→ Equipped Sword" << std::endl;
            break;
    }
}

void Game::displayPlayerStatus() {
    std::cout << "\n╔═══════════════════════════════════╗" << std::endl;
    std::cout << "║        PLAYER STATUS              ║" << std::endl;
    std::cout << "╚═══════════════════════════════════╝" << std::endl;
    
    player->draw();
    
    if (player->getTarget()) {
        double dist = player->distance(*player->getTarget());
        std::cout << "\nTarget: " << player->getTarget()->getName() 
                  << " (Distance: " << dist << ")" << std::endl;
        player->getTarget()->draw();
    } else {
        std::cout << "\nTarget: None" << std::endl;
    }
    
    std::cout << "\nEnemies remaining: " << countLivingEnemies() << std::endl;
}

void Game::displayHelp() {
    std::cout << "\n╔═══════════════════════════════════╗" << std::endl;
    std::cout << "║             HELP                  ║" << std::endl;
    std::cout << "╚═══════════════════════════════════╝" << std::endl;
    std::cout << "\nGOAL: Defeat all enemies!" << std::endl;
    std::cout << "\nACTIONS:" << std::endl;
    std::cout << "  Move: Change position (WASD + distance)" << std::endl;
    std::cout << "  Attack: Deal damage with current weapon" << std::endl;
    std::cout << "  Weapon: Switch between Bow/Spear/Sword" << std::endl;
    std::cout << "\nWEAPONS:" << std::endl;
    std::cout << "  Bow:   Long range (4), low power (1)" << std::endl;
    std::cout << "  Spear: Medium range (2), medium power (2)" << std::endl;
    std::cout << "  Sword: Melee (1), high power (4)" << std::endl;
    std::cout << "\nSTRATEGY:" << std::endl;
    std::cout << "  - Keep distance and use Bow (safe but slow)" << std::endl;
    std::cout << "  - Close combat with Sword (risky but powerful)" << std::endl;
    std::cout << "  - Enemies move 1 unit per turn towards you" << std::endl;
    std::cout << "  - Enemies attack when within range 1" << std::endl;
    
    waitForEnter();
}


// ========== DISPLAY METHODS ==========

void Game::displayIntro() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                                ║" << std::endl;
    std::cout << "║      CAMPUS QUEST: INTERACTIVE BATTLE          ║" << std::endl;
    std::cout << "║                                                ║" << std::endl;
    if (interactiveMode) {
        std::cout << "║         🎮 PLAYER CONTROLLED MODE 🎮           ║" << std::endl;
    } else {
        std::cout << "║            AUTOMATED MODE                      ║" << std::endl;
    }
    std::cout << "║                                                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n";
    std::cout << "Objective: Defeat all enemies before you fall!" << std::endl;
    std::cout << "Victory: All enemies defeated" << std::endl;
    std::cout << "Defeat: Player health reaches 0" << std::endl;
    std::cout << "Turn Limit: " << MAX_TURNS << " turns" << std::endl;
    std::cout << "\n";
}

void Game::displayTurnHeader() {
    // Use enhanced UI (JOB 11)
    std::stringstream title;
    title << UI::COLOR_BRIGHT_CYAN << "TURN " << currentTurn << " / " << MAX_TURNS << UI::COLOR_RESET;
    UI::drawTitleBox(title.str(), 52);
}

void Game::displayState() {
    // JOB 11: Enhanced UI with Status Dashboard
    
    // Gather info for dashboard
    std::string targetName = "";
    int targetHealth = 0;
    int targetMaxHealth = 0;
    double targetDistance = 0.0;
    
    if (player && player->getTarget() && player->getTarget()->isAlive()) {
        targetName = player->getTarget()->getName();
        targetHealth = player->getTarget()->getHealth();
        targetMaxHealth = 100;  // Approximate
        targetDistance = player->distance(*player->getTarget());
    }
    
    // Display comprehensive status dashboard
    if (player) {
        UI::drawStatusDashboard(
            player->getName(),
            player->getHealth(),
            100,  // Max health (could track this in Player)
            player->getX(),
            player->getY(),
            player->getCurrentWeapon()->getName(),
            player->getCurrentWeapon()->getRange(),
            player->getCurrentWeapon()->getPower(),
            targetName,
            targetHealth,
            targetMaxHealth,
            targetDistance,
            countLivingEnemies(),
            currentTurn,
            MAX_TURNS
        );
    }
    
    // Show all objects (with enhanced display)
    std::cout << "\n";
    UI::drawSectionHeader("ALL OBJECTS", 52);
    manager.drawAll();
}

void Game::displayResult() {
    std::cout << "\n\n";
    std::cout << "╔════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                                ║" << std::endl;
    
    switch (state) {
        case GameState::VICTORY:
            std::cout << "║              🎉 VICTORY! 🎉                    ║" << std::endl;
            std::cout << "║                                                ║" << std::endl;
            std::cout << "║        All enemies have been defeated!         ║" << std::endl;
            break;
            
        case GameState::DEFEAT:
            std::cout << "║              💀 DEFEAT 💀                      ║" << std::endl;
            std::cout << "║                                                ║" << std::endl;
            std::cout << "║          The hero has fallen...                ║" << std::endl;
            break;
            
        case GameState::DRAW:
            std::cout << "║              ⚔️  DRAW ⚔️                       ║" << std::endl;
            std::cout << "║                                                ║" << std::endl;
            std::cout << "║         Turn limit reached - no winner         ║" << std::endl;
            break;
            
        default:
            std::cout << "║              GAME ENDED                        ║" << std::endl;
            break;
    }
    
    std::cout << "║                                                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
    
    displayStats();
}

void Game::displayStats() {
    std::cout << "\n";
    std::cout << "┌─────────────────────────────────────┐" << std::endl;
    std::cout << "│          GAME STATISTICS            │" << std::endl;
    std::cout << "└─────────────────────────────────────┘" << std::endl;
    
    std::cout << "Total turns: " << currentTurn << " / " << MAX_TURNS << std::endl;
    
    if (player) {
        std::cout << "Player final health: " << player->getHealth() << std::endl;
        std::cout << "Player status: " << (player->isAlive() ? "ALIVE" : "DEFEATED") << std::endl;
    }
    
    int livingEnemies = countLivingEnemies();
    std::cout << "Enemies remaining: " << livingEnemies << std::endl;
    
    std::cout << "\nFinal game state:" << std::endl;
    manager.printStats();
    
    std::cout << "\n";
}


// ========== HELPER METHODS ==========

int Game::countLivingEnemies() const {
    int count = 0;
    
    for (size_t i = 0; i < manager.size(); i++) {
        if (const Enemy* enemy = dynamic_cast<const Enemy*>(manager.getObject(i))) {
            if (enemy->isAlive()) {
                count++;
            }
        }
    }
    
    return count;
}

std::string Game::getStateName(GameState state) const {
    switch (state) {
        case GameState::SETUP:   return "SETUP";
        case GameState::PLAYING: return "PLAYING";
        case GameState::VICTORY: return "VICTORY";
        case GameState::DEFEAT:  return "DEFEAT";
        case GameState::DRAW:    return "DRAW";
        default:                 return "UNKNOWN";
    }
}

void Game::waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::clearScreen() {
    // Cross-platform clear (simplified)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
