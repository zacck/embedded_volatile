
#include <stdint.h>

//define address
#define SRAM_ADDRESS1 0x20000004U


int main(void)
{
	uint32_t value = 0;
	// tell the coompiler not to optimoise reads to this var
	uint32_t  volatile *p = (uint32_t *)SRAM_ADDRESS1;

	while(1)
	{
		value = *p;
		if(value) break;

	}

	while(1);
	return 0;
}
