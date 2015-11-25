#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>

const float FPS = 60;

int main(void) {
	int width = 736;
	int height = 960;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *tlo = NULL;
	ALLEGRO_BITMAP *hero = NULL;

	al_init();
	al_init_primitives_addon();
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon
	al_init_image_addon();
	al_install_keyboard();

	timer = al_create_timer(1.0 / FPS);

	tlo = al_load_bitmap("tlo.jpg");
	hero = al_load_bitmap("hero.png");
	//al_convert_mask_to_alpha(hero, al_map_rgb(255, 255, 255));

	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(disp_data.width, disp_data.height);
	if (!display)
		return -1;

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	
	int count = 0;
	int posx = 20, posy = 668;
	int posxtlo = 0, posytlo = 0;
	bool moveleft = false, moveright = false; bool moveup = false; bool done = false;
	ALLEGRO_FONT *font44 = al_load_ttf_font("Arial.ttf", 44, 0);
	
	al_flip_display();
	
	while (done!=true) {
		
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				done = true;
			
			switch (ev.keyboard.keycode) {

			case ALLEGRO_KEY_LEFT:
				moveleft = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				moveright = true;
				break;
			}
		}
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			count++;
			al_draw_textf(font44, al_map_rgb(126, 126, 126), 0, 0, 0, "%i", count);

			
				if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
					posy -= 20;
				}
				if (moveleft) {
					if (posx > 0){
						posx -= 2;
					}
				}
				if (moveright) {
					if (posx < 736){
						posx += 2;
					}
				}
			
			al_draw_bitmap(hero, posx, posy, 0);
			al_flip_display();
			
		}
		//al_draw_bitmap(tlo, 0, 0, 0);
		//al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				done = true;

			switch (ev.keyboard.keycode) {

			case ALLEGRO_KEY_LEFT:
				moveleft = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				moveright = false;
				break;
			}
		}
	}



	//al_rest(20.0);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}