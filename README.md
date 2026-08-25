# Biologia Computacional

## Compilação e Execução

O projeto usa CMake e procura automaticamente por diretórios no padrão
`exercicioN` que contenham um `main.cpp`.

```sh
cmake -S . -B builds -DCMAKE_CXX_COMPILER=g++-15
cmake --build builds
```

Os executáveis são gerados em `builds/bin/`. Exemplo de execução do primeiro exercício, passando o caminho do dataset como argumento:

```sh
./builds/bin/exercicio1 exercicio1/dataset.txt
```

## Programação:

- Introdução aos Princípios da biologia molecular: Vida, material genético, genes, mecânismos do DNA para gerar proteínas.
- Estruturas do DNA, organização da informação entre o DNA e as proteínas, como análisar o DNA, diferenciação de indivíduos de uma mesma espécie.
- Comparação de cadeias. Comparação global. Comparação local. Comparação semi-global.
- Mapeamento de restrição.
- Rearranjo de genomas.
- Genes, micro-RNA, genomas, pangenomas.
 
## Referências:

- Introduction to Computational Molecular Biology, João Carlos Setubal e João Meidanis, PWS - Publishing Company, Boston, 1997.
- An Introduction to Bioinformatics Algorithms, Neil C. Jones and Pavel A Pevzner, MIT Press, 2004.
- Desenvolvendo Bioinformática, Cyntia Gibas e Per Jambeck, Editora Campus, 2002.
- Journal of Molecular Biology (artigos).
