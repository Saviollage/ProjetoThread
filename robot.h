#ifndef ROBOT_H
#define ROBOT_H

class Robot
{

private:
  int id;            /*  Id do Robô */
  double posX, posY; /*  Posições X e Y do robo */

public:
  Robot();         /* Construtor da classe */
  int getId();     /*  Retorna o id do robo */
  double getX();   /*  Retorna a posição X do robô */
  double getY();   /*  Retorna a posição Y do robô */
  void setId(int); /* Define a id do robô */

  void setLocation(double, double); /* Define a posição X e Y do robô */
};

#endif // ROBOT_H
