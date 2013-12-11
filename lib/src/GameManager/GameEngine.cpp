#include <GameManager/GameEngine.hpp>
#include <GameManager/GameState.hpp>
#include <iostream>



static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;

void GameEngine::PopState()
{

        // cleanup the current state
    if ( !states.empty() ) {
        states.top()->Release(this);
        states.pop();
    }

    // resume previous state
    if ( !states.empty() ) {
        states.top()->Resume(this);
    }
}

void GameEngine::PushState( GameState& state )
{
   /*  // set current state
    states.push( &state );
    states.top()->Initialize(); */

    // pause current state
    if ( !states.empty() ) {
        states.top()->Pause(this);
    }

    // store and init the new state
    states.push(&state);
    states.top()->Init(this);
}

void GameEngine::HandleEvents() 
{
    // let the state handle events
    if(!states.empty())
        states.top()->HandleEvents(this);
}

void GameEngine::Update() 
{
    // let the state update the game
    if(!states.empty())
        states.top()->Update(this);
}

void GameEngine::Draw() 
{
    // let the state draw the screen
    if(!states.empty())
        states.top()->Draw(this);
}

void GameEngine::Quit() {
    while(!states.empty()) {
        states.top()->Release(this);
        states.pop();
    }
}