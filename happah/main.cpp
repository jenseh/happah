#include "happah/Happah.h"
#include "happah/testmain.h"

int main(int argc, char** argv) {
    #ifndef TEST
	Happah happah(argc, argv);
	return happah.exec();
    #else
    testmain(argc,argv);
    #endif
}
