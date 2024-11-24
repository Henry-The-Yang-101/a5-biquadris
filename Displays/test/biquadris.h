#ifndef BIQUADRIS_H
#define BIQUADRIS_H

#include <iostream>
#include <vector>
#include <string>
// include board.h when its ready

using namespace std;
using CellCoordinate = pair<int, int>;
using BlockAttributes = pair<vector<CellCoordinate>, char>;
using Grid = vector<vector<char>>;

class BiQuadris {
  //Board board1
  //Board board2

  public:
    BiQuadris(string sequenceFile1 = "sequence1.txt", string sequenceFile2 = "sequence2.txt", bool devMode = false, bool bonusFeatures = true, int randomSeed = 0);
    ~BiQuadris();
};

class BiQuadrisProxy {
  protected:
    BiQuadris & gameEngine;
    BiQuadrisProxy(BiQuadris & gameEngine) : gameEngine{gameEngine} {}
    virtual ~BiQuadrisProxy() = default;
};


#endif
