#include <stdint.h>
#include <utils.h>
#include <spi.h>
#include <stm32f10x.h>
#include <stdbool.h>


int __attribute((noreturn)) main(void) {

SPI_Config();

cmd(0xAF);		//Display ON
cmd(0xB0);

while (1)
{
	cmd(0xE3);  // nop();
}


}
