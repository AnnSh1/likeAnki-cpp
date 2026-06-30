#include "controller.h"

bool Game::IsCardLearned(const Card& card) const {
    return card.GetStatus() >= 1.0;
}
bool Game::HasUnlearnedCards(const Deck& deck) const {
    for (const auto& [id, card] : deck) {
        if (card.GetStatus() < 1.0)
            return true;
    }
    return false;
}

void Game::UpdateStatus(Card& card, double change) {
    card.ChangeStatus(change);
}

void ConsoleView::ShowQuestion(const Card& card) {
    std::cout << card.GetQuestion() << std::endl;
}

void ConsoleView::ShowAnswer(const Card& card) {
    std::cout << card.GetAnswer() << std::endl;
}

int ConsoleView::GetUserChoice() {
    int choice;
    std::cout << "1. Easy\n" << "2. Hard\n" 
            << "3. Show answer.\n" 
            << "4. Exit early.\n";
    std::cin >> choice;
    return choice;
}

void ConsoleView::ShowProgress(const Deck& deck) {
    for (const auto& [id, card] : deck) {
        if (card.GetStatus() < 1.0) {
            std::cout << "<<< Not all cards have been studied. >>>\n";
            return;
        }
    }
    std::cout << "<<< All cards learned! >>>\n";    
}
