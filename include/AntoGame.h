#ifndef __PacMan__H__
#define __PacMan__H__


#define WINDOW_TITLE "AntoGame v1.0"
#define WINDOW_WIDTH  512
#define WINDOW_HEIGTH 600
#define ANTO_FRAMES 12
#define ANTO_WIDTH 18
#define ANTO_HEIGTH 24
#define GROUND_WIDTH 32
#define GROUND_HEIGTH 32
#define HOR_BARIER_WIDTH 72
#define HOR_BARIER_HEIGTH 25
#define VER_BARIER_WIDTH 8        
#define VER_BARIER_U_HEIGTH 29       
#define VER_BARIER_M_HEIGTH 32       
#define VER_BARIER_L_HEIGTH 26
#define PARAMETRE_COLLISION_UPPER_BARIER 18
#define PARAMETRE_COLLISION_LEFT_BARIER 4
#define PARAMETRE_COLLISION_RIGHT_BARIER 2
#define PARAMETRE_COLLISION_LOWER_BARIER 20
#define WOODS3_WIDTH 22 
#define WOODS3_HEIGTH 30
#define WOODS9_WIDTH 30
#define WOODS9_HEIGTH 32
#define WOODS3_NUM 5
#define WOODS9_NUM 4
#define BARREL_NUM 15
#define BARREL_WIDTH 28
#define BARREL_HEIGTH 38
#define FRUIT_NUM 11
#define MONS_WIDTH 40
#define MONS_HEIGTH 47.49140893
#define MONS_NUM 7





/*Structs:*/

typedef struct
{
	float x,y;
	SDL_Texture *frames[ANTO_FRAMES];
	int facing; // 1: front 2:left 3:back 4:right
	int moving;
	Mix_Chunk *eat_SE, *dead_SE, *mons_SE, *won_SE;
	int Is_dead;
	float speed;
	Mix_Music *music;

	int won_test;
}Anto;

typedef struct 
{
	int x,y;
	SDL_Texture *ground_texture;
	SDL_Texture *hor_barier_texture;
	SDL_Texture *ver_barier_m_texture, *ver_barier_l_texture, *ver_barier_u_texture; //u: upper, m: middle, l:lower
	SDL_Texture *woods3_texture, *woods9_texture;
	int woods3_x, woods9_x, woods3_y, woods9_y;
	SDL_Texture *barrel_texture[BARREL_NUM];
	int barrel_x[BARREL_NUM],barrel_y[BARREL_NUM];
	SDL_Texture *fruit_texture[FRUIT_NUM];
	int fruit_x[FRUIT_NUM], fruit_y[FRUIT_NUM];
	int fruit_eaten[FRUIT_NUM];
	int eaten_num;
	int fruit_w[FRUIT_NUM], fruit_h[FRUIT_NUM];
	SDL_Texture *mons_texture[7];
	int mons_x[MONS_NUM],mons_y[MONS_NUM];
	int mons_facing_left;
	int timer2,timer3,timer4;
	TTF_Font *font;
	SDL_Color white;
	SDL_Texture *game_over_texture, *you_won_texture;
	SDL_Texture *score_texture;
	int score_number;
	SDL_Surface *Tmp_surface;
	SDL_Texture *m_mute;


}Ground;


/*Functions prototype (in order of use):*/

void Initialize_states(Anto *anto, Ground *ground);

void Load_ground_stuff(Ground *ground, SDL_Surface *surface, SDL_Renderer *renderer);

void Load_anto_Stuff(Anto *anto,SDL_Surface *surface, SDL_Renderer *renderer);


void RendererSpecifications(SDL_Renderer *renderer);

int Non_Mvt_Events(Anto *anto, SDL_Event event);

void Mvt_Events(Anto *anto, Ground *ground);

void Collision_detection(Anto *anto, Ground *ground);

void Eat(Anto *anto, Ground *ground);

void Collision_mons(Anto *anto, Ground *ground);

void Draw_ground(Ground *ground, SDL_Renderer *renderer, int *timer1);

void Draw_anto(Anto *anto, SDL_Renderer *renderer, int *timer);

void Draw_above_anto(Ground *ground, SDL_Renderer *renderer);

int Game_Over(Anto *anto, Ground *ground, SDL_Renderer *renderer);

void Destroy_Everything(Anto *anto,Ground *ground , SDL_Window *window, SDL_Renderer *renderer);

#endif