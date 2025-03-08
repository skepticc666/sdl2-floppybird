#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>
#include <SDL_ttf.h>
#include <SDL_image.h>

int main()
{
    int width = 680;
    int height = 480;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;
    bool isrunning = true;

    SDL_Rect rect_bird;
    rect_bird.x = 0;
    rect_bird.y = 0;
    rect_bird.w = width / 20;
    rect_bird.h = width / 20;

    SDL_Rect rect_pt;
    rect_pt.x = width / 2;
    rect_pt.y = 0;
    rect_pt.w = width / 18;
    rect_pt.h = height / 5;


    SDL_Rect rect_pl;
    rect_pl.x = width / 2;
    rect_pl.y = rect_pt.h + height / 5;
    rect_pl.w = width / 18;
    rect_pl.h = height;

     
    if (TTF_Init() < 0)
    {
        std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    }

    TTF_Font *font;
    font = TTF_OpenFont("C:\\Programming\\C++\\sdl2 pong\\sample.ttf", 24);
    if (!font)
    {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    bool gameRunning = true;

    double dt = 0;

    SDL_Rect rect_top[5];
    SDL_Rect rect_btm[5];
    

    for(int i = 0 ; i < 4 ; i ++){ 

        int x = rand() % 100;
        // int m = rand() % 100;
        rect_top[i].x = (i*width/4) ;
        rect_top[i].y = 0;
        rect_top[i].w = width / 18;
        rect_top[i].h = height / 5 + x;
        
        rect_btm[i].x = rect_top[i].x;
        rect_btm[i].y = rect_top[i].h + height / 5;
        rect_btm[i].w = rect_top[i].w;
        rect_btm[i].h = height;
        
    }
    
    
    SDL_Texture* texture = IMG_LoadTexture(render, "C:\\Programming\\C++\\sdl2 floppybird\\image.png");


    // rect_top.x += 140;
    // rect_top.h += 22;
    // rect_btm.x = rect_top.x;
    // rect_btm.y = rect_top.h + height / 5;
    

    while (isrunning)
    {
        const auto &start_time = std::chrono::high_resolution_clock::now();

        rect_bird.x = 0;
        rect_bird.y += dt;
        SDL_Delay(100);

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isrunning = false;
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    rect_bird.x = 0;
                    rect_bird.y -= 20;
                }
            }
        }

        if (gameRunning == false)
        {
            continue;
        }


        SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
        SDL_RenderClear(render);

        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderFillRect(render, &rect_bird);
        SDL_RenderCopy(render, texture, NULL, &rect_bird); 



        for(int i = 0 ; i < 4 ; i ++){

            int m = rand() % 100; 

            SDL_SetRenderDrawColor(render,255,255,255,255);
            SDL_RenderFillRect(render , &rect_top[i]);
        
            SDL_SetRenderDrawColor(render,255,255,255,255);
            SDL_RenderFillRect(render , &rect_btm[i]);

            rect_top[i].x -= 5;
            rect_btm[i].x -= 5;
            
            if(rect_top[i].x + rect_top[i].w < 0){
                rect_top[i].x = width;
                rect_btm[i].x = width;
                rect_top[i].h = height / 5 + m ;
                rect_btm[i].y = rect_top[i].h + height / 5;
            }

            }



        
        

        
        // rect_pl.x -= 5;
        // rect_pt.x -= 5;
        // if (rect_pl.x + rect_pl.w < 0)
        // {
        //     rect_pt.x = width / 2;
        //     rect_pl.x = width / 2;
        // }

        // if (rect_bird.y < rect_pt.y + rect_pt.h || rect_bird.y + rect_bird.h > rect_pl.y)
        // {
        //     if (rect_bird.x + rect_bird.w > rect_pt.x)
        //     {

        //         // text initialization begins here
        //         SDL_Color text_color = {255, 0, 0, 255};
        //         SDL_Surface *text = TTF_RenderText_Solid(font, "GAME OVER!", text_color);

        //         SDL_Texture *text_texture = SDL_CreateTextureFromSurface(render, text);
        //         // text ends begins here

        //         // text.w;

        //         SDL_Rect src = {0, 0, text->w, text->h};
        //         SDL_Rect dest = {width / 2 - text->w * 4 / 2, height / 2 - text->h * 4 / 2, text->w * 4, text->h * 4};
        //         gameRunning = false;
        //     }
        // }

       

        // SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        // SDL_RenderFillRect(render, &rect_pt);

        // SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        // SDL_RenderFillRect(render, &rect_pl);

        SDL_RenderPresent(render);

        const auto &end_time = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<double, std::ratio<1, 60>>(end_time - start_time).count();
    }
}
