
# perpass Pasword Manager
<p>Basic cli based password manager in c++ that uses AES-256 encryption to store and manage account information</p>
<p>This is a personal project for me to use C++ practically and implement encryption</p>

- [x] Load encrypted passwords from a file
- [x] Add, remove, edit, and view password entries
- [x] Encrypt account info with AES using openSSL
- [x] Save encrypted passwords to a local file
- [x] Master key protection for accessing stored passwords
- [x] Add visual represenation

## Compile and Run

<b>Clone repo:</b>

```sh
git clone https://github.com/FulcrumDv/perpass.git
cd perpass
```
<b>Run</b>

```sh
clang++ encryption.cpp main.cpp passManager.cpp display.cpp service.cpp utilities.cpp  -o perpass -lssl -lcrypto && ./perpass
```


### Down the line
- Move storage method to DB
- Implement AES from scratch (simply for learning)


