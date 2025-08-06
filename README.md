# Implementação do Algoritmo Simplex de Duas Fases

Este repositório contém o código-fonte para o trabalho da disciplina SME0211-Otimização Linear, do Instituto de Ciências Matemáticas e de Computação (ICMC) da Universidade de São Paulo (USP). O projeto consiste na implementação do algoritmo Simplex, com a abordagem de duas fases e a regra de pivoteamento de Bland, para resolver problemas de otimização linear na forma padrão.

O objetivo principal deste trabalho foi desenvolver uma implementação robusta do algoritmo Simplex em C++. A escolha da linguagem C++ foi motivada por sua eficiência e desempenho, alinhando-se aos requisitos do projeto.

O sistema é capaz de ler problemas de otimização linear em diferentes formatos, incluindo o formato MPS (padrão e comprimido da biblioteca Netlib) e arquivos de texto (.txt) simples.

### Autores
* Felipe Destaole
* João Pedro Farjoun Silva 
* Luís Roberto Piva
* Téo Sobrino Alves

### Professora
* Marina Andretta

## Funcionalidades

* **Resolvedor Simplex de Duas Fases:** Implementação do método Simplex de duas fases para encontrar soluções ótimas em problemas de programação linear. A primeira fase encontra uma solução básica viável e a segunda otimiza essa solução.
* **Regra de Pivoteamento de Bland:** Utilização da regra de Bland para evitar ciclagem e garantir a convergência do algoritmo.
* **Leitor de Múltiplos Formatos:** O programa aceita instâncias nos seguintes formatos:
    * Arquivos `.mps` comprimidos (padrão Netlib).
    * Arquivos `.mps` descomprimidos.
    * Arquivos `.txt` formatados.
* **Conversor MPS para TXT:** Inclui scripts para converter automaticamente instâncias do formato MPS para o formato TXT utilizado pelo resolvedor.
* **Análise de Desempenho:** O programa reporta métricas importantes como tempo de execução, número de iterações em cada fase e o valor da função objetivo.

## Licença

Este projeto é um trabalho acadêmico e está disponível para fins educacionais. Sinta-se à vontade para explorar o código e os conceitos implementados.
