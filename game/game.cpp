#include "game.hpp"

#include <memory>

#include "console_logger.hpp"

Game2048::Game2048::Game2048() : mLogger{std::make_unique<ConsoleLogger>()}{
};

Game2048::Game2048::~Game2048() {}

void Game2048::Game2048::SetWindow(std::unique_ptr<Window> window) {
    mWindow = std::move(window);
}

Window* Game2048::Game2048::GetWindow(void) {
    return mWindow.get();
}

void Game2048::Game2048::Draw(void) {
    
}

void Game2048::Game2048::Init(void) {
    mWindow->SetTitle("Hello World");
    mWindow->SetHeightWidth(1280.0, 720.0);
}

void Game2048::Game2048::Terminate() {
    
}

void Game2048::Game2048::SaveState() {
    
}
