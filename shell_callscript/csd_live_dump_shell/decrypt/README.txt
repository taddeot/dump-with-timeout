
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
For the convenience of testing, the storage and naming of files does not conform to the specifications.
When using it officially, please set the path and name of the file first!!!
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

The main files in folder:

1.dec_package.sh: decrypt the package

2.rsa_prikey.pem: the private keys for rsa( for test)

==========================================================================
usage:
"./dec_package.sh <package name>",
for example "./dec_package.sh csd_Athena_123.tar.gz"

Compressed package location:tmp/CSD_PACK
==========================================================================

Result:
[2019-03-20_15-32-10] +++++++++ Start ++++++++

[2019-03-20_15-32-10] MD5 value is the same, decryption is complete.
[2019-03-20_15-32-11] ========= END ================

==========================================================================
A way to get a pair of rsa keys:

$openssl genrsa -out rsa_prikey.pem 2048
$openssl rsa -in rsa_prikey.pem -pubout -out rsa_pubkey.pem

