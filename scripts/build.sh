#!/bin/bash
# ビルドスクリプト
clear
set -e
cd "$(dirname "$0")/.."
cmake -S . -B build
cmake --build build
