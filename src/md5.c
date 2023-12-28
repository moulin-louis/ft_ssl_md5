//
// Created by loumouli on 12/19/23.
//

#include "ft_ssl.h"

#define F(X, Y, Z) ((X & Y) | (~X & Z))
#define G(X, Y, Z) ((X & Z) | (Y & ~Z))
#define H(X, Y, Z) (X ^ Y ^ Z)
#define I(X, Y, Z) (Y ^ (X | ~Z))

#define A0 0x67452301
#define B0 0xefcdab89
#define C0 0x98badcfe
#define D0 0x10325476

#define MD5_RESULT_SIZE 16

uint32_t s[64] = {
  7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4,
  11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

uint32_t K[64] = {
  0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8,
  0x8b44f7af,
  0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51,
  0xe9b6c7aa,
  0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905,
  0xfcefa3f8,
  0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60,
  0xbebfbc70,
  0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244,
  0x432aff97,
  0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314,
  0x4e0811a1,
  0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

uint8_t PADDING[64] = {
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00,
  0x00, 0x00, 0x00, 0x00
};

typedef struct {
  uint64_t size; // size of the input in bytes
  uint32_t buffer[4]; // accumulation of hash
  uint8_t input[64]; //input to be used for next step
  uint8_t digest[16]; // result hash
} MD5_Context;

static uint32_t rotl32(const uint32_t x, const uint32_t n) {
  return x << n | x >> (32 - n);
}

void print_md5(t_ssl* ssl) {
  for (uint32_t i = 0; i < MD5_RESULT_SIZE; ++i)
    printf("%02x", ssl->hash[i]);
}

static void ft_md5_init(MD5_Context* ctx) {
  ctx->size = 0;
  ctx->buffer[0] = (uint32_t)A0;
  ctx->buffer[1] = (uint32_t)B0;
  ctx->buffer[2] = (uint32_t)C0;
  ctx->buffer[3] = (uint32_t)D0;
}

static void ft_md5_step(MD5_Context* ctx, const uint32_t* input) {
  uint32_t AA = ctx->buffer[0];
  uint32_t BB = ctx->buffer[1];
  uint32_t CC = ctx->buffer[2];
  uint32_t DD = ctx->buffer[3];

  uint32_t F;
  uint32_t g;
  for (uint32_t i = 0; i < 64; ++i) {
    switch (i / 16) {
      case 0: // if 0 <= i <= 15
        F = F(BB, CC, DD);
        g = i;
        break;
      case 1: // if 16 <= i <= 31
        F = G(BB, CC, DD);
        g = ((i * 5) + 1) % 16;
        break;
      case 2: // if 32 <= i <= 47
        F = H(BB, CC, DD);
        g = ((i * 3) + 5) % 16;
        break;
      default: // if 48 <= i <= 63
        F = I(BB, CC, DD);
        g = (i * 7) % 16;
        break;
    }
    F = F + AA + K[i] + input[g];
    AA = DD;
    DD = CC;
    CC = BB;
    BB = BB + rotl32(F, s[i]);
  }
  ctx->buffer[0] += AA;
  ctx->buffer[1] += BB;
  ctx->buffer[2] += CC;
  ctx->buffer[3] += DD;
}

static void ft_md5_update(MD5_Context* ctx, const uint8_t* data, const uint64_t len) {
  uint32_t input[16];
  uint32_t offset = ctx->size % 64;
  ctx->size += len;

  for (uint32_t i = 0; i < len; ++i) {
    ctx->input[offset++] = (uint8_t)*(data + i);
    if (offset % 64 != 0)
      continue;
    //convert to little endian
    for (uint32_t j = 0; j < 16; ++j)
      input[j] = (uint32_t)ctx->input[j * 4 + 3] << 24 | (uint32_t)ctx->input[j * 4 + 2] << 16 | (uint32_t)ctx->input[j * 4 + 1] << 8 | (uint32_t)ctx->input[j * 4];
    ft_md5_step(ctx, input);
    offset = 0;
  }
}

static void ft_md5_final(MD5_Context* ctx) {
  uint32_t input[16];
  const uint32_t offset = ctx->size % 64;
  const uint32_t pad_len = offset < 56 ? 56 - offset : (56 + 64) - offset;

  ft_md5_update(ctx, PADDING, pad_len);
  ctx->size -= pad_len;
  for (uint32_t j = 0; j < 14; ++j)
    input[j] = (uint32_t)ctx->input[j * 4 + 3] << 24 | (uint32_t)ctx->input[j * 4 + 2] << 16 | (uint32_t)ctx->input[j * 4 + 1] << 8 | (uint32_t)ctx->input[j * 4];
  input[14] = (uint32_t)(ctx->size * 8);
  input[15] = (uint32_t)(ctx->size * 8 >> 32);
  ft_md5_step(ctx, input);
  for (uint32_t i = 0; i < 4; ++i) {
    ctx->digest[i * 4] = (uint8_t)(ctx->buffer[i] & 0x000000FF);
    ctx->digest[i * 4 + 1] = (uint8_t)((ctx->buffer[i] & 0x0000FF00) >> 8);
    ctx->digest[i * 4 + 2] = (uint8_t)((ctx->buffer[i] & 0x00FF0000) >> 16);
    ctx->digest[i * 4 + 3] = (uint8_t)((ctx->buffer[i] & 0xFF000000) >> 24);
  }
}

void hash_md5(t_ssl* ssl) {
  MD5_Context ctx;

  memset(&ctx, 0, sizeof(MD5_Context));
  ft_md5_init(&ctx);
  ft_md5_update(&ctx, ssl->input, ssl->len_input);
  ft_md5_final(&ctx);
  memcpy(ssl->hash, ctx.buffer, MD5_RESULT_SIZE);
}
