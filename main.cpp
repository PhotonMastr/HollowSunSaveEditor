#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <termios.h>
#include <unistd.h>
#ifdef _WIN32 
  #include <conio.h>
#endif

char getKeyPress() {
#ifdef _WIN32
  return _getch();
#else
  struct termios oldt, newt;
  char ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
#endif
}
void clearConsole() {
  std::cout << std::flush;
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void editSaveFile(const std::string& filename) {
    const std::vector<std::string> validLocations = {
        "TutorialBunker", "EmergeFromBunker", "Chapter1NearbyRuins",
        "TheRoad", "FourWayCrossroad", "WastelandCreatureFight",
        "RuinedCity", "Chapter1End"
    };
    
    std::vector<std::string> lines;
    std::string line;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file!\n";
        return;
    }

    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    if (lines.size() < 4) {
        std::cerr << "File does not contain enough lines to modify health, stamina, money, and account money.\n";
        return;
    }
    clearConsole();
    std::cout << "Welcome to The Hollow Sun Save editor\nThis allows you to edit your save file at will\nNot very fun if you cheat though, do as you will.\n";
    std::cout << "Press any key to continue... ";
    getKeyPress();
    bool done = false;

    while (!done) {
        clearConsole();
        std::cout << "Select the trait you want to edit:\n";
        std::cout << "1. Location\n";
        std::cout << "2. Health\n";
        std::cout << "3. Stamina\n";
        std::cout << "4. Money\n";
        std::cout << "5. Account Money\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        clearConsole();

        switch (choice) {
            case 1: {
                std::string newLocation;
                bool validLocation = false;

                while (!validLocation) {
                    std::cout << "Select a new location from the following options (0 to go back to exit):\n";
                    for (size_t i = 0; i < validLocations.size(); ++i) {
                        std::cout << i + 1 << ". " << validLocations[i] << "\n";
                    }

                    std::cout << "Enter the number corresponding to your choice: ";
                    int locationChoice;
                    std::cin >> locationChoice;

                    if (locationChoice == 0) {
                        done = false;  
                        return;
                    }

                    if (std::cin.fail() || locationChoice < 1 || locationChoice > validLocations.size()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid choice, please try again.\n";
                    } else {
                        newLocation = validLocations[locationChoice - 1];
                        validLocation = true;
                    }
                }
                lines[0] = newLocation;
                break;
            }
            case 2: {
                int newHealth;
                std::cout << "Enter new health value (or 0 to go back to main menu): ";
                std::cin >> newHealth;

                if (newHealth == 0) {
                    done = false; 
                    return;
                }

                lines[1] = std::to_string(newHealth) + " " + lines[1].substr(lines[1].find(' ') + 1);
                break;
            }
            case 3: {
                int newStamina;
                std::cout << "Enter new stamina value (or 0 to go back to main menu): ";
                std::cin >> newStamina;

                if (newStamina == 0) {
                    done = false;  
                    return;
                }

                lines[1] = lines[1].substr(0, lines[1].find(' ')) + " " + std::to_string(newStamina);
                break;
            }
            case 4: {
                int newMoney;
                std::cout << "Enter new money value (or 0 to go back to main menu): ";
                std::cin >> newMoney;

                if (newMoney == 0) {
                    done = false;  
                    return;
                }

                lines[3] = std::to_string(newMoney) + " " + lines[3].substr(lines[3].find(' ') + 1);
                break;
            }
            case 5: {
                int newAccountMoney;
                std::cout << "Enter new account money value (or 0 to go back to main menu): ";
                std::cin >> newAccountMoney;

                if (newAccountMoney == 0) {
                    done = false;  
                    return;
                }

                lines[3] = lines[3].substr(0, lines[3].find(' ')) + " " + std::to_string(newAccountMoney);
                break;
            }
            case 6:
                done = true;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

        if (choice != 6) {
            std::ofstream outFile(filename);
            if (!outFile) {
                std::cerr << "Error opening file for writing!\n";
                return;
            }

            for (const auto& l : lines) {
                outFile << l << "\n";
            }
            outFile.close();

            std::cout << "Trait updated successfully.\n";
            std::cout << "Press any key to continue...\n";
            std::cin.ignore();
            std::cin.get();  
        }
    }
}

int main() {
    std::string filename = "save.txt";
    editSaveFile(filename);

    return 0;
}
