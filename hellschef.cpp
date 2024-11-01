#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Chef {
public:
    std::string name;
    int skillLevel;
    int creativity;
    int presentation;

    Chef(std::string chefName, int skill, int creativityLevel, int presentationLevel)
        : name(chefName), skillLevel(skill), creativity(creativityLevel), presentation(presentationLevel) {}

    // Calculate a score based on skill, creativity, and presentation of the player
    int getScore() const {
        return (skillLevel * 3 + creativity * 2 + presentation);
    }

    // Display Chef information like his details and professional skills
    void display() const {
        std::cout << "Chef: " << name << "\n";
        std::cout << "Skill Level: " << skillLevel << ", Creativity: " << creativity << ", Presentation: " << presentation << "\n";
        std::cout << "Score: " << getScore() << "\n";
    }
};

class GlobalCookingClash {
private:
    std::vector<Chef> participants;
    Chef* winner = nullptr;

public:
    // Add a Chef to the competition as a guest
    void addParticipant(const Chef& chef) {
        participants.push_back(chef);
    }

    // Run the competition and find the winner of the event
    void runCompetition() {
        int highestScore = 0;
        for (auto& chef : participants) {
            chef.display();
            int score = chef.getScore();
            std::cout << "Total Score for " << chef.name << ": " << score << "\n\n";
            if (score > highestScore) {
                highestScore = score;
                winner = &chef;
            }
        }

        if (winner) {
            std::cout << "The winner of the Global Cooking Clash is " << winner->name << " with a score of " << highestScore << "!\n";
        } else {
            std::cout << "No participants in the competition.\n";
        }
    }
};

int main() {
    // Initialize random seed for varying skill levels of different players
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    GlobalCookingClash cookingClash;

    // Simulate adding chefs from different parts of the world
    cookingClash.addParticipant(Chef("Alice", std::rand() % 10 + 1, std::rand() % 10 + 1, std::rand() % 10 + 1));
    cookingClash.addParticipant(Chef("Bob", std::rand() % 10 + 1, std::rand() % 10 + 1, std::rand() % 10 + 1));
    cookingClash.addParticipant(Chef("Carlos", std::rand() % 10 + 1, std::rand() % 10 + 1, std::rand() % 10 + 1));
    cookingClash.addParticipant(Chef("Diana", std::rand() % 10 + 1, std::rand() % 10 + 1, std::rand() % 10 + 1));

    // Run the competition and determine the winner
    cookingClash.runCompetition();

    return 0;
}
