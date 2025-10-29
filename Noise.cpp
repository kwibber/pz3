#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

std::random_device rd;  // Источник энтропии (аппаратный)
std::mt19937 gen(rd()); // Инициализируем генератор
//std::uniform_int_distribution<int> dist(1, 600); // Распределение от 1 до 600
//std::uniform_int_distribution<int> dist1(0, 1); // Распределение от 0 до 1

class Noise {
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


        file >> width >> length >> max_value;
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
        std::ofstream file("end"+str);
        if (!file.is_open()){
            return false;
        }
        file << magic_number << "\n";
        file << width << " " << length << "\n";
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
        
        double n1 = n * p / 100;
       
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
                    int sum1 = pixels[(k-1)*width + i - 1] + pixels[(k-1)*width+i] + pixels[(k-1)*width+1+i];
                    //std::cout << (k-1)*width + i - 1 <<" " <<(k-1)*width+i << " " <<(k-1)*width+1+i << std::endl;
                    int sum2 = pixels[(k)*width-1+i] + pixels[(k)*width+1+i];
                    //std::cout << (k-1)*width + i - 1 <<" " <<(k-1)*width+i << " " <<(k-1)*width+1+i << std::endl;
                    int sum3 = pixels[(k+1)*width-1+i] + pixels[(k+1)*width+i] + pixels[(k+1)*width+1+i];
                    //std::cout << (k-1)*width + i - 1 <<" " <<(k-1)*width+i << " " <<(k-1)*width+1+i << std::endl;
                    pixels[k*width + i] = (sum2 + sum3)/8;
                }
                pixels[(k+1) * width - 1] = (pixels[(k+2)*width - 1] + pixels[(k+2)*width-2] + pixels[(k+1)*width-2] + pixels[k*width-1] + pixels[k*width-2])/5;
            }
            pixels[width*(length - 1)] = (pixels[width*(length - 1)+1] + pixels[width*(length - 2)] + pixels[width*(length-2)+1]) / 3;
            for (int i = 1; i < width - 1; i++){
                pixels[width*(length - 1)+i] = (pixels[(length - 1)*width+i-1] + pixels[width*(length - 1)+i+1] + pixels[width*(length - 2)+i] + pixels[i+width*(length - 2)-1] + pixels[i+width*(length - 2)+1])/5;
            }
            pixels[width*length - 1] = (pixels[width*length - 2] + pixels[width*(length-1) - 1] + pixels[(length-1) * width - 2]) / 3;
        }
    }
    
};



// Получаем случайное число

int main() {
    std::cout << "Введите имя файла" << std::endl;
    std::string str = "";
    Noise image;
    std::getline(std::cin, str);
    if (image.read_file(str)){
        std::cout << "Файл считан";
    }else {
        std::cout << "Ошибка чтения файла";
    }
    std::cout << "Выберите действие с файлом из списка" << std::endl << "1. Добавление шума" << std::endl << "2. Удаление шума" << std::endl;
    int n = 0;
    int prm = 0;
    while (n!=1 && n!=2 || prm == 0){
        std::cin >> n;
        int p;
        if (n==1){
            std::cout <<"Введите уровень шумов от 1 до 10"<<std::endl;
            int p = 0;
            std::cin >> p;
            if (p<0 || p > 10){
                prm = 0;
                std::cout << "Введено недопустимое значение" << std::endl;
                std::cout << "Введите правильное значение" << std::endl;
            } else{
                image.add_change(p);
                std::cout << "Шумы добавленны" << std::endl;
                prm = 1;
            }
        }else if (n==2){
            std::cout <<"Введите количество проходов от 1 до 10"<<std::endl;
            int p;
            std::cin >> p;
            if (p<0 || p > 10){
                prm = 0;
                std::cout << "Введено недопустимое значение" << std::endl;
                std::cout << "Введите правильное значение" << std::endl;
            } else{
                image.delete_change(p);
                std::cout << "Шумы удвленны" << std::endl;
                prm = 1;
            }
        }else{
            std::cout << "Введено неправельное значение." << std::endl;
            std::cout << "Введите число 1 или 2" << std::endl;
        }
    }
    if (image.write_file(str)){
        std::cout << "Файл возвращен" << std::endl;
    }else {
        std::cout << "Ошибка вывода" << std::endl;
    }
}