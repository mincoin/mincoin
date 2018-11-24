Unauthenticated REST Interface
==============================

The REST API can be enabled with the `-rest` option.

Supported API
-------------

####Transactions
`GET /rest/tx/<TX-HASH>.<bin|hex|json>`

Given a transaction hash: returns a transaction in binary, hex-encoded binary, or JSON formats.

For full TX query capability, one must enable the transaction index via "txindex=1" command line / configuration option.

####Blocks
`GET /rest/block/<BLOCK-HASH>.<bin|hex|json>`
`GET /rest/block/notxdetails/<BLOCK-HASH>.<bin|hex|json>`

Given a block hash: returns a block, in binary, hex-encoded binary or JSON formats.

The HTTP request and response are both handled entirely in-memory, thus making maximum memory usage at least 2.66MB (1 MB max block, plus hex encoding) per request.

With the /notxdetails/ option JSON response will only contain the transaction hash instead of the complete transaction details. The option only affects the JSON response.

####Blockheaders
`GET /rest/headers/<COUNT>/<BLOCK-HASH>.<bin|hex|json>`

Given a block hash: returns <COUNT> amount of blockheaders in upward direction.

####Chaininfos
`GET /rest/chaininfo.json`

Returns various state info regarding block chain processing.
Only supports JSON as output format.
* chain : (string) current network name as defined in BIP70 (main, test, regtest)
* blocks : (numeric) the current number of blocks processed in the server
* headers : (numeric) the current number of headers we have validated
* bestblockhash : (string) the hash of the currently best block
* difficulty : (numeric) the current difficulty
* verificationprogress : (numeric) estimate of verification progress [0..1]
* chainwork : (string) total amount of work in active chain, in hexadecimal
* pruned : (boolean) if the blocks are subject to pruning
* pruneheight : (numeric) heighest block available
* softforks : (array) status of softforks in progress

####Query UTXO set
`GET /rest/getutxos/<checkmempool>/<txid>-<n>/<txid>-<n>/.../<txid>-<n>.<bin|hex|json>`

The getutxo command allows querying of the UTXO set given a set of outpoints.
See BIP64 for input and output serialisation:
https://github.com/bitcoin/bips/blob/master/bip-0064.mediawiki

Example:
```
$ curl localhost:19335/rest/getutxos/checkmempool/34df9912d70143ba6cb2284fdbeeaa8bfa1a35c782d634cd9c63f0eb65fd8943-0.json 2>/dev/null | json_pp
{
   "chaintipHash" : "45c0fe6f2d288231dcdb2ca6341e5350a4092c2f053f27418248721116573ae0",
   "bitmap" : "1",
   "utxos" : [
      {
         "txvers" : 1,
         "height" : 119786,
         "scriptPubKey" : {
            "hex" : "76a9142faeac42c2f380b27858e4ff80008797e3a3a75688ac",
            "addresses" : [
               "mjs5JZArtyArPsXYZWVFpnPXocvoQ2mr8H"
            ],
            "type" : "pubkeyhash",
            "reqSigs" : 1,
            "asm" : "OP_DUP OP_HASH160 2faeac42c2f380b27858e4ff80008797e3a3a756 OP_EQUALVERIFY OP_CHECKSIG"
         },
         "value" : 1.9999519
      }
   ],
   "chainHeight" : 119794
}
```

####Memory pool
`GET /rest/mempool/info.json`

Returns various information about the TX mempool.
Only supports JSON as output format.
* size : (numeric) the number of transactions in the TX mempool
* bytes : (numeric) size of the TX mempool in bytes
* usage : (numeric) total TX mempool memory usage

`GET /rest/mempool/contents.json`

Returns transactions in the TX mempool.
Only supports JSON as output format.

Risks
-------------
Running a web browser on the same node with a REST enabled mincoind can be a risk. Accessing prepared XSS websites could read out tx/block data of your node by placing links like `<script src="http://127.0.0.1:9335/rest/tx/1234567890.json">` which might break the nodes privacy.
