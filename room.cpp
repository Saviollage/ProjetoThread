#include "room.h"

Room::Room(Robot _robots[])
{
    for(int i=0; i< 3; i++)
        robots[i] = _robots[i];

    width = 400;    /* Largura da sala de 400 cm */
    height = 300;   /* Altura da sala de 300 cm */
}
