//GPT was used for help here early on
#include "GameSystem/GameInit.h"

void GameInit::Init() {
    // Initialize the scene
    scene = Scene::create();
    scene->background = Color::black;

    // Set up the camera bounds
    left = -canvas.aspect() * 5;
    right = canvas.aspect() * 5;
    top = 5;
    bottom = -5;

    // Initialize the camera
    camera = OrthographicCamera::create(left, right, top, bottom, 0.1f, 100);
    camera->position.z = 10;

    // Handle window resizing
    canvas.onWindowResize([&](WindowSize size) {
        left = -size.aspect() * 5;
        right = size.aspect() * 5;
        camera->left = left;
        camera->right = right;
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });
}

Canvas& GameInit::getCanvas() {
    return canvas;
}

GLRenderer& GameInit::getRenderer() {
    return renderer;
}

std::shared_ptr<Scene>& GameInit::getScene() {
    return scene;
}

std::shared_ptr<OrthographicCamera>& GameInit::getCamera() {
    return camera;
}

void GameInit::getBounds(float& outLeft, float& outRight, float& outTop, float& outBottom) {
    outLeft = left;
    outRight = right;
    outTop = top;
    outBottom = bottom;
}
