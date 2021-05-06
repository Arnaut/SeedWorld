#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"


typedef struct UserData //Leo Tripier
{
  gdouble b_size;
  gdouble r_ocean;
  int mwidth;
  int mheight;
  int w_type;

} UserData;

typedef struct UserInterface //Leo Tripier
{
  GtkWindow* window;             // Main window

  GtkButton* start_button;        // Start button
  GtkButton* close_button;       // Close button
  GtkButton* with_seed_button;
  GtkButton* get_seed_button;
  GtkButton* gen_start_button;
  GtkButton* gen_param_button;

  GtkScaleButton* biome_size;
  GtkScaleButton* ratio;

  GtkRadioButton* map_width;
  GtkRadioButton* map_height;
  GtkRadioButton* world;

  GtkButton* back;

  GtkGrid* grid1;
  GtkGrid* grid2;
  GtkGrid* grid3;
  GtkGrid* grid4;

  SDL_Surface* image_surface;    //the map that will be created
  GtkBuilder* builder;           //just to save the builder
  GtkWidget* image;              //the image gtk will display (the map generated)

  UserData* data;

} UserInterface;

// Signal handler for the "clicked" signal of the buttons.
void on_start(GtkButton *button,gpointer ui)//Leo Tripier
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

// Main function.
int main()
{
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Loads the UI description and builds the UI.
    // (Exits if an error occurs.)
    GtkBuilder* builder = gtk_builder_new();
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "interface.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    //Getting the widgets

    //Leo Tripier

    UserData ud=
      {
       .b_size = (gdouble)(rand() / (double)RAND_MAX * 3),
       .r_ocean = (gdouble)((float)rand() / (float)RAND_MAX),
       .mwidth = 2048,
       .mheight = 2048,
       .w_type = (int)(rand() / (double)RAND_MAX * 2),
      };

    UserInterface ui=
      {
       .window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.SeedWorld")),
       .start_button = GTK_BUTTON(gtk_builder_get_object(builder, "start_button")),
       .close_button = GTK_BUTTON(gtk_builder_get_object(builder, "close_button")),
       .with_seed_button = GTK_BUTTON(gtk_builder_get_object(builder, "with_seed_button")),
       .get_seed_button = GTK_BUTTON(gtk_builder_get_object(builder, "get_seed_button")),
       .gen_start_button = GTK_BUTTON(gtk_builder_get_object(builder, "gen_start_button")),
       .gen_param_button = GTK_BUTTON(gtk_builder_get_object(builder, "gen_param_button")),
       .biome_size = GTK_SCALE_BUTTON(gtk_builder_get_object(builder,"biome_size")),
       .ratio = GTK_SCALE_BUTTON(gtk_builder_get_object(builder,"ratio")),
       .map_width = GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"map_width")),
       .map_height = GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"map_height")),
       .world = GTK_RADIO_BUTTON(gtk_builder_get_object(builder,"world")),
       .back = GTK_BUTTON(gtk_builder_get_object(builder,"back")),
       .grid1 = GTK_GRID(gtk_builder_get_object(builder, "grido")),
       .grid2 = GTK_GRID(gtk_builder_get_object(builder, "grido2")),
       .grid3 = GTK_GRID(gtk_builder_get_object(builder, "grido3")),
       .grid4 = GTK_GRID(gtk_builder_get_object(builder, "grido4")),
       .builder = builder,
       .data = &ud,
      };

    // Connects signal handlers.
    //Leo Tripier
    g_signal_connect(ui.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(ui.start_button, "clicked", G_CALLBACK(on_start), &ui);
    g_signal_connect(ui.close_button, "clicked", G_CALLBACK(gtk_main_quit), &ui);
    g_signal_connect(ui.with_seed_button, "clicked", G_CALLBACK(on_with_seed), &ui);
    g_signal_connect(ui.get_seed_button, "clicked", G_CALLBACK(on_get_seed), &ui);
    g_signal_connect(ui.gen_start_button, "clicked", G_CALLBACK(on_gen_start), &ui);
    g_signal_connect(ui.gen_param_button, "clicked", G_CALLBACK(on_gen_param), &ui);
    g_signal_connect(ui.back, "clicked", G_CALLBACK(on_back), &ui);

    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
    }
