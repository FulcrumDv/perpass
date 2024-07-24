#pragma once

#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <iostream>
#include <string>
#include <vector>

class Encryption {
public:
  void handleErrors(void);
  int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
              unsigned char *iv, unsigned char *ciphertext);
  int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
              unsigned char *iv, unsigned char *plaintext);
  std::vector<unsigned char> encryptLine(const std::string &line,
                                         const std::string &key);
  std::string decryptLine(const std::vector<unsigned char> &line,
                          const std::string &key);

private:
  const int IV_SIZE = 16; // 128bit for AES
};

#endif // !ENCRYPTION_H
