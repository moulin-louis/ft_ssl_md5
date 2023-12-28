//
// Created by loumouli on 12/19/23.
//

#include "ft_ssl.h"

#define SHA256_BLOCK_SIZE 32

#define H0 0x6a09e667
#define H1 0xbb67ae85
#define H2 0x3c6ef372
#define H3 0xa54ff53a
#define H4 0x510e527f
#define H5 0x9b05688c
#define H6 0x1f83d9ab
#define H7 0x5be0cd19

#define rot32l(x, n) (x << n | x >> (32 - n))
#define rot32r(x, n) (x >> n | x << (32 - n))

#define EP0(x) rot32r(x, 2) ^ rot32r(x, 13) ^ rot32r(x, 25)
#define EP1(x) rot32r(x, 6) ^ rot32r(x, 11) ^ rot32r(x, 25)
#define CH(e, f, g) (e & f) ^ ((~e) & g)
#define MAJ(a, b, c) (a & b) ^ (a & c) ~ (b & c)
#define S0(x) rot32r(x, 7) ^ rot32r(x, 18) ^ (x >> 3)
#define S1(x) rot32r(x, 17) ^ rot32r(x, 19) ^ (x >> 10)

uint32_t k[64] = {
  0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
  0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1,
  0xefbe4786,
  0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8,
  0xbf597fc7,
  0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354,
  0x766a0abb,
  0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585,
  0x106aa070,
  0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee,
  0x78a5636f,
  0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

typedef struct {
  uint8_t data[64];
  uint32_t datalen;
  uint64_t bitlen;
  uint32_t state[8];
} SHA256_Context;

static void ft_sha256_init(SHA256_Context* ctx) {
  ctx->datalen = 0;
  ctx->bitlen = 0;
  ctx->state[0] = H0;
  ctx->state[1] = H1;
  ctx->state[2] = H2;
  ctx->state[3] = H3;
  ctx->state[4] = H4;
  ctx->state[5] = H5;
  ctx->state[6] = H6;
  ctx->state[7] = H7;
}

static void ft_sha256_update(SHA256_Context* ctx, uint8_t* data, uint64_t datalen) {

}

static void ft_sha256_final(SHA256_Context* ctx) {

}

void print_sha256(t_ssl* ssl) {
  (void)ssl;
}

void hash_sha256(t_ssl* ssl) {
  SHA256_Context ctx;

  memset(&ctx, 0, sizeof(ctx));
  ft_sha256_init(&ctx);

  (void)ssl;
}
