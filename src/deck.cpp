#include "deck.h"

const std::unordered_map<std::string, Card>& Deck::GetDeck() const {
    return deck_;
}

std::string Deck::GetName() const {
    return name_;
}

void Deck::AddCard(const std::string& q, const std::string& ans) {
    std::string id = name_ + "_" + std::to_string(next_id_++);
    deck_.emplace(id, Card(q, ans));
}

void Deck::LoadCard(const std::string& id, const std::string& q, const std::string& ans, const double status) {
    deck_.emplace(id, Card(q, ans, status));
}

void Deck::RemoveCard(const std::string& q) {
    auto it = deck_.find(q);
    if (it != deck_.end()) {
        deck_.erase(it);
    } 
}
