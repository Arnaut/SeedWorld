#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Perlin.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


typedef struct UserData //Leo Tripier
{
  int m;
  int l;
  int s;
  int w;
  int t;
  int c;
  int width;
  int height;
  int seed;
  int w_type;
  int on;

} UserData;

typedef struct UserInterface //Leo Tripier
{
  GtkWindow* window;             // Main window
  GtkFixed* app_screen;
  
  GtkButton* gen_run;
  GtkEntry* seed_text;
  GtkButton* reroll;

  GtkRadioButton* weidth_1;
  GtkRadioButton* weidth_2;
  GtkRadioButton* height_1;
  GtkRadioButton* height_2;

  GtkButton* c_altitude;
  GtkAdjustment* m;
  GtkAdjustment* l;
  GtkAdjustment* s;
  
  GtkButton* c_temperature;
  GtkAdjustment* w;
  GtkAdjustment* t;
  GtkAdjustment* c;

  GtkRadioButton* fairy;
  GtkRadioButton* medieval;
  GtkRadioButton* futuristic;

  GtkToggleButton* on;
  
  GtkImage* img;
  
  UserData data;

} UserInterface;
// Signal handler for the "clicked" signal of the buttons.


void gen_seed(UserInterface* ui)//Arnaut Leyre
{
  srand(time(NULL));
  unsigned int res = (unsigned int) rand();
  char* buff;
  asprintf(&buff,"%d",res);
  gtk_entry_set_text(ui->seed_text,buff);
}

void on(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  UserInterface* i = ui;
  (void)button;
  if(i->data.on==1){ i->data.on = 0;}
  else {i->data.on = 1;}
}


void on_re(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  UserInterface* i = ui;
  (void)button;
  gen_seed(i);
}

void on_t1(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  UserInterface* i = ui;
  (void)button;
  i->data.w_type = 1;
}

void on_t2(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  UserInterface* i = ui;
  (void)button;
  i->data.w_type = 2;
}

void on_t3(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  UserInterface* i = ui;
  (void)button;
  i->data.w_type = 3;
}

void on_w1(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  UserInterface* i = ui;
  (void)button;
  i->data.width = 1024;
}

void on_w2(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  UserInterface* i = ui;
  (void)button;
  i->data.width = 2048;
}

void on_h1(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  UserInterface* i = ui;
  (void)button;
  i->data.height = 1024;
}

void on_h2(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  UserInterface* i = ui;
  (void)button;
  i->data.height = 2048;
}

void on_ca(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  (void) button;
  UserInterface* i = ui;
  i->data.m = gtk_adjustment_get_value(i->m);
  i->data.l = gtk_adjustment_get_value(i->l);
  i->data.s = gtk_adjustment_get_value(i->s);
  float m = (float) i->data.m;
  float l = (float) i->data.l;
  float s = (float) i->data.s;
  i->data.m = (int)(m*100/(m+l+s));
  i->data.l = (int)(l*100/(m+l+s));
  i->data.s = (int)(s*100/(m+l+s));
  i->data.s += 100 - (i->data.m+i->data.l+i->data.s);
  gtk_adjustment_set_value(i->m,(gdouble)i->data.m);
  gtk_adjustment_set_value(i->l,(gdouble)i->data.l);
  gtk_adjustment_set_value(i->s,(gdouble)i->data.s);
}

void on_ct(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  (void) button;
  UserInterface* i = ui;
  i->data.w = gtk_adjustment_get_value(i->w);
  i->data.t = gtk_adjustment_get_value(i->t);
  i->data.c = gtk_adjustment_get_value(i->c);
  float w = (float) i->data.w;
  float t = (float) i->data.t;
  float c = (float) i->data.c;
  i->data.w = (int)(w*100/(w+t+c));
  i->data.t = (int)(t*100/(w+t+c));
  i->data.c = (int)(c*100/(w+t+c));
  i->data.c += 100 - (i->data.w+i->data.t+i->data.c);
  gtk_adjustment_set_value(i->w,(gdouble)i->data.w);
  gtk_adjustment_set_value(i->t,(gdouble)i->data.t);
  gtk_adjustment_set_value(i->c,(gdouble)i->data.c);
}

void on_run(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  on_ca(button,ui);
  on_ct(button,ui);
  UserInterface* i = ui;
  (void)button;
  const char* buff = gtk_entry_get_text(i->seed_text);
  int res = 0;
  int len = gtk_entry_get_text_length(i->seed_text);
  for(int i = 0;i<len;i++)
    {
      res = res *10 + (int)(buff[i] - '0');
    }
  i->data.seed = res;
  srand((unsigned int)res);
  int height = i->data.height;
  int width = i->data.width;
  
  PerlinNoise(height,width,8,2,i->data.m,i->data.l,i->data.s,i->data.w,i->data.t,i->data.c,i->data.w_type,i->data.on);
  char* buf;
  asprintf(&buf,"%i-%i.bmp",width,height);
  gtk_image_set_from_file(i->img,buf);
}


// Main function.
int main()
{
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Loads the UI description and builds the UI.
    // (Exits if an error occurs.)
    GtkBuilder* builder = gtk_builder_new();
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "interfaceV4.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    //Getting the widgets

    //Leo Tripier
    UserData ud=
      {
       .m = 33,
       .l = 33,
       .s = 34,
       .w = 33,
       .t = 33,
       .c = 34,
       .width = 1024,
       .height = 1024,
       .w_type = 3,
       .on = 1,
      };

    //Arnaut Leyre & Leo Tripier
    UserInterface ui=
      {
       .window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.SeedWorld")),
       .app_screen = GTK_FIXED(gtk_builder_get_object(builder, "app_screen")),
       
       .gen_run = GTK_BUTTON(gtk_builder_get_object(builder, "gen_run")),
       .seed_text = GTK_ENTRY(gtk_builder_get_object(builder, "seed_text")),
       .reroll = GTK_BUTTON(gtk_builder_get_object(builder, "reroll")),
       
       .weidth_1 = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "weidth_1")),
       .weidth_2 = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "weidth_2")),
       .height_1 = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "height_1")),
       .height_2 = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "height_2")),

       .c_altitude = GTK_BUTTON(gtk_builder_get_object(builder, "c_altitude")),
       .m = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "m")),
       .l = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "l")),
       .s = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "s")),

       .c_temperature = GTK_BUTTON(gtk_builder_get_object(builder, "c_temperature")),
       .w = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "w")),
       .t = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "t")),
       .c = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "c")),

       .fairy = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "fairy")),
       .medieval = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "medieval")),
       .futuristic = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "futuristic")),

       .on = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "on")),

       .img = GTK_IMAGE(gtk_builder_get_object(builder, "image")),
       .data = ud,
      };

    gen_seed(&ui);
    // Connects signal handlers.
    //Leo Tripier
    g_signal_connect(ui.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //Arnaut Leyre
    g_signal_connect(ui.gen_run, "clicked", G_CALLBACK(on_run), &ui);
    g_signal_connect(ui.reroll, "clicked", G_CALLBACK(on_re), &ui);

    g_signal_connect(ui.c_altitude, "clicked", G_CALLBACK(on_ca), &ui);
    g_signal_connect(ui.c_temperature, "clicked", G_CALLBACK(on_ct), &ui);

    g_signal_connect(GTK_BUTTON(ui.weidth_1), "clicked", G_CALLBACK(on_w1), &ui);
    g_signal_connect(GTK_BUTTON(ui.weidth_2), "clicked", G_CALLBACK(on_w2), &ui);
    g_signal_connect(GTK_BUTTON(ui.height_1), "clicked", G_CALLBACK(on_h1), &ui);
    g_signal_connect(GTK_BUTTON(ui.height_2), "clicked", G_CALLBACK(on_h2), &ui);

     g_signal_connect(GTK_BUTTON(ui.fairy), "clicked", G_CALLBACK(on_t1), &ui);
    g_signal_connect(GTK_BUTTON(ui.medieval), "clicked", G_CALLBACK(on_t2), &ui);
    g_signal_connect(GTK_BUTTON(ui.futuristic), "clicked", G_CALLBACK(on_t3), &ui);

    g_signal_connect(GTK_BUTTON(ui.on), "clicked", G_CALLBACK(on), &ui);

    
    
    // Runs the main loop.
    gtk_main();

    g_object_unref(builder);
    // Exits.
    return 0;
    }
