#include "stdafx.h"
#include <io.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

char option;

char *c2v;
char *dxml[3];

char v2c_filename[256] = {0};
char uxml_filename[256] = {0};
char *current_state_filename;

char base64_alphabet[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int nothing_to_clear = 0;
int nothing_to_format = 0;
int dynamic_memory_supported_key = 0;   


//
// get length of encoded string
//
int base64_encode_get_length(int input_length)
{
    int pad_count = 0;
    int length = 0;

    pad_count = (3 - (input_length % 3)) % 3;

    length = (input_length + pad_count) / 3 * 4;

    return length + 1;
}

//
// use BASE64 to encode string
//
int base64_encode(unsigned char *input, int input_length, char *output)
{
    int i = 0;
    int j = 0;
    int k = 0;

    int length = 0;
    int pad_count = 0;

    unsigned char *input_string = 0;
    unsigned char *temp = 0;

    if (input == 0 || output == 0)
    {
        return 1;
    }

    length = input_length;
    pad_count = (3 - (length % 3)) % 3;

    if (pad_count > 0)
    {
        input_string = (unsigned char *)malloc(length + pad_count);
        if (input_string == 0)
        {
            return 2;
        }
        memset(input_string, 0, length + pad_count);
        memcpy(input_string, input, length);
        temp = input_string;
    }
    else
    {
        temp = input;
    }

    for (i = 0; i < length; i += 3)
    {
        unsigned long val = 0;
        for (j = 0; j < 3; j++)
        {
            val |= *temp++;
            val <<= 8;
        }

        for (k = 0; k < 4; k++)
        {
            unsigned char index = (unsigned char)((val >> 26) & 0x3f);
            *output++ = base64_alphabet[index];
            val <<= 6;
        }
    }

    temp = 0;

    if (pad_count > 0)
    {
        free(input_string);
        input_string = 0;

        *(output - 1) = '=';
        pad_count--;

        if (pad_count > 0)
        {
            *(output - 2) = '=';
        }
    }

    *output = 0;

    return 0;
}

//
// get length of decoded string
//
int base64_decode_get_length(int input_length)
{
    if ((input_length % 4) != 0)
    {
        return 0;
    }

    return  input_length / 4 * 3;
}

//
// decode a single char
//
unsigned char base64_decode_char(char input)
{
    if ((input >= 'A') && (input <= 'Z'))
    {
        return input - 'A' + 0; // 0 range starts at 'A'
    }

    if ((input >= 'a') && (input <= 'z'))
    {
        return input - 'a' + 26; // 26 range starts at 'a'
    }

    if ((input >= '0') && (input <= '9'))
    {
        return input - '0' + 52; // 52 range starts at '0'
    }

    if (input == '+')
    {
        return 62;
    }

    if (input == '/')
    {
        return 63;
    }

    if (input == '=')
    {
        return 64;
    }

    return 65;
}

//
// use BASE64 to decode string
//
int base64_decode(char *input, unsigned char *output, int *output_length)
{
    int i = 0;
    int j = 0;
    int k = 0;

    int length = 0;
    int pad_count = 0;

    int temp = 0;

    if (input == 0 || output == 0)
    {
        return 1;
    }

    length = (int)strlen(input);

    // verify if input is a legal BASE64 string
    if (length % 4 != 0)
    {
        return 2;
    }

    for (i = 0; i < length; i++)
    {
        temp = base64_decode_char(input[i]);
        if (temp == 64)
        {
            if ((i != (length - 1)) && (i != (length - 2)))
            {
                return 3;
            }

            if (i == (length - 2))
            {
                if (base64_decode_char(input[i + 1]) != 64)
                {
                    return 4;
                }
                pad_count++;
            }
            else
            {
                pad_count++;
            }
        }

        if (temp == 65)
        {
            return 5;
        }
    }

    for (i = 0; i < length; i += 4)
    {
        unsigned long val = 0;
        for (j = 0; j < 4; j++)
        {
            unsigned char index = base64_decode_char(*input++);
            val |= index & 0x3f;
            val <<= 6;
        }
        val <<= 2;

        for (k = 0; k < 3; k++)
        {
            *output++ = (char)(val >> 24);
            val <<= 8;
        }
    }

    *output_length = length / 4 * 3 - pad_count;

    return 0;
}

int get_file_length(char *filename)
{
	int size = 0;
    FILE *fp = 0;

    fp = fopen(filename, "rb");
    if (!fp)
    {
        printf(" fopen failed.\n");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
	return size;
}

//
// read content of file "filename" to "buffer"
// and return the length of the file on success
//
int load_file(char *filename, char **buffer)
{
    int size = 0;
    FILE *fp = 0;

    fp = fopen(filename, "rb");
    if (!fp)
    {
        printf(" fopen failed.\n");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (size)
    {
        if (*buffer)
        {
            free(*buffer);
        }
        *buffer = 0;
        *buffer = (char *)malloc(size + 1);
        if (!*buffer)
        {
            printf(" malloc failed.\n");
            fclose(fp);
            return 0;
        }
        memset(*buffer, 0, size + 1);
        fread(*buffer, size, 1, fp);
        (*buffer)[size] = '\0';
    }
    else
    {
        fclose(fp);
        return 0;
    }
    fclose(fp);

    return size;
}




 //save content of "buffer" to file "filename"

int store_file(char *buffer, char *filename)
{
    int size = 0;
    FILE *fp = 0;

    if (buffer == 0)
    {
        printf(" NULL buffer.\n");
		return -1;
    }
    size = (int)strlen(buffer);

    fp = fopen(filename, "wb+");
    if (!fp)
    {
        printf(" fopen failed.\n");
        return -1;
    }

    fwrite(buffer, size, 1, fp);
    fclose(fp);

    return 0;
}