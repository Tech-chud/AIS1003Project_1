//GPT was used for help here early on

#ifndef GAMEINIT_HPP
#define GAMEINIT_HPP

#include "threepp/threepp.hpp"
#include <memory>

using namespace threepp;

class GameInit {
public:
    static void Init(); // Initializes everything

    // Getters for accessing the initialized components
    static Canvas& getCanvas();
    static GLRenderer& getRenderer();
    static std::shared_ptr<Scene>& getScene();
    static std::shared_ptr<OrthographicCamera>& getCamera();
    static void getBounds(float& left, float& right, float& top, float& bottom);

private:
    static inline Canvas canvas{"2D Asteroids"};
    static inline GLRenderer renderer{canvas.size()};
    static inline std::shared_ptr<Scene> scene;
    static inline std::shared_ptr<OrthographicCamera> camera;
    static inline float left, right, top, bottom;
};

#endif // GAMEINIT_HPP
