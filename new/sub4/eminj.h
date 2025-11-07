/* eminj-pcw00-1500-a-t-M4 */
/*********************************************************************/
/*  Copyright Toyota Motor Corporation                               */
/*********************************************************************/

/*********************************************************************/
/* オブジェクト名  |  噴射要求の調停                                 */
/* 注意事項        |                                                 */
/*-------------------------------------------------------------------*/
/*  I/F変更履歴    | acw-11 : 集約対象用構造体,同時性ﾃﾞｰﾀ構造体から  */
/*                 |          以下のメンバを削除                     */
/*                 |            s4_eqinjclmt                         */
/*                 |          以下のIFを削除                         */
/*                 |            u4g_EMINJ_RQQINJCLMT                 */
/*                 |          以下のIFを公開                         */
/*                 |          【ﾍﾞﾝﾁ適合用ｿﾌﾄ有】OR【ﾍﾞﾝﾁ適合ﾓｰﾄﾞ有】*/
/*                 |            u1g_EMINJ_BENCH_ID                   */
/*                 |          以下のIFのコンパイルSW変更             */
/*                 |          【ﾍﾞﾝﾁ適合用ｿﾌﾄ有】->【ﾍﾞﾝﾁ適合用ｿﾌﾄ有】OR【ﾍﾞﾝﾁ適合ﾓｰﾄﾞ有】*/
/*                 |            u1g_eminj_BENCH_PRI                  */
/*                 |          【HV】->【EG-MG遊星ｷﾞｱ】OR【EG-MG直結】*/
/*                 |            u1g_EMINJ_STPHV_ID,u1g_eminj_STPHV_PRI */
/*                 |          【HV】->【ALL HV】                     */
/*                 |            u1g_EMINJ_WUPCAT_ID,u1g_eminj_WUPCAT_PRI */
/*                 |          【SS制御有】->【SS制御有】OR【EG-MGｸﾗｯﾁ】 */
/*                 |            u1g_EMINJ_STPSS_ID,u1g_eminj_STPSS_PRI */
/*                 |            u1g_EMINJ_STASS_ID,u1g_eminj_STASS_PRI */
/*                 |          【HV】AND【ﾎﾟｰﾄ】->【ALL HV】AND【D-4以外】 */
/*                 |            u1g_EMINJ_STAHV_ID,u1g_eminj_STAHV_PRI */
/*                 |          【HV】AND【D-4以外】-> コンパイルSWなし */
/*                 |            u1g_EMINJ_RDPN_ID,u1g_eminj_RDPN_PRI */
/*                 | acw-12 : 以下の変数を追加                       */
/*                 |            f4g_eminj_eprreql【可変燃圧制御有】  */
/*                 |            s2g_eminj_ecqinjast_8m               */
/*                 |            u1g_eminj_explreq                    */
/*                 |          以下の定数を追加                       */
/*                 |            u1g_EMINJ_NONE_ID                    */
/*                 |            u1g_EMINJ_RDNVES_ID【ALL HV】        */
/*                 |            u1g_EMINJ_RDPN_ST_ID【ALL HV】AND【ﾎﾟｰﾄ】*/
/*                 |            u1g_EMINJ_FCFRCTRL_ID【GPF有】       */
/*                 |            u1g_eminj_RDNVES_PRI【ALL HV】       */
/*                 |            u1g_eminj_RDPN_ST_PRI【ALL HV】AND【ﾎﾟｰﾄ】*/
/*                 |            u1g_eminj_FCFRCTRL_PRI【GPF有】      */
/*                 |          以下のIFのコンパイルSW変更             */
/*                 |          コンパイルSWなし ->【ALL HV】AND【D-4以外】 */
/*                 |            u1g_EMINJ_RDPN_ID                    */
/*                 |            u1g_eminj_RDPN_PRI                   */
/*                 | acw-13 :                                        */
/*                 |          以下の変数を追加                       */
/*                 |            u4g_eminj_einjptn                    */
/*                 |            s2g_eminj_eainjpn[5]【D-4以外】      */
/*                 |            f4g_eminj_eainjpn[5]【D-4以外】      */
/*                 |            s2g_eminj_eainjdn[5]【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/*                 |            f4g_eminj_eainjdn[5]【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/*                 |            s4g_eminj_eqinjstpn[5]【D-4以外】    */
/*                 |            f4g_eminj_eqinjstpn[5]【D-4以外】    */
/*                 |            s4g_eminj_eqinjstdn[5]【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/*                 |            f4g_eminj_eqinjstdn[5]【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/*                 |            s4g_eminj_eqinjflfix[8]              */
/*                 |            f4g_eminj_eqinjflfix[8]              */
/*                 |            s4g_eminj_eqinjplfix[8]              */
/*                 |            f4g_eminj_eqinjplfix[8]              */
/*                 |            stg_eminj_eminj                      */
/*                 |          以下の集約対象用構造体,同時性ﾃﾞｰﾀ構造体を追加 */
/*                 |           st_EMINJ_EMINJ_BUF                    */
/*                 |           st_EMINJ_EMINJ                        */
/*                 |          以下のst_EMINJ_EMINJ_DEF,st_EMINJ_EINJのメンバの */
/*                 |           コンパイルSW変更                      */
/*                 |           【ﾃﾞｭｱﾙINJ】AND【E-EGR】              */
/*                 |           ->【ﾃﾞｭｱﾙINJ】AND【EGR制御有】        */
/*                 |            f4_ekpfiegr                          */
/*                 |            f4_ekpfiegrn[u1g_EJCC_NOX]           */
/*                 |          以下の関数を追加                       */
/*                 |            vdg_eminj_eminj_dataget()            */
/*                 |          以下の定数を追加                       */
/*                 |            u1g_EMINJ_BINJPLCTR_ID【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/*                 |            u1g_eminj_BINJPLCTR_PRI【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/*                 |            u4g_EMINJ_INJPTN_VD                  */
/*                 |            u1g_eminj_FREE2_PRI【ﾌﾘｰﾎﾟｰﾄ2使用】  */
/*                 |            u1g_eminj_FREE3_PRI【ﾌﾘｰﾎﾟｰﾄ3使用】  */
/*                 |            u1g_eminj_FREE4_PRI【ﾌﾘｰﾎﾟｰﾄ4使用】  */
/*                 |            u1g_eminj_FREE5_PRI【ﾌﾘｰﾎﾟｰﾄ5使用】  */
/*                 |            u1g_eminj_FREE6_PRI【ﾌﾘｰﾎﾟｰﾄ6使用】  */
/*                 |            u1g_eminj_FREE7_PRI【ﾌﾘｰﾎﾟｰﾄ7使用】  */
/*                 |            u1g_EMINJ_FREE2_ID【ﾌﾘｰﾎﾟｰﾄ2使用】   */
/*                 |            u1g_EMINJ_FREE3_ID【ﾌﾘｰﾎﾟｰﾄ3使用】   */
/*                 |            u1g_EMINJ_FREE4_ID【ﾌﾘｰﾎﾟｰﾄ4使用】   */
/*                 |            u1g_EMINJ_FREE5_ID【ﾌﾘｰﾎﾟｰﾄ5使用】   */
/*                 |            u1g_EMINJ_FREE6_ID【ﾌﾘｰﾎﾟｰﾄ6使用】   */
/*                 |            u1g_EMINJ_FREE7_ID【ﾌﾘｰﾎﾟｰﾄ7使用】   */
/*                 |            u4g_EMINJ_RQINJPTN                   */
/*                 |            u4g_EMINJ_RQAINJPN                   */
/*                 |            u4g_EMINJ_RQAINJDN                   */
/*                 |            u4g_EMINJ_RQQINJSTPN                 */
/*                 |            u4g_EMINJ_RQQINJSTDN                 */
/*                 |            u4g_EMINJ_RQQINJFLFIX                */
/*                 |            u4g_EMINJ_RQQINJPLFIX                */
/*                 |            u2g_EMINJ_MOD007                     */
/*                 |          以下の変数を削除                       */
/*                 |            s4g_eminj_eqfccyl[u1g_EJCC_NCYL]     */
/*                 |            f4g_eminj_eqfccyl[u1g_EJCC_NCYL]     */
/*                 |            u1g_eminj_explrq[u1g_EJCC_NCYL]      */
/*                 |          以下のIFのコンパイルSW変更             */
/*                 |          【ALL HV】AND【D-4以外】->【ALL HV】   */
/*                 |           u1g_EMINJ_STAHV_ID,u1g_eminj_STAHV_PRI */
/*                 |          【ﾃﾞｭｱﾙINJ】AND【E-EGR】               */
/*                 |           ->【ﾃﾞｭｱﾙINJ】AND【EGR制御有】        */
/*                 |           f4g_eminj_ekpfiegr,                   */
/*                 |           f4g_eminj_ekpfiegrn[u1g_EJCC_NOX]     */
/*                 | acw-14 : 以下定数の追加                         */
/*                 |            u1g_EMINJ_STACM_ID                   */
/*                 |             (【ｻｰｷｯﾄｼﾞｵﾌｪﾝｼﾝｸﾞ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】)AND【SUB-CPU以外】AND【ｻｰｷｯﾄﾓｰﾄﾞ時の始動制御要求使用】*/
/*                 |            u1g_EMINJ_ACTGAF_ID【ﾃﾞｭｱﾙINJ】      */
/*                 |            u1g_EMINJ_IMBRQ_ID【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ﾃﾞｭｱﾙINJ】AND【ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
/*                 |            u1g_EMINJ_MFINJRQ_ID【失火OBD有】AND【ﾃﾞｭｱﾙINJ】AND【失火OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
/*                 |            u1g_EMINJ_FKGDRQ_ID【燃料OBD有】AND【ﾃﾞｭｱﾙINJ】AND【燃料系OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
/*                 |            u1g_eminj_STACM_PRI                  */
/*                 |             (【ｻｰｷｯﾄｼﾞｵﾌｪﾝｼﾝｸﾞ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】)AND【SUB-CPU以外】AND【ｻｰｷｯﾄﾓｰﾄﾞ時の始動制御要求使用】*/
/*                 |            u1g_eminj_IMBRQ_PRI【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ﾃﾞｭｱﾙINJ】AND【ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
/*                 |            u1g_eminj_MFINJRQ_PRI【失火OBD有】AND【ﾃﾞｭｱﾙINJ】AND【失火OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
/*                 |            u1g_eminj_FKGDRQ_PRI【燃料OBD有】AND【ﾃﾞｭｱﾙINJ】AND【燃料系OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
/*                 |          以下定数のコンパイルSW変更             */
/*                 |            u1g_EMINJ_STAHV_ID【ALL HV】AND【HV始動制御要求使用】*/
/*                 |            u1g_EMINJ_FCFRCTRL_ID【GPF有】AND【1気筒FC制御要求使用】*/
/*                 |            u1g_EMINJ_ACTOBD_ID【ﾃﾞｭｱﾙINJ】AND【OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
/*                 |            u1g_EMINJ_ACTLFG_ID(【ﾃﾞｭｱﾙINJ】OR【D-4】)AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】*/
/*                 |            u1g_EMINJ_BINJPLCTR_ID(【ﾃﾞｭｱﾙINJ】OR【D-4】)AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】*/
/*                 |            u1g_eminj_STAHV_PRI【ALL HV】AND【HV始動制御要求使用】*/
/*                 |            u1g_eminj_FCFRCTRL_PRI【GPF有】AND【1気筒FC制御要求使用】*/
/*                 |            u1g_eminj_INJIMB_PRI【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ﾃﾞｭｱﾙINJ】AND【ｲﾝﾊﾞﾗﾝｽ時の噴射制御要求使用】*/
/*                 |            u1g_eminj_ACTOBD_PRI【ﾃﾞｭｱﾙINJ】AND【OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
/*                 |            u1g_eminj_ACTLFG_PRI(【ﾃﾞｭｱﾙINJ】OR【D-4】)AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】*/
/*                 |            u1g_eminj_BINJPLCTR_PRI(【ﾃﾞｭｱﾙINJ】OR【D-4】)AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】*/
/*                 |          以下変数を追加                         */
/*                 |            f4g_eminj_eainjd1fix【ﾃﾞｭｱﾙINJ】OR【D-4】*/
/*                 |            f4g_eminj_eainjd2fix【ﾃﾞｭｱﾙINJ】OR【D-4】*/
/*                 |            f4g_eminj_eainjd3fix【ﾃﾞｭｱﾙINJ】OR【D-4】*/
/*                 |            f4g_eminj_eainjd4fix【ﾃﾞｭｱﾙINJ】OR【D-4】*/
/*                 |            f4g_eminj_ek1ffix                    */
/*                 |            f4g_eminj_ek2ffix                    */
/*                 |            f4g_eminj_ek3ffix                    */
/*                 | acw-15 : 集約対象用構造体st_EMINJ_EMINJ_BUFから */
/*                 |          以下のメンバの配列要素数を変更         */
/*                 |            s2_eainjdn[]   【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/*                 |            s4_eqinjstdn[] 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/*                 |          同時性ﾃﾞｰﾀ構造体st_EMINJ_EMINJから     */
/*                 |          以下のメンバの配列要素数を変更         */
/*                 |            s2_eainjdn[]   【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/*                 |            f4_eainjdn[]   【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/*                 |            s4_eqinjstdn[] 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/*                 |            f4_eqinjstdn[] 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/*                 |          以下定数の追加                         */
/*                 |            u1g_EMINJ_BINJPLCTR_WC_ID 【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】*/
/*                 |            u1g_EMINJ_BINJPLCTR_STAHV_ID 【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】*/
/*                 |            u1g_EMINJ_FREE8_ID 【ﾌﾘｰﾎﾟｰﾄ8使用】  */
/*                 |            u1g_EMINJ_FREE9_ID 【ﾌﾘｰﾎﾟｰﾄ9使用】  */
/*                 |            u1g_EMINJ_FREE10_ID 【ﾌﾘｰﾎﾟｰﾄ10使用】*/
/*                 |            u1g_EMINJ_FREE11_ID 【ﾌﾘｰﾎﾟｰﾄ11使用】*/
/*                 |            u1g_eminj_BINJPLCTR_WC_PRI 【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】*/
/*                 |            u1g_eminj_BINJPLCTR_STAHV_PRI 【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】*/
/*                 |            u1g_eminj_FREE8_PRI 【ﾌﾘｰﾎﾟｰﾄ8使用】 */
/*                 |            u1g_eminj_FREE9_PRI 【ﾌﾘｰﾎﾟｰﾄ9使用】 */
/*                 |            u1g_eminj_FREE10_PRI 【ﾌﾘｰﾎﾟｰﾄ10使用】*/
/*                 |            u1g_eminj_FREE11_PRI 【ﾌﾘｰﾎﾟｰﾄ11使用】*/
/*                 |          以下定数のコンパイルSW変更             */
/*                 |            u1g_EMINJ_STACM_ID (【ﾘﾓｰﾄｺﾝﾄﾛｰﾙ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】)AND【SUB-CPU以外】AND【始動時吹け上がり制御要求使用】*/
/*                 |            u1g_EMINJ_BINJPLCTR_ID 【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】*/
/*                 |            u1g_eminj_STACM_PRI (【ﾘﾓｰﾄｺﾝﾄﾛｰﾙ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】)AND【SUB-CPU以外】AND【始動時吹け上がり制御要求使用】*/
/*                 |            u1g_eminj_BINJPLCTR_PRI 【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】*/
/*                 |            u1g_EMINJ_RDNVES_ID コンパイルSWなし */
/*                 |          以下変数を追加                         */
/*                 |            f4g_eminj_eainjd5fix 【ﾃﾞｭｱﾙINJ】OR【D-4】*/
/*                 |            f4g_eminj_eainjd6fix 【ﾃﾞｭｱﾙINJ】OR【D-4】*/
/*                 |          以下変数の配列要素数を変更             */
/*                 |            s2g_eminj_eainjdn[] 【ﾃﾞｭｱﾙINJ】OR【D-4】*/
/*                 |            f4g_eminj_eainjdn[] 【ﾃﾞｭｱﾙINJ】OR【D-4】*/
/*                 |            s4g_eminj_eqinjstdn[] 【ﾃﾞｭｱﾙINJ】OR【D-4】*/
/*                 |            f4g_eminj_eqinjstdn[] 【ﾃﾞｭｱﾙINJ】OR【D-4】*/
/*                 |          以下互換用マクロを削除                 */
/*                 |            u4g_EMINJ_RQPRLREQ                   */
/*-------------------------------------------------------------------*/
/*  ファイル構成   |  eminj_l_mat.c, eminj_c_mat.c, eminj_c.h        */
/*-------------------------------------------------------------------*/
/*     個別変更履歴 （個別変更時は以下に変更日、内容を記入すること） */
/*********************************************************************/

#ifndef EMINJ_H
#define EMINJ_H

/*-------------------------------------------------------------------*/
/* ヘッダファイルのインクルード                                      */
/*-------------------------------------------------------------------*/
#include <engsrc/espc/ejcc.h>   /* JEEFI,u1g_EJCC_D4,u1g_EJCC_DUAL,u1g_EJCC_PORT,u1g_EJCC_NOX,JEPRDEMAND,JESS */
                                /* JEEGR,u1g_EJCC_NCYL,JECOMBCCPT_E,u1g_EJCC_SPRAYG_E,JEMAT_BENCHI */
                                /* JEMAT_BENCH_E,JEEGMG_E,u1g_EJCC_HVPLGR_E,u1g_EJCC_HVDIRECT_E,u1g_EJCC_HVCLUTCH_E */
                                /* JEALLHV_E,u1g_EJCC_ALLHV_E */
                                /* JENGPF_E,JENVCTR,JEMICN_E,u1g_EJCC_SUB_E,JEOBDAFIMB_D,JEOBDMF */
                                /* JEOBDFKG,JEPLMLT_E,JERMTCTR,JEFFV */

/*-------------------------------------------------------------------*/
/* コンパイルSW未定義チェック                                        */
/*-------------------------------------------------------------------*/
#if !defined JEEFI
#error "JEEFI is undeclared"
#endif

#if !defined u1g_EJCC_D4
#error "u1g_EJCC_D4 is undeclared"
#endif

#if !defined u1g_EJCC_DUAL
#error "u1g_EJCC_DUAL is undeclared"
#endif

#if !defined u1g_EJCC_PORT
#error "u1g_EJCC_PORT is undeclared"
#endif

#if !defined u1g_EJCC_NOX
#error "u1g_EJCC_NOX is undeclared"
#endif

#if !defined JEPRDEMAND
#error "JEPRDEMAND is undeclared"
#endif

#if !defined JESS
#error "JESS is undeclared"
#endif

#if !defined JEEGR
#error "JEEGR is undeclared"
#endif

#if !defined u1g_EJCC_NCYL
#error "u1g_EJCC_NCYL is undeclared"
#endif

#if !defined JECOMBCCPT_E
#error "JECOMBCCPT_E is undeclared"
#endif

#if !defined u1g_EJCC_SPRAYG_E
#error "u1g_EJCC_SPRAYG_E is undeclared"
#endif

#if !defined JEMAT_BENCHI
#error "JEMAT_BENCHI is undeclared"
#endif

#if !defined JEMAT_BENCH_E
#error "JEMAT_BENCH_E is undeclared"
#endif

#if !defined JEEGMG_E
#error "JEEGMG_E is undeclared"
#endif

#if !defined u1g_EJCC_HVPLGR_E
#error "u1g_EJCC_HVPLGR_E is undeclared"
#endif

#if !defined u1g_EJCC_HVDIRECT_E
#error "u1g_EJCC_HVDIRECT_E is undeclared"
#endif

#if !defined u1g_EJCC_HVCLUTCH_E
#error "u1g_EJCC_HVCLUTCH_E is undeclared"
#endif

#if !defined JEALLHV_E
#error "JEALLHV_E is undeclared"
#endif

#if !defined u1g_EJCC_ALLHV_E
#error "u1g_EJCC_ALLHV_E is undeclared"
#endif

#if !defined JENGPF_E
#error "JENGPF_E is undeclared"
#endif

#if !defined JENVCTR
#error "JENVCTR is undeclared"
#endif

#if !defined JEMICN_E
#error "JEMICN_E is undeclared"
#endif

#if !defined u1g_EJCC_SUB_E
#error "u1g_EJCC_SUB_E is undeclared"
#endif

#if !defined JEOBDAFIMB_D
#error "JEOBDAFIMB_D is undeclared"
#endif

#if !defined JEOBDMF
#error "JEOBDMF is undeclared"
#endif

#if !defined JEOBDFKG
#error "JEOBDFKG is undeclared"
#endif

#if !defined JEPLMLT_E
#error "JEPLMLT_E is undeclared"
#endif

#if !defined JERMTCTR
#error "JERMTCTR is undeclared"
#endif

#if !defined JEFFV
#error "JEFFV is undeclared"
#endif

/*-------------------------------------------------------------------*/
/* 型定義                                                            */
/*-------------------------------------------------------------------*/
/* 集約対象用構造体型 */
typedef struct
{
    u1 u1_pri;                        /* lsb=1 :優先度 */
    u4 u4_einjrq_dat;                 /* lsb=1 :要求有識別子 */
    u2 u2_einjmod;                    /* lsb=1 :噴射モード */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s2 s2_eainjp1;                    /* lsb=1024/128/256,unit=BTDC :ポート1回目噴射開始時期 */
    s2 s2_eainjp2;                    /* lsb=1024/128/256,unit=BTDC :ポート2回目噴射開始時期 */
    s2 s2_eainjp3;                    /* lsb=1024/128/256,unit=BTDC :ポート3回目噴射開始時期 */
    s2 s2_eainjp4;                    /* lsb=1024/128/256,unit=BTDC :ポート4回目噴射開始時期 */
    s2 s2_einjend;                    /* lsb=1024/128/256,unit=BTDC :ポート噴射終了時期 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2 s2_eainjd1;                    /* lsb=1024/128/256,unit=BTDC :筒内1回目噴射開始時期 */
    s2 s2_eainjd2;                    /* lsb=1024/128/256,unit=BTDC :筒内2回目噴射開始時期 */
    s2 s2_eainjd3;                    /* lsb=1024/128/256,unit=BTDC :筒内3回目噴射開始時期 */
    s2 s2_eainjd4;                    /* lsb=1024/128/256,unit=BTDC :筒内4回目噴射開始時期 */
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s4 s4_eqinjstp1;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート1回目始動時噴射量 */
    s4 s4_eqinjstp2;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート2回目始動時噴射量 */
    s4 s4_eqinjstp3;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート3回目始動時噴射量 */
    s4 s4_eqinjstp4;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート4回目始動時噴射量 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s4 s4_eqinjstd1;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内1回目始動時噴射量 */
    s4 s4_eqinjstd2;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内2回目始動時噴射量 */
    s4 s4_eqinjstd3;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内3回目始動時噴射量 */
    s4 s4_eqinjstd4;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内4回目始動時噴射量 */
#endif /* JEEFI */
    s4 s4_eqfc[u1g_EJCC_NCYL];        /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :FC中噴射量 */
    s2 s2_ek1f;                       /* lsb=(1*4)/128/256,unit=倍 :1回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
    s2 s2_ek1fn[u1g_EJCC_NOX];        /* lsb=(1*4)/128/256,unit=倍 :1回目噴射量算出係数(バンク別) */
    s2 s2_ek2f;                       /* lsb=(1*4)/128/256,unit=倍 :2回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
    s2 s2_ek2fn[u1g_EJCC_NOX];        /* lsb=(1*4)/128/256,unit=倍 :2回目噴射量算出係数(バンク別) */
    s2 s2_ek3f;                       /* lsb=(1*4)/128/256,unit=倍 :3回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
    s2 s2_ek3fn[u1g_EJCC_NOX];        /* lsb=(1*4)/128/256,unit=倍 :3回目噴射量算出係数(バンク別) */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2 s2_eprreq;                     /* lsb=(32*2)/128/256,unit=MPa :高圧ポンプ目標燃圧 */
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_NOT_USE    /*【可変燃圧制御無】*/
    s2 s2_eqfreq;                     /* lsb=512/128/256,unit=L/h :燃料ポンプ吐出流量 */
#else                                 /*【可変燃圧制御有】*/
    s2 s2_eprreql;                    /* lsb=1280/128/256,unit=kPa :低圧ポンプ目標燃圧 */
#endif /* JEPRDEMAND */
    u1 bi_exqinjast :1;               /* lsb=1 :始動後噴射量要求フラグ */
    u1 bi_dummy     :7;               /* ダミー */
    s2 s2_ekrchref[u1g_EJCC_NOX];     /* lsb=(32*2)/128/256,unit=倍 :噴射量補正係数(バンク別) */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    u1 u1_explreq;                    /* lsb=1 :PL噴射実施要求 */
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s2 s2_eainjcutp;                  /* lsb=1024/128/256,unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2 s2_eainjcutd;                  /* lsb=1024/128/256,unit=BTDC :筒内噴射強制ｶｯﾄ時期 */
#endif /* JEEFI */
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    s4 s4_eqinjexp;                   /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :膨張行程噴射量 */
#endif /* JECOMBCCPT_E */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s2 s2_eainjp;                     /* lsb=1024/128/256,unit=BTDC :ﾎﾟｰﾄ噴射開始時期(ﾎﾟｰﾄﾏﾙﾁ未対応部品互換用) */
    s4 s4_eqinjstp;                   /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ﾎﾟｰﾄ始動時噴射量(ﾎﾟｰﾄﾏﾙﾁ未対応部品互換用) */
#endif /* JEEFI */
} st_EMINJ_EMINJ_DEF;

/* 同時性データ構造体型 */
typedef struct
{
    u2 u2_einjmod;                    /* lsb=1 :噴射モード */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s2 s2_eainjp1;                    /* lsb=1024/128/256,unit=BTDC :ポート1回目噴射開始時期 */
    f4 f4_eainjp1;                    /* unit=BTDC :ポート1回目噴射開始時期 */
    s2 s2_eainjp2;                    /* lsb=1024/128/256,unit=BTDC :ポート2回目噴射開始時期 */
    f4 f4_eainjp2;                    /* unit=BTDC :ポート2回目噴射開始時期 */
    s2 s2_eainjp3;                    /* lsb=1024/128/256,unit=BTDC :ポート3回目噴射開始時期 */
    f4 f4_eainjp3;                    /* unit=BTDC :ポート3回目噴射開始時期 */
    s2 s2_eainjp4;                    /* lsb=1024/128/256,unit=BTDC :ポート4回目噴射開始時期 */
    f4 f4_eainjp4;                    /* unit=BTDC :ポート4回目噴射開始時期 */
    s2 s2_einjend;                    /* lsb=1024/128/256,unit=BTDC :ポート噴射終了時期 */
    f4 f4_einjend;                    /* unit=BTDC :ポート噴射終了時期 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2 s2_eainjd1;                    /* lsb=1024/128/256,unit=BTDC :筒内1回目噴射開始時期 */
    f4 f4_eainjd1;                    /* unit=BTDC :筒内1回目噴射開始時期 */
    s2 s2_eainjd2;                    /* lsb=1024/128/256,unit=BTDC :筒内2回目噴射開始時期 */
    f4 f4_eainjd2;                    /* unit=BTDC :筒内2回目噴射開始時期 */
    s2 s2_eainjd3;                    /* lsb=1024/128/256,unit=BTDC :筒内3回目噴射開始時期 */
    f4 f4_eainjd3;                    /* unit=BTDC :筒内3回目噴射開始時期 */
    s2 s2_eainjd4;                    /* lsb=1024/128/256,unit=BTDC :筒内4回目噴射開始時期 */
    f4 f4_eainjd4;                    /* unit=BTDC :筒内4回目噴射開始時期 */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_PORT            /*【ﾎﾟｰﾄ】*/
    s2 s2_eainjpadd;                  /* lsb=1024/128/256,unit=BTDC :ポート追加噴射開始時期 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2 s2_eainjdadd;                  /* lsb=1024/128/256,unit=BTDC :筒内追加噴射開始時期 */
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s4 s4_eqinjstp1;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート1回目始動時噴射量 */
    f4 f4_eqinjstp1;                  /* unit=mg/st :ポート1回目始動時噴射量 */
    s4 s4_eqinjstp2;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート2回目始動時噴射量 */
    f4 f4_eqinjstp2;                  /* unit=mg/st :ポート2回目始動時噴射量 */
    s4 s4_eqinjstp3;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート3回目始動時噴射量 */
    f4 f4_eqinjstp3;                  /* unit=mg/st :ポート3回目始動時噴射量 */
    s4 s4_eqinjstp4;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート4回目始動時噴射量 */
    f4 f4_eqinjstp4;                  /* unit=mg/st :ポート4回目始動時噴射量 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s4 s4_eqinjstd1;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内1回目始動時噴射量 */
    f4 f4_eqinjstd1;                  /* unit=mg/st :筒内1回目始動時噴射量 */
    s4 s4_eqinjstd2;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内2回目始動時噴射量 */
    f4 f4_eqinjstd2;                  /* unit=mg/st :筒内2回目始動時噴射量 */
    s4 s4_eqinjstd3;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内3回目始動時噴射量 */
    f4 f4_eqinjstd3;                  /* unit=mg/st :筒内3回目始動時噴射量 */
    s4 s4_eqinjstd4;                  /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内4回目始動時噴射量 */
    f4 f4_eqinjstd4;                  /* unit=mg/st :筒内4回目始動時噴射量 */
#endif /* JEEFI */
    f4 f4_eqfc[u1g_EJCC_NCYL];        /* unit=mg/st :FC中噴射量 */
    s2 s2_ek1f;                       /* lsb=(1*4)/128/256,unit=倍 :1回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
    f4 f4_ek1f;                       /* unit=倍 :1回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
    s2 s2_ek2f;                       /* lsb=(1*4)/128/256,unit=倍 :2回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
    f4 f4_ek2f;                       /* unit=倍 :2回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
    s2 s2_ek3f;                       /* lsb=(1*4)/128/256,unit=倍 :3回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
    f4 f4_ek3f;                       /* unit=倍 :3回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
    s2 s2_ek1fn[u1g_EJCC_NOX];        /* lsb=(1*4)/128/256,unit=倍 :1回目噴射量算出係数(バンク別) */
    f4 f4_ek1fn[u1g_EJCC_NOX];        /* unit=倍 :1回目噴射量算出係数(バンク別) */
    s2 s2_ek2fn[u1g_EJCC_NOX];        /* lsb=(1*4)/128/256,unit=倍 :2回目噴射量算出係数(バンク別) */
    f4 f4_ek2fn[u1g_EJCC_NOX];        /* unit=倍 :2回目噴射量算出係数(バンク別) */
    s2 s2_ek3fn[u1g_EJCC_NOX];        /* lsb=(1*4)/128/256,unit=倍 :3回目噴射量算出係数(バンク別) */
    f4 f4_ek3fn[u1g_EJCC_NOX];        /* unit=倍 :3回目噴射量算出係数(バンク別) */
    s2 s2_ekrchref[u1g_EJCC_NOX];     /* lsb=(32*2)/128/256,unit=倍 :噴射量補正係数(バンク別) */
    f4 f4_ekrchref[u1g_EJCC_NOX];     /* unit=倍 :噴射量補正係数(バンク別) */
    u1 bi_exqinjast :1;               /* lsb=1 :始動後噴射量要求フラグ */
    u1 bi_dummy     :7;               /* ダミー */
    u1 u1_exqinjast;                  /* lsb=1 :始動後噴射量要求フラグ */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    u1 u1_explreq;                    /* lsb=1 :PL噴射実施要求 */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL            /*【ﾃﾞｭｱﾙINJ】*/
    s2 s2_ekpfit;                     /* lsb=(1*4)/128/256,unit=倍 :目標ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
    f4 f4_ekpfit;                     /* unit=倍 :目標ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
    s2 s2_ekpfitn[u1g_EJCC_NOX];      /* lsb=(1*4)/128/256,unit=倍 :目標ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ別) */
    f4 f4_ekpfitn[u1g_EJCC_NOX];      /* unit=倍 :目標ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ別) */
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    f4 f4_ek1fpt;                     /* unit=倍 :ﾎﾟｰﾄ噴射のみ要求時の目標ﾎﾟｰﾄ1回目噴射量算出係数 */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL            /*【ﾃﾞｭｱﾙINJ】*/
 #if JEEGR == u1g_EJCC_USE            /*【EGR制御有】*/
    f4 f4_ekpfiegr;                   /* unit=倍 :EGR-ON時の目標ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
    f4 f4_ekpfiegrn[u1g_EJCC_NOX];    /* unit=倍 :EGR-ON時の目標ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ別) */
 #endif /* JEEGR */
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s2 s2_eainjcutp;                  /* lsb=1024/128/256,unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期 */
    f4 f4_eainjcutp;                  /* unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2 s2_eainjcutd;                  /* lsb=1024/128/256,unit=BTDC :筒内噴射強制ｶｯﾄ時期 */
    f4 f4_eainjcutd;                  /* unit=BTDC :筒内噴射強制ｶｯﾄ時期 */
#endif /* JEEFI */
    s4 s4_eqfc[u1g_EJCC_NCYL];        /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :FC中噴射量 */
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    s4 s4_eqinjexp;                   /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :膨張行程噴射量 */
    f4 f4_eqinjexp;                   /* unit=mg/st :膨張行程噴射量 */
#endif /* JECOMBCCPT_E */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s2 s2_ek1fpt;                     /* lsb=(1*4)/128/256,unit=倍 :ﾎﾟｰﾄ噴射のみ要求時の目標ﾎﾟｰﾄ1回目噴射量算出係数 */
#endif /* JEEFI */
} st_EMINJ_EINJ;

/* 集約対象用構造体型 */
typedef struct
{
    u1 u1_pri;                        /* lsb=1 :優先度 */
    u4 u4_einjrq_dat;                 /* lsb=1 :要求有識別子 */
    u2 u2_einjmod;                    /* lsb=1 :噴射モード */
    u4 u4_einjptn;                    /* lsb=1 :噴射パターン */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s2 s2_eainjpn[5];                 /* lsb=1024/128/256,unit=BTDC :ポートn回目噴射開始時期（噴射回数配列） */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
    s2 s2_einjend;                    /* lsb=1024/128/256,unit=BTDC :ポート噴射終了時期 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2 s2_eainjdn[6];                 /* lsb=1024/128/256,unit=BTDC :筒内n回目噴射開始時期（噴射回数配列） */ /* 始動時に最大6回噴射(直噴のみ) */
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s4 s4_eqinjstpn[5];               /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポートn回目始動時噴射量（噴射回数配列） */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s4 s4_eqinjstdn[6];               /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内n回目始動時噴射量（噴射回数配列） */ /* 始動時に最大6回噴射(直噴のみ) */
#endif /* JEEFI */
    s4 s4_eqfc[u1g_EJCC_NCYL];        /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :FC中噴射量 */
    s2 s2_ek1fn[u1g_EJCC_NOX];        /* lsb=(1*4)/128/256,unit=倍 :1回目噴射量算出係数(バンク別) */
    s2 s2_ek2fn[u1g_EJCC_NOX];        /* lsb=(1*4)/128/256,unit=倍 :2回目噴射量算出係数(バンク別) */
    s2 s2_ek3fn[u1g_EJCC_NOX];        /* lsb=(1*4)/128/256,unit=倍 :3回目噴射量算出係数(バンク別) */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2 s2_eprreq;                     /* lsb=(32*2)/128/256,unit=MPa :高圧ポンプ目標燃圧 */
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_NOT_USE    /*【可変燃圧制御無】*/
    s2 s2_eqfreq;                     /* lsb=512/128/256,unit=L/h :燃料ポンプ吐出流量 */
#else                                 /*【可変燃圧制御有】*/
    s2 s2_eprreql;                    /* lsb=1280/128/256,unit=kPa :低圧ポンプ目標燃圧 */
#endif /* JEPRDEMAND */
    u1 bi_exqinjast :1;               /* lsb=1 :始動後噴射量要求フラグ */
    u1 bi_dummy     :7;               /* ダミー */
    s2 s2_ekrchref[u1g_EJCC_NOX];     /* lsb=(32*2)/128/256,unit=倍 :噴射量補正係数(バンク別) */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    u1 u1_explreq;                    /* lsb=1 :PL噴射実施要求 */
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s2 s2_eainjcutp;                  /* lsb=1024/128/256,unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2 s2_eainjcutd;                  /* lsb=1024/128/256,unit=BTDC :筒内噴射強制ｶｯﾄ時期 */
#endif /* JEEFI */
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    s4 s4_eqinjexp;                   /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :膨張行程噴射量 */
#endif /* JECOMBCCPT_E */
    s4 s4_eqinjflfix[8];              /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :FL固定噴射量 */
    s4 s4_eqinjplfix[8];              /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :PL固定噴射量 */
} st_EMINJ_EMINJ_BUF;

/* 同時性データ構造体型 */
typedef struct
{
    u2 u2_einjmod;                    /* lsb=1 :噴射モード */
    u4 u4_einjptn;                    /* lsb=1 :噴射パターン */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s2 s2_eainjpn[5];                 /* lsb=1024/128/256,unit=BTDC :ポートn回目噴射開始時期（噴射回数配列） */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
    f4 f4_eainjpn[5];                 /* unit=BTDC :ポートn回目噴射開始時期（噴射回数配列） */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
    s2 s2_einjend;                    /* lsb=1024/128/256,unit=BTDC :ポート噴射終了時期 */
    f4 f4_einjend;                    /* unit=BTDC :ポート噴射終了時期 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2 s2_eainjdn[6];                 /* lsb=1024/128/256,unit=BTDC :筒内n回目噴射開始時期（噴射回数配列） */ /* 始動時に最大6回噴射(直噴のみ) */
    f4 f4_eainjdn[6];                 /* unit=BTDC :筒内n回目噴射開始時期（噴射回数配列） */ /* 始動時に最大6回噴射(直噴のみ) */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_PORT            /*【ﾎﾟｰﾄ】*/
    s2 s2_eainjpadd;                  /* lsb=1024/128/256,unit=BTDC :ポート追加噴射開始時期 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2 s2_eainjdadd;                  /* lsb=1024/128/256,unit=BTDC :筒内追加噴射開始時期 */
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s4 s4_eqinjstpn[5];               /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポートn回目始動時噴射量（噴射回数配列） */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
    f4 f4_eqinjstpn[5];               /* unit=mg/st :ポートn回目始動時噴射量（噴射回数配列） */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s4 s4_eqinjstdn[6];               /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内n回目始動時噴射量（噴射回数配列） */ /* 始動時に最大6回噴射(直噴のみ) */
    f4 f4_eqinjstdn[6];               /* unit=mg/st :筒内n回目始動時噴射量（噴射回数配列） */ /* 始動時に最大6回噴射(直噴のみ) */
#endif /* JEEFI */
    s4 s4_eqfc[u1g_EJCC_NCYL];        /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :FC中噴射量 */
    f4 f4_eqfc[u1g_EJCC_NCYL];        /* unit=mg/st :FC中噴射量 */
    s2 s2_ek1fn[u1g_EJCC_NOX];        /* lsb=(1*4)/128/256,unit=倍 :1回目噴射量算出係数(バンク別) */
    f4 f4_ek1fn[u1g_EJCC_NOX];        /* unit=倍 :1回目噴射量算出係数(バンク別) */
    s2 s2_ek2fn[u1g_EJCC_NOX];        /* lsb=(1*4)/128/256,unit=倍 :2回目噴射量算出係数(バンク別) */
    f4 f4_ek2fn[u1g_EJCC_NOX];        /* unit=倍 :2回目噴射量算出係数(バンク別) */
    s2 s2_ek3fn[u1g_EJCC_NOX];        /* lsb=(1*4)/128/256,unit=倍 :3回目噴射量算出係数(バンク別) */
    f4 f4_ek3fn[u1g_EJCC_NOX];        /* unit=倍 :3回目噴射量算出係数(バンク別) */
    s2 s2_ekrchref[u1g_EJCC_NOX];     /* lsb=(32*2)/128/256,unit=倍 :噴射量補正係数(バンク別) */
    f4 f4_ekrchref[u1g_EJCC_NOX];     /* unit=倍 :噴射量補正係数(バンク別) */
    u1 bi_exqinjast :1;               /* lsb=1 :始動後噴射量要求フラグ */
    u1 bi_dummy     :7;               /* ダミー */
    u1 u1_exqinjast;                  /* lsb=1 :始動後噴射量要求フラグ */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    u1 u1_explreq;                    /* lsb=1 :PL噴射実施要求 */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL            /*【ﾃﾞｭｱﾙINJ】*/
    s2 s2_ekpfit;                     /* lsb=(1*4)/128/256,unit=倍 :目標ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
    f4 f4_ekpfit;                     /* unit=倍 :目標ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
    s2 s2_ekpfitn[u1g_EJCC_NOX];      /* lsb=(1*4)/128/256,unit=倍 :目標ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ別) */
    f4 f4_ekpfitn[u1g_EJCC_NOX];      /* unit=倍 :目標ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ別) */
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s2 s2_ek1fpt;                     /* lsb=(1*4)/128/256,unit=倍 :ﾎﾟｰﾄ噴射のみ要求時の目標ﾎﾟｰﾄ1回目噴射量算出係数 */
    f4 f4_ek1fpt;                     /* unit=倍 :ﾎﾟｰﾄ噴射のみ要求時の目標ﾎﾟｰﾄ1回目噴射量算出係数 */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL            /*【ﾃﾞｭｱﾙINJ】*/
 #if JEEGR == u1g_EJCC_USE            /*【EGR制御有】*/
    f4 f4_ekpfiegr;                   /* unit=倍 :EGR-ON時の目標ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
    f4 f4_ekpfiegrn[u1g_EJCC_NOX];    /* unit=倍 :EGR-ON時の目標ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ別) */
 #endif /* JEEGR */
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s2 s2_eainjcutp;                  /* lsb=1024/128/256,unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期 */
    f4 f4_eainjcutp;                  /* unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2 s2_eainjcutd;                  /* lsb=1024/128/256,unit=BTDC :筒内噴射強制ｶｯﾄ時期 */
    f4 f4_eainjcutd;                  /* unit=BTDC :筒内噴射強制ｶｯﾄ時期 */
#endif /* JEEFI */
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    s4 s4_eqinjexp;                   /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :膨張行程噴射量 */
    f4 f4_eqinjexp;                   /* unit=mg/st :膨張行程噴射量 */
#endif /* JECOMBCCPT_E */
    s4 s4_eqinjflfix[8];              /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :FL固定噴射量 */
    f4 f4_eqinjflfix[8];              /* unit=mg/st :FL固定噴射量 */
    s4 s4_eqinjplfix[8];              /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :PL固定噴射量 */
    f4 f4_eqinjplfix[8];              /* unit=mg/st :PL固定噴射量 */
} st_EMINJ_EMINJ;

/*-------------------------------------------------------------------*/
/* フリーポート用ヘッダファイルのインクルード                        */
/*-------------------------------------------------------------------*/
#include <engsrc/eactmedi/einj/eminj_c.h>

/*-------------------------------------------------------------------*/
/* コンパイルSW未定義チェック                                        */
/*-------------------------------------------------------------------*/
#if !defined EMINJ_STAHV_MEDI
#error "EMINJ_STAHV_MEDI is undeclared"
#endif

#if !defined EMINJ_FCFRCTRL_MEDI
#error "EMINJ_FCFRCTRL_MEDI is undeclared"
#endif

#if !defined EMINJ_STACM_MEDI
#error "EMINJ_STACM_MEDI is undeclared"
#endif

#if !defined EMINJ_ACTOBD_MEDI
#error "EMINJ_ACTOBD_MEDI is undeclared"
#endif

#if !defined EMINJ_IMBRQ_MEDI
#error "EMINJ_IMBRQ_MEDI is undeclared"
#endif

#if !defined EMINJ_MFINJRQ_MEDI
#error "EMINJ_MFINJRQ_MEDI is undeclared"
#endif

#if !defined EMINJ_FKGDRQ_MEDI
#error "EMINJ_FKGDRQ_MEDI is undeclared"
#endif

#if !defined EMINJ_ACTLFG_MEDI
#error "EMINJ_ACTLFG_MEDI is undeclared"
#endif

#if !defined EMINJ_BINJPLCTR_MEDI
#error "EMINJ_BINJPLCTR_MEDI is undeclared"
#endif

#if !defined EMINJ_BINJPLCTR_WC_MEDI
#error "EMINJ_BINJPLCTR_WC_MEDI is undeclared"
#endif

#if !defined EMINJ_BINJPLCTR_STAHV_MEDI
#error "EMINJ_BINJPLCTR_STAHV_MEDI is undeclared"
#endif

/*-------------------------------------------------------------------*/
/* マクロ定義                                                        */
/*-------------------------------------------------------------------*/
/* $$$マクロ定数_標準_v4.11 */

#if (JEEFI == u1g_EJCC_D4)                                              /* 【D-4】 */
#define u4g_EMINJ_INJPTN_VD ((u4)(0x30000000U))                         /* m=eminj,lsb=,ofs=,unit= :噴射ﾊﾟﾀｰﾝ無効値 */

#else                                                                   /* 【D-4以外】 */
#define u4g_EMINJ_INJPTN_VD ((u4)(0x10000000U))                         /* m=eminj,lsb=,ofs=,unit= :噴射ﾊﾟﾀｰﾝ無効値 */
#endif                                                                  /* JEEFI */

#define u1g_EMINJ_PRINORQ ((u1)(((0.)/(1.))+0.5))                       /* m=eminj,lsb=1,ofs=,unit=- :優先要求無し判定値 */
#define u1g_EMINJ_NONE_ID ((u1)(((0.)/(1.))+0.5))                       /* m=eminj,lsb=1,ofs=,unit=- :噴射制御の優先調停要求無しID */

#if (JEMAT_BENCHI == u1g_EJCC_USE) || (JEMAT_BENCH_E == u1g_EJCC_USE)   /* 【ﾍﾞﾝﾁ適合用ｿﾌﾄ有】OR【ﾍﾞﾝﾁ適合ﾓｰﾄﾞ有】 */
#define u1g_EMINJ_BENCH_ID ((u1)(((2.)/(1.))+0.5))                      /* m=eminj,lsb=1,ofs=,unit=- :ﾍﾞﾝﾁ適合用噴射要求(ID) */
#endif                                                                  /* JEMAT_BENCHI JEMAT_BENCH_E */

#define u1g_EMINJ_EGSTPVS_ID ((u1)(((4.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :噴射停止(ID) */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
#define u1g_EMINJ_DEFLAIR_ID ((u1)(((6.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :工場ｴｱ抜き制御(ID) */
#endif                                                                  /* JEEFI */

#if (JEEGMG_E == u1g_EJCC_HVPLGR_E) || (JEEGMG_E == u1g_EJCC_HVDIRECT_E)    /* 【EG-MG遊星ｷﾞｱ】OR【EG-MG直結】 */
#define u1g_EMINJ_STPHV_ID ((u1)(((12.)/(1.))+0.5))                     /* m=eminj,lsb=1,ofs=,unit=- :HV停止制御(ID) */
#endif                                                                  /* JEEGMG_E */

#if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E)         /* 【SS制御有】OR【EG-MGｸﾗｯﾁ】 */
#define u1g_EMINJ_STPSS_ID ((u1)(((14.)/(1.))+0.5))                     /* m=eminj,lsb=1,ofs=,unit=- :SS停止制御(ID) */
#endif                                                                  /* JESS JEEGMG_E */

#define u1g_EMINJ_RDNVES_ID ((u1)(((16.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ｴﾝｼﾞﾝ停止・始動時の振動低減制御(ID) */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                  /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
#define u1g_EMINJ_SJC_ID ((u1)(((20.)/(1.))+0.5))                       /* m=eminj,lsb=1,ofs=,unit=- :触媒急速暖機制御(ID) */
#endif                                                                  /* JEEFI */

#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_WC_MEDI == ON)   /* 【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】 */
#define u1g_EMINJ_BINJPLCTR_WC_ID ((u1)(((22.)/(1.))+0.5))              /* m=eminj,lsb=1,ofs=,unit=- :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)(ID) */
#endif                                                                  /* JEALLHV_E JEPLMLT_E EMINJ_BINJPLCTR_WC_MEDI */

#if JEALLHV_E == u1g_EJCC_ALLHV_E                                       /* 【ALL HV】 */
#define u1g_EMINJ_WUPCAT_ID ((u1)(((24.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :触媒暖機制御(ID) */
#endif                                                                  /* JEALLHV_E */

#if (JENGPF_E != u1g_EJCC_NOT_USE) && (EMINJ_FCFRCTRL_MEDI == ON)       /* 【GPF有】AND【1気筒FC制御要求使用】 */
#define u1g_EMINJ_FCFRCTRL_ID ((u1)(((26.)/(1.))+0.5))                  /* m=eminj,lsb=1,ofs=,unit=- :1気筒FC制御(ID) */
#endif                                                                  /* JENGPF_E EMINJ_FCFRCTRL_MEDI */

#if ((JERMTCTR == u1g_EJCC_USE) || (JENVCTR == u1g_EJCC_USE)) && (JEMICN_E != u1g_EJCC_SUB_E) && (EMINJ_STACM_MEDI == ON)   /* (【ﾘﾓｰﾄｺﾝﾄﾛｰﾙ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】)AND【SUB-CPU以外】AND【始動時吹け上がり制御要求使用】 */
#define u1g_EMINJ_STACM_ID ((u1)(((28.)/(1.))+0.5))                     /* m=eminj,lsb=1,ofs=,unit=- :始動時吹け上がり制御(ID) */
#endif                                                                  /* JERMTCTR JENVCTR JEMICN_E EMINJ_STACM_MEDI */

#if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E)         /* 【SS制御有】OR【EG-MGｸﾗｯﾁ】 */
#define u1g_EMINJ_STASS_ID ((u1)(((30.)/(1.))+0.5))                     /* m=eminj,lsb=1,ofs=,unit=- :SS始動制御(ID) */
#endif                                                                  /* JESS JEEGMG_E */

#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT)         /* 【ALL HV】AND【ﾎﾟｰﾄ】 */
#define u1g_EMINJ_RDPN_ST_ID ((u1)(((36.)/(1.))+0.5))                   /* m=eminj,lsb=1,ofs=,unit=- :PN低減制御(始動時)(ID) */
#endif                                                                  /* JEALLHV_E JEEFI */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                  /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
#define u1g_EMINJ_STRATIST_ID ((u1)(((42.)/(1.))+0.5))                  /* m=eminj,lsb=1,ofs=,unit=- :成層始動制御(ID) */
#endif                                                                  /* JEEFI */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
#define u1g_EMINJ_STAFRG_ID ((u1)(((44.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :極低温始動制御(ID) */
#endif                                                                  /* JEEFI */

#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (EMINJ_STAHV_MEDI == ON)         /* 【ALL HV】AND【HV始動制御要求使用】 */
#define u1g_EMINJ_STAHV_ID ((u1)(((46.)/(1.))+0.5))                     /* m=eminj,lsb=1,ofs=,unit=- :HV始動制御(ID) */
#endif                                                                  /* JEALLHV_E EMINJ_STAHV_MEDI */

#if (JEEGMG_E == u1g_EJCC_HVPLGR_E) && (JEFFV == u1g_EJCC_NOT_USE) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_STAHV_MEDI == ON) /* 【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】 */
#define u1g_EMINJ_BINJPLCTR_STAHV_ID ((u1)(((48.)/(1.))+0.5))           /* m=eminj,lsb=1,ofs=,unit=- :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)(ID) */
#endif                                                                  /* JEEGMG_E JEFFV JEPLMLT_E EMINJ_BINJPLCTR_STAHV_MEDI */

#define u1g_EMINJ_FCINJCTR_ID ((u1)(((50.)/(1.))+0.5))                  /* m=eminj,lsb=1,ofs=,unit=- :FC中燃料噴射制御(ID) */

#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI != u1g_EJCC_D4)           /* 【ALL HV】AND【D-4以外】 */
#define u1g_EMINJ_RDPN_ID ((u1)(((52.)/(1.))+0.5))                      /* m=eminj,lsb=1,ofs=,unit=- :PN低減制御(ID) */
#endif                                                                  /* JEALLHV_E JEEFI */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
#define u1g_EMINJ_DTHRCTRL_ID ((u1)(((64.)/(1.))+0.5))                  /* m=eminj,lsb=1,ofs=,unit=- :気筒別ﾃﾞｨｻﾞ制御(ID) */
#endif                                                                  /* JEEFI */

#if ((JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)) && (EMINJ_ACTLFG_MEDI == ON)   /* (【ﾃﾞｭｱﾙINJ】OR【D-4】)AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】 */
#define u1g_EMINJ_ACTLFG_ID ((u1)(((66.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御(ID) */
#endif                                                                  /* JEEFI EMINJ_ACTLFG_MEDI */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
 #if EMINJ_ACTOBD_MEDI == ON                                            /* 【ﾃﾞｭｱﾙINJ】AND【OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
#define u1g_EMINJ_ACTOBD_ID ((u1)(((76.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :OBD要求によるｱｸﾃｨﾌﾞ制御(ID) */
 #endif                                                                 /* EMINJ_ACTOBD_MEDI */

#define u1g_EMINJ_ACTGAF_ID ((u1)(((84.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :A/F学習の為のｱｸﾃｨﾌﾞ制御(ID) */

 #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_IMBRQ_MEDI == ON)         /* 【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ﾃﾞｭｱﾙINJ】AND【ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
#define u1g_EMINJ_IMBRQ_ID ((u1)(((78.)/(1.))+0.5))                     /* m=eminj,lsb=1,ofs=,unit=- :ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御(ID) */
 #endif                                                                 /* JEOBDAFIMB_D EMINJ_IMBRQ_MEDI */

 #if (JEOBDMF == u1g_EJCC_USE) && (EMINJ_MFINJRQ_MEDI == ON)            /* 【失火OBD有】AND【ﾃﾞｭｱﾙINJ】AND【失火OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
#define u1g_EMINJ_MFINJRQ_ID ((u1)(((80.)/(1.))+0.5))                   /* m=eminj,lsb=1,ofs=,unit=- :失火OBD要求によるｱｸﾃｨﾌﾞ制御(ID) */
 #endif                                                                 /* JEOBDMF EMINJ_MFINJRQ_MEDI */

 #if (JEOBDFKG == u1g_EJCC_USE) && (EMINJ_FKGDRQ_MEDI == ON)            /* 【燃料OBD有】AND【ﾃﾞｭｱﾙINJ】AND【燃料系OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
#define u1g_EMINJ_FKGDRQ_ID ((u1)(((82.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :燃料系OBD要求によるｱｸﾃｨﾌﾞ制御(ID) */
 #endif                                                                 /* JEOBDFKG EMINJ_FKGDRQ_MEDI */
#endif                                                                  /* JEEFI */

#if (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_MEDI == ON)         /* 【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】 */
#define u1g_EMINJ_BINJPLCTR_ID ((u1)(((98.)/(1.))+0.5))                 /* m=eminj,lsb=1,ofs=,unit=- :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(ID) */
#endif                                                                  /* JEPLMLT_E EMINJ_BINJPLCTR_MEDI */

#if EMINJ_FREE0 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ0使用】 */
#define u1g_EMINJ_FREE0_ID ((u1)(((200.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ0用制御(ID) */
#endif                                                                  /* EMINJ_FREE0 */

#if EMINJ_FREE1 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ1使用】 */
#define u1g_EMINJ_FREE1_ID ((u1)(((201.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ1用制御(ID) */
#endif                                                                  /* EMINJ_FREE1 */

#if EMINJ_FREE2 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ2使用】 */
#define u1g_EMINJ_FREE2_ID ((u1)(((202.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ2用制御(ID) */
#endif                                                                  /* EMINJ_FREE2 */

#if EMINJ_FREE3 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ3使用】 */
#define u1g_EMINJ_FREE3_ID ((u1)(((203.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ3用制御(ID) */
#endif                                                                  /* EMINJ_FREE3 */

#if EMINJ_FREE4 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ4使用】 */
#define u1g_EMINJ_FREE4_ID ((u1)(((204.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ4用制御(ID) */
#endif                                                                  /* EMINJ_FREE4 */

#if EMINJ_FREE5 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ5使用】 */
#define u1g_EMINJ_FREE5_ID ((u1)(((205.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ5用制御(ID) */
#endif                                                                  /* EMINJ_FREE5 */

#if EMINJ_FREE6 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ6使用】 */
#define u1g_EMINJ_FREE6_ID ((u1)(((206.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ6用制御(ID) */
#endif                                                                  /* EMINJ_FREE6 */

#if EMINJ_FREE7 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ7使用】 */
#define u1g_EMINJ_FREE7_ID ((u1)(((207.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ7用制御(ID) */
#endif                                                                  /* EMINJ_FREE7 */

#if EMINJ_FREE8 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ8使用】 */
#define u1g_EMINJ_FREE8_ID ((u1)(((208.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ8用制御(ID) */
#endif                                                                  /* EMINJ_FREE8 */

#if EMINJ_FREE9 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ9使用】 */
#define u1g_EMINJ_FREE9_ID ((u1)(((209.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ9用制御(ID) */
#endif                                                                  /* EMINJ_FREE9 */

#if EMINJ_FREE10 == ON                                                  /* 【ﾌﾘｰﾎﾟｰﾄ10使用】 */
#define u1g_EMINJ_FREE10_ID ((u1)(((210.)/(1.))+0.5))                   /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ10用制御(ID) */
#endif                                                                  /* EMINJ_FREE10 */

#if EMINJ_FREE11 == ON                                                  /* 【ﾌﾘｰﾎﾟｰﾄ11使用】 */
#define u1g_EMINJ_FREE11_ID ((u1)(((211.)/(1.))+0.5))                   /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ11用制御(ID) */
#endif                                                                  /* EMINJ_FREE11 */

#define u4g_EMINJ_RQID_VD ((u4)(0x00000000U))                           /* m=eminj,lsb=,ofs=,unit= :要求有識別子無効値 */
#define u4g_EMINJ_RQINJMODE ((u4)(0x00000001U))                         /* m=eminj,lsb=,ofs=,unit= :噴射ﾓｰﾄﾞ要求有 */
#define u4g_EMINJ_RQINJPTN ((u4)(0x00000002U))                          /* m=eminj,lsb=,ofs=,unit= :噴射ﾊﾟﾀｰﾝ要求有 */
#define u4g_EMINJ_RQAINJP1 ((u4)(0x00000002U))                          /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄ1回目噴射開始時期要求有 */
#define u4g_EMINJ_RQAINJPN ((u4)(0x00000004U))                          /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄn回目噴射開始時期要求有（噴射毎） */
#define u4g_EMINJ_RQAINJP2 ((u4)(0x00000004U))                          /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄ2回目噴射開始時期要求有 */
#define u4g_EMINJ_RQAINJDN ((u4)(0x00000008U))                          /* m=eminj,lsb=,ofs=,unit= :筒内n回目噴射開始時期要求有（噴射毎） */
#define u4g_EMINJ_RQAINJP3 ((u4)(0x00000008U))                          /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄ3回目噴射開始時期要求有 */
#define u4g_EMINJ_RQAINJP4 ((u4)(0x00000010U))                          /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄ4回目噴射開始時期要求有 */
#define u4g_EMINJ_RQINJEND ((u4)(0x00000020U))                          /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄ噴射終了時期要求有 */
#define u4g_EMINJ_RQAINJCUTP ((u4)(0x00000040U))                        /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期要求 */
#define u4g_EMINJ_RQAINJCUTD ((u4)(0x00000080U))                        /* m=eminj,lsb=,ofs=,unit= :筒内噴射強制ｶｯﾄ時期要求 */
#define u4g_EMINJ_RQAINJD1 ((u4)(0x00000100U))                          /* m=eminj,lsb=,ofs=,unit= :筒内1回目噴射開始時期要求有 */
#define u4g_EMINJ_RQAINJD2 ((u4)(0x00000200U))                          /* m=eminj,lsb=,ofs=,unit= :筒内2回目噴射開始時期要求有 */
#define u4g_EMINJ_RQAINJD3 ((u4)(0x00000008U))                          /* m=eminj,lsb=,ofs=,unit= :筒内3回目噴射開始時期要求有 */
#define u4g_EMINJ_RQAINJD4 ((u4)(0x00000010U))                          /* m=eminj,lsb=,ofs=,unit= :筒内4回目噴射開始時期要求有 */
#define u4g_EMINJ_RQQINJSTPN ((u4)(0x00000400U))                        /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄn回目始動時噴射量要求有（噴射毎） */
#define u4g_EMINJ_RQQINJSTP1 ((u4)(0x00000400U))                        /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄ1回目始動時噴射量要求有 */
#define u4g_EMINJ_RQQINJSTDN ((u4)(0x00000800U))                        /* m=eminj,lsb=,ofs=,unit= :筒内n回目始動時噴射量要求有（噴射毎） */
#define u4g_EMINJ_RQQINJSTP2 ((u4)(0x00000800U))                        /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄ2回目始動時噴射量要求有 */
#define u4g_EMINJ_RQQINJFLFIX ((u4)(0x00001000U))                       /* m=eminj,lsb=,ofs=,unit= :FL固定噴射量要求有（噴射毎） */
#define u4g_EMINJ_RQQINJSTP3 ((u4)(0x00001000U))                        /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄ3回目始動時噴射量要求有 */
#define u4g_EMINJ_RQQINJPLFIX ((u4)(0x00002000U))                       /* m=eminj,lsb=,ofs=,unit= :PL固定噴射量要求有（噴射毎） */
#define u4g_EMINJ_RQQINJSTP4 ((u4)(0x00002000U))                        /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄ4回目始動時噴射量要求有 */
#define u4g_EMINJ_RQQINJSTD1 ((u4)(0x00004000U))                        /* m=eminj,lsb=,ofs=,unit= :筒内1回目始動時噴射量要求有 */
#define u4g_EMINJ_RQQINJSTD2 ((u4)(0x00008000U))                        /* m=eminj,lsb=,ofs=,unit= :筒内2回目始動時噴射量要求有 */
#define u4g_EMINJ_RQQINJSTD3 ((u4)(0x00001000U))                        /* m=eminj,lsb=,ofs=,unit= :筒内3回目始動時噴射量要求有 */
#define u4g_EMINJ_RQQINJSTD4 ((u4)(0x00002000U))                        /* m=eminj,lsb=,ofs=,unit= :筒内4回目始動時噴射量要求有 */
#define u4g_EMINJ_RQQFC ((u4)(0x00010000U))                             /* m=eminj,lsb=,ofs=,unit= :FC中噴射量要求有 */
#define u4g_EMINJ_RQQINJEXP ((u4)(0x00020000U))                         /* m=eminj,lsb=,ofs=,unit= :膨張行程噴射量要求有 */
#define u4g_EMINJ_RQK1FN ((u4)(0x00040000U))                            /* m=eminj,lsb=,ofs=,unit= :1回目噴射量算出係数要求有(ﾊﾞﾝｸ別) */
#define u4g_EMINJ_RQK2FN ((u4)(0x00080000U))                            /* m=eminj,lsb=,ofs=,unit= :2回目噴射量算出係数要求有(ﾊﾞﾝｸ別) */
#define u4g_EMINJ_RQK3FN ((u4)(0x00100000U))                            /* m=eminj,lsb=,ofs=,unit= :3回目噴射量算出係数要求有(ﾊﾞﾝｸ別) */
#define u4g_EMINJ_RQK1F ((u4)(0x00200000U))                             /* m=eminj,lsb=,ofs=,unit= :1回目噴射量算出係数要求有 */
#define u4g_EMINJ_RQK2F ((u4)(0x00400000U))                             /* m=eminj,lsb=,ofs=,unit= :2回目噴射量算出係数要求有 */
#define u4g_EMINJ_RQK3F ((u4)(0x00800000U))                             /* m=eminj,lsb=,ofs=,unit= :3回目噴射量算出係数要求有 */
#define u4g_EMINJ_RQPRREQ ((u4)(0x01000000U))                           /* m=eminj,lsb=,ofs=,unit= :高圧ﾎﾟﾝﾌﾟ目標燃圧要求有 */
#define u4g_EMINJ_RQQFREQ ((u4)(0x02000000U))                           /* m=eminj,lsb=,ofs=,unit= :燃料ﾎﾟﾝﾌﾟ吐出量要求有 */
#define u4g_EMINJ_RQPRREQL ((u4)(0x04000000U))                          /* m=eminj,lsb=,ofs=,unit= :低圧ﾎﾟﾝﾌﾟ目標燃圧要求有 */
#define u4g_EMINJ_RQXQINJAST ((u4)(0x08000000U))                        /* m=eminj,lsb=,ofs=,unit= :始動後噴射量要求ﾌﾗｸﾞ要求有 */
#define u4g_EMINJ_RQKRCHREF ((u4)(0x10000000U))                         /* m=eminj,lsb=,ofs=,unit= :噴射量補正係数要求有 */
#define u4g_EMINJ_RQPLREQ ((u4)(0x20000000U))                           /* m=eminj,lsb=,ofs=,unit= :PL噴射実施要求有 */
#define u4g_EMINJ_RQAINJP ((u4)(0x40000000U))                           /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄ噴射開始時期要求有 */
#define u4g_EMINJ_RQQINJSTP ((u4)(0x80000000U))                         /* m=eminj,lsb=,ofs=,unit= :ﾎﾟｰﾄ始動時噴射量要求有 */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                  /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
#define u2g_EMINJ_MOD0N1 ((u2)(0x0081U))                                /* m=eminj,lsb=,ofs=,unit= :筒内噴射N回(特殊要求) */
#endif                                                                  /* JEEFI */

#define u2g_EMINJ_MOD002 ((u2)(0x0002U))                                /* m=eminj,lsb=,ofs=,unit= :筒内噴射（触媒急速暖機） */
#define u2g_EMINJ_MOD003 ((u2)(0x0003U))                                /* m=eminj,lsb=,ofs=,unit= :筒内噴射（成層始動） */
#define u2g_EMINJ_MOD004 ((u2)(0x0004U))                                /* m=eminj,lsb=,ofs=,unit= :燃焼向上成層燃焼制御 */
#define u2g_EMINJ_MOD005 ((u2)(0x0005U))                                /* m=eminj,lsb=,ofs=,unit= :筒内噴射（触媒急速暖機：膨張行程噴射） */
#define u2g_EMINJ_MOD006 ((u2)(0x0006U))                                /* m=eminj,lsb=,ofs=,unit= :筒内噴射（成層始動：膨張行程噴射） */
#define u2g_EMINJ_MOD007 ((u2)(0x0007U))                                /* m=eminj,lsb=,ofs=,unit= :任意固定ﾏﾙﾁ噴射 */
/* $$$マクロ定数_標準_v4.11 */

/*-------------------------------------------------------------------*/
/* 関数                                                              */
/*-------------------------------------------------------------------*/
void vdg_eminj_pwon( void );            /* 初期値設定 */
                                        /* コール元 : vdg_elmng_pwon() */
                                        /* 事前初期化 : vdg_emprlp_pwon()【可変燃圧制御有】*/
                                        /*            : vdg_ebinjctr_pwon_seq()【D-4以外】*/

void vdg_eminj_8msm( void );            /* 噴射要求の調停処理 */
                                        /* コール元 : vdg_elmng_8msm() */

void vdg_eminj_einj_dataget( st_EMINJ_EINJ *ptt_retval );   /* 噴射情報取得処理（構造体1） */
                                                            /* コール元 :噴射SAC、APL */
                                                            /* 引数 ptt_retval :噴射情報取得バッファ（構造体1）のアドレス */

void vdg_eminj_eminj_dataget( st_EMINJ_EMINJ *ptt_retval ); /* 噴射情報取得処理（構造体2） */
                                                            /* コール元 :噴射SAC、APL */
                                                            /* 引数 ptt_retval :噴射情報取得バッファ（構造体2）のアドレス */

/*-------------------------------------------------------------------*/
/* 公開変数                                                          */
/*-------------------------------------------------------------------*/
extern st_EMINJ_EINJ stg_eminj_einj;                        /* 噴射方式調停構造体 */
#define u2g_eminj_einjmod   (stg_eminj_einj.u2_einjmod)     /* m=eminj,lsb=1 :噴射モード */
                                                            /* 更新タイミング ： pwon,8msm */

#define s2g_eminj_eainjp1   (stg_eminj_einj.s2_eainjp1)     /* m=eminj,lsb=1024/128/256,unit=BTDC :ポート1回目噴射開始時期 */
#define f4g_eminj_eainjp1   (stg_eminj_einj.f4_eainjp1)     /* m=eminj,unit=BTDC :ポート1回目噴射開始時期 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【D-4以外】*/

#define s2g_eminj_eainjp2   (stg_eminj_einj.s2_eainjp2)     /* m=eminj,lsb=1024/128/256,unit=BTDC :ポート2回目噴射開始時期 */
#define f4g_eminj_eainjp2   (stg_eminj_einj.f4_eainjp2)     /* m=eminj,unit=BTDC :ポート2回目噴射開始時期 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【D-4以外】*/

#define s2g_eminj_eainjp3   (stg_eminj_einj.s2_eainjp3)     /* m=eminj,lsb=1024/128/256,unit=BTDC :ポート3回目噴射開始時期 */
#define f4g_eminj_eainjp3   (stg_eminj_einj.f4_eainjp3)     /* m=eminj,unit=BTDC :ポート3回目噴射開始時期 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【D-4以外】*/

#define s2g_eminj_eainjp4   (stg_eminj_einj.s2_eainjp4)     /* m=eminj,lsb=1024/128/256,unit=BTDC :ポート4回目噴射開始時期 */
#define f4g_eminj_eainjp4   (stg_eminj_einj.f4_eainjp4)     /* m=eminj,unit=BTDC :ポート4回目噴射開始時期 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【D-4以外】*/

#define s2g_eminj_einjend   (stg_eminj_einj.s2_einjend)     /* m=eminj,lsb=1024/128/256,unit=BTDC :ポート噴射終了時期 */
extern f4 f4g_eminj_einjend;                                /* m=eminj,unit=BTDC :ポート噴射終了時期 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【D-4以外】*/
                                                            /*          : 従来より参照している部品のオブジェクトが変わるためf4型変数はマクロ定義への変更禁止 */

#define s2g_eminj_eainjcutp (stg_eminj_einj.s2_eainjcutp)   /* m=eminj,lsb=1024/128/256,unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期 */
#define f4g_eminj_eainjcutp (stg_eminj_einj.f4_eainjcutp)   /* m=eminj,unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【D-4以外】*/

#define s2g_eminj_eainjd1   (stg_eminj_einj.s2_eainjd1)     /* m=eminj,lsb=1024/128/256,unit=BTDC :筒内1回目噴射開始時期 */
#define f4g_eminj_eainjd1   (stg_eminj_einj.f4_eainjd1)     /* m=eminj,unit=BTDC :筒内1回目噴射開始時期 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

#define s2g_eminj_eainjd2   (stg_eminj_einj.s2_eainjd2)     /* m=eminj,lsb=1024/128/256,unit=BTDC :筒内2回目噴射開始時期 */
#define f4g_eminj_eainjd2   (stg_eminj_einj.f4_eainjd2)     /* m=eminj,unit=BTDC :筒内2回目噴射開始時期 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

#define s2g_eminj_eainjd3   (stg_eminj_einj.s2_eainjd3)     /* m=eminj,lsb=1024/128/256,unit=BTDC :筒内3回目噴射開始時期 */
#define f4g_eminj_eainjd3   (stg_eminj_einj.f4_eainjd3)     /* m=eminj,unit=BTDC :筒内3回目噴射開始時期 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

#define s2g_eminj_eainjd4   (stg_eminj_einj.s2_eainjd4)     /* m=eminj,lsb=1024/128/256,unit=BTDC :筒内4回目噴射開始時期 */
#define f4g_eminj_eainjd4   (stg_eminj_einj.f4_eainjd4)     /* m=eminj,unit=BTDC :筒内4回目噴射開始時期 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

#define s2g_eminj_eainjcutd (stg_eminj_einj.s2_eainjcutd)   /* m=eminj,lsb=1024/128/256,unit=BTDC :筒内噴射強制ｶｯﾄ時期 */
#define f4g_eminj_eainjcutd (stg_eminj_einj.f4_eainjcutd)   /* m=eminj,unit=BTDC :筒内噴射強制ｶｯﾄ時期 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

#define s4g_eminj_eqinjstp1 (stg_eminj_einj.s4_eqinjstp1)   /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート1回目始動時噴射量 */
#define f4g_eminj_eqinjstp1 (stg_eminj_einj.f4_eqinjstp1)   /* m=eminj,unit=mg/st :ポート1回目始動時噴射量 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【D-4以外】*/

#define s4g_eminj_eqinjstp2 (stg_eminj_einj.s4_eqinjstp2)   /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート2回目始動時噴射量 */
#define f4g_eminj_eqinjstp2 (stg_eminj_einj.f4_eqinjstp2)   /* m=eminj,unit=mg/st :ポート2回目始動時噴射量 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【D-4以外】*/

#define s4g_eminj_eqinjstp3 (stg_eminj_einj.s4_eqinjstp3)   /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート3回目始動時噴射量 */
#define f4g_eminj_eqinjstp3 (stg_eminj_einj.f4_eqinjstp3)   /* m=eminj,unit=mg/st :ポート3回目始動時噴射量 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【D-4以外】*/

#define s4g_eminj_eqinjstp4 (stg_eminj_einj.s4_eqinjstp4)   /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート4回目始動時噴射量 */
#define f4g_eminj_eqinjstp4 (stg_eminj_einj.f4_eqinjstp4)   /* m=eminj,unit=mg/st :ポート4回目始動時噴射量 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【D-4以外】*/

#define s4g_eminj_eqinjstd1 (stg_eminj_einj.s4_eqinjstd1)   /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内1回目始動時噴射量 */
extern f4 f4g_eminj_eqinjstd1;                              /* m=eminj,unit=mg/st :筒内1回目始動時噴射量 */

                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/
                                                            /*          : 従来より参照している部品のオブジェクトが変わるためf4型変数はマクロ定義への変更禁止 */

#define s4g_eminj_eqinjstd2 (stg_eminj_einj.s4_eqinjstd2)   /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内2回目始動時噴射量 */
extern f4 f4g_eminj_eqinjstd2;                              /* m=eminj,unit=mg/st :筒内2回目始動時噴射量 */

                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/
                                                            /*          : 従来より参照している部品のオブジェクトが変わるためf4型変数はマクロ定義への変更禁止 */

#define s4g_eminj_eqinjstd3 (stg_eminj_einj.s4_eqinjstd3)   /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内3回目始動時噴射量 */
extern f4 f4g_eminj_eqinjstd3;                              /* m=eminj,unit=mg/st :筒内3回目始動時噴射量 */

                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/
                                                            /*          : 従来より参照している部品のオブジェクトが変わるためf4型変数はマクロ定義への変更禁止 */

#define s4g_eminj_eqinjstd4 (stg_eminj_einj.s4_eqinjstd4)   /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内4回目始動時噴射量 */
extern f4 f4g_eminj_eqinjstd4;                              /* m=eminj,unit=mg/st :筒内4回目始動時噴射量 */

                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/
                                                            /*          : 従来より参照している部品のオブジェクトが変わるためf4型変数はマクロ定義への変更禁止 */

extern s4 s4g_eminj_eqfc[u1g_EJCC_NCYL];                    /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :FC中噴射量 */
extern f4 f4g_eminj_eqfc[u1g_EJCC_NCYL];                    /* m=eminj,unit=mg/st :FC中噴射量 */
                                                            /* 更新タイミング ： pwon,8msm */

#define s4g_eminj_eqinjexp  (stg_eminj_einj.s4_eqinjexp)    /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :膨張行程噴射量 */
#define f4g_eminj_eqinjexp  (stg_eminj_einj.f4_eqinjexp)    /* m=eminj,unit=mg/st :膨張行程噴射量 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/

#define s2g_eminj_ek1f      (stg_eminj_einj.s2_ek1f)        /* m=eminj,lsb=(1*4)/128/256,unit=倍 :1回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
#define f4g_eminj_ek1f      (stg_eminj_einj.f4_ek1f)        /* m=eminj,unit=倍 :1回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
                                                            /* 更新タイミング ： pwon,8msm */

#define s2g_eminj_ek2f      (stg_eminj_einj.s2_ek2f)        /* m=eminj,lsb=(1*4)/128/256,unit=倍 :2回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
#define f4g_eminj_ek2f      (stg_eminj_einj.f4_ek2f)        /* m=eminj,unit=倍 :2回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
                                                            /* 更新タイミング ： pwon,8msm */

#define s2g_eminj_ek3f      (stg_eminj_einj.s2_ek3f)        /* m=eminj,lsb=(1*4)/128/256,unit=倍 :3回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
#define f4g_eminj_ek3f      (stg_eminj_einj.f4_ek3f)        /* m=eminj,unit=倍 :3回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
                                                            /* 更新タイミング ： pwon,8msm */

extern s2 s2g_eminj_ek1fn[u1g_EJCC_NOX];                    /* m=eminj,lsb=(1*4)/128/256,unit=倍 :1回目噴射量算出係数(バンク別) */
extern f4 f4g_eminj_ek1fn[u1g_EJCC_NOX];                    /* m=eminj,unit=倍 :1回目噴射量算出係数(バンク別) */
                                                            /* 更新タイミング ： pwon,8msm */

extern s2 s2g_eminj_ek2fn[u1g_EJCC_NOX];                    /* m=eminj,lsb=(1*4)/128/256,unit=倍 :2回目噴射量算出係数(バンク別) */
extern f4 f4g_eminj_ek2fn[u1g_EJCC_NOX];                    /* m=eminj,unit=倍 :2回目噴射量算出係数(バンク別) */
                                                            /* 更新タイミング ： pwon,8msm */

extern s2 s2g_eminj_ek3fn[u1g_EJCC_NOX];                    /* m=eminj,lsb=(1*4)/128/256,unit=倍 :3回目噴射量算出係数(バンク別)  */
extern f4 f4g_eminj_ek3fn[u1g_EJCC_NOX];                    /* m=eminj,unit=倍 :3回目噴射量算出係数(バンク別)  */
                                                            /* 更新タイミング ： pwon,8msm */

extern f4 f4g_eminj_ek1ffix;                                /* m=eminj,unit=倍 :確定1回目噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
                                                            /* 更新タイミング ： 8msm */

extern f4 f4g_eminj_ek2ffix;                                /* m=eminj,unit=倍 :確定2回目噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
                                                            /* 更新タイミング ： 8msm */

extern f4 f4g_eminj_ek3ffix;                                /* m=eminj,unit=倍 :確定3回目噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
                                                            /* 更新タイミング ： 8msm */

#define big_eminj_exqinjast (stg_eminj_einj.bi_exqinjast)   /* m=eminj,lsb=1 :始動後噴射量要求フラグ */
#define u1g_eminj_exqinjast ((u1)stg_eminj_einj.bi_exqinjast)   /* m=eminj,lsb=1 :始動後噴射量要求フラグ */
                                                            /* 更新タイミング : pwon,8msm */
                                                            /* 注意事項 : ON = 始動後噴射量要求有 */

#define u1g_eminj_explreq   (stg_eminj_einj.u1_explreq)     /* m=eminj,lsb=1 :PL噴射実施要求 */
                                                            /* 更新タイミング : pwon,8msm */
                                                            /* 注意事項 : ON = PL噴射実施要求有 */
                                                            /*          :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

#define f4g_eminj_ekpfit    (stg_eminj_einj.f4_ekpfit)      /* m=eminj,unit=倍 :目標ポート噴射量算出係数(バンク間平均値(ツインセンサ)) */
extern s2 s2g_eminj_ekpfit;                                 /* m=eminj,lsb=(1*4)/128/256,unit=倍 :目標ポート噴射量算出係数(バンク間平均値(ツインセンサ)) */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】*/
                                                            /*          : 従来より参照している部品のオブジェクトが変わるためs2型変数はマクロ定義への変更禁止 */

extern s2 s2g_eminj_ekpfitn[u1g_EJCC_NOX];                  /* m=eminj,lsb=(1*4)/128/256,unit=倍 :目標ポート噴射量算出係数(バンク別) */
extern f4 f4g_eminj_ekpfitn[u1g_EJCC_NOX];                  /* m=eminj,unit=倍 :目標ポート噴射量算出係数(バンク別) */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】*/

#define s2g_eminj_ek1fpt    (stg_eminj_einj.s2_ek1fpt)      /* m=eminj,lsb=(1*4)/128/256,unit=倍 :ﾎﾟｰﾄ噴射のみ要求時の目標ﾎﾟｰﾄ1回目噴射量算出係数 */
#define f4g_eminj_ek1fpt    (stg_eminj_einj.f4_ek1fpt)      /* m=eminj,unit=倍 :ﾎﾟｰﾄ噴射のみ要求時の目標ﾎﾟｰﾄ1回目噴射量算出係数 */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【D-4以外】*/

#define f4g_eminj_ekpfiegr  (stg_eminj_einj.f4_ekpfiegr)    /* m=eminj,unit=倍 :EGR-ON時の目標ポート噴射量算出係数(バンク間平均値(ツインセンサ)) */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】AND【EGR制御有】*/

extern f4 f4g_eminj_ekpfiegrn[u1g_EJCC_NOX];                /* m=eminj,unit=倍 :EGR-ON時の目標ポート噴射量算出係数(バンク別) */
                                                            /* 更新タイミング ： pwon,8msm */
                                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】AND【EGR制御有】*/

extern u2 u2g_eminj_einjmodfix;             /* m=eminj,lsb=1 :現在確定噴射ﾓｰﾄﾞ */
                                            /* 更新タイミング : 8msm */

extern s2 s2g_eminj_ekpfix;                 /* m=eminj,lsb=(1*4)/128/256,unit=倍 :ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
extern f4 f4g_eminj_ekpfix;                 /* m=eminj,unit=倍 :ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
                                            /* 更新タイミング : pwon,8msm */

extern s2 s2g_eminj_ekpfi;                  /* m=eminj,lsb=(1*4)/128/256,unit=倍 :ポート噴射量算出係数(バンク間平均値(ツインセンサ)) */
extern f4 f4g_eminj_ekpfi;                  /* m=eminj,unit=倍 :ポート噴射量算出係数(バンク間平均値(ツインセンサ)) */
                                            /* 更新タイミング : pwon,8msm */

extern s2 s2g_eminj_ekpfin[u1g_EJCC_NOX];   /* m=eminj,lsb=(1*4)/128/256,unit=倍 :ポート噴射量算出係数(バンク別) */
extern f4 f4g_eminj_ekpfin[u1g_EJCC_NOX];   /* m=eminj,unit=倍 :ポート噴射量算出係数(バンク別) */
                                            /* 更新タイミング : pwon,8msm */

extern s2 s2g_eminj_eprreq;                 /* m=eminj,lsb=(32*2)/128/256,unit=MPa :高圧ポンプ目標燃圧 */
extern f4 f4g_eminj_eprreq;                 /* m=eminj,unit=MPa :高圧ポンプ目標燃圧 */
                                            /* 更新タイミング : 8msm */
                                            /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

extern s2 s2g_eminj_eqfreq;                 /* m=eminj,lsb=512/128/256,unit=L/h :燃料ポンプ吐出流量 */
                                            /* 更新タイミング : 8msm */
                                            /* 注意事項 :【可変燃圧制御無】*/

extern s2 s2g_eminj_eprreql;                /* m=eminj,lsb=1280/128/256,unit=kPa :低圧ポンプ目標燃圧 */
extern f4 f4g_eminj_eprreql;                /* m=eminj,unit=kPa :低圧ポンプ目標燃圧 */
                                            /* 更新タイミング : pwon,8msm */
                                            /* 注意事項 :【可変燃圧制御有】*/

extern s2 s2g_eminj_ekrichx;                /* m=eminj,lsb=(32*2)/128/256,unit=倍 :噴射量補正係数 */
extern f4 f4g_eminj_ekrichx;                /* m=eminj,unit=倍 :噴射量補正係数 */
                                            /* 更新タイミング : pwon,8msm */

extern s2 s2g_eminj_ekrchref[u1g_EJCC_NOX]; /* m=eminj,lsb=(32*2)/128/256,unit=倍 :噴射量補正係数(バンク別) */
extern f4 f4g_eminj_ekrchref[u1g_EJCC_NOX]; /* m=eminj,unit=倍 :噴射量補正係数(バンク別) */
                                            /* 更新タイミング : pwon,8msm */

extern u1 u1g_eminj_einjmedislid;           /* m=eminj,lsb=1 :噴射方式反映識別子 */
                                            /* 更新タイミング : 8msm */

extern st_EMINJ_EMINJ stg_eminj_eminj;                              /* 噴射方式調停構造体 */

#define u4g_eminj_einjptn       (stg_eminj_eminj.u4_einjptn)        /* m=eminj,lsb=1 :噴射パターン */
                                                                    /* 更新タイミング : 8msm */

extern s2 s2g_eminj_eainjpn[5];                                     /* m=eminj,lsb=1024/128/256,unit=BTDC :ポートn回目噴射開始時期(噴射回数配列) */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
extern f4 f4g_eminj_eainjpn[5];                                     /* m=eminj,unit=BTDC :ポートn回目噴射開始時期(噴射回数配列) */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
                                                                    /* 更新タイミング ： pwon,8msm */
                                                                    /* 注意事項 :【D-4以外】*/

extern f4 f4g_eminj_eainjd1fix;                                     /* m=eminj,unit=BTDC :確定筒内1回目噴射開始時期 */
                                                                    /* 更新タイミング ： 8msm */
                                                                    /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

extern f4 f4g_eminj_eainjd2fix;                                     /* m=eminj,unit=BTDC :確定筒内2回目噴射開始時期 */
                                                                    /* 更新タイミング ： 8msm */
                                                                    /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

extern f4 f4g_eminj_eainjd3fix;                                     /* m=eminj,unit=BTDC :確定筒内3回目噴射開始時期 */
                                                                    /* 更新タイミング ： 8msm */
                                                                    /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

extern f4 f4g_eminj_eainjd4fix;                                     /* m=eminj,unit=BTDC :確定筒内4回目噴射開始時期 */
                                                                    /* 更新タイミング ： 8msm */
                                                                    /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

extern f4 f4g_eminj_eainjd5fix;                                     /* m=eminj,unit=BTDC :確定筒内5回目噴射開始時期 */
                                                                    /* 更新タイミング ： 8msm */
                                                                    /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

extern f4 f4g_eminj_eainjd6fix;                                     /* m=eminj,unit=BTDC :確定筒内6回目噴射開始時期 */
                                                                    /* 更新タイミング ： 8msm */
                                                                    /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

extern s2 s2g_eminj_eainjdn[6];                                     /* m=eminj,lsb=1024/128/256,unit=BTDC :筒内n回目噴射開始時期(噴射回数配列) */ /* 始動時に最大6回噴射(直噴のみ) */
extern f4 f4g_eminj_eainjdn[6];                                     /* m=eminj,unit=BTDC :筒内n回目噴射開始時期(噴射回数配列) */ /* 始動時に最大6回噴射(直噴のみ) */
                                                                    /* 更新タイミング ： pwon,8msm */
                                                                    /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

extern s4 s4g_eminj_eqinjstpn[5];                                   /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポートn回目始動時噴射量（噴射回数配列） */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
extern f4 f4g_eminj_eqinjstpn[5];                                   /* m=eminj,unit=mg/st :ポートn回目始動時噴射量（噴射回数配列） */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
                                                                    /* 更新タイミング ： pwon,8msm */
                                                                    /* 注意事項 :【D-4以外】*/

extern s4 s4g_eminj_eqinjstdn[6];                                   /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内n回目始動時噴射量（噴射回数配列） */ /* 始動時に最大6回噴射(直噴のみ) */
extern f4 f4g_eminj_eqinjstdn[6];                                   /* m=eminj,unit=mg/st :筒内n回目始動時噴射量（噴射回数配列） */ /* 始動時に最大6回噴射(直噴のみ) */
                                                                    /* 更新タイミング ： pwon,8msm */
                                                                    /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/

extern s4 s4g_eminj_eqinjflfix[8];                                  /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :FL固定噴射量 */
extern f4 f4g_eminj_eqinjflfix[8];                                  /* m=eminj,unit=mg/st :FL固定噴射量 */
                                                                    /* 更新タイミング ： pwon,8msm */

extern s4 s4g_eminj_eqinjplfix[8];                                  /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :PL固定噴射量 */
extern f4 f4g_eminj_eqinjplfix[8];                                  /* m=eminj,unit=mg/st :PL固定噴射量 */
                                                                    /* 更新タイミング ： pwon,8msm */

/*-------------------------------------------------------------------*/
/* 適合定数                                                          */
/*-------------------------------------------------------------------*/
/* 非公開（部品内部のみ） */
extern volatile const s2 s2s_eminj_NE_RCD;              /* m=eminj,lsb=(12800*2)/128/256,unit=rpm :処理実行判定閾値 */

/*-------------------------------------------------------------------*/
/* 公開固定定数                                                      */
/*-------------------------------------------------------------------*/
extern volatile const u1 u1g_eminj_BENCH_PRI;           /* m=eminj,lsb=1 :ﾍﾞﾝﾁ適合用噴射要求の優先度 */
                                                        /* 注意事項 :【ﾍﾞﾝﾁ適合用ｿﾌﾄ有】OR【ﾍﾞﾝﾁ適合ﾓｰﾄﾞ有】*/
extern volatile const u1 u1g_eminj_DEFLAIR_PRI;         /* m=eminj,lsb=1 :工場ｴｱ抜き制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】*/
extern volatile const u1 u1g_eminj_EGSTPVS_PRI;         /* m=eminj,lsb=1 :噴射停止の優先度 */
extern volatile const u1 u1g_eminj_STPHV_PRI;           /* m=eminj,lsb=1 :HV停止制御の優先度 */
                                                        /* 注意事項 :【EG-MG遊星ｷﾞｱ】OR【EG-MG直結】*/
extern volatile const u1 u1g_eminj_WUPCAT_PRI;          /* m=eminj,lsb=1 :触媒暖機制御の優先度 */
                                                        /* 注意事項 :【ALL HV】*/
extern volatile const u1 u1g_eminj_STPSS_PRI;           /* m=eminj,lsb=1 :SS停止制御の優先度 */
                                                        /* 注意事項 :【SS制御有】OR【EG-MGｸﾗｯﾁ】*/
extern volatile const u1 u1g_eminj_RDNVES_PRI;          /* m=eminj,lsb=1 :ｴﾝｼﾞﾝ停止・始動時の振動低減制御の優先度 */
                                                        /* 注意事項 :【ALL HV】*/
extern volatile const u1 u1g_eminj_RDPN_PRI;            /* m=eminj,lsb=1 :PN低減制御の優先度 */
                                                        /* 注意事項 :【ALL HV】AND【D-4以外】*/
extern volatile const u1 u1g_eminj_RDPN_ST_PRI;         /* m=eminj,lsb=1 :PN低減制御(始動時)の優先度 */
                                                        /* 注意事項 :【ALL HV】AND【ﾎﾟｰﾄ】*/
extern volatile const u1 u1g_eminj_STAHV_PRI;           /* m=eminj,lsb=1 :HV始動制御の優先度 */
                                                        /* 注意事項 :【ALL HV】AND【HV始動制御要求使用】*/
extern volatile const u1 u1g_eminj_STASS_PRI;           /* m=eminj,lsb=1 :SS始動制御の優先度 */
                                                        /* 注意事項 :【SS制御有】OR【EG-MGｸﾗｯﾁ】*/
extern volatile const u1 u1g_eminj_STAFRG_PRI;          /* m=eminj,lsb=1 :極低温始動制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】*/
extern volatile const u1 u1g_eminj_RESTAHOT_PRI;        /* m=eminj,lsb=1 :高温再始動制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/
extern volatile const u1 u1g_eminj_KCST_PRI;            /* m=eminj,lsb=1 :始動時ﾉｯｸ防止制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/
extern volatile const u1 u1g_eminj_SJC_PRI;             /* m=eminj,lsb=1 :触媒急速暖機制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/
extern volatile const u1 u1g_eminj_STRATIST_PRI;        /* m=eminj,lsb=1 :成層始動制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/
extern volatile const u1 u1g_eminj_FCINJCTR_PRI;        /* m=eminj,lsb=1 :FC中燃料噴射制御の優先度 */
extern volatile const u1 u1g_eminj_RTNFC_PRI;           /* m=eminj,lsb=1 :FC復帰制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】*/
extern volatile const u1 u1g_eminj_CLRDEPI_PRI;         /* m=eminj,lsb=1 :ｱｲﾄﾞﾙ時ｲﾝｼﾞｪｸﾀﾃﾞﾎﾟ除去制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】*/
extern volatile const u1 u1g_eminj_FPLDLV_PRI;          /* m=eminj,lsb=1 :低圧ﾃﾞﾘﾊﾞﾘ内燃料脈動回避制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】AND【可変燃圧制御無】*/
extern volatile const u1 u1g_eminj_FCFRCTRL_PRI;        /* m=eminj,lsb=1 :1気筒FC制御の優先度 */
                                                        /* 注意事項 :【GPF有】AND【1気筒FC制御要求使用】*/
extern volatile const u1 u1g_eminj_STACM_PRI;           /* m=eminj,lsb=1,:始動時吹け上がり制御の優先度 */
                                                        /* 注意事項 :(【ﾘﾓｰﾄｺﾝﾄﾛｰﾙ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】)AND【SUB-CPU以外】AND【始動時吹け上がり制御要求使用】*/
extern volatile const u1 u1g_eminj_DTHRCTRL_PRI;        /* m=eminj,lsb=1 :気筒別ﾃﾞｨｻﾞ制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】*/
extern volatile const u1 u1g_eminj_ACTLFG_PRI;          /* m=eminj,lsb=1 :ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御の優先度 */
                                                        /* 注意事項 :(【ﾃﾞｭｱﾙINJ】OR【D-4】)AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】*/
extern volatile const u1 u1g_eminj_INJIMB_PRI;          /* m=eminj,lsb=1 :ｲﾝﾊﾞﾗﾝｽ時の噴射制御の優先度 */
                                                        /* 注意事項 :【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ﾃﾞｭｱﾙINJ】AND【ｲﾝﾊﾞﾗﾝｽ時の噴射制御要求使用】*/
extern volatile const u1 u1g_eminj_ACTAREFUEL_PRI;      /* m=eminj,lsb=1 :給油後の噴き分けｱｸﾃｨﾌﾞ制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】AND【FFV制御有】*/
extern volatile const u1 u1g_eminj_ACTOBD_PRI;          /* m=eminj,lsb=1 :OBD要求によるｱｸﾃｨﾌﾞ制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】AND【OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
extern volatile const u1 u1g_eminj_ACTGAF_PRI;          /* m=eminj,lsb=1 :A/F学習の為のｱｸﾃｨﾌﾞ制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】*/
extern volatile const u1 u1g_eminj_IMBRQ_PRI;           /* m=eminj,lsb=1, :ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御の優先度 */
                                                        /* 注意事項 :【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ﾃﾞｭｱﾙINJ】AND【ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
extern volatile const u1 u1g_eminj_MFINJRQ_PRI;         /* m=eminj,lsb=1, :失火OBD要求によるｱｸﾃｨﾌﾞ制御の優先度 */
                                                        /* 注意事項 :【失火OBD有】AND【ﾃﾞｭｱﾙINJ】AND【失火OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
extern volatile const u1 u1g_eminj_FKGDRQ_PRI;          /* m=eminj,lsb=1, :燃料系OBD要求によるｱｸﾃｨﾌﾞ制御の優先度 */
                                                        /* 注意事項 :【燃料OBD有】AND【ﾃﾞｭｱﾙINJ】AND【燃料系OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
extern volatile const u1 u1g_eminj_KCTRN_PRI;           /* m=eminj,lsb=1 :発進ﾉｯｸ防止制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】OR【D-4】*/
extern volatile const u1 u1g_eminj_RDVAP_PRI;           /* m=eminj,lsb=1 :ﾍﾞｰﾊﾟｰ抑制制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】*/
extern volatile const u1 u1g_eminj_DWNPR_PRI;           /* m=eminj,lsb=1 :燃圧低減制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】*/
extern volatile const u1 u1g_eminj_PRVDIL_PRI;          /* m=eminj,lsb=1 :冷間時希釈防止制御の優先度 */
                                                        /* 注意事項 :【ﾃﾞｭｱﾙINJ】*/
extern volatile const u1 u1g_eminj_PWRUP_PRI;           /* m=eminj,lsb=1 :出力性能向上制御の優先度 */

extern volatile const u1 u1g_eminj_BINJPLCTR_PRI;       /* m=eminj,lsb=1 :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御の優先度 */
                                                        /* 注意事項 :【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】*/
extern volatile const u1 u1g_eminj_BINJPLCTR_WC_PRI;    /* m=eminj,lsb=1 :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)の優先度 */
                                                        /* 注意事項 :【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】*/
extern volatile const u1 u1g_eminj_BINJPLCTR_STAHV_PRI; /* m=eminj,lsb=1 :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)の優先度 */
                                                        /* 注意事項 :【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】*/

extern volatile const u1 u1g_eminj_FREE0_PRI;           /* m=eminj,lsb=1 :ﾌﾘｰﾎﾟｰﾄ0用制御の優先度 */
                                                        /* 注意事項 :【ﾌﾘｰﾎﾟｰﾄ0使用】*/
extern volatile const u1 u1g_eminj_FREE1_PRI;           /* m=eminj,lsb=1 :ﾌﾘｰﾎﾟｰﾄ1用制御の優先度 */
                                                        /* 注意事項 :【ﾌﾘｰﾎﾟｰﾄ1使用】*/
extern volatile const u1 u1g_eminj_FREE2_PRI;           /* m=eminj,lsb=1 :ﾌﾘｰﾎﾟｰﾄ2用制御の優先度 */
                                                        /* 注意事項 :【ﾌﾘｰﾎﾟｰﾄ2使用】*/
extern volatile const u1 u1g_eminj_FREE3_PRI;           /* m=eminj,lsb=1 :ﾌﾘｰﾎﾟｰﾄ3用制御の優先度 */
                                                        /* 注意事項 :【ﾌﾘｰﾎﾟｰﾄ3使用】*/
extern volatile const u1 u1g_eminj_FREE4_PRI;           /* m=eminj,lsb=1 :ﾌﾘｰﾎﾟｰﾄ4用制御の優先度 */
                                                        /* 注意事項 :【ﾌﾘｰﾎﾟｰﾄ4使用】*/
extern volatile const u1 u1g_eminj_FREE5_PRI;           /* m=eminj,lsb=1 :ﾌﾘｰﾎﾟｰﾄ5用制御の優先度 */
                                                        /* 注意事項 :【ﾌﾘｰﾎﾟｰﾄ5使用】*/
extern volatile const u1 u1g_eminj_FREE6_PRI;           /* m=eminj,lsb=1 :ﾌﾘｰﾎﾟｰﾄ6用制御の優先度 */
                                                        /* 注意事項 :【ﾌﾘｰﾎﾟｰﾄ6使用】*/
extern volatile const u1 u1g_eminj_FREE7_PRI;           /* m=eminj,lsb=1 :ﾌﾘｰﾎﾟｰﾄ7用制御の優先度 */
                                                        /* 注意事項 :【ﾌﾘｰﾎﾟｰﾄ7使用】*/
extern volatile const u1 u1g_eminj_FREE8_PRI;           /* m=eminj,lsb=1 :ﾌﾘｰﾎﾟｰﾄ8用制御の優先度 */
                                                        /* 注意事項 :【ﾌﾘｰﾎﾟｰﾄ8使用】*/
extern volatile const u1 u1g_eminj_FREE9_PRI;           /* m=eminj,lsb=1 :ﾌﾘｰﾎﾟｰﾄ9用制御の優先度 */
                                                        /* 注意事項 :【ﾌﾘｰﾎﾟｰﾄ9使用】*/
extern volatile const u1 u1g_eminj_FREE10_PRI;          /* m=eminj,lsb=1 :ﾌﾘｰﾎﾟｰﾄ10用制御の優先度 */
                                                        /* 注意事項 :【ﾌﾘｰﾎﾟｰﾄ10使用】*/
extern volatile const u1 u1g_eminj_FREE11_PRI;          /* m=eminj,lsb=1 :ﾌﾘｰﾎﾟｰﾄ11用制御の優先度 */
                                                        /* 注意事項 :【ﾌﾘｰﾎﾟｰﾄ11使用】*/

/*-------------------------------------------------------------------*/
/* 適合マップ                                                        */
/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
/* オートカウンタ                                                    */
/*-------------------------------------------------------------------*/
extern s2 s2g_eminj_ecqinjast_8m;          /* m=eminj,lsb=268435.456/128/256,unit=ms :始動後噴射量要求継続ｶｳﾝﾀ */

#endif  /* EMINJ_H */
/**** End of File ****************************************************/
