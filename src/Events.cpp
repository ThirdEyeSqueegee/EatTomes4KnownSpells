#include "Events.h"

namespace Events {
    OnEquipEventHandler* OnEquipEventHandler::GetSingleton() {
        static OnEquipEventHandler singleton;
        return std::addressof(singleton);
    }

    RE::BSEventNotifyControl OnEquipEventHandler::ProcessEvent(const RE::TESEquipEvent* a_event, RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) {
        if (!a_event) return RE::BSEventNotifyControl::kContinue;

        if (a_event->actor->IsPlayerRef()) {
            if (const auto tome = RE::TESForm::LookupByID<RE::TESObjectBOOK>(a_event->baseObject)) {
                const auto spell = tome->GetSpell();
                if (const auto player = RE::PlayerCharacter::GetSingleton(); player->HasSpell(spell)) {
                    if (const auto level = spell->GetCostliestEffectItem()->baseEffect->GetMinimumSkillLevel()) {
                        const auto current_magicka = player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kMagicka);
                        if (level >= 0 && level < 25) {
                            player->AsActorValueOwner()->SetActorValue(RE::ActorValue::kMagicka, current_magicka + 10.0f);
                        } else if (level >= 25 && level < 50) {
                            player->AsActorValueOwner()->SetActorValue(RE::ActorValue::kMagicka, current_magicka + 20.0f);
                        } else if (level >= 50 && level < 75) {
                            player->AsActorValueOwner()->SetActorValue(RE::ActorValue::kMagicka, current_magicka + 30.0f);
                        } else if (level >= 75 && level < 100) {
                            player->AsActorValueOwner()->SetActorValue(RE::ActorValue::kMagicka, current_magicka + 40.0f);
                        } else {
                            player->AsActorValueOwner()->SetActorValue(RE::ActorValue::kMagicka, current_magicka + 50.0f);
                        }
                    }
                    player->RemoveItem(tome, 1, RE::ITEM_REMOVE_REASON::kRemove, nullptr, nullptr);
                    RE::PlaySound("ITMFoodEat");
                }
            }
        }

        return RE::BSEventNotifyControl::kContinue;
    }

    void OnEquipEventHandler::Register() {
        const auto holder = RE::ScriptEventSourceHolder::GetSingleton();
        holder->AddEventSink(GetSingleton());
        logger::info("Registered equip event handler");
    }
}
