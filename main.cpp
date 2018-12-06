#include <ctime>
#include "robot.h"
#include "room.h"
#include "source.h"
#include "buffer.h"
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <SFML/Graphics.hpp>
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

    int timeS1, timeS2, timeS3, bufferSize;
    /*  Define as condições iniciais dos robôs  */
    dru.setId(0);
    dru.setLocation(0, 0);
    drudru.setId(1);
    drudru.setLocation(200, 150);
    edru.setId(2);
    edru.setLocation(400, 300);

    
    cout << "Entre com o tempo em MS para a fonte 1 (1000 a 4000): ";
    cin >> timeS1;
    cout << "Entre com o tempo em MS para a fonte 2 (1000 a 4000): ";
    cin >> timeS2;
    cout << "Entre com o tempo em MS para a fonte 3 (1000 a 4000): ";
    cin >> timeS3;

    cout << "Entre com o tamanho do buffer: ";
    cin >> bufferSize;

    /*  Define as condições das fontes    */
    source1->setTime(timeS1);
    source2->setTime(timeS2);
    source3->setTime(timeS3);

    /*  Define a condição de tamanho do buffer  */
    buffer->setBufferSize(bufferSize);

    pthread_t sourceT1, sourceT2, sourceT3;

    const char *sourceM1 = "Iniciando a Thread para Source 1";
    const char *sourceM2 = "Iniciando a Thread para Source 2";
    const char *sourceM3 = "Iniciando a Thread para Source 3";

    int SourceRet1 = pthread_create(&sourceT1, NULL, Source1, (void *)sourceM1);
    if (SourceRet1)
    {
        cout << "Erro na thread para source 1" << endl;
    }

    int SourceRet2 = pthread_create(&sourceT2, NULL, Source1, (void *)sourceM2);
    if (SourceRet2)
    {
        cout << "Erro na thread para source 2" << endl;
    }

    int SourceRet3 = pthread_create(&sourceT3, NULL, Source1, (void *)sourceM3);
    if (SourceRet3)
    {
        cout << "Erro na thread para source 3" << endl;
    }

    /* PARA PARTE GRÁFICA */

    sf::RenderWindow window(sf::VideoMode(500, 400), "Posições Dru, DruDru e Edru");

    sf::CircleShape circleRed(50);   //DRU
    sf::CircleShape circleGreen(50); //DRUDRU
    sf::CircleShape circleBlue(50);  //EDRU

    circleRed.setFillColor(sf::Color(255, 0, 0));
    circleGreen.setFillColor(sf::Color(0, 255, 0));
    circleBlue.setFillColor(sf::Color(0, 0, 255));

    circleRed.setPosition(dru.getX(), dru.getY());
    circleGreen.setPosition(drudru.getX(), drudru.getY());
    circleBlue.setPosition(edru.getX(), edru.getY());

    while (window.isOpen())
    {
        system("clear");

        dru = buffer->setRobotRealPosition(dru.getId());
        drudru = buffer->setRobotRealPosition(drudru.getId());
        edru = buffer->setRobotRealPosition(edru.getId());

        cout << "\nDRU\t\t id: " << dru.getId() << "\t X: " << dru.getX() << "\t Y: " << dru.getY();
        cout << "\nDRUDRUDRU\t id: " << drudru.getId() << "\t X: " << drudru.getX() << "\t Y: " << drudru.getY();
        cout << "\nEDRU\t\t id: " << edru.getId() << "\t X: " << edru.getX() << "\t Y: " << edru.getY();
        cout << "\nTamanho do buffer: " << buffer->getBufferSize();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                // Someone closed the window- bye
                window.close();
        }
        // End user input detection

        // Clear everything from the last run of the while loop
        window.clear();

        circleRed.setPosition(dru.getX(), dru.getY());
        circleGreen.setPosition(drudru.getX(), drudru.getY());
        circleBlue.setPosition(edru.getX(), edru.getY());

        window.draw(circleRed);
        window.draw(circleGreen);
        window.draw(circleBlue);

        // Show everything on the screen
        window.display();
        usleep(50000);
    } // This is the end of the "while" loop

    return 0;
}
