Mincoin Core version 0.13.0 is now available from:

  <https://mincoinforum.com/bin/mincoin-core-0.13.0/>

This is a security update and new major version release, including new features,
various bugfixes and performance improvements as well as updated translations.
It is recommended to upgrade to this release as soon as possible.

Please report bugs using the issue tracker at github:

  <https://github.com/mincoin/mincoin/issues>

The notes below chronicle inherited changes introduced upstream starting with
the 0.9 branch and ending with v0.13.0 for this release. References to
pull-requests, branches and some other details have been preserved.


Upgrading and downgrading
=========================

How to Upgrade
--------------

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over /Applications/Mincoin-Qt (on Mac) or
mincoind/mincoin-qt (on Linux).


Downgrade warning
-----------------

### Downgrade to a version < 0.10.0

Because release 0.10.0 and later makes use of headers-first synchronization and
parallel block download (see further), the block files and databases are not
backwards-compatible with pre-0.10 versions of Mincoin Core or other software:

* Blocks will be stored on disk out of order (in the order they are
received, really), which makes it incompatible with some tools or
other programs. Reindexing using earlier versions will also not work
anymore as a result of this.

* The block index database will now hold headers for which no block is
stored on disk, which earlier versions won't support.

If you want to be able to downgrade smoothly, make a backup of your entire data
directory. Without this your node will need start syncing (or importing from
bootstrap.dat) anew afterwards. It is possible that the data from a completely
synchronised 0.10 node may be usable in older versions as-is, but this is not
supported and may break as soon as the older version attempts to reindex.

This does not affect wallet forward or backward compatibility.

### Downgrade to a version < 0.12.0

Because release 0.12.0 and later will obfuscate the chainstate on every
fresh sync or reindex, the chainstate is not backwards-compatible with
pre-0.12 versions of Mincoin Core or other software.

If you want to downgrade after you have done a reindex with 0.12.0 or later,
you will need to reindex when you first start Mincoin Core version 0.11 or
earlier.


Windows 64-bit installer
------------------------

New in 0.9.0 is the Windows 64-bit version of the client. There have been
frequent reports of users running out of virtual memory on 32-bit systems
during the initial sync. Because of this it is recommended to install the
64-bit version if your system supports it.

NOTE: Release candidate 2 Windows binaries are not code-signed; use PGP
and the SHA256SUMS.asc file to make sure your binaries are correct.
In the final 0.9.0 release, Windows setup.exe binaries will be code-signed.


OSX 10.5 / 32-bit no longer supported
-------------------------------------

0.9.0 drops support for older Macs. The minimum requirements are now:
* A 64-bit-capable CPU (see http://support.apple.com/kb/ht3696);
* Mac OS 10.6 or later (see https://support.apple.com/kb/ht1633).


Important information
=====================

Rebranding to Mincoin Core
--------------------------

To reduce confusion between Mincoin-the-network and Mincoin-the-software we
have renamed the reference client to Mincoin Core.


Gitian OSX build
----------------

The deterministic build system that was already used for Windows and Linux
builds is now used for OSX as well. Although the resulting executables have
been tested quite a bit, there could be possible regressions. Be sure to report
these on the Github bug tracker mentioned above.


Transaction flooding
--------------------

At the time of this release, the P2P network is being flooded with low-fee
transactions. This causes a ballooning of the mempool size.

If this growth of the mempool causes problematic memory use on your node, it is
possible to change a few configuration options to work around this. The growth
of the mempool can be monitored with the RPC command `getmempoolinfo`.

One is to increase the minimum transaction relay fee `minrelaytxfee`, which
defaults to 0.00001. This will cause transactions with fewer MNC/kB fee to be
rejected, and thus fewer transactions entering the mempool.

The other is to restrict the relaying of free transactions with
`limitfreerelay`. This option sets the number of kB/minute at which
free transactions (with enough priority) will be accepted. It defaults to 15.
Reducing this number reduces the speed at which the mempool can grow due
to free transactions.

For example, add the following to `mincoin.conf`:

    minrelaytxfee=0.00005 
    limitfreerelay=5

More robust solutions are being worked on for a follow-up release.


Compatibility
=============

Microsoft ended support for Windows XP on [April 8th, 2014](https://www.microsoft.com/en-us/WindowsForBusiness/end-of-xp-support),
an OS initially released in 2001. This means that not even critical security
updates will be released anymore. Without security updates, using a mincoin
wallet on a XP machine is irresponsible at least.

In addition to that, with 0.12.x there have been varied reports of Mincoin Core
randomly crashing on Windows XP. It is [not clear](https://github.com/bitcoin/bitcoin/issues/7681#issuecomment-217439891)
what the source of these crashes is, but it is likely that upstream
libraries such as Qt are no longer being tested on XP.

We do not have time nor resources to provide support for an OS that is
end-of-life. From 0.13.0 on, Windows XP is no longer supported. Users are
suggested to upgrade to a newer verion of Windows, or install an alternative OS
that is supported.

No attempt is made to prevent installing or running the software on Windows XP,
you can still do so at your own risk, but do not expect it to work: do not
report issues about Windows XP to the issue tracker.


Notable changes
===============

OP_RETURN and data in the block chain
-------------------------------------

On OP_RETURN:  There was been some confusion and misunderstanding in
the community, regarding the OP_RETURN feature in 0.9 and data in the
blockchain.  This change is not an endorsement of storing data in the
blockchain.  The OP_RETURN change creates a provably-prunable output,
to avoid data storage schemes -- some of which were already deployed --
that were storing arbitrary data such as images as forever-unspendable
TX outputs, bloating mincoin's UTXO database.

Storing arbitrary data in the blockchain is still a bad idea; it is less
costly and far more efficient to store non-currency data elsewhere.


Autotools build system
-----------------------

For 0.9.0 we switched to an autotools-based build system instead of individual
(q)makefiles.

Using the standard "./autogen.sh; ./configure; make" to build Mincoin-Qt and
mincoind makes it easier for experienced open source developers to contribute 
to the project.

Be sure to check doc/build-*.md for your platform before building from source.


Mincoin-cli
-----------

Another change in the 0.9 release is moving away from the mincoind executable
functioning both as a server and as a RPC client. The RPC client functionality
("tell the running mincoin daemon to do THIS") was split into a separate
executable, 'mincoin-cli'. The RPC client code will eventually be removed from
mincoind, but will be kept for backwards compatibility for a release or two.


`walletpassphrase` RPC
----------------------

The behavior of the `walletpassphrase` RPC when the wallet is already unlocked
has changed between 0.8 and 0.9.

The 0.8 behavior of `walletpassphrase` is to fail when the wallet is already unlocked:

    > walletpassphrase 1000
    walletunlocktime = now + 1000
    > walletpassphrase 10
    Error: Wallet is already unlocked (old unlock time stays)

The new behavior of `walletpassphrase` is to set a new unlock time overriding
the old one:

    > walletpassphrase 1000
    walletunlocktime = now + 1000
    > walletpassphrase 10
    walletunlocktime = now + 10 (overriding the old unlock time)


Transaction malleability-related fixes
--------------------------------------

This release contains a few fixes for transaction ID (TXID) malleability 
issues:

- -nospendzeroconfchange command-line option, to avoid spending
  zero-confirmation change
- IsStandard() transaction rules tightened to prevent relaying and mining of
  mutated transactions
- Additional information in listtransactions/gettransaction output to
  report wallet transactions that conflict with each other because
  they spend the same outputs.
- Bug fixes to the getbalance/listaccounts RPC commands, which would report
  incorrect balances for double-spent (or mutated) transactions.
- New option: -zapwallettxes to rebuild the wallet's transaction information

Transaction Fees
----------------

This release drops the default fee required to relay transactions across the
network and for miners to consider the transaction in their blocks to
0.01mMNC per kilobyte.

Note that getting a transaction relayed across the network does NOT guarantee
that the transaction will be accepted by a miner; by default, miners fill
their blocks with 50 kilobytes of high-priority transactions, and then with
700 kilobytes of the highest-fee-per-kilobyte transactions.

The minimum relay/mining fee-per-kilobyte may be changed with the
minrelaytxfee option. Note that previous releases incorrectly used
the mintxfee setting to determine which low-priority transactions should
be considered for inclusion in blocks.

The wallet code still uses a default fee for low-priority transactions of
0.1mMNC per kilobyte. During periods of heavy transaction volume, even this
fee may not be enough to get transactions confirmed quickly; the mintxfee
option may be used to override the default.


Faster synchronization
----------------------

Mincoin Core now uses 'headers-first synchronization'. This means that we first
ask peers for block headers (a total of 27 megabytes, as of December 2014) and
validate those. In a second stage, when the headers have been discovered, we
download the blocks. However, as we already know about the whole chain in
advance, the blocks can be downloaded in parallel from all available peers.

In practice, this means a much faster and more robust synchronization. On
recent hardware with a decent network link, it can be as little as 3 hours
for an initial full synchronization. You may notice a slower progress in the
very first few minutes, when headers are still being fetched and verified, but
it should gain speed afterwards.

A few RPCs were added/updated as a result of this:
- `getblockchaininfo` now returns the number of validated headers in addition to
the number of validated blocks.
- `getpeerinfo` lists both the number of blocks and headers we know we have in
common with each peer. While synchronizing, the heights of the blocks that we
have requested from peers (but haven't received yet) are also listed as
'inflight'.
- A new RPC `getchaintips` lists all known branches of the block chain,
including those we only have headers for.


Transaction fee changes
-----------------------

This release automatically estimates how high a transaction fee (or how
high a priority) transactions require to be confirmed quickly. The default
settings will create transactions that confirm quickly; see the new
'txconfirmtarget' setting to control the tradeoff between fees and
confirmation times. Fees are added by default unless the 'sendfreetransactions' 
setting is enabled.

Prior releases used hard-coded fees (and priorities), and would
sometimes create transactions that took a very long time to confirm.

Statistics used to estimate fees and priorities are saved in the
data directory in the `fee_estimates.dat` file just before
program shutdown, and are read in at startup.

New command line options for transaction fee changes:
- `-txconfirmtarget=n` : create transactions that have enough fees (or priority)
so they are likely to begin confirmation within n blocks (default: 1). This setting
is over-ridden by the -paytxfee option.
- `-sendfreetransactions` : Send transactions as zero-fee transactions if possible 
(default: 0)

New RPC commands for fee estimation:
- `estimatefee nblocks` : Returns approximate fee-per-1,000-bytes needed for
a transaction to begin confirmation within nblocks. Returns -1 if not enough
transactions have been observed to compute a good estimate.
- `estimatepriority nblocks` : Returns approximate priority needed for
a zero-fee transaction to begin confirmation within nblocks. Returns -1 if not
enough free transactions have been observed to compute a good
estimate.


RPC access control changes
--------------------------

Subnet matching for the purpose of access control is now done
by matching the binary network address, instead of with string wildcard matching.
For the user this means that `-rpcallowip` takes a subnet specification, which can be

- a single IP address (e.g. `1.2.3.4` or `fe80::0012:3456:789a:bcde`)
- a network/CIDR (e.g. `1.2.3.0/24` or `fe80::0000/64`)
- a network/netmask (e.g. `1.2.3.4/255.255.255.0` or `fe80::0012:3456:789a:bcde/ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff`)

An arbitrary number of `-rpcallow` arguments can be given. An incoming connection will be accepted if its origin address
matches one of them.

For example:

| 0.9.x and before                           | 0.10.x                                |
|--------------------------------------------|---------------------------------------|
| `-rpcallowip=192.168.1.1`                  | `-rpcallowip=192.168.1.1` (unchanged) |
| `-rpcallowip=192.168.1.*`                  | `-rpcallowip=192.168.1.0/24`          |
| `-rpcallowip=192.168.*`                    | `-rpcallowip=192.168.0.0/16`          |
| `-rpcallowip=*` (dangerous!)               | `-rpcallowip=::/0` (still dangerous!) |

Using wildcards will result in the rule being rejected with the following error in debug.log:

    Error: Invalid -rpcallowip subnet specification: *. Valid are a single IP (e.g. 1.2.3.4), a network/netmask (e.g. 1.2.3.4/255.255.255.0) or a network/CIDR (e.g. 1.2.3.4/24).


REST interface
--------------

A new HTTP API is exposed when running with the `-rest` flag, which allows
unauthenticated access to public node data.

It is served on the same port as RPC, but does not need a password, and uses
plain HTTP instead of JSON-RPC.

Assuming a local RPC server running on port 9335, it is possible to request:
- Blocks: http://localhost:9335/rest/block/*HASH*.*EXT*
- Blocks without transactions: http://localhost:9335/rest/block/notxdetails/*HASH*.*EXT*
- Transactions (requires `-txindex`): http://localhost:9335/rest/tx/*HASH*.*EXT*

In every case, *EXT* can be `bin` (for raw binary data), `hex` (for hex-encoded
binary) or `json`.

For more details, see the `doc/REST-interface.md` document in the repository.


RPC Server "Warm-Up" Mode
-------------------------

The RPC server is started earlier now, before most of the expensive
intialisations like loading the block index.  It is available now almost
immediately after starting the process.  However, until all initialisations
are done, it always returns an immediate error with code -28 to all calls.

This new behaviour can be useful for clients to know that a server is already
started and will be available soon (for instance, so that they do not
have to start it themselves).


Improved signing security
-------------------------

For 0.10 the security of signing against unusual attacks has been
improved by making the signatures constant time and deterministic.

This change is a result of switching signing to use libsecp256k1
instead of OpenSSL. Libsecp256k1 is a cryptographic library
optimized for the curve Mincoin uses which was created by Bitcoin
Core developer Pieter Wuille.

There exist attacks[1] against most ECC implementations where an
attacker on shared virtual machine hardware could extract a private
key if they could cause a target to sign using the same key hundreds
of times. While using shared hosts and reusing keys are inadvisable
for other reasons, it's a better practice to avoid the exposure.

OpenSSL has code in their source repository for derandomization
and reduction in timing leaks that we've eagerly wanted to use for a
long time, but this functionality has still not made its
way into a released version of OpenSSL. Libsecp256k1 achieves
significantly stronger protection: As far as we're aware this is
the only deployed implementation of constant time signing for
the curve Mincoin uses and we have reason to believe that
libsecp256k1 is better tested and more thoroughly reviewed
than the implementation in OpenSSL.

[1] https://eprint.iacr.org/2014/161.pdf


Watch-only wallet support
-------------------------

The wallet can now track transactions to and from wallets for which you know
all addresses (or scripts), even without the private keys.

This can be used to track payments without needing the private keys online on a
possibly vulnerable system. In addition, it can help for (manual) construction
of multisig transactions where you are only one of the signers.

One new RPC, `importaddress`, is added which functions similarly to
`importprivkey`, but instead takes an address or script (in hexadecimal) as
argument.  After using it, outputs credited to this address or script are
considered to be received, and transactions consuming these outputs will be
considered to be sent.

The following RPCs have optional support for watch-only:
`getbalance`, `listreceivedbyaddress`, `listreceivedbyaccount`,
`listtransactions`, `listaccounts`, `listsinceblock`, `gettransaction`. See the
RPC documentation for those methods for more information.

Compared to using `getrawtransaction`, this mechanism does not require
`-txindex`, scales better, integrates better with the wallet, and is compatible
with future block chain pruning functionality. It does mean that all relevant
addresses need to added to the wallet before the payment, though.


Consensus library
-----------------

Starting from 0.10.0, the Mincoin Core distribution includes a consensus library.

The purpose of this library is to make the verification functionality that is
critical to Mincoin's consensus available to other applications, e.g. to language
bindings such as [python-bitcoinlib](https://pypi.python.org/pypi/python-bitcoinlib) or
alternative node implementations.

This library is called `libbitcoinconsensus.so` (or, `.dll` for Windows).
Its interface is defined in the C header [bitcoinconsensus.h](https://github.com/bitcoin/bitcoin/blob/0.10/src/script/bitcoinconsensus.h).

In its initial version the API includes two functions:

- `bitcoinconsensus_verify_script` verifies a script. It returns whether the indicated input of the provided serialized transaction 
correctly spends the passed scriptPubKey under additional constraints indicated by flags
- `bitcoinconsensus_version` returns the API version, currently at an experimental `0`

The functionality is planned to be extended to e.g. UTXO management in upcoming releases, but the interface
for existing methods should remain stable.


Standard script rules relaxed for P2SH addresses
------------------------------------------------

The IsStandard() rules have been almost completely removed for P2SH
redemption scripts, allowing applications to make use of any valid
script type, such as "n-of-m OR y", hash-locked oracle addresses, etc.
While the Mincoin protocol has always supported these types of script,
actually using them on mainnet has been previously inconvenient as
standard Mincoin Core nodes wouldn't relay them to miners, nor would
most miners include them in blocks they mined.


mincoin-tx
----------

It has been observed that many of the RPC functions offered by mincoind are
"pure functions", and operate independently of the mincoind wallet. This
included many of the RPC "raw transaction" API functions, such as
createrawtransaction.

mincoin-tx is a newly introduced command line utility designed to enable easy
manipulation of mincoin transactions. A summary of its operation may be
obtained via "mincoin-tx --help" Transactions may be created or signed in a
manner similar to the RPC raw tx API. Transactions may be updated, deleting
inputs or outputs, or appending new inputs and outputs. Custom scripts may be
easily composed using a simple text notation, borrowed from the mincoin test
suite.

This tool may be used for experimenting with new transaction types, signing
multi-party transactions, and many other uses. Long term, the goal is to
deprecate and remove "pure function" RPC API calls, as those do not require a
server round-trip to execute.

Other utilities "mincoin-key" and "mincoin-script" have been proposed, making
key and script operations easily accessible via command line.


Mining and relay policy enhancements
------------------------------------

Mincoin Core's block templates are now for version 3 blocks only, and any mining
software relying on its `getblocktemplate` must be updated in parallel to use
libblkmaker either version 0.4.2 or any version from 0.5.1 onward.
If you are solo mining, this will affect you the moment you upgrade Mincoin
Core, which must be done prior to BIP66 achieving its 951/1001 status.
If you are mining with the stratum mining protocol: this does not affect you.
If you are mining with the getblocktemplate protocol to a pool: this will affect
you at the pool operator's discretion, which must be no later than BIP66
achieving its 951/1001 status.

The `prioritisetransaction` RPC method has been added to enable miners to
manipulate the priority of transactions on an individual basis.

Mincoin Core now supports BIP 22 long polling, so mining software can be
notified immediately of new templates rather than having to poll periodically.

Support for BIP 23 block proposals is now available in Mincoin Core's
`getblocktemplate` method. This enables miners to check the basic validity of
their next block before expending work on it, reducing risks of accidental
hardforks or mining invalid blocks.

Two new options to control mining policy:
- `-datacarrier=0/1` : Relay and mine "data carrier" (OP_RETURN) transactions
if this is 1.
- `-datacarriersize=n` : Maximum size, in bytes, we consider acceptable for
"data carrier" outputs.

The relay policy has changed to more properly implement the desired behavior of not 
relaying free (or very low fee) transactions unless they have a priority above the 
AllowFreeThreshold(), in which case they are relayed subject to the rate limiter.


BIP 66: strict DER encoding for signatures
------------------------------------------

Mincoin Core 0.10 implements BIP 66, which introduces block version 3, and a new
consensus rule, which prohibits non-DER signatures. Such transactions have been
non-standard since Mincoin v0.8.0 (released in February 2013), but were
technically still permitted inside blocks.

This change breaks the dependency on OpenSSL's signature parsing, and is
required if implementations would want to remove all of OpenSSL from the
consensus code.

The same miner-voting mechanism as in BIP 34 is used: when 751 out of a
sequence of 1001 blocks have version number 3 or higher, the new consensus
rule becomes active for those blocks. When 951 out of a sequence of 1001
blocks have version number 3 or higher, it becomes mandatory for all blocks.

Backward compatibility with current mining software is NOT provided, thus miners
should read the first paragraph of "Mining and relay policy enhancements" above.


Block file pruning
------------------

This release supports running a fully validating node without maintaining a copy 
of the raw block and undo data on disk. To recap, there are four types of data 
related to the blockchain in the mincoin system: the raw blocks as received over 
the network (blk???.dat), the undo data (rev???.dat), the block index and the 
UTXO set (both LevelDB databases). The databases are built from the raw data.

Block pruning allows Mincoin Core to delete the raw block and undo data once 
it's been validated and used to build the databases. At that point, the raw data 
is used only to relay blocks to other nodes, to handle reorganizations, to look 
up old transactions (if -txindex is enabled or via the RPC/REST interfaces), or 
for rescanning the wallet. The block index continues to hold the metadata about 
all blocks in the blockchain.

The user specifies how much space to allot for block & undo files. The minimum 
allowed is 550MB. Note that this is in addition to whatever is required for the 
block index and UTXO databases. The minimum was chosen so that Mincoin Core will 
be able to maintain at least 288 blocks on disk (two days worth of blocks at 10 
minutes per block). In rare instances it is possible that the amount of space 
used will exceed the pruning target in order to keep the required last 288 
blocks on disk.

Block pruning works during initial sync in the same way as during steady state, 
by deleting block files "as you go" whenever disk space is allocated. Thus, if 
the user specifies 550MB, once that level is reached the program will begin 
deleting the oldest block and undo files, while continuing to download the 
blockchain.

For now, block pruning disables block relay.  In the future, nodes with block 
pruning will at a minimum relay "new" blocks, meaning blocks that extend their 
active chain. 

Block pruning is currently incompatible with running a wallet due to the fact 
that block data is used for rescanning the wallet and importing keys or 
addresses (which require a rescan.) However, running the wallet with block 
pruning will be supported in the near future, subject to those limitations.

Block pruning is also incompatible with -txindex and will automatically disable 
it.

Once you have pruned blocks, going back to unpruned state requires 
re-downloading the entire blockchain. To do this, re-start the node with 
-reindex. Note also that any problem that would cause a user to reindex (e.g., 
disk corruption) will cause a pruned node to redownload the entire blockchain. 
Finally, note that when a pruned node reindexes, it will delete any blk???.dat 
and rev???.dat files in the data directory prior to restarting the download.

To enable block pruning on the command line:

- `-prune=N`: where N is the number of MB to allot for raw block & undo data.

Modified RPC calls:

- `getblockchaininfo` now includes whether we are in pruned mode or not.
- `getblock` will check if the block's data has been pruned and if so, return an 
error.
- `getrawtransaction` will no longer be able to locate a transaction that has a 
UTXO but where its block file has been pruned. 

Pruning is disabled by default.


Big endian support
------------------

Experimental support for big-endian CPU architectures was added in this
release. All little-endian specific code was replaced with endian-neutral
constructs. This has been tested on at least MIPS and PPC hosts. The build
system will automatically detect the endianness of the target.


Memory usage optimization
-------------------------

There have been many changes in this release to reduce the default memory usage
of a node, among which:

- Accurate UTXO cache size accounting (#6102); this makes the option `-dbcache`
  precise where this grossly underestimated memory usage before
- Reduce size of per-peer data structure (#6064 and others); this increases the
  number of connections that can be supported with the same amount of memory
- Reduce the number of threads (#5964, #5679); lowers the amount of (esp.
  virtual) memory needed


Fee estimation changes
----------------------

This release improves the algorithm used for fee estimation.  Previously, -1
was returned when there was insufficient data to give an estimate.  Now, -1
will also be returned when there is no fee or priority high enough for the
desired confirmation target. In those cases, it can help to ask for an estimate
for a higher target number of blocks. It is not uncommon for there to be no
fee or priority high enough to be reliably (85%) included in the next block and
for this reason, the default for `-txconfirmtarget=n` has changed from 1 to 2.


Privacy: Disable wallet transaction broadcast
---------------------------------------------

This release adds an option `-walletbroadcast=0` to prevent automatic
transaction broadcast and rebroadcast (#5951). This option allows separating
transaction submission from the node functionality.

Making use of this, third-party scripts can be written to take care of
transaction (re)broadcast:

- Send the transaction as normal, either through RPC or the GUI
- Retrieve the transaction data through RPC using `gettransaction` (NOT
  `getrawtransaction`). The `hex` field of the result will contain the raw
  hexadecimal representation of the transaction
- The transaction can then be broadcasted through arbitrary mechanisms
  supported by the script

One such application is selective Tor usage, where the node runs on the normal
internet but transactions are broadcasted over Tor.

For an example script see [bitcoin-submittx](https://github.com/laanwj/bitcoin-submittx).


Privacy: Stream isolation for Tor
---------------------------------

This release adds functionality to create a new circuit for every peer
connection, when the software is used with Tor. The new option,
`-proxyrandomize`, is on by default.

When enabled, every outgoing connection will (potentially) go through a
different exit node. That significantly reduces the chance to get unlucky and
pick a single exit node that is either malicious, or widely banned from the P2P
network. This improves connection reliability as well as privacy, especially
for the initial connections.

**Important note:** If a non-Tor SOCKS5 proxy is configured that supports
authentication, but doesn't require it, this change may cause that proxy to reject
connections. A user and password is sent where they weren't before. This setup
is exceedingly rare, but in this case `-proxyrandomize=0` can be passed to
disable the behavior.


Fix buffer overflow in bundled upnp
-----------------------------------

Bundled miniupnpc was updated to 1.9.20151008. This fixes a buffer overflow in
the XML parser during initial network discovery.

Details can be found here: http://talosintel.com/reports/TALOS-2015-0035/

This applies to the distributed executables only, not when building from source or
using distribution provided packages.

Additionally, upnp has been disabled by default. This may result in a lower
number of reachable nodes on IPv4, however this prevents future libupnpc
vulnerabilities from being a structural risk to the network
(see https://github.com/bitcoin/bitcoin/pull/6795).


Test for LowS signatures before relaying
----------------------------------------

Make the node require the canonical 'low-s' encoding for ECDSA signatures when
relaying or mining.  This removes a nuisance malleability vector.

Consensus behavior is unchanged.

If widely deployed this change would eliminate the last remaining known vector
for nuisance malleability on SIGHASH_ALL P2PKH transactions. On the down-side
it will block most transactions made by sufficiently out of date software.

Unlike the other avenues to change txids on transactions this
one was randomly violated by all deployed mincoin software prior to
its discovery. So, while other malleability vectors where made
non-standard as soon as they were discovered, this one has remained
permitted. Even BIP62 did not propose applying this rule to
old version transactions, but conforming implementations have become
much more common since BIP62 was initially written.

Mincoin Core has produced compatible signatures since a28fb70e in
September 2013, but this didn't make it into a release until 0.9
in March 2014; Bitcoinj has done so for a similar span of time.
Bitcoinjs and electrum have been more recently updated.

This does not replace the need for BIP62 or similar, as miners can
still cooperate to break transactions.  Nor does it replace the
need for wallet software to handle malleability sanely[1]. This
only eliminates the cheap and irritating DOS attack.

[1] On the Malleability of Bitcoin Transactions
Marcin Andrychowicz, Stefan Dziembowski, Daniel Malinowski, Łukasz Mazurek
http://fc15.ifca.ai/preproceedings/bitcoin/paper_9.pdf


Minimum relay fee default increase
-----------------------------------

The default for the `-minrelaytxfee` setting has been increased from `0.00001`
to `0.00005`.

This is necessitated by the current transaction flooding, causing
outrageous memory usage on nodes due to the mempool ballooning. This is a
temporary measure, bridging the time until a dynamic method for determining
this fee is merged (which will be in 0.12).

(see https://github.com/bitcoin/bitcoin/pull/6793, as well as the 0.11
release notes, in which this value was suggested)


BIP65 soft fork to enforce OP_CHECKLOCKTIMEVERIFY opcode
--------------------------------------------------------

This release includes several changes related to the [BIP65][] soft fork
which redefines the existing OP_NOP2 opcode as OP_CHECKLOCKTIMEVERIFY
(CLTV) so that a transaction output can be made unspendable until a
specified point in the future.

1. This release will only relay and mine transactions spending a CLTV
   output if they comply with the BIP65 rules as provided in code.

2. This release will produce version 4 blocks by default. Please see the
   *notice to miners* below.

3. Once 951 out of a sequence of 1,001 blocks on the local node's best block
   chain contain version 4 (or higher) blocks, this release will no
   longer accept new version 3 blocks and it will only accept version 4
   blocks if they comply with the BIP65 rules for CLTV.

For more information about the soft-forking change, please see
<https://github.com/bitcoin/bitcoin/pull/6351>

Graphs showing the progress towards block version 4 adoption may be
found at the URLs below:

- Block versions over the last 50,000 blocks as progress towards BIP65
  consensus enforcement: <http://bitcoin.sipa.be/ver-50k.png>

- Block versions over the last 2,000 blocks showing the days to the
  earliest possible BIP65 consensus-enforced block: <http://bitcoin.sipa.be/ver-2k.png>

**Notice to miners:** Mincoin Core’s block templates are now for
version 4 blocks only, and any mining software relying on its
getblocktemplate must be updated in parallel to use libblkmaker either
version 0.4.3 or any version from 0.5.2 onward.

- If you are solo mining, this will affect you the moment you upgrade
  Mincoin Core, which must be done prior to BIP65 achieving its 951/1001
  status.

- If you are mining with the stratum mining protocol: this does not
  affect you.

- If you are mining with the getblocktemplate protocol to a pool: this
  will affect you at the pool operator’s discretion, which must be no
  later than BIP65 achieving its 951/1001 status.

[BIP65]: https://github.com/bitcoin/bips/blob/master/bip-0065.mediawiki


BIP113 mempool-only locktime enforcement using GetMedianTimePast()
------------------------------------------------------------------

Mincoin transactions currently may specify a locktime indicating when
they may be added to a valid block.  Current consensus rules require
that blocks have a block header time greater than the locktime specified
in any transaction in that block.

Miners get to choose what time they use for their header time, with the
consensus rule being that no node will accept a block whose time is more
than two hours in the future.  This creates a incentive for miners to
set their header times to future values in order to include locktimed
transactions which weren't supposed to be included for up to two more
hours.

The consensus rules also specify that valid blocks may have a header
time greater than that of the median of the 11 previous blocks.  This
GetMedianTimePast() time has a key feature we generally associate with
time: it can't go backwards.

[BIP113][] specifies a soft fork (**not enforced in this release**) that
weakens this perverse incentive for individual miners to use a future
time by requiring that valid blocks have a computed GetMedianTimePast()
greater than the locktime specified in any transaction in that block.

Mempool inclusion rules currently require transactions to be valid for
immediate inclusion in a block in order to be accepted into the mempool.
This release begins applying the BIP113 rule to received transactions,
so transaction whose time is greater than the GetMedianTimePast() will
no longer be accepted into the mempool.

**Implication for miners:** you will begin rejecting transactions that
would not be valid under BIP113, which will prevent you from producing
invalid blocks if/when BIP113 is enforced on the network. Any
transactions which are valid under the current rules but not yet valid
under the BIP113 rules will either be mined by other miners or delayed
until they are valid under BIP113. Note, however, that time-based
locktime transactions are more or less unseen on the network currently.

**Implication for users:** GetMedianTimePast() always trails behind the
current time, so a transaction locktime set to the present time will be
rejected by nodes running this release until the median time moves
forward. To compensate, subtract one hour (3,600 seconds) from your
locktimes to allow those transactions to be included in mempools at
approximately the expected time.

[BIP113]: https://github.com/bitcoin/bips/blob/master/bip-0113.mediawiki


Windows bug fix for corrupted UTXO database on unclean shutdowns
----------------------------------------------------------------

Several Windows users reported that they often need to reindex the
entire blockchain after an unclean shutdown of Mincoin Core on Windows
(or an unclean shutdown of Windows itself). Although unclean shutdowns
remain unsafe, this release no longer relies on memory-mapped files for
the UTXO database, which significantly reduced the frequency of unclean
shutdowns leading to required reindexes during testing.

For more information, see: <https://github.com/bitcoin/bitcoin/pull/6917>

Other fixes for database corruption on Windows are expected in the
next major release.


Signature validation using libsecp256k1
---------------------------------------

ECDSA signatures inside Mincoin transactions now use validation using
[libsecp256k1](https://github.com/bitcoin-core/secp256k1) instead of OpenSSL.

Depending on the platform, this means a significant speedup for raw signature
validation speed. The advantage is largest on x86_64, where validation is over
five times faster. In practice, this translates to a raw reindexing and new
block validation times that are less than half of what it was before.

Libsecp256k1 has undergone very extensive testing and validation.

A side effect of this change is that libconsensus no longer depends on OpenSSL.


Reduce upload traffic
---------------------

A major part of the outbound traffic is caused by serving historic blocks to
other nodes in initial block download state.

It is now possible to reduce the total upload traffic via the `-maxuploadtarget`
parameter. This is *not* a hard limit but a threshold to minimize the outbound
traffic. When the limit is about to be reached, the uploaded data is cut by not
serving historic blocks (blocks older than one week).
Moreover, any SPV peer is disconnected when they request a filtered block.

This option can be specified in MiB per day and is turned off by default
(`-maxuploadtarget=0`).
The recommended minimum is 144 * MAX_BLOCK_SIZE (currently 144MB) per day.

Whitelisted peers will never be disconnected, although their traffic counts for
calculating the target.

A more detailed documentation about keeping traffic low can be found in
[/doc/reduce-traffic.md](/doc/reduce-traffic.md).

Direct headers announcement (BIP 130)
-------------------------------------

Between compatible peers, [BIP 130]
(https://github.com/bitcoin/bips/blob/master/bip-0130.mediawiki)
direct headers announcement is used. This means that blocks are advertised by
announcing their headers directly, instead of just announcing the hash. In a
reorganization, all new headers are sent, instead of just the new tip. This
can often prevent an extra roundtrip before the actual block is downloaded.


Memory pool limiting
--------------------

Previous versions of Mincoin Core had their mempool limited by checking
a transaction's fees against the node's minimum relay fee. There was no
upper bound on the size of the mempool and attackers could send a large
number of transactions paying just slighly more than the default minimum
relay fee to crash nodes with relatively low RAM. A temporary workaround
for previous versions of Mincoin Core was to raise the default minimum
relay fee.

Mincoin Core 0.12 will have a strict maximum size on the mempool. The
default value is 300 MB and can be configured with the `-maxmempool`
parameter. Whenever a transaction would cause the mempool to exceed
its maximum size, the transaction that (along with in-mempool descendants) has
the lowest total feerate (as a package) will be evicted and the node's effective
minimum relay feerate will be increased to match this feerate plus the initial
minimum relay feerate. The initial minimum relay feerate is set to
1000 satoshis per kB.

Mincoin Core 0.12 also introduces new default policy limits on the length and
size of unconfirmed transaction chains that are allowed in the mempool
(generally limiting the length of unconfirmed chains to 25 transactions, with a
total size of 101 KB).  These limits can be overriden using command line
arguments; see the extended help (`--help -help-debug`) for more information.


Opt-in Replace-by-fee transactions
----------------------------------

It is now possible to replace transactions in the transaction memory pool of
Mincoin Core 0.12 nodes. Mincoin Core will only allow replacement of
transactions which have any of their inputs' `nSequence` number set to less
than `0xffffffff - 1`.  Moreover, a replacement transaction may only be
accepted when it pays sufficient fee, as described in [BIP 125]
(https://github.com/bitcoin/bips/blob/master/bip-0125.mediawiki).

Transaction replacement can be disabled with a new command line option,
`-mempoolreplacement=0`.  Transactions signaling replacement under BIP125 will
still be allowed into the mempool in this configuration, but replacements will
be rejected.  This option is intended for miners who want to continue the
transaction selection behavior of previous releases.

The `-mempoolreplacement` option is *not recommended* for wallet users seeking
to avoid receipt of unconfirmed opt-in transactions, because this option does
not prevent transactions which are replaceable under BIP 125 from being accepted
(only subsequent replacements, which other nodes on the network that implement
BIP 125 are likely to relay and mine).  Wallet users wishing to detect whether
a transaction is subject to replacement under BIP 125 should instead use the
updated RPC calls `gettransaction` and `listtransactions`, which now have an
additional field in the output indicating if a transaction is replaceable under
BIP125 ("bip125-replaceable").

Note that the wallet in Mincoin Core 0.12 does not yet have support for
creating transactions that would be replaceable under BIP 125.


RPC: Random-cookie RPC authentication
-------------------------------------

When no `-rpcpassword` is specified, the daemon now uses a special 'cookie'
file for authentication. This file is generated with random content when the
daemon starts, and deleted when it exits. Its contents are used as
authentication token. Read access to this file controls who can access through
RPC. By default it is stored in the data directory but its location can be
overridden with the option `-rpccookiefile`.

This is similar to Tor's CookieAuthentication: see
https://www.torproject.org/docs/tor-manual.html.en

This allows running mincoind without having to do any manual configuration.

Relay: Any sequence of pushdatas in OP_RETURN outputs now allowed
-----------------------------------------------------------------

Previously OP_RETURN outputs with a payload were only relayed and mined if they
had a single pushdata. This restriction has been lifted to allow any
combination of data pushes and numeric constant opcodes (OP_1 to OP_16) after
the OP_RETURN. The limit on OP_RETURN output size is now applied to the entire
serialized scriptPubKey, 83 bytes by default. (the previous 80 byte default plus
three bytes overhead)


Relay: New and only new blocks relayed when pruning
---------------------------------------------------

When running in pruned mode, the client will now relay new blocks. When
responding to the `getblocks` message, only hashes of blocks that are on disk
and are likely to remain there for some reasonable time window (1 hour) will be
returned (previously all relevant hashes were returned).


Relay and Mining: Priority transactions
---------------------------------------

Mincoin Core has a heuristic 'priority' based on coin value and age. This
calculation is used for relaying of transactions which do not pay the
minimum relay fee, and can be used as an alternative way of sorting
transactions for mined blocks. Mincoin Core will relay transactions with
insufficient fees depending on the setting of `-limitfreerelay=<r>` (default:
`r=15` kB per minute) and `-blockprioritysize=<s>`.

In Mincoin Core 0.12, when mempool limit has been reached a higher minimum
relay fee takes effect to limit memory usage. Transactions which do not meet
this higher effective minimum relay fee will not be relayed or mined even if
they rank highly according to the priority heuristic.

The mining of transactions based on their priority is also now disabled by
default. To re-enable it, simply set `-blockprioritysize=<n>` where is the size
in bytes of your blocks to reserve for these transactions. The old default was
50k, so to retain approximately the same policy, you would set
`-blockprioritysize=50000`.

Additionally, as a result of computational simplifications, the priority value
used for transactions received with unconfirmed inputs is lower than in prior
versions due to avoiding recomputing the amounts as input transactions confirm.

External miner policy set via the `prioritisetransaction` RPC to rank
transactions already in the mempool continues to work as it has previously.
Note, however, that if mining priority transactions is left disabled, the
priority delta will be ignored and only the fee metric will be effective.

This internal automatic prioritization handling is being considered for removal
entirely in Mincoin Core 0.13, and it is at this time undecided whether the
more accurate priority calculation for chained unconfirmed transactions will be
restored. Community direction on this topic is particularly requested to help
set project priorities.


Automatically use Tor hidden services
-------------------------------------

Starting with Tor version 0.2.7.1 it is possible, through Tor's control socket
API, to create and destroy 'ephemeral' hidden services programmatically.
Mincoin Core has been updated to make use of this.

This means that if Tor is running (and proper authorization is available),
Mincoin Core automatically creates a hidden service to listen on, without
manual configuration. Mincoin Core will also use Tor automatically to connect
to other .onion nodes if the control socket can be successfully opened. This
will positively affect the number of available .onion nodes and their usage.

This new feature is enabled by default if Mincoin Core is listening, and
a connection to Tor can be made. It can be configured with the `-listenonion`,
`-torcontrol` and `-torpassword` settings. To show verbose debugging
information, pass `-debug=tor`.


Notifications through ZMQ
-------------------------

Mincoind can now (optionally) asynchronously notify clients through a
ZMQ-based PUB socket of the arrival of new transactions and blocks.
This feature requires installation of the ZMQ C API library 4.x and
configuring its use through the command line or configuration file.
Please see [docs/zmq.md](/doc/zmq.md) for details of operation.


Wallet: Transaction fees
------------------------

Various improvements have been made to how the wallet calculates
transaction fees.

Users can decide to pay a predefined fee rate by setting `-paytxfee=<n>`
(or `settxfee <n>` rpc during runtime). A value of `n=0` signals Mincoin
Core to use floating fees. By default, Mincoin Core will use floating
fees.

Based on past transaction data, floating fees approximate the fees
required to get into the `m`th block from now. This is configurable
with `-txconfirmtarget=<m>` (default: `2`).

Sometimes, it is not possible to give good estimates, or an estimate
at all. Therefore, a fallback value can be set with `-fallbackfee=<f>`
(default: `0.0002` MNC/kB).

At all times, Mincoin Core will cap fees at `-maxtxfee=<x>` (default:
0.10) MNC.
Furthermore, Mincoin Core will never create transactions paying less than
the current minimum relay fee.
Finally, a user can set the minimum fee rate for all transactions with
`-mintxfee=<i>`, which defaults to 1000 satoshis per kB.


Wallet: Negative confirmations and conflict detection
-----------------------------------------------------

The wallet will now report a negative number for confirmations that indicates
how deep in the block chain the conflict is found. For example, if a transaction
A has 5 confirmations and spends the same input as a wallet transaction B, B
will be reported as having -5 confirmations. If another wallet transaction C
spends an output from B, it will also be reported as having -5 confirmations.
To detect conflicts with historical transactions in the chain a one-time
`-rescan` may be needed.

Unlike earlier versions, unconfirmed but non-conflicting transactions will never
get a negative confirmation count. They are not treated as spendable unless
they're coming from ourself (change) and accepted into our local mempool,
however. The new "trusted" field in the `listtransactions` RPC output
indicates whether outputs of an unconfirmed transaction are considered
spendable.


Wallet: Merkle branches removed
-------------------------------

Previously, every wallet transaction stored a Merkle branch to prove its
presence in blocks. This wasn't being used for more than an expensive
sanity check. Since 0.12, these are no longer stored. When loading a
0.12 wallet into an older version, it will automatically rescan to avoid
failed checks.


Wallet: Pruning
---------------

With 0.12 it is possible to use wallet functionality in pruned mode.
This can reduce the disk usage from currently around 60 GB to
around 2 GB.

However, rescans as well as the RPCs `importwallet`, `importaddress`,
`importprivkey` are disabled.

To enable block pruning set `prune=<N>` on the command line or in
`mincoin.conf`, where `N` is the number of MiB to allot for
raw block & undo data.

A value of 0 disables pruning. The minimal value above 0 is 550. Your
wallet is as secure with high values as it is with low ones. Higher
values merely ensure that your node will not shut down upon blockchain
reorganizations of more than 2 days - which are unlikely to happen in
practice. In future releases, a higher value may also help the network
as a whole: stored blocks could be served to other nodes.

For further information about pruning, you may also consult the [release
notes of v0.11.0](https://github.com/bitcoin/bitcoin/blob/v0.11.0/doc/release-notes.md#block-file-pruning).


`NODE_BLOOM` service bit
------------------------

Support for the `NODE_BLOOM` service bit, as described in [BIP
111](https://github.com/bitcoin/bips/blob/master/bip-0111.mediawiki), has been
added to the P2P protocol code.

BIP 111 defines a service bit to allow peers to advertise that they support
bloom filters (such as used by SPV clients) explicitly. It also bumps the protocol
version to allow peers to identify old nodes which allow bloom filtering of the
connection despite lacking the new service bit.

In this version, it is only enforced for peers that send protocol versions
`>=70011`. For the next major version it is planned that this restriction will be
removed. It is recommended to update SPV clients to check for the `NODE_BLOOM`
service bit for nodes that report versions newer than 70011.


Option parsing behavior
-----------------------

Command line options are now parsed strictly in the order in which they are
specified. It used to be the case that `-X -noX` ends up, unintuitively, with X
set, as `-X` had precedence over `-noX`. This is no longer the case. Like for
other software, the last specified value for an option will hold.


RPC: Low-level API changes
--------------------------

- Monetary amounts can be provided as strings. This means that for example the
  argument to sendtoaddress can be "0.0001" instead of 0.0001. This can be an
  advantage if a JSON library insists on using a lossy floating point type for
  numbers, which would be dangerous for monetary amounts.

* The `asm` property of each scriptSig now contains the decoded signature hash
  type for each signature that provides a valid defined hash type.

* OP_NOP2 has been renamed to OP_CHECKLOCKTIMEVERIFY by [BIP 65](https://github.com/bitcoin/bips/blob/master/bip-0065.mediawiki)

The following items contain assembly representations of scriptSig signatures
and are affected by this change:

- RPC `getrawtransaction`
- RPC `decoderawtransaction`
- RPC `decodescript`
- REST `/rest/tx/` (JSON format)
- REST `/rest/block/` (JSON format when including extended tx details)
- `mincoin-tx -json`

For example, the `scriptSig.asm` property of a transaction input that
previously showed an assembly representation of:

    304502207fa7a6d1e0ee81132a269ad84e68d695483745cde8b541e3bf630749894e342a022100c1f7ab20e13e22fb95281a870f3dcf38d782e53023ee313d741ad0cfbc0c509001 400000 OP_NOP2

now shows as:

    304502207fa7a6d1e0ee81132a269ad84e68d695483745cde8b541e3bf630749894e342a022100c1f7ab20e13e22fb95281a870f3dcf38d782e53023ee313d741ad0cfbc0c5090[ALL] 400000 OP_CHECKLOCKTIMEVERIFY

Note that the output of the RPC `decodescript` did not change because it is
configured specifically to process scriptPubKey and not scriptSig scripts.


RPC: SSL support dropped
------------------------

SSL support for RPC, previously enabled by the option `rpcssl` has been dropped
from both the client and the server. This was done in preparation for removing
the dependency on OpenSSL for the daemon completely.

Trying to use `rpcssl` will result in an error:

    Error: SSL mode for RPC (-rpcssl) is no longer supported.

If you are one of the few people that relies on this feature, a flexible
migration path is to use `stunnel`. This is an utility that can tunnel
arbitrary TCP connections inside SSL. On e.g. Ubuntu it can be installed with:

    sudo apt-get install stunnel4

Then, to tunnel a SSL connection on 29335 to a RPC server bound on localhost on port 19335 do:

    stunnel -d 29335 -r 127.0.0.1:19335 -p stunnel.pem -P ''

It can also be set up system-wide in inetd style.

Another way to re-attain SSL would be to setup a httpd reverse proxy. This solution
would allow the use of different authentication, loadbalancing, on-the-fly compression and
caching. A sample config for apache2 could look like:

    Listen 443

    NameVirtualHost *:443
    <VirtualHost *:443>

    SSLEngine On
    SSLCertificateFile /etc/apache2/ssl/server.crt
    SSLCertificateKeyFile /etc/apache2/ssl/server.key

    <Location /mincoinrpc>
        ProxyPass http://127.0.0.1:9335/
        ProxyPassReverse http://127.0.0.1:9335/
        # optional enable digest auth
        # AuthType Digest
        # ...

        # optional bypass mincoind rpc basic auth
        # RequestHeader set Authorization "Basic <hash>"
        # get the <hash> from the shell with: base64 <<< mincoinrpc:<password>
    </Location>

    # Or, balance the load:
    # ProxyPass / balancer://balancer_cluster_name

    </VirtualHost>


Mining Code Changes
-------------------

The mining code in 0.12 has been optimized to be significantly faster and use less
memory. As part of these changes, consensus critical calculations are cached on a
transaction's acceptance into the mempool and the mining code now relies on the
consistency of the mempool to assemble blocks. However all blocks are still tested
for validity after assembly.


Other P2P Changes
-----------------

The list of banned peers is now stored on disk rather than in memory.
Restarting mincoind will no longer clear out the list of banned peers; instead
a new RPC call (`clearbanned`) can be used to manually clear the list.  The new
`setban` RPC call can also be used to manually ban or unban a peer.


Database cache memory increased
--------------------------------

As a result of growth of the UTXO set, performance with the prior default
database cache of 100 MiB has suffered.
For this reason the default was changed to 300 MiB in this release.

For nodes on low-memory systems, the database cache can be changed back to
100 MiB (or to another value) by either:

- Adding `dbcache=100` in mincoin.conf
- Changing it in the GUI under `Options → Size of database cache`

Note that the database cache setting has the most performance impact
during initial sync of a node, and when catching up after downtime.


mincoin-cli: arguments privacy
------------------------------

The RPC command line client gained a new argument, `-stdin`
to read extra arguments from standard input, one per line until EOF/Ctrl-D.
For example:

    $ src/mincoin-cli -stdin walletpassphrase
    mysecretcode
    120
    ..... press Ctrl-D here to end input
    $

It is recommended to use this for sensitive information such as wallet
passphrases, as command-line arguments can usually be read from the process
table by any user on the system.


C++11 and Python 3
------------------

Various code modernizations have been done. The Mincoin Core code base has
started using C++11. This means that a C++11-capable compiler is now needed for
building. Effectively this means GCC 4.7 or higher, or Clang 3.3 or higher.

When cross-compiling for a target that doesn't have C++11 libraries, configure with
`./configure --enable-glibc-back-compat ... LDFLAGS=-static-libstdc++`.

For running the functional tests in `qa/rpc-tests`, Python3.4 or higher is now
required.


Linux ARM builds
----------------

Due to popular request, Linux ARM builds have been added to the uploaded
executables.

The following extra files can be found in the download directory or torrent:

- `mincoin-${VERSION}-arm-linux-gnueabihf.tar.gz`: Linux binaries for the most
  common 32-bit ARM architecture.
- `mincoin-${VERSION}-aarch64-linux-gnu.tar.gz`: Linux binaries for the most
  common 64-bit ARM architecture.

ARM builds are still experimental. If you have problems on a certain device or
Linux distribution combination please report them on the bug tracker, it may be
possible to resolve them.

Note that Android is not considered ARM Linux in this context. The executables
are not expected to work out of the box on Android.


Compact Block support (BIP 152)
-------------------------------

Support for block relay using the Compact Blocks protocol has been implemented
in PR 8068.

The primary goal is reducing the bandwidth spikes at relay time, though in many
cases it also reduces propagation delay. It is automatically enabled between
compatible peers.
[BIP 152](https://github.com/bitcoin/bips/blob/master/bip-0152.mediawiki)

As a side-effect, ordinary non-mining nodes will download and upload blocks
faster if those blocks were produced by miners using similar transaction
filtering policies. This means that a miner who produces a block with many
transactions discouraged by your node will be relayed slower than one with
only transactions already in your memory pool. The overall effect of such
relay differences on the network may result in blocks which include widely-
discouraged transactions losing a stale block race, and therefore miners may
wish to configure their node to take common relay policies into consideration.


Hierarchical Deterministic Key Generation
-----------------------------------------
Newly created wallets will use hierarchical deterministic key generation
according to BIP32 (keypath m/0'/0'/k').
Existing wallets will still use traditional key generation.

Backups of HD wallets, regardless of when they have been created, can
therefore be used to re-generate all possible private keys, even the
ones which haven't already been generated during the time of the backup.
**Attention:** Encrypting the wallet will create a new seed which requires
a new backup!

Wallet dumps (created using the `dumpwallet` RPC) will contain the deterministic
seed. This is expected to allow future versions to import the seed and all
associated funds, but this is not yet implemented.

HD key generation for new wallets can be disabled by `-usehd=0`. Keep in
mind that this flag only has affect on newly created wallets.
You can't disable HD key generation once you have created a HD wallet.

There is no distinction between internal (change) and external keys.

HD wallets are incompatible with older versions of Mincoin Core.

[Pull request](https://github.com/bitcoin/bitcoin/pull/8035/files), [BIP 32](https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki)


Segregated Witness
------------------

The code preparations for Segregated Witness ("segwit"), as described in [BIP
141](https://github.com/bitcoin/bips/blob/master/bip-0141.mediawiki), [BIP
143](https://github.com/bitcoin/bips/blob/master/bip-0143.mediawiki), [BIP
144](https://github.com/bitcoin/bips/blob/master/bip-0144.mediawiki), and [BIP
145](https://github.com/bitcoin/bips/blob/master/bip-0145.mediawiki) are
finished and included in this release.  However, BIP 141 does not yet specify
activation parameters on mainnet, and so this release does not support segwit
use on mainnet.  Testnet use is supported, and after BIP 141 is updated with
proposed parameters, a future release of Mincoin Core is expected that
implements those parameters for mainnet.

Furthermore, because segwit activation is not yet specified for mainnet,
version 0.13.0 will behave similarly as other pre-segwit releases even after a
future activation of BIP 141 on the network.  Upgrading from 0.13.0 will be
required in order to utilize segwit-related features on mainnet (such as signal
BIP 141 activation, mine segwit blocks, fully validate segwit blocks, relay
segwit blocks to other segwit nodes, and use segwit transactions in the
wallet, etc).


Mining transaction selection ("Child Pays For Parent")
------------------------------------------------------

The mining transaction selection algorithm has been replaced with an algorithm
that selects transactions based on their feerate inclusive of unconfirmed
ancestor transactions.  This means that a low-fee transaction can become more
likely to be selected if a high-fee transaction that spends its outputs is
relayed.

With this change, the `-blockminsize` command line option has been removed.

The command line option `-blockmaxsize` remains an option to specify the
maximum number of serialized bytes in a generated block.  In addition, the new
command line option `-blockmaxweight` has been added, which specifies the
maximum "block weight" of a generated block, as defined by [BIP 141 (Segregated
Witness)] (https://github.com/bitcoin/bips/blob/master/bip-0141.mediawiki).

In preparation for Segregated Witness, the mining algorithm has been modified
to optimize transaction selection for a given block weight, rather than a given
number of serialized bytes in a block.  In this release, transaction selection
is unaffected by this distinction (as BIP 141 activation is not supported on
mainnet in this release, see above), but in future releases and after BIP 141
activation, these calculations would be expected to differ.

For optimal runtime performance, miners using this release should specify
`-blockmaxweight` on the command line, and not specify `-blockmaxsize`.
Additionally (or only) specifying `-blockmaxsize`, or relying on default
settings for both, may result in performance degradation, as the logic to
support `-blockmaxsize` performs additional computation to ensure that
constraint is met.  (Note that for mainnet, in this release, the equivalent
parameter for `-blockmaxweight` would be four times the desired
`-blockmaxsize`.  See [BIP 141]
(https://github.com/bitcoin/bips/blob/master/bip-0141.mediawiki) for additional
details.)

In the future, the `-blockmaxsize` option may be removed, as block creation is
no longer optimized for this metric.  Feedback is requested on whether to
deprecate or keep this command line option in future releases.


Reindexing changes
------------------

In earlier versions, reindexing did validation while reading through the block
files on disk. These two have now been split up, so that all blocks are known
before validation starts. This was necessary to make certain optimizations that
are available during normal synchronizations also available during reindexing.

The two phases are distinct in the Mincoin-Qt GUI. During the first one,
"Reindexing blocks on disk" is shown. During the second (slower) one,
"Processing blocks on disk" is shown.

It is possible to only redo validation now, without rebuilding the block index,
using the command line option `-reindex-chainstate` (in addition to
`-reindex` which does both). This new option is useful when the blocks on disk
are assumed to be fine, but the chainstate is still corrupted. It is also
useful for benchmarks.


Removal of internal miner
--------------------------

As CPU mining has been useless for a long time, the internal miner has been
removed in this release, and replaced with a simpler implementation for the
test framework.

The overall result of this is that `setgenerate` RPC call has been removed, as
well as the `-gen` and `-genproclimit` command-line options.

For testing, the `generate` call can still be used to mine a block, and a new
RPC call `generatetoaddress` has been added to mine to a specific address. This
works with wallet disabled.


New bytespersigop implementation
--------------------------------

The former implementation of the bytespersigop filter accidentally broke bare
multisig (which is meant to be controlled by the `permitbaremultisig` option),
since the consensus protocol always counts these older transaction forms as 20
sigops for backwards compatibility. Simply fixing this bug by counting more
accurately would have reintroduced a vulnerability. It has therefore been
replaced with a new implementation that rather than filter such transactions,
instead treats them (for fee purposes only) as if they were in fact the size
of a transaction actually using all 20 sigops.


Low-level P2P changes
----------------------

- The optional new p2p message "feefilter" is implemented and the protocol
  version is bumped to 70013. Upon receiving a feefilter message from a peer,
  a node will not send invs for any transactions which do not meet the filter
  feerate. [BIP 133](https://github.com/bitcoin/bips/blob/master/bip-0133.mediawiki)

- The P2P alert system has been removed in PR #7692 and the `alert` P2P message
  is no longer supported.

- The transaction relay mechanism used to relay one quarter of all transactions
  instantly, while queueing up the rest and sending them out in batch. As
  this resulted in chains of dependent transactions being reordered, it
  systematically hurt transaction relay. The relay code was redesigned in PRs
  \#7840 and #8082, and now always batches transactions announcements while also
  sorting them according to dependency order. This significantly reduces orphan
  transactions. To compensate for the removal of instant relay, the frequency of
  batch sending was doubled for outgoing peers.

- Since PR #7840 the BIP35 `mempool` command is also subject to batch processing.
  Also the `mempool` message is no longer handled for non-whitelisted peers when
  `NODE_BLOOM` is disabled through `-peerbloomfilters=0`.

- The maximum size of orphan transactions that are kept in memory until their
  ancestors arrive has been raised in PR #8179 from 5000 to 99999 bytes. They
  are now also removed from memory when they are included in a block, conflict
  with a block, and time out after 20 minutes.

- We respond at most once to a getaddr request during the lifetime of a
  connection since PR #7856.

- Connections to peers who have recently been the first one to give us a valid
  new block or transaction are protected from disconnections since PR #8084.


Low-level RPC changes
----------------------

- RPC calls have been added to output detailed statistics for individual mempool
  entries, as well as to calculate the in-mempool ancestors or descendants of a
  transaction: see `getmempoolentry`, `getmempoolancestors`, `getmempooldescendants`.

- `gettxoutsetinfo` UTXO hash (`hash_serialized`) has changed. There was a divergence between
  32-bit and 64-bit platforms, and the txids were missing in the hashed data. This has been
  fixed, but this means that the output will be different than from previous versions.

- Full UTF-8 support in the RPC API. Non-ASCII characters in, for example,
  wallet labels have always been malformed because they weren't taken into account
  properly in JSON RPC processing. This is no longer the case. This also affects
  the GUI debug console.

- Asm script outputs replacements for OP_NOP2 and OP_NOP3

  - OP_NOP2 has been renamed to OP_CHECKLOCKTIMEVERIFY by [BIP 
65](https://github.com/bitcoin/bips/blob/master/bip-0065.mediawiki)

  - OP_NOP3 has been renamed to OP_CHECKSEQUENCEVERIFY by [BIP 
112](https://github.com/bitcoin/bips/blob/master/bip-0112.mediawiki)

  - The following outputs are affected by this change:

    - RPC `getrawtransaction` (in verbose mode)
    - RPC `decoderawtransaction`
    - RPC `decodescript`
    - REST `/rest/tx/` (JSON format)
    - REST `/rest/block/` (JSON format when including extended tx details)
    - `mincoin-tx -json`

- The sorting of the output of the `getrawmempool` output has changed.

- New RPC commands: `generatetoaddress`, `importprunedfunds`, `removeprunedfunds`, `signmessagewithprivkey`,
  `getmempoolancestors`, `getmempooldescendants`, `getmempoolentry`,
  `createwitnessaddress`, `addwitnessaddress`.

- Removed RPC commands: `setgenerate`, `getgenerate`.

- New options were added to `fundrawtransaction`: `includeWatching`, `changeAddress`, `changePosition` and `feeRate`.


Low-level ZMQ changes
----------------------

- Each ZMQ notification now contains an up-counting sequence number that allows
  listeners to detect lost notifications.
  The sequence number is always the last element in a multi-part ZMQ notification and
  therefore backward compatible. Each message type has its own counter.
  PR [#7762](https://github.com/bitcoin/bitcoin/pull/7762).
