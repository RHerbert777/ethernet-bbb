#include <stddef.h>
#include <stdint.h>

#include "board.h"
#include "eth.h"
#include "net.h"

static uint8_t quadro_rx[1536];
static const uint8_t ip_local[4] = {192, 168, 10, 2};

int main(void)
{
    uint8_t mac_local[6];

    board_init();
    board_read_mac(mac_local);

    if (eth_init(mac_local) != 0) {
        for (;;) {
            /* Ponto para sinalizar falha de inicialização por UART ou LED. */
        }
    }

    net_init(mac_local, ip_local);

    for (;;) {
        int tamanho = eth_receive(quadro_rx, sizeof quadro_rx);

        if (tamanho > 0) {
            net_handle_frame(quadro_rx, (size_t)tamanho);
        }
    }
}