#include "sha1.h"
#include <stdio.h>
#include <string.h>
int main(){
    //char * text = "Hallo";
    char* text = "Franz jagt im komplett verwahrlosten Taxi quer durch Bayern";
    SHA1Context sha;
    int i,err;
    uint8_t Message_Digest[20];
    err = SHA1Reset(&sha);
    if (err)
    {
        printf("SHA1Reset Error %d.\n", err );
        return 1;
    }
    err = SHA1Input(&sha,
        (const unsigned char *) text,
        strlen(text));
    if (err)
    {
        printf("SHA1Input Error %d.\n", err );
        return 1;
    }
    err = SHA1Result(&sha, Message_Digest);
    if (err)
    {
        printf(
        "SHA1Result Error %d, could not compute message digest.\n",
        err );
    }
    else
    {
        printf("\t");
        for(i = 0; i < 20 ; ++i)
        {
            printf("%02X ", Message_Digest[i]);
        }
        printf("\n");
    }
}