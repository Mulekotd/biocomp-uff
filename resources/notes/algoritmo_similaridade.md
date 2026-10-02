# Algorítmo de Similaridade

Este algorimo pode ser utilizado para realizar o alinhamento global e local entre duas sequências. Isto serve para encontrar o alinhamento que torna elas o mais parecidas possível.

- Entrada: sequencias s, t.
- Saída: similaridade entre s e t.

## Pseudo-código

```txt
define:
    a      := matriz(m+1 x n+1)
    g      := -2 # penalidade por alinhar caracter com espaço (gap)
    p(i,j) := se s[i] igual t[j] retorna 1; se s[i] não igual t[j] então retorna -1
```

```txt
inicio:
    m <- |s|
    n <- |t|

    para i <- 0 até m faça
        a[i,0] <- i*g
    fimpara

    para j <- 0 até n faça
        a[0,j] <- j*g
    fimpara

    para i <- 1 até m faça
        para j <- 1 até n faça
            a[i,j] = max(a[i-1,j] + g, a[i-1,j-1] + p(i,j), a[i,j-1] + g)
        fimpara
    fimpara

    retorna a[m,n]
fim
```

### Exemplo

```txt
s := AATC
t := AATAC
```

#### Matriz A(5x6)

|         | t   | A   | A   | T   | A   | C   |
| ------- | --- | --- | --- | --- | --- | --- |
| s       | 0   | -2  | -4  | -6  | -8  | -10 |
| A       | -2  | 1   | -1  | -3  | -5  | -7  |
| A       | -4  | -1  | 2   | 0   | -2  | -4  |
| T       | -6  | -3  | 0   | 3   | 1   | -1  |
| C       | -8  | -5  | -2  | 1   | 2   | 2   |
