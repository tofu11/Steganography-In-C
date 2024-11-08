#include <criterion/criterion.h>
#include "Steganography.h"

void checkType(char *image, char *text, char *expected, const char *Type) {
    char *outputImage = "output1.bmp";
    char *outputText = "txt1.txt";
    
    // Encode 
    cr_assert_eq(Encoding(image, text, outputImage, Type), 0, 
                 "Encoding failed for encoding type %s", Type);

    // Decode 
    cr_assert_eq(Decode(image, text, Type), 0, 
                 "Decoding failed for encoding type %s", Type);
    
    // Compare
    FILE *File = fopen(outputText, "r");
    char content[1024];
    fscanf(File, "%s", content);
    fclose(File);
    
    cr_assert_str_eq(content, expected, 
                     "Expected decoded text to be '%s', but got '%s'", expected, content);
}

// US-ASCII
Test(type_tests, test01) {
    char *image = "linux.bmp";
    char *text = "Compilers are cool!";
    char *expected = "Compilers are cool!";
    
    checkType(image, text, expected, "-US-ASCII");
}

// UTF-8
Test(type_tests, test02) {
    char *image = "linux.bmp";
    char *text = "Compilers are cool!";
    char *expected = "Compilers are cool!";
    
    checkType(image, text, expected, "-UTF-8");
}

// UTF-16
Test(type_tests, test03) {
    char *image = "linux.bmp";
    char *text = "Compilers are cool!";
    char *expected = "Compilers are cool!";
    
    checkType(image, text, expected, "-UTF-16");
}

// invalid type
Test(type_tests, test04) {
    char *image = "linux.bmp";
    char *text = "Compilers are cool!";
    char *expected = "Compilers are cool!";
    
    cr_assert_eq(Encoding(image, text, "output1.bmp", "INVALID_ENCODING"), 1, 
                 "Expected Encoding to fail for invalid encoding type");
    cr_assert_eq(Decode("output1.bmp", "txt1.txt", "INVALID_ENCODING"), 1, 
                 "Expected Decoding to fail for invalid encoding type");
}

// empty 
Test(type_tests, test05) {
    char *image = "linux.bmp";
    char *text = "";
    char *expected = "";
    
    checkType(image, text, expected, "-UTF-8");
}

Test(steganography_tests, test06) {
    char *image = "linux.bmp";
    char *text = "";
    char *expected = "";
    
    checkType(image, text, expected, "-US-ASCII");
}
