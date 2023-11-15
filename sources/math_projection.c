#include "fdf.h"

static void model_transformation(t_coord *c, t_img image)
{
    c->x *= image.cam->zoom;
    c->y *= image.cam->zoom;
    c->z *= image.cam->zoom / image.cam->layerDepth;
    c->x -= (image.map.width * image.cam->zoom / 2);
    c->y -= (image.map.height * image.cam->zoom / 2);
}

static void view_transformation(t_coord *c, double rotationX, double rotationY, double rotationZ)
{
    int temp_x = c->x;

    c->x = temp_x * cos(rotationY) * cos(rotationZ) +
           c->y * sin(rotationX) * sin(rotationY) * cos(rotationZ) -
           c->y * cos(rotationX) * sin(rotationZ) +
           c->z * cos(rotationX) * sin(rotationY) * cos(rotationZ) +
           c->z * sin(rotationX) * sin(rotationZ);
    c->y = temp_x * cos(rotationY) * sin(rotationZ) +
           c->y * sin(rotationX) * sin(rotationY) * sin(rotationZ) +
           c->y * cos(rotationX) * cos(rotationZ) +
           c->z * cos(rotationX) * sin(rotationY) * sin(rotationZ) -
           c->z * sin(rotationX) * cos(rotationZ);
}

static void project_isometric(t_coord *c) 
{
    int temp_x = c->x;
    int temp_y = c->y;

    c->x = (temp_x - temp_y) * cos(DEG_TO_RAD(ISO_ANGLE));
    c->y = -c->z + (temp_x + temp_y) * sin(DEG_TO_RAD(ISO_ANGLE));
}

void project_onto_plane(t_coord *c, t_img image) 
{
    model_transformation(c, image);
    view_transformation(c, image.cam->rotationX, image.cam->rotationY, image.cam->rotationZ);
    project_isometric(c);
    c->x += ((WIDTH + image.cam->xPositionAdjustment) / 2);
    c->y += ((HEIGHT + image.cam->yPositionAdjustment) / 2);
}
