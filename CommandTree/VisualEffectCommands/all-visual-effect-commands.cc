#include "all-visual-effect-commands.h"

// BlindCommand definitions
BlindCommand::BlindCommand(VisualEffectProxy & biquadrisProxy, std::string commandName) : VisualEffectCommand{biquadrisProxy, commandName, false} {}

void BlindCommand::execute(int multiplier) {
  this->dependency.blindEffect();
}
