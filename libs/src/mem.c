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
