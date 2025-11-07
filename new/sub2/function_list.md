# eminj_l_mat.c 関数一覧

## 公開関数（extern）

| No | 関数名 | 行番号 | 呼び出しタイミング | 機能概要 |
|----|--------|--------|-------------------|---------|
| 1 | `vdg_eminj_pwon()` | 722-804 | pwon（電源ON時） | 初期値設定。噴射関連パラメータの初期化と基本値設定を行う |
| 2 | `vdg_eminj_8msm()` | 815-2593 | 8ms中タスク | 噴射要求の調停処理。各機能からの要求を優先度に基づいて調停しSACに公開 |

---

## 内部関数（static）

### データ処理関数

| No | 関数名 | 行番号 | 機能概要 |
|----|--------|--------|---------|
| 3 | `vds_eminj_einj_dataset()` | 2855-3001 | 旧構造体形式へのデータセット処理 |
| 4 | `vds_eminj_eminj_dataset()` | 3737-4002 | 新構造体形式へのデータセット処理 |
| 5 | `vds_eminj_einj_datacopy()` | 4014-4152 | 旧構造体形式のデータコピー処理 |
| 6 | `vds_eminj_einj_datacopy2()` | 4380-4458 | 新構造体形式のデータコピー処理 |
| 7 | `vds_eminj_einj_dataconv()` | 4470-4654 | 集約対象用の旧→新構造体データ移行処理 |
| 8 | `vds_eminj_einj_dataconv_rev()` | 4669-4895 | 集約対象用の新→旧構造体データ移行処理 |

### ラッパー関数

| No | 関数名 | 行番号 | 機能概要 |
|----|--------|--------|---------|
| 9 | `vds_eminj_erestahot_rap_dataget()` | 4907-4912 | 直噴起動制御データ取得（ラッパー関数） |
| 10 | `vds_eminj_erdpn_rap_dataget()` | 4925-4930 | PN粒子制御データ取得（ラッパー関数） |
| 11 | `vds_eminj_dummy_emedi_dataget()` | 4942-4945 | ダミー関数（旧構造体用） |
| 12 | `vds_eminj_dummy_emedi_dataget2()` | 4956-4959 | ダミー関数（新構造体用） |

---

## 関数詳細

### 1. vdg_eminj_pwon()
**目的:** 電源投入時の初期化処理

**処理内容:**
1. 噴射量補正係数の初期値設定 (`s2s_EMINJ_KRICHI`)
2. ポート噴射量算出係数の初期化
3. 噴射終了時期の基本値設定
4. 低圧燃料ポンプ目標圧力の初期化（可変圧制御時）
5. 初期データを構造体にセット

**主要変数:**
- `stg_eminj_einj` - 噴射部品制御構造体
- `stg_eminj_eminj` - 新噴射部品制御構造体

---

### 2. vdg_eminj_8msm()
**目的:** 8ms中タスクでの噴射要求調停処理

**処理フロー:**
1. **初期化処理** (行817-1000)
   - ローカル変数の初期化
   - 前回値の保存

2. **始動状態判定** (行1002-1100)
   - 始動フラグの判定
   - 始動時/始動後/通常の切り替え

3. **優先度選択** (行1102-1500)
   - 始動時優先度 (`u1s_eminj_estpri`)
   - 始動後優先度 (`u1s_eminj_eastpri`)
   - 通常優先度 (`u1s_eminj_epri`)
   - 最終優先度の決定

4. **調停テーブル処理** (行2033-2217)
   - ID順に機能のdataget関数を呼び出し
   - 要求データの取得と統合

5. **補正処理** (行2220-2450)
   - 噴射量補正係数の取得
   - リッチ補正の処理

6. **データ公開処理** (行2453-2580)
   - 旧構造体へのデータセット
   - 新構造体へのデータセット
   - 公開変数の更新

7. **SAC連携** (行2581-2590)
   - `vdg_ainjif_renew_injrq()` - SAC噴射要求受付

**主要ローカル変数:**
```c
u1t_injmedislid      // 噴射部品調停ID
u1t_xast             // 始動フラグ
u1s_eminj_estpri     // 始動時優先度
u1s_eminj_eastpri    // 始動後優先度
u1s_eminj_epri       // 通常優先度
u1s_eminj_eprisel_fix // 最高優先度
```

---

### 3. vds_eminj_einj_dataset()
**目的:** 調停結果を旧構造体形式にセット

**引数:**
- `ptt_data` - 出力先構造体 (`st_EMINJ_EINJ`)
- `ptt_copy` - コピー元構造体 (`st_EMINJ_EMINJ_DEF`)
- `u1_pwon` - 電源投入フラグ

**処理内容:**
1. 優先度のコピー
2. 要求データフラグの展開
3. 噴射モードのコピー
4. 噴射開始時期配列のコピー
5. 噴射量配列のコピー
6. 補正係数のコピー
7. LSB値からfloat値への変換

---

### 4. vds_eminj_eminj_dataset()
**目的:** 調停結果を新構造体形式にセット

**引数:**
- `ptt_data` - 出力先構造体 (`st_EMINJ_EMINJ`)
- `ptt_copy` - コピー元構造体 (`st_EMINJ_EMINJ_BUF`)
- `u1_pwon` - 電源投入フラグ

**処理内容:**
- `vds_eminj_einj_dataset()`と同様の処理を新構造体形式で実施
- 噴射パターン情報の追加処理
- FL/PL固定噴射量の処理

---

### 5. vds_eminj_einj_datacopy()
**目的:** 旧構造体形式のデータコピー

**処理内容:**
- メンバー変数の単純コピー
- 配列データのループコピー
- NE割り込みフラグによる条件分岐

---

### 6. vds_eminj_einj_datacopy2()
**目的:** 新構造体形式のデータコピー

**処理内容:**
- `vds_eminj_einj_datacopy()`と同様だが新構造体用
- 噴射パターン、FL/PL固定噴射量の追加コピー

---

### 7. vds_eminj_einj_dataconv()
**目的:** 旧構造体から新構造体への変換

**処理内容:**
1. 要求フラグの統合
   - 個別噴射段要求 → 配列要求に統合
   - 例: `RQAINJP1`, `RQAINJP2`, ... → `RQAINJPN`

2. データの配列化
   - 個別変数 → 配列形式に変換
   - 例: `s2_eainjp1`, `s2_eainjp2`, ... → `s2_eainjpn[]`

---

### 8. vds_eminj_einj_dataconv_rev()
**目的:** 新構造体から旧構造体への逆変換

**処理内容:**
1. 配列要求フラグの展開
   - 配列要求 → 個別要求フラグに展開
   - 配列値チェックにより有効要求を判定

2. 配列データの展開
   - 配列形式 → 個別変数に展開

**注意点:**
- 新構造体のみに存在するメンバー（噴射パターン等）は移行されない

---

### 9-10. ラッパー関数（erestahot, erdpn）
**目的:** 静的変数からのデータ取得

**背景:**
- 8msm内で複数回dataget関数が呼ばれる可能性
- 毎回異なるデータを返すのを防ぐため静的変数にキャッシュ
- ラッパー関数経由でキャッシュデータを提供

**適用機能:**
- `vds_eminj_erestahot_rap_dataget()` - 直噴起動制御
- `vds_eminj_erdpn_rap_dataget()` - PN粒子制御

---

### 11-12. ダミー関数
**目的:** テーブル構造の統一性維持

**理由:**
- 調停テーブルは全IDに関数ポインタが必要
- 未使用IDに対してはダミー関数を割り当て
- 処理は何もしない（空関数）

---

## 呼び出し関係図

```
[外部から]
    ↓
vdg_eminj_pwon()
    ├─→ vdg_ebinjctr_ebinjctr_dataget()
    ├─→ vds_eminj_einj_dataset()
    └─→ vds_eminj_eminj_dataset()

[外部から 8ms周期]
    ↓
vdg_eminj_8msm()
    ├─→ 調停テーブル各機能のdataget関数
    │   ├─→ vdg_eegstpvs_emedi_dataget()
    │   ├─→ vdg_estphv_emedi_dataget()
    │   ├─→ vdg_estpss_emedi_dataget()
    │   ├─→ vdg_estass_emedi_dataget()
    │   ├─→ vds_eminj_erestahot_rap_dataget()
    │   ├─→ vds_eminj_erdpn_rap_dataget()
    │   └─→ [その他多数の機能]
    ├─→ vdg_emkrichb_ekrichxb_get()
    ├─→ vds_eminj_einj_datacopy()
    ├─→ vds_eminj_einj_datacopy2()
    ├─→ vds_eminj_einj_dataset()
    ├─→ vds_eminj_eminj_dataset()
    └─→ vdg_ainjif_renew_injrq()
```

---

## コンパイルスイッチと関数の関係

### EFI方式別
- `JEEFI == u1g_EJCC_DUAL` : デュアルINJ（全機能有効）
- `JEEFI == u1g_EJCC_D4` : D-4（直噴関連のみ）
- `JEEFI == u1g_EJCC_PORT` : ポート噴射（ポート関連のみ）

### HV関連
- `JEALLHV_E == u1g_EJCC_ALLHV_E` : HV機能有効時の処理追加
- `JEEGMG_E == u1g_EJCC_HVPLGR_E` : HVプラグイン時の処理
- `JEEGMG_E == u1g_EJCC_HVCLUTCH_E` : HVクラッチ時の処理

### その他
- `JEPRDEMAND == u1g_EJCC_USE` : 可変圧制御有効
- `JESS == u1g_EJCC_USE` : SS機能有効
- `JEFFV != u1g_EJCC_NOT_USE` : FFV仕様有効

各スイッチにより、関数内の処理分岐やインクルードファイルが変化

---

生成日: 2025-11-07
