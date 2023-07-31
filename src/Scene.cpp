#include <iostream>
#include <algorithm>

#include "../include/Scene.hpp"

uint32_t Scene::nextID = 0;

const std::vector<std::unique_ptr<Object>>& Scene::getObjects() const {
    return _objects;
}


void Scene::add( std::unique_ptr<Object> o ) 
{  
    _objects.push_back(std::move(o));
}

bool Scene::remove( const uint64_t& ID )
{
    auto it = std::find_if(_objects.begin(), _objects.end(), [&](const std::unique_ptr<Object>& o){ return o->getID() == ID; });

    if( it != _objects.end() ){
        //std::cout << "DELETED\n";
        _objects.erase( it );
        return true;
    }
    std::cout<<"Couldn't remove the box, NOT FOUND!\n";
    return false;
}

void Scene::update( const float &dt ) 
{
    for ( const std::unique_ptr<Object>& o : _objects ) 
    {
        o->update( dt );
    }
    checkCollisions();
    TOTAL_TIME += dt;
}

Object* Scene::getObject( uint64_t ID )
{
    // FIX !!!
    auto it = std::find_if(_objects.begin(), _objects.end(), [&](const std::unique_ptr<Object>& o){ return o->getID() == ID; });
    return it->get();
}

void Scene::checkCollisions() 
{
   
    for (int i = 0; i < _objects.size(); i++) {
        
        for (int j = i + 1; j < _objects.size(); j++) {
            
            if (_objects[i]->isColliding(_objects[j])) {
                _objects[i]->handleCollision(_objects[j]);
                
            }

        }

    }
}

void Scene::listAll(){

    std::cout << "\nTOTAL OBJECTS : " << _objects.size() << "\n";

    for( const std::unique_ptr<Object>& o : _objects ){

        std::cout << "Object " << o->getID() 
        << " Position : " << o->getPosition() 
        << " Velocity : " << o->getVelocity() 
        << "\n";

    }
}

void Scene::printObject(Object* o){
    std::cout << "Object ID : " << o->getID() 
    << " Position = (" << o->getPosition() 
    << ") Mass = " << o->getMass()
    << " Velocity = (" << o->getVelocity() 
    << ") -[ " << "Total time = " << TOTAL_TIME 
    << " ]-" << std::flush ;
}


// NOT WORKING - PROBABLY getObject 
void Scene::printObject(uint64_t ID){
    Object* o = getObject(ID);
    std::cout << "Object ID : " << o->getID() 
    << " Position = (" << o->getPosition() 
    << ") Mass = " << o->getMass()
    << " Velocity = (" << o->getVelocity() 
    << ") -[ " << "Total time = " << TOTAL_TIME  
    << " ]-" << std::flush ;


}

int Scene::objectCount(){
    return _objects.size();
}
