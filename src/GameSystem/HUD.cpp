#include "GameSystem/HUD.h"

HUD::HUD(const std::shared_ptr<threepp::Canvas>& canvas)
    : canvas_(canvas), score_(0), health_(100), timeAlive_(0.0f) {

    auto font = threepp::Font::load("path/to/font.json"); // Load a font (you'll need to replace with an actual path)
    auto textMaterial = threepp::MeshBasicMaterial::create({{"color", threepp::Color::white}});

    // Create text objects for score, health, and time
    scoreText_ = threepp::Text::create("Score: 0", font, textMaterial);
    healthText_ = threepp::Text::create("Health: 100", font, textMaterial);
    timeText_ = threepp::Text::create("Time Alive: 0.0s", font, textMaterial);

    // Positioning the text elements
    scoreText_->position.set(-4.0f, 4.0f, 0.0f);
    healthText_->position.set(-4.0f, 3.5f, 0.0f);
    timeText_->position.set(-4.0f, 3.0f, 0.0f);

    // Add the text objects to the canvas
    canvas_->add(scoreText_);
    canvas_->add(healthText_);
    canvas_->add(timeText_);
}

void HUD::updateScore(int score) {
    score_ = score;
    updateTextElements();
}

void HUD::updateHealth(int health) {
    health_ = health;
    updateTextElements();
}

void HUD::updateTime(float timeAlive) {
    timeAlive_ = timeAlive;
    updateTextElements();
}

void HUD::updateTextElements() {
    scoreText_->setText("Score: " + std::to_string(score_));
    healthText_->setText("Health: " + std::to_string(health_));
    timeText_->setText("Time Alive: " + std::to_string(timeAlive_) + "s");
}

void HUD::render() {
    // In case you need specific render logic
}
