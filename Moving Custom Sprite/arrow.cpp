// Joel Adu - Lab 6 UFO player bitmap

#include "arrow.h"

arrowClass::arrowClass()
{
    speed = 0;
    x = 100;
    y = 100;
    dir = 1;
    score = 0;

    for (int i = 0; i < 4; i++)
    {
        arrow_bmp[i] = NULL;
    }
}

arrowClass::~arrowClass()
{
    for (int i = 0; i < 4; i++)
    {
        al_destroy_bitmap(arrow_bmp[i]);
    }
}

void arrowClass::drawArrow()
{
    al_draw_bitmap(arrow_bmp[getDirection()], getX(), getY(), 0);
}

void arrowClass::create_arrow_bitmap(ALLEGRO_DISPLAY* display)
{
    for (int i = 0; i < 4; i++)
    {
        arrow_bmp[i] = al_create_bitmap(64, 64);

        if (!arrow_bmp[i])
        {
            al_destroy_display(display);
            exit(1);
        }

        al_set_target_bitmap(arrow_bmp[i]);
        al_clear_to_color(al_map_rgb(0, 0, 0));

        float x = 0;
        float y = 0;

        // UFO cannon / antenna
        al_draw_filled_rectangle(x + 29, y + 5, x + 35, y + 20,
            al_map_rgb(120, 120, 120));

        // Blue cockpit
        al_draw_filled_circle(x + 32, y + 24, 12,
            al_map_rgb(0, 180, 255));

        // Purple UFO body
        al_draw_filled_ellipse(x + 32, y + 36, 28, 12,
            al_map_rgb(160, 0, 255));

        // Pink glow
        al_draw_filled_ellipse(x + 32, y + 40, 22, 7,
            al_map_rgb(255, 0, 220));

        // Lights
        al_draw_filled_circle(x + 32, y + 40, 4,
            al_map_rgb(255, 255, 0));

        al_draw_filled_circle(x + 20, y + 39, 3,
            al_map_rgb(0, 255, 100));

        al_draw_filled_circle(x + 44, y + 39, 3,
            al_map_rgb(0, 255, 100));

        // Highlight
        al_draw_line(x + 10, y + 33, x + 54, y + 33,
            al_map_rgb(255, 255, 255), 2);

        // Direction color marker
        switch (i)
        {
        case 0: // Up
            al_draw_filled_triangle(27, 8, 37, 8, 32, 0,
                al_map_rgb(255, 120, 0));
            break;

        case 1: // Right
            al_draw_filled_triangle(55, 27, 55, 37, 63, 32,
                al_map_rgb(255, 120, 0));
            break;

        case 2: // Down
            al_draw_filled_triangle(27, 56, 37, 56, 32, 63,
                al_map_rgb(255, 120, 0));
            break;

        case 3: // Left
            al_draw_filled_triangle(8, 27, 8, 37, 0, 32,
                al_map_rgb(255, 120, 0));
            break;
        }
    }
}

void arrowClass::erase_arrow()
{
    int left = x;
    int top = y;
    int right = x + 64;
    int bottom = y + 64;

    al_draw_filled_rectangle(left, top, right, bottom, al_map_rgb(0, 0, 0));
}

void arrowClass::up()
{
    dir = 0;
    speed++;

    if (speed > MAXSPEED)
        speed = MAXSPEED;
}

void arrowClass::down()
{
    dir = 2;
    speed++;

    if (speed > MAXSPEED)
        speed = MAXSPEED;
}

void arrowClass::left()
{
    dir = 3;
    speed++;

    if (speed > MAXSPEED)
        speed = MAXSPEED;
}

void arrowClass::right()
{
    dir = 1;
    speed++;

    if (speed > MAXSPEED)
        speed = MAXSPEED;
}

int arrowClass::getDirection()
{
    return dir;
}

int arrowClass::getSpeed()
{
    return speed;
}

int arrowClass::getX()
{
    return x;
}

int arrowClass::getY()
{
    return y;
}

void arrowClass::move_arrow(int width, int height)
{
    switch (dir)
    {
    case 0:
        y -= speed;
        break;

    case 1:
        x += speed;
        break;

    case 2:
        y += speed;
        break;

    case 3:
        x -= speed;
        break;
    }

    // Keep UFO inside gameplay area only
    if (x > width - 64)
    {
        x = width - 64;
        speed = 0;
    }

    if (x < 0)
    {
        x = 0;
        speed = 0;
    }

    if (y > height - 64)
    {
        y = height - 64;
        speed = 0;
    }

    if (y < 0)
    {
        y = 0;
        speed = 0;
    }
}