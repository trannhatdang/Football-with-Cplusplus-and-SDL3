#include "engine/Animation.h"

Animation::Animation(SDL_Renderer* renderer, const std::string& filepath, int width, int height, int num_frames, int scale) : m_width(width), m_height(height), m_num_frames(num_frames), m_scale(scale), m_filepath(filepath)
{
	m_texture = CreateTextureFromPNG(renderer, filepath);
}

Animation::~Animation()
{
	SDL_DestroyTexture(m_texture);
}

void Animation::OnDraw(SDL_Renderer* renderer, SDL_Rect viewport)
{
	SDL_FRect srcrect;
	srcrect.x = m_num_frames * m_width;
	srcrect.y = 0;
	srcrect.w = m_width;
	srcrect.h = m_height;

	SDL_FRect dstrect;
	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = m_width * m_scale;
	dstrect.h = m_height * m_scale;

	DrawTexture(renderer, m_texture, viewport, srcrect, dstrect);
}

std::string Animation::GetFilepath() const
{
	return m_filepath;
}

int Animation::GetCurrFrame() const
{
	return m_curr_frame;
}

int Animation::GetWidth() const
{
	return m_width;
}

int Animation::GetHeight() const
{
	return m_height;
}

int Animation::GetNumFrames() const
{
	return m_num_frames;
}

int Animation::GetScale() const
{
	return m_scale;
};
