#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "dg_engine_std.h"

class Animation
{
	private:
		SDL_Texture* m_texture;
		std::string m_filepath;
		int m_curr_frame = 0;
		int m_width;
		int m_height;
		int m_num_frames;
		int m_scale;
	public:
		Animation(SDL_Renderer* renderer, const std::string& filepath, int width, int height, int num_frames, int scale);
		~Animation();
		void OnDraw(SDL_Renderer* renderer, SDL_Rect viewport);

		std::string GetFilepath() const;
		int GetCurrFrame() const;
		int GetWidth() const;
		int GetHeight() const;
		int GetNumFrames() const;
		int GetScale() const;
};

#endif
