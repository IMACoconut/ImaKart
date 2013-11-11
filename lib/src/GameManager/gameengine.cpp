#include "GameManager/gameengine.hpp"
#include "GameManager/gamestate.hpp"
#include <iostream>



static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;

void GameEngine::Init(){
    states.top()->Init();    
    

}


void GameEngine::PopState()
{
    if ( !states.empty() )
    {
        states.top()->Release();
        states.pop();
        std::cout << "Pop" << std::endl;
    }
}

void GameEngine::PushState( GameState& state )
{
    // set current state
    states.push( &state );
    states.top()->Initialize();
}

void GameEngine::SetState( GameState& state )
{ 
    // Delete the actual current state (if any)
    PopState ();
 
    // Add the new state
    PushState( state );
}

void GameEngine::HandleEvents() 
{
    // let the state handle events
    states.top()->HandleEvents(this);
}

void GameEngine::Update() 
{
    // let the state update the game
    states.top()->Update(this);
}

void GameEngine::Draw() 
{
    // let the state draw the screen
    states.top()->Draw(this);
}