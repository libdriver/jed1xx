[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver JED1XX

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/jed1xx/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

デジタルガスセンサーは、低電力で小型化されたセンサーです。半導体ガスセンサーと高性能マイクロプロセッサを組み合わせて、環境内のガス濃度を検出します。高感度、コンパクト、高精度、I2Cデジタル信号出力方式を採用しており、ユーザーの使用とデバッグに便利で、ユーザーの設計開発サイクルを大幅に短縮します。環境安全、ポータブル機器など、多くの分野で幅広く応用できます。

LibDriver JED1XX は、LibDriver によって起動される JED1XX のフル機能ドライバーです。温度と相対湿度を読み取る機能を提供します。 LibDriver は MISRA 準拠です。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver JED1XXのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver JED1XX用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver JED1XXドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver JED1XXプログラミング例が含まれています。

/ docディレクトリには、LibDriver JED1XXオフラインドキュメントが含まれています。

/ datasheetディレクトリには、JED1XXデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

```C
#include "driver_jed1xx_basic.h"

uint8_t res;
uint32_t i;
float ppm;

/* basic init */
res = jed1xx_basic_init(JED1XX_TYPE_101_VOC);
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 3000ms */
    jed1xx_interface_delay_ms(3000);

    /* read data */
    res = jed1xx_basic_read(&ppm);
    if (res != 0)
    {
        (void)jed1xx_basic_deinit();

        return 1;
    }

    /* output */
    jed1xx_interface_debug_print("jed1xx: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
    jed1xx_interface_debug_print("jed1xx: output is %0.1fppm.\n", ppm);
    
    ...
}

...
    
/* deinit */
(void)jed1xx_basic_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/jed1xx/index.html](https://www.libdriver.com/docs/jed1xx/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。