#include "source.h"
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>

Source::Source(int valueId)
{
    thread = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&thread);
    id = valueId;
    _time = 0;
    pthread_mutex_unlock(&thread);
}

void Source::setTime(int valueTime) /* Define o tempo de captura da fonte em MS */
{
    if (valueTime > 4000) /* Limita o vamor maximo em 4000ms */
        _time = 4000;
    else if (valueTime < 1000) /*  Limita o valor minimo em 1000ms */
        _time = 1000;
    else
        _time = valueTime;
}

int Source::getTime() /*  Retorna o tempo da fonte em MS */
{
    return _time;
}
int Source::getId() /*  Retorna a ID da fonte */
{
    return id;
}

Robot Source::captureRobotPosition(Robot robot) /*  Captura a posição de cada robô */
{
    srand(time(0));

    double posX, posY;
    pthread_mutex_lock(&thread);

    do
    {
        /*    Faz a verificação de valores validos para a posicao X sendo dentro da sala  */

        posX = robot.getX() + (pow(-1, rand() % 2)) * (rand() % 10); /*  Pega a posição X podendo somar ou subtrair a ela por um valor de 0 a 10   */

    } while (posX < 0 || posX > 400);

    do
    {
        /*    Faz a verificação de valores validos para a posicao Y sendo dentro da sala  */

        posY = robot.getY() + (pow(-1, rand() % 2)) * (rand() % 10); /*  Pega a posição Y podendo somar ou subtrair a ela por um valor de 0 a 10   */

    } while (posY < 0 || posY > 300);

    robot.setLocation(posX, posY); /*  Aloca os valores encontrados para o robo auxiliar   */

    pthread_mutex_unlock(&thread);

    return robot; /*  Retorna o robo com as coorenadas preenchidas*/
}
