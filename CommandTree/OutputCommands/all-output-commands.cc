#include "all-output-commands.h"

// HintCommand definitions
HintCommand::HintCommand(ostream & out, std::string commandName) : OutputCommand{out, commandName, false} {}

void HintCommand::execute(int multiplier) {
  // DO LATER
  this->dependency << "Default commands:" << endl << endl;

};

