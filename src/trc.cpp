#include <iostream>
#include <fstream>

#include "trcRead.h"
#include "geom.h"
#include "bvh.h"

using namespace std;

int main()
{
  p3D a, b, c, d;
  rotation r;

  a.x = 44.4484;
  a.y = 41.5590;
  a.z = -0.1296;

  d = a;
  a = geom::normalizaVetor(a);
  d = geom::subtrai(d, a);

  geom::printPonto(d);

  /*a.x = 1;
  a.y = 0;
  a.z = 0;

  b.x = 1;
  b.y = 1.15470054/2;
  b.z = 0;*/

  b.x = 1;
  b.y = 1;
  b.z = 1;

  b = geom::normalizaVetor(b);

  geom::calculaMatrizRotacao(r, d, geom::getAngulo(d,b));
  geom::printv(r,9);
  c = geom::multiplicaRotacao31(r,d);
  //c = geom::normalizaVetor(c);
  geom::printPonto(c);

  return 0;

  string buff;
  char name[40] = "../bvh/ActorF_TPose.trc\0";
  trc inicio(name);
  posicao pos;
  pos = inicio.readPosition();

  bvh starte(inicio.fileData.OrigNumFrames, inicio.fileData.DataRate);
  pos = starte.getRightPos(pos);
  starte.getRightInitialCoordinates(pos);
  starte.setHierarchy();

  starte.write("../../../teste");

  int i;
  for (i = 0; i < inicio.fileData.OrigNumFrames; i += 1)
    starte.setMotionPosition(starte.getRightPos(inicio.readPosition()));

  return 0;
}
