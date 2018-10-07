#pragma once

#include "GameState.h"
#include "MenuState.h"
#include "AboutState.h"

void changeState(std::unique_ptr<BaseState> &state_obj);