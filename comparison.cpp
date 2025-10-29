#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


class Comparison {
private:
    std::string magic_number;
    int length, width, max_value;
    std::string magic_number1;
    int length1, width1, max_value1;
    std::vector<int> pixels;
    std::vector<int> pixels1;
public:
    bool read_file1(std::string &str){
        std::ifstream file(str);
        if (!file.is_open()){
            return false;
        } 

        file >> magic_number1;
        if (magic_number1 != "P2"){
            return false;
        }

        file >> std::ws;
        while (file.peek() == '#') {
            std::string comment;
            std::getline(file, comment);
        }


        file >> width1 >> length1 >> max_value1;
        pixels1.resize(width1 * length1);
        
        int pixel;
        for (int i = 0; i < length1 * width1; i++){
            file >> pixel;
            pixels1[i] = pixel;
        }
        file.close();
        return true;
    }
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
        pixels.resize(width * length*2);
        
        int pixel;
        for (int i=0; i < length * width; i++){
            file >> pixel;
            pixels[i] = pixel;
        }
        file.close();
        return true;
    }
    int sum_mistake(std::string str1, std::string str2){
        read_file(str1);
        read_file1(str2);
        int sum = 0;
        for (int i = 0; i < length * width; i++){
            sum += abs(pixels1[i] - pixels[i]);
        }
        return sum;
    }
};

int main() {
    Comparison im;
    std::ofstream file("end.csv");
    file << "sum after 1" << ";" << "sum after 3" << std::endl;
    file << im.sum_mistake("1.pgm", "endend1.pgm") << ";" << im.sum_mistake("1.pgm", "endendend1.pgm") << std::endl;
    file << im.sum_mistake("2.pgm", "endend2.pgm") << ";" << im.sum_mistake("2.pgm", "endendend2.pgm") << std::endl;
    file << im.sum_mistake("3.pgm", "endend3.pgm") << ";" << im.sum_mistake("3.pgm", "endendend3.pgm") << std::endl;
    file << im.sum_mistake("4.pgm", "endend4.pgm") << ";" << im.sum_mistake("4.pgm", "endendend4.pgm") << std::endl;
    file << im.sum_mistake("5.pgm", "endend5.pgm") << ";" << im.sum_mistake("5.pgm", "endendend5.pgm") << std::endl;
    
}