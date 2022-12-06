//
// Created by Juan Salazar on 30/09/22.
//

#ifndef FASTA_PROJECT_FASTAFILECLASS_H
#define FASTA_PROJECT_FASTAFILECLASS_H

#include "GraphClass.h"
#include "Huffman.h"

namespace FastaFile {

    class FASTAFileClass {
    private:
        std::list<DNA_sequence::SequenceClass> sequences_list_;
        int DNAsequences_count{};
        std::string file_name_;
        bool empty_file_ = true;
        std::list<char> lista_bases_ = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N',
                                        'X', '-', '\r'};
        int file_bases_count = 0;
        std::map<char, std::vector<int>> mapa_;
        std::map<char, int> mapa_freq_;

    public:
        FASTAFileClass();


        std::string NombreArchivo();

        ~FASTAFileClass();

        void printInformation();

        void exportLegible();

        int isSubSequence(std::string sub_sequence);

        explicit FASTAFileClass(std::string &file_name);

        explicit FASTAFileClass(std::string &file_name, const int &bin_opcion);

        void HuffmanEncodder();

        std::map<char, int> freqMapping();

        void compressFile(std::string file_name);

        FASTAFileClass &operator=(FASTAFileClass const &obj) {
            this->sequences_list_ = obj.sequences_list_;
            this->mapa_freq_ = obj.mapa_freq_;
            this->mapa_ = obj.mapa_;
            this->file_name_ = obj.file_name_;
            this->empty_file_ = false;
            this->file_bases_count = obj.file_bases_count;
            this->DNAsequences_count = obj.DNAsequences_count;
            return *this;
        }

        FASTAFileClass(const FASTAFileClass &obj) {
            this->sequences_list_ = obj.sequences_list_;
            this->mapa_freq_ = obj.mapa_freq_;
            this->mapa_ = obj.mapa_;
            this->file_name_ = obj.file_name_;
            this->empty_file_ = false;
            this->file_bases_count = obj.file_bases_count;
            this->DNAsequences_count = obj.DNAsequences_count;
        }

        std::string prepareFileName(std::string &file_name, const std::string &extension);

        void maskFile(const std::string &to_mask);

        void maskFile(const std::string &to_mask, const std::string &mask);

        void HuffmanEncodder(bool Mask);

        void FastaGraphmaker();
    };


} // Fasta File Class

#endif //FASTA_PROJECT_FASTAFILECLASS_H
