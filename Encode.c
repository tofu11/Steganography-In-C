

#include <opencv2/opencv.hpp>

using namespace cv;


//reading size of image file
int size_of_image(const char *fp1)
{
    const char *filetype = strrchr(fp1,:'.');
    unsigned int width, height;
    if (strcmp(ext, ".bmp") == 0 || strcmp(ext, ".jpg") == 0 ||
        strcmp(ext, ".jpeg") == 0 || strcmp(ext, ".png") == 0 ||
        strcmp(ext, ".tiff") == 0 || strcmp(ext, ".gif") == 0){
	    Mat image = imread(fp1,IMREAD_COLOR);
	    if (image.empty()) {
            printf("Could not open or find the image %s.\n", filename);
            return -1;
        }
	width=image.cols;
        height=image.rows;
    printf("Dimensions of the Image is %d x %d \n", width, height);
    int total_pixels = width * height;
    int total_bits = total_pixels * 3;
    int capacity = total_bits / 8;
    printf("Total Pixels: %d\n", total_pixels);
    printf("Total Bits: %d\n", total_bits);
    printf("Calculated Capacity (characters): %d\n", capacity);


    return capacity;

}
//Entering Secret Message to file
void secret_text(FILE *fp2)
{
    char ch;
    printf("Enter your secret text and press Enter to finish:\n");
    while ((ch = getchar()) != '\n') // Stop at newline instead of EOF
    {
        if (ch == EOF) break; 
        putc(ch, fp2);  
    }
}

//Size Of The Secret Message
int secret_text_size(FILE *fp2)
{
	int size_txt;
	fseek(fp2, 0L, SEEK_END);
	size_txt = ftell(fp2);
	fseek(fp2, 0L, SEEK_SET);
	return size_txt;
}
//bits of text file
int get_bit(char byte, int bit)
{
	return ((byte >> 8 - bit) & 1);
}

//encription of message
void stega_encrypt(FILE *fp1, FILE *fp2, FILE *fp3)
{
	char file_buff = 0, msg_buff = 0, ch;	//temp var for one byte from file and msg
	int i;
	int bit_msg;
	while((msg_buff = fgetc(fp2)) != EOF)
	{
		for(i = 1; i <= 8; i++)
		{
			file_buff = fgetc(fp1);

			int file_byte_lsb = (file_buff & 1);

			bit_msg = get_bit(msg_buff, i);

			if(file_byte_lsb == bit_msg)
			{
				fputc(file_buff, fp3);
			}
			else
			{
				if(file_byte_lsb == 0)
					file_buff = (file_buff | 1);
				else
					file_buff = (file_buff ^ 1);

				fputc(file_buff, fp3);
			}
		}
	}

	/*copying rest of data */
	while(!feof(fp1))
	{
		char tmp_cpy = fgetc(fp1);
		fputc(tmp_cpy,fp3);

	}

	if(msg_buff == EOF)
		printf("\n*** Secret Message Encrypted Successfully ***\n");
	else
		printf("\n*** Failed Encrypting ***\n");
}
//Encription For Strings
void string_encrypt(char *str,FILE *fp1, FILE *fp3)
{

	char file_buff, msg_buff;	//temp var for one byte from file and msg
	int i, j = 0;
	int bit_msg;
	while((msg_buff = str[j]) != '\0')
	{
		for(i = 1; i <= 8; i++)
		{
			file_buff = fgetc(fp1);

			int file_byte_lsb = (file_buff & 1);

			bit_msg = get_bit(msg_buff, i);

			if(file_byte_lsb == bit_msg)
			{
				fputc(file_buff, fp3);
			}
			else
			{
				if(file_byte_lsb == 0)
					file_buff = (file_buff | 1);
				else
					file_buff = (file_buff ^ 1);

				fputc(file_buff, fp3);
			}
		}
		j++;
	}
}
//Encription For Numbers
void size_encrypt(int num,FILE *fp1, FILE *fp3)
{

	char file_buff;	
	int i, j = 0;
	int bit_msg;

	for(i = 1; i <= 8; i++)
	{
		file_buff = fgetc(fp1);

		int file_byte_lsb = (file_buff & 1);

		bit_msg = get_bit(num, i);

		if(file_byte_lsb == bit_msg)
		{
			fputc(file_buff, fp3);
		}
		else
		{
			if(file_byte_lsb == 0)
				file_buff = (file_buff | 1);
			else
				file_buff = (file_buff ^ 1);

			fputc(file_buff, fp3);
		}
	}

}

int Encoding(char *argv_2,char *argv_3,char *argv_4)
{
	FILE *fp1, *fp2, *fp3;

	//opening Image File
	if((fp1 = fopen(argv_2, "r+")) == NULL) 
	{
		printf("Could not open file %s.\nAborting\n", argv_2);
		return 1;
	}

	int size_image = size_of_image(fp1);
	printf("Total %d Charecters can be stored in %s.\n", size_image, argv_2);

	//opening secret text file
	fp2 = fopen(argv_3, "w+");

	//Entering secret text to file
	secret_text(fp2);

	int size_txt = secret_text_size(fp2);
	printf("\nSize of The Secret Message is ==> %d\n", size_txt);

	//Comparing Image Size With Text
	if(size_image < size_txt)
	{
		printf("\n*** The Size Of Message Exceeds the Size of image ***\n");
		return 1;
	}

	//opening destination file
	fp3 = fopen(argv_4, "w+");
	if (fp3== NULL) 
	{
		fprintf(stderr, "Cannot create output file %s\n",argv_4);
		exit(1);
	}

	//copying 54 header file
	int i, c = 0;
	char tmp_cpy;
	rewind(fp1);	//Goes back to the beginning of the file
	for(i = 0;i < 54; i++)
	{
		tmp_cpy = fgetc(fp1);
		fputc(tmp_cpy,fp3);
		c++;
	}

	//checking 54 bytes copyed or not
	if(i == c)
		printf("\n*** Sucessfully copied 54 header bytes ***\n");
	else
	{
		printf("\n*** Failed to copy 54 header bytes ***\n");
		return 0;
	}

	//For Magic String
	char magic_str[10];
	char magic;
	int size;

	printf("\nEnter The Magic String '#' '$' Only : \t");

	for(i = 0; (magic = getchar()) != '\n'; i++)
	{
		if(magic == '#')
		{
			magic_str[i] = magic;
		}
		else if(magic == '$')
		{
			magic_str[i] = magic;
		}
		else
		{
			printf("*** You Entered Wrong Charecters ***\n");
			exit(2);
		}
	}

	magic_str[i] = '\0';
	size = strlen(magic_str);
	printf("Size Of The Magic string is ==> %d\n", size);
	size_encrypt(size,fp1,fp3);
	string_encrypt(magic_str,fp1,fp3);
	printf("*** Magic String Encrypted ***\n");

	//FOR PASSWORD
	char str[20];
	printf("\nEnter the password : \t");

	for (i=0;((str[i] = getchar()) != '\n');i++);
	str[i]= '\0';

	int size1;	
	size1 = strlen(str);
	printf("Size Of The Password is ==> %d\n", size1);
	size_encrypt(size1,fp1,fp3);
	string_encrypt(str,fp1,fp3);
	printf("*** Password Encrypted ***\n");

	//Encryption for Message
	size_encrypt(size_txt,fp1,fp3);
	stega_encrypt(fp1,fp2,fp3);

	/*Clean up before exit */
	fclose(fp1);	
	fclose(fp2);
	fclose(fp3);

	return 0;

}

int EncodingImage(char *inputImage, char *secretImage, char *resultingImage) {
    FILE *input_image, *secret_image, *output_image;

    if ((input_image = fopen(inputImage, "rb")) == NULL) {
        printf("Could not open input image file %s.\n", inputImage);
        return 1;
    }
    if ((secret_image = fopen(secretImage, "rb")) == NULL) {
        printf("Could not open secret image file %s.\n", secretImage);
        fclose(input_image);
        return 1;
    }
    if ((output_image = fopen(resultingImage, "wb")) == NULL) {
        printf("Could not create output file %s.\n", resultingImage);
        fclose(input_image);
        fclose(secret_image);
        return 1;
    }

    // Copy header
    for (int i = 0; i < 54; i++) {
        fputc(fgetc(input_image), output_image);
    }

    int ch;
    while ((ch = fgetc(secret_image)) != EOF) {
        for (int i = 0; i < 8; i++) {
            int byte = fgetc(input_image);
            if (byte == EOF) break;
            int i_val = (ch >> (7 - i)) & 1;
            byte = (byte & ~1) | i_val;
            fputc(byte, output_image);
        }
    }

    // Copy the rest of the image
    while ((ch = fgetc(input_image)) != EOF) {
        fputc(ch, output_image);
    }

    fclose(input_image);
    fclose(secret_image);
    fclose(output_image);
    return 0;
}
