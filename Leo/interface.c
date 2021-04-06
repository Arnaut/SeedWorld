#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"

typedef struct UserInterface
{
  GtkWindow* window;             // Main window
  GtkButton* start_button;        // Start button
  GtkButton* close_button;       // Close button
  GtkButton* close_button2;
  GtkButton* close_button3;
  GtkButton* with_seed_button;
  GtkButton* get_seed_button;
  GtkButton* gen_start_button;
  GtkButton* gen_param_button;
  //GtkButton* small_close;

  GtkGrid* grid1;
  GtkGrid* grid2;
  GtkGrid* grid3;

  SDL_Surface* image_surface;    //the map that will be created
  GtkBuilder* builder;           //just to save the builder
  GtkWidget* image;              //the image gtk will display (the map generated)

} UserInterface;

// Signal handler for the "clicked" signal of the buttons.
void on_start(GtkButton *button,gpointer ui)
{
    UserInterface* i = ui;
    (void)button;
    gtk_container_remove(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid1));
    gtk_container_add(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid2));
}

void on_with_seed(GtkButton *button,gpointer ui)
{
  UserInterface* i = ui;
  (void)button;
  gtk_container_remove(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid2));
}

void on_get_seed(GtkButton *button,gpointer ui)
{
  UserInterface* i = ui;
  (void)button;
  (void)i;
}

void on_gen_start(GtkButton *button,gpointer ui)
{
  UserInterface* i = ui;
  (void)button;
  gtk_container_remove(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid2));
  gtk_container_add(GTK_CONTAINER(i->window),GTK_WIDGET(i->grid3));
}

void on_gen_param(GtkButton *button,gpointer ui)
{
  UserInterface* i = ui;
  (void)button;
  (void)i;
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
    
    UserInterface ui=
      {
       .window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.SeedWorld")),
       .start_button = GTK_BUTTON(gtk_builder_get_object(builder, "start_button")),
       .close_button = GTK_BUTTON(gtk_builder_get_object(builder, "close_button")),
       .close_button2 = GTK_BUTTON(gtk_builder_get_object(builder, "close_button2")),
       .close_button3 = GTK_BUTTON(gtk_builder_get_object(builder, "close_button3")),
       .with_seed_button = GTK_BUTTON(gtk_builder_get_object(builder, "with_seed_button")),
       .get_seed_button = GTK_BUTTON(gtk_builder_get_object(builder, "get_seed_button")),
       .gen_start_button = GTK_BUTTON(gtk_builder_get_object(builder, "gen_start_button")),
       .gen_param_button = GTK_BUTTON(gtk_builder_get_object(builder, "gen_param_button")),
       .grid1 = GTK_GRID(gtk_builder_get_object(builder, "grido")),
       .grid2 = GTK_GRID(gtk_builder_get_object(builder, "grido2")),
       .grid3 = GTK_GRID(gtk_builder_get_object(builder, "grido3")),
       .builder = builder,
      };




    // Connects signal handlers.
    g_signal_connect(ui.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(ui.start_button, "clicked", G_CALLBACK(on_start), &ui);
    g_signal_connect(ui.close_button, "clicked", G_CALLBACK(gtk_main_quit), &ui);
    g_signal_connect(ui.close_button2, "clicked", G_CALLBACK(gtk_main_quit), &ui);
    g_signal_connect(ui.close_button3, "clicked", G_CALLBACK(gtk_main_quit), &ui);
    g_signal_connect(ui.with_seed_button, "clicked", G_CALLBACK(on_with_seed), &ui);
    g_signal_connect(ui.get_seed_button, "clicked", G_CALLBACK(on_get_seed), &ui);
    g_signal_connect(ui.gen_start_button, "clicked", G_CALLBACK(on_gen_start), &ui);
    g_signal_connect(ui.gen_param_button, "clicked", G_CALLBACK(on_gen_param), &ui);

    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}
