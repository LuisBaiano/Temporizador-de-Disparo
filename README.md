# **Temporizador de Disparo utilizando o Raspberry Pi Pico W**

**Autor: Luis Felipe Pereira de Carvalho**

**Técnico em Analises e Desenvolvimento de Sistemas - SENAI**

**Graduando em Bacharelado de Engenharia de Computação - UEFS**

## Índice

1. Objetivos
2. Descrição
3. Funcionalidades
4. Requisitos do Projeto
5. Como Executar o Programa
6. Estrutura do Código
7. Referências
8. Demonstrativo em Vídeo

## 1. Objetivos

Este projeto tem como objetivo implementar um sistema de temporização para o acionamento de LEDs utilizando o microcontrolador Raspberry Pi Pico W. A seguir, estão listados os principais objetivos a serem alcançados:

1. **Acionamento dos LEDs via Botão:**
   * Ao pressionar o botão (pushbutton), todos os três LEDs (azul, vermelho e verde) devem acender simultaneamente.
2. **Temporização de 3 Segundos:**
   * Após o acionamento do botão, implementar um temporizador de 3 segundos (3.000 ms) utilizando a função `add_alarm_in_ms()` do Pico SDK.
   * Após 3 segundos, desligar um LED, mantendo os outros dois acesos.
   * Após mais 3 segundos, desligar um segundo LED, deixando apenas um LED aceso.
   * Após mais 3 segundos, desligar o último LED.
3. **Funções de Call-back:**
   * Implementar a mudança de estado dos LEDs em funções de call-back do temporizador, seguindo o exemplo da função `turn_off_callback()`.
4. **Bloqueio de Novo Acionamento:**
   * Garantir que o botão só possa ser acionado novamente após o último LED ser desligado.
   * Durante a execução da temporização, o botão não deve iniciar uma nova chamada da função call-back.
5. **Integração com Ferramenta BitDogLab:**
   * Realizar um experimento utilizando a ferramenta educacional BitDogLab, conectando o LED RGB (GPIOs 11, 12 e 13) e o Botão A (GPIO 05) para validar o funcionamento do código.
6. **Opcional: Implementação de Debounce:**
   * Implementar uma rotina em software para mitigar o efeito de bouncing no botão (software debounce), garantindo um acionamento mais estável e confiável.

## 2. Descrição

Este projeto utiliza a placa Raspberry Pi Pico para controlar um conjunto de LEDs RGB através de um botão. A cada acionamento, uma sequência de estados é iniciada, desligando os LEDs um a um com um intervalo de 3 segundos. O código emprega interrupções para detecção do botão e timers para controle de tempo.

### Funcionamento do Sistema:

1. O botão é acionado.
2. Todos os LEDs acendem ao mesmo tempo.
3. Após 3 segundos, um LED se apaga.
4. Após mais 3 segundos, um segundo LED se apaga.
5. Após mais 3 segundos, o último LED se apaga.
6. O sistema retorna ao estado inicial, aguardando um novo acionamento do botão.

## 3. Funcionalidades

* Interrupção para detecção de acionamento do botão.
* Implementação de debounce via software.
* Controle de LEDs com transição temporizada.
* Uso de timers para gerenciamento das mudanças de estado.

## 4. Requisitos do Projeto

* Placa Raspberry Pi Pico (RP2040)
* Ambiente de desenvolvimento configurado (SDK do RP2040, compilador C/C++)
* LEDs RGB conectados aos pinos 11, 12 e 13
* Botão conectado ao pino 5

## 5. Como Executar o Programa

### 1. Configuração do Ambiente

* Instale o SDK do Raspberry Pi Pico seguindo a documentação oficial.
* Configure a ferramenta de build `CMake` e o compilador ARM.

### 2. Compilação do Código

* Clone o repositório ou copie o código para um diretório local.
* No terminal, navegue até o diretório do projeto e execute:
  ```sh
  mkdir build && cd build
  cmake ..
  make
  ```

### 3. Upload para a Raspberry Pi Pico W

* Conecte a Raspberry Pi Pico ao computador enquanto segura o botão `BOOTSEL`.
* Copie o arquivo `.uf2` gerado para a unidade que aparecerá no sistema.
* A Pico será reiniciada automaticamente e executará o código.

## 6. Estrutura do Código

* **Definição de pinos** : Configuração dos GPIOs para LEDs e botão.
* **Callback do alarme** : Função que controla a sequência de LEDs.
* **Interrupção do botão** : Implementa debounce e inicia a sequência.
* **Main** : Inicializa os periféricos e configura as interrupções.

## 7. Referências

* [Documentação da Raspberry Pi Pico](https://www.raspberrypi.com/documentation/microcontrollers/)
* [RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)

## 8. Demonstrativo em Vídeo

[Link para o vídeo demonstrativo](https://youtu.be/2tiSFT5_B-8)
