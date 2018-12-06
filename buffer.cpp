#include "buffer.h"

Buffer::Buffer()
{
    thread = PTHREAD_MUTEX_INITIALIZER;
    size = 0;
}

void Buffer::setBufferSize(int valueSize)
{ /*  Define o tamanho do buffer  */
    size = valueSize;
}

void Buffer::resultFromFont(Robot robot)
{ /*  Recebe a posição de cada um dos 3 robôs e as insere no vetor de posicoes    */

    pthread_mutex_lock(&thread);
    if (positions.size() <= size)
    {
        positions.push_back(robot);
    }
    pthread_mutex_unlock(&thread);
}

Robot Buffer::setRobotRealPosition(int robotId)
{ /*  Trata os valores do vetor 'positions' e define a posicao real de cada robô baseada na media dos valores recebidos   */
    int sumX = 0;
    int sumY = 0;
    int counter = 0;
    Robot *robot = new Robot();

    pthread_mutex_lock(&thread);

    robot->setId(robotId);

    for (int i = 0; i < positions.size(); i++)
    {
        if (positions.at(i).getId() == robotId)
        {
            sumX += positions.at(i).getX(); /*  Pega todas as posicoes X do robo    */
            sumY += positions.at(i).getY(); /*  Pega todas as posicoes Y do robo    */
            counter++;                      /*  Quantidade de robos presente no buffer  */

            positions.erase(positions.begin() + i); /*    Remove do vetor de buffer o robo ja lido    */
                                                    /*  Decrementa i para pode ler a mesma posição do vetor apos a realocação   */
        }
    }
    if (counter != 0)
        robot->setLocation(sumX / counter, sumY / counter); /*  Saindo do laço, ja aloca a média dos valores lidos no robô para saber sua posição real  */

    else
        robot->setLocation(robot->getX(), robot->getY());

    pthread_mutex_unlock(&thread);

    return *robot;
}

int Buffer::getBufferSize()
{
    return positions.size();
}