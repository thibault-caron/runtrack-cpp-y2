#include "UIHelper.hpp"
#include <sstream>
#include <iomanip>

namespace UI {

// ========== HEALTH BAR FUNCTIONS ==========

/**
 * Get health bar as string
 * 
 * Creates a visual health bar with optional color coding:
 * - Green: > 60% health
 * - Yellow: 30-60% health
 * - Red: < 30% health
 */
std::string getHealthBar(int current, int max, int barWidth, bool useColor) {
    std::stringstream ss;
    
    // Calculate percentage and bar fill
    if (max <= 0) max = 1;  // Prevent division by zero
    if (current < 0) current = 0;
    if (current > max) current = max;
    
    double percentage = static_cast<double>(current) / max;
    int filled = static_cast<int>(percentage * barWidth);
    
    // Add color if requested
    if (useColor) {
        ss << getHealthColor(current, max);
    }
    
    // Draw the bar
    ss << "[";
    for (int i = 0; i < barWidth; i++) {
        if (i < filled) {
            ss << "\u2588";  // Filled block (█)
        } else {
            ss << "\u2591";  // Light shade (░)
        }
    }
    ss << "] " << current << "/" << max << " HP";
    
    // Reset color
    if (useColor) {
        ss << COLOR_RESET;
    }
    
    return ss.str();
}

void drawHealthBar(int current, int max, int barWidth, bool useColor) {
    std::cout << getHealthBar(current, max, barWidth, useColor);
}

/**
 * Get health color based on percentage
 * 
 * Health-based color coding:
 * - High health (>60%) = Green (healthy)
 * - Medium health (30-60%) = Yellow (wounded)
 * - Low health (<30%) = Red (critical)
 */
std::string getHealthColor(int current, int max) {
    if (max <= 0) return COLOR_WHITE;
    
    double percentage = static_cast<double>(current) / max;
    
    if (percentage > 0.6) {
        return COLOR_BRIGHT_GREEN;  // Healthy
    } else if (percentage > 0.3) {
        return COLOR_BRIGHT_YELLOW;  // Wounded
    } else {
        return COLOR_BRIGHT_RED;  // Critical
    }
}


// ========== BOX DRAWING ==========

/**
 * Draw a title box with double-line borders
 * 
 * Uses box-drawing characters for professional appearance:
 * ╔ ═ ╗ (top)
 * ║   ║ (sides)
 * ╚ ═ ╝ (bottom)
 */
void drawTitleBox(const std::string& title, int width) {
    // Top border (╔═══╗)
    std::cout << "\u2554";  // ╔
    for (int i = 0; i < width - 2; i++) {
        std::cout << "\u2550";  // ═
    }
    std::cout << "\u2557" << std::endl;  // ╗
    
    // Title (centered)
    std::cout << "\u2551" << centerText(title, width - 2) << "\u2551" << std::endl;  // ║
    
    // Bottom border (╚═══╝)
    std::cout << "\u255A";  // ╚
    for (int i = 0; i < width - 2; i++) {
        std::cout << "\u2550";  // ═
    }
    std::cout << "\u255D" << std::endl;  // ╝
}

/**
 * Draw a section header with single-line borders
 * 
 * Uses lighter box-drawing characters:
 * ┌ ─ ┐ (top)
 * │   │ (sides)
 * └ ─ ┘ (bottom)
 */
void drawSectionHeader(const std::string& title, int width) {
    // Top border (┌───┐)
    std::cout << "\u250C";  // ┌
    for (int i = 0; i < width - 2; i++) {
        std::cout << "\u2500";  // ─
    }
    std::cout << "\u2510" << std::endl;  // ┐
    
    // Title (centered)
    std::cout << "\u2502" << centerText(title, width - 2) << "\u2502" << std::endl;  // │
    
    // Bottom border (└───┘)
    std::cout << "\u2514";  // └
    for (int i = 0; i < width - 2; i++) {
        std::cout << "\u2500";  // ─
    }
    std::cout << "\u2518" << std::endl;  // ┘
}

void drawSeparator(int width, char style) {
    for (int i = 0; i < width; i++) {
        std::cout << style;
    }
    std::cout << std::endl;
}


// ========== STATUS DISPLAY ==========

/**
 * Draw comprehensive status dashboard
 * 
 * This is like a HUD (Heads-Up Display) for your text game!
 * Shows all critical information in one organized view.
 */
void drawStatusDashboard(
    const std::string& playerName,
    int playerHealth,
    int playerMaxHealth,
    double playerX,
    double playerY,
    const std::string& weaponName,
    int weaponRange,
    int weaponPower,
    const std::string& targetName,
    int targetHealth,
    int targetMaxHealth,
    double targetDistance,
    int enemyCount,
    int currentTurn,
    int maxTurns
) {
    std::cout << "\n";
    std::cout << "\u2554";  // ╔
    for (int i = 0; i < 50; i++) std::cout << "\u2550";  // ═
    std::cout << "\u2557" << std::endl;  // ╗
    
    std::cout << "\u2551" << "                " << COLOR_BRIGHT_CYAN << "STATUS DASHBOARD" << COLOR_RESET 
              << "                    " << "\u2551" << std::endl;  // ║
    
    std::cout << "\u2560";  // ╠
    for (int i = 0; i < 50; i++) std::cout << "\u2550";  // ═
    std::cout << "\u2563" << std::endl;  // ╣
    
    // Turn info
    std::cout << "\u2551 " << STYLE_BOLD << "Turn:" << COLOR_RESET << " " << currentTurn << "/" << maxTurns;
    int padding = 39 - std::to_string(currentTurn).length() - std::to_string(maxTurns).length();
    for (int i = 0; i < padding; i++) std::cout << " ";
    std::cout << "\u2551" << std::endl;  // ║
    
    std::cout << "\u255F";  // ╟
    for (int i = 0; i < 50; i++) std::cout << "\u2500";  // ─
    std::cout << "\u2562" << std::endl;  // ╢
    
    // Player info
    std::cout << "\u2551 " << COLOR_BRIGHT_GREEN << "⚔️  " << playerName << COLOR_RESET;
    for (size_t i = playerName.length(); i < 35; i++) std::cout << " ";
    std::cout << "\u2551" << std::endl;  // ║
    
    std::cout << "\u2551   Position: (" << std::fixed << std::setprecision(1) 
              << playerX << ", " << playerY << ")";
    std::ostringstream pos;
    pos << std::fixed << std::setprecision(1) << playerX << ", " << playerY;
    padding = 30 - pos.str().length();
    for (int i = 0; i < padding; i++) std::cout << " ";
    std::cout << "\u2551" << std::endl;  // ║
    
    std::cout << "\u2551   Health: ";
    std::cout << getHealthBar(playerHealth, playerMaxHealth, 15, true);
    std::cout << "  \u2551" << std::endl;  // ║
    
    std::cout << "\u2551   Weapon: " << COLOR_YELLOW << weaponName << COLOR_RESET 
              << " (Range:" << weaponRange << ", Power:" << weaponPower << ")";
    padding = 15 - weaponName.length();
    for (int i = 0; i < padding; i++) std::cout << " ";
    std::cout << "\u2551" << std::endl;  // ║
    
    std::cout << "\u255F";  // ╟
    for (int i = 0; i < 50; i++) std::cout << "\u2500";  // ─
    std::cout << "\u2562" << std::endl;  // ╢
    
    // Target info
    if (!targetName.empty()) {
        std::cout << "\u2551 " << COLOR_BRIGHT_RED << "🎯 Target: " << targetName << COLOR_RESET;
        padding = 36 - targetName.length();
        for (int i = 0; i < padding; i++) std::cout << " ";
        std::cout << "\u2551" << std::endl;  // ║
        
        std::cout << "\u2551   Distance: " << std::fixed << std::setprecision(2) 
                  << targetDistance << " units";
        std::ostringstream dist;
        dist << std::fixed << std::setprecision(2) << targetDistance;
        padding = 31 - dist.str().length();
        for (int i = 0; i < padding; i++) std::cout << " ";
        std::cout << "\u2551" << std::endl;  // ║
        
        std::cout << "\u2551   Health: ";
        std::cout << getHealthBar(targetHealth, targetMaxHealth, 15, true);
        std::cout << "  \u2551" << std::endl;  // ║
    } else {
        std::cout << "\u2551 " << COLOR_BRIGHT_RED << "🎯 Target: None" << COLOR_RESET;
        for (int i = 0; i < 34; i++) std::cout << " ";
        std::cout << "\u2551" << std::endl;  // ║
    }
    
    std::cout << "\u255F";  // ╟
    for (int i = 0; i < 50; i++) std::cout << "\u2500";  // ─
    std::cout << "\u2562" << std::endl;  // ╢
    
    // Enemy count
    std::cout << "\u2551 " << COLOR_BRIGHT_RED << "☠️  Enemies Remaining: " << enemyCount << COLOR_RESET;
    padding = 26 - std::to_string(enemyCount).length();
    for (int i = 0; i < padding; i++) std::cout << " ";
    std::cout << "\u2551" << std::endl;  // ║
    
    std::cout << "\u255A";  // ╚
    for (int i = 0; i < 50; i++) std::cout << "\u2550";  // ═
    std::cout << "\u255D" << std::endl;  // ╝
}


// ========== UTILITY FUNCTIONS ==========

/**
 * Center text within a given width
 * Pads with spaces on both sides
 */
std::string centerText(const std::string& text, int width) {
    int padding = width - text.length();
    if (padding <= 0) return text;
    
    int leftPad = padding / 2;
    int rightPad = padding - leftPad;
    
    std::string result;
    for (int i = 0; i < leftPad; i++) result += " ";
    result += text;
    for (int i = 0; i < rightPad; i++) result += " ";
    
    return result;
}

/**
 * Wrap text with color and auto-reset
 */
std::string colorText(const std::string& text, const std::string& color) {
    return color + text + COLOR_RESET;
}

/**
 * Generic progress bar
 * Flexible for any progress indication
 */
std::string getProgressBar(int current, int max, int width, char fillChar, char emptyChar) {
    std::stringstream ss;
    
    if (max <= 0) max = 1;
    if (current < 0) current = 0;
    if (current > max) current = max;
    
    double percentage = static_cast<double>(current) / max;
    int filled = static_cast<int>(percentage * width);
    
    ss << "[";
    for (int i = 0; i < width; i++) {
        if (i < filled) {
            ss << fillChar;
        } else {
            ss << emptyChar;
        }
    }
    ss << "]";
    
    return ss.str();
}

} // namespace UI

