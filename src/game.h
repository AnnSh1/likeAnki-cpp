#pragma once

#include "deck.h"
#include <vector>
#include <iostream>

class Controller {
private:
    Deck& deck_;
public:
    Controller(Deck& deck) : deck_(deck) {}
    

    void StartGame(){
        int num;
        double change_status = 0.2;
        bool learned = true;
        while (learned) {
            bool has_unlearned = false;
            for (auto& [id, card] : deck_.GetDeck()) {
                if (card.GetStatus() < 1) {
                    has_unlearned = true;
                    std::cout << card.GetQuestion() << std::endl;
                    std::cout << "1. Легко\n" << "2. Тяжело\n" 
                            << "3. Показать другую сторону карточки.\n" 
                            << "4. Завершить досрочно.\n";
                    std::cin >> num;
                    switch (num) {
                        case 1:
                            card.ChangeStatus(change_status);
                            break;
                        case 2:
                            std::cout << card.GetAnswer() << "\n";
                            card.ChangeStatus(-change_status);
                            break;
                        case 3:
                            std::cout << card.GetAnswer() << "\n";
                            break;
                        case 4:
                            learned = false;
                            break;
                        default:
                            std::cout << "Неккоректный ввод\n";
                            break;                            
                    }

                    if (!learned) {
                        break;
                    }
                }
            }
            if (!has_unlearned) {
                break;
            }
        }
        if (learned) {
            std::cout << "🎉 Все карточки изучены!\n";
        } else {
            std::cout << "Не все карточки доучены.\n";
        }

        for (auto& [id, card] : deck_.GetDeck()) {
            if (card.GetStatus() >= 0.9) { 
                card.ChangeStatus(-0.2);
            }
        }
    }

};