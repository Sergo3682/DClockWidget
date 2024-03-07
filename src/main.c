#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <signal.h>

#include "./clock_widget.h"

static volatile int running = 1;
void intHandler(int dummy)
{
	running = 0;
}

int main(int argc, char* argv[])
{
	signal(SIGINT, intHandler);
	int width = 700, height = 100;
	int pos_x = SDL_WINDOWPOS_CENTERED, pos_y =SDL_WINDOWPOS_CENTERED;
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0)
		{
			width = atoi(argv[++i]);
		} else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--height") == 0)
		{
			height = atoi(argv[++i]);
		}  else if (strcmp(argv[i], "-x") == 0 || strcmp(argv[i], "--pos_x") == 0)
		{
			pos_x = atoi(argv[++i]);
		} else if (strcmp(argv[i], "-y") == 0 || strcmp(argv[i], "--pos_y") == 0)
		{
			pos_y = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "--help") == 0)
		{
			print_help();
		} else
		{
			printf("Unlnown flag!\n");
			print_help();
		}
	}
	init_window(width, height, pos_x, pos_y);
	calculate_scale(width, height);
	load_imgs();
	init_digit_places();
	while (running)
	{
		get_time();
		draw_digits();
		SDL_Delay(10);
	}
	printf("\n");
	destroy_window();
	return 0;
}

void print_help()
{
	printf("-x --pos_x: Set window position coordinate X. Expects integer\n"
			"-y --pos_y: Set window position coordinate Y. Expects integer\n"
			"-w --width: Set window width. Expects integer\n"
			"-h --height: Set window height. Expects integer\n"
			"--help Show help\n");
	exit(0);
}

void calculate_scale(int w, int h)
{
	my_scale.margin_ver = h/100;
	my_scale.margin_hor = w/100;
	my_scale.size_y = h - 2*my_scale.margin_ver;
	my_scale.size_x = (w-my_scale.margin_hor*2)/7;
	my_scale.distance = my_scale.margin_hor/2;
}

void get_time(void)
{
	time_t raw_time;
	time(&raw_time);
	tell_the_time = localtime(&raw_time);
}

int init_window(int w, int h, int pos_x, int pos_y)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return 1;
	}
	window = SDL_CreateWindow(
		"Clock Widget",
		pos_x,
		pos_y,
		w,
		h,
		SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS
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
	for (int i = 0; i<11; i++)
	{
		SDL_DestroyTexture(digits[i]);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void load_imgs(void) {
	digits[0] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("src/img/0.bmp"));
	digits[1] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("src/img/1.bmp"));
	digits[2] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("src/img/2.bmp"));
	digits[3] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("src/img/3.bmp"));
	digits[4] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("src/img/4.bmp"));
	digits[5] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("src/img/5.bmp"));
	digits[6] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("src/img/6.bmp"));
	digits[7] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("src/img/7.bmp"));
	digits[8] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("src/img/8.bmp"));
	digits[9] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("src/img/9.bmp"));
	digits[10] = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("src/img/sep.bmp"));
}

void init_digit_places(void)
{
	int margin = my_scale.margin_hor;
	for (int i = 0; i < 8; i++)
    {
		if (i == 2 || i == 5)
			digit_places[i].w = my_scale.size_x/3;
		else
			digit_places[i].w = my_scale.size_x;
		digit_places[i].h = my_scale.size_y;
		digit_places[i].x = margin;
		digit_places[i].y = my_scale.margin_ver;
		margin+=digit_places[i].w+my_scale.distance;
	}
}

void draw_digits(void)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	int digit = tell_the_time->tm_hour/10;
	SDL_RenderCopy(renderer, digits[digit], NULL, &digit_places[0]);

	digit = tell_the_time->tm_hour%10;
	SDL_RenderCopy(renderer, digits[digit], NULL, &digit_places[1]);

	SDL_RenderCopy(renderer, digits[10], NULL, &digit_places[2]);

	digit = tell_the_time->tm_min/10;
	SDL_RenderCopy(renderer, digits[digit], NULL, &digit_places[3]);

	digit = tell_the_time->tm_min%10;
	SDL_RenderCopy(renderer, digits[digit], NULL, &digit_places[4]);

	SDL_RenderCopy(renderer, digits[10], NULL, &digit_places[5]);

	digit = tell_the_time->tm_sec/10;
	SDL_RenderCopy(renderer, digits[digit], NULL, &digit_places[6]);

	digit = tell_the_time->tm_sec%10;
	SDL_RenderCopy(renderer, digits[digit], NULL, &digit_places[7]);

	SDL_RenderPresent(renderer);
}
