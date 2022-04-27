// SUNIL BHENSPALIYA
// 201951157 CSE
// LAB ASSIGNMENT 2

// DES algorithm Ecryption and Decryption 


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
uint64_t roundkeys[16];

char *S_BOX[16];






//function for change char values to int
int Char_To_Int(char a)
{
    if (a >= '0' && a <= '9')
        return a - '0';

    return (a - 'A') + 10;
}
//Apply s -box function 
uint64_t Apply_SBox(uint64_t text)
{
    uint64_t ans = 0;
    int shift = 24;

    for (int i = 3; i >= 0; i--)
    {
        uint8_t temp = (text >> shift) % 256;

        int row = (temp >> 4) % 16;
        int column = temp % 16;

        int first = Char_To_Int(S_BOX[row][2 * column]);
        int second = Char_To_Int(S_BOX[row][2 * column + 1]);

        uint8_t tempAns = first;
        tempAns = (tempAns << 4) | second;

        ans <<= 8;
        ans |= tempAns;

        shift -= 8;
    }

    return ans;
}
//Round function 
uint64_t RoundFunction(uint64_t right_part, uint64_t key_value)
{
    uint64_t part1 = right_part ^ key_value;

    uint64_t part2 = Apply_SBox(part1);

    return part2;
}

//key generate funtion to generate the keys
void GenerateRoundKeys(uint64_t key_value)
{
    for (int i = 0; i < 16; i++)
    {
        roundkeys[i] = (key_value << i) | (key_value >> (32 - i));
    }
}

//Encryption function to encrypt the message
uint64_t Encryption_function(uint64_t pltext)
{
    uint64_t cipher_text = pltext;

    for (int i = 0; i < 16; i++)
    {
        uint64_t l0 = (cipher_text >> 32) % 4294967296; // 4294967296 ==> 2 ^ 32
        uint64_t r0 = cipher_text % 4294967296;         // 4294967296 ==> 2 ^ 32

        uint64_t l1 = r0;
        uint64_t r1 = l0 ^ RoundFunction(r0, roundkeys[i]);

        cipher_text = l1;
        cipher_text <<= 32;
        cipher_text |= r1;
    }

    return cipher_text;
}
//Decryption function for to decrpt the message
uint64_t Decryption_function (uint64_t ciptext)
{
    uint64_t text = ciptext;

    for (int i = 15; i >= 0; i--)
    {
        uint64_t l1 = text >> 32 % 4294967296; // 4294967296 ==> 2 ^ 32
        uint64_t r1 = text % 4294967296;       // 4294967296 ==> 2 ^ 32

        uint64_t r0 = l1;
        uint64_t l0 = r1 ^ RoundFunction(r0, roundkeys[i]);

        text = l0;
        text <<= 32;
        text |= r0;
    }

    return text;
}
//main driver function for DES To encrpty and decrpt
int main()
{

    uint64_t pltxt;
    printf("\n\nEnter Plaintext for Encrptt : \n");
    scanf("%ld", &pltxt);

    uint32_t key_value;
    printf("\nEnter The following key :\n ");
    scanf("%ld", &key_value);

    GenerateRoundKeys(key_value);
//S0
    S_BOX[0] = "637C777BF26B6FC53001672BFED7AB76";
    //S1
    S_BOX[1] = "CA82C97DFA5947F0ADD4A2AF9CA472C0";
    //S2
    S_BOX[2] = "B7FD9326363FF7CC34A5E5F171D83115";
    //S3
    S_BOX[3] = "04C723C31896059A071280E2EB27B275";
    //S4
    S_BOX[4] = "09832C1A1B6E5AA0523BD6B329E32F84";
    //S5
    S_BOX[5] = "53D100ED20FCB15B6ACBBE394A4C58CF";
    //S6
    S_BOX[6] = "D0EFAAFB434D338545F9027F503C9FA8";
    //S7
    S_BOX[7] = "51A3408F929D38F5BCB6DA2110FFF3D2";
    //S8
    S_BOX[8] = "CD0C13EC5F974417C4A77E3D645D1973";
    //S9
    S_BOX[9] = "60814FDC222A908846EEB814DE5E0BDB";
    //S10
    S_BOX[10] = "E0323A0A4906245CC2D3AC629195E479";
    //S11
    S_BOX[11] = "E7C8376D8DD54EA96C56F4EA657AAE08";
    //S12
    S_BOX[12] = "BA78252E1CA6B4C6E8DD741F4BBD8B8A";
    //S13
    S_BOX[13] = "703EB5664803F60E613557B986C11D9E";
    //S14
    S_BOX[14] = "E1F8981169D98E949B1E87E9CE5528DF";
    //S15
    S_BOX[15] = "8CA1890DBFE6426841992D0FB054BB16";

    printf("\nAll the 16 round Keys are Following below:-\n\n");
    for (int i = 0; i < 16; i++){
    printf("%d: %ld :--\n", i, roundkeys[i]);
	}
	//CALL encryption to encrypt the message
    uint64_t ciptext = Encryption_function(pltxt);
 printf("\n\nThe following Encrpted Cipher Text is: %ld\n\n", ciptext);
//call decryption function to decrpt the cipher text 
    uint64_t decrptext = Decryption_function(ciptext);
printf("The following Decrypted Text is : %ld\n\n", decrptext);

    return 0;
}