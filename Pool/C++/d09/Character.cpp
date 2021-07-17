/*
** EPITECH PROJECT, 2020
** cpp_d09_2019 [WSL: Ubuntu]
** File description:
** Character
*/

#include "Character.hpp"

Character::Character(const std::string &name, int level, const std::string &race, const std::string &clas, int pv, int mp, int str, int stam, int intel, int spi, int agi)
: Range(Character::CLOSE), Name(name), Lvl(level), Race(race), Class(clas), MaxPv(pv), Pv(pv), MaxPower(mp), Power(mp), Strength(str), Stamina(stam), Intelligence(intel), Spirit(spi), Agility(agi)
{
    std::cout << name << " Created" << std::endl;
}

Character::~Character()
{
}

const std::string &Character::getName() const { return Name; }
const std::string &Character::getRace() const { return Race; }
const std::string &Character::getClass() const { return Class; }
int Character::getLvl() const { return Lvl; }
int Character::getPv() const { return Pv; }
int Character::getPower() const { return Power; }
int Character::getStrength() const { return Strength; }
int Character::getStamina() const { return Stamina; }
int Character::getIntelligence() const { return Intelligence; }
int Character::getSpirit() const { return Spirit; }
int Character::getAgility() const { return Agility; }

int Character::CloseAttack()
{
    if (Power < 10) {
        std::cout << Name << " out of power" << std::endl;
        return 0;
    }
    Power -= 10;
    std::cout << Name << " strikes with a wooden stick" << std::endl;
    return 10 + Strength;
}

int Character::RangeAttack()
{
    if (Power < 10) {
        std::cout << Name << " out of power" << std::endl;
        return 0;
    }
    Power -= 10;
    std::cout << Name << " tosses a stone" << std::endl;
    return 5 + Strength;
}

void Character::Heal()
{
    std::cout << Name << " takes a potion" << std::endl;
    Pv += 50;
    if (Pv > MaxPv)
        Pv = MaxPv;
}

void Character::RestorePower()
{
    std::cout << Name << " eats" << std::endl;
    Power += 100;
    if (Power > MaxPower)
        Power = MaxPower;
}

void Character::TakeDamage(int damage)
{
    Pv -= damage;
    if (Pv < 0)
        std::cout << Name << " out of combat" << std::endl;
    else
        std::cout << Name << " takes " << damage << " damage" << std::endl;
}

std::ostream &operator<<(std::ostream &os, Character &c)
{
    os << "Name:\t\t" << c.getName();
    os << "\nLvl:\t\t" << c.getLvl();
    os << "\nClass:\t\t" << c.getClass();
    os << "\nRace:\t\t" << c.getRace();
    os << "\nStrength:\t" << c.getStrength();
    os << "\nStamina:\t" << c.getStamina();
    os << "\nIntelligence:\t" << c.getIntelligence();
    os << "\nSpirit:\t\t" << c.getSpirit();
    os << "\nAgility:\t" << c.getAgility();
    return os;
}