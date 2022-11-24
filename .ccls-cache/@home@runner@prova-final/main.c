#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tcarro {
  int ano;
  char modelo[20];
  char cor[20];
};

// cores
#define Red "\033[031m"
#define Green "\033[032m"
#define Yellow "\033[032m"
#define Blue "\033[34m"
#define White "\033[0m"

// subrotinas
void limpar() { system("clear"); }

void calibragem(int calibrar, int opc, int *contc, int *carro) {
  printf("Informe a pressão em libras para a calibragem: ");
  scanf("%d", &calibrar);
  opc = 6;
  if (*carro > 0) {
    while (opc != 5) {
      printf("Quais rodas vai querer calibrar\n\n");
      printf("[1] - Roda da frente esquerda\n");
      printf("[2] - Roda da frente direita\n");
      printf("[3] - Roda traseira esquerda\n");
      printf("[4] - Roda traseira direita\n");
      printf("[5] - Encerar a calibragem\n");
      scanf("%d", &opc);
      switch (opc) {
      case 1:
        limpar();
        printf("%sRoda 1 calibrada!%s\n", Green, White);
        *contc = *contc + 1;
        break;
      case 2:
        limpar();
        printf("%sRoda 2 calibrada!%s\n", Green, White);
        *contc = *contc + 1;
        break;
      case 3:
        limpar();
        printf("%sRoda 3 calibrada!%s\n", Green, White);
        *contc = *contc + 1;
        break;
      case 4:
        limpar();
        printf("%sRoda 4 calibrada!%s\n", Green, White);
        *contc = *contc + 1;
        break;
      case 5:
        limpar();
        printf("Encerrando calibragem\n");
        break;
      default:
        limpar();
        printf("%sInforme uma opção válida!%s\n", Red, White);
      }
    }
    *carro = *carro - 1;
  } else {
    printf("%sSem carros na fila%s\n", Red, White);
  }
}

void menu(int *opcao) {
  printf("              Bem vindo ao Menu            \n\n");
  printf("Selecione a opção que deseja através dos números\n\n");
  printf("[1] - Adicionar um carro na fila\n");
  printf("[2] - Abastecimento  \n");
  printf("[3] - Retirar um carro da fila \n");
  printf("[4] - Calibrar Pneus \n");
  printf("[5] - Exibir carros na fila de espera \n");
  printf("[6] - Relatórios \n");
  printf("[7] - Encerrar  \n\n");
  printf("Opção selecionada: ");
  scanf("%d", &*opcao);
  printf("\n\n\n");
  system("clear");
}

void menuf(char *relatorio) {
  fflush(stdin);
  __fpurge(stdin);
  printf("Selecione a opção que deseja através das letras\n\n");
  printf("[a] - Quantidade de litros vendida\n");
  printf("[b] - Valor total arrecadado com as vendas  \n");
  printf("[c] - Quantidade de carros atendidos \n");
  printf("[d] - Quantidade de combustível restante no tanque \n");
  printf("[e] - Gerar arquivo para impressão  \n");
  printf("[f] - voltar ao menu anterior.  \n\n");

  printf("Opção selecionada: ");
  scanf("%c", &*relatorio);
}

void abastecer(int *carro, float *combustivel, int valor,
               float *combustivel_vendido, float *litros_vendidos, int *cont) {
  printf("Quantidade de litros restante: %s%.2f%s\n", Blue, *combustivel,
         White);
  printf("informe a quantidade de combustivel a ser abastecida: ");
  scanf("%f", &*combustivel_vendido);
  system("clear");
  if (*carro > 0) {
    if (*combustivel_vendido <= *combustivel) {
      *litros_vendidos = *litros_vendidos + *combustivel_vendido;
      *combustivel = *combustivel - *combustivel_vendido;
      printf("\n%sCarro abastecido%s\n", Blue, White);
      *carro = *carro - 1;
    } else {
      if (*combustivel == 0) {
        printf("%sTanque vazio%s\n", Red, White);
        printf("%sAbastacimento não realizado\n%s", Red, White);
        *carro = *carro - 1;
      } else {
        printf(
            "\n%sQuantidade de combustível no tanque insuficiente para "
            "abastecer%s \n\n Quantidade de Combustivel disponivel: %s%.2f%s\n",
            Red, White, Blue, *combustivel, White);
        printf("%sO seu carro retornou a fila,Tente novamente o processo%s\n",
               Blue, White);
      }
    }
  } else {
    printf("Não há carros na fila");
  }
}
void escreveTcarro(struct Tcarro *atendidos, int *cont, int *i) {
  for (int i = *cont - 1; i <= 0; i--) {
    printf("%sAno do carro: %d%s\n", Blue, atendidos[i].ano, White);
    printf("%scor: %s%s\n",Green, atendidos[i].cor, White);
    printf("%sModelo do carro: %s%s\n", Red, atendidos[i].modelo, White);
  }
}

// codigo principal
int main(void) {
  FILE *arquivo;
  int capacidade, opcao, carro, abastecidos, cont, contc, calibrar, opc, i;
  char relatorio;
  float combustivel, litros_vendidos, valor, combustivel_vendido, venda;
  carro = 0;cont = 0;i = 0;combustivel = 200;litros_vendidos = 0;contc = 0;
  arquivo = fopen("arquivo.txt", "w");
  if (arquivo == NULL){
    printf("Erro ao abrir o arquivo.\n");
  }
  struct Tcarro *atendidos;
  atendidos = (struct Tcarro*)malloc((cont + 1) * sizeof(struct Tcarro));
  // espera = maloc(sizeof(struct Tcarro));
  // atendidos = maloc(sizeof(struct Tcarro));
  printf("              Autor: João Victor Dos Santos Gomes\n\n");
  printf("Esse programa é responsavel por solicitar ao usuario um valor do "
         "combustivel e \ntambem o tamanho da fila que o estabelecimento "
         "suportará através de um menu interativo \n\n\n");

  printf("informe o valor do combustível: ");
  scanf("%f", &valor);
  if (valor <= 0) {
    while (valor <= 0) {
      printf("%s valor inválido, digite novamente: %s", Red, White);
      scanf("%f", &valor);
    }
  }
  printf("\n");
  printf("informe a capacidade de carros do estabeleciomento: ");
  scanf("%d", &capacidade);
  if (capacidade <= 0) {
    while (capacidade <= 0) {
      printf("%s valor inválido, digite novamente: %s", Red, White);
      scanf("%d", &capacidade);
    }
  }
  //leitura da fila de espera
  struct Tcarro *espera;
  espera = (struct Tcarro*)malloc((capacidade + 1) * sizeof(struct Tcarro));
  
  printf("\n");
  system("clear");
  printf("O valor do Combustível de hoje é de %s%.2fR$%s e o posto de gasolina "
         "suporta %s%d%s carros na fila de espera\n\n",
         Blue, valor, White, Blue, capacidade, White);
  menu(&opcao);
  while (opcao != 7) {
    switch (opcao) {
    case 1:
      if (carro == capacidade) {
        printf("%scapacidade máxima da fila atingida%s\n\n%sVolte mais "
               "tarde!%s\n\n",
               Red, White, Green, White);
        break;
      } else {
        printf("informe o ano do carro: ");
        scanf("%d", &espera[carro].ano);
        fflush(stdin);
        __fpurge(stdin);
        printf("informe a cor do carro: ");
        fgets(espera[carro].cor, 20, stdin);
        espera[carro].cor[strcspn(espera[carro].cor, "\n")] = 0;
        fflush(stdin);
        __fpurge(stdin);
        printf("informe o modelo do carro: ");
        fgets(espera[carro].modelo, 20, stdin);
        espera[carro].modelo[strcspn(espera[carro].modelo, "\n")] = 0;
        fflush(stdin);
        __fpurge(stdin);
        printf("%scarro adicionado!%s\n", Blue, White);
        carro++;
        break;
      }
    case 2:
      atendidos[cont] = espera[00];
      for (int i = 0; i <= carro; i++) {
        espera[i] = espera[i + 1];
      }
      cont++;
      abastecer(&carro, &combustivel, valor, &combustivel_vendido, &litros_vendidos, &cont);
      atendidos = (struct Tcarro*)realloc(atendidos, (cont + 2) * sizeof(struct Tcarro));
      break;
    case 3:
      if (carro > 0) {
        for (int i = 0; i <= carro; i++) {
          espera[i] = espera[i + 1];
        }
        carro--;
        printf("%sCarro retirado com sucesso%s\n", Blue, White);
      } else {
        printf("%sSem carros na fila%s\n", Red, White);
      }
      break;
    case 4:
      calibragem(calibrar, opc, &contc, &carro);
      break;
    case 5:
      printf("\n%sexibindo quantidade de carros na lista de espera: %d%s\n\n",Blue, carro, White);
      for (int i = carro - 1; i >= 0; i--) {
        printf("%s%d° Carro%s\n",Green,i+1, White);
        printf("%sAno do carro: %d%s\n", Blue,espera[i].ano, White);
        printf("%scor: %s%s\n", Green, espera[i].cor, White);
        printf("%sModelo do carro: %s%s\n", Red, espera[i].modelo, White);
        printf("\n\n");
      }
      break;
    case 6:
      menuf(&relatorio);
      system("clear");
      while (relatorio != 'f') {
        system("clear");
        switch (relatorio) {
        case 'a':
          printf("Foram vendidos %.2f litros\n", litros_vendidos);
          break;
        case 'b':
          printf("O valor total arrecadado com as vendas foi de %.2f R$\n", litros_vendidos * valor);
          break;
        case 'c':
          for (int i = cont - 1; i >= 0; i--) {
            printf("%s%d° Carro%s\n",Green,i+1, White);
            printf("%s%d° Carro%s\n",Green,i+1, White);
            printf("%sAno do carro: %d%s\n", Blue,atendidos[i].ano, White);
            printf("%scor: %s%s\n", Green, atendidos[i].cor, White);
            printf("%sModelo do carro: %s%s\n", Red, atendidos[i].modelo, White);
            printf("\n\n");
          }
          printf("%sForam atendidos %s%d%s carros%s\n", Blue, Green,cont, Blue, White);
          break;
        case 'd':
          printf("restam %.2f litros de combustivel no tanque\n\n",combustivel);
          break;
        case 'e':
          printf("gerando arquivo para impressão\n");
          fprintf(arquivo,"Foram vendidos %.2f litros\n\n", litros_vendidos);
          fprintf(arquivo, "O valor total arrecadado com as vendas foi de %.2f R$\n\n", litros_vendidos * valor);
          fprintf(arquivo, "Foram atendidos %d carros\n\n", cont);
          for (int i = cont - 1; i >= 0; i--) {
            fprintf(arquivo, "Ano do carro: %d\n", atendidos[i].ano);
            fprintf(arquivo, "cor: %s\n", atendidos[i].cor);
            fprintf(arquivo, "Modelo do carro: %s\n", atendidos[i].modelo);
            fprintf(arquivo, "\n\n");
          }
          fprintf(arquivo, "restam %.2f litros de combustivel no tanque\n\n",combustivel);
          fclose(arquivo);
          break;
        case 'f':
          system("clear");
          limpar();
          break;
        default:
          printf("%sdigite apenas uma opção válida%s\n\n", Red, White);
        }
        menuf(&relatorio);
      }
      limpar();
      break;
    case 7:
      printf("     programa Encerrado");
      break;
    default: {
      printf("digite apenas uma opção válida: ");
    }
    }
    menu(&opcao);
  }
  return 0;
}