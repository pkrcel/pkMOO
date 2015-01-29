#include <iostream>
#include <boost/format.hpp>
#include <cstring>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>


#include "lbxcontainer.h"
#include "utilities.h"
#include "tgui2.hpp"
#include "tgui2_widgets.hpp"

using std::cout;


int main(int argc, char* argv[])
{
   if (argc < 2) {
        cout << boost::format("\nIncorrect Number of arguments passed: %d\n")
             % (argc - 1) << boost::format("\nUsage: %s SOURCE \n\n")
             % getFileName(argv[0])  << "\t SOURCE - source LBX Archive\n"
             << "\t source LBX Archive must be of the GFX container type\n"
             << std::endl;
        return 1;
   }
   try {
      LBXcontainer myLBX(argv[1]);
      if (myLBX.getType() != LBX_GFX) {
         cout << "\nError: \n"
              << "Cannot run - selected archive is not of GFX Type"
              << std::endl;
         return 2;
    }
   if (!al_init()) return 3;
   ALLEGRO_DISPLAY *main_display = al_create_display(800,600);
   ALLEGRO_FONT *bif = al_create_builtin_font();
   ALLEGRO_EVENT_QUEUE *tq = al_create_event_queue();
   al_install_keyboard();
   al_install_mouse();

   al_register_event_source(tq, al_get_keyboard_event_source());
   al_register_event_source(tq, al_get_display_event_source(main_display));

   while (true) {
      ALLEGRO_EVENT ev;
      al_wait_for_event(tq, &ev);
      if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
          ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;
      if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;
      al_clear_to_color(al_map_rgb_f(0.0,0.0,0.0));
      al_draw_textf(bif, al_color_name("green"),
                    400,
                    400,
                    ALLEGRO_ALIGN_CENTRE,
                    "This should be the viewer's window");
      al_flip_display();
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


