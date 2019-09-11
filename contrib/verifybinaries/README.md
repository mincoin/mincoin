### Verify Binaries

#### Preparation:

Make sure you obtain the proper release signing key and verify the fingerprint with several independent sources.

```sh
$ gpg --fingerprint xieta
pub   rsa8192/0xBDB39CC45ADF5086 2013-06-03 [SCEA] [expires: 2040-10-19]
      Key fingerprint = 8023 4F33 8044 2230 709E  43C3 BDB3 9CC4 5ADF 5086
uid                   [ultimate] Xi Eta <xieta@mincointools.com>
sub   rsa8192/0xEA9DEE8F88461978 2013-06-03 [SEA] [expires: 2040-10-19]
      Key fingerprint = E6D4 29DB DC8C 2396 2707  9C50 EA9D EE8F 8846 1978
```

#### Usage:

This script attempts to download the signature file `SHA256SUMS.asc` from https://mincoin.us.

It first checks if the signature passes, and then downloads the files specified in the file, and checks if the hashes of these files match those that are specified in the signature file.

The script returns 0 if everything passes the checks. It returns 1 if either the signature check or the hash check doesn't pass. If an error occurs the return value is 2.


```sh
./verify.sh mincoin-core-0.11.2
./verify.sh mincoin-core-0.12.0
./verify.sh mincoin-core-0.13.0-rc3
```

If you do not want to keep the downloaded binaries, specify anything as the second parameter.

```sh
./verify.sh mincoin-core-0.13.0 delete
```
