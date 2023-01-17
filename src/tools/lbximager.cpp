#include <iostream>
#include <fmt/core.h>
#include <fmt/printf.h>
#include <cstring>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>


#include "lbxcontainer.h"
#include "utilities.h"

using std::cout;


int main(int argc, char* argv[])
{
   try {
      if (!al_init()) return 3;
      ALLEGRO_DISPLAY *main_display = al_create_display(800,600);
      ALLEGRO_FONT *bif = al_create_builtin_font();
      ALLEGRO_EVENT_QUEUE *tq = al_create_event_queue();
      ALLEGRO_TIMER *update_timer = al_create_timer(1.0/240);
      ALLEGRO_TIMER *draw_timer = al_create_timer(1.0/60);
      bool redraw = false;

      al_install_keyboard();
      al_install_mouse();
      al_init_primitives_addon();

      al_register_event_source(tq, al_get_keyboard_event_source());
      al_register_event_source(tq, al_get_mouse_event_source());
      al_register_event_source(tq, al_get_display_event_source(main_display));
      al_register_event_source(tq, al_get_timer_event_source(update_timer));
      al_register_event_source(tq, al_get_timer_event_source(draw_timer));

      al_start_timer(update_timer);
      al_start_timer(draw_timer);

      while (true) {
         ALLEGRO_EVENT ev;
         al_wait_for_event(tq, &ev);
         if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
             ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;
         if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;
         if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (ev.timer.source == update_timer) {
            }
            if (ev.timer.source == draw_timer) {
               redraw = true;
            }
         }
         if (redraw && al_is_event_queue_empty(tq)) {
            al_draw_textf(bif, al_color_name("green"),
                          400,
                          300,
                          ALLEGRO_ALIGN_CENTRE,
                          "This should be the viewer's window");
            al_flip_display();
            al_clear_to_color(al_map_rgb_f(0.0,0.0,0.0));
            redraw = false;
         }
      }
   }
   catch(LBXException &e){
   cout << e.fullDescription() << std::endl;
   return (-e.getID());
   }
   catch(std::exception &e){
     cout << "Application terminated abnormally!\n";
     cout << e.what();
     return (-0xDEADDEAD);
   }
   return 0;
}


