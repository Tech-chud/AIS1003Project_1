#include "GameSystem/GameHUD.h"
#include "threepp/loaders/FontLoader.hpp"
#include <iostream>

GameHUD::GameHUD(const threepp::WindowSize& size) : hud_(size) {
    try {
        // Load the default font
        threepp::FontLoader fontLoader;
        const auto font = fontLoader.defaultFont();


        // Create TextGeometry options
        threepp::TextGeometry::Options opts(font, 10, 5); // Larger font size for testing

        // Test text
        scoreText_ = std::make_shared<threepp::Text2D>(opts, "Test HUD");
        scoreText_->setColor(threepp::Color::red);
        hud_.add(*scoreText_, threepp::HUD::Options()
                                  .setNormalizedPosition({0.5f, 0.5f}) // Center the text
                                  .setVerticalAlignment(threepp::HUD::VerticalAlignment::CENTER)
                                  .setHorizontalAlignment(threepp::HUD::HorizontalAlignment::CENTER));

        std::cout << "HUD initialized successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception initializing HUD: " << e.what() << std::endl;
    }
}


void GameHUD::render(threepp::GLRenderer& renderer) {
    try {
        renderer.autoClear = false; // Prevent HUD from clearing the render target
        hud_.apply(renderer);      // Render the HUD on top of the scene
        renderer.autoClear = true; // Reset autoClear for future renders
    } catch (const std::exception& e) {
        std::cerr << "Exception while rendering HUD: " << e.what() << std::endl; // TEMP TEST COUSE PROBLEMS :DDDDDDDDDDDDDDDDD
    }
}

