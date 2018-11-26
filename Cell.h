#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED
class cell{
public:

    char type;
    bool cleaned;
    int distance;
    int dest_distance;
    pair dest_pair;
};
#endif
