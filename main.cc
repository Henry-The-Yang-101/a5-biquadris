#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <memory>
#include <utility>

#include "Biquadris/biquadris.h"

#include "CommandTree/command-tree.h"
#include "CommandTree/BoardActionCommands/all-board-action-commands.h"
#include "CommandTree/LevelBlockGenCommands/all-level-block-gen-commands.h"
#include "CommandTree/ManageGameStateCommands/all-manage-game-state-commands.h"
#include "CommandTree/MetaCommands/all-meta-commands.h"
#include "CommandTree/OutputCommands/all-output-commands.h"
#include "CommandTree/VisualEffectCommands/all-visual-effect-commands.h"

#include "Displays/console-view.h"
#include "Displays/graphics-view.h"

const int I_LOVE_CS{246};

int main (int argc, char* argv[]) {
  std::string blockSequenceFile1 = "sequence1.txt";
  std::string blockSequenceFile2 = "sequence2.txt";
  int randomSeed = I_LOVE_CS;
  int initLevelNum = 0;
  bool showGraphicsView = true;

  // Process command line arguments
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];

    if (arg == "-text") {
        showGraphicsView = false;
    } else if (arg == "-seed" && i + 1 < argc) {
      i++;
      std::string nextArg = argv[i];
      std::stringstream ss(nextArg);
      ss >> randomSeed;
      if (ss.fail()) {
        randomSeed = I_LOVE_CS;
      }
    } else if (arg == "-scriptfile1" && i + 1 < argc) {
      i++;
      blockSequenceFile1 = argv[i];
    } else if (arg == "-scriptfile2" && i + 1 < argc) {
      i++;
      blockSequenceFile2 = argv[i];
    } else if (arg == "-startlevel" && i + 1 < argc) {
      i++;
      std::string value = argv[i];
      std::stringstream ss(value);
      ss >> initLevelNum;
      if (ss.fail()) {
        initLevelNum = 0;
      }
    }
  }

  std::srand(randomSeed);

  BiQuadris gameEngine{};

  ManageGameStateProxy manageGameStateProxy{gameEngine};
  VisualEffectProxy visualEffectProxy{gameEngine};
  BoardActionProxy boardActionProxy{gameEngine};
  LevelBlockGenProxy levelBlockGenProxy{gameEngine};
  DisplayProxy displayProxy{gameEngine};

  

  std::shared_ptr<ConsoleView> consoleView = std::make_shared<ConsoleView>(displayProxy);
  std::shared_ptr<GraphicsView> graphicsView;

  gameEngine.attach(consoleView);

  if (showGraphicsView) {
    graphicsView = std::make_shared<GraphicsView>(displayProxy);
    gameEngine.attach(graphicsView);
  }

  
}


