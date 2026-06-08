// Joel Adu - Lab 6 custom bullet bitmap

#include "bullet.h"

bullet::bullet()
{
    alive = false;
    srand(time(0));
}

bool bullet::getStatus()
{
    return alive;
}

void bullet::fire()
{
    x = rand() % 615 + 10;
    y = 10;
    alive = true;
}

void bullet::erase_bullet()
{
    al_draw_filled_rectangle(x, y, x + 16, y + 16, al_map_rgb(0, 0, 0));
}

ALLEGRO_BITMAP* createBulletBitmap()
{
    ALLEGRO_BITMAP* bulletBmp = al_create_bitmap(16, 16);

    al_set_target_bitmap(bulletBmp);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // Custom bullet bitmap using 2+ primitives and 2+ colors
    al_draw_filled_circle(8, 8, 7, al_map_rgb(255, 255, 0));
    al_draw_filled_circle(8, 8, 3, al_map_rgb(255, 0, 0));
    al_draw_line(3, 8, 13, 8, al_map_rgb(255, 255, 255), 2);

    return bulletBmp;
}

int bullet::move_bullet(int arrowX, int arrowY, int width, int length, int height)
{
    static ALLEGRO_BITMAP* bulletBmp = createBulletBitmap();

    y++;

    // Draw bullet using bitmap instead of rectangle
    al_draw_bitmap(bulletBmp, x, y, 0);

    if (x > arrowX && x < arrowX + width && y > arrowY && y < arrowY + length)
    {
        al_draw_filled_rectangle(x, y, x + 16, y + 16, al_map_rgb(0, 0, 0));
        alive = false;
        return 1;
    }

    if (y > height)
        alive = false;

    return 0;
}