/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

Integer Coding Rules

一.Expr
1.整型操作数的值被限制在范围[0, 255]。
2.不能使用全局变量
3.只能使用的一元操作!, ~
4.只能使用的二元操作&, ^, |, +, <<, >>
5.一个表达式不会被限制拥有多个操作符
二.Fobidden
1.使用控制语句如if, do, while, for, switch等等
2.定义或使用任何宏
3.在当前文件中定义任何额外的函数
4.调用任何函数
5.使用其他操作
6.使用类型转换
7.使用除int之外的任何数据类型，使用arrays, structs, unions
8.假设机器的配置
9.使用2的补码，int的表示为32-bit
10.执行算术右移
11.如果左移的位数小于0或者大于31则会出现未预测的行为。
Floating Point Coding Rules

一.Forbidden
1.定义或使用任何宏
2.定义任何额外的函数
3.调用任何函数
4.使用任何形式的类型转换
5.使用arrays, structs, unions
Notes

1.使用dlc(data tab checker)编译器来检查解决方案的合理性
2.使用btest来检查你的函数的正确性
3.使用BDD checker来正式地证实你的函数


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
 //用与(and)运算构造异或(^)运算,利用摩尔定律1.A^B = (A&~B)|(~A&B) 2.= ~(~a&~b)&~(a&b) 3.= (a&b)|(~a|~b)
int bitXor(int x, int y) {
  return ~(~x&~y)&(~(x&y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
 //返回int型数据的最小值
int tmin(void) {
  return 0x80000000;
  //return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
 //判断参数是否为int型数据的最大值,即0x7fffffff
int isTmax(int x) {
    int moreTmax = 0x80000000;
	int symbolicBit = !!(moreTmax & x);
	x = x | moreTmax;
	x = ~x + symbolicBit;
	return !x;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
 //判断x是否为奇数(全为1的数)
int allOddBits(int x) {
	int mask = 1<<1;
	mask = mask | (mask<<2);
	mask = mask | (mask<<4);
	mask = mask | (mask<<8);
	mask = mask | (mask<<16);
	return !((mask&x)^mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
 //取相反数
int negate(int x) {
	return ~x+1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
 //判断x是否为大于等于0x30且小于等于0x39的数。
int isAsciiDigit(int x) {
	int mask1 = ~0xFF;
	return !((mask1&x)+((0xF0&x)^0x30)+!((12&x)^12)+!((10&x)^10));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
 //该函数实现三元运算符
int conditional(int x, int y, int z) {
	int mask1 = !x+(~0);
	int mask2 = ~mask1;
	return y&mask1|z&mask2;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
 //x <= y主要难点在于对减法溢出的判断
int isLessOrEqual(int x, int y) {
	int x_sign_bit = ((x>>31)&0x01);
	int y_sign_bit = ((y>>31)&0x01);
	int Tmin = 1 << 31;
	return (!((~x_sign_bit)&y_sign_bit)) & ((!(x^y)) | (x_sign_bit&(~y_sign_bit)) | ((((x+(~y+1))>>31)&0x1)&(!!(y^Tmin))));
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
//取反操作
int logicalNeg(int x) {
  return ((x>>31)|((~x+1)>>31))+1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
 //最少位数的二进制表示
int howManyBits(int x) {
	int flag = x>>31;
	x = (flag&~x)|(~flag&x);
	int b16 = (!!(x>>16))<<4;
	x = x >> b16;
	int b8 = (!!(x>>8))<<3;
	x = x >> b8;
	int b4 = (!!(x>>4))<<2;
	x = x >> b4;
	int b2 = (!!(x>>2))<<1;
	x = x >> b2;
	int b1 = !!(x>>1);
	x = x >> b1;
	return 1+b1+b2+b4+b8+b16+x;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
 //返回浮点数*2之后的值
// 求 2 乘浮点数
unsigned floatScale2(unsigned uf) {
  // 求出阶码位
  unsigned exp = uf & 0x7f800000;
  // 符号位
  unsigned sign = uf & 0x80000000;
  // 小数位置
  unsigned frac = uf & 0x007fffff;

  // 无穷小和0的情况
  if (exp == 0) {
    return sign | uf << 1;
  }

  // 无穷大和 NAN 的情况
  if (exp == 0x7f800000) {
    return uf;
  }

  // 阶码 + 1 如果无穷大的话，就直接返回原符号无穷大
  exp += 0x00800000;

  if (exp == 0x7f800000) {
    frac = 0;
  }
  // 如果不是无穷大就返回 +1 后的原符号数
  return sign | exp | frac;
}

/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
 //将浮点数转换为整数
int floatFloat2Int(unsigned uf) {
  // 符号位
  int sign = uf >> 31;
  // 阶码位
  int exp = ((uf >> 23) & 0xff) - 127;
  // 小数位
  int frac = (uf & 0x007fffff) | 0x00800000;
  int value = 0;
  if (exp < 0) {
    return 0;
  }
  if (exp > 31) {
    return 0x80000000;
  }
  if (exp < 23) {
    value = frac >> (23 - exp);
  } else if (exp > 23) {
    value = frac << (exp - 23);
  }
  return sign ? ~value + 1 : value; 
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
 //要求计算浮点数2.0^x
unsigned floatPower2(int x) {
  if (x < -149) {
    return 0;
  }
  if (x < -126) {
    return 1 << (x + 149);
  }
  if (x < 128) {
    return (x + 127) << 23;
  }
  // INF
  return 0xff << 23;
}
