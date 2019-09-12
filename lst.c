#include <stdio.h>

#define MAX_N 26
#define MAX_T 2048

typedef struct {

  char id;
  int c;
  int p;
  int d;

} TAREFA;

int main() {

  TAREFA tarefas[MAX_N];
  int n_tarefas, t, i;
  char grade[MAX_T+1];
  int num_preemp, num_trocas_cont;

  while (1) {
    // LEITURA //
    scanf("%d%d", &n_tarefas, &t);
    if (n_tarefas==0 || t==0)
       break;
    for (i=0; i<n_tarefas; ++i) {
       tarefas[i].id = 'A'+i;
       scanf("%d%d%d", &(tarefas[i].c), &(tarefas[i].p), &(tarefas[i].d) );
    }

    // SIMULACAO //

    num_preemp = 0;
    num_trocas_cont = 0;

    // declaracao de auxiliares
    int deadline_abs[n_tarefas];
    int periodo_abs[n_tarefas];
    int comp_abs[n_tarefas];
    char completa[n_tarefas];
    for(int j = 0; j < n_tarefas; j++)
      completa[j] = 0;
    int n_completas = 0;
    int menor_slack = MAX_T;
    int tarefa_menor_slack = 0;

    TAREFA anterior;
    int indice_da_anterior;

    //execucao de cada tempo //
    for(int j = 0; j < t; j++)
    {
      // execucao para cada tarefa // 
      for(int k = 0; k < n_tarefas; k++)
      {
        // 1. Antes de Executar as tarefas, verificar as informacoes de cada tarefa

        // comecou a execucao, setar primeiros deadlines e periodos
        if(j == 0) 
        {
          periodo_abs[k] = tarefas[k].p;
          deadline_abs[k] = tarefas[k].d;
          comp_abs[k] = 0;
        }
        // reset do periodo; setar novos deadlines, periodos e computacoes absolutas
        else if((j % tarefas[k].p == 0) && (completa[k] == 1))
        {
          periodo_abs[k] = ((j / tarefas[k].p)+1) * tarefas[k].p;
          deadline_abs[k] = (((j / tarefas[k].p)+1) * tarefas[k].p) - (tarefas[k].p - tarefas[k].d);
          comp_abs[k] = 0;
          completa[k] = 0;
        }
        // caso a tarefa perca o prazo
        else if((completa[k] == 1) && (deadline_abs[k] < j))
        {
          periodo_abs[k] = ((j / tarefas[k].p)+1) * tarefas[k].p;
          deadline_abs[k] = (((j / tarefas[k].p)+1) * tarefas[k].p) - (tarefas[k].p - tarefas[k].d);
          comp_abs[k] = 0;
          completa[k] = 0;
        }

        ///////////////////////////////////////////////////////////////////////////

        // 2. Calculo para saber qual tarefa vai executar

        // se a tarefa ainda nao foi concluida, calcular tempo de slack
        if(completa[k] == 0)
        {    
          int slack_aux = (deadline_abs[k] - j) - (tarefas[k].c - comp_abs[k]);

          if(slack_aux < menor_slack)
          {
            menor_slack = slack_aux;
            tarefa_menor_slack = k;
          }
          else if(slack_aux == menor_slack)
          {
            if(k < tarefa_menor_slack)
            {
              menor_slack = slack_aux;
              tarefa_menor_slack = k;            
            }
          }
        }
        // se foi concluida, aumenta numero de completas (se (completas == n_tarefas) entao o idle ganha o processador)
        else
        {
          n_completas++;
        }

        ////////////////////////////////////////////////////////////////////////////////

      } // para cada tarefa (k)

      // 3. Calculado o menor slack, executar

      // concluir uma computacao da tarefa com menor slack
      if(n_completas != n_tarefas)
      {
        comp_abs[tarefa_menor_slack]++;

        // testar se a tarefa foi concluida
        if((tarefas[tarefa_menor_slack].c - comp_abs[tarefa_menor_slack]) == 0)
          completa[tarefa_menor_slack] = 1;

        char id = tarefas[tarefa_menor_slack].id;

        // caso a tarefa perca o prazo, ela vai ser exibida em minuscula
        if(deadline_abs[tarefa_menor_slack] < j)
        {
          id = id + 32;
        }

        grade[j] = id;

        // caso estejamos executando uma tarefa e anteriormente na grade
        // houve um idle, aumenta o numero de preempcoes
        if(j>0)
        {
          if(grade[j-1] == '.')
          {
            num_preemp++;
          }
        } 
      }
      // todas as tarefas foram concluidas, idle executa
      else
      {
        grade[j] = '.';

        // caso executamos um idle e a execucao anterior n foi um idle tambem
        // o numero de trocas de contexto aumenta
        if(grade[j-1] != '.')
        {
          num_trocas_cont++;
        }
      }

      ////////////////////////////////////////////////////////////////////////////////

      // 4. Calcular trocas de contexto e preempcoes

      // guardar a ultima execucao em uma variavel para descobrir se ha trocas
      if(j == 0)
      {
        anterior = tarefas[tarefa_menor_slack];
        indice_da_anterior = tarefa_menor_slack;
      }
      else
      {
        // tarefa anterior e diferente da atual
        if((anterior.id != tarefas[tarefa_menor_slack].id) && grade[j-1] != '.')
        {
          num_trocas_cont++;

          // tarefa anterior e diferente e nao tinha acabado
          if(anterior.c - comp_abs[indice_da_anterior] != 0)
          {
            num_preemp++;
          }
          anterior = tarefas[tarefa_menor_slack];
          indice_da_anterior = tarefa_menor_slack;
        }
        else if(grade[j-1] == '.')
        {
          if(grade[j] != '.')
          {
            num_trocas_cont++;
            anterior = tarefas[tarefa_menor_slack];
            indice_da_anterior = tarefa_menor_slack;
          }
        }
      }

      // na ultima execucao, se a tarefa for completada ou estiver em idle, troca_de_contexto++
      if(j == t-1)
      {
        if(completa[tarefa_menor_slack] == 1 || grade[j] == '.')
        {
          num_trocas_cont++;
        }

        if(grade[j] == '.')
        {
          num_preemp++;
        }
      }
      
      menor_slack = MAX_T;
      n_completas = 0;

      ///////////////////////////////////////////////////////////////////////////////////////

    } // para cada tempo (j)

    grade[t] = '\0';

    // RESULTADOS

    printf("%s\n%d %d\n\n", grade, num_trocas_cont, num_preemp);
  }
  return 0;
}