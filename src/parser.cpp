#include <iostream>
#include <filesystem>
#include <fstream>
#include "parser.h"

void Parser::SaveDeck(const Deck& deck) {
    if (!std::filesystem::exists("cards")) {
        std::filesystem::create_directory("cards");
    }
    std::string deck_name = deck.GetName();
    std::string name_file = "cards/" + deck_name + ".txt";
    std::ofstream file(name_file);  

    
    int i = 0;
    for (const auto& [id, card] : deck.GetDeck()) {
        i++;
        file << deck_name << "_" << i << " ";
        file << card.GetQuestion() << " ";
        file << card.GetAnswer() << " ";
        file << card.GetStatus() << "\n";
    }
}

Deck Parser::LoadDeck(const std::string& deck_name) {
    std::string name_file = "cards/" + deck_name + ".txt";
    std::ifstream file(name_file);  
    Deck deck(deck_name);   

    std::string id;
    std::string question, answer;
    double status;
    while (file >> id >> question >> answer >> status) {
        deck.LoadCard(id, question, answer, status);
    }
    return deck;
}

std::vector<std::string> Parser::GetDeckList() {
    std::vector<std::string> list;
    auto folder = std::filesystem::directory_iterator("cards");
    if (std::filesystem::is_empty("cards")) {
        return list;
    }
    for (auto file : folder) {
        if (file.is_regular_file() && file.path().extension() == ".txt") {
            std::string card_name = file.path().stem().string();
            list.push_back(card_name);
        }
    }
    return list;
}

void Parser::DeleteDeck(const std::string& deck_name) {
    if (std::filesystem::exists("cards/" + deck_name + ".txt")) {
        std::filesystem::remove("cards/" + deck_name + ".txt");
    }
}