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
	ALLEGRO_BITMAP *hero2 = NULL;
	ALLEGRO_BITMAP *hero3 = NULL;
	ALLEGRO_BITMAP *hero4 = NULL;
	ALLEGRO_BITMAP *hero5 = NULL;
	ALLEGRO_BITMAP *coin = NULL;
	ALLEGRO_BITMAP *skok = NULL;

	al_init();
	al_init_primitives_addon();
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon
	al_init_image_addon();
	al_install_keyboard();

	timer = al_create_timer(1.0 / FPS);

	tlo = al_load_bitmap("tlo.jpg");
	hero = al_load_bitmap("hero.png");
	hero2 = al_load_bitmap("hero2.png");
	hero3 = al_load_bitmap("hero3.png");
	hero4 = al_load_bitmap("hero4.png");
	hero5 = al_load_bitmap("hero5.png");
	coin = al_load_bitmap("coin.png");
	skok = al_load_bitmap("skok.png");
	//al_convert_mask_to_alpha(coin, al_map_rgb(255, 255, 255));

	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(width,height);
	if (!display)
		return -1;

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	int jump = 0;
	int NOcoin[7];
	for (int i = 0; i < 7; i++){
		NOcoin[i] = 0;
	}
	int pom = 0;
	int liczmonety = 0;
	int frame = 0;
	int kierunek = 0;
	int count = 0, podloga = 669;
	int pom1 = 642, pom2=0;		// pomocnicze pomagaj¹ce wykrywac kolizje z lewej(pom2) i prawej strony (pom1)
	int posx = 20, posy = 668;
	bool moveleft = false, moveright = false; bool moveup = false; bool done = false; bool reset = false;
	ALLEGRO_FONT *font44 = al_load_ttf_font("Arial.ttf", 44, 0);
	
	al_flip_display();
	
	while (done!=true) {
		if (reset){
			jump = 0;
			NOcoin[7];
			for (int i = 0; i < 7; i++){
				NOcoin[i] = 0;
			}
			pom = 0;
			liczmonety = 0;
			frame = 0;
			kierunek = 0;
			count = 0, podloga = 669;
			pom1 = 642, pom2 = 0;
			posx = 20, posy = 668;
			moveleft = false; moveright = false;  moveup = false; done = false; reset = false;
		}

		pom1 = 0; pom2 = 0;
		if (posx > 716){						// spadanie za pierwszym schodem
			podloga = 669;
			if (posy > 640){
				pom2 = 720;
			}
			else pom2 = 0;
		}
		if (posy<640 || posx> 716){				// sciana drugiego schoda
			pom1 = 738;
		}
		else if (posy>640){						// pierwszy schodek lewy bok
			pom1 = 642;
		}
		if (posx > 642 && posx < 712){			// podloga na pierwszym schodku
			podloga = 639;
		}
		else if (posx < 642 && posy > 512)		// podloga na samym dole 
		{
			podloga = 669;
		}
		if (posy <= 579||posx>=813){			// ustalenie granicy pojscia w prawo nad drugim schodem
			pom1 = 925;
		}
		if (posx>813){							// prawy bok drugiego schoda oraz ustawienie podlogi za schodem 
			podloga = 669;
			if (posy > 579){
				pom2 = 818;
			}
			else pom2 = 0;
		}

		if (posx > 738 && posx < 813){			// podloga na drugim schodku schodku
			podloga = 579;
		}

		if (posy <= 512 && posx < 687 && posx > 115){		/// I wisz¹ca p³aszczyzna 
			podloga = 512;
		}
		if (posy > 512 && posy < 570 ){
			if (posx>300){
				pom2 = 705;
			}
			if (posx < 300){
				pom1 = 108;
			}
		}
		if (posy <= 448 && posx < 112 && posx > 20){		/// II wisz¹ca p³aszczyzna 
			podloga = 448;
		}
		if (posy > 448 && posy < 506){
			if (posx>50){
				pom2 = 130;
			}
			if (posx < 50){
				pom1 = 12;
			}
		}
		if (posy <= 406 && posx < 229 && posx > 164){		/// III wisz¹ca p³aszczyzna 
			podloga = 406;
		}
		if (posy > 406 && posy < 464){
			if (posx>165){
				pom2 = 245;
			}
			if (posx < 228){
				pom1 = 157;
			}
		}
		if (posy <= 384 && posx < 354 && posx > 259){		/// IV wisz¹ca p³aszczyzna 
			podloga = 384;
		}
		if (posy > 384 && posy < 443){
			if (posx>300 && posx<400){
				pom2 = 370;
			}
			if (posx < 300 && posx>250){
				pom1 = 252;
			}
		}
		if (posy <= 384 && posx < 619 && posx > 434){		/// V wisz¹ca p³aszczyzna ( liczone od do³u )
			podloga = 384;
		}
		if (posy > 384 && posy < 442){
			if (posx>600){
				pom2 = 637;
			}
			if (posx < 600 && posx > 410){
				pom1 = 427;
			}
		}
		if (posy == 512 && posx < 115){			// spadanie za I plaszczyzna
			podloga = 669;
		}
		if (posy == 448 && posx < 20){			// spadanie za II plaszczyzna
			podloga = 669;
		}

		if (posy < podloga){					// gravity
			posy ++;
		}
		//
		//
		//
		//
		// powy¿ej mapa , ponizej bêd¹ pu³apki
		if (posy >=668 && posy<=670 && posx < 450 && posx > 380){		// pierwsze kolce
			posx = 20,
			posy = 668;

		}
		if (posy >= 512 && posy <= 513 && posx > 354 && posx < 456){		// drugie kolce
			posx = 20,
			posy = 668;

		}
		if (posy >= 405 && posy <= 403 && posx > 150 && posx < 245){		// trzecie kolce // nie dzia³a powód -- niezidentyfikowany
			posx = 20,
			posy = 668;
		}
		//
		//
		//
		// pulapki prawie dzialajo , teraz kolej na monety 
		
		if (posx > 270 && posx < 320 && posy < 670 && posy > 642){
			if (NOcoin[0] == 0){ liczmonety++; }
			NOcoin[0] = 1;
		}
		if (posx > 570 && posx < 620 && posy < 670 && posy > 642){
			if (NOcoin[1] == 0){ liczmonety++; }
			NOcoin[1] = 1;
		}
		if (posx > 389 && posx < 439 && posy < 650  && posy > 597){
			if (NOcoin[2] == 0){ liczmonety++; }
			NOcoin[2] = 1;
		}
		if (posx > 756 && posx < 806 && posy < 589  && posy > 546 ){
			if (NOcoin[3] == 0){ liczmonety++; }
			NOcoin[3] = 1;
		}
		if (posx > 600 && posx < 650 && posy < 515 && posy > 482){
			if (NOcoin[4] == 0){ liczmonety++; }
			NOcoin[4] = 1;
		}
		if (posx > 210 && posx < 260 && posy < 515 && posy > 482){
			if (NOcoin[5] == 0){ liczmonety++; }
			NOcoin[5] = 1;
		}
		if (posx > 290 && posx < 340 && posy < 440 && posy > 354){
			if (NOcoin[6] == 0){ liczmonety++; }
			NOcoin[6] = 1;
		}
		// monet koniec 
		//
		//
		// dojscie do konca :)
		if (posx > 570 && posx < 617 && posy > 360 && posy <= 390){
			done=true;
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
			case ALLEGRO_KEY_R:
				reset = true;
				break;
			}
		}
		
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
				jump = 1;
				posy -= 3;
			}
			else{ jump = 0; }
			if (moveleft) {
				pom = 1;
				kierunek = 1;
				frame = (frame + 3) % 100;
				if (posx > pom2){
					posx -= 2;
				}
			}
			if (moveright) {
				pom = 1;
				frame = (frame + 3) % 100;
				kierunek = 0;
				if (posx < pom1){
					posx += 2;
				}
			}
			else if (!moveright && !moveleft){ pom = 0; }

		}
		if (render && al_is_event_queue_empty(event_queue)){
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(tlo, 0, 0, 0);
			al_draw_textf(font44, al_map_rgb(126, 126, 126), 0, 0, 0, "%i", count);
			al_draw_textf(font44, al_map_rgb(126, 126, 126), 0, 50, 0, "Ilosc monet: %i", liczmonety);
			if (jump == 1){ 
				al_draw_bitmap(skok, posx, posy, kierunek);
			}
			else{
				if (frame == 0 || pom==0){
					al_draw_bitmap(hero, posx, posy, kierunek);
				}
				if (frame > 0 && frame <= 25 && pom==1){
					al_draw_bitmap(hero5, posx, posy, kierunek);
				}
				if (frame > 25 && frame <= 50 && pom == 1){
					al_draw_bitmap(hero4, posx, posy, kierunek);
				}
				if (frame > 50 && frame <= 75 && pom == 1){
					al_draw_bitmap(hero3, posx, posy, kierunek);
				}
				if (frame > 75 && frame < 100 && pom == 1){
					al_draw_bitmap(hero2, posx, posy, kierunek);
				}
			}
			if (NOcoin[0] == 0){ 
				al_draw_bitmap(coin, 300, 675, 0); 
			}
			if (NOcoin[1] == 0){
				al_draw_bitmap(coin, 600, 675, 0);
			}
			if (NOcoin[2] == 0){
				al_draw_bitmap(coin, 419, 630, 0);
			}
			if (NOcoin[3] == 0){
				al_draw_bitmap(coin, 786, 579, 0);
			}
			if (NOcoin[4] == 0){
				al_draw_bitmap(coin, 630, 515, 0);
			}
			if (NOcoin[5] == 0){
				al_draw_bitmap(coin, 240, 515, 0);
			}
			if (NOcoin[6] == 0){
				al_draw_bitmap(coin, 320, 387, 0);
			}
		}
		al_flip_display();
	}
	//al_rest(20.0);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}