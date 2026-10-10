#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using Position = std::size_t;

bool isCommentary(const std::string& line) {
    return line.starts_with("#");
}

// Lê o arquivo de teste e armazena cada linha em um vetor de strings
std::vector<std::string> readTests(const std::string& path) {
    std::ifstream file(path);

    assert(file.is_open());

    std::vector<std::string> tests;

    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty() && !isCommentary(line))
            tests.push_back(line);
    }

    return tests;
}

// Encontra todas as ocorrências de uma subcadeia.
std::vector<Position> findSubstrings(const std::string& substring, const std::string& dna) {
    std::vector<Position> positions;

    for (Position position = dna.find(substring); position != std::string::npos;
        position = dna.find(substring, position + 1)) {
        positions.push_back(position);
    }

    return positions;
}

// Encontra todas as posições iniciais em que a subsequência pode aparecer.
std::vector<std::vector<Position>> findSubsequences(const std::string& subsequence,
                                                    const std::string& dna) {
    std::vector<std::vector<Position>> occurrences;

    for (Position start = 0; start < dna.size(); ++start) {
        if (dna[start] != subsequence[0])
            continue;

        std::vector<Position> positions = { start };
        Position current = start;

        for (Position index = 1; index < subsequence.size(); ++index) {
            current = dna.find(subsequence[index], current + 1);

            if (current == std::string::npos)
                break;

            positions.push_back(current);
        }

        if (positions.size() == subsequence.size())
            occurrences.push_back(positions);
    }

    return occurrences;
}

void printPositions(const std::vector<Position>& positions) {
    for (Position index = 0; index < positions.size(); ++index) {
        if (index != 0) std::cout << ", ";
        std::cout << positions[index] + 1;
    }
}

int main(int argc, char* argv[]) {
    assert(argc >= 4);

    const std::vector<std::string> substringTests = readTests(argv[2]);
    const std::vector<std::string> subsequenceTests = readTests(argv[3]);

    std::ifstream file(argv[1]);

    assert(file.is_open());

    std::string dna;

    while (std::getline(file, dna)) {
        if (dna.empty() || isCommentary(dna))
            continue;

        std::cout << "Subcadeias:\n";

        for (const std::string& test : substringTests) {
            const std::vector<Position> positions = findSubstrings(test, dna);

            std::cout << "  " << test << ": ";

            if (positions.empty()) {
                std::cout << "nenhuma ocorrencia\n";
            } else {
                printPositions(positions);
                std::cout << '\n';
            }
        }

        std::cout << "Subsequencias:\n";

        for (const std::string& test : subsequenceTests) {
            const std::vector<std::vector<Position>> occurrences = findSubsequences(test, dna);

            std::cout << "  " << test << ":\n";

            if (occurrences.empty()) {
                std::cout << "    nenhuma ocorrencia\n";
                continue;
            }

            for (const std::vector<Position>& positions : occurrences) {
                std::cout << "    ";
                printPositions(positions);
                std::cout << '\n';
            }
        }
    }

    return EXIT_SUCCESS;
}
