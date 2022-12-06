//
// Created by Juan Salazar on 26/10/22.
//

#ifndef FASTA_PROJECT_GRAPHCLASS_H
#define FASTA_PROJECT_GRAPHCLASS_H

#include <iostream>
#include <utility>
#include <vector>
#include <iomanip>
#include "SequenceClass.h"

namespace FastaGraph {

    class GraphMatrix {
    public:
        std::vector<std::vector<std::vector<int>>> matrix;

        GraphMatrix() = default;

        void insVertex(int y_size, int x_size) {
            x_size_ = x_size;
            y_size_ = y_size;
            N_vecs++;
            for (auto &x: matrix) {
                std::vector<int> vec_(5, -1);
                x.resize(y_size, vec_);
            }
            matrix.resize(x_size, std::vector<std::vector<int>>(y_size));
        }

        static bool checkBase(int x) {
            char c = char(x);
            if (c == 'A' || c == 'C' || c == 'G' || c == 'T' ||
                c == 'U' || c == 'R' || c == 'Y' || c == 'K' || c == 'M'
                || c == 'S' || c == 'W' || c == 'B' || c == 'D' || c == 'H' || c == 'N'
                || c == 'X' || c == 'V') {
                return true;
            }
            return false;
        }

        void insArch(int pos_y, int pos_x, std::vector<int> &Neighs, int char_value) {
            std::vector<int> vec_(5);
            vec_[0] = char_value;
            for (int i = 0; i < 4; i++) {
                int exit_w;
                if (!checkBase(Neighs[i])) Neighs[i] = -1;
                if (Neighs[i] == -1) {
                    exit_w = -1;
                } else {
                    int Nh = Neighs[i];
                    float diference_ = float(char_value) - float(Nh);
                    diference_ = std::abs(diference_);
                    float weight;
                    weight = 1 / (1 + diference_);
                    weight = weight * 1000;
                    exit_w = int(weight);
                }
                vec_[i + 1] = exit_w;
            }
            matrix[pos_x][pos_y] = vec_;
        }

        void printGraph(bool char_t = true) {
            std::cout << std::endl;
            std::cout << "   ";
            for (int i = 0; i < x_size_; i++) {
                if (i < 10) {
                    std::cout << "00" << i << " ";
                } else {
                    if (i < 100) {
                        std::cout << "0" << i << " ";
                    } else {
                        std::cout << i << " ";
                    }
                }
            }
            for (int i = 0; i < y_size_; i++) {
                std::cout << std::endl;
                if (i < 10) {
                    std::cout << "00" << i << " ";
                } else {
                    if (i < 100) {
                        std::cout << "0" << i << " ";
                    } else {
                        std::cout << i << " ";
                    }
                }
                for (auto x: matrix) {
                    if (x[i].empty()) {
                        std::cout << "<" << "   ";
                    } else {
                        std::vector<int> memx_ = x[i];
                        if (char_t) {
                            std::cout << char(memx_[0]) << "   ";
                        } else {
                            std::cout << (memx_[0]) << "   ";
                        }

                    }
                }
            }
        }

        void printTile() {
            std::cout << std::endl;
            std::cout << "           ";
            for (int i = 0; i < x_size_; i++) {
                std::cout << std::setw(10) << std::setfill('0') << i << " ";
            }
            for (int i = 0; i < y_size_; i++) {
                std::cout << std::endl;
                std::cout << std::setw(10) << std::setfill('0') << i << " ";
                for (auto x: matrix) {
                    if (x[i].empty()) {
                        std::cout << "<" << "   ";
                    } else {
                        std::vector<int> memx_ = x[i];
                        std::cout << std::setw(10) << std::setfill('0') << memx_[0] << " ";
                    }
                }
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }

        std::string name_seq;
    private:
        int N_vecs = 0;
        int x_size_ = 0;
        int y_size_ = 0;
    };

    class TileMatrix {
    public:
        GraphMatrix tile_base_;

        TileMatrix(int y_size, int x_size, GraphMatrix adj_, bool longest_ = false) {
            std::vector<int> entrace(8);
            if (longest_) {
                entrace[0] = 0;
            } else {
                entrace[0] = 2147483647;
            }
            entrace[1] = -1;
            entrace[6] = 0;
            tile_base_.insVertex(y_size, x_size);
            for (int x = 0; x < x_size; x++) {
                for (int y = 0; y < y_size; y++) {
                    if (adj_.matrix[x][y].empty()) {
                        entrace[1] = -3;
                        entrace[2] = -1;
                        entrace[3] = -1;
                        entrace[4] = -1;
                        entrace[5] = -1;
                        entrace[6] = 1;
                    } else {
                        entrace[7] = adj_.matrix[x][y][0];
                        entrace[2] = adj_.matrix[x][y][1];
                        entrace[3] = adj_.matrix[x][y][2];
                        entrace[4] = adj_.matrix[x][y][3];
                        entrace[5] = adj_.matrix[x][y][4];
                    }
                    tile_base_.matrix[x][y] = entrace;
                }
            }
        }

        void setSource(int pos_x = 0, int pos_y = 0, bool longest_ = false) {
            std::vector<int> entrace(7);
            entrace = tile_base_.matrix[pos_x][pos_y];
            entrace[0] = 0;
            entrace[1] = -2;
            if (longest_) entrace[0] = 2147483647;
            tile_base_.matrix[pos_x][pos_y] = entrace;
        }

        void checkNN(int pos_x, int pos_y) {
            int acumulated_ = tile_base_.matrix[pos_x][pos_y][0];
            int up_s, rg_s, lf_s, dw_s;
            if (tile_base_.matrix[pos_x][pos_y][2] != -1) {
                up_s = acumulated_ + tile_base_.matrix[pos_x][pos_y][2];
                if (up_s < tile_base_.matrix[pos_x][pos_y - 1][0]) {
                    tile_base_.matrix[pos_x][pos_y - 1][0] = up_s;
                    tile_base_.matrix[pos_x][pos_y - 1][1] = 2;
                }
            }
            if (tile_base_.matrix[pos_x][pos_y][3] != -1) {
                rg_s = acumulated_ + tile_base_.matrix[pos_x][pos_y][3];
                if (rg_s < tile_base_.matrix[pos_x + 1][pos_y][0]) {
                    tile_base_.matrix[pos_x + 1][pos_y][0] = rg_s;
                    tile_base_.matrix[pos_x + 1][pos_y][1] = 3;
                }
            }
            if (tile_base_.matrix[pos_x][pos_y][4] != -1) {
                dw_s = acumulated_ + tile_base_.matrix[pos_x][pos_y][4];
                if (dw_s < tile_base_.matrix[pos_x][pos_y + 1][0]) {
                    tile_base_.matrix[pos_x][pos_y + 1][0] = dw_s;
                    tile_base_.matrix[pos_x][pos_y + 1][1] = 0;
                }
            }
            if (tile_base_.matrix[pos_x][pos_y][5] != -1) {
                lf_s = acumulated_ + tile_base_.matrix[pos_x][pos_y][5];
                if (lf_s < tile_base_.matrix[pos_x - 1][pos_y][0]) {
                    tile_base_.matrix[pos_x - 1][pos_y][0] = lf_s;
                    tile_base_.matrix[pos_x - 1][pos_y][1] = 1;
                }
            }
        }

        void checkMI() {
            int minimum_ = 21000000;
            int x_, y_;
            for (int x = 0; x < tile_base_.matrix.size(); x++) {
                for (int y = 0; y < tile_base_.matrix[x].size(); y++) {
                    if (tile_base_.matrix[x][y][0] < minimum_) {
                        if (tile_base_.matrix[x][y][6] == 0) {
                            minimum_ = tile_base_.matrix[x][y][0];
                            x_ = x;
                            y_ = y;
                        }
                    }
                }
            }
            tile_base_.matrix[x_][y_][6] = 1;
            checkNN(x_, y_);
        }

        bool destino(int pos_x, int pos_y, bool longest_ = false) {
            if (!longest_) {
                if (tile_base_.matrix[pos_x][pos_y][0] != 2147483647) {
                    return true;
                }
            } else {
                if (tile_base_.matrix[pos_x][pos_y][0] != 0) {
                    return true;
                }
            }
            return false;
        }

        std::list<std::pair<int, int>> retrieve(int pos_x, int pos_y) {
            std::list<std::pair<int, int>> exit_;
            exit_.emplace_back(pos_x, pos_y);
            if (tile_base_.matrix[pos_x][pos_y][1] == 0) {
                exit_.splice(exit_.end(), retrieve(pos_x, pos_y - 1));
            }
            if (tile_base_.matrix[pos_x][pos_y][1] == 1) {
                exit_.splice(exit_.end(), retrieve(pos_x + 1, pos_y));
            }
            if (tile_base_.matrix[pos_x][pos_y][1] == 2) {
                exit_.splice(exit_.end(), retrieve(pos_x, pos_y + 1));
            }
            if (tile_base_.matrix[pos_x][pos_y][1] == 3) {
                exit_.splice(exit_.end(), retrieve(pos_x - 1, pos_y));
            }
            return exit_;
        }

        void shortest(int pos_i, int pos_j, int pos_x, int pos_y, bool longest_ = false) {
            if (!longest_) {
                std::cout << "Encontrando la ruta más corta... origen: " << pos_i << "," << pos_j << " Destino: "
                          << pos_x << "," << pos_y << std::endl;
                setSource(pos_i, pos_j);
                while (!destino(pos_x, pos_y)) {
                    checkMI();
                }
                std::cout << "La ruta más corta entre los dos puntos será ... " << std::endl;
                std::cout << " Pos_X" << " : " " Pos_Y" << std::endl;
                std::list<std::pair<int, int>> retr_ = retrieve(pos_x, pos_y);
                for (auto x: retr_) {
                    std::cout << x.first << " : " << x.second << std::endl;
                }
                std::cout << "El costo de la ruta será: " << tile_base_.matrix[pos_x][pos_y][0] << " :::  "
                          << std::endl;
                std::cout << "La matriz resultante de la busqueda es ..." << std::endl;
                tile_base_.printTile();
            } else {
                std::cout << "Encontrando la ruta más larga... origen: " << pos_i << "," << pos_j << " Destino: "
                          << pos_x << "," << pos_y << std::endl;
                setSource(pos_i, pos_j);
                while (!destino(pos_x, pos_y)) {
                    checkMI();
                }
                std::cout << "La ruta más larga entre los dos puntos será ... " << std::endl;
                std::cout << " Pos_X" << " : " " Pos_Y" << std::endl;
                std::list<std::pair<int, int>> retr_ = retrieve(pos_x, pos_y);
                for (auto x: retr_) {
                    std::cout << x.first << " : " << x.second << std::endl;
                }
                std::cout << "La matriz resultante de la busqueda es ..." << std::endl;
                tile_base_.printTile();

            }

        }

        bool completed_() {
            for (auto &x: tile_base_.matrix) {
                for (auto &y: x) {
                    if (y[6] == 0) {
                        return false;
                    }
                }
            }
            return true;
        }

        void checkMM(int pos_x, int pos_y) {
            int acumulated_ = tile_base_.matrix[pos_x][pos_y][0];
            if (acumulated_ == 2147483647) acumulated_ = 1;
            int up_s, rg_s, lf_s, dw_s;
            if (tile_base_.matrix[pos_x][pos_y][2] != -1) {
                up_s = acumulated_ + tile_base_.matrix[pos_x][pos_y][2];
                if (up_s > tile_base_.matrix[pos_x][pos_y - 1][0]) {
                    tile_base_.matrix[pos_x][pos_y - 1][0] = up_s;
                    tile_base_.matrix[pos_x][pos_y - 1][1] = 2;
                }
            }
            if (tile_base_.matrix[pos_x][pos_y][3] != -1) {
                rg_s = acumulated_ + tile_base_.matrix[pos_x][pos_y][3];
                if (rg_s > tile_base_.matrix[pos_x + 1][pos_y][0]) {
                    tile_base_.matrix[pos_x + 1][pos_y][0] = rg_s;
                    tile_base_.matrix[pos_x + 1][pos_y][1] = 3;
                }
            }
            if (tile_base_.matrix[pos_x][pos_y][4] != -1) {
                dw_s = acumulated_ + tile_base_.matrix[pos_x][pos_y][4];
                if (dw_s > tile_base_.matrix[pos_x][pos_y + 1][0]) {
                    tile_base_.matrix[pos_x][pos_y + 1][0] = dw_s;
                    tile_base_.matrix[pos_x][pos_y + 1][1] = 0;
                }
            }
            if (tile_base_.matrix[pos_x][pos_y][5] != -1) {
                lf_s = acumulated_ + tile_base_.matrix[pos_x][pos_y][5];
                if (lf_s > tile_base_.matrix[pos_x - 1][pos_y][0]) {
                    tile_base_.matrix[pos_x - 1][pos_y][0] = lf_s;
                    tile_base_.matrix[pos_x - 1][pos_y][1] = 1;
                }
            }
        }


        void checkMA() {
            int minimum_ = 0;
            int x_, y_;
            x_ = 0;
            y_ = 0;
            for (int x = 0; x < tile_base_.matrix.size(); x++) {
                for (int y = 0; y < tile_base_.matrix[x].size(); y++) {
                    if (tile_base_.matrix[x][y][0] > minimum_) {
                        if (tile_base_.matrix[x][y][6] == 0) {
                            minimum_ = tile_base_.matrix[x][y][0];
                            x_ = x;
                            y_ = y;
                        }
                    }
                }
            }
            tile_base_.matrix[x_][y_][6] = 1;
            checkMM(x_, y_);
        }

        void remote(int pos_i, int pos_j, TileMatrix tm) {

            int x_, y_;
            int max_ = 0;
            int char_base = tile_base_.matrix[pos_i][pos_j][7];
            for (int x = 0; x < tile_base_.matrix.size(); x++) {
                for (int y = 0; y < tile_base_.matrix[x].size(); y++) {
                    if (tile_base_.matrix[x][y][7] == char_base) {
                        if (tile_base_.matrix[x][y][0] > max_ && tile_base_.matrix[x][y][0] != 2147483647) {
                            x_ = x;
                            y_ = y;
                            max_ = tile_base_.matrix[x][y][0];
                        }
                    }

                }
            }
            std::cout << "La ruta más larga tiene un costo de: " << tile_base_.matrix[x_][y_][0]
                      << " y la ruta entre ellas es... " << std::endl;
            tm.shortest(pos_i, pos_j, x_, y_, true);

        }


        void longest(int pos_i, int pos_j, GraphMatrix adj, int y_size, int x_size) {
            TileMatrix tm(y_size, x_size, std::move(adj));
            std::cout << "Finding remote base.. " << std::endl;
            setSource(pos_i, pos_j, true);
            while (!completed_()) {
                checkMA();
            }
            remote(pos_i, pos_j, tm);
            tile_base_.printTile();
        }
    };

    class GraphClass {
    private:
    public:
        GraphClass() = default;

        static void makeFastaGraph(DNA_sequence::SequenceClass sequence) {
            GraphMatrix adj;
            std::list<std::string> lines_list = sequence.linesList();
            int pos_y = 0;
            int pos_x;
            int length = sequence.maxLenLine();
            adj.insVertex(lines_list.size(), length);
            for (auto str_it = lines_list.begin(); pos_y < lines_list.size(); str_it++, pos_y++) {
                pos_x = 0;
                std::string actual, last, next;
                std::vector<int> vec_NH(4, -1);
                actual = *str_it;
                str_it++;
                if (str_it != lines_list.end()) {
                    next = *str_it;
                    str_it--;
                }
                if (str_it != lines_list.begin()) {
                    str_it--;
                    last = *str_it;
                    str_it++;
                }
                for (; pos_x < actual.size(); pos_x++) {
                    unsigned char actual_char = actual[pos_x];
                    if (pos_x < actual.size()) {
                        unsigned char next_char = actual[pos_x + 1];
                        vec_NH[1] = int(next_char);
                    }
                    if (pos_x != 0) {
                        unsigned char last_char = actual[pos_x - 1];
                        vec_NH[3] = int(last_char);
                    }
                    if (!last.empty()) {
                        if (pos_x < last.size()) {
                            unsigned char up_char = last[pos_x];
                            vec_NH[0] = int(up_char);
                        }
                    }
                    if (!next.empty()) {
                        if (pos_x < next.size()) {
                            unsigned char down_char = next[pos_x];
                            vec_NH[2] = int(down_char);
                        }
                    }
                    adj.insArch(pos_y, pos_x, vec_NH, int(actual_char));
                }
            }
            adj.printGraph();
            TileMatrix tm(lines_list.size(), length, adj);
            tm.shortest(9, 1, 16, 1);
            TileMatrix af(lines_list.size(), length, adj, true);
            af.longest(9, 1, adj, lines_list.size(), length);
        }
    };

} // FastaGraph

#endif //FASTA_PROJECT_GRAPHCLASS_H
