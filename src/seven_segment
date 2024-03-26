#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdint.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int init_window(int, int, int, int);
int destroy_window(void);
int running = 1;


SDL_Rect segments[7];
struct scaler
{
	int smaller_side_size;
	int larger_side_size;
	int margin;
} sc;

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

void draw_digit(int);
void init_segments(void);
void calculate_scale(int, int);

int main(int argc, char* argv[])
{
	int width = 400, height = 780;
	int pos_x = SDL_WINDOWPOS_CENTERED, pos_y =SDL_WINDOWPOS_CENTERED;
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0)
		{
			if(sscanf(argv[++i], "%d", &width));
			else width = 400;
		} else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--height") == 0)
		{
			if(sscanf(argv[++i], "%d", &height));
			else height = 800;
		}
	}
	init_window(width, height, pos_x, pos_y);
	calculate_scale(width, height);
	init_segments();
	int n = 0;
	while (running)
	{
		draw_digit(n);
		if (scanf("%d", &n))
		{
			if (n<0) running = 0;
		}
		else 
		{
			printf("Invalid input!!!\n");
		}
		n = n%10;
	}
	destroy_window();
	return 0;
}

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

void draw_digit(int n)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	for (int i = 0; i<7; i++)
	{
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

int init_window(int w, int h, int pos_x, int pos_y)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return 1;
	}
	window = SDL_CreateWindow(
		"SevenSegment",
		pos_x,
		pos_y,
		w,
		h,
		SDL_WINDOW_SHOWN //| SDL_WINDOW_BORDERLESS
	);
	if (!window)
	{
		fprintf(stderr, "Error initializing window.\n");
		return 1;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error initializing renderer.\n");
		return 1;
	}
	return 0;
}

int destroy_window(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
