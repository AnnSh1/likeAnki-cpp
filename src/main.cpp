#include <iostream>
#include <vector>
#include <string>
#include "controller.h"
#include "parser.h"

void ShowMenu() {
    std::cout << "\n=== LIKE ANKI ===\n";
    std::cout << "Select an option:\n";
    std::cout << "1. Start review\n";
    std::cout << "2. Create new deck\n";
    std::cout << "3. Delete deck\n";
    std::cout << "4. Show all decks\n";
    std::cout << "5. Exit\n";
    std::cout << "Choice: \n";
}

void StartGame(Parser& parser) {
    std::vector<std::string> listDecks = parser.GetDeckList();
    if (listDecks.empty()) {
        std::cout << "<<< No decks. >>>";
        return;
    }

    std::cout << "Select a deck:\n";
    int i = 1;
    for (const auto& deck : listDecks) {
        std::cout << i++ << ". " << deck << "\n";
    }
    int num;
    std::cin >> num;
    if (num < 1 || num > i) {
        std::cout << "No such deck.\n";
        return;
    }
    std::string deck_name = listDecks[num - 1];
    Deck deck = parser.LoadDeck(deck_name);

    Controller game(deck);
    game.StartGame();

    parser.SaveDeck(deck);
    std::cout << "Progress saved!";
}

void CreateDeck(Parser& parser) {
    std::cout << "Enter deck name:\n";
    std::string deck_name;
    std::cin >> deck_name;
    Deck new_deck(deck_name);

    std::cout << "Enter cards as Question, Answer. Enter empty question to finish.\n";

    std::cin.ignore();

    std::string question;
    std::string answer;
    while (true) {
        std::cout << "Question: ";
        std::getline(std::cin, question);
        if (question.empty()) break;

        std::cout << "Answer: ";
        std::getline(std::cin, answer);
        if (answer.empty()) break;

        new_deck.AddCard(question, answer);
        std::cout << "Card added!\n";
    }

    parser.SaveDeck(new_deck);
    std::cout << "<<< Deck: " << deck_name << " saved! >>>";
}

void DeleteDeck(Parser& parser) {
    std::vector<std::string> listDecks = parser.GetDeckList();
    if (listDecks.empty()) {
        std::cout << "<<< No decks to delete. >>>";
        return;
    } else {
        int i = 1;
        for (const auto& deck : listDecks) {
            std::cout << i++ << ". " << deck << "\n";
        }
        std::cout << "Select a deck to delete:\n";
        int num = 1;
        std::cin >> num;
        if (num < 1 || num > i) {
            std::cout << "No such deck.\n";
            return;
        } 
        std::string deck_name = listDecks[num - 1];
        parser.DeleteDeck(deck_name);
        std::cout << "Deck deleted!\n";
    }
}

void ShowAllDecks(Parser& parser) {
    std::vector<std::string> listDecks = parser.GetDeckList();
    if (listDecks.empty()) {
        std::cout << "<<< Your folder is empty, you need to create a deck. >>>";
        return;
    }
    int i = 1;
    for (const auto& deck : listDecks) {
        std::cout << i++ << ". " << deck << std::endl;
    }
    
}

void Exit() {
    std::cout << "Goodbye!" << std::endl;
}

int main() {
    Parser parser;
    int choice = 0;
    while(true) {
        ShowMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                StartGame(parser);
                break; 
            case 2:
                CreateDeck(parser);
                break;
            case 3:
                DeleteDeck(parser);
                break;
            case 4:
                ShowAllDecks(parser);
                break;
            case 5:
                Exit();
                return 0;
            default: 
                std::cout << "Invalid choice!\n";
                break;
        }
    }
}
