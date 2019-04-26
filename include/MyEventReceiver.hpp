//
// EPITECH PROJECT, 2018
// MyEventReceiver
// File description:
// Event receiving
//

#include <irrlicht.h>

#pragma once

class MyEventReceiver : public irr::IEventReceiver
{
public:
	virtual bool OnEvent(const irr::SEvent &event)
		{
			if (event.EventType == irr::EET_KEY_INPUT_EVENT)
				_KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			return false;
		}
	virtual bool IsKeyDown(irr::EKEY_CODE keyCode)
		{
			return _KeyIsDown[keyCode];
		}
	MyEventReceiver()
		{
			for(irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; i++)
				_KeyIsDown[i] = false;
		}
private:
	bool _KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};
