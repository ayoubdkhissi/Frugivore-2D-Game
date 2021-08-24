#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "AntoGame.h"


/*Global variables :*/
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;	
SDL_Surface *surface = NULL;


int main(int argc, char const *argv[])
{
	int mode = 0;
  	//argument checking
  	for(int i = 1; i < argc; i++)
  	{
    if(strcasecmp(argv[i], "-mode") == 0 && i+1 < argc)
    {
      mode = atoi(argv[i+1]);
      if(mode < 0 || mode > 2)
        mode = 0;
    }
  }

	
	/*Local variables:*/
	Anto anto;
	Ground ground;



	/*Initialize positions :*/
	Initialize_states(&anto, &ground);

	/*Initialization SDL, creating window, creating renderer:*/
/**************************************************************************************/

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!=0)
    {
        SDL_Log("ERROR : Initialization SDL -> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window=SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WINDOW_WIDTH,WINDOW_HEIGTH,0);
    if(window==NULL)
    {
        SDL_Log("ERROR : Creating window -> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
    if(renderer==NULL)
    {
        SDL_Log("ERROR: Creating renderer > %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*Initialize IMG */
    if(!IMG_Init(IMG_INIT_PNG))
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        exit(EXIT_FAILURE);
    }

    /*Initialize Audio*/
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,4096)<0)
    {
        SDL_Log("ERROR: initialize Audio > %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*Initialize TTF:*/
    TTF_Init();

/*****************************************************************************************/

    /*loading the ground and its things*/
    Load_ground_stuff(&ground, surface, renderer);

	/*Loading anto frames,sounds and ...*/

	Load_anto_Stuff(&anto, surface, renderer);
	
	/*GAME LOOP :*/
	int timer=0,timer1=0;
	int done1 = 0, done2 = 0;
	SDL_Event event;
	while(done1 == 0 && done2 == 0)
	{
		timer++;
		timer1++;

		RendererSpecifications(renderer);

		/*Quit,Mute and other settings:*/
		done1 = Non_Mvt_Events(&anto, event);

		/*Mouvments:*/
		Mvt_Events(&anto, &ground);

		/*collision detection anto:*/
		Collision_detection(&anto, &ground);

		/*Eat fruits*/
		Eat(&anto, &ground);

		/*collision with monsters and die:*/
		Collision_mons(&anto, &ground);

		/*Drawing the ground, upper horizontal bariers, vertical barriers:*/
		Draw_ground(&ground, renderer, &timer1);

		/*Drawing Anto:*/
		Draw_anto(&anto, renderer, &timer);

		/*Drawing bariers */
		Draw_above_anto(&ground, renderer);

		done2 = Game_Over(&anto, &ground, renderer);


		/*Showing everything on the screen*/
		SDL_RenderPresent(renderer);

		SDL_Delay(10);
	}

	
	
	/**************************************************************************************/
	Destroy_Everything(&anto, &ground, window, renderer);
	printf("Yey it's working!\n");

	return 0;
}
