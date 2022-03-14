#include<iostream>
using namespace std;
#include<stdint.h>

struct Info
{
    /* data */
    uint8_t a;
    uint16_t b;
    uint8_t c;
};

//alignas可以指定结构体的对齐方式
struct alignas(4) Info2 {
 uint8_t a;
 uint16_t b;
 uint8_t c;
};

//对齐不能设置为小于默认对齐，此时 alignas失效
// struct alignas(2) Info2 {
//  uint8_t a;
//  uint32_t b;
//  uint8_t c;
// };


/*如果想使用单字节对齐的方式，使用alignas是无效的。应该使用#pragma pack(push,1)或者使用
__attribute__((packed))。*/

#if defined(__GNUC__) || defined(__GNUG__)
 #define ONEBYTE_ALIGN __attribute__((packed))
#elif defined(_MSC_VER)
 #define ONEBYTE_ALIGN
 #pragma pack(push,1)
#endif


struct Info3{
 uint8_t a;
 uint32_t b;
 uint8_t c;
} ONEBYTE_ALIGN;


#if defined(__GNUC__) || defined(__GNUG__)
 #undef ONEBYTE_ALIGN
#elif defined(_MSC_VER)
 #pragma pack(pop)
 #undef ONEBYTE_ALIGN
#endif

int main()
{
    cout<<sizeof(Info)<<endl;
    //alignof可以计算出类型的对齐方式
    cout<<alignof(Info)<<endl;

    cout<<sizeof(Info2)<<endl;
    cout<<alignof(Info2)<<endl;

    cout<<sizeof(Info3)<<endl;
    cout<<alignof(Info3)<<endl;

    return 0;
}