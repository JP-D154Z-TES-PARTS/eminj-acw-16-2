# サブタスク2: l_mat.cと仕様書の対応関係マッピング

## ファイル概要
- ファイル名: eminj_l_mat.c
- 行数: 約4961行
- 目的: 噴射要求調停処理のロジック実装

## 主要セクション構造

### 1. ヘッダインクルード部（行1-50付近）
```c
#include <../inc/common.h>
#include <../inc/gllib.h>
#include <engsrc/espc/ejcc.h>
#include <engsrc/inc/elsb.h>
#include <engsrc/inc/elib.h>
#include <engsrc/eactmedi/einj/eminj.h>
```

### 2. コンパイルスイッチチェック部
各種機能フラグ（JEEFI、JESS、JEEGR等）の定義確認

### 3. 型定義部
- st_EMINJ_PWON_LOGIC_t: 初期化用構造体
- 各種内部データ構造

### 4. 関数プロトタイプ宣言部
静的関数の前方宣言

### 5. グローバル変数定義部
- stg_eminj_einj: 噴射情報構造体
- 各種配列データ

### 6. 初期化関数（vdg_eminj_pwon）
パワーON時の初期化処理

### 7. メイン処理関数（vdg_eminj_8msm）
8ms周期で実行される噴射要求調停処理
- 優先度判定
- 要求データの調停
- 出力データの生成

### 8. データ取得関数群
- vdg_eminj_einj_dataget()
- vdg_eminj_eminj_dataget()

## 仕様書との対応関係

### ロジック変更シート対応
- 噴射モード設定ロジック
- 噴射量計算ロジック
- 噴射タイミング制御ロジック

### 定数管理エクセル対応
- 優先度定数（u1g_eminj_XXX_PRI）
- ID定数（u1g_EMINJ_XXX_ID）
- マクロ定数（u4g_EMINJ_RQxxx）

### 参照元/参照先チェックシート対応
- 外部モジュールからの参照（vdg_xxxxx_emedi_dataget）
- 外部モジュールへの提供（stg_eminj_einj等）

## コード変更時の注意点
1. CP932エンコーディングの維持
2. コンパイルスイッチ条件の整合性
3. 優先度テーブルの一貫性
4. データ構造のメモリアライメント
