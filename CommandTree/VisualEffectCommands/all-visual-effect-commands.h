#ifndef ALL_VISUAL_EFFECT_COMMANDS_H
#define ALL_VISUAL_EFFECT_COMMANDS_H

#include "visual-effect-command.h"

class BlindCommand : public VisualEffectCommand {
  public:
    BlindCommand(VisualEffectProxy & biquadrisProxy, std::string commandName);
    void execute(int multiplier) override;
    ~BlindCommand() = default;
};

#endif
