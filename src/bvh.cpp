/*
 * bvh.cpp
 *
 *  Created on: 08/09/2010
 *      Author: taiar
 */

#include "bvh.h"

bvh::bvh(int Frames, double rate)
{
  nFrames = Frames;
  frameTime = 1 / rate;

  int p[] =
  { -1, 0, 0, 0, 1, 2, 2, 3, 4, 2, 2, 6, 7, 9, 10, 13, 14, 15, 16 };
  parents.assign(p, p + 19);
  string n[] =
  { "Quadril", "LeftUpLeg", "Peito", "RightUpLeg", "LeftLowLeg", "Peito2",
      "Pescoço", "RightLowLeg", "LeftFoot", "LeftCollar", "RightCollar",
      "Cabeça", "RightFoot", "LeftUpArm", "RightUpArm", "LeftLowArm",
      "RightLowArm", "LeftHand", "RightHand" };
  names.assign(n, n + 19);

  int trad[] =
  { 0, 1, 5, 2, 31, 7, 8, 38, 33, 12, 13, 44, 40, 14, 22, 16, 24, 18, 26 };
  translation.assign(trad, trad + 19);

  int seq[] =
  { 0, 2, 6, 11, 9, 13, 15, 17, 10, 14, 16, 18, 1, 4, 8, 3, 7, 12 };
  directSequence.assign(seq, seq + 17);
}

bvh::~bvh()
{
  file.close();
}

posicao bvh::getRightPos(posicao pos)
{
  unsigned int i;
  posicao newPos;
  for (i = 0; i < translation.size(); i += 1)
    newPos.push_back(pos.at(translation.at(i)));
  return newPos;
}

void bvh::getRightInitialCoordinates(posicao pos)
{
  unsigned int i;
  posicao newPos;
  p3D newPoint;
  for (i = 0; i < pos.size(); i += 1)
  {
    newPoint = subtrai(pos[i], pos[0]);
    if (parents[i] > 0)
    {
      //newPoint = subtrai(newPoint, newPos[parents[i]]);
      newPoint = subtrai(pos[i], pos[parents[i]]);
      //cout << "essa eh " << names[i] << " - " << names[parents[i]] << " " << i << endl;
    }
    newPos.push_back(newPoint);
  }
  this->initialPose = newPos;
  this->lastPose = newPos;
  //return newPos;
}

void bvh::setInitialPose(posicao pos)
{
  //cout << "pose inicial setada" << endl;
  //geom::printPosition(pos);
  this->initialPose = pos;
}

void bvh::setMotionPosition(posicao pos)
{
  unsigned int i;
  posicao newPos;
  p3D newPoint;
  for (i = 0; i < pos.size(); i += 1)
  {
    if(1)
    {
      newPoint = subtrai(pos[i], pos[0]);
      if (parents[i] > 0)
      {
        //newPoint = subtrai(newPoint, newPos[parents[i]]);
        newPoint = subtrai(pos[i], pos[parents[i]]);
        //cout << "essa eh " << names[i] << " - " << names[parents[i]] << " " << i << endl;
      }
      newPos.push_back(newPoint);
    }
    else
    {
      newPoint.x = pos[i].x;
      newPoint.y = pos[i].y;
      newPoint.z = pos[i].z;
    }
  }
  pushMotionToFile(newPos);

}

void bvh::pushMotionToFile(posicao pos)
{
  unsigned int i;
  for (i = 0; i < pos.size(); i += 1)
    file << pos[directSequence[i]].x << " " << pos[directSequence[i]].y
        << " " << pos[directSequence[i]].z << " ";
  file << endl;
}

void bvh::setHierarchy()
{
  hierarchyProfile << "HIERARCHY";
  hierarchyProfile << "\nROOT Quadril";
  hierarchyProfile << "\n{";
  hierarchyProfile << "\n OFFSET  ";
  hierarchyProfile << this->initialPose[0].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[0].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[0].z;
  hierarchyProfile
      << "\n CHANNELS 6 Xposition Yposition Zposition Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n JOINT Peito";
  hierarchyProfile << "\n {";
  hierarchyProfile << "\n   OFFSET   ";
  hierarchyProfile << this->initialPose[2].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[2].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[2].z;
  hierarchyProfile << "\n   CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n   JOINT Pescoço";
  hierarchyProfile << "\n   {";
  hierarchyProfile << "\n     OFFSET   ";
  hierarchyProfile << this->initialPose[6].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[6].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[6].z;
  hierarchyProfile << "\n     CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n     JOINT Cabeça";
  hierarchyProfile << "\n     {";
  hierarchyProfile << "\n       OFFSET   ";
  hierarchyProfile << this->initialPose[11].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[11].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[11].z;
  hierarchyProfile << "\n       CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n       End Site ";
  hierarchyProfile << "\n       {";
  hierarchyProfile << "\n         OFFSET   0.00  3.87  0.00";
  hierarchyProfile << "\n       }";
  hierarchyProfile << "\n     }";
  hierarchyProfile << "\n   }";
  hierarchyProfile << "\n   JOINT LeftCollar";
  hierarchyProfile << "\n   {";
  hierarchyProfile << "\n     OFFSET   ";
  hierarchyProfile << this->initialPose[9].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[9].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[9].z;
  hierarchyProfile << "\n     CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n     JOINT LeftUpArm";
  hierarchyProfile << "\n     {";
  hierarchyProfile << "\n       OFFSET   ";
  hierarchyProfile << this->initialPose[13].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[13].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[13].z;
  hierarchyProfile << "\n       CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n       JOINT LeftLowArm";
  hierarchyProfile << "\n       {";
  hierarchyProfile << "\n         OFFSET   ";
  hierarchyProfile << this->initialPose[15].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[15].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[15].z;
  hierarchyProfile << "\n         CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n         JOINT LeftHand";
  hierarchyProfile << "\n         {";
  hierarchyProfile << "\n           OFFSET   ";
  hierarchyProfile << this->initialPose[17].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[17].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[17].z;
  hierarchyProfile << "\n           CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n           End Site ";
  hierarchyProfile << "\n           {";
  hierarchyProfile << "\n             OFFSET   0.00 -7.00  0.00";
  hierarchyProfile << "\n           }";
  hierarchyProfile << "\n         }";
  hierarchyProfile << "\n       }";
  hierarchyProfile << "\n     }";
  hierarchyProfile << "\n   }";
  hierarchyProfile << "\n   JOINT RightCollar";
  hierarchyProfile << "\n   {";
  hierarchyProfile << "\n     OFFSET  ";
  hierarchyProfile << this->initialPose[10].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[10].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[10].z;
  hierarchyProfile << "\n     CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n     JOINT RightUpArm";
  hierarchyProfile << "\n     {";
  hierarchyProfile << "\n       OFFSET  ";
  hierarchyProfile << this->initialPose[14].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[14].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[14].z;
  hierarchyProfile << "\n       CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n       JOINT RightLowArm";
  hierarchyProfile << "\n       {";
  hierarchyProfile << "\n         OFFSET   ";
  hierarchyProfile << this->initialPose[16].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[16].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[16].z;
  hierarchyProfile << "\n         CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n         JOINT RightHand";
  hierarchyProfile << "\n         {";
  hierarchyProfile << "\n           OFFSET   ";
  hierarchyProfile << this->initialPose[18].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[18].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[18].z;
  hierarchyProfile << "\n           CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n           End Site ";
  hierarchyProfile << "\n           {";
  hierarchyProfile << "\n             OFFSET   0.00 -7.00  0.00";
  hierarchyProfile << "\n           }";
  hierarchyProfile << "\n         }";
  hierarchyProfile << "\n       }";
  hierarchyProfile << "\n     }";
  hierarchyProfile << "\n   }";
  hierarchyProfile << "\n }";
  hierarchyProfile << "\n JOINT LeftUpLeg";
  hierarchyProfile << "\n {";
  hierarchyProfile << "\n   OFFSET   ";
  hierarchyProfile << this->initialPose[1].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[1].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[1].z;
  hierarchyProfile << "\n   CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n   JOINT LeftLowLeg";
  hierarchyProfile << "\n   {";
  hierarchyProfile << "\n     OFFSET   ";
  hierarchyProfile << this->initialPose[4].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[4].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[4].z;
  hierarchyProfile << "\n     CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n     JOINT LeftFoot";
  hierarchyProfile << "\n     {";
  hierarchyProfile << "\n       OFFSET   ";
  hierarchyProfile << this->initialPose[8].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[8].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[8].z;
  hierarchyProfile << "\n       CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n       End Site ";
  hierarchyProfile << "\n       {";
  hierarchyProfile << "\n         OFFSET   0.00 -3.46  0.00";
  hierarchyProfile << "\n       }";
  hierarchyProfile << "\n     }";
  hierarchyProfile << "\n   }";
  hierarchyProfile << "\n }";
  hierarchyProfile << "\n JOINT RightUpLeg";
  hierarchyProfile << "\n {";
  hierarchyProfile << "\n   OFFSET  ";
  hierarchyProfile << this->initialPose[3].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[3].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[3].z;
  hierarchyProfile << "\n   CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n   JOINT RightLowLeg";
  hierarchyProfile << "\n   {";
  hierarchyProfile << "\n     OFFSET   ";
  hierarchyProfile << this->initialPose[7].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[7].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[7].z;
  hierarchyProfile << "\n     CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n     JOINT RightFoot";
  hierarchyProfile << "\n     {";
  hierarchyProfile << "\n       OFFSET   ";
  hierarchyProfile << this->initialPose[12].x;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[12].y;
  hierarchyProfile << "  ";
  hierarchyProfile << this->initialPose[12].z;
  hierarchyProfile << "\n       CHANNELS 3 Zrotation Xrotation Yrotation";
  hierarchyProfile << "\n       End Site ";
  hierarchyProfile << "\n       {";
  hierarchyProfile << "\n         OFFSET   0.00 -3.75  0.00";
  hierarchyProfile << "\n       }";
  hierarchyProfile << "\n     }";
  hierarchyProfile << "\n   }";
  hierarchyProfile << "\n }";
  hierarchyProfile << "\n}";
}

int bvh::getParent(int c)
{
  return this->parents[c];
}

int bvh::getNextChild(int p)
{
  int i;
  //ja estava olhando um filho deste nó
  if (parents[childWatcher] == p)
  {
    for (i = childWatcher; i < (int) parents.size(); i += 1)
    {
      if (parents[childWatcher] == p)
      {
        childWatcher = i;
        return i;
      }
    }
    return -1;
  }
  //estava verificando filhos de um outro nó
  else
  {
    for (i = 0; i < (int) parents.size(); i += 1)
    {
      if (parents[childWatcher] == p)
      {
        childWatcher = i;
        return i;
      }
    }
    return -1;
  }
}

string bvh::nTabs(int c)
{
  string tabs = "\t";
  while (parents[c] > 0)
  {
    tabs = tabs + "\t";
    c = getParent(c);
  }
  return tabs;
}

string bvh::getName(int c)
{
  return this->names[c];
}

void bvh::write(char *campo)
{
  file.open(campo);

  wLCounter = 0;

  file << hierarchyProfile.str() << endl;

  file << "MOTION" << endl;
  file << "Frames:\t" << nFrames << endl;
  file << "Frame Time:\t" << "0.333" << endl;
}
