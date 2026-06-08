// Joel Adu - Lab 6 Collision Timer Modification

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include "arrow.h"
#include "bullet.h"

int main(void)
{
    arrowClass arrow;
    bullet mybullet[10];

    int score = 0;
    int step = 0;
    bool redraw = true;

    const int FPS = 60;
    const int width = 640;
    const int gameHeight = 480;
    const int screenHeight = 520;
    const int timeLimit = 30;

    bool done = false;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_FONT* font = NULL;

    if (!al_init())
        return -1;

    display = al_create_display(width, screenHeight);

    if (!display)
        return -1;

    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();

    font = al_create_builtin_font();

    arrow.create_arrow_bitmap(display);

    al_set_target_bitmap(al_get_backbuffer(display));

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    arrow.drawArrow();
    al_flip_display();

    double startTime = al_get_time();

    al_start_timer(timer);

    while (!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        int timeRemaining = timeLimit - (int)(al_get_time() - startTime);

        if (timeRemaining <= 0)
        {
            done = true;
        }

        if (ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            step++;

            for (int i = 0; i < 10; i++)
            {
                if (!mybullet[i].getStatus())
                {
                    mybullet[i].fire();
                }
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;

            case ALLEGRO_KEY_UP:
                arrow.up();
                break;

            case ALLEGRO_KEY_DOWN:
                arrow.down();
                break;

            case ALLEGRO_KEY_LEFT:
                arrow.left();
                break;

            case ALLEGRO_KEY_RIGHT:
                arrow.right();
                break;
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            // Clear gameplay screen and info bar
            al_clear_to_color(al_map_rgb(0, 0, 0));

            if (arrow.getSpeed() != 0)
            {
                arrow.move_arrow(width, gameHeight);
            }

            arrow.drawArrow();

            for (int i = 0; i < 10; i++)
            {
                score += mybullet[i].move_bullet(
                    arrow.getX(),
                    arrow.getY(),
                    64,
                    64,
                    gameHeight
                );
            }

            // Info area from y = 480 to y = 520
            al_draw_filled_rectangle(0, 480, 640, 520, al_map_rgb(40, 40, 40));

            al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 492, 0,
                "Time: %d", timeRemaining);

            al_draw_textf(font, al_map_rgb(255, 255, 0), 180, 492, 0,
                "Score: %d", score);

            al_draw_textf(font, al_map_rgb(0, 255, 255), 340, 492, 0,
                "Step: %d", step);

            al_flip_display();
        }
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_textf(font, al_map_rgb(255, 255, 255), 200, 240, 0,
        "Game Over! Final Score: %d", score);
    al_flip_display();

    al_rest(4.0);

    al_destroy_font(font);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);

    return 0;
}