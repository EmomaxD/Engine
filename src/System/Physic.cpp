#include "Physic.hpp"

#include "../Core/Engine.hpp"

#include <iostream>

namespace System{

    Physic::Physic(){
        m_scene = Engine::getActiveScene();
        m_gravity = gravityConstant;
    }

    void Physic::Update(){
        std::cout << "Physic system updating\n";
        /// enTT view function and get all RB, TRANSFORM, COLLIDER
    }

}