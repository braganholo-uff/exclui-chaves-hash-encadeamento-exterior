#### Problema

Implemente a exclusão de um conjunto de chaves de uma tabela hash com encadeamento exterior armazenada em memória principal. Cada registro da tabela guarda a matrícula de um aluno, que é a chave, e o seu CR. A função de hash é h(x) = x mod m, sendo m o tamanho da tabela. O compartimento i da tabela aponta para uma lista encadeada com os registros cujas matrículas têm hash igual a i, ou vale NULL se não houver nenhum registro com esse hash.

A função recebe a tabela, já preenchida com os registros informados na entrada, e um vetor com as matrículas que devem ser excluídas. As chaves são excluídas na ordem em que aparecem no vetor. Se uma chave não existir na tabela, ela é ignorada.

Para encontrar uma chave numa tabela hash, basta percorrer a lista de um único compartimento. Por isso, para cada chave, a função deve examinar **apenas** os registros da lista do compartimento h(chave), do início da lista até encontrar a chave ou chegar ao fim da lista. Os outros compartimentos não devem ser visitados. Para que isso possa ser conferido, a função imprime a matrícula de cada registro examinado (isto é, de cada registro cuja matrícula é comparada com a chave procurada), na ordem em que os registros são examinados.

O arquivo exclui\_chaves.c fornecido já contém as funções da tabela hash vistas em aula (hash, inicializa, aloca, insere, busca, imprime e libera) e a função imprime\_chave, que imprime a matrícula de um registro examinado.

Vocês devem implementar a função:

- void exclui\_chaves(Hash \*tab, int m, int \*chaves, int qtd\_chaves): exclui da tabela tab, de tamanho m, os registros cujas matrículas estão no vetor chaves, que tem qtd\_chaves posições. Para cada registro examinado, a função chama imprime\_chave com a matrícula desse registro. O espaço de cada registro excluído deve ser liberado com free

Use o arquivo exclui\_chaves.c fornecido nesse exercício, pois ele já contém o tratamento de entrada e saída.

#### Entrada:
- O tamanho m da tabela hash
- A quantidade n de registros a inserir na tabela, seguida de n linhas com a matrícula e o CR de cada aluno. Os registros são inseridos na ordem em que aparecem, e a função insere coloca cada registro novo no fim da lista do seu compartimento
- A quantidade k de chaves a excluir, seguida de uma linha com as k matrículas separadas por espaço

As matrículas são inteiros não negativos.

#### Saída:
- A linha "TABELA INICIAL:" seguida da tabela antes das exclusões
- A linha "CHAVES EXAMINADAS:" seguida das matrículas dos registros examinados durante as exclusões, uma por linha, na ordem em que foram examinados. Uma chave cujo compartimento está vazio não gera nenhuma linha
- A linha "TABELA FINAL:" seguida da tabela depois das exclusões

A tabela é impressa com uma linha por compartimento, no formato `i: matrícula (CR) -> matrícula (CR) -> NULL`. Um compartimento vazio aparece como `i: NULL`.

## Exemplo

A entrada abaixo monta a [tabela B](#tabela-b-oito-registros-em-sete-compartimentos) (m = 7, com 8 registros) e exclui as chaves 3 e 24. Ela corresponde ao [caso de teste 9](casos-teste/9).

Entrada:

```
7
8
21 7.5
10 8.0
14 6.2
8 9.1
3 5.4
28 7.0
17 8.8
5 6.6
2
3 24
```

Saída:

```
TABELA INICIAL:
0: 21 (7.50) -> 14 (6.20) -> 28 (7.00) -> NULL
1: 8 (9.10) -> NULL
2: NULL
3: 10 (8.00) -> 3 (5.40) -> 17 (8.80) -> NULL
4: NULL
5: 5 (6.60) -> NULL
6: NULL
CHAVES EXAMINADAS:
10
3
10
17
TABELA FINAL:
0: 21 (7.50) -> 14 (6.20) -> 28 (7.00) -> NULL
1: 8 (9.10) -> NULL
2: NULL
3: 10 (8.00) -> 17 (8.80) -> NULL
4: NULL
5: 5 (6.60) -> NULL
6: NULL
```

Como h(3) = 3 mod 7 = 3, a exclusão da chave 3 percorre a lista do compartimento 3, que é 10 -> 3 -> 17. O registro 10 é examinado e não é a chave procurada. Em seguida, o registro 3 é examinado e, como contém a chave, é excluído. A chave 24 também cai no compartimento 3, pois h(24) = 24 mod 7 = 3, cuja lista agora é 10 -> 17. Os dois registros são examinados, a lista termina e a chave 24 é ignorada, já que não existe na tabela. Os compartimentos 0, 1, 2, 4, 5 e 6 não são visitados.

## Tabelas usadas nos casos de teste

Em cada tabela, os registros foram inseridos na ordem indicada em "Registros inseridos", no formato matrícula:CR. Como a função insere coloca cada registro novo no fim da lista do seu compartimento, a ordem dos registros dentro de cada lista é a ordem de inserção. As listas não são ordenadas pela matrícula.

### Tabela A: tabela vazia

m = 5. Registros inseridos: nenhum

```
0: NULL
1: NULL
2: NULL
3: NULL
4: NULL
```

### Tabela B: oito registros em sete compartimentos

m = 7. Registros inseridos: 21:7.5, 10:8.0, 14:6.2, 8:9.1, 3:5.4, 28:7.0, 17:8.8, 5:6.6

Os valores de hash são h(21) = h(14) = h(28) = 0, h(8) = 1, h(10) = h(3) = h(17) = 3 e h(5) = 5.

```
0: 21 (7.50) -> 14 (6.20) -> 28 (7.00) -> NULL
1: 8 (9.10) -> NULL
2: NULL
3: 10 (8.00) -> 3 (5.40) -> 17 (8.80) -> NULL
4: NULL
5: 5 (6.60) -> NULL
6: NULL
```

### Tabela C: um único compartimento

m = 1. Registros inseridos: 40:7.0, 15:8.5, 32:6.0, 27:9.0

Com m = 1, toda matrícula tem hash 0, e a tabela se reduz a uma única lista encadeada.

```
0: 40 (7.00) -> 15 (8.50) -> 32 (6.00) -> 27 (9.00) -> NULL
```

### Tabela D: onze compartimentos

m = 11. Registros inseridos: 22:7.2, 13:8.4, 4:6.8, 18:9.5, 55:5.9, 26:7.7, 20:8.1, 35:6.3, 48:9.0, 43:7.4, 11:8.6, 31:5.5, 70:6.9, 88:8.3

Os valores de hash são h(22) = h(55) = h(11) = h(88) = 0, h(13) = h(35) = 2, h(4) = h(26) = h(48) = h(70) = 4, h(18) = 7, h(20) = h(31) = 9 e h(43) = 10.

```
0: 22 (7.20) -> 55 (5.90) -> 11 (8.60) -> 88 (8.30) -> NULL
1: NULL
2: 13 (8.40) -> 35 (6.30) -> NULL
3: NULL
4: 4 (6.80) -> 26 (7.70) -> 48 (9.00) -> 70 (6.90) -> NULL
5: NULL
6: NULL
7: 18 (9.50) -> NULL
8: NULL
9: 20 (8.10) -> 31 (5.50) -> NULL
10: 43 (7.40) -> NULL
```

## Exemplos

A tabela abaixo mostra apenas a parte "CHAVES EXAMINADAS:" da saída. A saída completa de cada exemplo está no caso de teste indicado.

|Caso|Tabela|Chaves excluídas|Chaves examinadas|Explicação|
|---|---|---|---|---|
|[1](casos-teste/1)|[A](#tabela-a-tabela-vazia)|3 7|(nenhuma)|A tabela está vazia. Os compartimentos h(3) = 3 e h(7) = 2 valem NULL, e não há registro para examinar|
|[3](casos-teste/3)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|21|21|21 é o primeiro registro da lista do compartimento 0. Depois da exclusão, tab[0] passa a apontar para o registro 14|
|[5](casos-teste/5)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|28|21<BR/>14<BR/>28|28 é o último registro da lista do compartimento 0, por isso os registros 21 e 14 são examinados antes dele|
|[7](casos-teste/7)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|9|(nenhuma)|h(9) = 2 e o compartimento 2 está vazio, então nenhum registro é examinado|
|[8](casos-teste/8)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|24|10<BR/>3<BR/>17|h(24) = 3. A lista do compartimento 3 é percorrida até o fim sem encontrar a chave, que é ignorada|
|[10](casos-teste/10)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|17 17|10<BR/>3<BR/>17<BR/>10<BR/>3|Na primeira vez, 17 é encontrado no fim da lista e excluído. Na segunda, ele já não existe, e a lista 10 -> 3 é percorrida até o fim|
|[14](casos-teste/14)|[C](#tabela-c-um-único-compartimento)|15 27 99|40<BR/>15<BR/>40<BR/>32<BR/>27<BR/>40<BR/>32|Com m = 1, todas as chaves estão na mesma lista, e cada exclusão começa a percorrer a lista pelo primeiro registro|
|[16](casos-teste/16)|[D](#tabela-d-onze-compartimentos)|1 66 25|22<BR/>55<BR/>11<BR/>88|As chaves 1 e 25 caem nos compartimentos vazios 1 e 3. A chave 66 cai no compartimento 0, cuja lista é percorrida até o fim|

## Casos de teste:

Os casos de teste estão na pasta [casos-teste](casos-teste). Cada caso tem 2 arquivos:

- entrada.txt: o que deve ser digitado no teclado (o tamanho da tabela, os registros e as chaves a excluir)
- saida.txt: a saída esperada do programa

|Caso|Tabela|Chaves excluídas|Descrição|Arquivos|
|---|---|---|---|---|
|[1](casos-teste/1)|[A](#tabela-a-tabela-vazia)|3 7|Tabela vazia: nenhum registro é examinado|[entrada.txt](casos-teste/1/entrada.txt) [saida.txt](casos-teste/1/saida.txt)|
|[2](casos-teste/2)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|(nenhuma)|Lista de chaves vazia: a tabela não muda|[entrada.txt](casos-teste/2/entrada.txt) [saida.txt](casos-teste/2/saida.txt)|
|[3](casos-teste/3)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|21|Chave no primeiro registro de uma lista com três registros|[entrada.txt](casos-teste/3/entrada.txt) [saida.txt](casos-teste/3/saida.txt)|
|[4](casos-teste/4)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|3|Chave no meio de uma lista|[entrada.txt](casos-teste/4/entrada.txt) [saida.txt](casos-teste/4/saida.txt)|
|[5](casos-teste/5)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|28|Chave no último registro de uma lista|[entrada.txt](casos-teste/5/entrada.txt) [saida.txt](casos-teste/5/saida.txt)|
|[6](casos-teste/6)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|8|Chave no único registro da lista: o compartimento fica vazio|[entrada.txt](casos-teste/6/entrada.txt) [saida.txt](casos-teste/6/saida.txt)|
|[7](casos-teste/7)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|9|Chave não existe e o compartimento dela está vazio|[entrada.txt](casos-teste/7/entrada.txt) [saida.txt](casos-teste/7/saida.txt)|
|[8](casos-teste/8)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|24|Chave não existe e a lista do compartimento é percorrida até o fim|[entrada.txt](casos-teste/8/entrada.txt) [saida.txt](casos-teste/8/saida.txt)|
|[9](casos-teste/9)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|3 24|Exclusão seguida de uma chave inexistente no mesmo compartimento (exemplo completo acima)|[entrada.txt](casos-teste/9/entrada.txt) [saida.txt](casos-teste/9/saida.txt)|
|[10](casos-teste/10)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|17 17|Mesma chave duas vezes: na segunda vez ela já não existe|[entrada.txt](casos-teste/10/entrada.txt) [saida.txt](casos-teste/10/saida.txt)|
|[11](casos-teste/11)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|17 3 10|Esvazia um compartimento, começando pelo último registro da lista|[entrada.txt](casos-teste/11/entrada.txt) [saida.txt](casos-teste/11/saida.txt)|
|[12](casos-teste/12)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|14 24 5 30 21|Chaves de vários compartimentos, existentes e inexistentes|[entrada.txt](casos-teste/12/entrada.txt) [saida.txt](casos-teste/12/saida.txt)|
|[13](casos-teste/13)|[B](#tabela-b-oito-registros-em-sete-compartimentos)|28 17 5 14 8 3 21 10|Exclui todos os registros: a tabela fica vazia|[entrada.txt](casos-teste/13/entrada.txt) [saida.txt](casos-teste/13/saida.txt)|
|[14](casos-teste/14)|[C](#tabela-c-um-único-compartimento)|15 27 99|Tabela com um único compartimento (m = 1)|[entrada.txt](casos-teste/14/entrada.txt) [saida.txt](casos-teste/14/saida.txt)|
|[15](casos-teste/15)|[D](#tabela-d-onze-compartimentos)|55 70 13 77 11 88 4|Várias exclusões nas listas de uma tabela maior|[entrada.txt](casos-teste/15/entrada.txt) [saida.txt](casos-teste/15/saida.txt)|
|[16](casos-teste/16)|[D](#tabela-d-onze-compartimentos)|1 66 25|Nenhuma das chaves existe na tabela|[entrada.txt](casos-teste/16/entrada.txt) [saida.txt](casos-teste/16/saida.txt)|

### Como compilar e rodar os testes

O projeto tem um Makefile. Abra a pasta do projeto no VSCode e use o terminal integrado (menu Terminal > New Terminal). Os comandos abaixo devem ser executados na pasta do projeto:

|Comando|O que faz|
|---|---|
|`make`|Compila o programa, gerando o executável exclui\_chaves|
|`make test`|Roda todos os casos de teste e mostra quais passaram e quais falharam|
|`make caso N=4`|Roda apenas o caso 4 e mostra as diferenças entre a sua saída e a saída esperada|
|`make clean`|Apaga o executável e a pasta execucao|

No `make caso`, as linhas marcadas com < são da sua saída e as linhas marcadas com > são da saída esperada. A saída do seu programa fica gravada em execucao/saida\_obtida.txt.

Para usar o make é preciso ter o gcc e o make instalados. No Linux e no macOS eles normalmente já estão disponíveis (no macOS, instale as ferramentas de linha de comando com `xcode-select --install`, se necessário). No Windows, use o WSL ou o MSYS2.

Para rodar o programa manualmente com um caso de teste, redirecione o arquivo de entrada do caso:

```
./exclui_chaves < casos-teste/9/entrada.txt
```

Também é possível rodar `./exclui_chaves` e digitar a entrada no teclado.

## Dicas Importantes:

- A entrada e a saída já são tratadas no arquivo fornecido para ler e imprimir os dados no formato esperado pela questão. Vocês devem APENAS implementar a função solicitada no problema
- Para cada chave, calcule o compartimento com a função hash e percorra somente a lista desse compartimento. Percorrer a tabela inteira imprime registros que não deveriam ser examinados, e os casos de teste falham
- Chame imprime\_chave para cada registro cuja matrícula for comparada com a chave procurada, inclusive o registro que contém a chave. Ao encontrar a chave, pare de percorrer a lista
- As listas não são ordenadas pela matrícula. Para concluir que uma chave não existe, é preciso chegar ao fim da lista
- Uma chave pode cair num compartimento vazio (tab[h] igual a NULL). Nesse caso não há registro para examinar
- Quando o registro excluído é o primeiro da lista, é o próprio compartimento tab[h] que passa a apontar para o registro seguinte. Nos demais casos, quem muda é o campo prox do registro anterior
- Não use a função busca antes de excluir, pois ela não imprime os registros examinados e faria a lista ser percorrida duas vezes
- Veja outras dicas em http://www.ic.uff.br/~vanessa/courses/runcodes.html
