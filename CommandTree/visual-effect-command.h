#ifndef VISUAL_EFFECT_COMMAND_H
#define VISUAL_EFFECT_COMMAND_H

#include "command.h"
#include "../Biquadris/biquadris-proxies.h"

class VisualEffectCommand : Command<VisualEffectProxy> {
  VisualEffectCommand(VisualEffectProxy & biquadrisProxy) : Command<VisualEffectProxy>{biquadrisProxy} {}
  virtual ~VisualEffectCommand() = default;
};

#endif
