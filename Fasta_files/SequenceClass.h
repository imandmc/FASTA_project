//
// Created by Juan Salazar on 30/09/22.
//

#ifndef FASTA_PROJECT_SEQUENCECLASS_H
#define FASTA_PROJECT_SEQUENCECLASS_H

#include <iostream>
#include <list>
#include <utility>
#include <regex>
#include <sstream>
#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <map>


namespace DNA_sequence {
    class SequenceClass {
    private:
        std::list<std::string> lines_list_;
        std::string seq_name_;
        bool seq_correct_bool_ = true;
        int max_len_line_ = 0;
        bool complete_ = true;

    public:
        SequenceClass();

        explicit SequenceClass(const std::string &nombre_secuencia);

        ~SequenceClass();

        bool addLine(std::string line);

        void assignName(std::string sequence_name);

        bool checkBase(char c);

        bool sequenceCorrect() const;

        void clear();

        void makeGraph();

        void printLines();

        std::string seqName();

        std::list<std::string> linesList();

        void updateSeqLinesList(std::list<std::string> nueva_lista);

        int maxLenLine() const;

        int identation();

        void updateMaxLenLine(int longitud);

        void assignGraph();
    };

    SequenceClass::SequenceClass() = default;

    SequenceClass::SequenceClass(const std::string &nombre_secuencia) {
        this->seq_name_ = nombre_secuencia;
    }

    bool SequenceClass::addLine(std::string line) {
        int temp_max = int(line.length());
        bool success = false;
        std::string::const_iterator it = line.begin();
        while (it != line.end() && checkBase(*it)) {
            ++it;
        }
        if (!line.empty() && it == line.end()) {
            lines_list_.push_back(line);
            success = true;
        }
        if (temp_max > this->max_len_line_) this->max_len_line_ = temp_max;
        return success;
    }

    void SequenceClass::assignName(std::string sequence_name) {
        this->seq_name_ = std::move(sequence_name);
    }

    bool SequenceClass::checkBase(char c) {
        if (c == 'A' || c == 'C' || c == 'G' || c == 'T' ||
            c == 'U' || c == 'R' || c == 'Y' || c == 'K' || c == 'M'
            || c == 'S' || c == 'W' || c == 'B' || c == 'D' || c == 'H' || c == 'N'
            || c == 'X' || c == 'V' || c == '-' || c == '\r') {
            if (c == '-') complete_ = false;
            return true;
        }
        this->seq_correct_bool_ = false;
        return false;
    }

    bool SequenceClass::sequenceCorrect() const {
        return this->seq_correct_bool_;
    }

    SequenceClass::~SequenceClass() {
        this->lines_list_.clear();
        this->seq_name_.clear();
    }

    void SequenceClass::clear() {
        this->lines_list_.clear();
        this->seq_name_.clear();
    }

    void SequenceClass::makeGraph() {

    }

    void SequenceClass::printLines() {
        std::cout << "Sequence: " << this->seq_name_ << std::endl;
        std::cout << "Identation (number of lines): " << identation() << std::endl;
        std::cout << "Max Length of Lines: " << max_len_line_ << std::endl;
        std::cout << "Complete?: " << complete_ << std::endl;
    }

    std::string SequenceClass::seqName() {
        return this->seq_name_;
    }

    std::list<std::string> SequenceClass::linesList() {
        return this->lines_list_;
    }

    void SequenceClass::updateSeqLinesList(std::list<std::string> nueva_lista) {
        this->lines_list_ = std::move(nueva_lista);
    }

    int SequenceClass::maxLenLine() const {
        return this->max_len_line_;
    }

    int SequenceClass::identation() {
        int identation_ = int(lines_list_.size());
        return identation_;
    }

    void SequenceClass::updateMaxLenLine(int longitud) {
        this->max_len_line_ = longitud;
    }

    void SequenceClass::assignGraph() {

    }


}

#endif //FASTA_PROJECT_SEQUENCECLASS_H
