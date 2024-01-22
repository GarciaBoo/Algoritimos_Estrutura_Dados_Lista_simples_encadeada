# Projeto II (SCC0202)

**Autores:**
- Bruna Azevedo Garcia
- Hellen Cristine Silva Rosa

**Compilador:** gcc

**Plataformas utilizadas:** repl.it e vscode

## Objetivo do Projeto

Este programa gerencia informações de sites, armazenando dados como código, nome, relevância, link e palavras-chave associadas. A principal funcionalidade consiste na leitura de um arquivo de entrada ("googlebot.txt"), onde cada linha contém informações de um site, e a inserção desses dados em uma **lista simplesmente encadeada**.

O programa oferece diversas funcionalidades através de um menu interativo, permitindo ao usuário realizar operações como inserção, remoção, atualização de relevância, inserção de palavras-chave, busca por palavra-chave, sugestão de sites e impressão da lista de sites.

## Estruturas de Dados Utilizadas

O programa utiliza uma **lista simplesmente encadeada** pela sua eficiência nas operações de inserção ordenada, remoção e busca. A economia de espaço é otimizada, evitando o uso desnecessário de espaços e garantindo o desempenho adequado do programa.

## Instruções de Uso

Ao iniciar o programa, um menu de opções é apresentado. Conforme o usuário seleciona uma opção, é possível realizar ações específicas na lista. O programa foi projetado de forma intuitiva, com mensagens de instrução para orientar cada ação.

## Justificativas para Escolhas de Estruturas e Implementações

As escolhas do programa foram fundamentadas nas seguintes justificativas:

- **Eficiência:** A lista simplesmente encadeada proporciona eficiência nas operações de inserção ordenada, remoção e busca.

- **Economia de Espaço:** Evita o uso desnecessário de espaços, otimizando o desempenho do programa.

- **Inserção Ordenada:** A função de inserção foi implementada para ordenar os códigos, utilizando uma busca interna para encontrar as posições corretas de inserção.

- **Remoção e Busca Sequencial:** A abordagem sequencial foi escolhida para operações de remoção e busca, demonstrando eficácia no contexto do programa.

- **Busca Não Ordenada:** A busca sequencial foi utilizada para a função de busca, considerando que as palavras-chave não estavam ordenadas, proporcionando flexibilidade para diferentes estilos de busca.

O conjunto de escolhas de estruturas e implementações visa garantir a eficiência e a correção das operações realizadas no programa.
