#ifndef PAIR_H_INCLUDED
#define PAIR_H_INCLUDED
class Pair{
public:
    Pair(const int & row, const int & col){
        row_idx = row;
        col_idx = col;
    }
    bool operator ==(const Pair & input){
        return (input.row_idx == row_idx) && (input.col_idx == col_idx);
    }
    int row_idx;
    int col_idx;

};





#endif
