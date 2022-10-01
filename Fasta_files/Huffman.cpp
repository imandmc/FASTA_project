#include "Huffman.h"


int main() {
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr) / sizeof(arr[0]);
    Huffman huff;
    huff.HuffmanEncoding(arr, freq, size);
    return 0;
}
