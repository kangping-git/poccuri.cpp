#!/bin/bash
# 実行バイナリを起動するスクリプト
set -e
cd "$(dirname "$0")/../build"
./PoccuriCpp "$@"
