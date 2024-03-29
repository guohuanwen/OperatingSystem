//
//  test2.c
//  OperatingSystem
//
//  Created by huanwen guo on 2019/6/12.
//  Copyright © 2019 bigwen. All rights reserved.
//

#include "test2.h"
#include "stdio.h"


typedef  unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for(i = 0; i < len; i++) {
        printf("%.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
}

//2.5
void test2_5() {
    printf("2.5:\n");
    int val = 0x87654321;
    //我的mbp是小端
    byte_pointer valp = (byte_pointer) &val;
    show_bytes(valp, 1);//21
    show_bytes(valp, 2);//2143
    show_bytes(valp, 3);//214365
    show_bytes(valp, 4);//21436587
    printf("\n");
}

//2.6
void test2_6() {
    printf("2.6:\n");
    int val1 = 3510593;
    float val2 = 3510583.0;
    show_bytes((byte_pointer) &val1, sizeof(val1));
    show_bytes((byte_pointer) &val2, sizeof(val2));
    printf("\n");
}

//to 二进制
void printf_binary(int num) {
    int binary = 0;
    int i = 0;
    do {
        int n = num % 2;
        int ten = 1;
        for (int j = 0; j < i; j++){
            ten = ten * 10;
        }
        binary = binary + n * ten;
        num = num / 2;
        i++;
    } while (num > 0);
    printf("binary : %d\n", binary);
}

//2.8
void test2_8(){
    printf("2.8:\n");
    int a = 0b01101001;
    int b = 0b01010101;

    printf_binary(~a);
    printf_binary(~b);
    printf_binary(a & b);
    printf_binary(a | b);
    printf_binary(a ^ b);
    
    printf("\n");
}

void print_color(int color) {
    if (color == 0b000) {
        printf("黑色");
    } else if (color == 0b001) {
        printf("蓝色");
    } else if (color == 0b010) {
        printf("绿色");
    } else if (color == 0b011) {
        printf("青色");
    } else if (color == 0b100) {
        printf("红色");
    } else if (color == 0b101) {
        printf("红紫色");
    } else if (color == 0b110) {
        printf("黄色");
    } else if (color == 0b111) {
        printf("白色");
    } else {
        printf("未知");
    }
    printf("\n");
}

//2.9
void test2_9() {
    printf("2.9:\n");
    int black = 0b000;
    int blue = 0b001;
    int green = 0b010;
    int cyan = 0b011;
    int red = 0b100;
    int magenta = 0b101;
    int yellow = 0b110;
    int white = 0b111;
    printf("蓝色+绿色：");
    print_color(blue | green);
    printf("黄色&蓝绿：");
    print_color(yellow & cyan);
    printf("红色^红紫色：");
    print_color(red ^ magenta);
    printf("\n");
}

void inplace_swap(int *x, int *y) {
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

//2.10
void test2_10() {
    printf("2.10:\n");
    printf("性质 1：a^0=a  2: a^b^a=a^a^b 则： a^b^a=b \n");
    int a = 10;
    int b = 2;
    printf("a = %d b = %d \n", a, b);
    inplace_swap(&a, &b);
    printf("a = %d b = %d \n", a, b);
    printf("\n");
}

void reverse_array(int a[], int cnt) {
    int first, last;
    first = 0;
    last = cnt - 1;
    for (;first <= last;first++,last--) {
        if (first != last) {//support any num
            inplace_swap(&a[first], &a[last]);
        }
    }
}

//2.11
void test2_11() {
    printf("2.11:\n");
    int a[6];
    a[0] = 0;
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    a[4] = 4;
    a[5] = 5;
    for (int i = 0; i< 6; i++) {
        printf("%d", a[i]);
    }
    printf("\n");
    reverse_array(a, 5);
    for (int i = 0; i< 6; i++) {
        printf("%d", a[i]);
    }
    printf("\n\n");
}

//2.12
void test2_12() {
    printf("2.12: \n");
    int x = 0x87654321;
    printf("~0 = %x\n", ~0);
    printf("x最低有效字节 %x\n", x&0xff);
    printf("x除最低有效字节，其他都取补 %x\n", (x&0xff) | (~(x|0xff)));
    printf("x最低有效字节设置成全1 %x\n", x|0x000000ff);
    printf("\n");
}

//模拟bis操作
int bis(int x, int m) {
    return x | m;
}

//模拟bic操作
int bic(int x, int m) {
    return ~m & x;
}

//2.13
void test2_13() {
    printf("2.13: \n");
    printf("%x\n", bis(0x0, 0x0));
    printf("%x\n", bis(0x0, 0x1));
    printf("%x\n", bis(0x1, 0x0));
    printf("%x\n", bis(0x1, 0x1));
    printf("\n");
    printf("%x\n", bic(0x0, 0x0));
    printf("%x\n", bic(0x0, 0x1));
    printf("%x\n", bic(0x1, 0x0));
    printf("%x\n", bic(0x1, 0x1));
    
    int x = 0b10101;
    int y = 0b01010;
    int bisXy = bis(x, y);
    printf("x^y = bis(bic(bis(x, y), x), bic(bis(x, y), y)) : \n");
    printf_binary(bis(bic(bisXy, x), bic(bisXy, y)));
    
    printf("\n");
}

int checkXY(int x, int y) {
    return ~(x-y|y-x);
}

//2.15
void test2_15() {
    printf("2.15:\n");
    int x = 123;
    int y = 123;
    printf("%x\n", checkXY(x, y));
    
    printf("\n");
}

int main() {
    printf("hello world\n");
    show_float(0);
    test2_5();
    test2_6();
    test2_8();
    test2_9();
    test2_10();
    test2_11();
    test2_12();
    test2_13();
    test2_15();
}

