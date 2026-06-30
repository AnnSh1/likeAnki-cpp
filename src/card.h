#pragma once

#include <iostream>
#include <string>

class Card {
    private:
        std::string id_;
        std::string question_;
        std::string answer_;
        double status_ = 0;

    public:
        Card(const std::string& question, const std::string& answer)
            :question_(question),
            answer_(answer) {}

        Card(const std::string& question, const std::string& answer, const double status)
            : question_(question),
            answer_(answer),
            status_(status) {}
        
        void ChangeStatus(double quality) {
            status_ += quality;
            if (status_ < 0) {
                status_ = 0;
            } else if (status_ > 1) {
                status_ = 1;
            }
        }

        std::string GetQuestion() const {
            return question_;
        }

        std::string GetAnswer() const {
            return answer_;
        }

        double GetStatus() const {
            return status_;
        }
};
