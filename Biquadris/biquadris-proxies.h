#include "biquadris.h"

class ManageGameStateProxy : BiQuadrisProxy {
  ManageGameStateProxy(BiQuadris & gameEngine);
  void setBonusFeatures(bool isOn);
  void setDevMode(bool isOn);
  void gameOver();
};

class VisualEffectProxy : BiQuadrisProxy {
  VisualEffectProxy(BiQuadris & gameEngine);
  void blindEffect();
};

class BoardActionProxy : BiQuadrisProxy {
  BoardActionProxy(BiQuadris & gameEngine);
  void moveBlockHorizontal(int multipler);
  void moveBlockDown(int multipler);
  void rotateBlockClockwise(int multipler);
  void rotateBlockCounterClockwise(int multipler);
  void dropBlock(int multipler);
  void holdBlock();
  void restartBoard();
  void heavyEffect();
};

class LevelBlockGenProxy : BiQuadrisProxy {
  LevelBlockGenProxy(BiQuadris & gameEngine);

  void levelUp(int multipler);
  void levelDown(int multipler);
  void enableRandom();
  void disableRandom(string blockSequenceFile);
  void replaceCurrentBlock(char blockType);
  void forceEffect(char blockType);
};
