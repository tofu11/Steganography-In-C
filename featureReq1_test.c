#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>
#include "Stegano_header.h"

// Encode text into image
Test(encode, encodeText) {
    int result = Encoding("test_cases/linux.bmp", "test_cases/secret.txt", "test_results/encoded_linux.bmp");
    cr_assert_eq(result, 0, "Encoding should return 0 on success");

    FILE *encoded_image = fopen("test_results/encoded_linux.bmp", "r");
    cr_assert_not_null(encoded_image, "Encoded image file should be created");
    fclose(encoded_image);
}

// Decode encoded text from an image
Test(decode, decodeText) {
    Encoding("test_cases/linux.bmp", "test_cases/secret.txt", "test_results/encoded_linux.bmp");
    int result = Decode("test_results/encoded_linux.bmp", "test_results/decoded_text.txt");
    cr_assert_eq(result, 0, "Decoding should return 0 on success");

    // Check that the decoded text matches the original secret text
    FILE *decoded_text = fopen("test_results/decoded_text.txt", "r");
    FILE *original_text = fopen("test_cases/secret.txt", "r");

    cr_assert_not_null(decoded_text, "Decoded text file should exist");
    cr_assert_not_null(original_text, "Original text file should exist");

    char decoded_content[256], original_content[256];
    fread(decoded_content, sizeof(char), 256, decoded_text);
    fread(original_content, sizeof(char), 256, original_text);

    cr_assert_str_eq(decoded_content, original_content, "Decoded content should match the original content");

    fclose(decoded_text);
    fclose(original_text);
}

// Encode an image into another image
Test(encode, encodeImage) {
    int result = EncodingImage("test_cases/linux.bmp", "test_cases/hidden.bmp", "test_results/encoded_base_with_image.bmp");
    cr_assert_eq(result, 0, "Encoding image should return 0 on success");

    // Check if the encoded image file exists
    FILE *encoded_image = fopen("test_results/encoded_base_with_image.bmp", "r");
    cr_assert_not_null(encoded_image, "Encoded image file with hidden image should be created");
    fclose(encoded_image);
}

// Test for decoding an image from another image
Test(decode, decodeImage) {
    EncodingImage("test_cases/linux.bmp", "test_cases/hidden.bmp", "test_results/encoded_base_with_image.bmp");
    int result = DecodeImage("test_results/encoded_base_with_image.bmp", "test_results/decoded_hidden.bmp");
    cr_assert_eq(result, 0, "Decoding image should return 0 on success");

    // Check if the decoded image matches the original hidden image
    FILE *decoded_image = fopen("test_results/decoded_hidden.bmp", "r");
    FILE *original_hidden = fopen("test_cases/hidden.bmp", "r");

    cr_assert_not_null(decoded_image, "Decoded hidden image file should exist");
    cr_assert_not_null(original_hidden, "Original hidden image file should exist");

    fclose(decoded_image);
    fclose(original_hidden);
}

