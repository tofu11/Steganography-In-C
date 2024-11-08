#include "Stegano_header.h"

int main(int argc, char *argv[])
{
    int i;
    char *argv_2, *argv_3, *argv_4;
    int is_image = 0; // 0 for text (default), 1 for image
    const char *encoding = "-US-ASCII"; // Default encoding

    switch (argc)
    {
        case 10:
            for (i = 2; i < 10; i++) {
                if (!strcmp(argv[i], "-i"))
                    argv_2 = argv[i + 1];
                else if (!strcmp(argv[i], "-s"))
                    argv_3 = argv[i + 1];
                else if (!strcmp(argv[i], "-o"))
                    argv_4 = argv[i + 1];
                else if (!strcmp(argv[i], "-image"))
                    is_image = 1;
                else if (!strcmp(argv[i], "-text"))
                    is_image = 0;
                else if (!strcmp(argv[i], "-US-ASCII") || !strcmp(argv[i], "-UTF-8") || !strcmp(argv[i], "-UTF-16"))
                    encoding = argv[i];
            }
            if (is_image)
                EncodingImage(argv_2, argv_3, argv_4); 
            else
                Encoding(argv_2, argv_3, argv_4);
            break;
            
        case 9: 
            if (!strcmp(argv[1], "-E"))
            {
                for (i = 2; i < 9; i++)
                {
                    if (!strcmp(argv[i], "-i"))
                        argv_2 = argv[i + 1];
                    else if (!strcmp(argv[i], "-s"))
                        argv_3 = argv[i + 1];
                    else if (!strcmp(argv[i], "-o"))
                        argv_4 = argv[i + 1];
                    else if (!strcmp(argv[i], "-image"))
                        is_image = 1;
                    else if (!strcmp(argv[i], "-text"))
                        is_image = 0;
                    else if (!strcmp(argv[i], "-US-ASCII") || !strcmp(argv[i], "-UTF-8") || !strcmp(argv[i], "-UTF-16"))
                        encoding = argv[i];
                }
                if (is_image)
                    EncodingImage(argv_2, argv_3, argv_4); 
                else
                    Encoding(argv_2, argv_3, argv_4);
                break;
            }
        case 8: 
            if (!strcmp(argv[1], "-E"))
            {
                for (i = 2; i < 8; i++)
                {
                    if (!strcmp(argv[i], "-i"))
                        argv_2 = argv[i + 1];
                    else if (!strcmp(argv[i], "-s"))
                        argv_3 = argv[i + 1];
                    else if (!strcmp(argv[i], "-o"))
                        argv_4 = argv[i + 1];
                }
                Encoding(argv_2, argv_3, argv_4); 
                break;
            }

        case 7: 
            if (!strcmp(argv[1], "-D"))
            {
                for (i = 2; i < 7; i++)
                {
                    if (!strcmp(argv[i], "-i"))
                        argv_2 = argv[i + 1];
                    else if (!strcmp(argv[i], "-o"))
                        argv_4 = argv[i + 1];
                    else if (!strcmp(argv[i], "-image"))
                        is_image = 1;
                    else if (!strcmp(argv[i], "-text"))
                        is_image = 0;
                    else if (!strcmp(argv[i], "-US-ASCII") || !strcmp(argv[i], "-UTF-8") || !strcmp(argv[i], "-UTF-16"))
                        encoding = argv[i];
                }
                if (is_image)
                    DecodeImage(argv_2, argv_4); 
                else
                    Decode(argv_2, argv_4,encoding);
                break;
            }
	case 6: 
            if (!strcmp(argv[1], "-D"))
            {
                for (i = 2; i < 6; i++)
                {
                    if (!strcmp(argv[i], "-i"))
                        argv_2 = argv[i + 1];
                    else if (!strcmp(argv[i], "-o"))
                        argv_4 = argv[i + 1];
                    else if (!strcmp(argv[i], "-image"))
                        is_image = 1;
                    else if (!strcmp(argv[i], "-text"))
                        is_image = 0;
                }
                
                // Default to text decoding if not specified
                if (is_image)
                    DecodeImage(argv_2, argv_4); 
                else
                    Decode(argv_2, argv_4);
                break;
            }

        default:
            printf("\t*** !! Error !! ERROR !! Error !!***\n\n");
            printf("*** EXECUTION ==> ");
            printf("\n\t\t*** ENCODING *** ==> \t./Stegano -E -text|-image -i <input.bmp> -s <secret.txt|secret.bmp> -o <output.bmp>\n\n");
            printf("\t\t*** DECODING *** ==> \t./Stegano -D -text|-image -i <encoded.bmp> -o <decoded.txt|decoded.bmp>\n\n");
            printf("\t\tFOR MORE DETAILS ===> **README**\n");
    }

    return 0;
}

