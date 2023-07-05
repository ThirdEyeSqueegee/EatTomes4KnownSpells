#include "Hooks.h"

namespace Hooks {
    std::uintptr_t RestoreActorValue(RE::Actor* a_actor, RE::ActorValue a_actorValue, float a_value) {
        REL::Relocation<decltype(&RestoreActorValue)> func{ RELOCATION_ID(37816, 38455) };
        return func(a_actor, a_actorValue, a_value);
    }
}
