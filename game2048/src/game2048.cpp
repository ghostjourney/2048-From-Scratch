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
    std::array<float, 4> clearColor;
    clearColor[0] = 1.0f;
    clearColor[1] = 0.0f;
    clearColor[2] = 0.0f;
    clearColor[3] = 1.0f;
    mWindow->GetRenderer()->SetClearColor(clearColor);
    auto proj = gfs::ProjectionMatrix<float>(0.0f, mWindow->GetWidth(), 0.0f, mWindow->GetHeight(), 0.0f, 100.0f);
    mWindow->GetRenderer()->SetProjection(proj);
    auto view = gfs::CreateIdentity<float, 4>(1.0f);
    mWindow->GetRenderer()->SetView(view);
    mWindow->GetRenderer()->Draw(mWindow.get(), *buffer);
    
    return std::move(buffer);
}


void Game2048::Game2048::Terminate() {
    
}

void Game2048::Game2048::SaveState() {
    
}
