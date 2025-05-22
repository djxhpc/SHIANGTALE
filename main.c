
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

#include "myheader.h"
#include <stdint.h>


#define HEIGHT_DIS 800
#define WIDTH_DIS 1200
#define WIDTH_SYMS 200 //BUTON大小
#define WIDTH_CRUZ 50
#define HEIGHT_SYMS 135//放大往下
#define COL1 350//距離左邊視窗的BUTON距離
#define FINCOL1 (COL1 + WIDTH_SYMS)
#define COL2 (FINCOL1 + 100)//中間BUTON距離
#define FINCOL2 (COL2 + WIDTH_SYMS)


#define TAMCOLAEVENTO 100
enum {PLAY, RESTART, MENU, SETTINGS,LOAD,RULES,LEVEL1,FS,windows,slid0, QUIT};

//ebug
#define DEBUG 1


#define false 0
#define true 1

char cola_ev[TAMCOLAEVENTO];
char* pevento = cola_ev;


	static ALLEGRO_DISPLAY * display = NULL;       //display
	static ALLEGRO_BITMAP * display_background;    //Fondo
	static ALLEGRO_BITMAP * play;                  //Boton play
	static ALLEGRO_BITMAP * controles;             //controles
	static ALLEGRO_BITMAP * restart;               //boton restart
	static ALLEGRO_BITMAP * settings;              //bton settings
	static ALLEGRO_BITMAP * menu;                  //Boton menu
	static ALLEGRO_BITMAP * quit;                  //bton quit
	static ALLEGRO_BITMAP * back2;
	static ALLEGRO_BITMAP * back3;              //titulo
	static ALLEGRO_BITMAP * load;                  //load
	static ALLEGRO_BITMAP * rules;                 //boton rules
	static ALLEGRO_BITMAP * level1;
	static ALLEGRO_BITMAP * level2;
	static ALLEGRO_BITMAP * level3;
	static ALLEGRO_BITMAP * fullscreen;
	static ALLEGRO_BITMAP * window;
	static ALLEGRO_BITMAP * fullwindow;
	static ALLEGRO_BITMAP * setting02;
	static ALLEGRO_BITMAP * loadgame0;
	static ALLEGRO_BITMAP * slider0;
	static ALLEGRO_BITMAP * slider1;
	static ALLEGRO_BITMAP * slider2;
	static ALLEGRO_BITMAP * slider3;
	static ALLEGRO_BITMAP * slider4;
	static ALLEGRO_BITMAP * slider5;

        static ALLEGRO_EVENT_QUEUE  * event_queue = NULL;
        static char close_display = false;

    ALLEGRO_SAMPLE* background = NULL;
    ALLEGRO_SAMPLE_ID backgroundId;




static void config_menu (void);
static void rule_menu (void);
static void setting_menu (void);
static void load_menu (void);

int main(void)
{

al_init(); /* initialize Allegro */
    al_install_keyboard(); /* install the keyboard for Allegro to use */
    al_init_image_addon();


    al_install_audio();  // install sound driver
    al_init_acodec_addon();      //AUDIO
    al_reserve_samples(9);


    al_init_font_addon();    // install font addons
    al_init_ttf_addon();


background = al_load_sample("UTMENU.wav");
al_play_sample(background, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &backgroundId);


    char rules2 = false;
    char back02 = false;
    char back03 = false;


     //Inicializo Allegro
	if( !al_init() )
	{
		fprintf(stderr, "Unable to start allegro\n");
		return -1;
	}


        //Inicializo  event
        event_queue = al_create_event_queue();
        if(!event_queue)
        {
            al_uninstall_system();
            printf("failed to create event_queue!\n");
            return -1;
        }

        //Inicializo kb
        if(!al_install_keyboard())
        {
            printf("failed to initialize the keyboard!\n");
            al_destroy_event_queue(event_queue);
            al_uninstall_system();
            return -1;
        }

         //Inicializo Mouse

        if (!al_install_mouse())
        {
            printf ("failed to inicialize mouse!\n");
            al_destroy_event_queue(event_queue);
            al_uninstall_system();
            return -1;
        }


        //Inicializo  images
	else if( !al_init_image_addon())
	{
		fprintf(stderr,"Unable to start image addon \n");
		al_uninstall_system();
                al_destroy_event_queue(event_queue);
		return -1;
	}



	else if( !(display_background = al_load_bitmap("fondo2.jpg")) )
	{

                al_destroy_event_queue(event_queue);
		return -1;
	}

        //boton play
	else if( !(play = al_load_bitmap("play.png")) )
	{

                //al_destroy_event_queue(event_queue);
		return -1;
	}
        //quit
        else if( !(quit = al_load_bitmap("quit.png")) )
	{

                //al_destroy_event_queue(event_queue);
		return -1;
	}
        //restart
        else if( !(restart = al_load_bitmap("restart.png")) )
	{

                al_destroy_event_queue(event_queue);
		return -1;
	}
        //load
        else if( !(load = al_load_bitmap("load.png")) )
	{
		fprintf(stderr,"Unable to load max score\n");
               // al_destroy_bitmap(display_background);
                //al_destroy_bitmap(play);
               // al_destroy_bitmap(quit);
               // al_destroy_bitmap(restart);
	//	al_uninstall_system();
		//al_shutdown_image_addon();
                //al_destroy_event_queue(event_queue);
		return -1;
	}
        //rules
        else if( !(rules = al_load_bitmap("rules.png")) )
	{

                //al_destroy_event_queue(event_queue);
		return -1;
	}
        //settings
        else if( !(settings = al_load_bitmap("settings.png")) )
	{


                //al_destroy_event_queue(event_queue);
		return -1;
	}
	//level1
        else if( !(level1 = al_load_bitmap("level1.png")) )
	{

                al_destroy_event_queue(event_queue);
		return -1;
	}

	//level2
        else if( !(level2 = al_load_bitmap("level2.png")) )
	{

                al_destroy_event_queue(event_queue);
		return -1;
	}

	//level3
        else if( !(level3 = al_load_bitmap("level3.png")) )
	{

                al_destroy_event_queue(event_queue);
		return -1;
	}
        //menu
        else if( !(menu = al_load_bitmap("menu.png")) )
	{

                al_destroy_event_queue(event_queue);

		return -1;
	}
	   else if( !(setting02 = al_load_bitmap("setting2.png")) )
	{

                al_destroy_event_queue(event_queue);

		return -1;
	}
	   else if( !(loadgame0 = al_load_bitmap("loadgame.png")) )
	{

                al_destroy_event_queue(event_queue);

		return -1;
	}


	else if( !(back2 = al_load_bitmap("back2.jpg")) )
	{

		return -1;
	}

	else if( !(back3 = al_load_bitmap("back3.jpg")) )
	{

                al_destroy_event_queue(event_queue);
		return -1;
	}


        else if( !(controles = al_load_bitmap("rules2.png")) )
	{

               // al_destroy_event_queue(event_queue);
		return -1;
	}

	    else if( !(fullscreen = al_load_bitmap("fs.png")) )
	{

               // al_destroy_event_queue(event_queue);
		return -1;
	}
	   else if( !(window = al_load_bitmap("812.png")) )
	{

               // al_destroy_event_queue(event_queue);
		return -1;
	}
	  else if( !(fullwindow = al_load_bitmap("8f.png")) )
	{

               // al_destroy_event_queue(event_queue);
		return -1;
	}
	else if( !(slider0 = al_load_bitmap("sl0.png")) )
	{

               // al_destroy_event_queue(event_queue);
		return -1;
	}
	else if( !(slider1 = al_load_bitmap("sl1.png")) )
	{

               // al_destroy_event_queue(event_queue);
		return -1;
	}
	else if( !(slider2 = al_load_bitmap("sl2.png")) )
	{

               // al_destroy_event_queue(event_queue);
		return -1;
	}
	else if( !(slider3 = al_load_bitmap("sl3.png")) )
	{

               // al_destroy_event_queue(event_queue);
		return -1;
	}
	else if( !(slider4 = al_load_bitmap("sl4.png")) )
	{

               // al_destroy_event_queue(event_queue);
		return -1;
	}
	else if( !(slider5 = al_load_bitmap("sl5.png")) )
	{

               // al_destroy_event_queue(event_queue);
		return -1;
	}
        //Inicializo display
	else if( !(display = al_create_display(WIDTH_DIS,HEIGHT_DIS)) )
	{
		fprintf(stderr,"Unable to create display\n");

                al_destroy_event_queue(event_queue);
		return -1;
	}



        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_mouse_event_source());



        config_menu();

        while (!close_display)
        {
            ALLEGRO_EVENT evento;   //variable events
            if (al_get_next_event(event_queue, &evento))
            {
                if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //display
                    close_display = true;
                if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                {
                    if ((evento.mouse.x >= COL1) && (evento.mouse.x <= FINCOL1) )   //columna
                    {

                        if ((evento.mouse.y >= HEIGHT_SYMS) && (evento.mouse.y <= HEIGHT_SYMS*2))
                        {
                           *pevento++ = PLAY; // boton play

                           close_display = true;
                           #if DEBUG
                            game();break;
                            #endif
                        }


                        //Button rules

                        //Instrucciones
                        if ((evento.mouse.y >= (HEIGHT_SYMS*2 + 50)) && (evento.mouse.y <= ((HEIGHT_SYMS*2 + 50) + HEIGHT_SYMS)))
                        {


                          *pevento++ = RULES;
                           al_flip_display();

                           rule_menu();
                            rules2 = true;

                            #if DEBUG
                            printf("Button rules\n");
                            #endif







                        }

                    }

                    if ((evento.mouse.x >= COL2) && (evento.mouse.x <= FINCOL2) )   //columna
                    {
                        //Button restart

                        if ((evento.mouse.y >= HEIGHT_SYMS) && (evento.mouse.y <= HEIGHT_SYMS*2))
                        {


                           *pevento++ = SETTINGS;
                           al_flip_display();
                        back02 = true;
                        setting_menu();



                           #if DEBUG
                            printf("Button SETTINGS\n");
                            #endif
                        }
                        //Boton load


                        if ((evento.mouse.y >= (HEIGHT_SYMS*2 + 50)) && (evento.mouse.y <= ((HEIGHT_SYMS*2 + 50) + HEIGHT_SYMS)))
                        {


                            *pevento++ = LOAD;
                           al_flip_display();
                        back03 = true;
                        load_menu();

                            #if DEBUG
                            printf("Button LOAD\n");
                            #endif


                        }

                    }

                     //Button quit

                        //display
                    if ((evento.mouse.x >= COL1) && (evento.mouse.x <= FINCOL2+270) )   //columna
                    {

                      if ((evento.mouse.y >= (HEIGHT_SYMS*3.1 + 100)) && (evento.mouse.y <= ((HEIGHT_SYMS*3.1 + 100) + HEIGHT_SYMS))
                          )
                        {
                            *pevento++ = QUIT;
                            close_display = true;
                            #if DEBUG
                            printf("Button EXIT\n");
                            #endif
                        }
                    }
                     if ((evento.mouse.x >= COL1) && (evento.mouse.x <= FINCOL1) )   //columna
                    {

                      if ((evento.mouse.y >= (HEIGHT_SYMS*1+45  )) && (evento.mouse.y <= ((HEIGHT_SYMS*1+45 ) + HEIGHT_SYMS))
                          )
                        {

                         al_draw_scaled_bitmap(window,
                                              0,0, al_get_bitmap_width(window),al_get_bitmap_height(window),COL1,HEIGHT_SYMS*1 + 100 ,500,120, 0);

                            *pevento++ = FS;
                         al_flip_display();
                            #if DEBUG
                            printf("Button window\n");
                            #endif
                        }
                    }
                    if ((evento.mouse.x >= COL2) && (evento.mouse.x <= FINCOL2) )   //columna
                    {

                      if ((evento.mouse.y >= (HEIGHT_SYMS*1+45  )) && (evento.mouse.y <= ((HEIGHT_SYMS*1+45 ) + HEIGHT_SYMS))
                          )
                        {

                            al_draw_scaled_bitmap(fullscreen,
                                              0,0, al_get_bitmap_width(fullscreen),al_get_bitmap_height(fullscreen),COL1,HEIGHT_SYMS*1 + 100 ,500,120, 0);

                            *pevento++ = windows;
                            al_flip_display();

                            #if DEBUG
                            printf("Button FS\n");
                            #endif
                        }
                    }


                      if ((evento.mouse.y >= (HEIGHT_SYMS*3+ 5 )) && (evento.mouse.y <= ((HEIGHT_SYMS*3-20 ) + HEIGHT_SYMS)))
                        {
                      if ((evento.mouse.x >= COL2-20) && (evento.mouse.x <= COL2+20) )   //columna
                        {
                              al_draw_scaled_bitmap(slider1,0,0, al_get_bitmap_width(slider1),al_get_bitmap_height(slider1),COL1,HEIGHT_SYMS*3 + 5 ,500,120, 0);


                            *pevento++ = slider1;
                            al_flip_display();
                            #if DEBUG
                            printf("Button slider1\n");
                            #endif
                        }

                          if ((evento.mouse.x >= COL2+21) && (evento.mouse.x <= COL2+61) )   //columna
                        {

              al_draw_scaled_bitmap(slider2,0,0, al_get_bitmap_width(slider2),al_get_bitmap_height(slider2),COL1,HEIGHT_SYMS*3 + 5 ,500,120, 0);

                            *pevento++ = slider2;
                            al_flip_display();
                            #if DEBUG
                            printf("Button slider2\n");
                            #endif
                        }
                        if ((evento.mouse.x >= COL2+62) && (evento.mouse.x <= COL2+102) )   //columna
                        {


           al_draw_scaled_bitmap(slider3,0,0, al_get_bitmap_width(slider3),al_get_bitmap_height(slider3),COL1,HEIGHT_SYMS*3 + 5 ,500,120, 0);

                            *pevento++ = slider3;
                            al_flip_display();
                            #if DEBUG
                            printf("Button slider3\n");
                            #endif
                        }
                        if ((evento.mouse.x >= COL2+103) && (evento.mouse.x <= COL2+143) )   //columna
                        {


              al_draw_scaled_bitmap(slider4,0,0, al_get_bitmap_width(slider4),al_get_bitmap_height(slider4),COL1,HEIGHT_SYMS*3 + 5 ,500,120, 0);


                            *pevento++ = slider4;
                            al_flip_display();
                            #if DEBUG
                            printf("Button slider4\n");
                            #endif
                        }
                    if ((evento.mouse.x >= COL2+144) && (evento.mouse.x <= COL2+184) )   //columna
                        {


              al_draw_scaled_bitmap(slider5,0,0, al_get_bitmap_width(slider5),al_get_bitmap_height(slider5),COL1,HEIGHT_SYMS*3 + 5 ,500,120, 0);


                            *pevento++ = slider5;
                            al_flip_display();
                            #if DEBUG
                            printf("Button slider5\n");
                            #endif
                        }
















                    }

                }



         if (rules2 == true||back02 == true||back03 == true)

                {
                  if (evento.type ==ALLEGRO_EVENT_MOUSE_BUTTON_UP)//rule中建立按鍵功能
                            {


                               if (evento.mouse.x >= WIDTH_DIS-WIDTH_SYMS)
                                    if (evento.mouse.y <= HEIGHT_SYMS)
                                    {
                                      config_menu();
                                    }
                            }

                }


            }





        }


















        al_destroy_bitmap(display_background);
        al_destroy_bitmap(rules);
        al_destroy_bitmap(play);
        al_destroy_bitmap(quit);
        al_destroy_bitmap(restart);
        al_destroy_bitmap(load);
        al_destroy_bitmap(back2);
        al_destroy_bitmap(back3);
        al_destroy_bitmap(settings);
        al_destroy_bitmap(level1);
        al_destroy_bitmap(level2);
        al_destroy_bitmap(level3);
        al_destroy_bitmap(menu);
	    al_shutdown_image_addon();
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        return 0;
}


static void config_menu (void)
{

	//display

        al_clear_to_color(al_map_rgb(0,0,0));

        al_draw_scaled_bitmap(display_background,
						0,0, al_get_bitmap_width(display_background),al_get_bitmap_height(display_background), //image
						0,0,al_get_display_width(display),al_get_display_height(display),
						0);
        //tetris
       // al_draw_scaled_bitmap(tetris,
						//0,0, al_get_bitmap_width(tetris),al_get_bitmap_height(tetris), //imagen
						//0,0,400,100, //a que tamaño queres que se dibuje la imagen
						//0);
        //play
        al_draw_scaled_bitmap(play,
            0,0, al_get_bitmap_width(play),al_get_bitmap_height(play),
            COL1,HEIGHT_SYMS ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION.
            500); //rotacion
        //settings
        al_draw_scaled_bitmap(settings,
            0,0, al_get_bitmap_width(settings),al_get_bitmap_height(settings),
            COL2,HEIGHT_SYMS ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION.
            0); //rotacion

        //load
        al_draw_scaled_bitmap(load,
            0,0, al_get_bitmap_width(load),al_get_bitmap_height(load),
            COL2, HEIGHT_SYMS*2 + 50 ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION. tamano que quiero que se imprima la imagen
            0); //rotacion

        //rules
        al_draw_scaled_bitmap(rules,
            0,0, al_get_bitmap_width(rules),al_get_bitmap_height(rules),
            COL1,HEIGHT_SYMS*2 + 50 ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION.
            0); //rotacion


        //quit
        al_draw_scaled_bitmap(quit,
            0,0, al_get_bitmap_width(quit),al_get_bitmap_height(quit),
            COL1,HEIGHT_SYMS*3.15 + 100 ,WIDTH_SYMS+300,125,  // POSICION.
            0); //rotacion


          //quit
        al_draw_scaled_bitmap(menu,
            0,0, al_get_bitmap_width(menu),al_get_bitmap_height(menu),
            COL1,HEIGHT_SYMS*-0.70 + 100 ,500,120,  // POSICION.
            0); //rotacion




	al_flip_display();
}
static void rule_menu (void)
{
 al_clear_to_color(al_map_rgb(0,0,0));




                            al_draw_scaled_bitmap(controles,
						1,0, al_get_bitmap_width(controles),al_get_bitmap_height(controles), //image
						0,0,al_get_display_width(display),al_get_display_height(display), //image
						0);
                           al_draw_scaled_bitmap(quit,
                                                0,0, al_get_bitmap_width(quit),al_get_bitmap_height(quit),
                                                WIDTH_DIS-WIDTH_CRUZ ,0 ,WIDTH_CRUZ,WIDTH_CRUZ,  // POSICION.
                                                0); //rotacion








al_flip_display();

}
static void setting_menu (void)
{
   al_clear_to_color(al_map_rgb(0,0,0));

	al_draw_scaled_bitmap(quit,
            0,0, al_get_bitmap_width(quit),al_get_bitmap_height(quit),
            WIDTH_DIS-WIDTH_CRUZ ,0 ,WIDTH_CRUZ,WIDTH_CRUZ,  // POSICION.
            0); //rotacion


             al_draw_scaled_bitmap(back2,
						0,0, al_get_bitmap_width(back2),al_get_bitmap_height(back2), //image
						0,0,al_get_display_width(display),al_get_display_height(display), //image
						0);
						al_draw_scaled_bitmap(quit,
                                                0,0, al_get_bitmap_width(quit),al_get_bitmap_height(quit),
                                                WIDTH_DIS-WIDTH_CRUZ ,0 ,WIDTH_CRUZ,WIDTH_CRUZ,  // POSICION.
                                                0); //rotacion

        al_draw_scaled_bitmap(fullwindow,
        0,0, al_get_bitmap_width(fullwindow),al_get_bitmap_height(fullwindow),COL1,HEIGHT_SYMS*1 + 100 ,500,120, 0); //白色底部
        al_draw_scaled_bitmap(setting02,
            0,0, al_get_bitmap_width(setting02),al_get_bitmap_height(setting02),
            COL1,HEIGHT_SYMS*-0.70 + 100 ,500,120,  // POSICION
            0); //rotacion

            al_draw_scaled_bitmap(slider0,0,0, al_get_bitmap_width(slider0),al_get_bitmap_height(slider0),COL1,HEIGHT_SYMS*3 + 5 ,500,120, 0);
             //al_draw_scaled_bitmap(slider1,0,0, al_get_bitmap_width(slider1),al_get_bitmap_height(slider1),COL1,HEIGHT_SYMS*3 + 5 ,500,120, 0);
              //al_draw_scaled_bitmap(slider2,0,0, al_get_bitmap_width(slider2),al_get_bitmap_height(slider2),COL1,HEIGHT_SYMS*3 + 5 ,500,120, 0);
               //al_draw_scaled_bitmap(slider3,0,0, al_get_bitmap_width(slider3),al_get_bitmap_height(slider3),COL1,HEIGHT_SYMS*3 + 5 ,500,120, 0);
               // al_draw_scaled_bitmap(slider4,0,0, al_get_bitmap_width(slider4),al_get_bitmap_height(slider4),COL1,HEIGHT_SYMS*3 + 5 ,500,120, 0);


al_flip_display();
}
static void load_menu (void)
{
 al_clear_to_color(al_map_rgb(0,0,0));




           al_draw_scaled_bitmap(back3,
						0,0, al_get_bitmap_width(back3),al_get_bitmap_height(back3), //image
						0,0,al_get_display_width(display),al_get_display_height(display), //image
						0);
            al_draw_scaled_bitmap(level1,
            0,0, al_get_bitmap_width(level1),al_get_bitmap_height(level1),
            COL2,HEIGHT_SYMS ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION.
            0); //rotacion

            al_draw_scaled_bitmap(level2,
            0,0, al_get_bitmap_width(level2),al_get_bitmap_height(level2),
            COL2, HEIGHT_SYMS*2.5  ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION.
            0); //rotacion

            al_draw_scaled_bitmap(level3,
            0,0, al_get_bitmap_width(level3),al_get_bitmap_height(level3),
            COL2, HEIGHT_SYMS*4  ,WIDTH_SYMS,HEIGHT_SYMS,  // POSICION.
            0); //rotacion



            al_draw_scaled_bitmap(quit,
            0,0, al_get_bitmap_width(quit),al_get_bitmap_height(quit),
            WIDTH_DIS-WIDTH_CRUZ ,0 ,WIDTH_CRUZ,WIDTH_CRUZ,  // POSICION.
            0); //rotacion



            al_draw_scaled_bitmap(loadgame0,
            0,0, al_get_bitmap_width(loadgame0),al_get_bitmap_height(loadgame0),
            COL1,HEIGHT_SYMS*-0.70 + 100 ,500,120,  // POSICION.
            0); //rotacion
al_flip_display();
}


