
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
For the convenience of testing, the storage and naming of files does not conform to the specifications.
When using it officially, please set the path and name of the file first!!!
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

The main files in folder:

1.livedump.sh: call dump shell and encrypt package(#!/bin/sh)

2.mk_files/: script to make files(for test)

3.rsa_pubkey.pem:the public keys for rsa( for test)

4.checkdumpfile.sh: check file exist

5. tftpdownload.sh: send package to server

6. bash_livedump.sh: When using the /bin/bash interpreter, the output of the kill command cannot be masked, so use the trap command.
It is especially used for the bash interpreter

==========================================================================
Instructions:

use "./ivedump.sh" to run the shell

the shell will call mk_files1>mk_files2>mk_files3>mk_files4>mk_files5
and the result will be:
++++++++++++++++++++++++++++++++
+ livedump1:fail               +
+ livedump2:success            +
+ livedump3:fail               +
+ livedump4success             +
+ livedump5:fail               +
++++++++++++++++++++++++++++++++
==========================================================================
	 Content Layout
(omit)

==========================================================================
The livedump.sh script will encrypt the package(aes+rsa) after dump is completed.
The original compressed package  is: tmp/CSD_PACK/csd_Originalfile.tar.gz
The encrypted package name is: tmp/CSD_PACK/csd_encd_file.tar.gz

Csd_encd_file.tar.gz contains the following:
1.csd_enc.tar.gz: Aes encrypted csd_Originalfile.tar.gz
2.csd_key.log: Rsa encrypted aes key
3.md5.log: MD5 value of csd_Originalfile.tar.gz
==========================================================================















#User guides about smime
#1.Generate private and public keys
#"openssl req -x509 -nodes -days 100000 -newkey rsa:2048  -keyout privatekey.pem  -out #publickey.pem"
#then you will be asked to answer some questions
#2.Encrypt file(s) by pubclickey
#"openssl  smime  -encrypt -aes256  -in  example.tar.gz  -binary  -outform DEM  -out  #example.en  publickey.pem"
#3.Decrypt
#"openssl  smime -decrypt  -in  example.en  -binary -inform DEM -inkey privatekey.pem  -out  #example_test.tar.gz "

