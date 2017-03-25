#include "main.h"

int main(){
	printf("atas-service started\n");

	Atasgps* atasgps = new Atasgps();
	atasgps->connect();
}
