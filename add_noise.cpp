#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>

std::random_device rd;  // Источник энтропии (аппаратный)
std::mt19937 gen(rd()); // Инициализируем генератор
//std::uniform_int_distribution<int> dist(1, 600); // Распределение от 1 до 600
//std::uniform_int_distribution<int> dist1(0, 1); // Распределение от 0 до 1

class Add_noise {
private:
    std::string magic_number;
    int length, width, max_value;
    std::vector<int> pixels;
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
        pixels.resize(width * length);
        
        int pixel;
        for (int i; i < length * width; i++){
            file >> pixel;
            pixels[i] = pixel;
        }
        file.close();
        return true;
    }
    bool write_file(std::string &str){
        std::ofstream file(str);
        if (!file.is_open()){
            return false;
        }
        file << magic_number << "\n";
        file << length << " " << width << "\n";
        file << max_value << "\n";

        for (int i = 0; i < length ; ++i) {
            for (int j = 0; j < width; ++j) {
                file << pixels[i * width + j] << " ";
            }
            file << "\n";
        }
        file.close();
        return true;
    }
    void add_change(int p){
        
        double n = length * width;
        std::cout << n << " ";
        double n1 = n * p / 100;
        std::cout << n1;
        for (int i = 0; i < n1; i++){
            int x = std::uniform_int_distribution<int>(0, length - 1)(gen);
            int y = std::uniform_int_distribution<int>(0, width - 1)(gen);
            int val = std::uniform_int_distribution<int>(0, max_value)(gen);
            pixels[x * width + y] = val; 
            
        }
    }
    void delete_change(int p){
        for (int j = 0; j < p; j++){
            pixels[0] = (pixels[1] + pixels[width] + pixels[width + 1]) / 3;
            for (int i = 1; i < width - 1; i++){
                pixels[i] = (pixels[i-1] + pixels[i+1] + pixels[i+width] + pixels[i+width-1] + pixels[i+width+1])/5;
            }
            pixels[width - 1] = (pixels[width - 2] + pixels[2 * width - 1] + pixels[2 * width - 2]) / 3;
            for (int k = 1; k < length - 1; k++){
                pixels[k * width] = (pixels[(k-1)*width] + pixels[(k-1)*width+1] + pixels[k*width+1] + pixels[(k+1)*width] + pixels[(k+1)*width+1])/5;
                for (int i = 1; i < width - 1; i++){
                    int sum1 = 
                    int sum2 = 
                    int sum3 =
                }
            }
        }
    }
    
};



// Получаем случайное число

int main() {
    std::string str = "";
    Add_noise image;
    std::getline(std::cin, str);
    if (image.read_file(str)){
        std::cout << "+";
    }else {
        std::cout << "-";
    }
    int p;
    std::cin >> p;
    image.add_change(p);
    if (image.write_file(str)){
        std::cout << "+";
    }else {
        std::cout << "-";
    }
//     for (int i = 0; i < ; i++) {
//         int random_value = dist(gen);
//         std::cout << random_value << std::endl;
//     }
}