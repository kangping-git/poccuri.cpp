# poccuri.cpp
## 概要
なんか機械学習について勉強したくなったから書いてる。速度は今は気にしない。書きたいから書く。それだけ～～～
## TODO
- Matrix
- BP法の実装
- Webで自動でコード生成とか
- WebAssemblyでWeb上での学習もあり
- Webサーバ自動で立ててGUIで学習を管理できたり
- CUDA使ったり
どうでしょうか。目標高く持ちすぎですね。はい
## 独自の保存ファイル形式を考える
.pcrb
MAGIC NUMBER 37 3d 64 71
変数保存用。
変数の種類を二つ目に
VARIABLE KIND
01 ... FloatVariable
02 ... VectorVariable
03 ... MatrixVariable
次に、サイズ。FloatVariableは0 bytes, VectorVariableは4 bytes, MatrixVariableは8 bytes.

## LICENSE
MITライセンスです。煮るなり焼くなりどうにでも使ってください。