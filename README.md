```shell
git clone https://github.com/yildizozan/aes.git
```

```shell
cd aes
```

```shell
git submodule update --init --recursive
```

```shell
mkdir build
```

```shell
cmake ..
```

```shell
make
```

### Program executable paths

AES

```shell
<PROJECT_ROOR>/build/aesctl/aesctl
```

File verifyer

```shell
<PROJECT_ROOR>/build/verifyer/verifyer
```

## aesctl

ECB mode encrypt / decrypt

```shell
aesctl --encrypt --ecb --key "Thats my Kung Fu" --in plain-long.txt
```

```shell
aesctl --decrypt --ecb --key "Thats my Kung Fu" --in out.txt --out decrypted.txt
```

CBC mode encrypt / decrypt

```shell
aesctl --encrypt --cbc --key "Thats my Kung Fu" --iv abcdefghijklmnop --in plain.txt
```

```shell
aesctl --decrypt --cbc --key "Thats my Kung Fu" --iv abcdefghijklmnop --in out.txt --out decrypted.txt 
```

OFB mode encrypt / decrypt

```shell
aesctl --encrypt --ofb --key "Thats my Kung Fu" --iv abcdefghijklmnop --in plain.txt
```

```shell
aesctl --decrypt --ofb --key "Thats my Kung Fu" --iv abcdefghijklmnop --in out.txt --out decrypted.txt 
```
