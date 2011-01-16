/*
 * geom.cpp
 *
 *  Created on: 02/09/2010
 *      Author: taiar
 */

#include "geom.h"

p3D geom::subtrai(p3D p1, p3D p2)
{
  p3D mid;
  int n = 10;
  mid.x = (p1.x - p2.x) / n;
  mid.y = (p1.y - p2.y) / n;
  mid.z = (p1.z - p2.z) / n;
  return mid;
}

double geom::rad2deg(double v)
{
  return v * rad;
}

double geom::deg2rad(double v)
{
  return v / rad;
}

double geom::getNorma(p3D p)
{
  return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

double geom::prodEsc(p3D p, p3D q)
{
  return (double) (p.x * q.x) + (p.y * q.y) + (p.z * q.z);
}

double geom::getAngulo(p3D p, p3D q)
{
  return rad2deg(acos(prodEsc(p, q) / (getNorma(p) * getNorma(q))));
}

void geom::printPonto(p3D pos)
{
  cout << pos.x << " ; " << pos.y << " ; " << pos.z << endl;
}

void geom::calculaMatrizRotacao(rotation r, p3D p, double o)
{
  double c = cos(deg2rad(o));
  double s = sin(deg2rad(o));
  double t = 1 - c;

  r[0] = t * p.x * p.x + c;
  r[1] = t * p.x * p.y - s * p.z;
  r[2] = t * p.x * p.z + s * p.y;
  r[3] = t * p.x * p.y + s * p.z;
  r[4] = t * p.y * p.y + c;
  r[5] = t * p.y * p.z - s * p.x;
  r[6] = t * p.x * p.z - s * p.y;
  r[7] = t * p.y * p.z + s * p.x;
  r[8] = t * p.z * p.z + c;
}

p3D geom::multiplicaRotacao31(rotation r, p3D p)
{
  p3D a;
  a.x = r[0] * p.x + r[1] * p.y + r[2] * p.z;
  a.y = r[3] * p.x + r[4] * p.y + r[5] * p.z;
  a.z = r[6] * p.x + r[7] * p.y + r[8] * p.z;
  return a;
}

p3D geom::normalizaVetor(p3D p)
{
  p3D temp;
  double norma = getNorma(p);

  temp.x = p.x / norma;
  temp.y = p.y / norma;
  temp.z = p.z / norma;

  return temp;

}

void geom::printPosition(posicao pos)
{
  unsigned int i;
  for (i = 0; i < pos.size(); i += 1)
    cout << pos[i].x << " ; " << pos[i].y << " ; " << pos[i].z << endl;
  cout << endl;
}

void geom::printv(double *v, int s)
{
  int i;
  for (i = 0; i < s; i += 1)
    cout << v[i] << " ";
  cout << endl;
}
