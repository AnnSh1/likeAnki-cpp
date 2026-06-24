#pragma once

#include <iostream>
#include <vector>
#include "deck.h"

class Parser {
public:
    void SaveDeck(const Deck& deck);

    Deck LoadDeck(const std::string& deck_name);

    std::vector<std::string> GetDeckList();

    void DeleteDeck(const std::string& deck_name);
};