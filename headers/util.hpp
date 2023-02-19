#pragma once
#include <iostream>

namespace util::memory
{
    static void vmt(uint64_t address, int idx, void* fn, void** og)
    {
        auto old_vt = *(void***)address;

        *og = old_vt[idx];

        int vt_size = 1;
        for (; *(uint64_t*)((uint64_t)old_vt + vt_size * 0x8); vt_size++) {}

        auto new_vt = new uint64_t[vt_size * 0x8];

        for (auto i = 0; i < vt_size; i++)
            new_vt[i] = *(uint64_t*)((uint64_t)old_vt + (i * 0x8));

        new_vt[idx] = (uint64_t)fn;
        *(uint64_t**)address = new_vt;
    }
}