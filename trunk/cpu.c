/*
// Limitation of SIC Simulator
// - read/write only 2 device
// Info
// - 0xF1 - Device for input
// - 0x05 - Device for output
*/

#include<stdio.h>
#include"cpu.h"

/*function init*/
int cpu(void);
void fetch_decode(void);
void execute(void);
void savememory(void);
void register_overflow(void);
int file_device_init(int device_id);
int read_device(int device_id);
void write_device(int device_id, int c);
int load_mem(unsigned char *num, int mode);
void save_mem(int value, unsigned char *target, int mode);

/*variable init*/
/*
*   address : address from instruction
*   path : TA address
*/
unsigned char memory[MAX_ADDRESS] = {0};
int ra = 0, rx = 0, rl = 0, rpc = 0, rsw = 0;
int opcode = 0, xbit = 0, address = 0, path = 0;
FILE *device_input, *device_output;

int cpu(void)
{
    int i;
    
    while(rpc<MAX_ADDRESS-1)
    {
        fetch_decode();
        rpc += 3;
        execute();
        register_overflow();
    }
    savememory();
    return 0;
}
void register_overflow(void)
{
    ra &= 0xFFFFFF;
    rx &= 0xFFFFFF;
    rl &= 0xFFFFFF;
    rpc &= 0xFFFFFF;
    rsw &= 0xFFFFFF;
}