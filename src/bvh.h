/*
 * bvh.h
 *
 *  Created on: 08/09/2010
 *      Author: taiar
 */

using namespace std;

#ifndef BVH_H_
#define BVH_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "geom.h"

class bvh: public geom
{
  public:
    bvh(int, double);
    ~bvh();
    int getParent(int);
    string getName(int);
    void write(char*);
    int getNextChild(int);
    string nTabs(int);
    posicao getRightPos(posicao);
    void getRightInitialCoordinates(posicao);
    void setInitialPose(posicao);
    void setMotionPosition(posicao);
    void pushMotionToFile(posicao);
    void setHierarchy();

  private:
    ofstream file;
    posicao initialPose;
    posicao lastPose;
    vector<int> parents;
    vector<string> names;
    vector<int> translation;
    vector<int> directSequence;
    ofstream output;
    stringstream hierarchyProfile;
    int nFrames;
    double frameTime;

    int wLCounter;
    int childWatcher;
};

#endif /* BVH_H_ */
