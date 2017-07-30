#include <stdio.h>
#include <string.h>

#include "udc_protocol.h"
#include "udc_datatype.h"

int main(void){

	UDC_CA_DATA_t data;
	memset(&data, 0, sizeof (data));

	udc_cadata_write(data);
	return 0;
}
