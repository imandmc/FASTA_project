//
// Created by Juan Salazar on 1/10/22.
//

#ifndef FASTA_PROJECT_HUFFMAN_H
#define FASTA_PROJECT_HUFFMAN_H

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>


class Huffman {
private:
    std::map<char, std::vector<int>> mapeo;
    struct HuffmanNode {
        unsigned frecuencia_;
        char codigo_;
        struct HuffmanNode *left, *right;
    };
    struct MinHeap {
        unsigned size_;
        unsigned capacidad_;
        struct HuffmanNode **array_;
    };

    static struct HuffmanNode *nuevoNodo(char codigo, unsigned frecuencia) {
        struct HuffmanNode *temp;
        temp = (struct HuffmanNode *) malloc(sizeof(struct HuffmanNode));
        temp->left = temp->right = nullptr;
        temp->codigo_ = codigo;
        temp->frecuencia_ = frecuencia;
        return temp;
    }

    static struct MinHeap *nuevoMinHeap(unsigned capacidad) {
        struct MinHeap *minHeap;
        minHeap = (struct MinHeap *) malloc(sizeof(struct MinHeap));
        minHeap->size_ = 0;
        minHeap->capacidad_ = capacidad;
        minHeap->array_ = (struct HuffmanNode **) malloc(minHeap->capacidad_ * sizeof(struct HuffmanNode *));
        return minHeap;
    }

    static void swapHuffmanNode(struct HuffmanNode **a, struct HuffmanNode **b) {
        struct HuffmanNode *t = *a;
        *a = *b;
        *b = t;
    }

    void minHeapify(struct MinHeap *minHeap, int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < minHeap->size_ && minHeap->array_[left]->
                frecuencia_ < minHeap->array_[smallest]->frecuencia_)
            smallest = left;

        if (right < minHeap->size_ && minHeap->array_[right]->
                frecuencia_ < minHeap->array_[smallest]->frecuencia_)
            smallest = right;

        if (smallest != idx) {
            swapHuffmanNode(&minHeap->array_[smallest],
                            &minHeap->array_[idx]);
            minHeapify(minHeap, smallest);
        }
    }

    static int isSizeOne(struct MinHeap *minHeap) {
        return (minHeap->size_ == 1);
    }

    struct HuffmanNode *extractMin(struct MinHeap *minHeap) {
        struct HuffmanNode *temp = minHeap->array_[0];
        minHeap->array_[0] = minHeap->array_[minHeap->size_ - 1];
        --minHeap->size_;
        minHeapify(minHeap, 0);
        return temp;
    }

    static void insertMinHeap(struct MinHeap *minHeap, struct HuffmanNode *huffmanNode) {
        ++minHeap->size_;
        int i = minHeap->size_ - 1;
        while (i && huffmanNode->frecuencia_ < minHeap->array_[(i - 1) / 2]->frecuencia_) {
            minHeap->array_[i] = minHeap->array_[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        minHeap->array_[i] = huffmanNode;
    }

    void construirMinHeap(struct MinHeap *minHeap) {
        int n = minHeap->size_ - 1;
        int i;
        for (i = (n - 1) / 2; i >= 0; --i) {
            minHeapify(minHeap, i);
        }
    }

    static int isLeaf(struct HuffmanNode *root) {
        return !(root->left) && !(root->right);
    }

    struct MinHeap *crearMinHeap(char codigo[], int frecuencia[], int size) {
        struct MinHeap *minHeap = nuevoMinHeap(size);
        for (int i = 0; i < size; ++i) {
            minHeap->array_[i] = nuevoNodo(codigo[i], frecuencia[i]);
        }
        minHeap->size_ = size;

        construirMinHeap(minHeap);

        return minHeap;
    }

    struct HuffmanNode *construirHuffman(char codigo[], int frecuencia[], int size) {
        struct HuffmanNode *left, *right, *top;
        struct MinHeap *minHeap = crearMinHeap(codigo, frecuencia, size);
        while (!isSizeOne(minHeap)) {
            left = extractMin(minHeap);
            right = extractMin(minHeap);
            top = nuevoNodo('$', left->frecuencia_ + right->frecuencia_);
            top->left = left;
            top->right = right;
            insertMinHeap(minHeap, top);
        }

        return extractMin(minHeap);
    }


    void printCodes(struct HuffmanNode *root, int arr[], int top) {
        if (root->left) {
            arr[top] = 0;
            printCodes(root->left, arr, top + 1);
        }
        if (root->right) {
            arr[top] = 1;
            printCodes(root->right, arr, top + 1);
        }
        if (isLeaf(root)) {
            int n = sizeof(arr) / sizeof(arr[0]) + 1;
            std::vector<int> vecint;
            for (int i = 0; i < top; ++i) {
                vecint.push_back(arr[i]);
            }
            std::vector<int> dest(arr, arr + n);
            this->mapeo.emplace(root->codigo_, vecint);
        }
    }

    static void printArr(int arr[], int n) {
        int i;
        for (i = 0; i < n; ++i) {
            std::cout << arr[i];
        }
        std::cout << "\n";
    }


public:

    void HuffmanEncoding(char codigo[], int frecuencia[], int size) {
        struct HuffmanNode *root = construirHuffman(codigo, frecuencia, size);
        int top = 0;
        int arr[100];
        printCodes(root, arr, top);
    }

    std::map<char, std::vector<int>> MapHuffman() {
        return this->mapeo;
    }


};


#endif //FASTA_PROJECT_HUFFMAN_H
