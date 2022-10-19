# Data Lab
## 1.BitXor
```
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~x&~y)&(~(x&y));
}
```
该函数要用与(and)运算构造异或(^)运算,利用摩尔定律1.A^B = (A&~B)|(~A&B) 2.= ~(~a&~b)&~(a&b) 3.= (a&b)|(~a|~b)
## tmin
```
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 0x80000000;
  //return 1 << 31;
}
```
该函数要求返回int型数据的最小值，可以直接返回也可以令二进制1左移31位来得到。
## 2.isTMax
```
/* isTmax - returns 1 if x is the maximum, two's complement number,
*     and 0 otherwise 
*   Legal ops: ! ~ & ^ | +
*   Max ops: 10
*   Rating: 1
*/
int isTmax(int x) {
  int moreTmax = 0x80000000;//Tmax + 1
	int symbolicBit = !!(moreTmax & x);//
	x = x | moreTmax;
	x = ~x + symbolicBit;
	return ~x;
}
```
该函数判断参数是否为int型数据的最大值，即0x7fffffff。可对符号位与其他位分别判断，首先令symbolicBit为x的符号位，并将x的符号位-置为1。当x等于`0x7fffffff`和`0xffffffff`时，对符号位置1的x取反会得到0值。因此，仅需进而判断原来的x符号位是否为1即可。
## allOddBits
```
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
	int mask = 1<<1;
	mask = mask | (mask<<2);
	mask = mask | (mask<<4);
	mask = mask | (mask<<8);
	mask = mask | (mask<<16);
	return !((mask&x)^mask);
}
```
本函数判断x是否为全为1的数，因此仅需将x与`0xAAAAAAAA`取异或即可。
## negate
```
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	return ~x+1;
}
```
取相反数，根据补码的规则等于反码+1。
## 3.isAsciiDigit
```
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
	int mask1 = ~0xFF;
	return !((mask1&x)+((0xF0&x)^0x30)+!((12&x)^12)+!((10&x)^10));
}
```
本函数需要判断x是否为大于等于0x30且小于等于0x39的数，满足该条件的数有以下性质：
* 高24bit均为0；
* 低5至8bit为0011；
* 低4和低3bit不同时为0；
* 低4和低2bit不同时为0；
将上述条件进行取或操作
## conditional
```
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	int mask1 = !x+(~0);
	int mask2 = ~mask1;
	return y&mask1|z&mask2;
}
```
该函数让我们实现三元运算符。当x为0时，`!x+0xffffffff`为全1掩码，当x为非0时，其为全0掩码。
## isLessOrEqual
```
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int x_sign_bit = ((x>>31)&0x01);
	int y_sign_bit = ((y>>31)&0x01);
	int Tmin = 1 << 31;
	return (!((~x_sign_bit)&y_sign_bit)) & ((!(x^y)) | (x_sign_bit&(~y_sign_bit)) | ((((x+(~y+1))>>31)&0x1)&(!!(y^Tmin))));
}
```
根据x,y的符号位分为几种情况：
1. 满足小于等于
	* 两数相等
	* `x<0, y>0`,避免符号位相等时的溢出情况
	* 符号位相等比较。通过第一个操作数加上第二个操作数取补的形式，若结果小于0，则`x<y`

	(1)负负比较，可能会出现对`Tmin`取补发生下溢出的特殊情况，因此需要排除第二个操作数为`Tmin`的情况，恰好该情况要么**相等**，要么就是`x>y`
	(2)正正比较
2. 不满足小于等于，即大于等于(`x>0, y<0`)
## 4.logicalNeg
```
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  return ((x>>31)|((~x+1)>>31))+1;
}
```
利于0的补码是其本身的特性将0与正数负数区分开来。再利用算数右移特性，将0构造成全0，负数和正数构造成全1，最后+1得到返回值。
## howManyBits
```
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
```
**对于负数，最少位数的二进制表示为一位符号位加上负数取反后的最高位1的位数；对于正数，最少位数的二进制表示为一位符号位加上其最高位1的位数;**对于int型数据，符号位为0的最小数为0，符号位为1的最大数为-1，当非负数 x 和负数 y 满足 x == -y-1 时，x 和 ~y的二进制表示相同。因此，对于负数以-1为起点编码、对于正数以0为起点编码的编码方式所得到的int类型整体2进制位数最小。其中，对最高位1的位数的求取可以采用手动二分法得到。
## floatScale2
```
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
```
这题的意思是要求浮点数 *2 之后的值，先根据 IEEE 浮点数依次求出符号位、阶码位以及小数位。因为 float 是 32 位，一般 s = 1、exp 为 8 位，然后小数位为 23 位。
根据这些条件排除掉无穷小、0、无穷大以及NaN 的情况：
* 无穷大和 NAN 直接返回参数就行(怎么乘都是一样的)
* 无穷小和0则直接 *2 带上符号位就行
* 剩下的情况，指数 +1 之后指数为 255 则表示为无穷大(*2相当于指数 +1)，否则返回指数 + 1 后的原符号数
## floatFloat2int
```
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
```
大概分为这几种情况:
* 原符号值为0就返回0
* 阶码部分大于31(小数部分是大于1的)，就返回题目规定的溢出值
* 其它情况对于浮点数的小数位正常移位操作即可
## floatPower2
```
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
```
这题要求计算浮点数 2.0^x，因为浮点数中阶码表示的意义正好是2的多少次幂。
最小的正规格化数为：2^(1-bias-n) = 2^(-149)，bias = 2^(k-1) - 1 = 127,n = 23
最小规格化数：2^(0-bias) * 2 = 2 ^ (-126)
最大规格化数：2^(2^8 - 2 - bias) = 2 ^ 127
因此区间为 [Tmin, -148], [-149, -125], [-126, 127], [128, Tmax]