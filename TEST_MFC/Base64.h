
int base64_encode_get_length(int input_length);
int base64_decode_get_length(int input_length);
int base64_encode(unsigned char *input, int input_length, char *output);
unsigned char base64_decode_char(char input);
int base64_decode(char *input, unsigned char *output, int *output_length);
int load_file(char *filename, char **buffer);
int store_file(char *buffer, char *filename);
int get_file_length(char *file_name);