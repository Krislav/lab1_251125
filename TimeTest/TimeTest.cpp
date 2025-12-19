#include "TimeTest.hpp"



using clk = std::chrono::high_resolution_clock;
using ms = std::chrono::duration<double, std::milli>;

void CompareReadFromBuffer() {
    
    ReadStream stream("MegaBigFile.txt");
    stream.Open();
    
    stream.Seek(0); // Чтение одного символо
    auto start_char = clk::now();
    while(!stream.IsEnd()) {
        stream.ReadCharFromBuffer();
    }
    auto end_char = clk::now();

    stream.Seek(0); // Чтение файла используя буфер
    auto start_text = clk::now();
    std::string text = stream.ReadTextFromBuffer();
    auto end_text = clk::now();
    stream.Close();

    auto start_direct = clk::now(); // Чтение файла просто так
    FILE* file = fopen("MegaBigFile.txt", "r");
    int count_something = 0;
    if (file) {
        setvbuf(file, NULL, _IONBF, 0);  
        int ch;
        while ((ch = fgetc(file)) != EOF) {
            count_something++;
        }
        fclose(file);
    }
    auto end_direct = clk::now();

    
    std::cout << "ReadCharFromBuffer time: " << ms(end_char - start_char).count() << " ms\n";
    std::cout << "ReadTextFromBuffer time: " << ms(end_text - start_text).count() << " ms\n";
    std::cout << "Read text direcrly time: " << ms(end_direct - start_direct).count() << " ms\n";
    
    stream.Close();
}