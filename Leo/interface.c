#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"



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
  int w_type;

} UserData;

typedef struct UserInterface //Leo Tripier
{
  GtkWindow* window;             // Main window
  GtkFixed* app_screen;
  
  GtkButton* gen_run;
  GtkEntry* seed_text;

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
  
  
  SDL_Surface* image_surface;    //the map that will be created
  GtkBuilder* builder;           //just to save the builder
  GtkWidget* image;              //the image gtk will display (the map generated)

  UserData data;

} UserInterface;

// Signal handler for the "clicked" signal of the buttons.

/*void on_start(GtkButton *button,gpointer ui)//Leo Tripier
{
    UserInterface* i = ui;
    (void)button;
    gtk_container_remove(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid1));
    gtk_container_add(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid2));
}

void on_with_seed(GtkButton *button,gpointer ui)//Leo Tripier
{
  UserInterface* i = ui;
  (void)button;
  gtk_container_remove(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid2));
}

void on_get_seed(GtkButton *button,gpointer ui)//Leo Tripier
{
  UserInterface* i = ui;
  (void)button;
  (void)i;
}

void on_gen_start(GtkButton *button,gpointer ui)//Leo Tripier
{
  UserInterface* i = ui;
  (void)button;
  gtk_container_remove(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid2));
  gtk_container_add(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid3));
}

void on_gen_param(GtkButton *button,gpointer ui)//Leo Tripier
{
  UserInterface* i = ui;
  (void)button;
  gtk_container_remove(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid2));
  gtk_container_add(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid4));
}

void on_back(GtkButton* button, gpointer ui)//Leo Tripier
{
  UserInterface* i = ui;
  (void)button;
  gtk_container_remove(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid4));
  gtk_container_add(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid2));
  i->data->b_size = gtk_scale_button_get_value(i->biome_size) / (gdouble)25.0;
  i->data->r_ocean = gtk_scale_button_get_value(i->ratio) / (gdouble)100.0;
}
*/

void on_gen_run(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  UserInterface* i = ui;
  (void)button;
  (void)i;
}

void on_ca(GtkButton *button,gpointer ui)//Arnaut Leyre
{
  (void) button;
  UserInterface* i = ui;
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
       .width = 2048,
       .height = 2048,
       .w_type = 0,
      };

    //Arnaut Leyre & Leo Tripier
    UserInterface ui=
      {
       .window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.SeedWorld")),
       .app_screen = GTK_FIXED(gtk_builder_get_object(builder, "app_screen")),
       
       .gen_run = GTK_BUTTON(gtk_builder_get_object(builder, "gen_run")),
       .seed_text = GTK_ENTRY(gtk_builder_get_object(builder, "seed_text")),
       
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
       
       .data = ud,
      };

    // Connects signal handlers.
    //Leo Tripier
    g_signal_connect(ui.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //Arnaut Leyre
    g_signal_connect(ui.gen_run, "clicked", G_CALLBACK(on_gen_run), &ui);

    g_signal_connect(ui.c_altitude, "clicked", G_CALLBACK(on_ca), &ui);
    g_signal_connect(ui.c_temperature, "clicked", G_CALLBACK(on_ct), &ui);
    
    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
    }
