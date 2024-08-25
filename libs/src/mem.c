void memset(void* src, char value, int bytes) {
    unsigned char* src_ptr = (unsigned char*)src;
    for(int i = 0; i < bytes; i++)
        src_ptr[i] = value;
}

void memcpy(void* src, void* dst, int bytes) {
    unsigned char* src_ptr = (unsigned char*)src;
    unsigned char* dst_ptr = (unsigned char*)dst;
    for(int i = 0; i < bytes; i++)
        dst_ptr[i] = src_ptr[i];
}

int memcmp(const void* mem1, const void* mem2, int bytes){
    const unsigned char* p_mem1 = mem1;
    const unsigned char* p_mem2 = mem2;
    for(int i = 0; i < bytes; i++){
        if (p_mem1[i] < p_mem2[i])
            return -1;
        else if(p_mem1[i] > p_mem2[i])
            return 1;
    }

    return 0;
}