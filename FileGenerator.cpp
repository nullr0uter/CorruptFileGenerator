#include <iostream>
#include <fstream>
#include <vector>
#include <random>

enum Unit { BYTES, KB, MB, GB };

size_t calculateSize(size_t amount, Unit unit) {
    size_t factor = 1;
    switch (unit) {
        case KB: factor = 1024; break;
        case MB: factor = 1024 * 1024; break;
        case GB: factor = 1024 * 1024 * 1024; break;
        default: break;
    }
    return amount * factor;
}

void createCorruptFile(const std::string& filename, size_t fileSize) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error while creating the file!" << std::endl;
        return;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    for (size_t i = 0; i < fileSize; ++i) {
        file.put(static_cast<char>(dis(gen)));
    }
    file.close();
    std::cout << "Corrupted file " << filename << " was created successfully!" << std::endl;
}

int main() {
    std::string filename;
    std::string fileExtension;
    size_t sizeAmount;
    int unitSelection;
    std::cout << "Please input the filename (without extension): ";
    std::cin >> filename;
    std::cout << "Please input the wanted extension (e.g.: .pptx): ";
    std::cin >> fileExtension;
    std::cout << "Please input the filesize as a number (e.g.: 17): ";
    std::cin >> sizeAmount;
    std::cout << "Choose preferred unit as a number (0 = Bytes, 1 = KB, 2 = MB, 3 = GB): ";
    std::cin >> unitSelection;
    Unit unit = static_cast<Unit>(unitSelection);
    size_t fileSize = calculateSize(sizeAmount, unit);
    filename += fileExtension;
    createCorruptFile(filename, fileSize);
    return 0;
}
