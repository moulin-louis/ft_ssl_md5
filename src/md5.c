//
// Created by loumouli on 12/19/23.
//

#include "ft_ssl.h"
#include <openssl/evp.h>

#define F(X, Y, Z) ((X & Y) | (~X & Z))
#define G(X, Y, Z) ((X & Z) | (Y & ~Z))
#define H(X, Y, Z) (X ^ Y ^ Z)
#define I(X, Y, Z) (Y ^ (X | ~Z))

//rorate left 32 bits int
#define rotl32(V, R) ((V << R) | (V >> (32 - R))
//rorate left 16 bits int
#define rotl16(V, R) ((V << R) | (V >> (16 - R))
//rorate left 8 bits int
#define rotl8(V, R) ((V << R) | (V >> (8 - R))

#define A0 0x67452301
#define B0 0xefcdab89
#define C0 0x98badcfe
#define D0 0x10325476

#define MD5_RESULT_SIZE 16

typedef struct {
  uint64_t size; // size of the input in bytes
  uint32_t buffer[4]; // accumulation of hash
  uint8_t input[64]; //input to be used for next step
  uint8_t digest[16]; // result hash
  uint32_t s[64];  //s used for md5 algo
  uint32_t K[64]; //K used for md5 algo
} MD5_Context;

void ft_md5_init(MD5_Context* ctx) {
  ctx->size = 0;
  ctx->buffer[0] = A0;
  ctx->buffer[1] = B0;
  ctx->buffer[2] = C0;
  ctx->buffer[3] = D0;
  for (uint32_t i = 0; i < 64; i++) {
    ctx->K[i] = floor(pow(2, 32) * fabs(sin(i + 1)));
  }
  ctx->s = {0, 1, 2};
}

void ft_md5_step(MD5_Context* ctx) {
  uint32_t AA = ctx->buffer[0];
  uint32_t BB = ctx->buffer[1];
  uint32_t CC = ctx->buffer[2];
  uint32_t DD = ctx->buffer[3];

  uint32_t E;
  uint32_t j;

  for (int32_t i = 0; i < 64; i++) {
    switch (i / 16) {
      case 0: //F
        E = F(BB, CC, DD);
        j = i;
        break;
      case 1: //G
        E = G(BB, CC, DD);
        j = (5 * i + 1) % 16;
        break;
      case 2: //H
        E = H(BB, CC, DD);
        j = (3 * i + 5) % 16;
        break;
      default: //I
        E = I(CC, BB, DD);
        j = (7 * i) % 16;
    }
    uint32_t tmp = DD;
    DD = CC;
    CC = BB;
    BB = BB + rotl32(AA + E + ctx->K[i] + ctx->input[j], ctx->s[i]);
    AA = tmp;
  }
  ctx->buffer[0] += AA;
  ctx->buffer[1] += BB;
  ctx->buffer[2] += CC;
  ctx->buffer[3] += DD;
}

void ft_md5_update(MD5_Context* ctx, uint8_t* data, uint64_t len) {

}

void ft_md5_final(MD5_Context* ctx) {

}

void hash_md5(t_ssl* ssl) {
  MD5_Context ctx;
  ft_md5_init(&ctx);
  ft_md5_update(&ctx, ssl->input, strlen((char*)ssl->input));
  ft_md5_final(&ctx);
  memcpy(ssl->hash, ctx.buffer, MD5_RESULT_SIZE);
  printf("MY MD5 RESULT: ");
  for (uint32_t i = 0; i < MD5_RESULT_SIZE; i++) {
    printf("%02x", ssl->hash[i]);
  }
  printf("\n");


  uint8_t result[MD5_RESULT_SIZE] = {};
  uint32_t md_len;
  OpenSSL_add_all_digests();
  const EVP_MD* md = EVP_get_digestbyname("md5");
  EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
  EVP_DigestInit_ex(mdctx, md, NULL);
  EVP_DigestUpdate(mdctx, ssl->input, strlen((char*)ssl->input));
  EVP_DigestFinal_ex(mdctx, result, &md_len);
  EVP_MD_CTX_free(mdctx);
  EVP_cleanup();

  printf("OPENSSL MD5 RESULT: ");
  for (uint32_t i = 0; i < MD5_RESULT_SIZE; i++) {
    printf("%02x", result[i]);
  }
  printf("\n");

  if (memcmp(ssl->hash, result, MD5_RESULT_SIZE) == 0)
    printf("SAME RESULT\n");
  else
    printf("DIFFERENT RESULT\n");
}