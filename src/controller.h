#pragma once

#include "deck.h"
#include <vector>
#include <iostream>


class Game {
public:
    bool IsCardLearned(const Card& card) const;
    bool HasUnlearnedCards(const Deck& deck) const;
    void UpdateStatus(Card& card, double change);
};

class ConsoleView { 
public:
    void ShowQuestion(const Card& card);
    void ShowAnswer(const Card& card);
    int GetUserChoice();
    void ShowProgress(const Deck& deck);
};

class Controller {
private:
    Deck& deck_;
    Game game_;
    ConsoleView view_;

public:
    explicit Controller(Deck& deck) : deck_(deck), game_(), view_() {}  

    void StartGame() {
        double change_status = 0.2;
        bool should_exit = false;
        if (!game_.HasUnlearnedCards(deck_)) {
            std::cout << "All cards are already learned!\nDo you want to review them again? (y/n): \n";
            char choice;
            std::cin >> choice;
            if (choice == 'y') {
                for (auto& [id, card] : deck_) { 
                    game_.UpdateStatus(card, -change_status);
                }
            }
        }

        while (!should_exit && game_.HasUnlearnedCards(deck_)) {
            for (auto& [id, card] : deck_) { 
                if (!game_.IsCardLearned(card)) {
                    view_.ShowQuestion(card);
                    int choice = view_.GetUserChoice();
                    switch (choice) {
                        case 1:
                            game_.UpdateStatus(card, change_status);
                            break;
                        case 2:
                            view_.ShowAnswer(card);
                            game_.UpdateStatus(card, -change_status);
                            break;
                        case 3:
                            view_.ShowAnswer(card);
                            break;
                        case 4:
                            should_exit = true;
                            break;
                        default:
                            std::cout << "Invalid input\n";
                            break;
                    }
                    if (should_exit) break;
                }
            }
        }
        view_.ShowProgress(deck_);
    }
};

