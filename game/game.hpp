#pragma once

#include <memory>

#include "window.hpp"
#include "logger.hpp"

namespace Game2048 {

    /**
     * Game2048 Program Object
     *
     * The object will be created, initialized, and used
     * by platform code to run the game.
     *
     */
    class Game2048 {
        public:
        Game2048();
        ~Game2048();

        Game2048(const Game2048&)=delete;
        Game2048(const Game2048&&)=delete;
        Game2048& operator=(const Game2048&)=delete;
        Game2048& operator=(const Game2048&&)=delete;

        /**
         * Initilize the Game with game code
         */
        void Init(void);

        /**
         * Set the associated window for this class. This will be platform specific
         *
         * \param window platform specific version of window
         */
        void SetWindow(std::unique_ptr<Window> window);
       
        /**
         * retrieves the associated window
         *
         * \returns pointer to window. Does not transfer ownership
         */
        Window* GetWindow(void);
       
        /**
         * called to immediately terminate the game
         */
        void Terminate();
       
        /**
         * save the game state to nonvolatile location
         */
        void SaveState();
       
        /**
         * draw game frame
         */
        void Draw(void);

        /**
         * Get program wide logger
         *
         * \returns pointer to logger. Does not transfer ownership
         */
        Logger* GetLogger()
        
        private:
        /// platform specific window
        std::unique_ptr<Window> mWindow;

        /// general logger
        std::unique_ptr<Logger> mLogger;
    };
};
