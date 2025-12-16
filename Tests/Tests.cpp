#include "Tests.hpp"

void TestReadStream() { // GROUP 1 Test Read stream
    ResetTestNumber();
    int result_of_test = 1;

    
    result_of_test = 1; //TEST 1.1 Проверка ошибки пустого имени
    ReadStream rs1_1("");
    try {
        rs1_1.Open();
    }
    catch(ErrorCode ex) {
        if (ex == ErrorCode::EMPTY_NAME) result_of_test = 0;
        else result_of_test = 2;
    }
    rs1_1.Close();
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 0; //TEST 1.2 Проверка открытия файла
    std::string name1_2 = "TestFile.txt";
    ReadStream rs1_2(name1_2);
    try {
        rs1_2.Open();
        if (rs1_2.IsOpen() != 1) result_of_test = 1;
    }
    catch(ErrorCode ex) {
        result_of_test = 2;
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 0; //TEST 1.3 Проверка закрытия файла
    try {
        rs1_2.Close();
        if (rs1_2.IsOpen() != 0) result_of_test = 1;
    }
    catch(ErrorCode ex) {
        result_of_test = 2;
    }
    TestResultPrint(result_of_test);
    NextTest();
    
    result_of_test = 1; //TEST 1.4 Проверка чтения символа
    rs1_2.Open();
    try {
        char a = rs1_2.ReadChar();
        if (a == '1') result_of_test = 0;
    }
    catch(ErrorCode ex) {
        result_of_test = 2;
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 1; //TEST 1.5 Проверка seek
    try {
        rs1_2.Seek(4);
        char a = rs1_2.ReadChar();
        if (a == '5') result_of_test = 0;
    }
    catch(ErrorCode ex) {
        result_of_test = 2; 
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 1; //TEST 1.6 Чтения всего файла(с заполнением буфера заного)
    rs1_2.Close();
    rs1_2.Open();
    try {
        std::string str17 = "";
        for (int i = 0; i < 18; i++) {
            str17 += rs1_2.ReadChar();
        }
        if (str17 == "12345abcde12345abc") result_of_test = 0;
        else std::cout << str17 << "\n";
    }
    catch(ErrorCode ex) {
        result_of_test = 2; 
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 1; //TEST 1.7 Проверка конца файла
    try {
        if (rs1_2.IsEnd()) result_of_test = 0;
    }
    catch(ErrorCode ex) {
        result_of_test = 2; 
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 1; //TEST 1.8 Проверка размера
    rs1_2.Close();
    rs1_2.Open();
    try {
        if (rs1_2.GetSize() == 18) result_of_test = 0;
    }
    catch(ErrorCode ex) {
        result_of_test = 2; 
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 0; //TEST 1.9 Проверка позиции
    try {
        if (rs1_2.GetPos() != 0) result_of_test = 1;
        rs1_2.Seek(3);
        if (rs1_2.GetPos() != 3) result_of_test = 1;
    }
    catch(ErrorCode ex) {
        result_of_test = 2; 
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 1; //TEST 1.10 Проверка получения имени
    try {
        if (rs1_2.GetFileName() == "TestFile.txt") result_of_test = 0;
    }
    catch(ErrorCode ex) {
        result_of_test = 2; 
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 1; //TEST 1.11 Проверка поиска подстроки
    ReadStream rs1_12("TestFileFind.txt");
    rs1_12.Open();
    std::string sub = "aba";
    try {
        int c = rs1_12.FindStr(sub);
        if (c == 2) result_of_test = 0;
    }
    catch(ErrorCode ex) {
        result_of_test = 2; 
    }
    TestResultPrint(result_of_test);
    NextTest();

    rs1_2.Close();
    rs1_12.Close();
}

void TestWriteStream() { // GROUP 2 Test Write stream
    ResetTestNumber();
    NextGroup();
    int result_of_test = 1;

    
    result_of_test = 1; //TEST 2.1 Проверка ошибки пустого имени
    WriteStream ws2_1("");
    try {
        ws2_1.Open();
    }
    catch(ErrorCode ex) {
        if (ex == ErrorCode::EMPTY_NAME) result_of_test = 0;
        else result_of_test = 2;
    }
    ws2_1.Close();
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 0; //TEST 2.2 Проверка открытия файла
    std::string name2_2 = "TestFile2.txt";
    WriteStream ws2_2(name2_2);
    try {
        ws2_2.Open();
        if (ws2_2.IsOpen() != 1) result_of_test = 1;
    }
    catch(ErrorCode ex) {
        result_of_test = 2;
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 0; //TEST 2.3 Проверка закрытия файла
    try {
        ws2_2.Close();
        if (ws2_2.IsOpen() != 0) result_of_test = 1;
    }
    catch(ErrorCode ex) {
        result_of_test = 2;
    }
    TestResultPrint(result_of_test);
    NextTest();
    
    result_of_test = 0; //TEST 2.4 Проверка записи
    ws2_2.Open();
    try {
        ws2_2.WriteChar('x');
    }
    catch(ErrorCode ex) {
        result_of_test = 2;
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 1; //TEST 2.5 Проверка seek
    try {
        ws2_2.WriteStr("12345abcde12345abc");
        ws2_2.Seek(4);
        if (ws2_2.GetPos() == 4) result_of_test = 0;
    }
    catch(ErrorCode ex) {
        result_of_test = 2; 
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 1; //TEST 2.6 Проверка размера
    ws2_2.Close();
    ws2_2.Open();
    try {
        ws2_2.WriteStr("12345abcde12345abc");
        if (ws2_2.GetSize() == 18) result_of_test = 0;
    }
    catch(ErrorCode ex) {
        result_of_test = 2; 
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 0; //TEST 2.7 Проверка позиции
    try {
        ws2_2.Seek(3);
        if (ws2_2.GetPos() != 3) result_of_test = 1;
    }
    catch(ErrorCode ex) {
        result_of_test = 2; 
    }
    TestResultPrint(result_of_test);
    NextTest();

    result_of_test = 1; //TEST 2.8 Проверка получения имени
    try {
        if (ws2_2.GetFileName() == "TestFile2.txt") result_of_test = 0;
    }
    catch(ErrorCode ex) {
        result_of_test = 2; 
    }
    TestResultPrint(result_of_test);
    NextTest();

    ws2_2.Close();
}

void TestAll(){
    TestReadStream();
    TestWriteStream();
}