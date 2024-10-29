//
// Created by borga on 10/29/2024.
//

#ifndef KEYLISTENER_H
#define KEYLISTENER_H
#include <iostream>
#include "threepp/threepp.hpp"

class InputListener: public KeyListener, public MouseListener {

    public:

    explicit InputListener(Scene& scene): scene(scene){}


    void onMouseDown(int key, const Vector2 & pos) override {

        if (key == 0) {
            std::cout << "Mousepressed" << std::endl;
            handleMousePress();
        }

    }

private:
    Scene& scene;
    Mesh* myAddedMesh = nullptr;
    bool addedPlayer = false;

    void handleMousePress() {
        if (!addedPlayer) {
            auto mesh = createPlayer();
            myAddedMesh = mesh.get();
            scene.add(mesh);
            addedPlayer = true;
        }
    }

    std::shared_ptr<Mesh> createPlayer() {
        auto geometry = ::CylinderGeometry::create(0.05,0.2,0.5);
        auto material = MeshBasicMaterial::create();
        material->color = Color::white;
        auto mesh = Mesh::create(geometry, material);
        return mesh;
    }

};

#endif //KEYLISTENER_H
