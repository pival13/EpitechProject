/*
** EPITECH PROJECT, 2020
** cpp_d14m_2019 [WSL: Ubuntu]
** File description:
** LittleHand
*/

#include "LittleHand.hpp"

void LittleHand::sortFruitBox(FruitBox &unsorted, FruitBox &lemon, FruitBox &banana, FruitBox &lime)
{
    int i = unsorted.nbFruits();

    for (; i != 0; i--) {
        Fruit *f = unsorted.pickFruit();
        if (dynamic_cast<Lime *>(f)) {
            if (!lime.putFruit(f))
                unsorted.putFruit(f);
        } else if (dynamic_cast<Banana *>(f)) {
            if (!banana.putFruit(f))
                unsorted.putFruit(f);
        } else if (dynamic_cast<Lemon *>(f)) {
            if (!lemon.putFruit(f))
                unsorted.putFruit(f);
        } else
            unsorted.putFruit(f);
    }
}

FruitBox * const *LittleHand::organizeCoconut(Coconut const * const *coconuts)
{
    int nb = 0;
    for (; coconuts[nb] != nullptr; ++nb);

    FruitBox **box;
    if (nb % 6 == 0)
        box = new FruitBox *[nb/6+1];
    else
        box = new FruitBox *[nb/6+2];

    int j = -1;
    for (int i = 0; i != nb; i++) {
        if (i % 6 == 0) {
            ++j;
            box[j] = new FruitBox(6);
        }
        box[j]->putFruit(new Coconut(*coconuts[i]));
    }
    return box;
}
                             
void LittleHand::plugMixer(MixerBase &mixer)
{
    static_cast<Mixer &>(mixer).plug();
}