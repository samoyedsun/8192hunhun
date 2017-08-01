#ifndef DATA_PACKET
#define DATA_PACKET
#include <stdlib.h>
#include <string.h>
#include <iostream>

class DataPacket
{
    public:
        DataPacket();
        DataPacket(int size);
        ~DataPacket();
template <typename T>
        DataPacket& operator << (const T &val)
        {
            void *buf_ptr = NULL;
            int new_size = sizeof(val);

            if (0u == this->block_count_)
                buf_ptr = malloc(new_size);
            else
            {
                new_size += this->block_count_;
                buf_ptr = realloc(this->data_block_, new_size);
            }

            if (NULL == buf_ptr)
            {
                std::cout << "memory allocation fail!"  << std::endl;
            }
            else
            {
                this->data_block_ = this->pos_ptr_ = buf_ptr;
                this->block_count_ = new_size;
            }

            return *this;
        }


        template <typename T>
        DataPacket& operator >> (T &val)
        {
            if (0u >= this->block_count_)
                return *this;

            int ele_size = sizeof(val);
            char *buf_ptr =  (char *)this->pos_ptr_;

            if (memcpy((void *)&val, buf_ptr, ele_size) != NULL)
            {

                this->pos_ptr_ = buf_ptr + ele_size;
                this->block_count_ -= ele_size;
            }

            return *this;
        }

        void* get_data_ptr();
        int get_data_size();

    private:
        void *data_block_;
        int  block_count_;

        void *pos_ptr_;
};

#endif