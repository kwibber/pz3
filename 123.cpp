#include <iostream>
#include <random>
#include <fstream>
#include <string>
std::random_device rd;  // Источник энтропии (аппаратный)
std::mt19937 gen(rd()); // Инициализируем генератор

class Add_noise {
private:
    std::string magic_number;
    int length, width, max_value;
    int pixels[];
public:
    bool read_file(std::string &str){
        std::ifstream file(str);
        if (!file.is_open()){
            return false;
        } 

        file >> magic_number;
        if (magic_number != "P2"){
            return false;
        }

        file >> std::ws;
        while (file.peek() == '#') {
            std::string comment;
            std::getline(file, comment);
        }


        file >> length >> width >> max_value;

        
        
        file.close();
        return true;
    }
    
    
    
};



// Получаем случайное число

int main() {
    std::string str = "";
    Add_noise image;
    std::getline(std::cin, str);
    
    

}