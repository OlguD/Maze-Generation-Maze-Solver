#include <gtk/gtk.h>
#include "utils/utils.h"
#include <stdio.h>

#define CELL_SIZE 30
#define MAZE_WIDTH 15
#define MAZE_HEIGHT 15
#define DELAY 100 // 0.1 saniye

static int currentX = 0;
static int currentY = 0;
static gboolean solved = FALSE;
int maze[MAZE_WIDTH][MAZE_HEIGHT];

void update_solution(GtkWidget *widget) {
    if (!solved) {
        if (solveMazeStep(maze, currentX, currentY, MAZE_WIDTH - 2, MAZE_HEIGHT - 2)) {
            solved = TRUE;
        } else {
            int nextX = -1, nextY = -1;
            for (int i = 0; i < 4; i++) {
                int newX = currentX + directions[i].x;
                int newY = currentY + directions[i].y;
                if (isValidMove(maze, newX, newY)) {
                    nextX = newX;
                    nextY = newY;
                    break;
                }
            }

            if (nextX != -1 && nextY != -1) {
                currentX = nextX;
                currentY = nextY;
            } else {
                maze[currentX][currentY] = BACKTRACK;
                if (!backtrack(maze, &currentX, &currentY)) {
                    solved = TRUE; // Çözüm bulunamadı
                }
            }
        }
        gtk_widget_queue_draw(widget);
    }
}

void draw_maze(GtkWidget *widget, cairo_t *cr) {
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            switch (maze[x][y]) {
                case WALL:
                    cairo_set_source_rgb(cr, 0, 0, 0); // Siyah (duvar)
                    break;
                case PATH:
                    cairo_set_source_rgb(cr, 1, 1, 1); // Beyaz (yol)
                    break;
                case VISITED:
                    cairo_set_source_rgb(cr, 0, 1, 0); // Yeşil (ziyaret edilmiş)
                    break;
                case BACKTRACK:
                    cairo_set_source_rgb(cr, 1, 0, 0); // Kırmızı (geri izleme)
                    break;
                default:
                    cairo_set_source_rgb(cr, 1, 1, 1); // Beyaz (varsayılan)
                    break;
            }
            cairo_rectangle(cr, x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            cairo_fill(cr);
        }
    }
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    draw_maze(widget, cr);
    return FALSE;
}

static gboolean on_timeout(gpointer user_data) {
    GtkWidget *widget = GTK_WIDGET(user_data);
    update_solution(widget);
    return !solved; // Zamanlayıcıyı çalıştırmayı durdurur
}

void start_solving(GtkWidget *widget) {
    solved = FALSE;
    currentX = 1;  // Başlangıç noktasını (1,1) olarak ayarlayın
    currentY = 1;
    loadMazeFromFile("maze.txt", maze);
    gtk_widget_queue_draw(widget);
    g_timeout_add(DELAY, on_timeout, widget);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *drawing_area;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Maze Solver Visualization");
    gtk_window_set_default_size(GTK_WINDOW(window), MAZE_WIDTH * CELL_SIZE, MAZE_HEIGHT * CELL_SIZE);

    drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    start_solving(drawing_area);

    gtk_widget_show_all(window);
    g_timeout_add(DELAY, on_timeout, drawing_area);
    gtk_main();

    return 0;
}
