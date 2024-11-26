#ifndef VISUAL_EFFECT_COMMAND_H
#define VISUAL_EFFECT_COMMAND_H

#include "../aggregate-command.h"
#include "../../Biquadris/biquadris-proxies.h"

class VisualEffectCommand : public AggregateCommand<VisualEffectProxy> {
  protected:
    VisualEffectCommand(VisualEffectProxy & biquadrisProxy, std::string commandName, bool hasArgs) : 
      AggregateCommand<VisualEffectProxy>{biquadrisProxy, commandName, hasArgs} {}

    virtual ~VisualEffectCommand() = default;
};

#endif
