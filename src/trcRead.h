/*
 * trcRead.h
 *
 *  Created on: 02/09/2010
 *      Author: taiar
 */

using namespace std;

#ifndef TRCREAD_H_
#define TRCREAD_H_

#include <iostream>
#include <fstream>
#include <vector>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "geom.h"

class trc: public geom
{
  public:
    struct
    {
      float DataRate;
      float CameraRate;
      unsigned int NumFrames;
      unsigned int NumMarkers;
      char Units[10];
      float OrigDataRate;
      int OrigDataStartFrame;
      int OrigNumFrames;
    } fileData;

    ifstream arquivo;
    vector<vector<p3D> > mocapData;

    trc(char*);
    ~trc();

    posicao readPosition();
    void headerRead();
    void printPonto(p3D);
    posicao getPos();

  private:
    bool header;
    int actNPos;
    posicao actPos;
};

#endif /* TRCREAD_H_ */
