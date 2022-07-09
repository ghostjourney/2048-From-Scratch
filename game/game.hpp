#pragma once

#include <memory>

#include "window.hpp"
#include "logger.hpp"

namespace Game2048 {
    class Game2048 {
        public:
        Game2048();
        ~Game2048();

        void Init(void);

        void SetWindow(std::unique_ptr<Window> window);

        Window* GetWindow(void);
        
        
        void Terminate();
        
        void SaveState();

        Game2048(const Game2048&)=delete;
        Game2048(const Game2048&&)=delete;
        Game2048& operator=(const Game2048&)=delete;
        Game2048& operator=(const Game2048&&)=delete;
        
        private:
        std::unique_ptr<Window> mWindow;
        std::unique_ptr<Logger> mLogger;
    };
};
