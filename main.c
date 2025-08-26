#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"    // Biblioteca do FreeRTOS
#include "freertos/task.h"         // Funções para manipulação de tarefas
#include "freertos/queue.h"        // Funções para manipulação de filas
#include "freertos/semphr.h"       // Funções para manipulação de semáforos

// Declaração de semáforos binários
SemaphoreHandle_t xBinarySemaphore1 = NULL; // Semáforo 1
SemaphoreHandle_t xBinarySemaphore2 = NULL; // Semáforo 2
SemaphoreHandle_t xBinarySemaphore3 = NULL; // Semáforo 3 (novo semáforo para terceira tarefa)

// Função da Task1
void Task1(void *pvParameters)
{
    while (1) 
    {
        // A tarefa só prossegue quando o semáforo 1 for dado (liberado)
        if(xSemaphoreTake(xBinarySemaphore1, portMAX_DELAY) == pdTRUE) 
        {
            // Executa a ação da tarefa (impressão da mensagem)
            printf("[Tarefa 1] Executou - Henrique Montone Casagrande Rodrigues\n");
            
            // Aguarda 1 segundo
            vTaskDelay(pdMS_TO_TICKS(1000));
            
            // Libera o semáforo da Task2 para que a Task2 possa ser executada
            xSemaphoreGive(xBinarySemaphore2);
        }
    }
}

// Função da Task2
void Task2(void *pvParameters)
{
    while (1) 
    {
        // A tarefa só prossegue quando o semáforo 2 for dado (liberado)
        if(xSemaphoreTake(xBinarySemaphore2, portMAX_DELAY) == pdTRUE) 
        {
            // Executa a ação da tarefa (impressão da mensagem)
            printf("[Tarefa 2] Executou - Henrique Montone Casagrande Rodrigues\n");
            
            // Aguarda 1 segundo
            vTaskDelay(pdMS_TO_TICKS(1000));
            
            // Libera o semáforo da Task3 para que a Task3 possa ser executada
            xSemaphoreGive(xBinarySemaphore3);
        }
    }
}

// Função da Task3
void Task3(void *pvParameters)
{
    while (1) 
    {
        // A tarefa só prossegue quando o semáforo 3 for dado (liberado)
        if(xSemaphoreTake(xBinarySemaphore3, portMAX_DELAY) == pdTRUE) 
        {
            // Executa a ação da tarefa (impressão da mensagem)
            printf("[Tarefa 3] Executou - Henrique Montone Casagrande Rodrigues\n");
            
            // Aguarda 1 segundo
            vTaskDelay(pdMS_TO_TICKS(1000));
            
            // Libera o semáforo da Task1 para que a Task1 possa ser executada novamente
            xSemaphoreGive(xBinarySemaphore1);
        }
    }
}

// Função principal - app_main
void app_main(void)
{
    // Criação dos semáforos binários
    xBinarySemaphore1 = xSemaphoreCreateBinary();  // Semáforo para controlar Task1
    xBinarySemaphore2 = xSemaphoreCreateBinary();  // Semáforo para controlar Task2
    xBinarySemaphore3 = xSemaphoreCreateBinary();  // Semáforo para controlar Task3

    // Verificando se a criação dos semáforos foi bem-sucedida
    if (xBinarySemaphore1 == NULL || xBinarySemaphore2 == NULL || xBinarySemaphore3 == NULL) 
    {
        printf("Falha ao criar semáforos binários\n");
        return; // Se falhar, retorna e não executa mais
    }

    // Inicializando o primeiro semáforo para que a Task1 comece imediatamente
    xSemaphoreGive(xBinarySemaphore1);

    // Criação das tarefas
    xTaskCreate(Task1,      // Função da tarefa
                "Task1",    // Nome da tarefa
                2048,       // Tamanho da pilha (stack size)
                NULL,       // Parâmetros da tarefa
                5,          // Prioridade da tarefa
                NULL);      // Handle opcional da tarefa

    xTaskCreate(Task2,      // Função da tarefa
                "Task2",    // Nome da tarefa
                2048,       // Tamanho da pilha (stack size)
                NULL,       // Parâmetros da tarefa
                5,          // Prioridade da tarefa
                NULL);      // Handle opcional da tarefa

    xTaskCreate(Task3,      // Função da tarefa
                "Task3",    // Nome da tarefa
                2048,       // Tamanho da pilha (stack size)
                NULL,       // Parâmetros da tarefa
                5,          // Prioridade da tarefa
                NULL);      // Handle opcional da tarefa
}
