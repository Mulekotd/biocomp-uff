#include <algorithm>
#include <fstream>
#include <iostream>
#include <print>
#include <unordered_map>
#include <vector>

std::string generateAntiparallel(const std::string& dna)
{
    static const std::unordered_map<char, char> complement = {
        {'A', 'T'},
        {'T', 'A'},
        {'C', 'G'},
        {'G', 'C'}
    };

    std::string antiparallel;

    for (char base : dna)
        antiparallel += complement.at(base);

    return antiparallel;
}

// Encontra todos os palíndromos maximais expandindo cada centro possível.
std::unordered_map<std::string, std::vector<std::size_t>> findMaxDNAPalindromes(
    const std::string& dna, const std::string& antiparallel, const int k)
{
    std::unordered_map<std::string, std::vector<std::size_t>> palindromes;

    // Cada centro é um vão entre dna[center - 1] e dna[center].
    for (std::size_t center = 1; center < dna.size(); ++center)
    {
        std::size_t left = center - 1;
        std::size_t right = center;
        std::size_t bestStart = 0;
        std::size_t bestLength = 0;

        while (true)
        {
            if (dna[left] != antiparallel[dna.size() - 1 - right])
                break;

            const std::size_t length = right - left + 1;

            if (length > bestLength)
            {
                bestStart = left;
                bestLength = length;
            }

            // Não é possível expandir mais.
            if (left == 0 || right + 1 == dna.size())
                break;

            --left;
            ++right;
        }

        // Imprime somente palíndromos maximais com tamanho exatamente igual a k.
        if (bestLength == static_cast<std::size_t>(k))
            palindromes[dna.substr(bestStart, bestLength)].push_back(bestStart + 1);
    }

    return palindromes;
}

int main(void)
{
    const std::string path = "dataset.txt";

    int k;

    std::print("Digite o valor de k (par e maior ou igual a 4): ");
    std::cin >> k;

    if (k < 4 || k % 2 != 0)
    {
        std::println("[Debug] k deve ser par e maior ou igual a 4.");
        return -1;
    }

    std::ifstream file(path);

    if (!file.is_open())
    {
        std::println("[Debug] Não foi possível abrir o arquivo indicado.");
        return -1;
    }

    std::string dna; // Cadeia do DNA (5′ → 3′)

    int sequence = 1;

    // Extrai cada linha do dataset
    while (std::getline(file, dna))
    {
        // 1o: Acha a cadeia antiparalela do DNA (3′ → 5′)
        std::string antiparallel = generateAntiparallel(dna);

        // 2o: Inverte a cadeia antiparalela
        std::reverse(antiparallel.begin(), antiparallel.end());

        // 3o: Encontra todos os palindromos maximais de tamanho k
        auto palindromes = findMaxDNAPalindromes(dna, antiparallel, k);

        std::println("\nSequência {}:", sequence++);

        for (const auto& [palindrome, positions] : palindromes)
        {
            std::print("Palíndromo: {} | tamanho: {} | posições: ",
                       palindrome, palindrome.size());

            for (std::size_t i = 0; i < positions.size(); ++i)
                std::print("{}{}", positions[i],
                           (i + 1) == positions.size() ? "\n" : ", ");
        }
    }

    return 0;
}
