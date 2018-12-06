#include "robot.h"
#ifndef ROOM_H
#define ROOM_H

class Room
{
private:
  Robot robots[3]; /*  3 Robos presentes na sala   */
  int width;       /*  Largura da sala     */
  int height;      /*  Altura da sala      */

public:
  Room(Robot[]); /* Construtor da classe */
};

#endif // ROOM_H
