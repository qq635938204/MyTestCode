// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 MD5_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// MD5_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#include <stdio.h>
#include "../Code/public.h"
#include <string>
using namespace std;

#ifdef _DEBUG
#define  PATH "../X64/Debug/MD5.lib"
#else
#define  PATH "../X64/Release/MD5.lib"
#endif
#ifdef MD5_EXPORTS
#define MD5_API __declspec(dllexport)
#else
#define MD5_API __declspec(dllimport)
#pragma	comment(lib,PATH)
#endif

/* MD5 context. */
typedef struct {
	UINT4 state[4];                                   /* state (ABCD) */
	UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;

// 此类是从 MD5.dll 导出的
class MD5_API CMD5 {
public:
	CMD5(void);
	~CMD5();
	// TODO:  在此添加您的方法。
public:
	typedef unsigned char uchar8; //make sure it is 8bit
	typedef char char8; //make sure it is 8bit

	void init();

	void UpdateMd5(const uchar8 input[], const int length);
	void UpdateMd5(const char8 input[], const int length);

	void Finalize();

	void ComputMd5(const uchar8 input[], const int length);
	void ComputMd5(const char8 input[], const int length);

	string GetMd5();

	void printMd5();


private:
	typedef unsigned int uint32;       //make sure it is 32 bit;
	typedef unsigned long long uint64; //make sure it is 64 bit;
	uint32 A, B, C, D;
	const static int blockLen_ = 64;    // 512/8                                  
	//the remain after last updata (because md5 may be computed segment by segment)
	uchar8 remain_[blockLen_];
	int remainNum_;         // the number of remain_,  < 64 
	uint64 totalInputBits_;
	uchar8 md5Result_[16];   //bit style md5 result,totally 128 bit
	char md5Result_hex_[33]; //hexadecimal style result; md5Result_hex_[32]='\0'
	bool isDone_;            // indicate the comput is finished;

	inline uint32 RotateLeft(const uint32 x, int n);
	inline uint32 F(const uint32 x, const uint32 y, const uint32 z);
	inline uint32 G(const uint32 x, const uint32 y, const uint32 z);
	inline uint32 H(const uint32 x, const uint32 y, const uint32 z);
	inline uint32 I(const uint32 x, const uint32 y, const uint32 z);
	inline void FF(uint32 &a, const uint32 b, const uint32 c, const uint32 d,
		const uint32 Mj, const int s, const uint32 ti);
	inline void GG(uint32 &a, const uint32 b, const uint32 c, const uint32 d,
		const uint32 Mj, const int s, const uint32 ti);
	inline void HH(uint32 &a, const uint32 b, const uint32 c, const uint32 d,
		const uint32 Mj, const int s, const uint32 ti);
	inline void II(uint32 &a, const uint32 b, const uint32 c, const uint32 d,
		const uint32 Mj, const int s, const uint32 ti);


	void UcharToUint(uint32 output[], const uchar8 input[], const unsigned int transLength);

	void FourRound(const uchar8 block[]);

	void LinkResult();
};

extern MD5_API int nMD5;

MD5_API int fnMD5(void);

MD5_API void Test(void);