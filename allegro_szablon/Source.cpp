#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>

const float FPS = 60;

int main(void) {
	int width =960;
	int height = 736;
	bool render = false;

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

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(width,height);
	if (!display)
		return -1;

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	int kierunek = 0;
	int count = 0, podloga = 669;
	int pom1 = 642, pom2=0;		// pomocnicze pomagaj¹ce wykrywac kolizje
	int posx = 20, posy = 668;
	int posxtlo = 0, posytlo = 0;
	bool moveleft = false, moveright = false; bool moveup = false; bool done = false;
	ALLEGRO_FONT *font44 = al_load_ttf_font("Arial.ttf", 44, 0);
	
	al_flip_display();
	
	while (done!=true) {



		if (posx > 716){			// spadanie za pierwszym schodem
			podloga = 669;
			if (posy > 640){
				pom2 = 720;
			}
			else pom2 = 0;
		}
		if (posy<640 || posx> 716){				// sciana drugiego schoda
			pom1 = 738;
		}
		else if (posy>640){					// pierwszy schodek lewy bok
			pom1 = 642;
		}
		if (posx > 642 && posx < 712){		// podloga na pierwszym schodku
			podloga = 640;
		}
		else if (posx < 642 && posy > 512) // podloga na samym dole // posy--> tutaj bedzie ten element wyzej tymczasowa 550
		{
			podloga = 669;
		}
		if (posy <= 579||posx>=813){				// ustalenie granicy pojscia w prawo nad drugim schodem
			pom1 = 925;
		}
		if (posx>813){								// prawy bok drugiego schoda oraz ustawienie podlogi za schodem 
			podloga = 669;
			if (posy > 579){
				pom2 = 818;
			}
			else pom2 = 0;
		}

		if (posx > 738 && posx < 813){		// podloga na drugim schodku schodku
			podloga = 579;
		}
		///
		/// Do tego momentu jest pierwszy poziom podloga na dole oraz dwa schody dobrze zrobione , ewentualne poprawki kosmetyczne w póŸniejszyc fazach
		///
		if (posy <= 512 && posx < 687 && posx > 115){		/// I wisz¹ca p³aszczyzna 
			podloga = 512;
		}
		if (posy <= 448 && posx < 112 && posx > 20){		/// II wisz¹ca p³aszczyzna 
			podloga = 448;
		}
		if (posy <= 406 && posx < 229 && posx > 164){		/// III wisz¹ca p³aszczyzna 
			podloga = 406;
		}
		if (posy <= 384 && posx < 354 && posx > 259){		/// IV wisz¹ca p³aszczyzna 
			podloga = 384;
		}
		if (posy <= 384 && posx < 619 && posx > 434){		/// V wisz¹ca p³aszczyzna ( liczone od do³u )
			podloga = 384;
		}
		if (posy == 512 && posx < 115){			// spadanie za I plaszczyzna
			podloga = 669;
		}
		if (posy == 448 && posx < 20){			// spadanie za I plaszczyzna
			podloga = 669;
		}

		if (posy < podloga){			// gravity
			posy ++;
		}
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				done = true;
			
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				moveup = true;
				break;
			case ALLEGRO_KEY_LEFT:
				moveleft = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				moveright = true;
				break;
			}
		}
		
		//al_draw_bitmap(tlo, 0, 0, 0);
		//al_flip_display();
		
		if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				done = true;

			switch (ev.keyboard.keycode) {

			case ALLEGRO_KEY_UP:
				moveup = false;
				break;
			case ALLEGRO_KEY_LEFT:
				moveleft = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				moveright = false;
				break;
			}
		}
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			
			count++;
			render = true;	
			if (moveup) {
				posy -= 2;
			}
			if (moveleft) {
				kierunek = 1;
				if (posx > pom2){
					posx -= 2;
				}
			}
			if (moveright) {
				kierunek = 0;
				if (posx < pom1){
					posx += 2;
				}
			}

		}
		if (render && al_is_event_queue_empty(event_queue)){
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(tlo, 0, 0, 0);
			al_draw_textf(font44, al_map_rgb(126, 126, 126), 0, 0, 0, "%i", count);
			al_draw_bitmap(hero, posx, posy, kierunek);
		}
		al_flip_display();
	}
	//al_rest(20.0);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}