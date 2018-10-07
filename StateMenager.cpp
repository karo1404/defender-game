#include "StateMenager.h"


void changeState(std::unique_ptr<BaseState> &state_obj)
{
	if (state_obj->getNextState() != STATE_EMPTY)
	{
		switch (state_obj->getNextState())
		{
		case STATE_QUIT:
			state_obj.reset();
			return;

		case STATE_MENU:
			state_obj.reset(new MenuState(state_obj->main_window, state_obj->main_renderer, state_obj->frame_counter, state_obj->e));
			break;

		case STATE_GAME:
			state_obj.reset(new GameState(state_obj->main_window, state_obj->main_renderer, state_obj->frame_counter, state_obj->e));
			break;

		case STATE_ABOUT:
			state_obj.reset(new AboutState(state_obj->main_window, state_obj->main_renderer, state_obj->frame_counter, state_obj->e));
		}
		state_obj->setNextState(STATE_EMPTY);
	}
}