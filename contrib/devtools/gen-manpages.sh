#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

MINCOIND=${MINCOIND:-$SRCDIR/mincoind}
MINCOINCLI=${MINCOINCLI:-$SRCDIR/mincoin-cli}
MINCOINTX=${MINCOINTX:-$SRCDIR/mincoin-tx}
MINCOINQT=${MINCOINQT:-$SRCDIR/qt/mincoin-qt}

[ ! -x $MINCOIND ] && echo "$MINCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
MNCVER=($($MINCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for mincoind if --version-string is not set,
# but has different outcomes for mincoin-qt and mincoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$MINCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $MINCOIND $MINCOINCLI $MINCOINTX $MINCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${MNCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${MNCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
