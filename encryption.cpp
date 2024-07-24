#include "encryption.h"
#include <openssl/conf.h>
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>
#include <vector>

void Encryption::handleErrors(void) {}

int Encryption::encrypt(unsigned char *plaintext, int plaintext_len,
                        unsigned char *key, unsigned char *iv,
                        unsigned char *ciphertext) {
  EVP_CIPHER_CTX *ctx;

  int len;
  int ciphertext_len;

  // Create and initialise the context
  if (!(ctx = EVP_CIPHER_CTX_new()))
    handleErrors();

  /* Initialise the encryption operation
   * IV size for most modes is the same as the block size
   * AES this is 128 bits
   */
  if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
    handleErrors();
  }

  // input string and get encrypted output
  if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
    handleErrors();
  }

  // Finalize the encryption
  if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
    handleErrors();
  }

  ciphertext_len += len;

  // Clean up
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}
int Encryption::decrypt(unsigned char *ciphertext, int ciphertext_len,
                        unsigned char *key, unsigned char *iv,
                        unsigned char *plaintext) {

  EVP_CIPHER_CTX *ctx;
  int len;
  int plaintext_len;

  // Create and initialise the context
  if (!(ctx = EVP_CIPHER_CTX_new())) {
    handleErrors();
  }

  // Initialise the decryption operation
  if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
    handleErrors();
  }

  if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /*
   * Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
    handleErrors();
  plaintext_len += len;

  // Clean up //
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

// wrapper for encryption for lines of text in a file

std::vector<unsigned char> Encryption::encryptLine(const std::string &line,
                                                   const std::string &key) {

  std::vector<unsigned char> iv(IV_SIZE);
  // generate random iv
  RAND_bytes(iv.data(), IV_SIZE);

  /*
   * vector to hold encrypted data
   * length of input + max block size to account for padding
   */
  std::vector<unsigned char> ciphertext(line.size() + EVP_MAX_BLOCK_LENGTH);

  // reinterpret_cast to convert from const char* to unsigned char*
  int ciphertext_len = encrypt(
      reinterpret_cast<unsigned char *>(const_cast<char *>(line.c_str())),
      line.length(),
      reinterpret_cast<unsigned char *>(const_cast<char *>(key.c_str())),
      iv.data(), ciphertext.data());

  // Prepend IV to ciphertext
  std::vector<unsigned char> result = iv;
  result.insert(result.end(), ciphertext.begin(),
                ciphertext.begin() + ciphertext_len);

  return result;
}

std::string Encryption::decryptLine(const std::vector<unsigned char> &encryptedData,
                        const std::string &key) {
  if (encryptedData.size() <= IV_SIZE) {
    handleErrors();
  }

  std::vector<unsigned char> iv(encryptedData.begin(),
                                encryptedData.begin() + IV_SIZE);
  std::vector<unsigned char> ciphertext(encryptedData.begin() + IV_SIZE,
                                        encryptedData.end());

  std::vector<unsigned char> decrypted(ciphertext.size());
  int decrypted_len = decrypt(
      ciphertext.data(), ciphertext.size(),
      reinterpret_cast<unsigned char *>(const_cast<char *>(key.c_str())),
      iv.data(), decrypted.data());

  return std::string(decrypted.begin(), decrypted.begin() + decrypted_len);
}
