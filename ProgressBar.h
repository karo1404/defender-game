#pragma once
#include "AnimatedTexture.h"

//Class responsible for creating progress bars 
class ProgressBar
{
	AnimatedTexture* texture;
	Uint16 present_value = 0;
	Uint16 max_value;
	int max_texture_width;

public:

	ProgressBar() = delete;
	ProgressBar(AnimatedTexture* image, int max_val);
	ProgressBar(ProgressBar& object);
	~ProgressBar();

	inline void setValue(Uint16 value) { present_value = value; };
	inline void setMaxValue(Uint16 value) { max_value = value; };
	inline Uint16 getValue() { return present_value; };
	inline Uint16 getMaxValue() { return max_value; };
	inline int getMaxWidth() { return max_texture_width; };

	//render without new present value at x,y coords
	void render(int x, int y);

	//render with new present value at x,y coords
	void render(int x, int y, Uint16 value);

	//sets hue & saturation of the bar
	inline void setColor(Uint8 r, Uint8 g, Uint8 b) { texture->setColor(r, g, b); };

	//sets opacity (alpha channel) of the bar
	inline void setOpacity(Uint8 alpha) { texture->setOpacity(alpha); };

};