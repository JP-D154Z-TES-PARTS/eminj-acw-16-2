# データ構造対応表

## 主要データ構造の定義と対応関係

### 1. 調停テーブル構造体

#### st_EMINJ_EMINJ_TBL（旧構造体用）
**定義箇所:** eminj_l_mat.c 行343-347

```c
typedef struct
{
    void (* pt_dataget)( st_EMINJ_EMINJ_DEF * ptt_store );
    u1 u1_id;  // lsb=1 :ID
} st_EMINJ_EMINJ_TBL;
```

**メンバー:**
- `pt_dataget` : 各機能のデータ取得関数ポインタ
- `u1_id` : 機能識別ID

**仕様書対応:**
- セクションB「各機能毎に複数のIDと優先度を付与」に対応
- 調停テーブルによる機能管理の実装

---

#### st_EMINJ_EMINJ_TBL2（新構造体用）
**定義箇所:** eminj_l_mat.c 行349-353

```c
typedef struct
{
    void (* pt_dataget2)( st_EMINJ_EMINJ_BUF * ptt_store );
    u1 u1_id;  // lsb=1 :ID
} st_EMINJ_EMINJ_TBL2;
```

**用途:**
- 新構造体形式対応の調停テーブル
- 旧構造体と同様の役割

---

### 2. 噴射制御構造体

#### st_EMINJ_EINJ（旧構造体）
**定義箇所:** eminj.h（外部ヘッダファイル）

**主要メンバー:**
```c
struct st_EMINJ_EINJ {
    u1  u1_pri;              // 優先度
    u4  u4_einjrq_dat;       // 噴射要求データ
    u2  u2_einjmod;          // 噴射モード
    
    // ポート噴射関連（D-4以外）
    s2  s2_eainjp1;          // ポート1段目噴射開始時期
    s2  s2_eainjp2;          // ポート2段目噴射開始時期
    s2  s2_eainjp3;          // ポート3段目噴射開始時期
    s2  s2_eainjp4;          // ポート4段目噴射開始時期
    s2  s2_einjend;          // ポート噴射終了時期
    s2  s2_eainjcutp;        // ポート噴射強制停止時期
    
    // 直噴関連（デュアルINJ/D-4）
    s2  s2_eainjd1;          // 直噴1段目噴射開始時期
    s2  s2_eainjd2;          // 直噴2段目噴射開始時期
    s2  s2_eainjd3;          // 直噴3段目噴射開始時期
    s2  s2_eainjd4;          // 直噴4段目噴射開始時期
    s2  s2_eainjcutd;        // 直噴噴射強制停止時期
    
    // 噴射量関連
    s4  s4_eqinjstp1;        // ポート1段目始動時噴射量
    s4  s4_eqinjstp2;        // ポート2段目始動時噴射量
    s4  s4_eqinjstp3;        // ポート3段目始動時噴射量
    s4  s4_eqinjstp4;        // ポート4段目始動時噴射量
    s4  s4_eqinjstd1;        // 直噴1段目始動時噴射量
    s4  s4_eqinjstd2;        // 直噴2段目始動時噴射量
    s4  s4_eqinjstd3;        // 直噴3段目始動時噴射量
    s4  s4_eqinjstd4;        // 直噴4段目始動時噴射量
    s4  s4_eqfc[NCYL];       // FC燃料噴射量
    
    // 補正係数関連
    s2  s2_ek1fn[NOX];       // 1段目噴射量算出係数（バンク別）
    s2  s2_ek2fn[NOX];       // 2段目噴射量算出係数（バンク別）
    s2  s2_ek3fn[NOX];       // 3段目噴射量算出係数（バンク別）
    s2  s2_ekrchref[NOX];    // 噴射量補正係数（バンク別）
    
    // 圧力関連
    s2  s2_eprreq;           // 直噴燃料ポンプ目標圧力
    s2  s2_eqfreq;           // 低圧燃料ポンプ吐出量（非可変圧時）
    s2  s2_eprreql;          // 低圧燃料ポンプ目標圧力（可変圧時）
    
    // その他
    u1  bi_exqinjast[NCYL];  // 始動後噴射量要求フラグ
    u1  u1_explreq;          // PL噴射実施要求
    
    // float値（演算用）
    f4  f4_eainjp1;
    f4  f4_eainjp2;
    // ... その他多数のfloat変数
};
```

**仕様書対応:**
- セクションC「IF情報1 公開変数」に対応
- 噴射制御に必要な全パラメータを保持

---

#### st_EMINJ_EMINJ（新構造体）
**定義箇所:** eminj.h（外部ヘッダファイル）

**主要な違い:**
- 配列化された構造
  - 個別変数 `s2_eainjp1, s2_eainjp2, ...` → 配列 `s2_eainjpn[]`
  - 個別変数 `s2_eainjd1, s2_eainjd2, ...` → 配列 `s2_eainjdn[]`
  - 個別変数 `s4_eqinjstp1, s4_eqinjstp2, ...` → 配列 `s4_eqinjstpn[]`
  - 個別変数 `s4_eqinjstd1, s4_eqinjstd2, ...` → 配列 `s4_eqinjstdn[]`

- 追加メンバー
  - `u4_einjptn` : 噴射パターン
  - `s4_eqinjflfix[8]` : FL固定噴射量
  - `s4_eqinjplfix[8]` : PL固定噴射量

**利点:**
- コードの簡潔化（ループ処理可能）
- 拡張性の向上（段数変更が容易）

---

### 3. 内部バッファ構造体

#### st_EMINJ_EMINJ_DEF（旧構造体形式）
**用途:** 各機能モジュールからのデータ取得用

**特徴:**
- `st_EMINJ_EINJ`と同じメンバー構成
- 調停前の一時バッファとして使用

---

#### st_EMINJ_EMINJ_BUF（新構造体形式）
**用途:** 各機能モジュールからのデータ取得用（新構造体版）

**特徴:**
- `st_EMINJ_EMINJ`と同じメンバー構成
- 配列形式のデータ保持

---

### 4. グローバル変数

#### 制御構造体インスタンス

```c
st_EMINJ_EMINJ stg_eminj_eminj;  // 新噴射部品制御構造体（行457）
st_EMINJ_EINJ  stg_eminj_einj;   // 噴射部品制御構造体（行460）
```

**アクセス:**
- 専用関数経由でのアクセスを推奨（仕様書記載）
- 直接参照は非推奨

---

#### 公開変数（SAC連携用）

**噴射モード関連:**
```c
u2 u2g_eminj_einjmodfix;        // 現在確定噴射モード（行463）
```

**ポート噴射関連（D-4以外）:**
```c
f4 f4g_eminj_einjend;           // ポート噴射終了時期（行465）
s2 s2g_eminj_eainjpn[5];        // ポートn段目噴射開始時期（行466）
f4 f4g_eminj_eainjpn[5];        // 〃 float値（行467）
s4 s4g_eminj_eqinjstpn[5];      // ポートn段目始動時噴射量（行468）
f4 f4g_eminj_eqinjstpn[5];      // 〃 float値（行469）
```

**直噴関連（デュアルINJ/D-4）:**
```c
f4 f4g_eminj_eainjd1fix;        // 確定直噴1段目噴射開始時期（行472）
f4 f4g_eminj_eainjd2fix;        // 確定直噴2段目噴射開始時期（行473）
// ... d3fix〜d6fixまで
s2 s2g_eminj_eainjdn[6];        // 直噴n段目噴射開始時期（行478）
f4 f4g_eminj_eainjdn[6];        // 〃 float値（行479）
f4 f4g_eminj_eqinjstd1;         // 直噴1段目始動時噴射量（行480）
// ... qinjstd2〜qinjstd4まで
s4 s4g_eminj_eqinjstdn[6];      // 直噴n段目始動時噴射量（行484）
f4 f4g_eminj_eqinjstdn[6];      // 〃 float値（行485）
```

**FC・補正係数関連:**
```c
s4 s4g_eminj_eqfc[NCYL];        // FC燃料噴射量（行487）
f4 f4g_eminj_eqfc[NCYL];        // 〃 float値（行488）
s2 s2g_eminj_ek1fn[NOX];        // 1段目噴射量算出係数（行489）
f4 f4g_eminj_ek1fn[NOX];        // 〃 float値（行490）
s2 s2g_eminj_ek2fn[NOX];        // 2段目噴射量算出係数（行491）
f4 f4g_eminj_ek2fn[NOX];        // 〃 float値（行492）
s2 s2g_eminj_ek3fn[NOX];        // 3段目噴射量算出係数（行493）
f4 f4g_eminj_ek3fn[NOX];        // 〃 float値（行494）

f4 f4g_eminj_ek1ffix;           // 確定1段目噴射量算出係数（行495）
f4 f4g_eminj_ek2ffix;           // 確定2段目噴射量算出係数（行496）
f4 f4g_eminj_ek3ffix;           // 確定3段目噴射量算出係数（行497）

s2 s2g_eminj_ekpfi;             // ポート噴射量算出係数（行498）
f4 f4g_eminj_ekpfi;             // 〃 float値（行499）
s2 s2g_eminj_ekpfix;            // ポート噴射量算出係数（確定）（行500）
f4 f4g_eminj_ekpfix;            // 〃 float値（行501）
s2 s2g_eminj_ekpfin[NOX];       // ポート噴射量算出係数（バンク別）（行502）
f4 f4g_eminj_ekpfin[NOX];       // 〃 float値（行503）
```

**圧力関連:**
```c
s2 s2g_eminj_eprreq;            // 直噴燃料ポンプ目標圧力（行505）
f4 f4g_eminj_eprreq;            // 〃 float値（行506）
s2 s2g_eminj_eqfreq;            // 低圧燃料ポンプ吐出量（行509）
s2 s2g_eminj_eprreql;           // 低圧燃料ポンプ目標圧力（行511）
f4 f4g_eminj_eprreql;           // 〃 float値（行512）
```

**調停・補正係数:**
```c
u1 u1g_eminj_einjmedislid;      // 噴射部品調停ID（行514）
s2 s2g_eminj_ekrichx;           // 噴射量補正係数（行515）
f4 f4g_eminj_ekrichx;           // 〃 float値（行516）
s2 s2g_eminj_ekrchref[NOX];     // 噴射量補正係数（バンク別）（行517）
f4 f4g_eminj_ekrchref[NOX];     // 〃 float値（行518）
```

**PL噴射関連（デュアルINJ/D-4）:**
```c
s2 s2g_eminj_ekpfit;            // 目標ポート噴射量算出係数（行520）
s2 s2g_eminj_ekpfitn[NOX];      // 〃（バンク別）（行521）
f4 f4g_eminj_ekpfitn[NOX];      // 〃 float値（行522）
f4 f4g_eminj_ekpfiegrn[NOX];    // EGR-ON時の目標ポート噴射量算出係数（行524）
```

**固定噴射量:**
```c
s4 s4g_eminj_eqinjflfix[8];     // FL固定噴射量（行527）
f4 f4g_eminj_eqinjflfix[8];     // 〃 float値（行528）
s4 s4g_eminj_eqinjplfix[8];     // PL固定噴射量（行529）
f4 f4g_eminj_eqinjplfix[8];     // 〃 float値（行530）
```

**仕様書対応:**
- セクションC「IF情報1 公開変数」の全項目に対応
- SACへの公開データとして使用

---

#### 内部制御変数（static）

**優先度管理:**
```c
static u1 u1s_eminj_estpri;     // 始動時要求の優先度（行532）
static u1 u1s_eminj_estpri2;    // 始動時要求2の優先度（行533）
static u1 u1s_eminj_estprir;    // 始動時要求と始動時要求2間の優先度選択（行534）
static u1 u1s_eminj_eastpri;    // 始動後要求の優先度（行535）
static u1 u1s_eminj_eastpri2;   // 始動後要求2の優先度（行536）
static u1 u1s_eminj_exastmedi;  // 始動後要求調停対象フラグ（行537）
static u4 u4s_eminj_erqdat[2];  // 要求及び噴射部品要求記憶ID（行538）
static u1 u1s_eminj_epri;       // 通常要求の優先度（行539）
static u1 u1s_eminj_epri2;      // 通常要求2の優先度（行540）
```

**状態フラグ:**
```c
static u1 u1s_eminj_exasto;         // 始動フラグ（前回値）（行541）
static u1 u1s_eminj_exast_lch;      // 始動フラグ（ラッチ用）（行542）
static u1 u1s_eminj_exnercdfew;     // NE割り込みタスク実行フラグ（行543）
static u1 u1s_eminj_eprisel_fix;    // 最高優先度（行544）
static u1 u1s_eminj_eprifix;        // 確定優先度（行545）
```

**キャッシュデータ:**
```c
static st_EMINJ_EMINJ_DEF sts_eminj_erestahot_data;  // 直噴起動制御データ（行550）
static st_EMINJ_EMINJ_DEF sts_eminj_erdpn_data;      // PN粒子制御データ（行553）
```

---

### 5. 要求フラグビット定義

#### u4_einjrq_dat のビット構成
**定義箇所:** eminj.h（外部ヘッダファイル）

```c
#define u4g_EMINJ_RQINJMODE    (0x00000001U)  // 噴射モード要求有
#define u4g_EMINJ_RQAINJP      (0x00000002U)  // ポート噴射開始時期要求有
#define u4g_EMINJ_RQAINJP1     (0x00000004U)  // ポート1段目噴射開始時期要求有
#define u4g_EMINJ_RQAINJP2     (0x00000008U)  // ポート2段目噴射開始時期要求有
#define u4g_EMINJ_RQAINJP3     (0x00000010U)  // ポート3段目噴射開始時期要求有
#define u4g_EMINJ_RQAINJP4     (0x00000020U)  // ポート4段目噴射開始時期要求有
#define u4g_EMINJ_RQAINJPN     (0x0000003EU)  // ポートn段目噴射開始時期要求有（統合）
// ... その他多数のビットフラグ
```

**用途:**
- 各機能がどのパラメータを要求しているかを示す
- ビット単位で複数要求を同時に表現可能

---

### 6. 定数定義

#### マクロ定数（行359-449）

**基本値:**
```c
#define s2s_EMINJ_KRICHI       // 噴射量補正係数初期値（行359）
#define s2s_EMINJ_AINJP_VD     // ポート噴射開始時期初期値（行362）
#define s2s_EMINJ_AINJP_MN     // ポート噴射開始時期下限値（行363）
#define s2s_EMINJ_AINJP_MX     // ポート噴射開始時期上限値（行364）
// ... その他多数
```

**機能ID:**
```c
#define u1s_EMINJ_RESTAHOT_ID  ((u1)32)  // 直噴起動制御ID（行412）
#define u1s_EMINJ_KCST_ID      ((u1)34)  // 始動性悪化防止制御ID（行413）
// ... その他多数
```

**要求無しデータ:**
```c
#define u4s_EMINJ_NORQDAT      ((u4)0x00000000U)  // 無要求データ（行452）
```

---

## データフロー図

```
[各機能モジュール]
        ↓ dataget関数
[st_EMINJ_EMINJ_DEF / st_EMINJ_EMINJ_BUF]
        ↓ datacopy関数
[内部バッファ]
        ↓ dataset関数
[stg_eminj_einj / stg_eminj_eminj]
        ↓ 公開変数更新
[s2g_eminj_xxx / f4g_eminj_xxx / u1g_eminj_xxx]
        ↓ SAC連携
[SAC（噴射制御モジュール）]
```

---

## LSB値とfloat値の対応

### 変換ルール
- LSB値（s2, s4）: 整数型、メモリ効率重視
- float値（f4）: 浮動小数点型、演算精度重視

### 変換式の例
```c
// LSB → float
f4g_eminj_ekrichx = (f4)s2g_eminj_ekrichx * (f4)((32.*2.)/128./256.);

// float → LSB
s2g_eminj_ekrichx = (s2)(f4g_eminj_ekrichx / ((32.*2.)/128./256.) + 0.5);
```

### 目的
- 通信・保存時: LSB値（省メモリ）
- 演算時: float値（高精度）
- 両方を保持することで用途に応じて使い分け

---

生成日: 2025-11-07
