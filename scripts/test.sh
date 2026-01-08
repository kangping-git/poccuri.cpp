#!/bin/bash
# テスト実行スクリプト
set -e
cd "$(dirname "$0")/../build"
ctest --output-on-failure
