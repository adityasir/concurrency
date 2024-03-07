#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>

void generateBinaryNumbers(const std::string& filename, int start, int end) {
    std::ofstream outFile(filename, std::ios::binary);
    
    if (!outFile.is_open()) {
        std::cerr << "Error opening output file: " << filename << std::endl;
        return;
    }

    for (int i = start; i <= end; ++i) {
        std::bitset<32> binaryRepresentation(i); // Assuming 32-bit binary numbers
        std::string binaryString = binaryRepresentation.to_string();

        // Write the binary number to the file
        outFile << binaryString << std::endl;
    }

    outFile.close();
    std::cout << "Binary numbers generated and written to: " << filename << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <output_file> <start_number> <end_number>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int startNumber, endNumber;

    try {
        startNumber = std::stoi(argv[2]);
        endNumber = std::stoi(argv[3]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 1;
    }

    if (startNumber > endNumber) {
        std::cerr << "Start number must be less than or equal to end number." << std::endl;
        return 1;
    }

    generateBinaryNumbers(filename, startNumber, endNumber);

    return 0;
}

