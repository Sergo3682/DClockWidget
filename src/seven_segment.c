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

void draw_digit(SDL_Renderer *renderer, int n)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	for (int i = 0; i<7; i++)
	{
		
	printf("HIIIIIII\n");
		if((states[n]>>i) & 1)
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		else
			SDL_SetRenderDrawColor(renderer, 64, 64, 64, 128);
		SDL_RenderFillRect(renderer, &segments[i]);
	}
	SDL_RenderPresent(renderer);
}

void init_segments(void)
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
	segments[0].x = sc.smaller_side_size + sc.margin;
	segments[0].y = 0;
	
	segments[1].x = 0;
	segments[1].y = sc.smaller_side_size + sc.margin;
	
	segments[2].x = sc.larger_side_size + sc.smaller_side_size + 2*sc.margin;
	segments[2].y = sc.smaller_side_size + sc.margin;
	
	segments[3].x = sc.smaller_side_size + sc.margin;
	segments[3].y = sc.larger_side_size + sc.smaller_side_size + 2*sc.margin;
	
	segments[4].x = 0;
	segments[4].y = sc.larger_side_size + 2*(sc.smaller_side_size + sc.margin);
	
	segments[5].x = sc.larger_side_size + sc.smaller_side_size + 2*sc.margin;;
	segments[5].y = sc.larger_side_size + 2*(sc.smaller_side_size + sc.margin);
	
	segments[6].x = sc.smaller_side_size + sc.margin;
	segments[6].y = 2*sc.larger_side_size + 2*sc.smaller_side_size + 4*sc.margin;
}
