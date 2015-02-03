#include <iostream>
#include <boost/format.hpp>
#include <cstring>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>


#include "lbxcontainer.h"
#include "utilities.h"
#include "tgui2.hpp"
#include "tgui2_widgets.hpp"

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

      tgui::init(main_display);
      tgui::setFont(bif);
      std::vector<std::string> menus;
      std::vector<TGUI_Splitter *> splits;
      std::vector<tgui::TGUIWidget *> filemenus;
      filemenus.push_back(new TGUI_TextMenuItem("Open", 0));
      filemenus.push_back(new TGUI_TextMenuItem("Save", 0));
      filemenus.push_back(new TGUI_TextMenuItem("Whatever", 0));
      menus.push_back("File");
      splits.push_back(new TGUI_Splitter(0, 0, 160, 40, TGUI_VERTICAL, false, filemenus));
      TGUI_MenuBar *main_menu = new TGUI_MenuBar(0, 0, 800, 20, menus, splits);
      TGUI_Button *btn_1 = new TGUI_Button("Got it, close!", 800-220, 600-45 ,200, 25);

      tgui::setNewWidgetParent(nullptr);
      tgui::addWidget(main_menu);
      tgui::setNewWidgetParent(nullptr);
      tgui::addWidget(btn_1);
      tgui::setFocus(btn_1);
      tguiWidgetsSetColors(al_color_name("green"), al_color_name("black"));

      al_start_timer(update_timer);
      al_start_timer(draw_timer);

      while (true) {
         ALLEGRO_EVENT ev;
         al_wait_for_event(tq, &ev);
         tgui::handleEvent(&ev);
         if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
             ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;
         if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;
         if (ev.type == ALLEGRO_EVENT_TIMER) {
            if (ev.timer.source == update_timer) {
               tgui::TGUIWidget *retW = tgui::update();
               if (retW == btn_1) break;
            }
            if (ev.timer.source == draw_timer) {
               redraw = true;
            }
         }
         if (redraw && al_is_event_queue_empty(tq)) {
            tgui::draw();
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


