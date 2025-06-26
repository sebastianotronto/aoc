#!/bin/sh

usage() {
	echo "Usage: $0 day part"
	echo "Example: $0 07 b"
}

[ -n "$1" ] && [ -n "$2" ] || (usage; exit 1)
[ -d "$1" ]  || (echo "Directory $1 does not exist"; exit 1)
[ -f "$1/$2.rs" ] || (echo "File $1/$2.rs does not exist"; exit 2)

rustc "$1/$2.rs" -o "$1/$2.out" && time "./$1/$2.out"
