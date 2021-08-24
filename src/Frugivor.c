#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Frugivor.h"


/*Functions:*/

/**********************************************************************************************/

void Initialize_states(Anto *anto, Ground *ground)
{
    anto->x=150; anto->y=450;
    anto->facing=1;
    anto->moving=0;
    anto->Is_dead=0;
    anto->speed=1;
    anto->won_test =0;

    ground->woods3_x = (WINDOW_WIDTH - WOODS3_WIDTH*WOODS3_NUM)/2;
    ground->woods9_x = (WINDOW_WIDTH - WOODS9_WIDTH*WOODS9_NUM)/2;
    ground->woods3_y = WINDOW_HEIGTH - WOODS9_HEIGTH - WOODS3_HEIGTH;
    ground->woods9_y = WINDOW_HEIGTH - WOODS9_HEIGTH -10 ;


    /*init monsters*/
    ground->mons_x[0] = 430;
    ground->mons_y[0] = 150;
    ground->mons_x[1] = 60;
    ground->mons_y[1] = 175;
    ground->mons_x[2] = 150;
    ground->mons_y[2] = 112;
    ground->mons_x[3] = 320;
    ground->mons_y[3] = 290;
    ground->mons_x[4] = 80;
    ground->mons_y[4] = 350;
    ground->mons_x[5] = 10;
    ground->mons_y[5] = 210;
    ground->mons_x[6] = 255;
    ground->mons_y[6] = 200;

    ground->mons_facing_left = 0;
    ground->timer2=0;
    ground->timer3=0;
    ground->timer4=0;

    //init barrels
    ground->barrel_x[0] = 25;
    ground->barrel_y[0] = 100;
    ground->barrel_x[1] = 25;
    ground->barrel_y[1] = 180;
    ground->barrel_x[2] = 470;
    ground->barrel_y[2] = 30;
    ground->barrel_x[3] = 470;
    ground->barrel_y[3] = 130;
    ground->barrel_x[4] = 250;
    ground->barrel_y[4] = 250;
    ground->barrel_x[5] = 300;
    ground->barrel_y[5] = 250;
    ground->barrel_x[6] = 475;
    ground->barrel_y[6] = 470;
    ground->barrel_x[7] = 410;
    ground->barrel_y[7] = 410;
    ground->barrel_x[8] = 380;
    ground->barrel_y[8] = 70;
    ground->barrel_x[9] = 40;
    ground->barrel_y[9] = 450;
    ground->barrel_x[10] = 40;
    ground->barrel_y[10] = 360;
    ground->barrel_x[11] = 200;
    ground->barrel_y[11] = 200;
    ground->barrel_x[12] = 200;
    ground->barrel_y[12] = 125;
    ground->barrel_x[13] = 250;
    ground->barrel_y[13] = 50;
    ground->barrel_x[14] = 50;
    ground->barrel_y[14] = 10;

    //init fruits
    ground->fruit_x[0] = 25;
    ground->fruit_y[0] = 150;
    ground->fruit_x[1] = 205;
    ground->fruit_y[1] = 180;
    ground->fruit_x[2] = 285;
    ground->fruit_y[2] = 268;
    ground->fruit_x[3] = 430;
    ground->fruit_y[3] = 55;
    ground->fruit_x[4] = 435;
    ground->fruit_y[4] = 130;
    ground->fruit_x[5] = 480;
    ground->fruit_y[5] = 100;
    ground->fruit_x[6] = 20;
    ground->fruit_y[6] = 25;
    ground->fruit_x[7] = 20;
    ground->fruit_y[7] = 400;
    ground->fruit_x[8] = 220;
    ground->fruit_y[8] = 100;
    ground->fruit_x[9] = 320;
    ground->fruit_y[9] = 25;
    ground->fruit_x[10] = 320;
    ground->fruit_y[10] = 300;

    ground->fruit_w[0]=10;
    ground->fruit_h[0]=11;
    ground->fruit_w[1]=10;
    ground->fruit_h[1]=10;
    ground->fruit_w[2]=8;
    ground->fruit_h[2]=10;
    ground->fruit_w[3]=16;
    ground->fruit_h[3]=19;
    ground->fruit_w[4]=12;
    ground->fruit_h[4]=12;
    ground->fruit_w[5]=9;
    ground->fruit_h[5]=12;
    ground->fruit_w[6]=24;
    ground->fruit_h[6]=22;
    ground->fruit_w[7]=12;
    ground->fruit_h[7]=12;
    ground->fruit_w[8]=19;
    ground->fruit_h[8]=16;
    ground->fruit_w[9]=21;
    ground->fruit_h[9]=17;
    ground->fruit_w[10]=16;
    ground->fruit_h[10]=18;


    /*Init fruit eating:*/
    for(int i=0;i<FRUIT_NUM;i++)
    {
        ground->fruit_eaten[i]=0;
    }



    /*Declaring a color*/
    ground->white.r = 255;
    ground->white.g = 255;
    ground->white.b = 255;

    /*Init score*/
    ground->score_number = 0;


}


void RendererSpecifications(SDL_Renderer *renderer)
{

    /*Giving blue color to the renderer : */
    SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE);//SDL_ALPHA_OPAQUE=255
    /*Clear the screen (to blue)*/
    SDL_RenderClear(renderer);
    /*Giving white color to the renderer: */
    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);//SDL_ALPHA_OPAQUE=255
}

/*********************************************************************************************/
int Non_Mvt_Events(Anto *anto, SDL_Event event)
{
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return 1;
						break;
                    case SDLK_m:
                        /*Mute/Unmute background music*/
                        if(!Mix_PlayingMusic())
                            Mix_PlayMusic(anto->music,-1);
                        else if(Mix_PausedMusic())
                            Mix_ResumeMusic();
                        else Mix_PauseMusic();
                        break;
				}
				break;
			case SDL_QUIT:
				return 1;
				break;
            default:
                break;
            
		}
	}
	return 0;
}

/*********************************************************************************************/

void Mvt_Events(Anto *anto, Ground *ground)
{
    /*Anto is always still, unless he moves :) */
    anto->moving=0;

    
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_RIGHT])
    {
        anto->x += anto->speed;
        anto->facing=4;
        anto->moving=1;
    }

    else if(state[SDL_SCANCODE_LEFT])
    {
        anto->x -= anto->speed;
        anto->facing=2;
        anto->moving=1;
    }

    else if(state[SDL_SCANCODE_UP])
    {
        anto->y -= anto->speed;
        anto->facing=3;
        anto->moving=1;
    }

    else if(state[SDL_SCANCODE_DOWN])
    {
        anto->y += anto->speed;
        anto->facing=1;
        anto->moving=1;
    }

    /*increment timers*/
    ground->timer2 ++;
    ground->timer3 ++;
    ground->timer4 ++;

    /*monster mvmt:*/
    //init timers
    if(ground->timer2 >200)
    {
        ground->timer2=0;
    }
    if(ground->timer3 >300)
    {
        ground->timer3=0;
    }
    if(ground->timer4 > 300)
    {
        ground->timer4 =0;
    }


    /*monster 0 mvmt*/
    if(ground->timer2 < 100)
    {
        if(ground->timer2 == 0)
            ground->mons_facing_left = 0;
        ground->mons_x[0]--;
    }
    else if(ground->timer2 >= 100)
    {
        if(ground->timer2 == 100)
            ground->mons_facing_left = 1;
        ground->mons_x[0]++;
    }
    /*monster 1 mvt*/
    if(ground->timer2 < 100)
    {
        ground->mons_y[1]--;
    }
    else if(ground->timer2 >= 100)
    {
        ground->mons_y[1]++;
    }

    /*monster 2 mvt*/
    if(ground->timer3 < 50)
    {
        ground->mons_y[2]++;
    }
    else if(ground->timer3 >= 100 && ground->timer3 <150)
    {
        ground->mons_y[2]++;
    }
    else if(ground->timer3 >=150 && ground->timer3 <200)
    {
        ground->mons_y[2]--;
    }
    else if(ground->timer3 > 250)
    {
        ground->mons_y[2]--;
    }

    /*monster 3 mvt*/
    if(ground->timer2 < 100)
    {
        if(ground->timer2 == 0)
            ground->mons_facing_left = 0;
        ground->mons_x[3]--;
    }
    else if(ground->timer2 >= 100)
    {
        if(ground->timer2 == 100)
            ground->mons_facing_left = 1;
        ground->mons_x[3]++;
    }

    /*monster 4 mvt:*/
    if(ground->timer4 >=100 && ground->timer4 <200)
    {
        ground->mons_y[4]++;
    }
    if(ground->timer4 >=200 && ground->timer4 <300)
    {
        ground->mons_y[4]--;
    }




}

/*********************************************************************************************/
void Load_ground_stuff(Ground *ground, SDL_Surface *surface, SDL_Renderer *renderer)
{
    /*Loading ground1:*/
    surface = IMG_Load("res/ground&stuff/ground1.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(ground1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->ground_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->ground_texture == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(ground1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /**/

    /*Loading Horizontal barier:*/
    surface = IMG_Load("res/ground&stuff/hor_barier.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(hor_barier) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->hor_barier_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->hor_barier_texture == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(ground1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading vertical upper barier:*/
    surface = IMG_Load("res/ground&stuff/ver_barier_u.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(ver_barier_up) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->ver_barier_u_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->ver_barier_u_texture == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(ver_barier_up) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading vertical middle barier:*/
    surface = IMG_Load("res/ground&stuff/ver_barier_m.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(ver_barier_middle) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->ver_barier_m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->ver_barier_m_texture == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(ver_barier_middle) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading vertical lower barier:*/
    surface = IMG_Load("res/ground&stuff/ver_barier_l.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(ver_barier_lower) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->ver_barier_l_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->ver_barier_l_texture == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(ver_barier_lower) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading woods3:*/
    surface = IMG_Load("res/ground&stuff/woods3.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(woods3) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->woods3_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->woods3_texture == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(woods3) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading woods9:*/
    surface = IMG_Load("res/ground&stuff/woods9.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(woods9) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->woods9_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->woods9_texture == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(woods9) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading barrels*/
    for(int i=0; i<BARREL_NUM ;i++)
    {
        surface = IMG_Load("res/ground&stuff/barrel.png");
        if(surface == NULL)
        {
            SDL_Log("ERROR : Loading image(barrel) ==> %s\n",SDL_GetError());
            exit(EXIT_FAILURE);
        }
        ground->barrel_texture[i] = SDL_CreateTextureFromSurface(renderer, surface);
        if(ground->barrel_texture[i] == NULL)
        {
            SDL_Log("ERROR creating texture from the surface(barrel) ==> %s\n",SDL_GetError());
            exit(EXIT_FAILURE);
        }
        SDL_FreeSurface(surface);
    }

    /*Loading fruits*/
    /*apple*/
    surface = IMG_Load("res/ground&stuff/apple.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(apple) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->fruit_texture[0] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->fruit_texture[0] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(apple) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
    /*botato*/
    surface = IMG_Load("res/ground&stuff/botato.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(botato) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->fruit_texture[1] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->fruit_texture[1] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(botato) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
    /*dragon*/
    surface = IMG_Load("res/ground&stuff/dragon.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(dragon) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->fruit_texture[2] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->fruit_texture[2] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(dragon) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
    /*grape*/
    surface = IMG_Load("res/ground&stuff/grape.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(grape) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->fruit_texture[3] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->fruit_texture[3] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(grape) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
    /*kiwi*/
    surface = IMG_Load("res/ground&stuff/kiwi.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(kiwi) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->fruit_texture[4] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->fruit_texture[4] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(dragon) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
    /*tzz1*/
    surface = IMG_Load("res/ground&stuff/tzz1.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(tzz1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->fruit_texture[5] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->fruit_texture[5] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(tzz1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
    /*watermelon:*/
    surface = IMG_Load("res/ground&stuff/watermelon.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(watermelon) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->fruit_texture[6] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->fruit_texture[6] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(water) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
    /*strawberry:*/
    surface = IMG_Load("res/ground&stuff/strawberry.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(strawberry) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->fruit_texture[7] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->fruit_texture[7] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(strawberry) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*tomato:*/
    surface = IMG_Load("res/ground&stuff/tomato.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(tomato) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->fruit_texture[8] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->fruit_texture[8] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(tomato) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*corn:*/
    surface = IMG_Load("res/ground&stuff/corn.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(corn) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->fruit_texture[9] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->fruit_texture[9] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(corn) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*falafel:*/
    surface = IMG_Load("res/ground&stuff/falafel.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(falafel) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->fruit_texture[10] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->fruit_texture[10] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(falafel) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);



    /*mons0*/
    surface = IMG_Load("res/ground&stuff/mons0.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(mons0) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->mons_texture[0] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->mons_texture[0] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(mons0) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*mons1:*/
    surface = IMG_Load("res/ground&stuff/mons1.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(mons1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->mons_texture[1] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->mons_texture[1] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(mons1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*mons2:*/
    surface = IMG_Load("res/ground&stuff/mons2.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(mons2) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->mons_texture[2] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->mons_texture[2] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(mons2) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*mons3:*/
    surface = IMG_Load("res/ground&stuff/mons3.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(mons3) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->mons_texture[3] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->mons_texture[3] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(mons3) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*mons4:*/
    surface = IMG_Load("res/ground&stuff/mons4.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(mons4) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->mons_texture[4] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->mons_texture[4] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(mons4) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*mons5:*/
    surface = IMG_Load("res/ground&stuff/mons5.png");
    if(surface == NULL)
    {
        SDL_Log("ERROR : Loading image(mons5) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->mons_texture[5] = SDL_CreateTextureFromSurface(renderer, surface);
    if(ground->mons_texture[5] == NULL)
    {
        SDL_Log("ERROR creating texture from the surface(mons5) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading font*/
    ground->font = TTF_OpenFont("res/fonts/FarmingFont.ttf", 300);
    if(ground->font == NULL)
    {
        SDL_Log("ERROR : Loading font ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*loading the 'game over' text to the surface:*/
    surface = TTF_RenderText_Blended(ground->font,"GAME OVER!",ground->white);

    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading GAME OVER text to the surface -> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->game_over_texture=SDL_CreateTextureFromSurface(renderer,surface);
    if(ground->game_over_texture==NULL)
    {
        SDL_Log("ERROR : Creating texture 'gameover' from the surface -> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*loading the 'you win' text to the surface:*/
    surface = TTF_RenderText_Blended(ground->font,"YOU WON!",ground->white);

    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading 'you won' text to the surface -> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->you_won_texture=SDL_CreateTextureFromSurface(renderer,surface);
    if(ground->you_won_texture==NULL)
    {
        SDL_Log("ERROR : Creating texture 'you won' from the surface -> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*loading the 'press m mute' text to the surface:*/
    surface = TTF_RenderText_Blended(ground->font,"Press 'm' to mute music",ground->white);

    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading mute text to the surface -> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    ground->m_mute=SDL_CreateTextureFromSurface(renderer,surface);
    if(ground->m_mute==NULL)
    {
        SDL_Log("ERROR : Creating texture 'mute_m' from the surface -> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
    

}




/*********************************************************************************************/

void Load_anto_Stuff(Anto *anto,SDL_Surface *surface, SDL_Renderer *renderer)
{
	//************Loading Frames************//

	/*Loading AntoFront0.png to the surface and creating a texture from it:*/
	surface = IMG_Load("res/caracters/AntoFront0.png");
	if(surface==NULL)
    {
        SDL_Log("ERROR : Loading image(AntoFront0) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    anto->frames[0]=SDL_CreateTextureFromSurface(renderer, surface);
    if(anto->frames[0]==NULL)
    {
    	SDL_Log("ERROR creating texture from the surface(AntoFront0) ==> %s\n",SDL_GetError());
    	exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading AntoFront1.png to the surface and creating a texture from it:*/
    surface = IMG_Load("res/caracters/AntoFront1.png");
    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading image(AntoFront1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    anto->frames[1]=SDL_CreateTextureFromSurface(renderer, surface);
    if(anto->frames[1]==NULL)
    {
        SDL_Log("ERROR creating texture from the surface(AntoFront1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading AntoFront2.png to the surface and creating a texture from it:*/
    surface = IMG_Load("res/caracters/AntoFront2.png");
    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading image(AntoFront2) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    anto->frames[2]=SDL_CreateTextureFromSurface(renderer, surface);
    if(anto->frames[2]==NULL)
    {
        SDL_Log("ERROR creating texture from the surface(AntoFront2) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading AntoLeft0.png to the surface and creating a texture from it:*/
    surface = IMG_Load("res/caracters/AntoLeft0.png");
    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading image(AntoLeft0) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    anto->frames[3]=SDL_CreateTextureFromSurface(renderer, surface);
    if(anto->frames[3]==NULL)
    {
        SDL_Log("ERROR creating texture from the surface(AntoLeft0) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading AntoLeft1.png to the surface and creating a texture from it:*/
    surface = IMG_Load("res/caracters/AntoLeft1.png");
    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading image(AntoLeft1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    anto->frames[4]=SDL_CreateTextureFromSurface(renderer, surface);
    if(anto->frames[4]==NULL)
    {
        SDL_Log("ERROR creating texture from the surface(AntoLeft1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading AntoLeft2.png to the surface and creating a texture from it:*/
    surface = IMG_Load("res/caracters/AntoLeft2.png");
    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading image(AntoLeft2) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    anto->frames[5]=SDL_CreateTextureFromSurface(renderer, surface);
    if(anto->frames[5]==NULL)
    {
        SDL_Log("ERROR creating texture from the surface(AntoLeft2) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading AntoBack0.png to the surface and creating a texture from it:*/
    surface = IMG_Load("res/caracters/AntoBack0.png");
    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading image(AntoBack0) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    anto->frames[6]=SDL_CreateTextureFromSurface(renderer, surface);
    if(anto->frames[6]==NULL)
    {
        SDL_Log("ERROR creating texture from the surface(AntoBack0) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading AntoBack1.png to the surface and creating a texture from it:*/
    surface = IMG_Load("res/caracters/AntoBack1.png");
    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading image(AntoBack1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    anto->frames[7]=SDL_CreateTextureFromSurface(renderer, surface);
    if(anto->frames[7]==NULL)
    {
        SDL_Log("ERROR creating texture from the surface(AntoBack1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading AntoBack2.png to the surface and creating a texture from it:*/
    surface = IMG_Load("res/caracters/AntoBack2.png");
    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading image(AntoBack2) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    anto->frames[8]=SDL_CreateTextureFromSurface(renderer, surface);
    if(anto->frames[8]==NULL)
    {
        SDL_Log("ERROR creating texture from the surface(AntoBack2) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading AntoRight0.png to the surface and creating a texture from it:*/
    surface = IMG_Load("res/caracters/AntoRight0.png");
    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading image(AntoRight0) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    anto->frames[9]=SDL_CreateTextureFromSurface(renderer, surface);
    if(anto->frames[9]==NULL)
    {
        SDL_Log("ERROR creating texture from the surface(AntoRight0) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading AntoRight1.png to the surface and creating a texture from it:*/
    surface = IMG_Load("res/caracters/AntoRight1.png");
    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading image(AntoRight1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    anto->frames[10]=SDL_CreateTextureFromSurface(renderer, surface);
    if(anto->frames[10]==NULL)
    {
        SDL_Log("ERROR creating texture from the surface(AntoRight1) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Loading AntoRight2.png to the surface and creating a texture from it:*/
    surface = IMG_Load("res/caracters/AntoRight2.png");
    if(surface==NULL)
    {
        SDL_Log("ERROR : Loading image(AntoRight2) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    anto->frames[11]=SDL_CreateTextureFromSurface(renderer, surface);
    if(anto->frames[11]==NULL)
    {
        SDL_Log("ERROR creating texture from the surface(AntoRight2) ==> %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);

    /*Load eat sound effect:*/
    anto->eat_SE = Mix_LoadWAV("res/sounds/eat.wav");
    if(anto->eat_SE == NULL)
    {
        printf("ERROR! loading sound effect -> %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*Load dead sound effect:*/
    anto->dead_SE = Mix_LoadWAV("res/sounds/gameover.wav");
    if(anto->dead_SE == NULL)
    {
        printf("ERROR! loading sound effect -> %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*load mons souns effect:*/
    anto->mons_SE = Mix_LoadWAV("res/sounds/mons.wav");
    if(anto->mons_SE == NULL)
    {
        printf("ERROR! loading sound effect -> %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*load mons souns effect:*/
    anto->won_SE = Mix_LoadWAV("res/sounds/won.wav");
    if(anto->won_SE == NULL)
    {
        printf("ERROR! loading sound effect -> %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*Loading background music*/
    anto->music = Mix_LoadMUS("res/sounds/music.wav");
    if(anto->music == NULL)
    {
        printf("ERROR! loading sound effect -> %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    /*playing the music:*/
    Mix_PlayMusic(anto->music,-1);





}

/*********************************************************************************************/
void Collision_detection(Anto *anto, Ground *ground)
{
    /*Collision detection with upper bariers:*/
    if(anto->y < HOR_BARIER_HEIGTH - PARAMETRE_COLLISION_UPPER_BARIER)
    {
        anto->y=HOR_BARIER_HEIGTH - PARAMETRE_COLLISION_UPPER_BARIER;
        anto->moving = 0;
    }

    /*Collision detection with the left bariers:*/
    if(anto->x < VER_BARIER_WIDTH - PARAMETRE_COLLISION_LEFT_BARIER)
    {
        anto->x = VER_BARIER_WIDTH - PARAMETRE_COLLISION_LEFT_BARIER;
        anto->moving = 0;
    }

    /*Collision detection with the right bariers:*/
    if(anto->x + ANTO_WIDTH > WINDOW_WIDTH - VER_BARIER_WIDTH + PARAMETRE_COLLISION_RIGHT_BARIER )
    {
        anto->x = WINDOW_WIDTH - VER_BARIER_WIDTH + PARAMETRE_COLLISION_RIGHT_BARIER - ANTO_WIDTH;
        anto->moving = 0;
    }

    /*Collision detection with lower bariers: */
    if(anto->y + ANTO_HEIGTH > WINDOW_HEIGTH -HOR_BARIER_HEIGTH + PARAMETRE_COLLISION_LOWER_BARIER)
    {
        anto->y = WINDOW_HEIGTH - HOR_BARIER_HEIGTH + PARAMETRE_COLLISION_LOWER_BARIER - ANTO_HEIGTH ;
        anto->moving = 0;
    }


    /*Collision detection with woods3*/
    for (int i = 0; i <WOODS3_NUM ; i++)
    {   
        if(anto->x + ANTO_WIDTH > ground->woods3_x + WOODS3_WIDTH*i  && anto->x < ground->woods3_x + WOODS3_WIDTH*i + WOODS3_WIDTH )
        {
            /*from above*/
            if(anto->y + ANTO_HEIGTH > ground->woods3_y && anto->y < ground->woods3_y)
            {
                anto->y=ground->woods3_y- ANTO_HEIGTH;
            }
        }

        if(anto->y+ANTO_HEIGTH > ground->woods3_y && anto->y < ground->woods3_y+WOODS3_HEIGTH)
        {
            /*from right:*/
            if(anto->x < ground->woods3_x + WOODS3_WIDTH*i +WOODS3_WIDTH && anto->x + ANTO_WIDTH > ground->woods3_x +WOODS3_WIDTH)
            {
                anto->x = ground->woods3_x +WOODS3_WIDTH + WOODS3_WIDTH*i;
            }

            /*from left:*/
            if(anto->x + ANTO_WIDTH > ground->woods3_x && anto->x < ground->woods3_x )
            {
                anto->x = ground->woods3_x - ANTO_WIDTH;   
            }
        }
    }
    /*Collision detection with woods9*/
    for (int i = 0; i <WOODS9_NUM ; i++)
    {   
        if(anto->x + ANTO_WIDTH > ground->woods9_x + WOODS9_WIDTH*i  && anto->x < ground->woods9_x + WOODS9_WIDTH*i + WOODS9_WIDTH )
        {
            /*from above*/
            if(anto->y + ANTO_HEIGTH > ground->woods9_y && anto->y < ground->woods9_y)
            {
                anto->y=ground->woods9_y- ANTO_HEIGTH;
            }
        }

        if(anto->y+ANTO_HEIGTH > ground->woods9_y && anto->y < ground->woods9_y+WOODS9_HEIGTH)
        {
            /*from right:*/
            if(anto->x < ground->woods9_x + WOODS9_WIDTH*i + WOODS9_WIDTH && anto->x + ANTO_WIDTH > ground->woods9_x +WOODS9_WIDTH)
            {
                anto->x = ground->woods9_x +WOODS9_WIDTH + WOODS9_WIDTH*i;
            }

            /*from left:*/
            if(anto->x + ANTO_WIDTH > ground->woods9_x && anto->x < ground->woods9_x )
            {
                anto->x = ground->woods9_x - ANTO_WIDTH;   
            }
        }
    }

    /*Collistion detection with the barrels*/
    for(int i=0; i<BARREL_NUM; i++)
    {
        if(anto->x + ANTO_WIDTH/2 > ground->barrel_x[i] && anto->x + ANTO_WIDTH/2 < ground->barrel_x[i] + BARREL_WIDTH )
        {
            /*from under*/
            if(anto->y < ground->barrel_y[i]+BARREL_HEIGTH && anto->y > ground->barrel_y[i])
            {
                anto->y = ground->barrel_y[i]+BARREL_HEIGTH;
            }
        }

        if(anto->x + ANTO_WIDTH > ground->barrel_x[i] && anto->x  < ground->barrel_x[i] + BARREL_WIDTH)
        {
             /*from above*/
            if(anto->y + ANTO_HEIGTH > ground->barrel_y[i] && anto->y < ground->barrel_y[i])
            {
                anto->y=ground->barrel_y[i]- ANTO_HEIGTH;
            }
        }
        if(anto->y+ANTO_HEIGTH/2 > ground->barrel_y[i] && anto->y +ANTO_HEIGTH/2 < ground->barrel_y[i]+BARREL_HEIGTH)
        {
            /*from right:*/
            if(anto->x < ground->barrel_x[i] + BARREL_WIDTH && anto->x + ANTO_WIDTH > ground->barrel_x[i] + BARREL_WIDTH)
            {
                anto->x = ground->barrel_x[i] + BARREL_WIDTH;
            }

            /*from left:*/
            else if(anto->x + ANTO_WIDTH > ground->barrel_x[i] && anto->x < ground->barrel_x[i])
            {
                anto->x = ground->barrel_x[i] - ANTO_WIDTH;   
            }
        }
    }
}
/*********************************************************************************************/
void Eat(Anto *anto, Ground *ground)
{
    for(int i=0;i<FRUIT_NUM;i++)
    {
         if(anto->x + ANTO_WIDTH/2 > ground->fruit_x[i] && anto->x + ANTO_WIDTH/2 < ground->fruit_x[i] + ground->fruit_w[i])
        {
            /*from under*/
            if(anto->y < ground->fruit_y[i]+ ground->fruit_h[i] && anto->y > ground->fruit_y[i])
            {
                if(ground->fruit_eaten[i] == 0)
                {
                    ground->fruit_eaten[i] = 1;
                    Mix_PlayChannel(2, anto->eat_SE, 0);
                    ground->score_number++;
                    anto->speed+=0.1;
                }
            }
        }

        if(anto->x + ANTO_WIDTH > ground->fruit_x[i] && anto->x  < ground->fruit_x[i] + ground->fruit_w[i])
        {
             /*from above*/
            if(anto->y + ANTO_HEIGTH > ground->fruit_y[i] && anto->y < ground->fruit_y[i])
            {
                if(ground->fruit_eaten[i] == 0)
                {
                    ground->fruit_eaten[i] = 1;
                    Mix_PlayChannel(2, anto->eat_SE, 0);
                    ground->score_number++;
                    anto->speed+=0.1;
                }
            }
        }
        if(anto->y+ANTO_HEIGTH/2 > ground->fruit_y[i] && anto->y +ANTO_HEIGTH/2 < ground->fruit_y[i]+ ground->fruit_h[i])
        {
            /*from right:*/
            if(anto->x < ground->fruit_x[i] + ground->fruit_w[i] && anto->x + ANTO_WIDTH > ground->fruit_x[i] + ground->fruit_w[i])
            {
                if(ground->fruit_eaten[i] == 0)
                {
                    ground->fruit_eaten[i] = 1;
                    Mix_PlayChannel(2, anto->eat_SE, 0);
                    ground->score_number++;
                    anto->speed+=0.1;
                }

            }

            /*from left:*/
            else if(anto->x + ANTO_WIDTH > ground->fruit_x[i] && anto->x < ground->fruit_x[i])
            {
                if(ground->fruit_eaten[i] == 0)
                {
                    ground->fruit_eaten[i] = 1;
                    Mix_PlayChannel(2, anto->eat_SE, 0);
                    ground->score_number++;
                    anto->speed+=0.1;
                }
            }
        }
    }
}

/*********************************************************************************************/
void Collision_mons(Anto *anto, Ground *ground)
{
    for(int i=0;i<MONS_NUM;i++)
    {
         if(anto->x + ANTO_WIDTH/2 > ground->mons_x[i] && anto->x + ANTO_WIDTH/2 < ground->mons_x[i] + MONS_WIDTH)
        {
            /*from under*/
            if(anto->y < ground->mons_y[i]+ MONS_HEIGTH && anto->y > ground->mons_y[i])
            {
                anto->Is_dead = 1;
            }
        }

        if(anto->x + ANTO_WIDTH > ground->mons_x[i] && anto->x  < ground->mons_x[i] + MONS_WIDTH)
        {
             /*from above*/
            if(anto->y + ANTO_HEIGTH - 5 > ground->mons_y[i] && anto->y < ground->mons_y[i])
            {
                anto->Is_dead = 1;
            }
        }
        if(anto->y+ANTO_HEIGTH/2 > ground->mons_y[i] && anto->y +ANTO_HEIGTH/2 < ground->mons_y[i]+ MONS_HEIGTH)
        {
            /*from right:*/
            if(anto->x < ground->mons_x[i] + MONS_WIDTH && anto->x + ANTO_WIDTH > ground->mons_x[i] + MONS_WIDTH)
            {
                anto->Is_dead = 1;
            }

            /*from left:*/
            else if(anto->x + ANTO_WIDTH > ground->mons_x[i] && anto->x < ground->mons_x[i])
            {
                anto->Is_dead = 1;
            }
        }
    }
}


/*********************************************************************************************/
void Draw_ground(Ground *ground, SDL_Renderer *renderer, int *timer1)
{
    /*Draw the ground*/
    for(int i=0; i<WINDOW_WIDTH; i+=GROUND_WIDTH)
    {
        for(int j=0; j<WINDOW_HEIGTH; j+=GROUND_HEIGTH)
        {
            SDL_Rect GroundRect = {i, j, GROUND_WIDTH, GROUND_HEIGTH};
            SDL_RenderCopy(renderer, ground->ground_texture, NULL, &GroundRect);
        }
    }

    /*Drawing upper horrizontal barriers*/
    for(int i=0; i<WINDOW_WIDTH; i+=HOR_BARIER_WIDTH)
    {
        SDL_Rect Hor_BarierRect = {i,0,HOR_BARIER_WIDTH, HOR_BARIER_HEIGTH};
        SDL_RenderCopy(renderer, ground->hor_barier_texture, NULL, &Hor_BarierRect);
    }

    /*Draw barrels:*/
    for(int i = 0; i < BARREL_NUM; i++)
    {
      SDL_Rect barrelRect = { ground->barrel_x[i], ground->barrel_y[i], BARREL_WIDTH, BARREL_HEIGTH};
      SDL_RenderCopy(renderer, ground->barrel_texture[i], NULL, &barrelRect);
    }
    /*Draw fruits:*/
    for(int i=0;i<FRUIT_NUM;i++)
    {
        if(i==0)
        {
            if(!ground->fruit_eaten[i])
            {
                SDL_Rect fruitRect={ground->fruit_x[i], ground->fruit_y[i], 10, 11};
                SDL_RenderCopy(renderer, ground->fruit_texture[i], NULL, &fruitRect);
            }
        }
        else if(i==1)
        {
            if(!ground->fruit_eaten[i])
            {
                SDL_Rect fruitRect={ground->fruit_x[i], ground->fruit_y[i], 10, 10};
                SDL_RenderCopy(renderer, ground->fruit_texture[i], NULL, &fruitRect);
            }
        }
        else if(i==2)
        {
            if(!ground->fruit_eaten[i])
            {
                SDL_Rect fruitRect={ground->fruit_x[i], ground->fruit_y[i], 8, 10};
                SDL_RenderCopy(renderer, ground->fruit_texture[i], NULL, &fruitRect);
            }
        }
        else if(i==3)
        {
            if(!ground->fruit_eaten[i])
            {
                SDL_Rect fruitRect={ground->fruit_x[i], ground->fruit_y[i], 16, 19};
                SDL_RenderCopy(renderer, ground->fruit_texture[i], NULL, &fruitRect);
            }
        }
        else if(i==4)
        {
            if(!ground->fruit_eaten[i])
            {
                SDL_Rect fruitRect={ground->fruit_x[i], ground->fruit_y[i], 12, 12};
                SDL_RenderCopy(renderer, ground->fruit_texture[i], NULL, &fruitRect);
            }
        }
        else if(i==5)
        {
            if(!ground->fruit_eaten[i])
            {
                SDL_Rect fruitRect={ground->fruit_x[i], ground->fruit_y[i], 9, 12};
                SDL_RenderCopy(renderer, ground->fruit_texture[i], NULL, &fruitRect);
            }
        }
        else if(i==6)
        {
            if(!ground->fruit_eaten[i])
            {
                SDL_Rect fruitRect={ground->fruit_x[i], ground->fruit_y[i], 24, 22};
                SDL_RenderCopy(renderer, ground->fruit_texture[i], NULL, &fruitRect);
            }
        }
        else if(i==7)
        {
            if(!ground->fruit_eaten[i])
            {
                SDL_Rect fruitRect={ground->fruit_x[i], ground->fruit_y[i], 12, 12};
                SDL_RenderCopy(renderer, ground->fruit_texture[i], NULL, &fruitRect);
            }
        }
        else if(i==8)
        {
            if(!ground->fruit_eaten[i])
            {
                SDL_Rect fruitRect={ground->fruit_x[i], ground->fruit_y[i], 19, 16};
                SDL_RenderCopy(renderer, ground->fruit_texture[i], NULL, &fruitRect);
            }
        }
        else if(i==9)
        {
            if(!ground->fruit_eaten[i])
            {
                SDL_Rect fruitRect={ground->fruit_x[i], ground->fruit_y[i], 21, 17};
                SDL_RenderCopy(renderer, ground->fruit_texture[i], NULL, &fruitRect);
            }
        }
        else if(i==10)
        {
            if(!ground->fruit_eaten[i])
            {
                SDL_Rect fruitRect={ground->fruit_x[i], ground->fruit_y[i], 16, 18};
                SDL_RenderCopy(renderer, ground->fruit_texture[i], NULL, &fruitRect);
            }
        }
    }


    /*Drawing monster:*/

    /*mons0*/
    SDL_Rect monsRect = {ground->mons_x[0], ground->mons_y[0], MONS_WIDTH, MONS_HEIGTH};

    if(*timer1>30) *timer1=0;
    if(*timer1 <= 15)
    {
        SDL_RenderCopyEx(renderer, ground->mons_texture[0],NULL, &monsRect, 0, NULL,ground->mons_facing_left);
    }
    else if(*timer1 > 15 && *timer1 <= 30)
    {
        SDL_RenderCopyEx(renderer, ground->mons_texture[1],NULL, &monsRect, 0, NULL,ground->mons_facing_left);
    }
    /*mons1*/
    SDL_Rect monsRect1 = {ground->mons_x[1], ground->mons_y[1], MONS_WIDTH, MONS_HEIGTH};

    if(*timer1 <= 15)
    {
        SDL_RenderCopy(renderer, ground->mons_texture[0],NULL, &monsRect1);
    }
    else if(*timer1 > 15 && *timer1 <= 30)
    {
        SDL_RenderCopy(renderer, ground->mons_texture[1],NULL, &monsRect1);
    }
    /*mons2*/
    SDL_Rect monsRect2 = {ground->mons_x[2], ground->mons_y[2], MONS_WIDTH, MONS_HEIGTH};

    if(*timer1 <= 15)
    {
        SDL_RenderCopyEx(renderer, ground->mons_texture[0],NULL, &monsRect2, 0, NULL, 1);
    }
    else if(*timer1 > 15 && *timer1 <= 30)
    {
        SDL_RenderCopyEx(renderer, ground->mons_texture[1],NULL, &monsRect2, 0, NULL, 1);
    }
    /*mons3*/
    SDL_Rect monsRect3 = {ground->mons_x[3], ground->mons_y[3], MONS_WIDTH, MONS_HEIGTH};

    if(*timer1 <= 15)
    {
        SDL_RenderCopyEx(renderer, ground->mons_texture[2],NULL, &monsRect3, 0, NULL, ground->mons_facing_left);
    }
    else if(*timer1 > 15 && *timer1 <= 30)
    {
        SDL_RenderCopyEx(renderer, ground->mons_texture[3],NULL, &monsRect3, 0, NULL, ground->mons_facing_left);
    }

    /*mons4*/
    SDL_Rect monsRect4 = {ground->mons_x[4], ground->mons_y[4], MONS_WIDTH, MONS_HEIGTH};

    if(*timer1 <= 15)
    {
        SDL_RenderCopy(renderer, ground->mons_texture[2],NULL, &monsRect4);
    }
    else if(*timer1 > 15 && *timer1 <= 30)
    {
        SDL_RenderCopy(renderer, ground->mons_texture[3],NULL, &monsRect4);
    }

    /*mons5*/
    SDL_Rect monsRect5 = {ground->mons_x[5], ground->mons_y[5], MONS_WIDTH, MONS_HEIGTH};

    if(*timer1 <= 15)
    {
        SDL_RenderCopyEx(renderer, ground->mons_texture[4],NULL, &monsRect5, 0, NULL, 1);
    }
    else if(*timer1 > 15 && *timer1 <= 30)
    {
        SDL_RenderCopyEx(renderer, ground->mons_texture[5],NULL, &monsRect5, 0, NULL, 1);
    }

    /*mons6*/
    SDL_Rect monsRect6 = {ground->mons_x[6], ground->mons_y[6], MONS_WIDTH, MONS_HEIGTH};

    if(*timer1 <= 15)
    {
        SDL_RenderCopyEx(renderer, ground->mons_texture[4],NULL, &monsRect6, 0, NULL, 1);
    }
    else if(*timer1 > 15 && *timer1 <= 30)
    {
        SDL_RenderCopyEx(renderer, ground->mons_texture[5],NULL, &monsRect6, 0, NULL, 1);
    }

    //The loading here is inside the game loop because the texture is changing:
    /*load the score(number)*/
    char buff[255]="";
    sprintf(buff," %d",(int)ground->score_number);

    ground->Tmp_surface = TTF_RenderText_Blended(ground->font,buff,ground->white);
    /*Creating texture from the surface(font):*/
    ground->score_texture=SDL_CreateTextureFromSurface(renderer,ground->Tmp_surface);

    SDL_FreeSurface(ground->Tmp_surface);
    /*Draw score :*/
    SDL_Rect score_numberRect = {40,540,20,40};
    SDL_RenderCopy(renderer, ground->score_texture, NULL, &score_numberRect);

    /*drawing the mute msg:*/
    SDL_Rect muteRect = {10,520,150,15};
    SDL_RenderCopy(renderer,ground->m_mute,NULL,&muteRect);

}
/*********************************************************************************************/
int Game_Over(Anto *anto, Ground *ground, SDL_Renderer *renderer)
{
    /*Draw the 'you win:*/

    if(ground->score_number == FRUIT_NUM)
    {
        SDL_Rect you_wonRect = {WINDOW_WIDTH/2 - 300/2,WINDOW_HEIGTH/2 - 400/2, 300,400  };
        SDL_RenderCopy(renderer, ground->you_won_texture, NULL, &you_wonRect);
        if(!anto->won_test)
        {
            Mix_PauseMusic();
            Mix_PlayChannel(3, anto->won_SE, 0);
            anto->won_test = 1;
            printf("You Won!\n");
        }


        printf("You Won!\n");
        
    }

    if(!anto->won_test)
    {
        /*Draw 'game over and shut the game:*/
        if(anto->Is_dead)
        {

            SDL_Rect game_overRect = {WINDOW_WIDTH/2 - 300/2,WINDOW_HEIGTH/2 - 400/2, 300,400  };
            SDL_RenderCopy(renderer, ground->game_over_texture, NULL, &game_overRect);

            Mix_PauseMusic();
            Mix_PlayChannel(1, anto->dead_SE, 0);
            Mix_PlayChannel(MIX_DEFAULT_CHANNELS, anto->mons_SE, 0);
            printf("You Lost!\n");
            SDL_Delay(1000);
            return 1;
        }
    }
    return 0;

}

/*********************************************************************************************/
//this function is made because I want to draw lower barriers(+left&rigth) above Anto => that's wyh I didn't want
//to write it with the function Draw_ground
void Draw_above_anto(Ground *ground, SDL_Renderer *renderer)
{
    /*Draw woods3:*/
    for (int i = 0; i <WOODS3_NUM ; i++)
    {
        SDL_Rect woods3Rect={ground->woods3_x +WOODS3_WIDTH*i, ground->woods3_y, WOODS3_WIDTH, WOODS3_HEIGTH};
        SDL_RenderCopy(renderer, ground->woods3_texture, NULL, &woods3Rect);
    }

    /*Draw woods9:*/
    for(int i = 0; i<WOODS9_NUM; i++)
    {
        SDL_Rect woods9Rect={ground->woods9_x + WOODS9_WIDTH*i, ground->woods9_y, WOODS9_WIDTH, WOODS9_HEIGTH};
        SDL_RenderCopy(renderer, ground->woods9_texture, NULL, &woods9Rect);
    }
    /*Draw lower horizontal barieres*/
    for(int i=0; i<WINDOW_WIDTH; i+=HOR_BARIER_WIDTH)
    {
        SDL_Rect Hor_BarierRect = {i,WINDOW_HEIGTH - HOR_BARIER_HEIGTH ,HOR_BARIER_WIDTH, HOR_BARIER_HEIGTH};
        SDL_RenderCopy(renderer, ground->hor_barier_texture, NULL, &Hor_BarierRect);

    }

    /*Drawing vertical barriers :*/
    for(int i=0; i<=WINDOW_WIDTH-VER_BARIER_WIDTH ; i+=WINDOW_WIDTH-VER_BARIER_WIDTH)
    {
        for(int j=HOR_BARIER_HEIGTH/2; j<WINDOW_HEIGTH-HOR_BARIER_HEIGTH ; j+=VER_BARIER_U_HEIGTH+VER_BARIER_M_HEIGTH+VER_BARIER_L_HEIGTH-HOR_BARIER_HEIGTH)
        {
            SDL_Rect Ver_U_BarierRect = {i,j,VER_BARIER_WIDTH, VER_BARIER_U_HEIGTH};
            SDL_Rect Ver_M_BarierRect = {i,j+VER_BARIER_U_HEIGTH,VER_BARIER_WIDTH, VER_BARIER_M_HEIGTH};
            SDL_Rect Ver_L_BarierRect = {i,j+VER_BARIER_U_HEIGTH+VER_BARIER_M_HEIGTH,VER_BARIER_WIDTH, VER_BARIER_L_HEIGTH};

            SDL_RenderCopy(renderer, ground->ver_barier_u_texture, NULL, &Ver_U_BarierRect);
            SDL_RenderCopy(renderer, ground->ver_barier_m_texture, NULL, &Ver_M_BarierRect);
            SDL_RenderCopy(renderer, ground->ver_barier_l_texture, NULL, &Ver_L_BarierRect);
        }
    }

}



/*********************************************************************************************/

void Draw_anto(Anto *anto, SDL_Renderer *renderer, int *timer)
{
    
    SDL_Rect antoRect={anto->x, anto->y, ANTO_WIDTH, ANTO_HEIGTH};
    if(*timer>40) *timer=0;

    if(anto->facing==1)
    {
        if(!anto->moving)
        SDL_RenderCopy(renderer, anto->frames[0], NULL, &antoRect);
        else
        {
            if(*timer>40) *timer=0;
            if(*timer<=20)
                SDL_RenderCopy(renderer, anto->frames[1], NULL, &antoRect);
            else if(*timer>20 && *timer<=40)
                SDL_RenderCopy(renderer, anto->frames[2], NULL, &antoRect);
        }
        
    }
    else if(anto->facing==2)
    {
        if(!anto->moving)
        SDL_RenderCopy(renderer, anto->frames[3], NULL, &antoRect);
        else
        {
            if(*timer>40) *timer=0;
            if(*timer<=20)
                SDL_RenderCopy(renderer, anto->frames[4], NULL, &antoRect);
            else if(*timer>20 && *timer<=40)
                SDL_RenderCopy(renderer, anto->frames[5], NULL, &antoRect);
        }
    }
    else if(anto->facing==3)
    {
        if(!anto->moving)
        SDL_RenderCopy(renderer, anto->frames[6], NULL, &antoRect);
        else
        {
            if(*timer>40) *timer=0;
            if(*timer<=20)
                SDL_RenderCopy(renderer, anto->frames[7], NULL, &antoRect);
            else if(*timer>20 && *timer<=40)
                SDL_RenderCopy(renderer, anto->frames[8], NULL, &antoRect);
        }
    }
    else if(anto->facing==4)
    {
        if(!anto->moving)
        SDL_RenderCopy(renderer, anto->frames[9], NULL, &antoRect);
        else
        {
            if(*timer>40) *timer=0;
            if(*timer<=20)
                SDL_RenderCopy(renderer, anto->frames[10], NULL, &antoRect);
            else if(*timer>20 && *timer<=40)
                SDL_RenderCopy(renderer, anto->frames[11], NULL, &antoRect);
        }
    }
    else SDL_RenderCopy(renderer, anto->frames[0], NULL, &antoRect);

}

/*********************************************************************************************/
void Destroy_Everything(Anto *anto,Ground *ground, SDL_Window *window, SDL_Renderer *renderer)
{
    for (int i=0; i<ANTO_FRAMES; i++)
        SDL_DestroyTexture(anto->frames[i]);
    for(int i=0;i<BARREL_NUM;i++)
        SDL_DestroyTexture(ground->barrel_texture[i]);
    for(int i=0;i<FRUIT_NUM;i++)
        SDL_DestroyTexture(ground->fruit_texture[i]);
    for(int i=0;i<MONS_NUM;i++)
        SDL_DestroyTexture(ground->mons_texture[i]);

    SDL_DestroyTexture(ground->ground_texture);
    SDL_DestroyTexture(ground->hor_barier_texture);
    SDL_DestroyTexture(ground->ver_barier_m_texture);
    SDL_DestroyTexture(ground->ver_barier_l_texture);
    SDL_DestroyTexture(ground->you_won_texture);
    SDL_DestroyTexture(ground->game_over_texture);
    SDL_DestroyTexture(ground->score_texture);


    Mix_FreeChunk(anto->eat_SE);
    Mix_FreeMusic(anto->music);
    TTF_CloseFont(ground->font);
    Mix_Quit();
    IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();	
}