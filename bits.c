/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {//德摩根
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x&~y)&~(x&y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x){//特殊
        if(!y)
            return 1;
        else
            return 0;
    }
    else{
        if (!y)
            return 0;
        else
            if(x>>31 ^ y>>31)//首位符号位
                return 0;
            else return 1;
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using使用位移运算计算一个正整数的以 2 为底的对数
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int a=(v > 0xFFFF)<<4;
    v=v>>a;
    int b=(v > 0xFF)<<3;
    v=v>>b;
    int c=(v > 0xF)<<2;
    v=v>>c;
    int d=(v > 0x3)<<1;
    v=v>>d;
    int e=(v > 0x1);
    v=v>>e;
    return a|b|c|d|e;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int move_n = n << 3;
    int move_m = m << 3;
    int byte_n = (x>> move_n) & 0xFF;
    int byte_m = (x>> move_m) & 0xFF;
    int mask = 0xFF << move_m | 0xFF << (move_n);
    return (x & ~mask) | (byte_n << move_m) | (byte_m << move_n);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) { 
    unsigned result =0;
    int i = 32;
    while(i != 0){
        result = result<<1;
        unsigned temp = v & 1;
        result = result | temp;
        v = v >> 1;
        i = i - 1;
    }
    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    x = x >> n;
    int shift_n = 32 + (~n + 1);
    int no_32shift = shift_n & 0x1F;//防止出现不合法32位移动，学到新的技巧&0x1F
    int mask = ~(~0 << no_32shift) | (((!n)<<31)>>31);//int mask = ~(~0 << no_32shift) | ((~(!n)) + 1)也行
    return x & mask;
}

/*
 * leftBitCount - returns count of number of consective（连续的） 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int allone = !~x;//全一特殊情况
    int cnt = 0;
    int h16_allone = !(~(x >> 16));
    int tmp = h16_allone << 4;
    cnt += tmp;
    x = x << tmp;
    int h8_allone = !(~(x >> 24));
    tmp = h8_allone << 3;
    cnt += tmp;
    x = x << tmp;
    int h4_allone = !(~(x >> 28));
    tmp = h4_allone << 2;
    cnt += tmp;
    x = x << tmp;
    int h2_allone = !(~(x >> 30));
    tmp = h2_allone << 1;
    cnt += tmp;
    x = x << tmp;
    int h1_one = !(~(x >> 31));
    cnt += h1_one;
    return cnt + allone;
}

/*
 * float_i2f - Return bit-level equivalent(等价结果) of expression (float) x
 *   Result is returned as unsigned int（无符号整数）, but it is to be interpreted as the bit-level representation of a single-precision floating point values（单精度浮点数二进制位表示）.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned res = 0;
    unsigned sign = 0;
    unsigned abs = x;
    if(x < 0) {
        sign = 1;
        abs = -x;
    }
    //查找最高位1

    int E = 158;
    if (x == 0) return 0;
    while(!(abs & 0x80000000)){
        E = E-1;
        abs = abs<<1;
    }
    unsigned lost = abs & 0xff;
    int round = 0;
    unsigned m;
    if (lost > 0x80) round = 1;
    else{
        if (lost == 0x80){
            if ((abs >> 8) & 1)//奇数
                round=1;
        }
    }
    if (round){
        abs = abs + 0x100;//第八位（从0数）最低保留位
        if (!(abs & 0x80000000)) E=E+1;
    }
    m = (abs >> 8) & 0x7FFFFF;
    res = (sign << 31)|(E << 23)|m;
    return res;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument阶码全1尾数非0
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
 //不用浮点运算，仅通过整数位操作模拟IEEE754浮点乘2
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned E = (uf >> 23) & 0xFF;
    unsigned M = uf & 0x7FFFFF;
    if( E == 255) return uf;
    else{
        if (E == 0){
            M = M << 1;
        }
        else E=E+1;
    }
    return sign|(E << 23)|M;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.1+11+52
 *   The conversion rounds towards zero.向零舍入（直接截断小数）
 *   Note: Assumes IEEE 754 representation and standard two's complement（二进制补码） integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.返回转换后的整数值，溢出时返回0x80000000，下溢时返回0
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {/*构造一个1后面接52位尾数的整数N，原本的(-1)^S*M*2^real->(-1)^S*N*2^(real-52)
    记k=real-52,考虑正负性
    0、正数：real大于30肯定溢出int
    负数是唯一考虑：且real<=30
    k<0一定右移，位数d=52-real。
    N=high*2^32+low(low是低32位)。
    所以考虑右移位数d是否到32。
    到：先右移32位,low消失,N=high;high再把剩下的位数右移完(d-32)
    不到:low有一部分被留存；high全部21有效位留存，要挪到正确位置（左移32-d）*/
    int sign = uf2 >> 31;
    int E = (uf2 >>20) & 0x7FF;
    int real_e = E - 1023;
    unsigned M_high = (uf2 & (0XFFFFF)) | 1<<20;
    unsigned M_low = uf1;
    unsigned res = 0;
    if (real_e < 0){
        return 0;
    }
    if(E > 0x7FE){
        return 0x80000000;
    }
    if(!E){
        return 0;
    }
    if (real_e > 30){
        return 0x80000000;
    }
    if (real_e < 20){//52-real_e>=32;
        res = M_high >> (20 - real_e);//整个low被弄没了，只剩high右移(52-real_e)-32
    }
    else if(real_e >20){//high左移32-(52-real_e),low(52-real_e)
        res = (M_high << (real_e-20)) | M_low >> (52 - real_e);
    }
    else{
        res = M_high;
    }
    if (sign){
        res = ~res + 1;
    }
    return res;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF(0x7F800000).
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {//sign=0
    int E = x + 127;
    if (x > 127) return 0x7F800000;//上溢
    else if (x < -149) return 0;//下溢
    else if (x <= -127) {//非规格化0.M,E=0,找M
        unsigned m = 1 << (x + 149 );
        return m;
    }
    else return (E << 23);//规格化1.M,E=x+127,M0
}
