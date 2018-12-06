#include <ctime>
#include "robot.h"
#include "room.h"
#include "source.h"
#include "buffer.h"
#include <cstdio>
#include <unistd.h>
#include <iostream>
using namespace std;

Robot dru; /*  Declaração dos robôs  */
Robot drudru;
Robot edru;

Source *source1 = new Source(1); /*  Declaração das fontes iniciando com suas respectivas ids*/
Source *source2 = new Source(1);
Source *source3 = new Source(1);

Buffer *buffer = new Buffer(); /*  Declaração do buffer    */

void *Source1(void *msg)
{
    cout << endl
         << msg;
    while (true)
    {
        /*  Preenche o buffer com dados sobre os 3 robôs e aguarda o tempo especifico da fonte  */
        buffer->resultFromFont(source1->captureRobotPosition(dru));
        buffer->resultFromFont(source1->captureRobotPosition(drudru));
        buffer->resultFromFont(source1->captureRobotPosition(edru));
        usleep(source1->getTime());
    }
}

void *Source2(void *msg)
{
    cout << endl
         << msg;
    while (true)
    {
        /*  Preenche o buffer com dados sobre os 3 robôs e aguarda o tempo especifico da fonte  */
        buffer->resultFromFont(source2->captureRobotPosition(dru));
        buffer->resultFromFont(source2->captureRobotPosition(drudru));
        buffer->resultFromFont(source2->captureRobotPosition(edru));
        usleep(source2->getTime());
    }
}

void *Source3(void *msg)
{
    cout << endl
         << msg;
    while (true)
    {
        /*  Preenche o buffer com dados sobre os 3 robôs e aguarda o tempo especifico da fonte  */
        buffer->resultFromFont(source3->captureRobotPosition(dru));
        buffer->resultFromFont(source3->captureRobotPosition(drudru));
        buffer->resultFromFont(source3->captureRobotPosition(edru));
        usleep(source3->getTime());
    }
}

int main(int argc, char *argv[])
{
    srand(time(0));

    /*  Define as condições iniciais dos robôs  */
    dru.setId(0);
    dru.setLocation(rand() % 50, rand() % 50);
    drudru.setId(1);
    drudru.setLocation(rand() % 50, rand() % 50);
    edru.setId(2);
    edru.setLocation(rand() % 50, rand() % 50);

    /*  Define as condições das fontes    */
    source1->setTime(1000);
    source2->setTime(2000);
    source3->setTime(4000);

    /*  Define a condição de tamanho do buffer  */
    buffer->setBufferSize(100);

    pthread_t sourceT1, sourceT2, sourceT3;

    const char *sourceM1 = "Iniciando a Thread para Source 1";
    const char *sourceM2 = "Iniciando a Thread para Source 2";
    const char *sourceM3 = "Iniciando a Thread para Source 3";

    int SourceRet1 = pthread_create(&sourceT1, NULL, Source1, (void *)sourceM1);
    if (SourceRet1)
    {
        cout << "Erro na thread para source 1" << endl;
    }
    usleep(5000);

    int SourceRet2 = pthread_create(&sourceT2, NULL, Source1, (void *)sourceM2);
    if (SourceRet2)
    {
        cout << "Erro na thread para source 2" << endl;
    }

    usleep(5000);

    int SourceRet3 = pthread_create(&sourceT3, NULL, Source1, (void *)sourceM3);
    if (SourceRet3)
    {
        cout << "Erro na thread para source 3" << endl;
    }

    while (1)
    {
        system("clear");
        /*  Aloca a posição lida do buffer ja processada em cada robô e mostra a informação*/
        dru = buffer->setRobotRealPosition(dru.getId());
        drudru = buffer->setRobotRealPosition(drudru.getId());
        edru = buffer->setRobotRealPosition(edru.getId());

        cout << "\nDRU\t\t id: " << dru.getId() << "\t X: " << dru.getX() << "\t Y: " << dru.getY();
        cout << "\nDRUDRUDRU\t id: " << drudru.getId() << "\t X: " << drudru.getX() << "\t Y: " << drudru.getY();
        cout << "\nEDRU\t\t id: " << edru.getId() << "\t X: " << edru.getX() << "\t Y: " << edru.getY();
        cout << "\nTamanho do buffer: " << buffer->getBufferSize();
        usleep(4000);
    }

    return 0;
}
