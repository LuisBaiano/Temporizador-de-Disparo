#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"

/* Configuração de Hardware */
#define BUTTON_PIN   5   ///< Pino GPIO do botão (Botão A do BitDogLab)
#define BLUE_PIN    12   ///< Pino GPIO do LED azul (RGB)
#define RED_PIN     13   ///< Pino GPIO do LED vermelho (RGB)
#define GREEN_PIN   11   ///< Pino GPIO do LED verde (RGB)

/* Constantes do Sistema */
#define DEBOUNCE_TIME_MS   250  ///< Tempo mínimo entre pressionamentos válidos (debounce)
#define ALARM_DELAY_MS    3000  ///< Atraso entre mudanças de estado dos LEDs

/* Variáveis Globais de Estado */
static volatile bool busy = false;            ///< Flag de bloqueio durante operação
static volatile uint32_t last_press_time = 0; ///< Timestamp do último pressionamento válido

/**
 * @brief Função de callback do temporizador para transições de estado
 * 
 * @param id ID do alarme (não utilizado)
 * @param user_data Próximo estado codificado como inteiro (3: todos desligados, 2: verde, 1: vermelho+verde)
 * @return int64_t Sempre retorna 0 (alarme de disparo único)
 * 
 * @details Gerencia as transições de estado dos LEDs a cada 3 segundos:
 * - Estado 1: Desliga LED azul (vermelho+verde permanecem)
 * - Estado 2: Desliga LED vermelho (verde permanece)
 * - Estado 3: Desliga LED verde e libera sistema
 */
int64_t alarm_callback(alarm_id_t id, void *user_data) {
    uint32_t led_state = (uint32_t)user_data;

    switch (led_state) {
        case 3:  // Estado final - todos LEDs desligados
            gpio_put(GREEN_PIN, 0);
            busy = false;
            break;
        case 2:  // Segunda transição - LED vermelho desliga
            gpio_put(RED_PIN, 0);
            add_alarm_in_ms(ALARM_DELAY_MS, alarm_callback, (void*)3, false);
            break;
        case 1:  // Primeira transição - LED azul desliga
            gpio_put(BLUE_PIN, 0);
            add_alarm_in_ms(ALARM_DELAY_MS, alarm_callback, (void*)2, false);
            break;
    }
    return 0;
}

/**
 * @brief Rotina de serviço de interrupção do botão com debounce
 * 
 * @param gpio Número do GPIO que gerou a interrupção
 * @param events Tipo de evento (detecção de borda)
 * 
 * @details Acionada na borda de descida (pressionamento). Implementa debounce software
 * e inicia sequência dos LEDs se o sistema estiver livre. Configurado com pull-up
 * para hardware BitDogLab (botão ativo em nível baixo).
 */

void button_isr(uint gpio, uint32_t events) {
    if (gpio != BUTTON_PIN) return;

    uint32_t now = to_ms_since_boot(get_absolute_time());
    
    // Verificação de debounce e estado ocupado
    if ((now - last_press_time) > DEBOUNCE_TIME_MS && !busy) {
        busy = true;  // Bloqueia sistema durante operação
        
        // Ativa todos os LEDs
        gpio_put(BLUE_PIN, 1);
        gpio_put(RED_PIN, 1);
        gpio_put(GREEN_PIN, 1);
        
        // Agenda primeira transição de estado
        add_alarm_in_ms(ALARM_DELAY_MS, alarm_callback, (void*)1, false);
        
        last_press_time = now;  // Atualiza timestamp
    }
}

/**
 * @brief Ponto principal de execução do programa
 * 
 * Inicializa periféricos e entra em modo de baixo consumo.
 * 
 * Insere um sleep_ms(150) para reduzir o uso da CPU e permitir tempo de leitura do sinal do botão
 */

int main() {
    stdio_init_all();

    // Configuração dos LEDs
    gpio_init(BLUE_PIN);
    gpio_set_dir(BLUE_PIN, GPIO_OUT);
    gpio_put(BLUE_PIN, 0);

    gpio_init(RED_PIN);
    gpio_set_dir(RED_PIN, GPIO_OUT);
    gpio_put(RED_PIN, 0);

    gpio_init(GREEN_PIN);
    gpio_set_dir(GREEN_PIN, GPIO_OUT);
    gpio_put(GREEN_PIN, 0);

    // Configuração do botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);  // Botão ativo em nível baixo
    
    // Configuração de interrupção
    gpio_set_irq_enabled_with_callback(
        BUTTON_PIN, 
        GPIO_IRQ_EDGE_FALL,  // Detecta pressionamentos (borda de descida)
        true, 
        &button_isr
    );

    while (1) {
        sleep_ms(150);
    }

}