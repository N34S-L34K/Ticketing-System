#include <iostream>    
#include <queue>        
#include <string>       
#include <thread>      
#include <chrono>     


std::queue<std::string> personQueue; 
int ticketCounter = 1; 

int main() {
    std::cout << "Welcome to Olivia Rodrigo concert ticketing system\n";

   
    std::thread([]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::minutes(10)); 
            if (!personQueue.empty()) {
                std::string person = personQueue.front(); 
                personQueue.pop(); 
                std::cout << "\nAfter 10 minutes\n";
                std::cout << person << " received a ticket (ticket# "
                          << (ticketCounter < 10 ? "00" : "0") << ticketCounter++ << ")\n"; 
                std::cout << "Queue size: " << personQueue.size() << "\n"; 
            }
        }
    }).detach();

    while (true) {
        std::cout << "1. Enqueue a person\n";
        std::cout << "2. Check your position in the queue\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice; 
        std::cin.ignore(); 

        if (choice == 1) {
            std::cout << "Enter the name: ";
            std::string name;
            std::getline(std::cin, name); 
            personQueue.push(name); 
            std::cout << name << " added to the queue with ticket# "
                      << (ticketCounter < 10 ? "00" : "0") << ticketCounter << "\n"; 
            std::cout << "Queue size: " << personQueue.size() << "\n"; 
        } else if (choice == 2) {
            std::cout << "Enter your name: ";
            std::string identifier;
            std::getline(std::cin, identifier); 
            
            
            int position = 1;
            bool found = false;
            std::queue<std::string> tempQueue = personQueue; 
            while (!tempQueue.empty()) {
                if (tempQueue.front() == identifier) {
                    found = true;
                    break;
                }
                tempQueue.pop(); 
                position++; 
            }
            if (found) {
                std::cout << identifier << " is currently at position " << position << " in the queue\n";
            } else {
                std::cout << identifier << " is not in the queue.\n"; 
            }
        } else if (choice == 3) {
            break; // Exit the loop
        } else {
            std::cout << "Invalid option. Please try again.\n"; 
        }
    }

    return 0;
}
