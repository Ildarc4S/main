#include <iostream>
#include "hash.hpp"

int main()
{
    const hash::S line = "H";
    std::cout << hash::getHash(line) << std::endl;

    const hash::Ss lines = {
        "hellow",
        "world",
        "hellow",
        "hellow",
        "world" };

    const auto inds = hash::getSameLineIndices(lines.);

    for (const auto& i : inds)
    {
        for (const auto& j : inds)
        {

        }
    }
    std::cout << "well done" << std::endl;
    system("pause");
}
