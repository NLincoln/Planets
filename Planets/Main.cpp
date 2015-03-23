//
//
//
//
//
#include "Main.hpp"
#include "PlanetManager.hpp"
#include "Logger.h"

#include <iostream>


uint Rand::GetRandomUINT(uint min, uint max)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<uint> uni(min, max);
	return uni(rng);
	
}

void SetPixel(SDL_Surface* Surface, int x, int y, Uint32 pixel)
{
	Uint32* pixels = (Uint32*)Surface->pixels;
	pixels[(y * Surface->w) + x] = pixel;
}

void RenderFrame(SDL_Surface* Surface, GraphManager Graph)
{
	std::vector<GraphData*> Nodes = Graph.GetGraphData();

#define SIZE 1
	for (uint i = 0; i < Nodes.size(); i++)
	{
		SDL_Rect Rect;
		Rect.x = Nodes[i]->GetPosition().x - SIZE;
		Rect.y = Nodes[i]->GetPosition().y - SIZE;
		Rect.h = SIZE * 2;
		Rect.w = SIZE * 2;
		if (SDL_MUSTLOCK(Surface))
			SDL_LockSurface(Surface);
		SDL_FillRect(Surface, &Rect, SDL_MapRGB(Surface->format, 255, 0, 0));
		if (SDL_MUSTLOCK(Surface))
			SDL_UnlockSurface(Surface);
	}
}

int main(int argc, const char** argv)
{
	Logger::ClearLog();
	PlanetManager PlanetManager;
	
	ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0);
	SDL_Window* Window = SDL_CreateWindow("Planets", 10, 10, FIELD_WIDTH, FIELD_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Surface* Surface = SDL_CreateRGBSurface(0, FIELD_WIDTH, FIELD_HEIGHT, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	
	RenderFrame(Surface, PlanetManager.GetGraphData());
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_SetRenderTarget(Renderer, Texture);
	ASSERT(Surface);
	SDL_RenderPresent(Renderer);
	while (true)
	{

	}

	SDL_DestroyTexture(Texture);
	SDL_FreeSurface(Surface);
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	return 0;
}
