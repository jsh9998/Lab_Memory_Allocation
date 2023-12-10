#include "oslabs.h"

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id);
struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id);
struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id);
struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id, int last_address);
void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt);

struct MEMORY_BLOCK nullBlockCreation()
{
    struct MEMORY_BLOCK nullblock;
    nullblock.end_address = 0;
    nullblock.process_id = 0;
    nullblock.segment_size = 0;
    nullblock.start_address = 0;
}

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id)
{

    struct MEMORY_BLOCK NULLBLOCK;

    for (int x = 0; x < *map_cnt; x++)
    {
        if (request_size == memory_map[x].segment_size && memory_map[x].process_id == 0)
        {
            memory_map[x].process_id = process_id;
            return memory_map[x];
        }
        else if (request_size < memory_map[x].segment_size && memory_map[x].process_id == 0)
        {

            struct MEMORY_BLOCK newBlock;
            newBlock.process_id = 0;
            newBlock.end_address = memory_map[x].end_address;
            memory_map[x].end_address = memory_map[x].start_address + request_size - 1;
            memory_map[x].process_id = process_id;
            memory_map[x].segment_size = request_size;

                        int excessMemory = memory_map[x].segment_size - request_size;
            newBlock.segment_size = excessMemory;
            newBlock.start_address = memory_map[x].end_address + 1;

            memory_map[*map_cnt] = newBlock;
            (*map_cnt)++;

            return memory_map[x];
        }
    }

    NULLBLOCK = nullBlockCreation();
    return NULLBLOCK;
};
struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id){

};
struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id){

};
struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id, int last_address){

};
void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt){

};