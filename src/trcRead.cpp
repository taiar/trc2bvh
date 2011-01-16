/*
 * trcRead.cpp
 *
 *  Created on: 02/09/2010
 *      Author: taiar
 */

#include "trcRead.h"

trc::trc(char* file)
{
  arquivo.open(file);
  if (!arquivo)
    cout << "Arquivo nao encontrado" << endl;
  header = false;
  actNPos = 0;
}

trc::~trc()
{
  arquivo.close();
}

void trc::headerRead()
{
  if (!header)
  {
    char buff[255];
    string linha;
    arquivo >> buff;
    while (strcmp(buff, "OrigNumFrames") != 0)
      arquivo >> buff;
    arquivo >> buff;
    fileData.DataRate = atof(buff);
    arquivo >> buff;
    fileData.CameraRate = atof(buff);
    arquivo >> buff;
    fileData.NumFrames = atof(buff);
    arquivo >> buff;
    fileData.NumMarkers = atof(buff);
    arquivo >> buff;
    strcpy(fileData.Units, buff);
    arquivo >> buff;
    fileData.OrigDataRate = atof(buff);
    arquivo >> buff;
    fileData.OrigDataStartFrame = atof(buff);
    arquivo >> buff;
    fileData.OrigNumFrames = atof(buff);

    arquivo >> buff;
    while (strcmp(buff, "Frame#") != 0)
      arquivo >> buff;

    getline(arquivo, linha);
    getline(arquivo, linha);
    header = true;
  }
}

posicao trc::readPosition()
{
  if (!header)
    headerRead();

  posicao pose(fileData.NumMarkers);

  if (arquivo.eof())
    return pose;

  char buff[255];
  p3D ponto;

  unsigned int i;

  arquivo >> buff; // numero do frame
  arquivo >> buff; // tempo do frame
  pose.clear();

  for (i = 0; i < fileData.NumMarkers; i += 1)
  {
    arquivo >> ponto.x;
    arquivo >> ponto.y;
    arquivo >> ponto.z;
    pose.push_back(ponto);
  }
  actNPos += 1;

  return pose;
}

posicao trc::getPos()
{
  this->readPosition();
  return this->actPos;
}

void trc::printPonto(p3D p)
{
  printf("%lf ; %lf ; %lf\n", p.x, p.y, p.z);
  //cout << p.x << " ; " << p.y << " ; " << p.z << endl;
}
