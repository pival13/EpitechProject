/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** AsteroKreog
*/

#include "AsteroKreog.hpp"

AsteroKreog::AsteroKreog()
{
}

AsteroKreog::~AsteroKreog()
{
}

std::string AsteroKreog::getName() const { return "AsteroKreog"; }

std::string AsteroKreog::beMined(StripMiner *) const { return "Kreogium"; }

std::string AsteroKreog::beMined(DeepCoreMiner *) const { return "Sullite"; }
