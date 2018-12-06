#include <vector>
#include "robot.h"
#include <pthread.h>
#ifndef BUFFER_H
#define BUFFER_H

class Buffer
{
    int size;                     /* Tamanho do buffer */
    std::vector<Robot> positions; /*    Vetor com a posição de cada robô    */
    pthread_mutex_t thread;

  public:
    Buffer();
    int getBufferSize();
    void setBufferSize(int);         /*  Define o tamanho do buffer  */
    void resultFromFont(Robot);      /*  Recebe a posição de cada um dos 3 robôs e as insere no vetor de posicoes    */
    Robot setRobotRealPosition(int); /*  Trata os valores do vetor 'positions' e define a posicao real do robô cuja id é passada como parametro da funcao   */
};

#endif // BUFFER_H
