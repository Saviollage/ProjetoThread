#include <pthread.h>
#include "robot.h"
#include "buffer.h"
#ifndef SOURCE_H
#define SOURCE_H

class Source
{
    int id;    /* Id da fonte */
    int _time; /*  Tempo de captura de cada fonte */
    pthread_mutex_t thread;

  public:
    Source(int);       /*  Construtor  */
    void setTime(int); /* Define o tempo de captura da fonte em MS */
    int getTime();     /*  Retorna o tempo da fonte em MS */
    int getId();       /*  Retorna a id da fonte*/

    Robot captureRobotPosition(Robot); /*  Captura a posição de cada robô  */
};

#endif // SOURCE_H
