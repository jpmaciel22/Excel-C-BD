#include <stdio.h>
#include <stdlib.h>

// definindo a tipagem das pecas que serao inseridas usando struct
struct Peca {
    int numero;
    char nome[50];
    int quantidade;
};

// funcao para exibir o menu
void exibirMenu() {
    printf("\nMenu:\n");
    printf("1. Adicionar peca\n");
    printf("2. Remover peca\n");
    printf("3. Salvar e sair\n");
    printf("Escolha a opcao: ");
}

void main() {
    int quantidadePecas = 0;
    int quantidadetotaldepecas = 1000;
    int opcao;
    struct Peca pecas[quantidadetotaldepecas];
        
        // carregando o arquivo.. se ele existir executar..
        FILE *arquivo = fopen("pecas.csv", "r");
        if (arquivo != NULL) {


        // guarda os caracteres da primeira linha , pois executa até o primeiro \n, assim ''limpando'' a leitura desta mesma linha
        char buffer[100];
        fgets(buffer, sizeof(buffer), arquivo);
        

        // lendo os arquivos especificando qual a tipagem de cada ";" 
        while (fscanf(arquivo, "%d;%s;%d\n", &pecas[quantidadePecas].numero, &pecas[quantidadePecas].nome, &pecas[quantidadePecas].quantidade) != EOF) {
            quantidadePecas++;
            //printf("%d ", quantidadePecas);
        }

        fclose(arquivo);

        printf("Dados carregados do arquivo pecas.csv.\n");
    }
    //printf("%d",sizeof(pecas));
    if (sizeof(pecas)<=0){

        // inserindo a quantidade de pecas que serao registradas
        printf("Digite a quantidade inicial de pecas referentes: ");
        scanf("%d", &quantidadePecas);

        // testa se quantidade é maior q 0...
        if (quantidadePecas <= 0) {
            printf("A quantidade de pecas deve ser maior que zero.\n");
            exit(0);
        }

        // define o array que sera utilizado
        //struct Peca pecas[quantidadePecas];

        // coloca as informacoes da peca para poder preencher a lista
        for (int i = 0; i < quantidadePecas; i++) {
            printf("Digite o numero da peca %d: ", i + 1);
            scanf("%d", &pecas[i].numero);

            printf("Digite o nome da peca %d: ", i + 1);
            scanf("%s", pecas[i].nome);

            printf("Digite a quantidade da peca %d: ", i + 1);
            scanf("%d", &pecas[i].quantidade);
        }
    }
   /* for(int i=0;i<sizeof(pecas);i++){
        printf("%d,%s,%d",pecas[i].numero,pecas[i].nome,pecas[i].quantidade);
    }*/
    // opcoes do menu
    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: // adiciona a peca
            {
                if (quantidadetotaldepecas < sizeof(pecas) / sizeof(pecas[0])) {
                    printf("Digite os dados da nova peca:\n");
                    printf("Digite o numero da nova peca: ");
                    scanf("%d", &pecas[quantidadePecas].numero);

                    printf("Digite o nome da nova peca: ");
                    scanf("%s", pecas[quantidadePecas].nome);

                    printf("Digite a quantidade da nova peca: ");
                    scanf("%d", &pecas[quantidadePecas].quantidade);

                    quantidadePecas++;
                    printf("Peca adicionada com sucesso!\n");
                } else {
                    printf("Nao e possivel adicionar mais pecas. Limite atingido.\n");
                }
            }
                break;
            case 2: // remove a peca
            {
                if (quantidadePecas > 0) {
                    int numeroRemover;
                    printf("Digite o numero da peca a ser removida: ");
                    scanf("%d", &numeroRemover);

                    // procurando a peca com o indice especificado
                    int indiceRemover = -1;
                    for (int i = 0; i < quantidadePecas; i++) {
                        if (pecas[i].numero == numeroRemover) {
                            indiceRemover = i;
                            break;
                        }
                    }

                    // muda a alocacao do indice da peca removendo ela
                    if (indiceRemover != -1) {
                        for (int i = indiceRemover; i < quantidadePecas - 1; i++) {
                            pecas[i] = pecas[i + 1];
                        }
                        quantidadePecas--;
                        printf("Peca removida com sucesso!\n");
                    } else {
                        printf("Peca nao encontrada.\n");
                    }
                } else {
                    printf("Nao ha pecas para remover.\n");
                }
            }
                break;
            case 3: // salva e sai
                {
                // abre o arquivo para poder guardar os dados
                FILE *arquivo = fopen("pecas.csv", "w");

                // verifica se conseguiu abrir o arquivo criado
                if (arquivo == NULL) {
                    printf("Erro ao criar o arquivo CSV.\n");
                    exit(0);
                }

                // escreve a tabelinha dos dados inseridos
                fprintf(arquivo, "Numero;Nome;Quantidade\n");

                // coloca os dados no csv
                for (int i = 0; i < quantidadePecas; i++) {
                    fprintf(arquivo, "%d;%s;%d\n", pecas[i].numero, pecas[i].nome, pecas[i].quantidade);
                }

                // fecha o arquivo
                fclose(arquivo);

                printf("Dados das pecas salvos com sucesso em pecas.csv!\n");
                }
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 3);

    exit(0);
}