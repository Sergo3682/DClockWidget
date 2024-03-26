#ifndef CLOCK_WIDGET_HEADER
#define CLOCK_WIDGET_HEADER
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *digits[11];
SDL_Rect digit_places[8];
struct tm *tell_the_time;


typedef struct 
{
	int margin_ver;
	int margin_hor;
	int distance;
	int size_x;
	int size_y;
} scale;

scale my_scale;

void print_help(void);
int init_window(int, int, int, int);
int destroy_window(void);
void get_time(void);
void load_imgs(char *);
void draw_digits(void);
void init_digit_places(void);
void render(void);
void calculate_clock_scale(int, int);
void create_digits(SDL_Color, SDL_Color);

#endif /* CLOCK_WIDGET_HEADER */
