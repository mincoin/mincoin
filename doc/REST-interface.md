Unauthenticated REST Interface
==============================

The REST API can be enabled with the `-rest` option.

The interface runs on the same port as the JSON-RPC interface, by default port 9335 for mainnet and port 19335 for testnet.

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
$ curl localhost:19335/rest/getutxos/checkmempool/1e2a14c8d8449f8631561be8e3aa8852679bb66bf5b2e7c0104187bb1e18a9d8-0.json 2>/dev/null | json_pp
{
   "utxos" : [
      {
         "height" : 2147483647,
         "value" : 0.0009252,
         "txvers" : 2,
         "scriptPubKey" : {
            "reqSigs" : 1,
            "type" : "pubkeyhash",
            "hex" : "76a914662210d81335de4a0a626bfb1e5c8203c2e28e8d88ac",
            "addresses" : [
               "mppz2Z5ECsQFVw4Lo3vagYmRTB27cxWFcF"
            ],
            "asm" : "OP_DUP OP_HASH160 662210d81335de4a0a626bfb1e5c8203c2e28e8d OP_EQUALVERIFY OP_CHECKSIG"
         }
      }
   ],
   "chaintipHash" : "f0cb897dd28373d30c90167b6b77efd6f98c54072aeabdcbe38bc1b489660a80",
   "chainHeight" : 125003,
   "bitmap" : "1"
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
