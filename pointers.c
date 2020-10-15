#include <stdio.h>
#include <stdlib.h>

void
f(void)
{
    int a[4];                       //a : the starting address of array a
    int *b = malloc(16);            //b : the starting address of memory area that has the size of 16 bytes
    int *c;                         //c : garbage value
    int i;

    printf("1: a = %p, b = %p, c = %p\n", a, b, c); //%p : pointer address

    c = a;  //c : the starting address of array a
    for (i = 0; i < 4; i++)
	a[i] = 100 + i;     // a[] = {100, 101, 102, 103}
    c[0] = 200;         // a[] = {200, 101, 102, 103}
    printf("2: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",       //%d : integer variable
	   a[0], a[1], a[2], a[3]);     // a[0] = 200, a[1] = 101, a[2] = 102, a[3] = 103

    c[1] = 300;      // a[1] = 300 --> a[] = {200, 300, 102, 103}
    *(c + 2) = 301;  // a[2] = 301 --> a[] = {200, 300, 301, 103}
    3[c] = 302;      // a[3] = 302 --> a[] = {200, 300, 301, 302}
    printf("3: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    c = c + 1;  // c : the starting address of a[1]
    *c = 400;   // c = a[1] = 400 -> a[] = {200, 400, 301, 302}
    printf("4: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    c = (int *) ((char *) c + 1);               // ((char *)c + 1) -> move 1 byte from a[1]
    *c = 500;                                   // x86 and AMD64 / x86-64 series of processors use the little-endian format
                                                // originally,
                                                // a[1] == 400 == 0x190.  0x190 is stored in the memory as {0x90, 0x01, 0x00, 0x00}
                                                // a[2] == 301 == 0x12D.  0x12D is stored in the memory as {0x2D, 0x01, 0x00, 0x00}
                                                // now,
                                                // *c   == 500 == 0x1F4.  0x1F4 is stored in the memory as {0xF4, 0x01, 0x00, 0x00}
                                                // a[1] = {0x90, 0xF4, 0x01, 0x00} = 0x1F490 = 128144
                                                // a[2] = {0x00, 0x01, 0x00, 0x00} = 0x100 = 256

    printf("5: a[0] = %d, a[1] = %d, a[2] = %d, a[3] = %d\n",
	   a[0], a[1], a[2], a[3]);

    b = (int *) a + 1;                  // b = a[1] = &a[0] + 4byte
    c = (int *) ((char *) a + 1);       // c = &a[0] + 1byte
    printf("6: a = %p, b = %p, c = %p\n", a, b, c);
}

int
main(int ac, char **av)
{
    f();
    return 0;
}
