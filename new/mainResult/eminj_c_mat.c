/* eminj-kjcw00-1600-a-t-M4 */
/*********************************************************************/
/*  Copyright Toyota Motor Corporation                               */
/*********************************************************************/

/*********************************************************************/
/* オブジェクト名  |  噴射要求の調停                                 */
/* 注意事項        |                                                 */
/*-------------------------------------------------------------------*/
/*     個別変更履歴 （個別変更時は以下に変更日、内容を記入すること） */
/*********************************************************************/

/*-------------------------------------------------------------------*/
/* 適合定数のセクション定義                                          */
/*-------------------------------------------------------------------*/
#pragma ghs section rozdata = ".mat_eminj"

/*-------------------------------------------------------------------*/
/* ヘッダファイルのインクルード                                      */
/*-------------------------------------------------------------------*/
#include <../inc/common.h>
#include <../inc/gllib.h>
#include <engsrc/espc/ejcc.h>                   /* JEEFI,u1g_EJCC_D4,u1g_EJCC_PORT,u1g_EJCC_DUAL,JESS,JEMAT_BENCHI */
                                                /* JEPRDEMAND,JEOBDAFIMB_D,JEFFV */
                                                /* JEMAT_BENCH_E,JEEGMG_E,u1g_EJCC_HVPLGR_E,u1g_EJCC_HVDIRECT_E,u1g_EJCC_HVCLUTCH_E */
                                                /* JEALLHV_E,u1g_EJCC_ALLHV_E */
                                                /* JENGPF_E,JENVCTR,JEMICN_E,u1g_EJCC_SUB_E,JEOBDMF,JEOBDFKG */
                                                /* JEPLMLT_E,JERMTCTR */
#include <engsrc/inc/elsb.h>

#include <engsrc/eactmedi/einj/eminj.h>

/*-------------------------------------------------------------------*/
/* コンパイラバージョン定義                                          */
/*-------------------------------------------------------------------*/
#define MK32_ID (0x00000040)            /* R9コンパイラを使用 */

#ifdef __GHS_VERSION_NUMBER
 #if ( ( __GHS_VERSION_NUMBER >= 201355 ) \
    && ( __GHS_VERSION_NUMBER < 201400 ) )
 #else
  #error "コンパイルされるコンパイラが異なっています。"
 #endif
#endif

/*-------------------------------------------------------------------*/
/* コンパイルSW未定義チェック                                        */
/*-------------------------------------------------------------------*/
#if !defined JEEFI
#error "JEEFI is undeclared"
#endif

#if !defined u1g_EJCC_D4
#error "u1g_EJCC_D4 is undeclared"
#endif

#if !defined u1g_EJCC_PORT
#error "u1g_EJCC_PORT is undeclared"
#endif

#if !defined u1g_EJCC_DUAL
#error "u1g_EJCC_DUAL is undeclared"
#endif

#if !defined JESS
#error "JESS is undeclared"
#endif

#if !defined JEMAT_BENCHI
#error "JEMAT_BENCHI is undeclared"
#endif

#if !defined JEPRDEMAND
#error "JEPRDEMAND is undeclared"
#endif

#if !defined JEOBDAFIMB_D
#error "JEOBDAFIMB_D is undeclared"
#endif

#if !defined JEFFV
#error "JEFFV is undeclared"
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

#if !defined EMINJ_STAHV_MEDI
#error "EMINJ_STAHV_MEDI is undeclared"
#endif

#if !defined EMINJ_FCFRCTRL_MEDI
#error "EMINJ_FCFRCTRL_MEDI is undeclared"
#endif

#if !defined EMINJ_STACM_MEDI
#error "EMINJ_STACM_MEDI is undeclared"
#endif

#if !defined EMINJ_INJIMB_MEDI
#error "EMINJ_INJIMB_MEDI is undeclared"
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
/* 適合定数                                                          */
/*-------------------------------------------------------------------*/
/* $$$適合定数_標準_v4.11 */
volatile const s2 s2s_eminj_NE_RCD = s2g_ELSB_NE(4000.);                /* m=eminj,lsb=(12800*2)/128/256,ofs=,unit=rpm :処理実行判定閾値 */
/* EMINJ_KRICHIは、eminj_l_mat.cファイルに定義しました。 */
/* #if (JEEFI == u1g_EJCC_D4) */                                        /* 【D-4】 */
/* EMINJ_INJPTN_VDは、eminj.hファイルに定義しました。 */
/* #else */                                                             /* 【D-4以外】 */
/* EMINJ_INJPTN_VDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if (JEEFI != u1g_EJCC_D4) */                                        /* 【D-4以外】 */
/* EMINJ_AINJP_VDは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_AINJP_MNは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_AINJP_MXは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K1F_VDは、eminj_l_mat.cファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if (JEEFI == u1g_EJCC_PORT) */                                      /* 【ﾎﾟｰﾄ】 */
/* EMINJ_AINJPADD_MNは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_AINJPADD_MXは、eminj_l_mat.cファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) */            /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/* EMINJ_AINJD_VDは、eminj_l_mat.cファイルに定義しました。 */
 /* #if (JECOMBCCPT_E == u1g_EJCC_SPRAYG_E) */                          /* 【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】 */
/* EMINJ_AINJD_MNは、eminj_l_mat.cファイルに定義しました。 */
 /* #else */                                                            /* 【ｽﾌﾟﾚｰｶﾞｲﾄﾞ以外】 */
/* EMINJ_AINJD_MNは、eminj_l_mat.cファイルに定義しました。 */
 /* #endif */                                                           /* JECOMBCCPT_E */
/* EMINJ_AINJD_MXは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_AINJDADD_MNは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_AINJDADD_MXは、eminj_l_mat.cファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* EMINJ_QINJIは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_QINJ_VDは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_QINJ_MNは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_QINJ_MXは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_QINJST_MNは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_QINJST_MXは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_QINJFLFIX_VDは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_QINJPLFIX_VDは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K1F_MNは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K1F_MXは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K1FN_MNは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K1FN_MXは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K2F_MNは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K2F_MXは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K2FN_MNは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K2FN_MXは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K3F_MNは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K3F_MXは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K3FN_MNは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_K3FN_MXは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_KRCHREF_MNは、eminj_l_mat.cファイルに定義しました。 */
/* EMINJ_KRCHREF_MXは、eminj_l_mat.cファイルに定義しました。 */
/* $$$適合定数_標準_v4.11 */

/*-------------------------------------------------------------------*/
/* 固定定数                                                          */
/*-------------------------------------------------------------------*/
/* $$$固定定数_標準_v4.11 */
/* 固定定数 EMINJ_PRINORQは、eminj.hファイルに定義しました。 */

#if (JEMAT_BENCHI == u1g_EJCC_USE) || (JEMAT_BENCH_E == u1g_EJCC_USE)   /* 【ﾍﾞﾝﾁ適合用ｿﾌﾄ有】OR【ﾍﾞﾝﾁ適合ﾓｰﾄﾞ有】 */
volatile const u1 u1g_eminj_BENCH_PRI = (u1)(((2.)/(1.))+0.5);          /* m=eminj,lsb=1,ofs=,unit=- :ﾍﾞﾝﾁ適合用噴射要求の優先度 */
#endif                                                                  /* JEMAT_BENCHI JEMAT_BENCH_E */

volatile const u1 u1g_eminj_EGSTPVS_PRI = (u1)(((4.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :噴射停止の優先度 */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
volatile const u1 u1g_eminj_DEFLAIR_PRI = (u1)(((6.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :工場ｴｱ抜き制御の優先度 */
#endif                                                                  /* JEEFI */

#if (JEEGMG_E == u1g_EJCC_HVPLGR_E) || (JEEGMG_E == u1g_EJCC_HVDIRECT_E)    /* 【EG-MG遊星ｷﾞｱ】OR【EG-MG直結】 */
volatile const u1 u1g_eminj_STPHV_PRI = (u1)(((12.)/(1.))+0.5);         /* m=eminj,lsb=1,ofs=,unit=- :HV停止制御の優先度 */
#endif                                                                  /* JEEGMG_E */

#if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E)         /* 【SS制御有】OR【EG-MGｸﾗｯﾁ】 */
volatile const u1 u1g_eminj_STPSS_PRI = (u1)(((14.)/(1.))+0.5);         /* m=eminj,lsb=1,ofs=,unit=- :SS停止制御の優先度 */
#endif                                                                  /* JESS JEEGMG_E */

#if JEALLHV_E == u1g_EJCC_ALLHV_E                                       /* 【ALL HV】 */
volatile const u1 u1g_eminj_RDNVES_PRI = (u1)(((16.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ｴﾝｼﾞﾝ停止・始動時の振動低減制御の優先度 */
#endif                                                                  /* JEALLHV_E */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                  /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
volatile const u1 u1g_eminj_SJC_PRI = (u1)(((20.)/(1.))+0.5);           /* m=eminj,lsb=1,ofs=,unit=- :触媒急速暖機制御の優先度 */
#endif                                                                  /* JEEFI */

#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_WC_MEDI == ON)   /* 【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】 */
volatile const u1 u1g_eminj_BINJPLCTR_WC_PRI = (u1)(((22.)/(1.))+0.5);  /* m=eminj,lsb=1,ofs=,unit=- :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)の優先度 */
#endif                                                                  /* JEALLHV_E JEPLMLT_E EMINJ_BINJPLCTR_WC_MEDI */

#if JEALLHV_E == u1g_EJCC_ALLHV_E                                       /* 【ALL HV】 */
volatile const u1 u1g_eminj_WUPCAT_PRI = (u1)(((24.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :触媒暖機制御の優先度 */
#endif                                                                  /* JEALLHV_E */

#if (JENGPF_E != u1g_EJCC_NOT_USE) && (EMINJ_FCFRCTRL_MEDI == ON)       /* 【GPF有】AND【1気筒FC制御要求使用】 */
volatile const u1 u1g_eminj_FCFRCTRL_PRI = (u1)(((26.)/(1.))+0.5);      /* m=eminj,lsb=1,ofs=,unit=- :1気筒FC制御の優先度 */
#endif                                                                  /* JENGPF_E EMINJ_FCFRCTRL_MEDI */

#if ((JERMTCTR == u1g_EJCC_USE) || (JENVCTR == u1g_EJCC_USE)) && (JEMICN_E != u1g_EJCC_SUB_E) && (EMINJ_STACM_MEDI == ON)   /* (【ﾘﾓｰﾄｺﾝﾄﾛｰﾙ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】)AND【SUB-CPU以外】AND【始動時吹け上がり制御要求使用】 */
volatile const u1 u1g_eminj_STACM_PRI = (u1)(((28.)/(1.))+0.5);         /* m=eminj,lsb=1,ofs=,unit=- :始動時吹け上がり制御の優先度 */
#endif                                                                  /* JERMTCTR JENVCTR JEMICN_E EMINJ_STACM_MEDI */

#if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E)         /* 【SS制御有】OR【EG-MGｸﾗｯﾁ】 */
volatile const u1 u1g_eminj_STASS_PRI = (u1)(((30.)/(1.))+0.5);         /* m=eminj,lsb=1,ofs=,unit=- :SS始動制御の優先度 */
#endif                                                                  /* JESS JEEGMG_E */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                  /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
volatile const u1 u1g_eminj_RESTAHOT_PRI = (u1)(((32.)/(1.))+0.5);      /* m=eminj,lsb=1,ofs=,unit=- :高温再始動制御の優先度 */
volatile const u1 u1g_eminj_KCST_PRI = (u1)(((34.)/(1.))+0.5);          /* m=eminj,lsb=1,ofs=,unit=- :始動時ﾉｯｸ防止制御の優先度 */
#endif                                                                  /* JEEFI */

#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT)         /* 【ALL HV】AND【ﾎﾟｰﾄ】 */
volatile const u1 u1g_eminj_RDPN_ST_PRI = (u1)(((36.)/(1.))+0.5);       /* m=eminj,lsb=1,ofs=,unit=- :PN低減制御(始動時)の優先度 */
#endif                                                                  /* JEALLHV_E JEEFI */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                  /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
volatile const u1 u1g_eminj_STRATIST_PRI = (u1)(((42.)/(1.))+0.5);      /* m=eminj,lsb=1,ofs=,unit=- :成層始動制御の優先度 */
#endif                                                                  /* JEEFI */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
volatile const u1 u1g_eminj_STAFRG_PRI = (u1)(((44.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :極低温始動制御の優先度 */
#endif                                                                  /* JEEFI */

#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (EMINJ_STAHV_MEDI == ON)         /* 【ALL HV】AND【HV始動制御要求使用】 */
volatile const u1 u1g_eminj_STAHV_PRI = (u1)(((46.)/(1.))+0.5);         /* m=eminj,lsb=1,ofs=,unit=- :HV始動制御の優先度 */
#endif                                                                  /* JEALLHV_E EMINJ_STAHV_MEDI */

#if (JEEGMG_E == u1g_EJCC_HVPLGR_E) && (JEFFV == u1g_EJCC_NOT_USE) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_STAHV_MEDI == ON) /* 【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】 */
volatile const u1 u1g_eminj_BINJPLCTR_STAHV_PRI = (u1)(((48.)/(1.))+0.5);   /* m=eminj,lsb=1,ofs=,unit=- :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)の優先度 */
#endif                                                                  /* JEEGMG_E JEFFV JEPLMLT_E EMINJ_BINJPLCTR_STAHV_MEDI */

volatile const u1 u1g_eminj_FCINJCTR_PRI = (u1)(((50.)/(1.))+0.5);      /* m=eminj,lsb=1,ofs=,unit=- :FC中燃料噴射制御の優先度 */

#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI != u1g_EJCC_D4)           /* 【ALL HV】AND【D-4以外】 */
volatile const u1 u1g_eminj_RDPN_PRI = (u1)(((52.)/(1.))+0.5);          /* m=eminj,lsb=1,ofs=,unit=- :PN低減制御の優先度 */
#endif                                                                  /* JEALLHV_E JEEFI */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                  /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
volatile const u1 u1g_eminj_RTNFC_PRI = (u1)(((54.)/(1.))+0.5);         /* m=eminj,lsb=1,ofs=,unit=- :FC復帰制御の優先度 */
#endif                                                                  /* JEEFI */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
volatile const u1 u1g_eminj_CLRDEPI_PRI = (u1)(((56.)/(1.))+0.5);       /* m=eminj,lsb=1,ofs=,unit=- :ｱｲﾄﾞﾙ時ｲﾝｼﾞｪｸﾀﾃﾞﾎﾟ除去制御の優先度 */
#endif                                                                  /* JEEFI */

#if (JEEFI == u1g_EJCC_DUAL) && (JEPRDEMAND == u1g_EJCC_NOT_USE)        /* 【ﾃﾞｭｱﾙINJ】AND【可変燃圧制御無】 */
volatile const u1 u1g_eminj_FPLDLV_PRI = (u1)(((60.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :低圧ﾃﾞﾘﾊﾞﾘ内燃料脈動回避制御の優先度 */
#endif                                                                  /* JEEFI JEPRDEMAND */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
volatile const u1 u1g_eminj_DTHRCTRL_PRI = (u1)(((64.)/(1.))+0.5);      /* m=eminj,lsb=1,ofs=,unit=- :気筒別ﾃﾞｨｻﾞ制御の優先度 */
#endif                                                                  /* JEEFI */

#if ((JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)) && (EMINJ_ACTLFG_MEDI == ON)   /* (【ﾃﾞｭｱﾙINJ】OR【D-4】)AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】 */
volatile const u1 u1g_eminj_ACTLFG_PRI = (u1)(((66.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御の優先度 */
#endif                                                                  /* JEEFI EMINJ_ACTLFG_MEDI */

#if (JEOBDAFIMB_D == u1g_EJCC_USE) && (JEEFI == u1g_EJCC_DUAL) && (EMINJ_INJIMB_MEDI == ON) /* 【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ﾃﾞｭｱﾙINJ】AND【ｲﾝﾊﾞﾗﾝｽ時の噴射制御要求使用】 */
volatile const u1 u1g_eminj_INJIMB_PRI = (u1)(((72.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ｲﾝﾊﾞﾗﾝｽ時の噴射制御の優先度 */
#endif                                                                  /* JEOBDAFIMB_D JEEFI EMINJ_INJIMB_MEDI */

#if (JEEFI == u1g_EJCC_DUAL) && (JEFFV != u1g_EJCC_NOT_USE)             /* 【ﾃﾞｭｱﾙINJ】AND【FFV制御有】 */
volatile const u1 u1g_eminj_ACTAREFUEL_PRI = (u1)(((74.)/(1.))+0.5);    /* m=eminj,lsb=1,ofs=,unit=- :給油後の噴き分けｱｸﾃｨﾌﾞ制御の優先度 */
#endif                                                                  /* JEEFI JEFFV */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
 #if EMINJ_ACTOBD_MEDI == ON                                            /* 【ﾃﾞｭｱﾙINJ】AND【OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
volatile const u1 u1g_eminj_ACTOBD_PRI = (u1)(((76.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :OBD要求によるｱｸﾃｨﾌﾞ制御の優先度 */
 #endif                                                                 /* EMINJ_ACTOBD_MEDI */

volatile const u1 u1g_eminj_ACTGAF_PRI = (u1)(((84.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :A/F学習の為のｱｸﾃｨﾌﾞ制御の優先度 */

 #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_IMBRQ_MEDI == ON)         /* 【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ﾃﾞｭｱﾙINJ】AND【ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
volatile const u1 u1g_eminj_IMBRQ_PRI = (u1)(((78.)/(1.))+0.5);         /* m=eminj,lsb=1,ofs=,unit=- :ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御の優先度 */
 #endif                                                                 /* JEOBDAFIMB_D EMINJ_IMBRQ_MEDI */

 #if (JEOBDMF == u1g_EJCC_USE) && (EMINJ_MFINJRQ_MEDI == ON)            /* 【失火OBD有】AND【ﾃﾞｭｱﾙINJ】AND【失火OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
volatile const u1 u1g_eminj_MFINJRQ_PRI = (u1)(((80.)/(1.))+0.5);       /* m=eminj,lsb=1,ofs=,unit=- :失火OBD要求によるｱｸﾃｨﾌﾞ制御の優先度 */
 #endif                                                                 /* JEOBDMF EMINJ_MFINJRQ_MEDI */

 #if (JEOBDFKG == u1g_EJCC_USE) && (EMINJ_FKGDRQ_MEDI == ON)            /* 【燃料OBD有】AND【ﾃﾞｭｱﾙINJ】AND【燃料系OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
volatile const u1 u1g_eminj_FKGDRQ_PRI = (u1)(((82.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :燃料系OBD要求によるｱｸﾃｨﾌﾞ制御の優先度 */
 #endif                                                                 /* JEOBDFKG EMINJ_FKGDRQ_MEDI */
#endif                                                                  /* JEEFI */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                  /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
volatile const u1 u1g_eminj_KCTRN_PRI = (u1)(((86.)/(1.))+0.5);         /* m=eminj,lsb=1,ofs=,unit=- :発進ﾉｯｸ防止制御の優先度 */
#endif                                                                  /* JEEFI */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
volatile const u1 u1g_eminj_RDVAP_PRI = (u1)(((88.)/(1.))+0.5);         /* m=eminj,lsb=1,ofs=,unit=- :ﾍﾞｰﾊﾟｰ抑制制御の優先度 */
volatile const u1 u1g_eminj_DWNPR_PRI = (u1)(((90.)/(1.))+0.5);         /* m=eminj,lsb=1,ofs=,unit=- :燃圧低減制御の優先度 */
#endif                                                                  /* JEEFI */

volatile const u1 u1g_eminj_PWRUP_PRI = (u1)(((92.)/(1.))+0.5);         /* m=eminj,lsb=1,ofs=,unit=- :出力性能向上制御の優先度 */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
volatile const u1 u1g_eminj_PRVDIL_PRI = (u1)(((96.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :冷間時希釈防止制御の優先度 */
#endif                                                                  /* JEEFI */

#if (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_MEDI == ON)         /* 【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】 */
volatile const u1 u1g_eminj_BINJPLCTR_PRI = (u1)(((98.)/(1.))+0.5);     /* m=eminj,lsb=1,ofs=,unit=- :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御の優先度 */
#endif                                                                  /* JEPLMLT_E EMINJ_BINJPLCTR_MEDI */

#if EMINJ_FREE0 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ0使用】 */
volatile const u1 u1g_eminj_FREE0_PRI = (u1)(((200.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ0用制御の優先度 */
#endif                                                                  /* EMINJ_FREE0 */

#if EMINJ_FREE1 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ1使用】 */
volatile const u1 u1g_eminj_FREE1_PRI = (u1)(((201.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ1用制御の優先度 */
#endif                                                                  /* EMINJ_FREE1 */

#if EMINJ_FREE2 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ2使用】 */
volatile const u1 u1g_eminj_FREE2_PRI = (u1)(((202.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ2用制御の優先度 */
#endif                                                                  /* EMINJ_FREE2 */

#if EMINJ_FREE3 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ3使用】 */
volatile const u1 u1g_eminj_FREE3_PRI = (u1)(((203.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ3用制御の優先度 */
#endif                                                                  /* EMINJ_FREE3 */

#if EMINJ_FREE4 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ4使用】 */
volatile const u1 u1g_eminj_FREE4_PRI = (u1)(((204.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ4用制御の優先度 */
#endif                                                                  /* EMINJ_FREE4 */

#if EMINJ_FREE5 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ5使用】 */
volatile const u1 u1g_eminj_FREE5_PRI = (u1)(((205.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ5用制御の優先度 */
#endif                                                                  /* EMINJ_FREE5 */

#if EMINJ_FREE6 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ6使用】 */
volatile const u1 u1g_eminj_FREE6_PRI = (u1)(((206.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ6用制御の優先度 */
#endif                                                                  /* EMINJ_FREE6 */

#if EMINJ_FREE7 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ7使用】 */
volatile const u1 u1g_eminj_FREE7_PRI = (u1)(((207.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ7用制御の優先度 */
#endif                                                                  /* EMINJ_FREE7 */

#if EMINJ_FREE8 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ8使用】 */
volatile const u1 u1g_eminj_FREE8_PRI = (u1)(((208.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ8用制御の優先度 */
#endif                                                                  /* EMINJ_FREE8 */

#if EMINJ_FREE9 == ON                                                   /* 【ﾌﾘｰﾎﾟｰﾄ9使用】 */
volatile const u1 u1g_eminj_FREE9_PRI = (u1)(((209.)/(1.))+0.5);        /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ9用制御の優先度 */
#endif                                                                  /* EMINJ_FREE9 */

#if EMINJ_FREE10 == ON                                                  /* 【ﾌﾘｰﾎﾟｰﾄ10使用】 */
volatile const u1 u1g_eminj_FREE10_PRI = (u1)(((210.)/(1.))+0.5);       /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ10用制御の優先度 */
#endif                                                                  /* EMINJ_FREE10 */

#if EMINJ_FREE11 == ON                                                  /* 【ﾌﾘｰﾎﾟｰﾄ11使用】 */
volatile const u1 u1g_eminj_FREE11_PRI = (u1)(((211.)/(1.))+0.5);       /* m=eminj,lsb=1,ofs=,unit=- :ﾌﾘｰﾎﾟｰﾄ11用制御の優先度 */
#endif                                                                  /* EMINJ_FREE11 */

/* 固定定数 EMINJ_NONE_IDは、eminj.hファイルに定義しました。 */
/* #if (JEMAT_BENCHI == u1g_EJCC_USE) || (JEMAT_BENCH_E == u1g_EJCC_USE) */ /* 【ﾍﾞﾝﾁ適合用ｿﾌﾄ有】OR【ﾍﾞﾝﾁ適合ﾓｰﾄﾞ有】 */
/* 固定定数 EMINJ_BENCH_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEMAT_BENCHI JEMAT_BENCH_E */
/* 固定定数 EMINJ_EGSTPVS_IDは、eminj.hファイルに定義しました。 */
/* #if JEEFI == u1g_EJCC_DUAL */                                        /* 【ﾃﾞｭｱﾙINJ】 */
/* 固定定数 EMINJ_DEFLAIR_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if (JEEGMG_E == u1g_EJCC_HVPLGR_E) || (JEEGMG_E == u1g_EJCC_HVDIRECT_E) */  /* 【EG-MG遊星ｷﾞｱ】OR【EG-MG直結】 */
/* 固定定数 EMINJ_STPHV_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEEGMG_E */
/* #if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E) */   /* 【SS制御有】OR【EG-MGｸﾗｯﾁ】 */
/* 固定定数 EMINJ_STPSS_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JESS JEEGMG_E */
/* 固定定数 EMINJ_RDNVES_IDは、eminj.hファイルに定義しました。 */
/* #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) */            /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/* 固定定数 EMINJ_SJC_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_WC_MEDI == ON) */ /* 【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】 */
/* 固定定数 EMINJ_BINJPLCTR_WC_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEALLHV_E JEPLMLT_E EMINJ_BINJPLCTR_WC_MEDI */
/* #if JEALLHV_E == u1g_EJCC_ALLHV_E */                                 /* 【ALL HV】 */
/* 固定定数 EMINJ_WUPCAT_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEALLHV_E */
/* #if (JENGPF_E != u1g_EJCC_NOT_USE) && (EMINJ_FCFRCTRL_MEDI == ON) */ /* 【GPF有】AND【1気筒FC制御要求使用】 */
/* 固定定数 EMINJ_FCFRCTRL_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JENGPF_E EMINJ_FCFRCTRL_MEDI */
/* #if ((JERMTCTR == u1g_EJCC_USE) || (JENVCTR == u1g_EJCC_USE)) && (JEMICN_E != u1g_EJCC_SUB_E) && (EMINJ_STACM_MEDI == ON) */ /* (【ﾘﾓｰﾄｺﾝﾄﾛｰﾙ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】)AND【SUB-CPU以外】AND【始動時吹け上がり制御要求使用】 */
/* 固定定数 EMINJ_STACM_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JERMTCTR JENVCTR JEMICN_E EMINJ_STACM_MEDI */
/* #if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E) */   /* 【SS制御有】OR【EG-MGｸﾗｯﾁ】 */
/* 固定定数 EMINJ_STASS_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JESS JEEGMG_E */
/* #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) */            /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/* 固定定数 EMINJ_RESTAHOT_IDは、eminj_l_mat.cファイルに定義しました。 */
/* 固定定数 EMINJ_KCST_IDは、eminj_l_mat.cファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT) */   /* 【ALL HV】AND【ﾎﾟｰﾄ】 */
/* 固定定数 EMINJ_RDPN_ST_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEALLHV_E JEEFI */
/* #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) */            /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/* 固定定数 EMINJ_STRATIST_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if JEEFI == u1g_EJCC_DUAL */                                        /* 【ﾃﾞｭｱﾙINJ】 */
/* 固定定数 EMINJ_STAFRG_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (EMINJ_STAHV_MEDI == ON) */   /* 【ALL HV】AND【HV始動制御要求使用】 */
/* 固定定数 EMINJ_STAHV_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEALLHV_E EMINJ_STAHV_MEDI */
/* #if (JEEGMG_E == u1g_EJCC_HVPLGR_E) && (JEFFV == u1g_EJCC_NOT_USE) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_STAHV_MEDI == ON) */   /* 【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】 */
/* AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】 */
/* 固定定数 EMINJ_BINJPLCTR_STAHV_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEEGMG_E JEFFV JEPLMLT_E EMINJ_BINJPLCTR_STAHV_MEDI */
/* 固定定数 EMINJ_FCINJCTR_IDは、eminj.hファイルに定義しました。 */
/* #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI != u1g_EJCC_D4) */     /* 【ALL HV】AND【D-4以外】 */
/* 固定定数 EMINJ_RDPN_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEALLHV_E JEEFI */
/* #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) */            /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/* 固定定数 EMINJ_RTNFC_IDは、eminj_l_mat.cファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if JEEFI == u1g_EJCC_DUAL */                                        /* 【ﾃﾞｭｱﾙINJ】 */
/* 固定定数 EMINJ_CLRDEPI_IDは、eminj_l_mat.cファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if (JEEFI == u1g_EJCC_DUAL) && (JEPRDEMAND == u1g_EJCC_NOT_USE) */  /* 【ﾃﾞｭｱﾙINJ】AND【可変燃圧制御無】 */
/* 固定定数 EMINJ_FPLDLV_IDは、eminj_l_mat.cファイルに定義しました。 */
/* #endif */                                                            /* JEEFI JEPRDEMAND */
/* #if JEEFI == u1g_EJCC_DUAL */                                        /* 【ﾃﾞｭｱﾙINJ】 */
/* 固定定数 EMINJ_DTHRCTRL_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if ((JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)) && (EMINJ_ACTLFG_MEDI == ON) */ /* (【ﾃﾞｭｱﾙINJ】OR【D-4】)AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】 */
/* 固定定数 EMINJ_ACTLFG_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEEFI EMINJ_ACTLFG_MEDI */
/* #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (JEEFI == u1g_EJCC_DUAL) && (EMINJ_INJIMB_MEDI == ON) */   /* 【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ﾃﾞｭｱﾙINJ】AND【ｲﾝﾊﾞﾗﾝｽ時の噴射制御要求使用】 */
/* 固定定数 EMINJ_INJIMB_IDは、eminj_l_mat.cファイルに定義しました。 */
/* #endif */                                                            /* JEOBDAFIMB_D JEEFI EMINJ_INJIMB_MEDI */
/* #if (JEEFI == u1g_EJCC_DUAL) && (JEFFV != u1g_EJCC_NOT_USE) */       /* 【ﾃﾞｭｱﾙINJ】AND【FFV制御有】 */
/* 固定定数 EMINJ_ACTAREFUEL_IDは、eminj_l_mat.cファイルに定義しました。 */
/* #endif */                                                            /* JEEFI JEFFV */
/* #if JEEFI == u1g_EJCC_DUAL */                                        /* 【ﾃﾞｭｱﾙINJ】 */
 /* #if EMINJ_ACTOBD_MEDI == ON */                                      /* 【ﾃﾞｭｱﾙINJ】AND【OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
/* 固定定数 EMINJ_ACTOBD_IDは、eminj.hファイルに定義しました。 */
 /* #endif */                                                           /* EMINJ_ACTOBD_MEDI */
/* 固定定数 EMINJ_ACTGAF_IDは、eminj.hファイルに定義しました。 */
 /* #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_IMBRQ_MEDI == ON) */   /* 【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ﾃﾞｭｱﾙINJ】AND【ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
/* 固定定数 EMINJ_IMBRQ_IDは、eminj.hファイルに定義しました。 */
 /* #endif */                                                           /* JEOBDAFIMB_D EMINJ_IMBRQ_MEDI */
 /* #if (JEOBDMF == u1g_EJCC_USE) && (EMINJ_MFINJRQ_MEDI == ON) */      /* 【失火OBD有】AND【ﾃﾞｭｱﾙINJ】AND【失火OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
/* 固定定数 EMINJ_MFINJRQ_IDは、eminj.hファイルに定義しました。 */
 /* #endif */                                                           /* JEOBDMF EMINJ_MFINJRQ_MEDI */
 /* #if (JEOBDFKG == u1g_EJCC_USE) && (EMINJ_FKGDRQ_MEDI == ON) */      /* 【燃料OBD有】AND【ﾃﾞｭｱﾙINJ】AND【燃料系OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
/* 固定定数 EMINJ_FKGDRQ_IDは、eminj.hファイルに定義しました。 */
 /* #endif */                                                           /* JEOBDFKG EMINJ_FKGDRQ_MEDI */
/* #endif */                                                            /* JEEFI */
/* #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) */            /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/* 固定定数 EMINJ_KCTRN_IDは、eminj_l_mat.cファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if JEEFI == u1g_EJCC_DUAL */                                        /* 【ﾃﾞｭｱﾙINJ】 */
/* 固定定数 EMINJ_RDVAP_IDは、eminj_l_mat.cファイルに定義しました。 */
/* 固定定数 EMINJ_DWNPR_IDは、eminj_l_mat.cファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* 固定定数 EMINJ_PWRUP_IDは、eminj_l_mat.cファイルに定義しました。 */
/* #if JEEFI == u1g_EJCC_DUAL */                                        /* 【ﾃﾞｭｱﾙINJ】 */
/* 固定定数 EMINJ_PRVDIL_IDは、eminj_l_mat.cファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* #if (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_MEDI == ON) */   /* 【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】 */
/* 固定定数 EMINJ_BINJPLCTR_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEPLMLT_E EMINJ_BINJPLCTR_MEDI */
/* #if EMINJ_FREE0 == ON */                                             /* 【ﾌﾘｰﾎﾟｰﾄ0使用】 */
/* 固定定数 EMINJ_FREE0_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* EMINJ_FREE0 */
/* #if EMINJ_FREE1 == ON */                                             /* 【ﾌﾘｰﾎﾟｰﾄ1使用】 */
/* 固定定数 EMINJ_FREE1_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* EMINJ_FREE1 */
/* #if EMINJ_FREE2 == ON */                                             /* 【ﾌﾘｰﾎﾟｰﾄ2使用】 */
/* 固定定数 EMINJ_FREE2_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* EMINJ_FREE2 */
/* #if EMINJ_FREE3 == ON */                                             /* 【ﾌﾘｰﾎﾟｰﾄ3使用】 */
/* 固定定数 EMINJ_FREE3_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* EMINJ_FREE3 */
/* #if EMINJ_FREE4 == ON */                                             /* 【ﾌﾘｰﾎﾟｰﾄ4使用】 */
/* 固定定数 EMINJ_FREE4_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* EMINJ_FREE4 */
/* #if EMINJ_FREE5 == ON */                                             /* 【ﾌﾘｰﾎﾟｰﾄ5使用】 */
/* 固定定数 EMINJ_FREE5_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* EMINJ_FREE5 */
/* #if EMINJ_FREE6 == ON */                                             /* 【ﾌﾘｰﾎﾟｰﾄ6使用】 */
/* 固定定数 EMINJ_FREE6_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* EMINJ_FREE6 */
/* #if EMINJ_FREE7 == ON */                                             /* 【ﾌﾘｰﾎﾟｰﾄ7使用】 */
/* 固定定数 EMINJ_FREE7_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* EMINJ_FREE7 */
/* #if EMINJ_FREE8 == ON */                                             /* 【ﾌﾘｰﾎﾟｰﾄ8使用】 */
/* 固定定数 EMINJ_FREE8_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* EMINJ_FREE8 */
/* #if EMINJ_FREE9 == ON */                                             /* 【ﾌﾘｰﾎﾟｰﾄ9使用】 */
/* 固定定数 EMINJ_FREE9_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* EMINJ_FREE9 */
/* #if EMINJ_FREE10 == ON */                                            /* 【ﾌﾘｰﾎﾟｰﾄ10使用】 */
/* 固定定数 EMINJ_FREE10_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* EMINJ_FREE10 */
/* #if EMINJ_FREE11 == ON */                                            /* 【ﾌﾘｰﾎﾟｰﾄ11使用】 */
/* 固定定数 EMINJ_FREE11_IDは、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* EMINJ_FREE11 */
/* 固定定数 EMINJ_RQID_VDは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQINJMODEは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQINJPTNは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQAINJP1は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQAINJPNは、eminj.hファイルに定義しました。 */
/* EMINJ_RQAINJPNとEMINJ_RQAINJP,EMINJ_RQAINJP1～EMINJ_RQAINJP4は異なる構造体で使用される */
/* 固定定数 EMINJ_RQAINJP2は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQAINJDNは、eminj.hファイルに定義しました。 */
/* EMINJ_RQAINJDNとEMINJ_RQAINJD1～EMINJ_RQAINJD4は異なる構造体で使用される */
/* 固定定数 EMINJ_RQAINJP3は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQAINJP4は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQINJENDは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQAINJCUTPは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQAINJCUTDは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQAINJD1は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQAINJD2は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQAINJD3は、eminj.hファイルに定義しました。 */
/* 噴射回数はﾎﾟｰﾄ・筒内合わせて最大4回でﾎﾟｰﾄと筒内の3回目噴射開始時期要求は排他となるため、ﾊﾞﾘｭｰは同一にしておく */
/* 固定定数 EMINJ_RQAINJD4は、eminj.hファイルに定義しました。 */
/* 噴射回数はﾎﾟｰﾄ・筒内合わせて最大4回でﾎﾟｰﾄと筒内の4回目噴射開始時期要求は排他となるため、ﾊﾞﾘｭｰは同一にしておく */
/* 固定定数 EMINJ_RQQINJSTPNは、eminj.hファイルに定義しました。 */
/* EMINJ_RQQINJSTPNとEMINJ_RQQINJSTP,EMINJ_RQQINJSTP1～EMINJ_RQQINJSTP4は異なる構造体で使用される */
/* 固定定数 EMINJ_RQQINJSTP1は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQQINJSTDNは、eminj.hファイルに定義しました。 */
/* EMINJ_RQQINJSTDNとEMINJ_RQQINJSTD1～EMINJ_RQQINJSTD4は異なる構造体で使用される */
/* 固定定数 EMINJ_RQQINJSTP2は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQQINJFLFIXは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQQINJSTP3は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQQINJPLFIXは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQQINJSTP4は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQQINJSTD1は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQQINJSTD2は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQQINJSTD3は、eminj.hファイルに定義しました。 */
/* 噴射回数はﾎﾟｰﾄ・筒内合わせて最大4回でﾎﾟｰﾄと筒内の3回目始動時噴射要求は排他となるため、ﾊﾞﾘｭｰは同一にしておく */
/* 固定定数 EMINJ_RQQINJSTD4は、eminj.hファイルに定義しました。 */
/* 噴射回数はﾎﾟｰﾄ・筒内合わせて最大4回でﾎﾟｰﾄと筒内の4回目始動時噴射要求は排他となるため、ﾊﾞﾘｭｰは同一にしておく */
/* 固定定数 EMINJ_RQQFCは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQQINJEXPは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQK1FNは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQK2FNは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQK3FNは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQK1Fは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQK2Fは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQK3Fは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQPRREQは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQQFREQは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQPRREQLは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQXQINJASTは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQKRCHREFは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQPLREQは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQAINJPは、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_RQQINJSTPは、eminj.hファイルに定義しました。 */
/* #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) */            /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
/* 固定定数 EMINJ_MOD0N1は、eminj.hファイルに定義しました。 */
/* #endif */                                                            /* JEEFI */
/* 固定定数 EMINJ_MOD002は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_MOD003は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_MOD004は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_MOD005は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_MOD006は、eminj.hファイルに定義しました。 */
/* 固定定数 EMINJ_MOD007は、eminj.hファイルに定義しました。 */
/* $$$固定定数_標準_v4.11 */

/*-------------------------------------------------------------------*/
/* 適合マップ                                                        */
/*-------------------------------------------------------------------*/
/* $$$適合マップ_標準_v4.11 */
/* $$$適合マップ_標準_v4.11 */

/**** End of File ****************************************************/
