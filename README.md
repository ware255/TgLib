# TgLib
TelegramBotを簡単に作成するためのライブラリ

## 概要
ライブラリと言ってもコンパイルして実行すればわかると思いますが、ただのオウム返しボットです。<br>
うまく改造できるかはあなた次第。<br>

ちなみに作った理由ですが、いくらGitHub漁ってもOpenSSLが必要だったりBoost Libraryが必要だったりまぁWindowsで環境構築するのがめんどくさいからです。<br>
TelegramをGETしたときにjson形式で帰ってくるのでjsoncppを導入しないとこっちの負担がえぐくなる（）<br>

**まぁ俺の優しさに感謝しやがれ**

## プラットフォーム
Windows 10 以降

## 依存関係
* Jsoncpp
* Win32API

Jsoncppがまだ入っていない場合はこの動画を見るといいかもしれないです。<br>
[jsoncpp setup Windows](https://youtu.be/GkiQZElKSY4) <br>

Win32APIは基本的にwinhttp.hしか使わないです。

## コンパイル
※gccが入っているかつOSがWindows10を前提としています。
```
> g++ main.cpp -o test.exe -I (include path to jsoncpp) -L (lib path to jsoncpp) -ljsoncpp -lwinhttp -Wall
```
