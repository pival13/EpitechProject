/*
** EPITECH PROJECT, 2020
** cpp_d10_2019 [WSL: Ubuntu]
** File description:
** KoalaSteroid
*/

#include "KoalaSteroid.hpp"

KoalaSteroid::KoalaSteroid()
{
}

KoalaSteroid::~KoalaSteroid()
{
}

std::string KoalaSteroid::getName() const { return "KoalaSteroid"; }
std::string KoalaSteroid::beMined(StripMiner *) const { return "Koalite"; }
std::string KoalaSteroid::beMined(DeepCoreMiner *) const { return "Zazium"; }