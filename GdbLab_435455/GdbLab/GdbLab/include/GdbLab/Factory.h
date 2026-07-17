#pragma once
#include <iostream>
#include <memory>
#include <vector>

namespace gdbLab
{
class Stooge;
using StoogePtr = std::unique_ptr<Stooge>;

enum class FamousStooges : uint8_t
{
    LARRY,
    MOE,
    CURLY
};

// NOLINTBEGIN
class Stooge
{
public:
    Stooge() = default;
    Stooge(const Stooge &) = delete;
    Stooge &operator=(const Stooge &) = delete;
    Stooge(Stooge &&) = delete;
    Stooge &operator=(Stooge &&) = delete;
    virtual ~Stooge() = default;

    static StoogePtr makeStooge(FamousStooges choice);
    virtual void slapStick() = 0;
    virtual void doTrick() { std::cout << "Rabbit\n"; };
};

class Larry : public Stooge
{
public:
    void slapStick() override { std::cout << "Larry: poke eyes\n"; }
    void doTrick() override { std::cout << "Larry: balancing act\n"; }
};

class Moe : public Stooge
{
public:
    void slapStick() override { std::cout << "Moe: slap head\n"; }
    void doTrick() override { std::cout << "Moe: juggling\n"; }
};

class Curly : public Stooge
{
public:
    void slapStick() override { std::cout << "Curly: suffer abuse\n"; }
    void doTrick() override { std::cout << "Curly: magic trick\n"; }
};

class RandomGuy : public Stooge
{
public:
    void slapStick() override { std::cout << "RandomGuy: is silent\n"; }
    void doTrick() override { std::cout << "RandomGuy: no trick\n"; }
};

// NOLINTEND
class Comedy
{
public:
    static void playFirstAct(const std::vector<int> &choices);
    static void playSecondAct(const std::vector<int> &choices);
};

}  // namespace gdbLab
