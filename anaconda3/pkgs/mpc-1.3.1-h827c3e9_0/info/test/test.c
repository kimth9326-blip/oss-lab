/* From https://www.multiprecision.org/downloads/mpc-1.3.1.pdf */

#include <stdio.h>

#include <mpc.h>

int main (void)
{
    mpc_t x, y, r;
    mpc_init2(x, 256); /* precision exactly 256 bits */
    mpc_init2(y, 256);
    mpc_init2(r, 256);

    mpc_set_d(x, 1.0, MPC_RNDNN);
    mpc_set_d(y, 2.0, MPC_RNDNN);

    mpc_add(r, x, y, MPC_RNDNN);

    printf("Sum should be 3.0: ");
    mpc_out_str(stdout, 10, 0, r, MPC_RNDNN);
    putchar ('\n');

    mpc_clear(x);
    mpc_clear(y);
    mpc_clear(r);
    return 0;
}
