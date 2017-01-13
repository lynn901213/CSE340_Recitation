#include <string.h>
#include <stdio.h>

int main()
{
    char s1[] = "Hello";
    char s2[20] = "world";
    char s3[100];

    char* s4 = "CSE 340: Principles of Programming Languages";
    char* s5 = s4;
    char* s6 = strdup("programming is fun");

    //

    printf("s1 = %s\n", s1);
    printf("s2 = '%s'\n", s2);
    printf("s3 = '%s'\n", s3);
    printf("s4 = '%s'\n", s4);
    printf("s5 = '%s'\n", s5);
    printf("s6 = '%s'\n", s6);

    puts("");

    printf("sizeof(s1) = %lu\n", sizeof(s1));
    printf("sizeof(s2) = %lu\n", sizeof(s2));
    printf("sizeof(s3) = %lu\n", sizeof(s3));
    printf("sizeof(s4) = %lu\n", sizeof(s4));
    printf("sizeof(s5) = %lu\n", sizeof(s5));
    printf("sizeof(s6) = %lu\n", sizeof(s6));

    puts("");

    printf("s1 is stored at %p\n", s1);
    printf("s2 is stored at %p\n", s2);
    printf("s3 is stored at %p\n", s3);
    printf("s4 is stored at %p\n", s4);
    printf("s5 is stored at %p\n", s5);
    printf("s6 is stored at %p\n", s6);

    return 0;
}
