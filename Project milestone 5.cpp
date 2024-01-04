#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

    
    
// RISC assembly to machine code mapping
std::map<std::string, std::string> assemblyToMachineCode = {
    {"add", "0000"},
        {"sub", "0001"},
        {"lw", "0010"},
        {"sw", "0011"},
		{"lt", "0100"},  
        {"eq", "0101"},  
        {"gt", "0110"},
		{"addi", "0111"},
        {"j", "1000"},
        {"beq", "1001"},
        {"cvt.s.w", "1010"},
        {"mtc1.d", "1011"},
        {"div.d", "1100"},
        {"jr", "1101"},
        {"li", "1110"},
        {"la", "1111"},
        {"jal", "10000"},
        {"bclt", "10001"},
        {"c.lt", "10010"},
        {"li.s", "10011"},
        {"c.lt.s", "10100"},
        {"swc1", "10101"},
        {"cvt.d.s", "10110"},
        {".text", "11010"},
    
    {".word", "0000"},
    {".space", "0001"},
    {".asciiz", "0010"},



    {"$zero", "00000"},
    {"$at", "00001"},
    {"$v0", "00010"},
    {"$v1", "00011"},
    {"$a0", "00100"},
    {"$a1", "00101"},
    {"$a2", "00110"},
    {"$a3", "00111"},
    {"$t0", "01000"},
    {"$t1", "01001"},
    {"$t2", "01010"},
    {"$t3", "01011"},
    {"$t4", "01100"},
    {"$t5", "01101"},
    {"$t6", "01110"},
    {"$t7", "01111"},
    {"$s0", "10000"},
    {"$s1", "10001"},
    {"$s2", "10010"},
    {"$f0", "10011"},
    {"$f1", "10100"},
    {"$f2", "10101"},
    {"$f3", "10110"},
    {"$f4", "10111"},
    {"$f5", "11000"},
    {"$f6", "11001"},
    {"$f7", "11010"},
    {"$t8", "11011"},
    {"$t9", "11100"},
    {"$k0", "11101"},
    {"$k1", "11110"},
    {"$gp", "11111"},
    {"$sp", "100000"},
    {"$fp", "100001"},
    {"$ra", "100010"},
    {"$f0", "10011"},
    {"$f1", "10100"},
    {"$f2", "10101"},
    {"$f3", "10110"},
    {"$f4", "10111"},
    {"$f5", "11000"},
    {"$f6", "11001"},
    {"$f7", "11010"},
};
    
// Symbol table to store label addresses
std::unordered_map<std::string, int> symbolTable;

// Function to convert RISC assembly code to machine code
std::string convertAssemblyToMachineCode(const std::string& assembly) {
    std::string machineCode;
    std::istringstream iss(assembly);
    std::string token;

    while (iss >> token) {
        if (token.back() == ':') {
            // Handle labels
            std::string label = token.substr(0, token.length() - 1); // Remove the trailing ':'
            symbolTable[label] = machineCode.length() / 4; // Record label address (assuming 4 bytes per instruction)
        } else if (token == ".globl" || token == ".data" || token == ".text") {
            // Handle directives
            // For simplicity, assume these directives don't generate machine code
            // You can adjust this part based on the actual behavior you need
        } else if (symbolTable.find(token) != symbolTable.end()) {
            // Handle labels referenced in instructions
            int labelAddress = symbolTable[token];
            // Convert label address to binary and append to machine code
            for (int i = 15; i >= 0; --i) {
                machineCode.push_back(((labelAddress >> i) & 1) + '0');
            }
        } else if (assemblyToMachineCode.find(token) != assemblyToMachineCode.end()) {
            // Handle instructions
            machineCode += assemblyToMachineCode[token];
        } else if (registerToBinary.find(token) != registerToBinary.end()) {
            // Handle registers
            machineCode += registerToBinary[token];
        } else {
            // Handle unknown token
            std::cout << "Unknown token: " << token << std::endl;
        }
    }

    return machineCode;
}


int main() {
    std::string inputFilename = "Iott.txt";      // Input assembly file
    std::string outputFilename = "output.txt";    // Output machine code file

    // Read the assembly code from the input file
    std::ifstream inputFile(inputFilename);
    if (!inputFile) {
        std::cerr << "Failed to open input file: " << inputFilename << std::endl;
        return 1;
    }

    std::ostringstream oss;
    oss << inputFile.rdbuf();
    std::string assemblyCode = oss.str();

    // Convert the assembly code to machine code
    std::string machineCode = convertAssemblyToMachineCode(assemblyCode);

    // Output the machine code to the output file
    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cerr << "Failed to open output file: " << outputFilename << std::endl;
        return 1;
    }

    outputFile << machineCode;
    outputFile.close();

    // Output the machine code to the console
    std::cout << "Machine Code:" << std::endl;
    std::cout << machineCode << std::endl;
    return 0;
}