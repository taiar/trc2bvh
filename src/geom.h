/*
 * geom.h
 *
 *  Created on: 02/09/2010
 *      Author: taiar
 */

using namespace std;


#ifndef GEOM_H_
#define GEOM_H_

#include <vector>
#include <iostream>
#include <math.h>

#define rad 57.2957795

typedef struct
{
  double x;
  double y;
  double z;
} p3D;

typedef double rotation[9];

typedef struct vector<p3D> posicao;

class geom
{
  public:
  static p3D subtrai(p3D, p3D);
  static double deg2rad(double);
  static double rad2deg(double);
  static double prodEsc(p3D,p3D);
  static double getNorma(p3D);
  static double getAngulo(p3D, p3D);
  static void calculaMatrizRotacao(rotation, p3D, double);
  static p3D multiplicaRotacao31(rotation, p3D);
  static p3D multiplicaRotacao33(rotation, p3D);
  static p3D normalizaVetor(p3D);

  static void printv(double*, int);
  static void printPonto(p3D);
  static void printPosition(posicao pos);

  private:
};

#endif /* GEOM_H_ */
