#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <utility>
#include <stdexcept>
#include <cstdlib>

#include "Biquadris/biquadris.h"
#include "Biquadris/biquadris-proxies.h"

#include "CommandTree/command-tree.h"
#include "CommandTree/BoardActionCommands/all-board-action-commands.h"
#include "CommandTree/LevelBlockGenCommands/all-level-block-gen-commands.h"
#include "CommandTree/ManageGameStateCommands/all-manage-game-state-commands.h"
#include "CommandTree/MetaCommands/all-meta-commands.h"
#include "CommandTree/OutputCommands/all-output-commands.h"
#include "CommandTree/VisualEffectCommands/all-visual-effect-commands.h"

// #include "Displays/console-view.h"
// #include "Displays/graphics-view.h"

const int I_LOVE_CS{246};
const std::vector<char> POSSIBLE_TETROMINOES = {'I', 'J', 'L', 'O', 'S', 'Z', 'T'};

int main (int argc, char* argv[]) {
  std::string blockSequenceFile1 = "sequence1.txt";
  std::string blockSequenceFile2 = "sequence2.txt";
  int randomSeed = I_LOVE_CS;
  int initLevelNum = 0;
  bool showGraphicsView = true;
  bool initBonusEnabled = true;

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
    } else if (arg == "-disableBonusFeatures") {
      initBonusEnabled = false;
    }
  }

  std::srand(randomSeed);


  BiQuadris gameEngine{blockSequenceFile1, blockSequenceFile2, initLevelNum, initBonusEnabled};

  // Setting up commandsTree:
  CommandTree commandDecisionTree;


  ManageGameStateProxy manageGameStateProxy{gameEngine};
  VisualEffectProxy visualEffectProxy{gameEngine};
  BoardActionProxy boardActionProxy{gameEngine};
  LevelBlockGenProxy levelBlockGenProxy{gameEngine};

  // ManageGameState commands:
  commandDecisionTree.addCommand(std::make_unique<BonusOnCommand>(manageGameStateProxy, "bonuson"));
  commandDecisionTree.addCommand(std::make_unique<BonusOffCommand>(manageGameStateProxy, "bonusoff"));
  commandDecisionTree.addCommand(std::make_unique<DevOnCommand>(manageGameStateProxy, "devcommandson"));
  commandDecisionTree.addCommand(std::make_unique<DevOffCommand>(manageGameStateProxy, "devcommandsoff"));
  commandDecisionTree.addCommand(std::make_unique<SpareCommand>(manageGameStateProxy, "spare"));
  
  // VisualEffect commands:
  commandDecisionTree.addCommand(std::make_unique<BlindCommand>(visualEffectProxy, "blind"));

  // BoardAction commands:
  commandDecisionTree.addCommand(std::make_unique<LeftCommand>(boardActionProxy, "left"));
  commandDecisionTree.addCommand(std::make_unique<RightCommand>(boardActionProxy, "right"));
  commandDecisionTree.addCommand(std::make_unique<DownCommand>(boardActionProxy, "down"));
  commandDecisionTree.addCommand(std::make_unique<DropCommand>(boardActionProxy, "drop"));
  commandDecisionTree.addCommand(std::make_unique<ClockwiseCommand>(boardActionProxy, "clockwise"));
  commandDecisionTree.addCommand(std::make_unique<CounterClockwiseCommand>(boardActionProxy, "counterclockwise"));
  commandDecisionTree.addCommand(std::make_unique<HoldCommand>(boardActionProxy, "hold"));
  commandDecisionTree.addCommand(std::make_unique<HeavyEffectCommand>(boardActionProxy, "heavy"));
  commandDecisionTree.addCommand(std::make_unique<RestartCommand>(boardActionProxy, "restart"));

  // LevelBlockGen commands:
  commandDecisionTree.addCommand(std::make_unique<LevelUpCommand>(levelBlockGenProxy, "levelup"));
  commandDecisionTree.addCommand(std::make_unique<LevelDownCommand>(levelBlockGenProxy, "leveldown"));
  commandDecisionTree.addCommand(std::make_unique<RandomCommand>(levelBlockGenProxy, "random"));
  commandDecisionTree.addCommand(std::make_unique<NoRandomCommand>(levelBlockGenProxy, "norandom"));
  commandDecisionTree.addCommand(std::make_unique<ForceCommand>(levelBlockGenProxy, "force"));

  for (char tetromino : POSSIBLE_TETROMINOES) {
    commandDecisionTree.addCommand(std::make_unique<ReplaceBlockCommand>(levelBlockGenProxy, std::string{1, tetromino}));
  }
  
  // Meta commands:
  commandDecisionTree.addCommand(std::make_unique<RenameCommand>(commandDecisionTree, "rename"));
  commandDecisionTree.addCommand(std::make_unique<MacroCommand>(commandDecisionTree, "macro"));
  commandDecisionTree.addCommand(std::make_unique<SequenceCommand>(commandDecisionTree, "sequence"));

  // Output commands:
  commandDecisionTree.addCommand(std::make_unique<HintCommand>(std::cout, "hint"));

  DisplayProxy displayProxy{gameEngine};

  // std::shared_ptr<ConsoleView> consoleView = std::make_shared<ConsoleView>(displayProxy);
  // std::shared_ptr<GraphicsView> graphicsView;

  // gameEngine.attach(consoleView);

  // if (showGraphicsView) {
  //   graphicsView = std::make_shared<GraphicsView>(displayProxy);
  //   gameEngine.attach(graphicsView);
  // }

  // Game loop:
  std::string userInput;

  gameEngine.notifyObservers();

  while (std::getline(std::cin, userInput)) {
    try {
      gameEngine.notifyObservers();
      commandDecisionTree.findAndExecute(userInput);
    } catch (std::runtime_error & error) {
      std::cerr << error.what() << std::endl;
    }
  }
}
