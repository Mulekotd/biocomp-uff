#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <print>
#include <unordered_map>

#define MIN_HARPIN_LEN 12
#define MAX_HARPIN_LEN 20
#define MIN_HEAD_LEN 3

static const std::unordered_map<char, char> baseComplement = {
    {'A', 'T'},
    {'T', 'A'},
    {'C', 'G'},
    {'G', 'C'}
};

// Verifica na entrada do dataset se a linha é um comentário
bool isCommentary(const std::string line) {
    return line.starts_with("#");
}

// Verifica se duas subcadeias são palindromicas
bool isReverseComplement(int k, const std::string prefix, const std::string suffix) {
    int isComplementary = true;

    // Partindo do inicio do prefixo
    // Partindo do final do sufixo
    // Verifica se prefixo == complementar(sufixo)

    for (int i = 0; i < k; i++) {
        char leftBase = prefix.at(i);
        char rightBase = suffix.at(k - i - 1);

        if (leftBase != baseComplement.at(rightBase)) {
            isComplementary = false;
            break;
        }
    }

    return isComplementary;
}

std::unordered_map<int, std::string> findHairpins(int k, const std::string dna) {
    std::unordered_map<int, std::string> hairpins;

    const int maxHeadLength = k - 1;

    for (int startPosition = 0;
        startPosition + 2 * k + MIN_HEAD_LEN <= static_cast<int>(dna.length());
        startPosition++) {
        std::string prefix = dna.substr(startPosition, k); // Monta o prefixo

        int headOffset = 0;

        while (MIN_HEAD_LEN + headOffset <= maxHeadLength) {
            int headLength = MIN_HEAD_LEN + headOffset;
            int endPosition = 2 * k + headLength;

            if (startPosition + endPosition > static_cast<int>(dna.length()))
                break;

            std::string suffix = dna.substr(k + headLength + startPosition, k); // Monta o sufixo

            if (isReverseComplement(k, prefix, suffix)) {
                std::string hairpin = dna.substr(startPosition, endPosition);

                if (hairpin.length() >= MIN_HARPIN_LEN && hairpin.length() <= MAX_HARPIN_LEN) {
                    hairpins.insert(std::pair<int, std::string>(startPosition, hairpin));
                    startPosition = endPosition + startPosition - 1; // Subtrai 1 pois o loop incrementa novamente
                    break;
                }
            }

            headOffset++;
        }
    }

    return hairpins;
}

int main(int argc, char *argv[]) {
    // Verifica se o arquivo foi passado como argumento
    assert(argc >= 2);

    const std::string path = argv[1];

    int k;

    std::print("Digite o valor de k: ");
    std::cin >> k;

    // Verifica se k > 4
    assert(k > 4);

    std::ifstream file(path);

    // Verifica se o arquivo foi aberto corretamente
    assert(file.is_open());

    std::string line;
    std::unordered_map<int, std::string> hairpins; // Mapeia a posição e seu respectivo grampo

    int sequence = 1;

    while (std::getline(file, line)) {
        if (isCommentary(line))
            continue;

        hairpins = findHairpins(k, line);

        std::println("\nSequência: {}", sequence);

        for (const auto& [position, hairpin] : hairpins)
            std::println("Posição: {} | Grampo: {} | Tamanho: {}", position, hairpin, hairpin.length());

        sequence++;
    }

    return EXIT_SUCCESS;
}
