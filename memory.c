#include "oslabs.h"
struct MEMORY_BLOCK nullBlockCreation();
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

    return nullblock;
}

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id)
{

    struct MEMORY_BLOCK NULLBLOCK;
    struct MEMORY_BLOCK newBlock;

    // Find best fit block
    int blockIndex = -1;
    for (int x = 0; x < *map_cnt; x++)
    {
        if ((memory_map[x].segment_size >= request_size) && (memory_map[x].process_id == 0))
        {
            if (blockIndex == -1 || memory_map[x].segment_size < memory_map[blockIndex].segment_size)
            {
                blockIndex = x;
            }
        }
    }

    // Return nullblock if no available fit found
    if (blockIndex == -1)
    {
        NULLBLOCK = nullBlockCreation();
        return NULLBLOCK;
    }

    // Split the block if needed
    if (memory_map[blockIndex].segment_size > request_size)
    {
        (*map_cnt)++;
        for (int x = blockIndex + 2; x < *map_cnt; x++)
        {
            memory_map[x] = memory_map[x - 1];
        }
        newBlock.process_id = 0;
        newBlock.start_address = memory_map[blockIndex].start_address + request_size;
        newBlock.end_address = memory_map[blockIndex].end_address;
        newBlock.segment_size = memory_map[blockIndex].segment_size - request_size;

        memory_map[blockIndex + 1] = newBlock;
        memory_map[blockIndex].end_address = memory_map[blockIndex].start_address + request_size - 1;
        memory_map[blockIndex].segment_size = request_size;
    }

    memory_map[blockIndex].process_id = process_id;
    return memory_map[blockIndex];
};
struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id)
{
    struct MEMORY_BLOCK NULLBLOCK;
    struct MEMORY_BLOCK newBlock;

    // Find best fit block
    int blockIndex = -1;
    for (int x = 0; x < *map_cnt; x++)
    {
        if ((memory_map[x].segment_size >= request_size) && (memory_map[x].process_id == 0))
        {
            blockIndex = x;
            break;
        }
    }

    // Return nullblock if no available fit found
    if (blockIndex == -1)
    {
        NULLBLOCK = nullBlockCreation();
        return NULLBLOCK;
    }

    // Split the block if needed
    if (memory_map[blockIndex].segment_size > request_size)
    {
        (*map_cnt)++;
        for (int x = blockIndex + 2; x < *map_cnt; x++)
        {
            memory_map[x] = memory_map[x - 1];
        };
        newBlock.process_id = 0;
        newBlock.start_address = memory_map[blockIndex].start_address + request_size;
        newBlock.end_address = memory_map[blockIndex].end_address;
        newBlock.segment_size = memory_map[blockIndex].segment_size - request_size;

        memory_map[blockIndex + 1] = newBlock;
        memory_map[blockIndex].end_address = memory_map[blockIndex].start_address + request_size - 1;
        memory_map[blockIndex].segment_size = request_size;
    }

    memory_map[blockIndex].process_id = process_id;
    return memory_map[blockIndex];
};
struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id)
{
    struct MEMORY_BLOCK NULLBLOCK;
    struct MEMORY_BLOCK newBlock;

    // Find best fit block
    int blockIndex = -1;
    for (int x = 0; x < *map_cnt; x++)
    {
        if ((memory_map[x].segment_size >= request_size) && (memory_map[x].process_id == 0))
        {
            if ((blockIndex == -1) || (memory_map[x].segment_size > memory_map[blockIndex].segment_size))
                blockIndex = x;
        }
    }

    // Return nullblock if no available fit found
    if (blockIndex == -1)
    {
        NULLBLOCK = nullBlockCreation();
        return NULLBLOCK;
    }

    // Split the block if needed
    if (memory_map[blockIndex].segment_size > request_size)
    {
        (*map_cnt)++;
        for (int x = blockIndex + 2; x < *map_cnt; x++)
        {
            memory_map[x] = memory_map[x - 1];
        }
        newBlock.process_id = 0;
        newBlock.start_address = memory_map[blockIndex].start_address + request_size;
        newBlock.end_address = memory_map[blockIndex].end_address;
        newBlock.segment_size = memory_map[blockIndex].segment_size - request_size;

        memory_map[blockIndex + 1] = newBlock;
        memory_map[blockIndex].end_address = memory_map[blockIndex].start_address + request_size - 1;
        memory_map[blockIndex].segment_size = request_size;
    }

    memory_map[blockIndex].process_id = process_id;
    return memory_map[blockIndex];
};
struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id, int last_address)
{
    struct MEMORY_BLOCK NULLBLOCK;
    struct MEMORY_BLOCK newBlock;

    // Find best fit block
    int blockIndex = -1;
    for (int x = 0; x < *map_cnt; x++)
    {
        if ((memory_map[x].segment_size >= request_size) && (memory_map[x].process_id == 0) && memory_map[x].start_address >= last_address)
        {
            blockIndex = x;
            break;
        }
    }

    // Return nullblock if no available fit found
    if (blockIndex == -1)
    {
        NULLBLOCK = nullBlockCreation();
        return NULLBLOCK;
    }

    // Split the block if needed
    if (memory_map[blockIndex].segment_size > request_size)
    {
        (*map_cnt)++;
        for (int x = blockIndex + 2; x < *map_cnt; x++)
        {
            memory_map[x] = memory_map[x - 1];
        }
        newBlock.process_id = 0;
        newBlock.start_address = memory_map[blockIndex].start_address + request_size;
        newBlock.end_address = memory_map[blockIndex].end_address;
        newBlock.segment_size = memory_map[blockIndex].segment_size - request_size;

        memory_map[blockIndex + 1] = newBlock;
        memory_map[blockIndex].end_address = memory_map[blockIndex].start_address + request_size - 1;
        memory_map[blockIndex].segment_size = request_size;
    }

    memory_map[blockIndex].process_id = process_id;
    return memory_map[blockIndex];
};
void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt)
{

    int blockIndex = -1;
    // Find map index of freed block
    for (int x = 0; x < *map_cnt; x++)
    {
        if (memory_map[x].start_address == freed_block.start_address)
        {
            blockIndex = x;
            break;
        }
    }
    // Set memory as available
    memory_map[blockIndex].process_id = 0;

    // Merging with memory before the freed blockindex
    if (memory_map[blockIndex - 1].process_id == 0 && blockIndex >= 1)
    {
        blockIndex--;
        memory_map[blockIndex].end_address = memory_map[blockIndex + 1].end_address;
        memory_map[blockIndex].segment_size = memory_map[blockIndex + 1].segment_size + memory_map[blockIndex].segment_size;

        (*map_cnt)--;
        for (int x = blockIndex + 1; x < *map_cnt; x++)
        {
            memory_map[x] = memory_map[x + 1];
        }
    }

    // Merging with memory after the freed blockindex
    if (memory_map[blockIndex + 1].process_id == 0 && blockIndex < *map_cnt)
    {
        memory_map[blockIndex].end_address = memory_map[blockIndex + 1].end_address;
        memory_map[blockIndex].segment_size = memory_map[blockIndex + 1].segment_size + memory_map[blockIndex].segment_size;

        (*map_cnt)--;
        for (int x = blockIndex + 1; x < *map_cnt; x++)
        {
            memory_map[x] = memory_map[x + 1];
        }
    }
};