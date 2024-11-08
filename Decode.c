/* decryption of sizes */


int get_encoding_bytes(const char *encoding) {
    if (strcmp(encoding, "-US-ASCII") == 0) {
        return 1;
    } else if (strcmp(encoding, "-UTF-8") == 0) {
        return 1; 
    } else if (strcmp(encoding, "-UTF-16") == 0) {
        return 2;
    } else {
        printf("Unsupported encoding type: %s\n", encoding);
        exit(1);
    }
}





void size_decryption(FILE *pf1, int *size_txt)
{
	int file_buff = 0, i;
	int ch, bit_msg;
	for (i = 0; i < 8; i++)
	{
		ch = fgetc(pf1);
		bit_msg = (ch & 1);
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}
	}
	*size_txt = file_buff;
}

/* decryption of strings*/
void string_decryption(FILE *pf1,char *strng,int size, int bytes)
{
	int file_buff=0, i, j=0, k=0;
	int ch, bit_msg;
        int total_bits = size * 8 * bytes;
	for (i = 0; i < total_bits; i++)
	{
		j++;
		ch = fgetc(pf1);
		bit_msg = (ch & 1);
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}

		if ( j == 8 * bytes)
		{
                    for (int b = bytes_per_char - 1; b >= 0; b--) {
                        strng[k + b] = (file_buff >> (8 * b)) & 0xFF;
                    } 
			j=0;
			k+=bytes;
			file_buff = 0;
		}
	}
	strng[k] = '\0';
}
/* decryption of secret message*/
void secret_decryption(int size_txt, FILE *pf1, FILE *pf2)
{
	int file_buff=0, i, j = 0, k = 0;
	int ch,bit_msg;
	char output[250] = {0};
	for (i = 0; i < (size_txt * 8); i++)
	{
		j++;
		ch = fgetc(pf1);
		bit_msg = (ch & 1);
		if (bit_msg)
		{
			file_buff = (file_buff << 1) | 1;
		}
		else
		{
			file_buff = file_buff << 1;
		}

		if ( j == 8)
		{
			putc(file_buff, pf2);
			output[k++] = file_buff;
			j=0;
			file_buff = 0;
		}
	}
	printf("\n*** Secret Text Is ==> %s\n\n", output);
}
int Decode(char *argv_2, char *argv_4, char *encoding)
{
	FILE *pf1, *pf2;
	
	int size, size1, size_txt;

        int bytes_per_char = get_encoding_bytes(encoding);

	//opening Image File
	if((pf1 = fopen(argv_2, "r")) == NULL) 
	{
		printf("Could not open file %s.\nAborting\n", argv_2);
		return 1;
	}

	fseek(pf1,54 ,SEEK_SET);
	
	if((pf2 = fopen(argv_4, "w+")) == NULL) 
	{
		printf("Could not open file %s.\nAborting\n", argv_4);
		return 1;
	}

	//magic str
	char magic_strn[20], magic_strn1[20], strng[20];
	int j;

	size_decryption(pf1,&size);
	string_decryption(pf1,magic_strn,size,1);

	printf("\nEnter the  magic string : \t");
	for(j = 0;(magic_strn1[j] = getchar()) != '\n'; j++);
	magic_strn1[j]= '\0';

	int temp;
	temp = strcmp(magic_strn1, magic_strn);

	if(temp)
	{
		printf("\n\t*** Entered Wrong Magic String ***\n");
		return 0;
	}
	else
		printf("\n\t*** Magic String Accepted ***\n\n");

	//password
	char passwd[20], passwd_str[20];

	size_decryption(pf1,&size1);
	string_decryption(pf1,passwd_str,size1,bytes_per_char);

	printf("Enter The Password : \t");
	scanf("%s", passwd);

	temp = strcmp(passwd,passwd_str);

	if(temp)
	{
		printf("\n\t*** Entered Wrong Password ***\n");
		return 0;
	}
	else
		printf("\n\t*** Password Accepted ***\n");

	/*Secret Text */
	size_decryption(pf1, &size_txt);
	secret_decryption(size_txt, pf1, pf2);

	printf("*** The Secret Text Is Copied To ==> %s\n\n", argv_4);

	/* closeing files */
	fclose(pf1);

}

int DecodeImage(char *inputImage, char *outputImage) {
    FILE *input_image, *output_image;

    if ((input_image = fopen(inputImage, "rb")) == NULL) {
        printf("Could not open input image file %s.\n", inputImage);
        return 1;
    }
    if ((output_image = fopen(outputImage, "wb")) == NULL) {
        printf("Could not create output image file %s.\n", outputImage);
        fclose(input_image);
        return 1;
    }

    fseek(input_image, 54, SEEK_SET);

    int ch;
    while (!feof(input_image)) {
        ch = 0;
        for (int bit = 0; bit < 8; bit++) {
            int image_byte = fgetc(input_image);
            if (image_byte == EOF) {
                fclose(input_image);
                fclose(output_image);
                return 0;
            }
            int bit_value = image_byte & 1;
            ch = (ch << 1) | bit_value;
        }
        fputc(ch, output_image);
    }

    fclose(input_image);
    fclose(output_image);
    return 0;
}

