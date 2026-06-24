#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "card.h"

class Deck {
private:
    std::string name_;
    std::unordered_map<std::string, Card> deck_;
    unsigned int next_id_ = 0;
public:
    Deck(const std::string& name) : name_(name) {}

    const std::unordered_map<std::string, Card>& GetDeck() const;

    std::string GetName() const;
    void AddCard(const std::string& q, const std::string& ans);
    void LoadCard(const std::string& id, const std::string& q, const std::string& ans, const double status);
    void RemoveCard(const std::string& q);

    auto begin() const {return deck_.begin();}
    auto end() const {return deck_.end();}

    auto begin() {return deck_.begin();}
    auto end() {return deck_.end();}
};
