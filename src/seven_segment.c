#include "./seven_segment.h"

const uint8_t states[10] = 
{
	0x77,//0
	0x24,//1
	0x5d,//2
	0x6d,//3
	0x2e,//4
	0x6b,//5
	0x7b,//6
	0x25,//7
	0x7f,//8
	0x6f//9
};

SDL_Rect segments[7];
struct scaler
{
	int smaller_side_size;
	int larger_side_size;
	int margin;
} sc;

void calculate_scale(int w, int h)
{
	if (h > 2*w)
	{
		sc.smaller_side_size = w/10;
		sc.margin = sc.smaller_side_size/5;
		sc.larger_side_size = w - 2*sc.smaller_side_size - 2*sc.margin;
	} else
	{
		sc.smaller_side_size = h/20;
		sc.margin = sc.smaller_side_size/5;
		sc.larger_side_size = (h - 3*sc.smaller_side_size - 4*sc.margin)/2;
	}
}

void draw_digit(SDL_Renderer *renderer, int n, SDL_Color c)
{
	for (int i = 0; i<7; i++)
	{
		if((states[n]>>i) & 1)
			SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
		else
			SDL_SetRenderDrawColor(renderer, 64, 64, 64, 128);
		SDL_RenderFillRect(renderer, &segments[i]);
	}
}

void draw_separator(SDL_Renderer *renderer, int x, int y)
{
	SDL_Rect dot;
	dot.w = sc.smaller_side_size*2;
	dot.x = x;
	dot.h = sc.smaller_side_size*2;
	dot.y = y + 2*dot.h;
	SDL_RenderFillRect(renderer, &dot);
	dot.y = 2*sc.larger_side_size + 4*sc.margin - 2*dot.h;
	SDL_RenderFillRect(renderer, &dot);
}

void init_segments(int x_offset, int y_offset)
{
	for (int i = 0; i<7; i++)
	{
		if(i%3 == 0) 
		{
			segments[i].w = sc.larger_side_size; 
			segments[i].h = sc.smaller_side_size;
		}
		else 
		{
			segments[i].h = sc.larger_side_size; 
			segments[i].w = sc.smaller_side_size;
		}
	}
	segments[0].x = x_offset + sc.smaller_side_size + sc.margin;
	segments[0].y = y_offset;
	
	segments[1].x = x_offset;
	segments[1].y = y_offset + sc.smaller_side_size + sc.margin;
	
	segments[2].x = x_offset + sc.larger_side_size + sc.smaller_side_size + 2*sc.margin;
	segments[2].y = y_offset + sc.smaller_side_size + sc.margin;
	
	segments[3].x = x_offset + sc.smaller_side_size + sc.margin;
	segments[3].y = y_offset + sc.larger_side_size + sc.smaller_side_size + 2*sc.margin;
	
	segments[4].x = x_offset;
	segments[4].y = y_offset + sc.larger_side_size + 2*(sc.smaller_side_size + sc.margin);
	
	segments[5].x = x_offset + sc.larger_side_size + sc.smaller_side_size + 2*sc.margin;;
	segments[5].y = y_offset + sc.larger_side_size + 2*(sc.smaller_side_size + sc.margin);
	
	segments[6].x = x_offset + sc.smaller_side_size + sc.margin;
	segments[6].y = y_offset + 2*sc.larger_side_size + 2*sc.smaller_side_size + 4*sc.margin;
}
