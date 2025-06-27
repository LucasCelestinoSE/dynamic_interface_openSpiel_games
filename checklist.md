### Checklist para Finalizar o Projeto

---

#### Fase 1: Reorientação e Análise do Estado Atual
O objetivo aqui é lembrar o que o projeto faz, como ele funciona e qual o seu estado atual.

-   [ ] **1. Configurar o Ambiente e Compilar:**
    -   Verifique se todas as dependências (`raylib`, `open_spiel`, `abseil-cpp`) estão corretamente instaladas e configuradas no `CMakeLists.txt`.
    -   Tente compilar o projeto do zero no diretório `build`. Anote e corrija quaisquer erros de compilação.

-   [ ] **2. Executar e Testar Manualmente:**
    -   Se compilar, execute o programa.
    -   O que aparece na tela? O que funciona? O que está quebrado ou incompleto?
    -   Anote o comportamento atual para saber o ponto de partida.

-   [ ] **3. Revisar o Código Fonte Principal:**
    -   Leia o `src/main.cc` para entender o loop principal do jogo e como a `raylib` é inicializada.
    -   Analise os arquivos em `src/interface_graphical/` para entender como o tabuleiro e as peças são desenhados.
    -   Verifique a pasta `src/open_spiel/` para ver como (e se) a integração com a biblioteca OpenSpiel foi iniciada.

-   [ ] **4. Revisar o `README.md`:**
    -   Verifique se você deixou alguma anotação sobre os objetivos do projeto ou como executá-lo.

---

#### Fase 2: Desenvolvimento e Funcionalidades Faltantes
Com base na análise anterior, o foco agora é implementar o que falta para o jogo ser funcional.

-   [ ] **1. Integração Core com OpenSpiel:**
    -   Implementar a lógica para carregar um jogo específico do OpenSpiel (ex: Xadrez, Jogo da Velha).
    -   Criar a comunicação de duas vias:
        -   A interface gráfica (cliques do mouse) deve gerar movimentos válidos no estado do jogo do OpenSpiel.
        -   O estado do jogo no OpenSpiel (posições das peças, turno do jogador) deve ser refletido na interface gráfica da `raylib`.

-   [ ] **2. Completar a Interface Gráfica (Raylib):**
    -   Garantir que a interface possa desenhar qualquer estado de tabuleiro vindo do OpenSpiel.
    -   Implementar feedback visual para o jogador: destacar a peça selecionada, mostrar movimentos possíveis, indicar o turno atual.
    -   Criar telas ou menus básicos: menu principal para selecionar o jogo, tela de vitória/derrota/empate.

-   [ ] **3. Lógica de Interação do Usuário:**
    -   Refinar a lógica de arrastar e soltar (ou clicar) para mover as peças.
    -   Implementar a validação de movimentos usando as regras do OpenSpiel (não permitir movimentos ilegais).

-   [ ] **4. Suporte Dinâmico a Jogos (Opcional, mas sugerido pelo nome do projeto):**
    -   Criar um mecanismo para que o usuário possa escolher qual jogo do OpenSpiel quer jogar, e a interface se adapte dinamicamente (se for o objetivo).

---

#### Fase 3: Polimento e Finalização
Com o jogo funcional, o foco muda para a qualidade e a experiência do usuário.

-   [ ] **1. Refatoração e Limpeza de Código:**
    -   Organize o código, remova código comentado ou de teste.
    -   Crie funções e classes para evitar repetição e melhorar a legibilidade.

-   [ ] **2. Tratamento de Erros e Casos Especiais:**
    -   O que acontece se um arquivo de imagem não for encontrado?
    -   O que acontece ao tentar um movimento inválido? O programa deve lidar com isso de forma elegante.

-   [ ] **3. Documentação do Código e do Projeto:**
    -   Adicione comentários em partes complexas do código.
    -   Atualize o `README.md` com uma descrição final do projeto, como compilá-lo e como jogar.

-   [ ] **4. Build Final:**
    -   Limpe o diretório de build e faça uma compilação final em modo `Release`.
    -   Crie um pacote ou um arquivo zip com o executável e os assets necessários para que outra pessoa possa jogar.
