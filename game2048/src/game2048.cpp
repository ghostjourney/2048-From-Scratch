#include "game2048/game2048.hpp"

#include <memory>

#include "gfs/buffer.hpp"

#include "gfs/console_logger.hpp"

Game2048::Game2048::Game2048() : mLogger{std::make_unique<gfs::ConsoleLogger>()}{
};

Game2048::Game2048::~Game2048() {}

void Game2048::Game2048::SetWindow(std::unique_ptr<gfs::Window> window) {
    mWindow = std::move(window);
}

gfs::Window* Game2048::Game2048::GetWindow(void) {
    return mWindow.get();
}

void Game2048::Game2048::Init(void) {
    mWindow->SetTitle("Hello World");
    mWindow->SetHeightWidth(600.0, 800.0);

    mTile = std::unique_ptr<Tile>();
}


std::unique_ptr<std::vector<gfs::Vertex2D>> Game2048::Game2048::Draw(void) {
    auto buffer = std::make_unique<std::vector<gfs::Vertex2D>>();
    mTile->Draw(*buffer.get());
    return std::move(buffer);
}


void Game2048::Game2048::Terminate() {
    
}

void Game2048::Game2048::SaveState() {
    
}
