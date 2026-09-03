## Roteiro de apresentação

Para a implementação, eu dividi o problema basicamente em três partes: primeiro, gerar a fita complementar; depois, ajustar a orientação dessa fita; e, por último, encontrar os palíndromos propriamente ditos.

### 1. Geração da fita complementar

Eu comecei implementando a função `generateAntiparallel`.

Como no DNA cada base possui uma base complementar, utilizei um `unordered_map` para representar essas relações:

* A complementa T;
* T complementa A;
* C complementa G;
* G complementa C.

Então eu percorro a sequência original e, para cada base encontrada, adiciono sua complementar em uma nova string.

### 2. Inversão da fita complementar

Depois disso, no `main`, eu utilizo `std::reverse` sobre essa sequência complementar.

Eu fiz isso porque as duas fitas de DNA são antiparalelas. Ou seja, enquanto uma é considerada no sentido 5' para 3', a outra está orientada no sentido contrário.

Invertendo a sequência complementar, eu consigo trabalhar com ambas como strings em uma orientação conveniente para o algoritmo.

### 3. Busca pelos palíndromos

A parte principal do programa está na função `findMaxDNAPalindromes`.

Para encontrar os palíndromos, eu utilizei uma estratégia de **expansão a partir do centro**.

Como o exercício trabalha com palíndromos de DNA de tamanho par, cada possível centro do palíndromo é considerado como o espaço entre duas bases consecutivas.

Então, para cada centro, eu começo com dois índices:

`left = center - 1`

e

`right = center`.

A partir deles, tento expandir para os dois lados.

A condição principal é verificar se a base da esquerda corresponde ao complemento da base da direita.

Essa comparação é feita por:

`dna[left] != antiparallel[dna.size() - 1 - right]`

Apesar de parecer um pouco complicada, essa expressão permite acessar, dentro do complemento reverso, a base correspondente ao complemento de `dna[right]`.

Na prática, a pergunta feita pelo algoritmo é:

**"A base que está na esquerda é complementar à base que está na direita?"**

Se a resposta for sim, eu continuo expandindo:

`--left`

e

`++right`.

Se não forem complementares, a expansão daquele centro termina.

### 4. Palíndromo maximal

Durante essa expansão, eu guardo o maior palíndromo encontrado para aquele centro utilizando as variáveis `bestStart` e `bestLength`.

Isso é importante porque o objetivo da função não é simplesmente guardar qualquer trecho palindrômico encontrado, mas guardar o **palíndromo maximal daquele centro**.

Ou seja, eu continuo expandindo enquanto for possível e considero o maior trecho válido encontrado.

No final, verifico:

`bestLength == k`

Portanto, o programa guarda apenas palíndromos **maximais cujo tamanho seja exatamente o valor de `k`**.

### 5. Armazenamento dos resultados

Para armazenar os palíndromos encontrados, utilizei:

`std::unordered_map<std::string, std::vector<std::size_t>>`

A chave do mapa é a própria sequência palindrômica, e o vetor associado guarda todas as posições em que aquela sequência apareceu.

Por exemplo, conceitualmente eu posso ter:

`"ATCGAT" -> [3, 15, 27]`

Isso significa que o mesmo palíndromo foi encontrado começando nas posições 3, 15 e 27.

Na hora de armazenar a posição, eu utilizo:

`bestStart + 1`

porque os índices de uma string em C++ começam em zero, mas eu quis apresentar as posições começando em 1 para o usuário.

### 6. Leitura do dataset

No `main`, o programa recebe o caminho do dataset pela linha de comando.

Depois, o usuário informa o valor de `k`.

Eu também faço uma validação para garantir que `k` seja par e maior ou igual a 4.

Em seguida, o arquivo é aberto e cada linha é tratada como uma sequência de DNA independente.

Para cada sequência, o programa:

1. gera sua fita complementar;
2. inverte essa fita para obter o complemento reverso;
3. procura os palíndromos maximais;
4. e imprime os palíndromos encontrados e suas respectivas posições.

### Conclusão

Então, de forma resumida, minha implementação seguiu esta ideia:

**DNA original → complemento → complemento reverso → expansão pelos centros → identificação dos palíndromos maximais → armazenamento das posições.**

A parte que eu considero principal do algoritmo é justamente a expansão pelo centro, porque ela evita testar todas as subcadeias possíveis individualmente.

Para cada posição entre duas bases eu tento expandir enquanto as bases forem complementares. Quando essa propriedade deixa de ser satisfeita, eu sei que encontrei o maior palíndromo possível para aquele centro.
