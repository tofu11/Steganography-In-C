#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Stegano_header.h"

void sizeDecryptionTest(FILE *pf1, int expected_size) {
    int actual_size = 0;
    size_decryption(pf1, &actual_size);

    cr_assert_eq(actual_size, expected_size,  "size_decryption() should have returned size %d, but got %d", expected_size, actual_size);
}


void stringDecryptionTest(FILE *pf1, const char *expected_string, int size) {
    char actual_string[256] = {0};
    string_decryption(pf1, actual_string, size);

    cr_assert_str_eq(actual_string, expected_string, "string_decryption() should have returned string \"%s\", but got \"%s\"",expected_string, actual_string);
}


void secretDecryptionTest(FILE *pf1, FILE *pf2, int size_txt, const char *expected_output) {
    secret_decryption(size_txt, pf1, pf2);

    rewind(pf2);
    char output[256] = {0};
    fread(output, sizeof(char), size_txt, pf2);
    
    cr_assert_str_eq(output, expected_output, "secret_decryption() should have returned secret text \"%s\", but got \"%s\"",expected_output, output);
}

Test(decode, validDecode) {
    FILE *input_file = tmpfile();  
    FILE *output_file = tmpfile();

    unsigned char mock_data[] = {
        0b01010011, 
        0b01000101, 
        0b01000011, 
        0b01010010, 
        0b01000101, 
        0b01010100  
    };
    

    fwrite(mock_data, sizeof(unsigned char), sizeof(mock_data), input_file);
    rewind(input_file);

    
    Decode("input.dat", "output.dat");

    
    rewind(output_file);
    char output[256] = {0};
    fread(output, sizeof(char), 6, output_file); 

    
    cr_assert_str_eq(output, "SECRET", "Decode() should have returned the secret text \"SECRET\", but got \"%s\"",output);

    fclose(input_file);
    fclose(output_file);
}
