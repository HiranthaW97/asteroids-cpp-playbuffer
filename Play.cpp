//********************************************************************************************************************************
// Play.cpp
//----------------------------------------------------------------------------------------------------------------------------
// PlayBuffer is a single-header framework: ALL of its code lives in Play.h.
// The declarations are always visible, but the *implementation* (the actual
// function bodies, WinMain, the audio/graphics managers, etc.) is wrapped in
//     #ifdef PLAY_IMPLEMENTATION ... #endif
//
// This one .cpp file is the single place where we switch that implementation
// on, so the framework gets compiled exactly ONCE in the whole program.
// Every other file (MainGame.cpp, Ship.cpp, ...) just #includes "Play.h" and
// sees only the declarations, which prevents duplicate-symbol linker errors.
//
// You should never need to edit this file.
//********************************************************************************************************************************
#define PLAY_IMPLEMENTATION
#include "Play.h"
