#include <GdbLab/Factory.h>

#include <iostream>
#include <memory>
#include <vector>

namespace gdbLab
{
StoogePtr Stooge::makeStooge(FamousStooges choice)
{
    switch (choice)
    {
        case FamousStooges::LARRY:
            return std::make_unique<Larry>();
            break;
        case FamousStooges::MOE:
            return std::make_unique<Moe>();
            break;
        case FamousStooges::CURLY: {
            return std::make_unique<Curly>();
        }
        break;

        default:
            break;
    }
    return std::make_unique<RandomGuy>();
}

void Comedy::playFirstAct(const std::vector<int> &choices)
{
    std::vector<StoogePtr> stooges;
    stooges.reserve(choices.size());
    for (auto choice : choices)
    {
        stooges.emplace_back(Stooge::makeStooge(static_cast<FamousStooges>(choice)));
    }

    std::cout << "The Three Stooges present: A Day at the Office!\n\n";

    std::cout << "Boss: (angrily) What do you three think you're doing?! Get to work!\n";
    for (auto &stooge : stooges)
    {
        stooge->slapStick();
    }

    std::cout << "Boss: (frustrated) That's it, you're all fired!\n";
    for (auto &stooge : stooges)
    {
        stooge->slapStick();
    }

    std::cout << "The End.\n";
}

void Comedy::playSecondAct(const std::vector<int> &choices)
{
    std::vector<StoogePtr> stooges;
    stooges.reserve(choices.size());
    for (auto choice : choices)
    {
        stooges.emplace_back(Stooge::makeStooge(static_cast<FamousStooges>(choice)));
    }

    std::cout << "The Three Stooges present:  A Day at the Circus!\n\n";
    for (auto &stooge : stooges)
    {
        stooge->doTrick();
    }

    std::cout << "The End.\n";
}

}  // namespace gdbLab
