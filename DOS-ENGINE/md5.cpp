// SWAMI KARUPPASWAMI THUNNAI
#include"md5.h"

MD5::MD5()
{
	Init();
}

void MD5::Init()
{
	context.count[0] = context.count[1] = 0;

	// Load magic initialization constants.
	context.state[0] = 0x67452301;
	context.state[1] = 0xefcdab89;
	context.state[2] = 0x98badcfe;
	context.state[3] = 0x10325476;
}
void MD5::Update(unsigned char *input, unsigned int inputLen) // length of input block
{
	unsigned int i, index, partLen;

	// Compute number of bytes mod 64
	index = (unsigned int)((context.count[0] >> 3) & 0x3F);

	// Update number of bits
	if ((context.count[0] += ((UINT4)inputLen << 3))
		< ((UINT4)inputLen << 3))
		context.count[1]++;
	context.count[1] += ((UINT4)inputLen >> 29);

	partLen = 64 - index;

	// Transform as many times as possible.
	if (inputLen >= partLen) {
		memcpy((POINTER)&context.buffer[index], (POINTER)input, partLen);
		MD5Transform(context.state, context.buffer);

		for (i = partLen; i + 63 < inputLen; i += 64)
			MD5Transform(context.state, &input[i]);

		index = 0;
	}
	else
		i = 0;

	/* Buffer remaining input */
	memcpy((POINTER)&context.buffer[index], (POINTER)&input[i], inputLen - i);
}

void MD5::Final()
{
	unsigned char bits[8];
	unsigned int index, padLen;

	// Save number of bits
	Encode(bits, context.count, 8);

	// Pad out to 56 mod 64.
	index = (unsigned int)((context.count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	Update(PADDING, padLen);

	// Append length (before padding)
	Update(bits, 8);

	// Store state in digest
	Encode(digestRaw, context.state, 16);

	// Zeroize sensitive information.
	memset((POINTER)&context, 0, sizeof(context));

	writeToString();
}

std::string CALL_MD5_Function(char *string1)	//Give path here
{

	MD5 md5;
	// print the digest for a binary file on disk.
	std::string hash = md5.digestFile(string1);
	return hash;
}

void MD5::writeToString()
{
	int pos;

	for (pos = 0; pos < 16; pos++)
	{
		sprintf(digestChars + (pos * 2), "%02x", digestRaw[pos]);	//prints the values
		array_to_be_returned[pos] = digestChars + (pos * 2);
	}
}