/* eminj-pcw00-1500-a-t-M4 */
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
/* ヘッダファイルのインクルード                                      */
/*-------------------------------------------------------------------*/
#include <../inc/common.h>
#include <../inc/gllib.h>
#include <engsrc/espc/ejcc.h>                   /* JEEFI,u1g_EJCC_DUAL,u1g_EJCC_D4,u1g_EJCC_PORT,u1g_EJCC_NOX,JESS,JEMAT_BENCHI */
                                                /* JEPRDEMAND,JEOBDAFIMB_D,JEFFV,JENOX,u1g_EJCC_TWIN,JEEGR,u1g_EJCC_NCYL,JECOMBCCPT_E,u1g_EJCC_SPRAYG_E */
                                                /* u1g_ejcc_NCYL,u1g_ejcc_NOX,JEMAT_BENCH_E,JEEGMG_E,u1g_EJCC_HVPLGR_E,u1g_EJCC_HVDIRECT_E,u1g_EJCC_HVCLUTCH_E,JEALLHV_E,u1g_EJCC_ALLHV_E */
                                                /* JENGPF_E,JEPLMLT_E,JENVCTR,JEMICN_E,u1g_EJCC_SUB_E,JEOBDMF,JEOBDFKG */
                                                /* JERMTCTR */
#include <engsrc/inc/elsb.h>
#include <engsrc/inc/elib.h>

#include <engsrc/eactmedi/einj/eminj.h>

#include <sac/ainjif.h>                          /* u2g_AINJIF_MOD011,vdg_ainjif_renew_injrq() */

#include <engsrc/estate/esin/ene.h>              /* s2g_ene_ene */
#if JEALLHV_E == u1g_EJCC_ALLHV_E               /*【ALL HV】*/
#include <engsrc/efunc/edrblty/eels/erdnves.h>   /* vdg_erdnves_group00_dataget() */
#endif /* JEALLHV_E */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
#include <engsrc/efunc/eunusual/eplant/edeflair.h> /* vdg_edeflair_emedi_dataget() */
#endif /* JEEFI */
#include <engsrc/efunc/eelsrq/eegstpvs.h>        /* vdg_eegstpvs_emedi_dataget() */
#if (JEEGMG_E == u1g_EJCC_HVPLGR_E) || (JEEGMG_E == u1g_EJCC_HVDIRECT_E)    /*【EG-MG遊星ｷﾞｱ】OR【EG-MG直結】*/
#include <engsrc/efunc/eeco/ehv/estphv.h>        /* vdg_estphv_emedi_dataget() */
#endif /* JEEGMG_E */
#if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E)         /*【SS制御有】OR【EG-MGｸﾗｯﾁ】*/
#include <engsrc/efunc/eeco/ess/estpss.h>        /* vdg_estpss_emedi_dataget() */
#include <engsrc/efunc/eeco/ess/estass.h>        /* vdg_estass_emedi_dataget() */
#endif /* JESS,JEEGMG_E */
#include <engsrc/efunc/eesta/eclrfld.h>          /* s2g_eclrfld_ekqstmxp,s2g_eclrfld_ekqstmxd */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
#include <engsrc/efunc/eesta/estafrg.h>          /* vdg_estafrg_emedi_dataget() */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
#include <engsrc/efunc/eesta/erestahot.h>        /* vdg_erestahot_emedi_dataget() */
#include <engsrc/efunc/eemi/ecat/esjc/esjc.h>    /* vdg_esjc_emedi_dataget() */
#include <engsrc/efunc/edrblty/eknk/ekcst.h>     /* vdg_ekcst_emedi_dataget() */
#endif /* JEEFI */
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (EMINJ_STAHV_MEDI == ON)      /*【ALL HV】AND【HV始動制御要求使用】*/
#include <engsrc/efunc/eeco/ehv/estahv.h>        /* vdg_estahv_emedi_dataget2() */
#endif /* JEALLHV_E,EMINJ_STAHV_MEDI */
#if JEALLHV_E == u1g_EJCC_ALLHV_E               /*【ALL HV】*/
#include <engsrc/efunc/eemi/ecat/ewupcat/ewupcat.h>  /* vdg_ewupcat_emedi_dataget(),f4g_ewupcat_ek1fptcat,f4g_ewupcat_ekpfitcat */
#endif /* JEALLHV_E */
#if JEEGMG_E == u1g_EJCC_HVCLUTCH_E             /*【EG-MGｸﾗｯﾁ】*/
#include <engsrc/efunc/efuncin/ectrlhv.h>        /* u1g_ectrlhv_exast */
#else                                           /* 【EG-MGｸﾗｯﾁ以外】 */
#include <engsrc/estate/estepin/exst.h>          /* u1g_exst_exastefi */
#endif /* JEEGMG_E */
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI != u1g_EJCC_D4)       /*【ALL HV】AND【D-4以外】*/
#include <engsrc/efunc/eemi/eoutgs/erdpn/erdpn.h>    /* vdg_erdpn_emedi_dataget(),f4g_erdpn_ek1fpt,f4g_erdpn_ekpfit,f4g_erdpn_ekpfitn[] */
#endif /* JEALLHV_E,JEEFI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
 #if JEFFV != u1g_EJCC_NOT_USE  /*【FFV制御有】*/
#include <engsrc/efunc/eemi/eactive/eactarefuel.h>   /* vdg_eactarefuel_emedi_dataget(),s2g_eactarefuel_ekpfit */
 #endif /* JEFFV */
#include <engsrc/efunc/eprotectf/efuel/eclrdepi.h>   /* vdg_eclrdepi_emedi_dataget() */
 #if JEPRDEMAND == u1g_EJCC_NOT_USE             /*【可変燃圧制御無】*/
#include <engsrc/efunc/edrblty/estblcomb/efpldlv.h>  /* vdg_efpldlv_emedi_dataget() */
 #endif /* JEPRDEMAND */
 #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_INJIMB_MEDI == ON)    /*【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ｲﾝﾊﾞﾗﾝｽ時の噴射制御要求使用】*/
#include <engsrc/efunc/eemi/eactive/einjimb.h>   /* vdg_einjimb_emedi_dataget() */
 #endif /* JEOBDAFIMB_D,EMINJ_INJIMB_MEDI */
 #if EMINJ_ACTOBD_MEDI == ON    /* 【OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
#include <engsrc/efunc/eemi/eactive/eactobd.h>   /* vdg_eactobd_emedi_dataget() */
 #endif /* EMINJ_ACTOBD_MEDI */
#include <engsrc/efunc/eemi/eactive/eactgaf.h>   /* vdg_eactgaf_emedi_dataget() */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
#include <engsrc/efunc/eeco/efc/ertnfc.h>        /* vdg_ertnfc_group00_dataget() */
 #if EMINJ_ACTLFG_MEDI == ON    /*【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】*/
#include <engsrc/efunc/eemi/eactive/eactlfg.h>   /* vdg_eactlfg_emedi_dataget(),vdg_eactlfg_emedi_dataget2() */
 #endif /* EMINJ_ACTLFG_MEDI */
#include <engsrc/efunc/eemi/eoutgs/estratist.h>  /* vdg_estratist_emedi_dataget(),s2g_estratist_ekpfit */
#include <engsrc/efunc/edrblty/eknk/ekctrn.h>    /* vdg_ekctrn_emedi_dataget() */
#endif /* JEEFI */
#include <engsrc/efunc/edrblty/etrq/epwrup.h>    /* vdg_epwrup_emedi_dataget() */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
#include <engsrc/efunc/eprotectf/efuel/edwnpr.h> /* vdg_edwnpr_emedi_dataget() */
#include <engsrc/efunc/eprotectf/efuel/erdvap.h> /* vdg_erdvap_emedi_dataget() */
#include <engsrc/efunc/eprotectf/efuel/eprvdil.h> /* vdg_eprvdil_emedi_dataget(),s2g_eprvdil_ekpfit */
#include <engsrc/efunc/efunctran/edthrctrl.h>    /* vdg_edthrctrl_emedi_dataget() */
#endif /* JEEFI */
#if (JENGPF_E != u1g_EJCC_NOT_USE) && (EMINJ_FCFRCTRL_MEDI == ON)  /*【GPF有】AND【1気筒FC制御要求使用】*/
#include <engsrc/efunc/efunctran/efcfrctrl.h>    /* vdg_efcfrctrl_emedi_dataget() */
#endif /* JENGPF_E,EMINJ_FCFRCTRL_MEDI */
#if (JEMAT_BENCHI == u1g_EJCC_USE) || (JEMAT_BENCH_E == u1g_EJCC_USE)   /*【ﾍﾞﾝﾁ適合用ｿﾌﾄ有】OR【ﾍﾞﾝﾁ適合ﾓｰﾄﾞ有】*/
#include <engsrc/efunc/eunusual/emat/ebench.h>   /* vdg_ebench_emedi_dataget() */
#endif /* JEMAT_BENCHI,JEMAT_BENCH_E */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
#include <engsrc/efunc/eprotectm/eexhaust/ecatotp.h> /* s2g_ecatotp_eainjadd */
#endif /* JEEFI */
#include <engsrc/efunc/eesta/ebstactr/ebstactr.h> /* st_EBSTACTR_EBSTACTR,vdg_ebstactr_ebstactr_dataget() */
#if ((JERMTCTR == u1g_EJCC_USE) || (JENVCTR == u1g_EJCC_USE)) && (JEMICN_E != u1g_EJCC_SUB_E) && (EMINJ_STACM_MEDI == ON)
  /* (【ﾘﾓｰﾄｺﾝﾄﾛｰﾙ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】) AND【SUB-CPU以外】AND【始動時吹け上がり制御要求使用】 */
#include <engsrc/efunc/eesta/estacm.h>           /* vdg_estacm_emedi_dataget() */
#endif /* JERMTCTR,JENVCTR,JEMICN_E,EMINJ_STACM_MEDI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
 #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_IMBRQ_MEDI == ON)  /*【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
#include <engsrc/efunc/eemi/eactive/eimbrq.h>  /* vdg_eimbrq_emedi_dataget() */
 #endif /* JEOBDAFIMB_D,EMINJ_IMBRQ_MEDI */
 #if (JEOBDMF == u1g_EJCC_USE) && (EMINJ_MFINJRQ_MEDI == ON)  /*【失火OBD有】AND【失火OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
#include <engsrc/efunc/eemi/eactive/emfinjrq.h>  /* vdg_emfinjrq_emedi_dataget() */
 #endif /* JEOBDMF,EMINJ_MFINJRQ_MEDI */
 #if (JEOBDFKG == u1g_EJCC_USE) && (EMINJ_FKGDRQ_MEDI == ON)  /* 【燃料OBD有】AND【燃料系OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
#include <engsrc/efunc/eemi/eactive/efkgdrq.h>  /* vdg_efkgdrq_emedi_dataget() */
 #endif /* JEOBDFKG,EMINJ_FKGDRQ_MEDI */
#endif /* JEEFI */
#include <engsrc/etran/einj/ebinjctr.h>          /* st_EBINJCTR_EBINJCTR,vdg_ebinjctr_ebinjctr_dataget() */
#include <engsrc/etran/einj/einjadd.h>           /* s2g_einjadd_eainjpadd,s2g_einjadd_eainjdadd */
#include <engsrc/etran/einj/efasta/emkrichb.h>   /* vdg_emkrichb_ekrichxb_get(),s2g_emkrichb_ekrichxbcrt[] */
#include <engsrc/etran/einj/efcinjctr.h>         /* vdg_efcinjctr_emedi_dataget() */
#include <engsrc/etran/einj/ebinj/eainjcut.h>    /* s2g_eainjcut_eainjcutp,s2g_eainjcut_eainjcutd */
#if (((JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_MEDI == ON)) \
   || ((JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_WC_MEDI == ON)) \
   || ((JEEGMG_E == u1g_EJCC_HVPLGR_E) && (JEFFV == u1g_EJCC_NOT_USE) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_STAHV_MEDI == ON)) \
   || (((JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)) && (JEPLMLT_E == u1g_EJCC_USE)))
   /* (【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】) */
   /* OR (【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】) */
   /* OR (【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】) */
   /* OR ((【ﾃﾞｭｱﾙINJ】OR【D-4】) AND【PLﾏﾙﾁ噴射有】) */
#include <engsrc/etran/einj/ebinjplctr.h>        /* f4g_ebinjplctr_ekpfit,f4g_ebinjplctr_ekpfitn[],vdg_ebinjplctr_emedi_dataget() */
                                                 /* vdg_ebinjplctr_wc_emedi_dataget(),vdg_ebinjplctr_stahv_emedi_dataget() */
                                                 /* s2g_ebinjplctr_eprreq */ /* temp:仕様確認の内容反映(DENG-STD-25017⑤) */
#endif /* JEPLMLT_E,EMINJ_BINJPLCTR_MEDI,JEALLHV_E,EMINJ_BINJPLCTR_WC_MEDI,JEEGMG_E,JEFFV,EMINJ_BINJPLCTR_STAHV_MEDI,JEEFI */
#if (JEEFI == u1g_EJCC_D4) || (JEEFI == u1g_EJCC_DUAL) /*【D-4】OR【ﾃﾞｭｱﾙINJ】*/
#include <engsrc/etran/einj/ebinj/eainjdb.h>     /* s2g_eainjdb_eainjdb1 */
#include <engsrc/etran/einj/ebinj/eprhpb.h>      /* s2g_eprhpb_eprhpb */
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_USE  /*【可変燃圧制御有】*/
#include <engsrc/eactmedi/einj/emprlp.h>                           /* s2g_emprlp_eprlp */
#else                           /*【可変燃圧制御無】*/
#include <engsrc/eactmedi/einj/emqlp.h>                            /* s2g_emqlp_eqlp */
#endif /* JEPRDEMAND */

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

#if !defined u1g_EJCC_DUAL
#error "u1g_EJCC_DUAL is undeclared"
#endif

#if !defined u1g_EJCC_PORT
#error "u1g_EJCC_PORT is undeclared"
#endif

#if !defined u1g_EJCC_NOX
#error "u1g_EJCC_NOX is undeclared"
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

#if !defined JENOX
#error "JENOX is undeclared"
#endif

#if !defined u1g_EJCC_TWIN
#error "u1g_EJCC_TWIN is undeclared"
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

#if !defined JEPLMLT_E
#error "JEPLMLT_E is undeclared"
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
/* 型定義                                                            */
/*-------------------------------------------------------------------*/
/* 噴射方式集約テーブル */
typedef struct
{
    void (* pt_dataget)( st_EMINJ_EMINJ_DEF * ptt_store );  /* 噴射方式データ取得関数ｱﾄﾞﾚｽ */
    u1 u1_id;                                               /* lsb=1 :ID */
} st_EMINJ_EMINJ_TBL;

typedef struct
{
    void (* pt_dataget2)( st_EMINJ_EMINJ_BUF * ptt_store ); /* 噴射方式データ取得関数ｱﾄﾞﾚｽ */
    u1 u1_id;                                               /* lsb=1 :ID */
} st_EMINJ_EMINJ_TBL2;

/*-------------------------------------------------------------------*/
/* macro定義                                                         */
/*-------------------------------------------------------------------*/
/* $$$マクロ定数_標準_v4.11 */
#define s2s_EMINJ_KRICHI (s2g_glround((1.0)/((32.*2.)/128./256.)))      /* m=eminj,lsb=(32*2)/128/256,ofs=,unit=倍 :増量補正係数初期値 */

#if (JEEFI != u1g_EJCC_D4)                                              /* 【D-4以外】 */
#define s2s_EMINJ_AINJP_VD (s2g_ELSB_AOP(120.03125))                    /* m=eminj,lsb=1024/128/256,ofs=,unit=BTDC :ﾎﾟｰﾄ噴射開始時期無効値 */
#define s2s_EMINJ_AINJP_MN (s2g_ELSB_AOP(120.03125))                    /* m=eminj,lsb=1024/128/256,ofs=,unit=BTDC :ポート噴射開始時期下限値 */
#define s2s_EMINJ_AINJP_MX (s2g_ELSB_AOP(840.))                         /* m=eminj,lsb=1024/128/256,ofs=,unit=BTDC :ポート噴射開始時期上限値 */
#define s2s_EMINJ_K1F_VD (s2g_glround((0.)/((1.*4.)/128./256.)))        /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :1回目噴射量算出係数無効値 */
#endif                                                                  /* JEEFI */

#if (JEEFI == u1g_EJCC_PORT)                                            /* 【ﾎﾟｰﾄ】 */
#define s2s_EMINJ_AINJPADD_MN (s2g_ELSB_AOP(120.))                      /* m=eminj,lsb=1024/128/256,ofs=,unit=BTDC :ポート追加噴射開始時期下限値 */
#define s2s_EMINJ_AINJPADD_MX (s2g_ELSB_AOP(360.))                      /* m=eminj,lsb=1024/128/256,ofs=,unit=BTDC :ポート追加噴射開始時期上限値 */
#endif                                                                  /* JEEFI */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                  /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
#define s2s_EMINJ_AINJD_VD (s2g_ELSB_AOP(-180.))                        /* m=eminj,lsb=1024/128/256,ofs=,unit=BTDC :筒内噴射開始時期無効値 */

 #if (JECOMBCCPT_E == u1g_EJCC_SPRAYG_E)                                /* 【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】 */
#define s2s_EMINJ_AINJD_MN (s2g_ELSB_AOP(-180.))                        /* m=eminj,lsb=1024/128/256,ofs=,unit=BTDC :筒内噴射開始時期下限値 */

 #else                                                                  /* 【ｽﾌﾟﾚｰｶﾞｲﾄﾞ以外】 */
#define s2s_EMINJ_AINJD_MN (s2g_ELSB_AOP(0.))                           /* m=eminj,lsb=1024/128/256,ofs=,unit=BTDC :筒内噴射開始時期下限値 */
 #endif                                                                 /* JECOMBCCPT_E */

#define s2s_EMINJ_AINJD_MX (s2g_ELSB_AOP(540.))                         /* m=eminj,lsb=1024/128/256,ofs=,unit=BTDC :筒内噴射開始時期上限値 */
#define s2s_EMINJ_AINJDADD_MN (s2g_ELSB_AOP(0.))                        /* m=eminj,lsb=1024/128/256,ofs=,unit=BTDC :筒内追加噴射開始時期下限値 */
#define s2s_EMINJ_AINJDADD_MX (s2g_ELSB_AOP(360.))                      /* m=eminj,lsb=1024/128/256,ofs=,unit=BTDC :筒内追加噴射開始時期上限値 */
#endif                                                                  /* JEEFI */

#define s4s_EMINJ_QINJI (s4g_glround((0.)/((4096.*1024.)/128./256./256./256.))) /* m=eminj,lsb=(4096*1024)/128/256/256/256,ofs=,unit=mg/st :噴射量初期値 */
#define s4s_EMINJ_QINJ_VD (s4g_glround((0.)/((4096.*1024.)/128./256./256./256.)))   /* m=eminj,lsb=(4096*1024)/128/256/256/256,ofs=,unit=mg/st :噴射量無効値 */
#define s4s_EMINJ_QINJ_MN (s4g_glround((0.)/((4096.*1024.)/128./256./256./256.)))   /* m=eminj,lsb=(4096*1024)/128/256/256/256,ofs=,unit=mg/st :噴射量下限値 */
#define s4s_EMINJ_QINJ_MX (s4g_glround((2800.)/((4096.*1024.)/128./256./256./256.)))    /* m=eminj,lsb=(4096*1024)/128/256/256/256,ofs=,unit=mg/st :噴射量上限値 */
#define s4s_EMINJ_QINJST_MN (s4g_glround((0.)/((4096.*1024.)/128./256./256./256.))) /* m=eminj,lsb=(4096*1024)/128/256/256/256,ofs=,unit=mg/st :始動時噴射量下限値 */
#define s4s_EMINJ_QINJST_MX (s4g_glround((2800.)/((4096.*1024.)/128./256./256./256.)))  /* m=eminj,lsb=(4096*1024)/128/256/256/256,ofs=,unit=mg/st :始動時噴射量上限値 */
#define s4s_EMINJ_QINJFLFIX_VD (s4g_glround((0.)/((4096.*1024.)/128./256./256./256.)))  /* m=eminj,lsb=(4096*1024)/128/256/256/256,ofs=,unit=mg/st :FL固定噴射量無効値 */
#define s4s_EMINJ_QINJPLFIX_VD (s4g_glround((0.)/((4096.*1024.)/128./256./256./256.)))  /* m=eminj,lsb=(4096*1024)/128/256/256/256,ofs=,unit=mg/st :PL固定噴射量無効値 */
#define s2s_EMINJ_K1F_MN (s2g_glround((0.)/((1.*4.)/128./256.)))        /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :1回目噴射量算出係数下限値 */
#define s2s_EMINJ_K1F_MX (s2g_glround((1.)/((1.*4.)/128./256.)))        /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :1回目噴射量算出係数上限値 */
#define s2s_EMINJ_K1FN_MN (s2g_glround((0.)/((1.*4.)/128./256.)))       /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :1回目噴射量算出係数下限値(バンク別) */
#define s2s_EMINJ_K1FN_MX (s2g_glround((1.)/((1.*4.)/128./256.)))       /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :1回目噴射量算出係数上限値(バンク別) */
#define s2s_EMINJ_K2F_MN (s2g_glround((0.)/((1.*4.)/128./256.)))        /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :2回目噴射量算出係数下限値 */
#define s2s_EMINJ_K2F_MX (s2g_glround((1.)/((1.*4.)/128./256.)))        /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :2回目噴射量算出係数上限値 */
#define s2s_EMINJ_K2FN_MN (s2g_glround((0.)/((1.*4.)/128./256.)))       /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :2回目噴射量算出係数下限値(バンク別) */
#define s2s_EMINJ_K2FN_MX (s2g_glround((1.)/((1.*4.)/128./256.)))       /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :2回目噴射量算出係数上限値(バンク別) */
#define s2s_EMINJ_K3F_MN (s2g_glround((0.)/((1.*4.)/128./256.)))        /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :3回目噴射量算出係数下限値 */
#define s2s_EMINJ_K3F_MX (s2g_glround((1.)/((1.*4.)/128./256.)))        /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :3回目噴射量算出係数上限値 */
#define s2s_EMINJ_K3FN_MN (s2g_glround((0.)/((1.*4.)/128./256.)))       /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :3回目噴射量算出係数下限値(バンク別) */
#define s2s_EMINJ_K3FN_MX (s2g_glround((1.)/((1.*4.)/128./256.)))       /* m=eminj,lsb=(1*4)/128/256,ofs=,unit=倍 :3回目噴射量算出係数上限値(バンク別) */
#define s2s_EMINJ_KRCHREF_MN (s2g_glround((0.)/((32.*2.)/128./256.)))   /* m=eminj,lsb=(32*2)/128/256,ofs=,unit=倍 :噴射量補正係数下限値 */
#define s2s_EMINJ_KRCHREF_MX (s2g_glround((30.)/((32.*2.)/128./256.)))  /* m=eminj,lsb=(32*2)/128/256,ofs=,unit=倍 :噴射量補正係数上限値 */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                  /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
#define u1s_EMINJ_RESTAHOT_ID ((u1)(((32.)/(1.))+0.5))                  /* m=eminj,lsb=1,ofs=,unit=- :高温再始動制御(ID) */
#define u1s_EMINJ_KCST_ID ((u1)(((34.)/(1.))+0.5))                      /* m=eminj,lsb=1,ofs=,unit=- :始動時ﾉｯｸ防止制御(ID) */
#endif                                                                  /* JEEFI */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                  /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
#define u1s_EMINJ_RTNFC_ID ((u1)(((54.)/(1.))+0.5))                     /* m=eminj,lsb=1,ofs=,unit=- :FC復帰制御(ID) */
#endif                                                                  /* JEEFI */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
#define u1s_EMINJ_CLRDEPI_ID ((u1)(((56.)/(1.))+0.5))                   /* m=eminj,lsb=1,ofs=,unit=- :ｱｲﾄﾞﾙ時ｲﾝｼﾞｪｸﾀﾃﾞﾎﾟ除去制御(ID) */
#endif                                                                  /* JEEFI */

#if (JEEFI == u1g_EJCC_DUAL) && (JEPRDEMAND == u1g_EJCC_NOT_USE)        /* 【ﾃﾞｭｱﾙINJ】AND【可変燃圧制御無】 */
#define u1s_EMINJ_FPLDLV_ID ((u1)(((60.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :低圧ﾃﾞﾘﾊﾞﾘ内燃料脈動回避制御(ID) */
#endif                                                                  /* JEEFI JEPRDEMAND */

#if (JEOBDAFIMB_D == u1g_EJCC_USE) && (JEEFI == u1g_EJCC_DUAL) && (EMINJ_INJIMB_MEDI == ON) /* 【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ﾃﾞｭｱﾙINJ】AND【ｲﾝﾊﾞﾗﾝｽ時の噴射制御要求使用】 */
#define u1s_EMINJ_INJIMB_ID ((u1)(((72.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :ｲﾝﾊﾞﾗﾝｽ時の噴射制御(ID) */
#endif                                                                  /* JEOBDAFIMB_D JEEFI EMINJ_INJIMB_MEDI */

#if (JEEFI == u1g_EJCC_DUAL) && (JEFFV != u1g_EJCC_NOT_USE)             /* 【ﾃﾞｭｱﾙINJ】AND【FFV制御有】 */
#define u1s_EMINJ_ACTAREFUEL_ID ((u1)(((74.)/(1.))+0.5))                /* m=eminj,lsb=1,ofs=,unit=- :給油後の噴き分けｱｸﾃｨﾌﾞ制御(ID) */
#endif                                                                  /* JEEFI JEFFV */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                  /* 【ﾃﾞｭｱﾙINJ】OR【D-4】 */
#define u1s_EMINJ_KCTRN_ID ((u1)(((86.)/(1.))+0.5))                     /* m=eminj,lsb=1,ofs=,unit=- :発進ﾉｯｸ防止制御(ID) */
#endif                                                                  /* JEEFI */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
#define u1s_EMINJ_RDVAP_ID ((u1)(((88.)/(1.))+0.5))                     /* m=eminj,lsb=1,ofs=,unit=- :ﾍﾞｰﾊﾟｰ抑制制御(ID) */
#define u1s_EMINJ_DWNPR_ID ((u1)(((90.)/(1.))+0.5))                     /* m=eminj,lsb=1,ofs=,unit=- :燃圧低減制御(ID) */
#endif                                                                  /* JEEFI */

#define u1s_EMINJ_PWRUP_ID ((u1)(((92.)/(1.))+0.5))                     /* m=eminj,lsb=1,ofs=,unit=- :出力性能向上制御(ID) */

#if JEEFI == u1g_EJCC_DUAL                                              /* 【ﾃﾞｭｱﾙINJ】 */
#define u1s_EMINJ_PRVDIL_ID ((u1)(((96.)/(1.))+0.5))                    /* m=eminj,lsb=1,ofs=,unit=- :冷間時希釈防止制御(ID) */
#endif                                                                  /* JEEFI */

/* $$$マクロ定数_標準_v4.11 */
#define u4s_EMINJ_NORQDAT       ((u4)0x00000000U)   /* lsb=1 :調停要求無し */

/*-------------------------------------------------------------------*/
/* 変数定義                                                          */
/*-------------------------------------------------------------------*/
st_EMINJ_EMINJ stg_eminj_eminj;             /* 新噴射方式調停構造体 */
                                            /* 注意事項 :アクセスには専用関数を使用すること */

st_EMINJ_EINJ stg_eminj_einj;               /* 噴射方式調停構造体 */
                                            /* 注意事項 :アクセスには専用関数を使用すること */

u2 u2g_eminj_einjmodfix;                    /* m=eminj,lsb=1 :現在確定噴射ﾓｰﾄﾞ */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
f4 f4g_eminj_einjend;                       /* m=eminj,unit=BTDC :ポート噴射終了時期 */
s2 s2g_eminj_eainjpn[5];                    /* m=eminj,lsb=1024/128/256,unit=BTDC :ポートn回目噴射開始時期(噴射回数配列) */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
f4 f4g_eminj_eainjpn[5];                    /* m=eminj,unit=BTDC :ポートn回目噴射開始時期(噴射回数配列) */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
s4 s4g_eminj_eqinjstpn[5];                  /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポートn回目始動時噴射量（噴射回数配列） */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
f4 f4g_eminj_eqinjstpn[5];                  /* m=eminj,unit=mg/st :ポートn回目始動時噴射量（噴射回数配列） */ /* 2025年の5回噴射まで考慮し配列要素は[5]として定義する */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
f4 f4g_eminj_eainjd1fix;                    /* m=eminj,unit=BTDC :確定筒内1回目噴射開始時期 */
f4 f4g_eminj_eainjd2fix;                    /* m=eminj,unit=BTDC :確定筒内2回目噴射開始時期 */
f4 f4g_eminj_eainjd3fix;                    /* m=eminj,unit=BTDC :確定筒内3回目噴射開始時期 */
f4 f4g_eminj_eainjd4fix;                    /* m=eminj,unit=BTDC :確定筒内4回目噴射開始時期 */
f4 f4g_eminj_eainjd5fix;                    /* m=eminj,unit=BTDC :確定筒内5回目噴射開始時期 */
f4 f4g_eminj_eainjd6fix;                    /* m=eminj,unit=BTDC :確定筒内6回目噴射開始時期 */
s2 s2g_eminj_eainjdn[6];                    /* m=eminj,lsb=1024/128/256,unit=BTDC :筒内n回目噴射開始時期(噴射回数配列) */ /* 始動時に最大6回噴射(直噴のみ) */
f4 f4g_eminj_eainjdn[6];                    /* m=eminj,unit=BTDC :筒内n回目噴射開始時期(噴射回数配列) */ /* 始動時に最大6回噴射(直噴のみ) */
f4 f4g_eminj_eqinjstd1;                     /* m=eminj,unit=mg/st :筒内1回目始動時噴射量 */
f4 f4g_eminj_eqinjstd2;                     /* m=eminj,unit=mg/st :筒内2回目始動時噴射量 */
f4 f4g_eminj_eqinjstd3;                     /* m=eminj,unit=mg/st :筒内3回目始動時噴射量 */
f4 f4g_eminj_eqinjstd4;                     /* m=eminj,unit=mg/st :筒内4回目始動時噴射量 */
s4 s4g_eminj_eqinjstdn[6];                  /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内n回目始動時噴射量（噴射回数配列） */ /* 始動時に最大6回噴射(直噴のみ) */
f4 f4g_eminj_eqinjstdn[6];                  /* m=eminj,unit=mg/st :筒内n回目始動時噴射量（噴射回数配列） */ /* 始動時に最大6回噴射(直噴のみ) */
#endif /* JEEFI */
s4 s4g_eminj_eqfc[u1g_EJCC_NCYL];           /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :FC中噴射量 */
f4 f4g_eminj_eqfc[u1g_EJCC_NCYL];           /* m=eminj,unit=mg/st :FC中噴射量 */
s2 s2g_eminj_ek1fn[u1g_EJCC_NOX];           /* m=eminj,lsb=(1*4)/128/256,unit=倍 :1回目噴射量算出係数(バンク別) */
f4 f4g_eminj_ek1fn[u1g_EJCC_NOX];           /* m=eminj,unit=倍 :1回目噴射量算出係数(バンク別) */
s2 s2g_eminj_ek2fn[u1g_EJCC_NOX];           /* m=eminj,lsb=(1*4)/128/256,unit=倍 :2回目噴射量算出係数(バンク別) */
f4 f4g_eminj_ek2fn[u1g_EJCC_NOX];           /* m=eminj,unit=倍 :2回目噴射量算出係数(バンク別) */
s2 s2g_eminj_ek3fn[u1g_EJCC_NOX];           /* m=eminj,lsb=(1*4)/128/256,unit=倍 :3回目噴射量算出係数(バンク別)  */
f4 f4g_eminj_ek3fn[u1g_EJCC_NOX];           /* m=eminj,unit=倍 :3回目噴射量算出係数(バンク別)  */
f4 f4g_eminj_ek1ffix;                       /* m=eminj,unit=倍 :確定1回目噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
f4 f4g_eminj_ek2ffix;                       /* m=eminj,unit=倍 :確定2回目噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
f4 f4g_eminj_ek3ffix;                       /* m=eminj,unit=倍 :確定3回目噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
s2 s2g_eminj_ekpfi;                         /* m=eminj,lsb=(1*4)/128/256,unit=倍 :ポート噴射量算出係数 */
f4 f4g_eminj_ekpfi;                         /* m=eminj,unit=倍 :ポート噴射量算出係数 */
s2 s2g_eminj_ekpfix;                        /* m=eminj,lsb=(1*4)/128/256,unit=倍 :ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
f4 f4g_eminj_ekpfix;                        /* m=eminj,unit=倍 :ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
s2 s2g_eminj_ekpfin[u1g_EJCC_NOX];          /* m=eminj,lsb=(1*4)/128/256,unit=倍 :ポート噴射量算出係数(バンク別) */
f4 f4g_eminj_ekpfin[u1g_EJCC_NOX];          /* m=eminj,unit=倍 :ポート噴射量算出係数(バンク別) */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
s2 s2g_eminj_eprreq;                        /* m=eminj,lsb=(32*2)/128/256,unit=MPa :高圧ポンプ目標燃圧 */
f4 f4g_eminj_eprreq;                        /* m=eminj,unit=MPa :高圧ポンプ目標燃圧 */
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_NOT_USE          /*【可変燃圧制御無】*/
s2 s2g_eminj_eqfreq;                        /* m=eminj,lsb=512/128/256,unit=L/h :燃料ポンプ吐出流量 */
#else                           /*【可変燃圧制御有】*/
s2 s2g_eminj_eprreql;                       /* m=eminj,lsb=1280/128/256,unit=kPa :低圧ポンプ目標燃圧 */
f4 f4g_eminj_eprreql;                       /* m=eminj,unit=kPa :低圧ポンプ目標燃圧 */
#endif /* JEPRDEMAND */
u1 u1g_eminj_einjmedislid;                  /* m=eminj,lsb=1 :噴射方式反映識別子 */
s2 s2g_eminj_ekrichx;                       /* m=eminj,lsb=(32*2)/128/256,unit=倍 :噴射量補正係数 */
f4 f4g_eminj_ekrichx;                       /* m=eminj,unit=倍 :噴射量補正係数 */
s2 s2g_eminj_ekrchref[u1g_EJCC_NOX];        /* m=eminj,lsb=(32*2)/128/256,unit=倍 :噴射量補正係数(バンク別) */
f4 f4g_eminj_ekrchref[u1g_EJCC_NOX];        /* m=eminj,unit=倍 :噴射量補正係数(バンク別) */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
s2 s2g_eminj_ekpfit;                        /* m=eminj,lsb=(1*4)/128/256,unit=倍 :目標ポート噴射量算出係数 */
s2 s2g_eminj_ekpfitn[u1g_EJCC_NOX];         /* m=eminj,lsb=(1*4)/128/256,unit=倍 :目標ポート噴射量算出係数(バンク別) */
f4 f4g_eminj_ekpfitn[u1g_EJCC_NOX];         /* m=eminj,unit=倍 :目標ポート噴射量算出係数(バンク別) */
 #if JEEGR == u1g_EJCC_USE      /*【EGR制御有】*/
f4 f4g_eminj_ekpfiegrn[u1g_EJCC_NOX];       /* m=eminj,unit=倍 :EGR-ON時の目標ポート噴射量算出係数(バンク別) */
 #endif /* JEEGR */
#endif /* JEEFI */
s4 s4g_eminj_eqinjflfix[8];                 /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :FL固定噴射量 */
f4 f4g_eminj_eqinjflfix[8];                 /* m=eminj,unit=mg/st :FL固定噴射量 */
s4 s4g_eminj_eqinjplfix[8];                 /* m=eminj,lsb=(4096*1024)/128/256/256/256,unit=mg/st :PL固定噴射量 */
f4 f4g_eminj_eqinjplfix[8];                 /* m=eminj,unit=mg/st :PL固定噴射量 */

static u1 u1s_eminj_estpri;                 /* lsb=1 :始動時要求の優先度 */
static u1 u1s_eminj_estpri2;                /* lsb=1 :始動時要求2の優先度 */
static u1 u1s_eminj_estprir;                /* lsb=1 :始動時要求と始動時要求2調停の優先度履歴 */
static u1 u1s_eminj_eastpri;                /* lsb=1 :始動後要求の優先度 */
static u1 u1s_eminj_eastpri2;               /* lsb=1 :始動後要求2の優先度 */
static u1 u1s_eminj_exastmedi;              /* lsb=1 :始動後要求調停許可フラグ */
static u4 u4s_eminj_erqdat[2];              /* lsb=1 :要求噴射方式要求有識別子 */
static u1 u1s_eminj_epri;                   /* lsb=1 :通常要求の優先度 */
static u1 u1s_eminj_epri2;                  /* lsb=1 :通常要求2の優先度 */
static u1 u1s_eminj_exasto;                 /* lsb=1 :始動後フラグ(前回値) */
static u1 u1s_eminj_exast_lch;              /* lsb=1 :始動後フラグ(ラッチ用(t_xast)) */
static u1 u1s_eminj_exnercdfew;             /* lsb=1 :NEタスク少判定フラグ */
static u1 u1s_eminj_eprisel_fix;            /* lsb=1 :最高優先度 */
static u1 u1s_eminj_eprifix;                /* lsb=1 :確定優先度(機能解析用のﾓﾆﾀ変数) */

/* 集約対象部品のdataget関数が複数回参照となるものはNRAMに退避しラッパー関数にてアクセスする */
/* 8msm内で集約対象のget関数コールを1度にしテーブル間でデータの整合をとる */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)          /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
static st_EMINJ_EMINJ_DEF sts_eminj_erestahot_data;
#endif /* JEEFI */
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI != u1g_EJCC_D4)       /*【ALL HV】AND【D-4以外】*/
static st_EMINJ_EMINJ_DEF sts_eminj_erdpn_data;
#endif /* JEALLHV_E,JEEFI */

/* モニタ変数定義 */
#ifdef M_EMINJ       /* デバッグモード */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
static s2 s2s_eminj_einjend_mon;            /* lsb=1024/128/256,unit=BTDC :ポート噴射終了時期(モニタ用) */
static s2 s2s_eminj_eminj_einjend_mon;      /* lsb=1024/128/256,unit=BTDC :ポート噴射終了時期(モニタ用) */
#endif /* JEEFI */
/* u2s_eminj_einjmod_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eainjp1_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eainjp1_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eainjp2_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eainjp2_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eainjp3_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eainjp3_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eainjp4_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eainjp4_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eainjcutp_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eainjcutp_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eainjd1_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eainjd1_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eainjd2_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eainjd2_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eainjd3_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eainjd3_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eainjd4_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eainjd4_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eainjcutd_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eainjcutd_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eainjpadd_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eainjdadd_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s4s_eminj_eqinjstp1_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eqinjstp1_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s4s_eminj_eqinjstp2_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eqinjstp2_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s4s_eminj_eqinjstp3_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eqinjstp3_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s4s_eminj_eqinjstp4_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eqinjstp4_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s4s_eminj_eqinjstd1_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s4s_eminj_eqinjstd2_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s4s_eminj_eqinjstd3_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s4s_eminj_eqinjstd4_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s4s_eminj_eqinjexp_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eqinjexp_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_ek1f_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_ek1f_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_ek2f_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_ek2f_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_ek3f_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_ek3f_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* u1s_eminj_exqinjast_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* u1s_eminj_explreq_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_ekpfit_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_ek1fpt_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_ek1fpt_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_ekpfiegr_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_einjend_monは、f4g_eminj_einjendで代用可能 */
/* f4s_eminj_eqinjstd1_monは、f4g_eminj_eqinjstd1で代用可能 */
/* f4s_eminj_eqinjstd2_monは、f4g_eminj_eqinjstd2で代用可能 */
/* f4s_eminj_eqinjstd3_monは、f4g_eminj_eqinjstd3で代用可能 */
/* f4s_eminj_eqinjstd4_monは、f4g_eminj_eqinjstd4で代用可能 */
/* s2s_eminj_ekpfit_monは、s2g_eminj_ekpfitで代用可能 */
/* stt_injdat.u1_exqinjastのモニタ変数は、u1s_eminj_exqinjast_monで代用可能 */
/* s4s_eminj_eqfc_mon[u1g_EJCC_NCYL]は、s4g_eminj_eqfc[u1g_EJCC_NCYL]で代用可能 */
/* f4s_eminj_eqfc_mon[u1g_EJCC_NCYL]は、f4g_eminj_eqfc[u1g_EJCC_NCYL]で代用可能 */
/* s2s_eminj_ek1fn_mon[u1g_EJCC_NOX]は、s2g_eminj_ek1fn[u1g_EJCC_NOX]で代用可能 */
/* f4s_eminj_ek1fn_mon[u1g_EJCC_NOX]は、f4g_eminj_ek1fn[u1g_EJCC_NOX]で代用可能 */
/* s2s_eminj_ek2fn_mon[u1g_EJCC_NOX]は、s2g_eminj_ek2fn[u1g_EJCC_NOX]で代用可能 */
/* f4s_eminj_ek2fn_mon[u1g_EJCC_NOX]は、f4g_eminj_ek2fn[u1g_EJCC_NOX]で代用可能 */
/* s2s_eminj_ek3fn_mon[u1g_EJCC_NOX]は、s2g_eminj_ek3fn[u1g_EJCC_NOX]で代用可能 */
/* f4s_eminj_ek3fn_mon[u1g_EJCC_NOX]は、f4g_eminj_ek3fn[u1g_EJCC_NOX]で代用可能 */
/* s2s_eminj_ekrchref_mon[u1g_EJCC_NOX]は、s2g_eminj_ekrchref[u1g_EJCC_NOX]で代用可能 */
/* f4s_eminj_ekrchref_mon[u1g_EJCC_NOX]は、f4g_eminj_ekrchref[u1g_EJCC_NOX]で代用可能 */
/* s2s_eminj_ekpfitn_mon[u1g_EJCC_NOX]は、s2g_eminj_ekpfitn[u1g_EJCC_NOX]で代用可能 */
/* f4s_eminj_ekpfitn_mon[u1g_EJCC_NOX]は、f4g_eminj_ekpfitn[u1g_EJCC_NOX]で代用可能 */
/* f4s_eminj_ekpfiegrn_mon[u1g_EJCC_NOX]は、f4g_eminj_ekpfiegrn[u1g_EJCC_NOX]で代用可能 */
/* u2s_eminj_eminj_einjmod_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* u4s_eminj_eminj_einjptn_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eminj_eainjcutp_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eminj_eainjcutp_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eminj_eainjcutd_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eminj_eainjcutd_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eminj_eainjpadd_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eminj_eainjdadd_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s4s_eminj_eminj_eqinjexp_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eminj_eqinjexp_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* u1s_eminj_eminj_exqinjast_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* u1s_eminj_eminj_explreq_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eminj_ekpfit_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eminj_ek1fpt_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eminj_ek1fpt_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* f4s_eminj_eminj_ekpfiegr_monは、vdg_eminj_8msmでのみ参照のため関数内で定義 */
/* s2s_eminj_eminj_eainjpn_mon[5]は、s2g_eminj_eainjpn[5]で代用可能 */
/* f4s_eminj_eminj_eainjpn_mon[5]は、f4g_eminj_eainjpn[5]で代用可能 */
/* f4s_eminj_eminj_einjend_monは、f4g_eminj_einjendで代用可能 */
/* s2s_eminj_eminj_eainjdn_mon[6]は、s2g_eminj_eainjdn[6]で代用可能 */
/* f4s_eminj_eminj_eainjdn_mon[6]は、f4g_eminj_eainjdn[6]で代用可能 */
/* s4s_eminj_eminj_eqinjstpn_mon[5]は、s4g_eminj_eqinjstpn[5]で代用可能 */
/* f4s_eminj_eminj_eqinjstpn_mon[5]は、f4g_eminj_eqinjstpn[5]で代用可能 */
/* s4s_eminj_eminj_eqinjstdn_mon[6]は、s4g_eminj_eqinjstdn[6]で代用可能 */
/* f4s_eminj_eminj_eqinjstdn_mon[6]は、f4g_eminj_eqinjstdn[6]で代用可能 */
/* s4s_eminj_eminj_eqfc_mon[u1g_EJCC_NCYL]は、s4g_eminj_eqfc[u1g_EJCC_NCYL]で代用可能 */
/* f4s_eminj_eminj_eqfc_mon[u1g_EJCC_NCYL]は、f4g_eminj_eqfc[u1g_EJCC_NCYL]で代用可能 */
/* s2s_eminj_eminj_ek1fn_mon[u1g_EJCC_NOX]は、s2g_eminj_ek1fn[u1g_EJCC_NOX]で代用可能 */
/* f4s_eminj_eminj_ek1fn_mon[u1g_EJCC_NOX]は、f4g_eminj_ek1fn[u1g_EJCC_NOX]で代用可能 */
/* s2s_eminj_eminj_ek2fn_mon[u1g_EJCC_NOX]は、s2g_eminj_ek2fn[u1g_EJCC_NOX]で代用可能 */
/* f4s_eminj_eminj_ek2fn_mon[u1g_EJCC_NOX]は、f4g_eminj_ek2fn[u1g_EJCC_NOX]で代用可能 */
/* s2s_eminj_eminj_ek3fn_mon[u1g_EJCC_NOX]は、s2g_eminj_ek3fn[u1g_EJCC_NOX]で代用可能 */
/* f4s_eminj_eminj_ek3fn_mon[u1g_EJCC_NOX]は、f4g_eminj_ek3fn[u1g_EJCC_NOX]で代用可能 */
/* s2s_eminj_eminj_ekrchref_mon[u1g_EJCC_NOX]は、s2g_eminj_ekrchref[u1g_EJCC_NOX]で代用可能 */
/* f4s_eminj_eminj_ekrchref_mon[u1g_EJCC_NOX]は、f4g_eminj_ekrchref[u1g_EJCC_NOX]で代用可能 */
/* stt_injdat2.u1_exqinjastのモニタ変数は、u1s_eminj_eminj_exqinjast_monで代用可能 */
/* s2s_eminj_eminj_ekpfit_monは、s2g_eminj_ekpfitで代用可能 */
/* s2s_eminj_eminj_ekpfitn_mon[u1g_EJCC_NOX]は、s2g_eminj_ekpfitn[u1g_EJCC_NOX]で代用可能 */
/* f4s_eminj_eminj_ekpfitn_mon[u1g_EJCC_NOX]は、f4g_eminj_ekpfitn[u1g_EJCC_NOX]で代用可能 */
/* f4s_eminj_eminj_ekpfiegrn_mon[u1g_EJCC_NOX]は、f4g_eminj_ekpfiegrn[u1g_EJCC_NOX]で代用可能 */
/* s4s_eminj_eminj_eqinjflfix_mon[8]は、s4g_eminj_eqinjflfix[8]で代用可能 */
/* f4s_eminj_eminj_eqinjflfix_mon[8]は、f4g_eminj_eqinjflfix[8]で代用可能 */
/* s4s_eminj_eminj_eqinjplfix_mon[8]は、s4g_eminj_eqinjplfix[8]で代用可能 */
/* f4s_eminj_eminj_eqinjplfix_mon[8]は、f4g_eminj_eqinjplfix[8]で代用可能 */
#endif /* M_EMINJ */

/*-------------------------------------------------------------------*/
/* 関数のprototype宣言                                               */
/*-------------------------------------------------------------------*/
static void vds_eminj_eminj_hpri( st_EMINJ_EMINJ_DEF *ptt_datsel, const st_EMINJ_EMINJ_DEF *ptt_datdft, st_EMINJ_EMINJ_BUF *ptt_datsel2, const st_EMINJ_EMINJ_BUF *ptt_datdft2 );       /* 噴射モードの調停(優先度選択) */
static void vds_eminj_eminjlmt_hpri( st_EMINJ_EMINJ_DEF *ptt_datsel, const st_EMINJ_EMINJ_DEF *ptt_datdft, st_EMINJ_EMINJ_BUF *ptt_datsel2, const st_EMINJ_EMINJ_BUF *ptt_datdft2 );    /* 調停制約時の噴射モードの調停(優先度選択) */
static void vds_eminj_einj_dataset( st_EMINJ_EINJ *ptt_store, const st_EMINJ_EINJ *ptt_data, u1 u1t_xnercdfew ); /* データ更新処理 */
static void vds_eminj_einj_datacopy( st_EMINJ_EMINJ_DEF *ptt_data, const st_EMINJ_EMINJ_DEF *ptt_copy );         /* 集約対象用構造体データコピー処理 */
static void vds_eminj_eminj_dataset( st_EMINJ_EMINJ *ptt_store, const st_EMINJ_EMINJ *ptt_data, u1 u1t_xnercdfew );   /* データ更新処理 */
static void vds_eminj_einj_datacopy2( st_EMINJ_EMINJ_BUF *ptt_data, const st_EMINJ_EMINJ_BUF *ptt_copy );             /* 集約対象用構造体データコピー処理 */
static void vds_eminj_einj_dataconv( st_EMINJ_EMINJ_BUF *ptt_data_new, const st_EMINJ_EMINJ_DEF *ptt_data_old );      /* 集約対象用旧→新構造体データ移行処理 */
static void vds_eminj_einj_dataconv_rev( st_EMINJ_EMINJ_DEF *ptt_data_old, const st_EMINJ_EMINJ_BUF *ptt_data_new );  /* 集約対象用新→旧構造体データ移行処理 */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)              /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
static void vds_eminj_erestahot_rap_dataget( st_EMINJ_EMINJ_DEF *ptt_store );
#endif /* JEEFI */
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI != u1g_EJCC_D4)       /*【ALL HV】AND【D-4以外】*/
static void vds_eminj_erdpn_rap_dataget( st_EMINJ_EMINJ_DEF *ptt_store );
#endif /* JEALLHV_E,JEEFI */
static void vds_eminj_dummy_emedi_dataget( st_EMINJ_EMINJ_DEF *ptt_store );
static void vds_eminj_dummy_emedi_dataget2( st_EMINJ_EMINJ_BUF *ptt_store );

/*-------------------------------------------------------------------*/
/* const data定義                                                    */
/*-------------------------------------------------------------------*/
/* 要素数 */
#define u1s_EMINJ_EMINJ_NUM     ((u1)(sizeof(sts_eminj_eminj_tbl)/sizeof(sts_eminj_eminj_tbl[0])))          /* lsb=256/256,unit=個 :噴射方式の優先度選択要素数 */
#define u1s_EMINJ_EMINJLMT_NUM  ((u1)(sizeof(sts_eminj_eminjlmt_tbl)/sizeof(sts_eminj_eminjlmt_tbl[0])))    /* lsb=256/256,unit=個 :噴射方式の優先度選択要素数(調停制約時) */
#define u1s_EMINJ_EMINJ_NUM2    ((u1)((u1)(sizeof(sts_eminj_eminj_tbl2)/sizeof(sts_eminj_eminj_tbl2[0])) - (u1)1))       /* lsb=256/256,unit=個 :噴射方式の優先度選択要素数 -1DUMMY */
#define u1s_EMINJ_EMINJLMT_NUM2 ((u1)((u1)(sizeof(sts_eminj_eminjlmt_tbl2)/sizeof(sts_eminj_eminjlmt_tbl2[0])) - (u1)1)) /* lsb=256/256,unit=個 :噴射方式の優先度選択要素数(調停制約時) -1DUMMY */
#define u1s_EMINJ_EMINJST_NUM   ((u1)((u1)(sizeof(sts_eminj_eminjst_tbl)/sizeof(sts_eminj_eminjst_tbl[0])) - (u1)1))     /* lsb=256/256,unit=個 :始動時要求優先度要素数 -1DUMMY */
#define u1s_EMINJ_EMINJST_NUM2  ((u1)((u1)(sizeof(sts_eminj_eminjst_tbl2)/sizeof(sts_eminj_eminjst_tbl2[0])) - (u1)1))   /* lsb=256/256,unit=個 :始動時要求優先度要素数 -1DUMMY */
#define u1s_EMINJ_EMINJAST_NUM  ((u1)((u1)(sizeof(sts_eminj_eminjast_tbl)/sizeof(sts_eminj_eminjast_tbl[0])) - (u1)1))   /* lsb=256/256,unit=個 :始動後要求優先度要素数 -1DUMMY */
#define u1s_EMINJ_EMINJAST_NUM2 ((u1)((u1)(sizeof(sts_eminj_eminjast_tbl2)/sizeof(sts_eminj_eminjast_tbl2[0])) - (u1)1)) /* lsb=256/256,unit=個 :始動後要求優先度要素数 -1DUMMY */

/*-------------------------------------------------------------------*/
/* 関数                                                              */
/*-------------------------------------------------------------------*/
/*********************************************************************/
/*  関数名        | vdg_eminj_pwon( )                                */
/*  処理内容      | 初期値設定                                       */
/*  制御タイミング| pwon                                             */
/*  引数          | なし                                             */
/*  戻り値        | なし                                             */
/*  注意事項      |                                                  */
/*********************************************************************/
void
vdg_eminj_pwon( void )
{
    u1 u1t_mox;    /* lsb=1 :メインセンサ数 */
    u1 u1t_nox_c;  /* lsb=1 :メインセンサ数 */
    s2 s2t_kpfi;   /* lsb=(1*4)/128/256,unit=倍 :ポート噴射量算出係数 */
    s2 s2t_kpfix;  /* lsb=(1*4)/128/256,unit=倍 :ﾎﾟｰﾄ噴射量算出係数(ﾊﾞﾝｸ間平均値(ﾂｲﾝｾﾝｻ)) */
    s2 s2t_kpfin[u1g_EJCC_NOX]; /* lsb=(1*4)/128/256,unit=倍 :ポート噴射量算出係数(バンク別) */
#if JEPRDEMAND == u1g_EJCC_USE       /*【可変燃圧制御有】*/
    s2 s2t_prreql; /* lsb=1280/128/256,unit=kPa :低圧ポンプ目標燃圧 */
#endif /* JEPRDEMAND */
    st_EMINJ_EINJ stt_injdat = { 0 };               /* 同時性構造体ワーク(一括初期化) */
    st_EMINJ_EMINJ stt_injdat2 = { 0 };             /* 同時性構造体ワーク(一括初期化) */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    st_EBINJCTR_EBINJCTR stt_binjctrdat = { 0 };    /* 同時性構造体ワーク(一括初期化) */
#endif /* JEEFI */

    u1t_nox_c = u1g_ejcc_NOX;

    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        stt_injdat.s2_ekrchref[u1t_mox] = s2s_EMINJ_KRICHI;
        stt_injdat.f4_ekrchref[u1t_mox] = (f4)(stt_injdat.s2_ekrchref[u1t_mox]) * (f4)((32.*2.)/128./256.);
        stt_injdat2.s2_ekrchref[u1t_mox] = stt_injdat.s2_ekrchref[u1t_mox];
        stt_injdat2.f4_ekrchref[u1t_mox] = stt_injdat.f4_ekrchref[u1t_mox];
    }
    s2g_eminj_ekrichx = s2s_EMINJ_KRICHI;
    f4g_eminj_ekrichx = (f4)s2s_EMINJ_KRICHI * (f4)((32.*2.)/128./256.);
#if JEEFI == u1g_EJCC_PORT      /*【ﾎﾟｰﾄ】*/
    s2t_kpfi = (s2)(((1.)/((1.*4.)/128./256.))+0.5);
    s2t_kpfix = (s2)(((1.)/((1.*4.)/128./256.))+0.5);
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        s2t_kpfin[u1t_mox] = (s2)(((1.)/((1.*4.)/128./256.))+0.5);
    }
#else                           /*【ﾎﾟｰﾄ以外】*/
    s2t_kpfi = (s2)(((0.)/((1.*4.)/128./256.))+0.5);
    s2t_kpfix = (s2)(((0.)/((1.*4.)/128./256.))+0.5);
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        s2t_kpfin[u1t_mox] = (s2)(((0.)/((1.*4.)/128./256.))+0.5);
    }
#endif /* JEEFI */
    s2g_eminj_ekpfi = s2t_kpfi;
    f4g_eminj_ekpfi = (f4)s2t_kpfi * (f4)((1.*4.)/128./256.);
    s2g_eminj_ekpfix = s2t_kpfix;
    f4g_eminj_ekpfix = (f4)s2t_kpfix * (f4)((1.*4.)/128./256.);
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        s2g_eminj_ekpfin[u1t_mox] = s2t_kpfin[u1t_mox];
        f4g_eminj_ekpfin[u1t_mox] = (f4)s2t_kpfin[u1t_mox] * (f4)((1.*4.)/128./256.);
    }
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    vdg_ebinjctr_ebinjctr_dataget( &stt_binjctrdat );   /* 同時性データ取得 */

    stt_injdat.s2_einjend = stt_binjctrdat.s2_einjendb;
    stt_injdat.f4_einjend = (f4)(stt_injdat.s2_einjend) * (f4)(1024./128./256.);
    stt_injdat2.s2_einjend = stt_injdat.s2_einjend;
    stt_injdat2.f4_einjend = stt_injdat.f4_einjend;
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_USE       /*【可変燃圧制御有】*/
    s2t_prreql = s2g_emprlp_eprlp;
    s2g_eminj_eprreql = s2t_prreql;
    f4g_eminj_eprreql = (f4)s2t_prreql * (f4)(1280./128./256.);
#endif /* JEPRDEMAND */
    vds_eminj_einj_dataset( &stg_eminj_einj, &stt_injdat, (u1)ON );
    vds_eminj_eminj_dataset( &stg_eminj_eminj, &stt_injdat2, (u1)ON );

#ifdef M_EMINJ       /* デバッグモード */
 #if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    s2s_eminj_einjend_mon = stt_injdat.s2_einjend;
    s2s_eminj_eminj_einjend_mon = stt_injdat2.s2_einjend;
 #endif /* JEEFI */
    /* s2s_eminj_ekrchref_mon[u1g_EJCC_NOX]は、s2g_eminj_ekrchref[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_ekrchref_mon[u1g_EJCC_NOX]は、f4g_eminj_ekrchref[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_einjend_monは、f4g_eminj_einjendで代用可能 */
    /* s2s_eminj_eminj_ekrchref_mon[u1g_EJCC_NOX]は、s2g_eminj_ekrchref[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_eminj_ekrchref_mon[u1g_EJCC_NOX]は、f4g_eminj_ekrchref[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_eminj_einjend_monは、f4g_eminj_einjendで代用可能 */

    /* 初期値に0が代入される変数は、モニタ変数への格納不要 */

#endif /* M_EMINJ */
}

/*********************************************************************/
/*  関数名        | vdg_eminj_8msm( )                                */
/*  処理内容      | 噴射要求の調停処理                               */
/*  制御タイミング| 8msm                                             */
/*  引数          | なし                                             */
/*  戻り値        | なし                                             */
/*  注意事項      |                                                  */
/*********************************************************************/
void
vdg_eminj_8msm( void )
{
    u1 u1t_xnercdfew;           /* lsb=1 :NEタスク少判定フラグ */
    u1 u1t_injmedislid;         /* lsb=1 :噴射方式反映識別子 */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s4 s4t_kqstmxd;             /* lsb=128/128/256,unit=倍 :筒内始動時噴射量制限係数 */
    u2 u2t_injmod;              /* lsb=1 :噴射モード */
    u2 u2t_injmod2;             /* lsb=1 :噴射モード */
    s2 s2t_ainjdadd;            /* lsb=1024/128/256,unit=BTDC :筒内追加噴射開始時期 */
    s2 s2t_ainjadd;             /* lsb=1024/128/256,unit=BTDC :瞬間OT防止追加噴射開始時期 */
    s2 s2t_ainjdaddmin;         /* lsb=1024/128/256,unit=BTDC :筒内追加噴射開始時期(最小値選択用) */
    u2 u2t_binjmodmsk00F0;      /* lsb=1 :ebinjctrの噴射モードを0x00F0でマスクした値 */
    u2 u2t_binjmodmsk0F0F;      /* lsb=1 :ebinjctrの噴射モードを0x0F0Fでマスクした値 */
    s2 s2t_ainjdb1;             /* lsb=1024/128/256,unit=BTDC :基本筒内噴射開始時期 */
    s2 s2t_ainjcutd;            /* lsb=1024/128/256,unit=BTDC :筒内噴射強制ｶｯﾄ時期 */
    s2 s2t_prhpb;               /* lsb=(32*2)/128/256,unit=MPa :高圧ﾎﾟﾝﾌﾟ基本目標燃圧 */
 #if JEPLMLT_E == u1g_EJCC_USE  /*【PLﾏﾙﾁ噴射有】*/ /* temp:仕様確認の内容反映(DENG-STD-25017⑤) start */
    s2 s2t_binjplctr_prreq;     /* lsb=(32*2)/128/256,unit=MPa :パーシャルリフトマルチ噴射高圧ポンプ目標燃圧 */
 #endif /* JEPLMLT_E */ /* temp:仕様確認の内容反映(DENG-STD-25017⑤) end */
#endif /* JEEFI */
    u4 u4t_rqdat[2];            /* lsb=1 :要求指示データ 0:旧構造体、1:新構造体 */
    u1 u1t_injnum;              /* lsb=1 :噴射段数 */
    u1 u1t_mox;                 /* lsb=1 :メインセンサ数 */
    u1 u1t_nox_c;               /* lsb=1 :メインセンサ数 */
    u1 u1t_cyl;                 /* lsb=1 :気筒数 */
    u1 u1t_ncyl_c;              /* lsb=1 :気筒数 */
    s2 s2t_krichxbcrt[u1g_EJCC_NOX]; /* lsb=(32*2)/128/256,unit=倍 :現在基本増量補正係数 */
    s2 s2t_krichx;              /* lsb=(32*2)/128/256,unit=倍 :噴射量補正係数 */
    s2 s2t_kpfi_wk;             /* lsb=(1*4)/128/256,unit=倍 :ﾎﾟｰﾄ噴射量算出係数ワーク */
    s2 s2t_kpfin[u1g_EJCC_NOX]; /* lsb=(1*4)/128/256,unit=倍 :ポート噴射量算出係数(バンク別) */
    s4 s4t_k1f;                 /* lsb=(1*4)/128/256,unit=倍 :1回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
    s4 s4t_k2f;                 /* lsb=(1*4)/128/256,unit=倍 :2回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
    s4 s4t_k3f;                 /* lsb=(1*4)/128/256,unit=倍 :3回目噴射量算出係数(バンク間平均値(ツインセンサ)) */
    u1 u1t_xqinjast;            /* lsb=1 :始動後噴射量要求ﾌﾗｸﾞ */
    u1 u1t_xqinjasto;           /* lsb=1 :始動後噴射量要求ﾌﾗｸﾞ前回値 */
    u1 u1t_xast;                /* lsb=1 :始動後フラグ */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    s2 s2t_ainjcutp;            /* lsb=1024/128/256,unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期 */
    s4 s4t_kqstmxp;             /* lsb=128/128/256,unit=倍 :ﾎﾟｰﾄ始動時噴射量制限係数 */
    u2 u2t_injmodmsk0F00;       /* lsb=1 :噴射モードを0x0F00でマスクした値 */
    u2 u2t_injmodmsk00F0;       /* lsb=1 :噴射モードを0x00F0でマスクした値 */
    u2 u2t_injmodmsk000F;       /* lsb=1 :噴射モードを0x000Fでマスクした値 */
 #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT)      /*【ALL HV】AND【ﾎﾟｰﾄ】*/
    f4 f4t_k1fptcat;            /* unit=倍 :触媒暖機ﾎﾟｰﾄ噴射のみ要求時ﾎﾟｰﾄ1回目噴射量算出係数 */
    f4 f4t_k1fpt;               /* unit=倍 :目標ﾎﾟｰﾄ1回目噴射量算出係数 */
 #endif /* JEALLHV_E,JEEFI */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
    s4 s4t_kpfi;                /* lsb=(1*4)/128/256,unit=倍 :ﾎﾟｰﾄ噴射量算出係数(始動時) */
    s4 s4t_qinjadd;             /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ﾎﾟｰﾄ噴射量算出用 */
    s4 s4t_qinjadd2;            /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ﾎﾟｰﾄ噴射量算出用2 */
    s4 s4t_qinjdiv;             /* lsb=(16*64)/128/256/256/256,unit=mg/st :ﾎﾟｰﾄ噴射量算出用(逆数値) */
    s2 s2t_kpfit;               /* lsb=(1*4)/128/256,unit=倍 :目標ﾎﾟｰﾄ噴射量算出係数 */
    s2 s2t_kpfitn[u1g_EJCC_NOX];    /* lsb=(1*4)/128/256,unit=倍 :目標ポート噴射量算出係数(バンク別) */
    s2 s2t_kpfit_eprvdil;       /* lsb=(1*4)/128/256,unit=倍 :目標ﾎﾟｰﾄ噴射量算出係数(eprvdil_ekpfit) */
 #if (((JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_MEDI == ON)) \
   || ((JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_WC_MEDI == ON)) \
   || ((JEEGMG_E == u1g_EJCC_HVPLGR_E) && (JEFFV == u1g_EJCC_NOT_USE) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_STAHV_MEDI == ON)))
   /* (【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】) */
   /* OR (【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】) */
   /* OR (【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】) */
    f4 f4t_kpfit;               /* unit=倍 :目標ポート噴射量算出係数(バンク間平均) */
    f4 f4t_kpfitn[u1g_EJCC_NOX];    /* unit=倍 :目標ポート噴射量算出係数(バンク別) */
    s2 s2t_kpfitplctr;          /* lsb=(1*4)/128/256,unit=倍 :目標ポート噴射量算出係数(バンク間平均) */
    s2 s2t_kpfitnplctr[u1g_EJCC_NOX]; /* lsb=(1*4)/128/256,unit=倍 :目標ポート噴射量算出係数(バンク別) */
 #endif /* JEPLMLT_E,EMINJ_BINJPLCTR_MEDI,JEALLHV_E,EMINJ_BINJPLCTR_WC_MEDI,JEEGMG_E,JEFFV,EMINJ_BINJPLCTR_STAHV_MEDI */
    s2 s2t_kpfit_estratist;     /* lsb=(1*4)/128/256,unit=倍 :成層始動制御時目標ﾎﾟｰﾄ噴射量算出係数 */
 #if JEALLHV_E == u1g_EJCC_ALLHV_E      /*【ALL HV】*/
    s2 s2t_kpfitcat;            /* lsb=(1*4)/128/256,unit=倍 :触媒暖機時目標ﾎﾟｰﾄ噴射量算出係数(ﾎﾟｰﾄ・筒内噴射割合) */
    s2 s2t_kpfit_erdpn;         /* lsb=(1*4)/128/256,unit=倍 :始動後ＰＮ低減制御時目標ﾎﾟｰﾄ噴射量算出係数(ﾎﾟｰﾄ筒内噴射割合) */
 #endif /* JEALLHV_E */
 #if JEFFV != u1g_EJCC_NOT_USE  /*【FFV制御有】*/
    s2 s2t_kpfit_eactarefuel;   /* lsb=(1*4)/128/256,unit=倍 :給油後燃料入れ替えの為の目標噴き分け率 */
 #endif /* JEFFV */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_PORT      /*【ﾎﾟｰﾄ】*/
    s2 s2t_ainjpadd;            /* lsb=1024/128/256,unit=BTDC :ﾎﾟｰﾄ追加噴射開始時期 */
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_NOT_USE    /*【可変燃圧制御無】*/
    s2 s2t_qlp;                 /* lsb=512/128/256,unit=L/h :低圧ﾎﾟﾝﾌﾟ目標吐出流量 */
#else                                 /*【可変燃圧制御有】*/
    s2 s2t_prlp;                /* lsb=1280/128/256,unit=kPa :低圧ﾎﾟﾝﾌﾟ目標燃圧 */
#endif /* JEPRDEMAND */
    st_EMINJ_EMINJ_DEF stt_minj_data = { 0 };       /* 調停用同時性構造体ワーク(一括初期化) */
    st_EMINJ_EMINJ_DEF stt_minj_datdft = { 0 };     /* 調停用同時性構造体デフォルト値(一括初期化) */
    st_EMINJ_EINJ stt_injdat = { 0 };               /* 同時性構造体ワーク(一括初期化) */
    st_EBINJCTR_EBINJCTR stt_binjctrdat = { 0 };    /* 同時性構造体ワーク(一括初期化) */
    st_EBSTACTR_EBSTACTR stt_bstactrdat = { 0 };    /* 同時性構造体ワーク(一括初期化) */
    st_EMINJ_EMINJ_BUF stt_minj_data2 = { 0 };      /* 調停用同時性構造体ワーク(一括初期化) */
    st_EMINJ_EMINJ_BUF stt_minj_datdft2 = { 0 };    /* 調停用同時性構造体デフォルト値(一括初期化) */
    st_EMINJ_EMINJ stt_injdat2 = { 0 };             /* 同時性構造体ワーク(一括初期化) */

    /* モニタ変数定義 */
#ifdef M_EMINJ       /* デバッグモード */
    volatile static u2 u2s_eminj_einjmod_mon;       /* lsb=1 :噴射モード(モニタ用) */
    volatile static u2 u2s_eminj_eminj_einjmod_mon; /* lsb=1 :噴射モード(モニタ用) */
    volatile static u4 u4s_eminj_eminj_einjptn_mon; /* lsb=1 :噴射パターン(モニタ用) */
 #if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    volatile static s2 s2s_eminj_eainjp1_mon;       /* lsb=1024/128/256,unit=BTDC :ポート1回目噴射開始時期(モニタ用) */
    volatile static f4 f4s_eminj_eainjp1_mon;       /* unit=BTDC :ポート1回目噴射開始時期(モニタ用) */
    volatile static s2 s2s_eminj_eainjp2_mon;       /* lsb=1024/128/256,unit=BTDC :ポート2回目噴射開始時期(モニタ用) */
    volatile static f4 f4s_eminj_eainjp2_mon;       /* unit=BTDC :ポート2回目噴射開始時期(モニタ用) */
    volatile static s2 s2s_eminj_eainjp3_mon;       /* lsb=1024/128/256,unit=BTDC :ポート3回目噴射開始時期(モニタ用) */
    volatile static f4 f4s_eminj_eainjp3_mon;       /* unit=BTDC :ポート3回目噴射開始時期(モニタ用) */
    volatile static s2 s2s_eminj_eainjp4_mon;       /* lsb=1024/128/256,unit=BTDC :ポート4回目噴射開始時期(モニタ用) */
    volatile static f4 f4s_eminj_eainjp4_mon;       /* unit=BTDC :ポート4回目噴射開始時期(モニタ用) */
    volatile static s2 s2s_eminj_eainjcutp_mon;     /* lsb=1024/128/256,unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期(モニタ用) */
    volatile static f4 f4s_eminj_eainjcutp_mon;     /* unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期(モニタ用) */
    volatile static s2 s2s_eminj_eminj_eainjcutp_mon;    /* lsb=1024/128/256,unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期(モニタ用) */
    volatile static f4 f4s_eminj_eminj_eainjcutp_mon;    /* unit=BTDC :ﾎﾟｰﾄ噴射強制ｶｯﾄ時期(モニタ用) */
 #endif /* JEEFI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    volatile static s2 s2s_eminj_eainjd1_mon;       /* lsb=1024/128/256,unit=BTDC :筒内1回目噴射開始時期(モニタ用) */
    volatile static f4 f4s_eminj_eainjd1_mon;       /* unit=BTDC :筒内1回目噴射開始時期(モニタ用) */
    volatile static s2 s2s_eminj_eainjd2_mon;       /* lsb=1024/128/256,unit=BTDC :筒内2回目噴射開始時期(モニタ用) */
    volatile static f4 f4s_eminj_eainjd2_mon;       /* unit=BTDC :筒内2回目噴射開始時期(モニタ用) */
    volatile static s2 s2s_eminj_eainjd3_mon;       /* lsb=1024/128/256,unit=BTDC :筒内3回目噴射開始時期(モニタ用) */
    volatile static f4 f4s_eminj_eainjd3_mon;       /* unit=BTDC :筒内3回目噴射開始時期(モニタ用) */
    volatile static s2 s2s_eminj_eainjd4_mon;       /* lsb=1024/128/256,unit=BTDC :筒内4回目噴射開始時期(モニタ用) */
    volatile static f4 f4s_eminj_eainjd4_mon;       /* unit=BTDC :筒内4回目噴射開始時期(モニタ用) */
    volatile static s2 s2s_eminj_eainjcutd_mon;     /* lsb=1024/128/256,unit=BTDC :筒内噴射強制ｶｯﾄ時期(モニタ用) */
    volatile static f4 f4s_eminj_eainjcutd_mon;     /* unit=BTDC :筒内噴射強制ｶｯﾄ時期(モニタ用) */
    volatile static s2 s2s_eminj_eminj_eainjcutd_mon;    /* lsb=1024/128/256,unit=BTDC :筒内噴射強制ｶｯﾄ時期(モニタ用) */
    volatile static f4 f4s_eminj_eminj_eainjcutd_mon;    /* unit=BTDC :筒内噴射強制ｶｯﾄ時期(モニタ用) */
 #endif /* JEEFI */
 #if JEEFI == u1g_EJCC_PORT      /*【ﾎﾟｰﾄ】*/
    volatile static s2 s2s_eminj_eainjpadd_mon;     /* lsb=1024/128/256,unit=BTDC :ポート追加噴射開始時期(モニタ用) */
    volatile static s2 s2s_eminj_eminj_eainjpadd_mon;    /* lsb=1024/128/256,unit=BTDC :ポート追加噴射開始時期(モニタ用) */
 #endif /* JEEFI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    volatile static s2 s2s_eminj_eainjdadd_mon;     /* lsb=1024/128/256,unit=BTDC :筒内追加噴射開始時期(モニタ用) */
    volatile static s2 s2s_eminj_eminj_eainjdadd_mon;    /* lsb=1024/128/256,unit=BTDC :筒内追加噴射開始時期(モニタ用) */
 #endif /* JEEFI */
 #if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    volatile static s4 s4s_eminj_eqinjstp1_mon;     /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート1回目始動時噴射量(モニタ用) */
    volatile static f4 f4s_eminj_eqinjstp1_mon;     /* unit=mg/st :ポート1回目始動時噴射量(モニタ用) */
    volatile static s4 s4s_eminj_eqinjstp2_mon;     /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート2回目始動時噴射量(モニタ用) */
    volatile static f4 f4s_eminj_eqinjstp2_mon;     /* unit=mg/st :ポート2回目始動時噴射量(モニタ用) */
    volatile static s4 s4s_eminj_eqinjstp3_mon;     /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート3回目始動時噴射量(モニタ用) */
    volatile static f4 f4s_eminj_eqinjstp3_mon;     /* unit=mg/st :ポート3回目始動時噴射量(モニタ用) */
    volatile static s4 s4s_eminj_eqinjstp4_mon;     /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :ポート4回目始動時噴射量(モニタ用) */
    volatile static f4 f4s_eminj_eqinjstp4_mon;     /* unit=mg/st :ポート4回目始動時噴射量(モニタ用) */
 #endif /* JEEFI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    volatile static s4 s4s_eminj_eqinjstd1_mon;     /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内1回目始動時噴射量(モニタ用) */
    volatile static s4 s4s_eminj_eqinjstd2_mon;     /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内2回目始動時噴射量(モニタ用) */
    volatile static s4 s4s_eminj_eqinjstd3_mon;     /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内3回目始動時噴射量(モニタ用) */
    volatile static s4 s4s_eminj_eqinjstd4_mon;     /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :筒内4回目始動時噴射量(モニタ用) */
 #endif /* JEEFI */
 #if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E                   /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    volatile static s4 s4s_eminj_eqinjexp_mon;      /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :膨張行程噴射量(モニタ用) */
    volatile static f4 f4s_eminj_eqinjexp_mon;      /* unit=mg/st :膨張行程噴射量(モニタ用) */
    volatile static s4 s4s_eminj_eminj_eqinjexp_mon;     /* lsb=(4096*1024)/128/256/256/256,unit=mg/st :膨張行程噴射量(モニタ用) */
    volatile static f4 f4s_eminj_eminj_eqinjexp_mon;     /* unit=mg/st :膨張行程噴射量(モニタ用) */
 #endif /* JECOMBCCPT_E */
    volatile static s2 s2s_eminj_ek1f_mon;          /* lsb=(1*4)/128/256,unit=倍 :1回目噴射量算出係数(モニタ用) */
    volatile static f4 f4s_eminj_ek1f_mon;          /* unit=倍 :1回目噴射量算出係数(モニタ用) */
    volatile static s2 s2s_eminj_ek2f_mon;          /* lsb=(1*4)/128/256,unit=倍 :2回目噴射量算出係数(モニタ用) */
    volatile static f4 f4s_eminj_ek2f_mon;          /* unit=倍 :2回目噴射量算出係数(モニタ用) */
    volatile static s2 s2s_eminj_ek3f_mon;          /* lsb=(1*4)/128/256,unit=倍 :3回目噴射量算出係数(モニタ用) */
    volatile static f4 f4s_eminj_ek3f_mon;          /* unit=倍 :3回目噴射量算出係数(モニタ用) */
    volatile static u1 u1s_eminj_exqinjast_mon;     /* lsb=1 :始動後噴射量要求フラグ(モニタ用) */
    volatile static u1 u1s_eminj_eminj_exqinjast_mon;    /* lsb=1 :始動後噴射量要求フラグ(モニタ用) */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    volatile static u1 u1s_eminj_explreq_mon;       /* lsb=1 :PL噴射実施要求(モニタ用) */
    volatile static u1 u1s_eminj_eminj_explreq_mon;      /* lsb=1 :PL噴射実施要求(モニタ用) */
 #endif /* JEEFI */
 #if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
    volatile static f4 f4s_eminj_ekpfit_mon;        /* unit=倍 :目標ポート噴射量算出係数(モニタ用) */
    volatile static f4 f4s_eminj_eminj_ekpfit_mon;       /* unit=倍 :目標ポート噴射量算出係数(モニタ用) */
 #endif /* JEEFI */
 #if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    volatile static s2 s2s_eminj_ek1fpt_mon;        /* lsb=(1*4)/128/256,unit=倍 :ﾎﾟｰﾄ噴射のみ要求時の目標ﾎﾟｰﾄ1回目噴射量算出係数(モニタ用) */
    volatile static f4 f4s_eminj_ek1fpt_mon;        /* unit=倍 :ﾎﾟｰﾄ噴射のみ要求時の目標ﾎﾟｰﾄ1回目噴射量算出係数(モニタ用) */
    volatile static s2 s2s_eminj_eminj_ek1fpt_mon;       /* lsb=(1*4)/128/256,unit=倍 :ﾎﾟｰﾄ噴射のみ要求時の目標ﾎﾟｰﾄ1回目噴射量算出係数(モニタ用) */
    volatile static f4 f4s_eminj_eminj_ek1fpt_mon;       /* unit=倍 :ﾎﾟｰﾄ噴射のみ要求時の目標ﾎﾟｰﾄ1回目噴射量算出係数(モニタ用) */
 #endif /* JEEFI */
 #if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
  #if JEEGR == u1g_EJCC_USE      /*【EGR制御有】*/
    volatile static f4 f4s_eminj_ekpfiegr_mon;      /* unit=倍 :EGR-ON時の目標ポート噴射量算出係数(モニタ用) */
    volatile static f4 f4s_eminj_eminj_ekpfiegr_mon;     /* unit=倍 :EGR-ON時の目標ポート噴射量算出係数(モニタ用) */
  #endif /* JEEGR */
 #endif /* JEEFI */
#endif /* M_EMINJ */

    /* NE同期タスク量判定 */
    u1t_xnercdfew = (u1)OFF;
    if ( s2g_ene_ene < s2s_eminj_NE_RCD )           /* NE同期タスクが少ない */
    {
        u1t_xnercdfew = (u1)ON;
    }
    u1s_eminj_exnercdfew = u1t_xnercdfew;

    u1t_ncyl_c = u1g_ejcc_NCYL;
    u1t_nox_c = u1g_ejcc_NOX;

    /* 同時性データ取得 */
    vdg_ebinjctr_ebinjctr_dataget( &stt_binjctrdat );
    vdg_ebstactr_ebstactr_dataget( &stt_bstactrdat );

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2t_ainjdb1 = s2g_eainjdb_eainjdb1;
    s2t_ainjcutd = s2g_eainjcut_eainjcutd;
    s2t_prhpb = s2g_eprhpb_eprhpb;
 #if JEPLMLT_E == u1g_EJCC_USE  /*【PLﾏﾙﾁ噴射有】*/ /* temp:仕様確認の内容反映(DENG-STD-25017⑤) start */
    s2t_binjplctr_prreq = s2g_ebinjplctr_eprreq;
 #endif /* JEPLMLT_E */ /* temp:仕様確認の内容反映(DENG-STD-25017⑤) end */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_PORT      /*【ﾎﾟｰﾄ】*/
    s2t_ainjpadd = s2g_einjadd_eainjpadd;
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    s2t_ainjcutp = s2g_eainjcut_eainjcutp;
 #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT)  /*【ALL HV】AND【ﾎﾟｰﾄ】*/
    f4t_k1fptcat = f4g_ewupcat_ek1fptcat;
    f4t_k1fpt = f4g_erdpn_ek1fpt;
 #endif /* JEALLHV_E,JEEFI */
#endif /* JEEFI */

#if JEPRDEMAND == u1g_EJCC_NOT_USE    /*【可変燃圧制御無】*/
    s2t_qlp = s2g_emqlp_eqlp;
#else                                 /*【可変燃圧制御有】*/
    s2t_prlp = s2g_emprlp_eprlp;
#endif /* JEPRDEMAND */

    /* デフォルト値ラッチ */
    stt_minj_datdft.u1_pri = u1g_EMINJ_PRINORQ;
    stt_minj_datdft.u4_einjrq_dat = u4s_EMINJ_NORQDAT;
    stt_minj_datdft.u2_einjmod = stt_binjctrdat.u2_einjmod;
    stt_minj_datdft2.u1_pri = u1g_EMINJ_PRINORQ;
    stt_minj_datdft2.u4_einjrq_dat = u4s_EMINJ_NORQDAT;
    stt_minj_datdft2.u2_einjmod = stt_binjctrdat.u2_einjmod;
    stt_minj_datdft2.u4_einjptn = u4g_EMINJ_INJPTN_VD;
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    stt_minj_datdft.s2_eainjp1 = stt_binjctrdat.s2_eainjpb1;
    stt_minj_datdft.s2_eainjp2 = s2s_EMINJ_AINJP_VD;
    stt_minj_datdft.s2_eainjp3 = s2s_EMINJ_AINJP_VD;
    stt_minj_datdft.s2_eainjp4 = s2s_EMINJ_AINJP_VD;
    stt_minj_datdft.s2_einjend = stt_binjctrdat.s2_einjendb;
    stt_minj_datdft.s2_eainjcutp = s2t_ainjcutp;
    stt_minj_datdft2.s2_eainjpn[0] = stt_binjctrdat.s2_eainjpb1;
    stt_minj_datdft2.s2_eainjpn[1] = s2s_EMINJ_AINJP_VD;
    stt_minj_datdft2.s2_eainjpn[2] = s2s_EMINJ_AINJP_VD;
    stt_minj_datdft2.s2_eainjpn[3] = s2s_EMINJ_AINJP_VD;
    stt_minj_datdft2.s2_einjend = stt_binjctrdat.s2_einjendb;
    stt_minj_datdft2.s2_eainjcutp = s2t_ainjcutp;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    stt_minj_datdft.s2_eainjd1 = s2t_ainjdb1;
    stt_minj_datdft.s2_eainjd2 = stt_binjctrdat.s2_eainjd2;
    stt_minj_datdft.s2_eainjd3 = stt_binjctrdat.s2_eainjd3;
    stt_minj_datdft.s2_eainjd4 = s2s_EMINJ_AINJD_VD;
    stt_minj_datdft.s2_eainjcutd = s2t_ainjcutd;
    stt_minj_datdft.s2_eprreq = s2t_prhpb;
    stt_minj_datdft2.s2_eainjdn[0] = s2t_ainjdb1;
    stt_minj_datdft2.s2_eainjdn[1] = stt_binjctrdat.s2_eainjd2;
    stt_minj_datdft2.s2_eainjdn[2] = stt_binjctrdat.s2_eainjd3;
    stt_minj_datdft2.s2_eainjdn[3] = s2s_EMINJ_AINJD_VD;
    stt_minj_datdft2.s2_eainjdn[4] = s2s_EMINJ_AINJD_VD;
    stt_minj_datdft2.s2_eainjdn[5] = s2s_EMINJ_AINJD_VD;
    stt_minj_datdft2.s2_eainjcutd = s2t_ainjcutd;
    stt_minj_datdft2.s2_eprreq = s2t_prhpb;
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_PORT      /*【ﾎﾟｰﾄ】*/
    stt_injdat.s2_eainjpadd = s2t_ainjpadd;             /* 優先度調停を行わない変数のためこの位置で代入 */
    stt_injdat2.s2_eainjpadd = s2t_ainjpadd;            /* 優先度調停を行わない変数のためこの位置で代入 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2t_ainjdadd = s2g_einjadd_eainjdadd;
    s2t_ainjadd = s2g_ecatotp_eainjadd;
    ELIB_MINSLCT2( s2t_ainjdadd, s2t_ainjadd, s2t_ainjdaddmin );
    stt_injdat.s2_eainjdadd = s2t_ainjdaddmin;          /* 優先度調停を行わない変数のためこの位置で代入 */
    stt_injdat2.s2_eainjdadd = s2t_ainjdaddmin;         /* 優先度調停を行わない変数のためこの位置で代入 */
#endif /* JEEFI */
    for ( u1t_cyl = (u1)0U; u1t_cyl < u1t_ncyl_c; u1t_cyl++ )
    {
        stt_minj_datdft.s4_eqfc[u1t_cyl] = stg_eminj_einj.s4_eqfc[u1t_cyl];   /* 前回値 */
        stt_minj_datdft2.s4_eqfc[u1t_cyl] = stg_eminj_eminj.s4_eqfc[u1t_cyl]; /* 前回値 */
    }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E                   /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    stt_minj_datdft.s4_eqinjexp = s4s_EMINJ_QINJ_VD;
    stt_minj_datdft2.s4_eqinjexp = s4s_EMINJ_QINJ_VD;
#endif /* JECOMBCCPT_E */
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)8U; u1t_injnum++ )
    {
        stt_minj_datdft2.s4_eqinjflfix[u1t_injnum] = s4s_EMINJ_QINJFLFIX_VD;
        stt_minj_datdft2.s4_eqinjplfix[u1t_injnum] = s4s_EMINJ_QINJPLFIX_VD;
    }
    stt_minj_datdft.s2_ek1f = stt_binjctrdat.s2_ek1f;
    stt_minj_datdft.s2_ek2f = stt_binjctrdat.s2_ek2f;
    stt_minj_datdft.s2_ek3f = stt_binjctrdat.s2_ek3f;
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        stt_minj_datdft.s2_ek1fn[u1t_mox] = stt_binjctrdat.s2_ek1f;
        stt_minj_datdft.s2_ek2fn[u1t_mox] = stt_binjctrdat.s2_ek2f;
        stt_minj_datdft.s2_ek3fn[u1t_mox] = stt_binjctrdat.s2_ek3f;
        stt_minj_datdft2.s2_ek1fn[u1t_mox] = stt_binjctrdat.s2_ek1f;
        stt_minj_datdft2.s2_ek2fn[u1t_mox] = stt_binjctrdat.s2_ek2f;
        stt_minj_datdft2.s2_ek3fn[u1t_mox] = stt_binjctrdat.s2_ek3f;
    }
#if JEPRDEMAND == u1g_EJCC_NOT_USE    /*【可変燃圧制御無】*/
    stt_minj_datdft.s2_eqfreq = s2t_qlp;
    stt_minj_datdft2.s2_eqfreq = s2t_qlp;
#else                                 /*【可変燃圧制御有】*/
    stt_minj_datdft.s2_eprreql = s2t_prlp;
    stt_minj_datdft2.s2_eprreql = s2t_prlp;
#endif /* JEPRDEMAND */
#if JEEGMG_E == u1g_EJCC_HVCLUTCH_E   /*【EG-MGｸﾗｯﾁ】*/
    u1t_xast = u1g_ectrlhv_exast;
#else                                 /*【EG-MGｸﾗｯﾁ以外】*/
    u1t_xast = u1g_exst_exastefi;
#endif /* JEEGMG_E */
    u1s_eminj_exast_lch = u1t_xast;

    u1t_xqinjasto = stg_eminj_einj.bi_exqinjast;

    /* t_xqinjast(始動後噴射量要求ﾌﾗｸﾞ)の算出 */
    if ( ( u1s_eminj_exasto == (u1)ON )                 /* 始動時 */
      && ( u1t_xast == (u1)OFF ) )
    {
        u1t_xqinjast = (u1)OFF;
    }
    else if ( u1t_xqinjasto == (u1)OFF )                /* 機能要求による始動後要求が無い */
    {
        u1t_xqinjast = stt_bstactrdat.u1_exqinjastb;
    }
    else
    {
        u1t_xqinjast = u1t_xqinjasto;
    }
    glbitcp_bibi( u1t_xqinjast, stt_minj_datdft.bi_exqinjast );
    glbitcp_bibi( u1t_xqinjast, stt_minj_datdft2.bi_exqinjast );
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    stt_minj_datdft.u1_explreq = stt_binjctrdat.u1_explreq;
    stt_minj_datdft2.u1_explreq = stt_binjctrdat.u1_explreq;
#endif /* JEEFI */
    if ( u1t_xnercdfew == (u1)ON )                      /* NE同期タスクが少ない */
    {
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
        stt_minj_datdft.s4_eqinjstp1 = stt_bstactrdat.s4_eqinjstapb;
        stt_minj_datdft.s4_eqinjstp2 = s4s_EMINJ_QINJ_VD;
        stt_minj_datdft.s4_eqinjstp3 = s4s_EMINJ_QINJ_VD;
        stt_minj_datdft.s4_eqinjstp4 = s4s_EMINJ_QINJ_VD;
        stt_minj_datdft2.s4_eqinjstpn[0] = stt_bstactrdat.s4_eqinjstapb;
        stt_minj_datdft2.s4_eqinjstpn[1] = s4s_EMINJ_QINJ_VD;
        stt_minj_datdft2.s4_eqinjstpn[2] = s4s_EMINJ_QINJ_VD;
        stt_minj_datdft2.s4_eqinjstpn[3] = s4s_EMINJ_QINJ_VD;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        stt_minj_datdft.s4_eqinjstd1 = stt_bstactrdat.s4_eqinjstad1b;
        stt_minj_datdft.s4_eqinjstd2 = s4s_EMINJ_QINJ_VD;
        stt_minj_datdft.s4_eqinjstd3 = s4s_EMINJ_QINJ_VD;
        stt_minj_datdft.s4_eqinjstd4 = s4s_EMINJ_QINJ_VD;
        stt_minj_datdft2.s4_eqinjstdn[0] = stt_bstactrdat.s4_eqinjstad1b;
        stt_minj_datdft2.s4_eqinjstdn[1] = s4s_EMINJ_QINJ_VD;
        stt_minj_datdft2.s4_eqinjstdn[2] = s4s_EMINJ_QINJ_VD;
        stt_minj_datdft2.s4_eqinjstdn[3] = s4s_EMINJ_QINJ_VD;
        stt_minj_datdft2.s4_eqinjstdn[4] = s4s_EMINJ_QINJ_VD;
        stt_minj_datdft2.s4_eqinjstdn[5] = s4s_EMINJ_QINJ_VD;
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
        if ( ( stt_bstactrdat.u1_exainjstab == (u1)ON )     /* 基本始動時ポート噴射要求有り */
          && ( u1t_xqinjasto == (u1)OFF ) )                 /* 機能要求による始動後要求が無い */
        {
            stt_minj_datdft.s2_eainjp1 = stt_bstactrdat.s2_eainjpstab;
            stt_minj_datdft.s2_einjend = stt_bstactrdat.s2_einjendstab;
            stt_minj_datdft2.s2_eainjpn[0] = stt_bstactrdat.s2_eainjpstab;
            stt_minj_datdft2.s2_einjend = stt_bstactrdat.s2_einjendstab;
        }
#endif /* JEEFI */
        if ( ( stt_bstactrdat.u1_exqinjastb == (u1)OFF )    /* 基本始動後噴射量要求無し */
          && ( u1t_xqinjasto == (u1)OFF ) )                 /* 機能要求による始動後要求が無い */
        {
            stt_minj_datdft.u2_einjmod = stt_bstactrdat.u2_einjmod;
            stt_minj_datdft2.u2_einjmod = stt_bstactrdat.u2_einjmod;
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
            stt_minj_datdft.s2_eainjd1 = stt_bstactrdat.s2_eainjdsta1b;
            stt_minj_datdft.s2_eprreq = stt_bstactrdat.s2_eprreqhstab;
            stt_minj_datdft2.s2_eainjdn[0] = stt_bstactrdat.s2_eainjdsta1b;
            stt_minj_datdft2.s2_eprreq = stt_bstactrdat.s2_eprreqhstab;
#endif /* JEEFI */
        }
    }

    /* 優先度調停 */
    if ( u1t_xnercdfew == (u1)ON )                      /* NE同期タスクが少ない */
    {
        vds_eminj_eminj_hpri( &stt_minj_data, &stt_minj_datdft, &stt_minj_data2, &stt_minj_datdft2 );       /* 調停制約無し時の調停処理 */
    }
    else                                                /* NE同期タスクが多い */
    {
        vds_eminj_eminjlmt_hpri( &stt_minj_data, &stt_minj_datdft, &stt_minj_data2, &stt_minj_datdft2 );    /* 調停制約有り時の調停処理 */
    }
    u4t_rqdat[0] = u4s_eminj_erqdat[0];
    u4t_rqdat[1] = u4s_eminj_erqdat[1];

    u1t_injmedislid = u1g_eminj_einjmedislid;
    if ( u1t_injmedislid == u1g_EMINJ_NONE_ID )
    {
        /* 優先選択要求無し時処理 */
        vds_eminj_einj_datacopy( &stt_minj_data, &stt_minj_datdft );
        vds_eminj_einj_datacopy2( &stt_minj_data2, &stt_minj_datdft2 );

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        if ( ( stt_bstactrdat.u1_exqinjastb == (u1)ON )     /* 基本始動後噴射量要求有り */
          || ( u1t_xqinjasto == (u1)ON ) )                  /* 機能要求による始動後要求有り */
        {
            stt_minj_data.s2_eainjd1 = stt_binjctrdat.s2_eainjd1;
            stt_minj_data.s2_eprreq = stt_binjctrdat.s2_eprreq;
 #if JEPLMLT_E == u1g_EJCC_USE  /*【PLﾏﾙﾁ噴射有】*/ /* temp:仕様確認の内容反映(DENG-STD-25017⑤) start */
            ELIB_LOWGD2( stt_minj_data.s2_eprreq, s2t_binjplctr_prreq, stt_minj_data.s2_eprreq );
 #endif /* JEPLMLT_E */ /* temp:仕様確認の内容反映(DENG-STD-25017⑤) end */
            stt_minj_data2.s2_eainjdn[0] = stt_binjctrdat.s2_eainjd1;
        }
#endif /* JEEFI */
    }
    else
    {
        /* 優先選択要求有り時処理 */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        u2t_injmod = stt_minj_data.u2_einjmod;
        u2t_injmod2 = stt_minj_data2.u2_einjmod;
        u2t_binjmodmsk00F0 = (stt_binjctrdat.u2_einjmod & (u2)0x00F0U);
        u2t_binjmodmsk0F0F = (stt_binjctrdat.u2_einjmod & (u2)0x0F0FU);
#endif /* JEEFI */

        /* 要求噴射方式要求指示無し時処理 */
        if ( (u4t_rqdat[0] & u4g_EMINJ_RQINJMODE) == (u4)0U )           /* 噴射モード要求無し */
        {
            stt_minj_data.u2_einjmod = stt_minj_datdft.u2_einjmod;
        }
        else                                                            /* 噴射モード要求有り */
        {
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
            if ( u2t_injmod == u2g_EMINJ_MOD0N1 )                       /* 要求が基本噴射制御反映要求あり筒内１００％時 */
            {
                if ( ( u2t_binjmodmsk00F0 != (u2)0x0000U )              /* 基本噴射要求が直噴１００％時 */
                  && ( u2t_binjmodmsk0F0F == (u2)0x0001U ) )
                {
                    stt_minj_data.u2_einjmod = stt_binjctrdat.u2_einjmod;
                }

 #if JEEFI == u1g_EJCC_DUAL     /*【ﾃﾞｭｱﾙINJ】*/
                if ( u2t_binjmodmsk0F0F == (u2)0x0101U )                /* 基本噴射要求が直噴１００％でない時 */
                                                                        /* 筒内噴射回数は0以上が条件のため、条件式を省略 */
                {
                    stt_minj_data.u2_einjmod = u2g_AINJIF_MOD011;
                }
 #endif /* JEEFI */
            }
#endif /* JEEFI */
        }

        if ( (u4t_rqdat[1] & u4g_EMINJ_RQINJMODE) == (u4)0U )           /* 噴射モード要求無し */
        {
            stt_minj_data2.u2_einjmod = stt_minj_datdft2.u2_einjmod;
        }
        else                                                            /* 噴射モード要求有り */
        {
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
            if ( u2t_injmod2 == u2g_EMINJ_MOD0N1 )                      /* 要求が基本噴射制御反映要求あり筒内１００％時 */
            {
                if ( ( u2t_binjmodmsk00F0 != (u2)0x0000U )              /* 基本噴射要求が直噴１００％時 */
                  && ( u2t_binjmodmsk0F0F == (u2)0x0001U ) )
                {
                    stt_minj_data2.u2_einjmod = stt_binjctrdat.u2_einjmod;
                }

 #if JEEFI == u1g_EJCC_DUAL     /*【ﾃﾞｭｱﾙINJ】*/
                if ( u2t_binjmodmsk0F0F == (u2)0x0101U )                /* 基本噴射要求が直噴１００％でない時 */
                                                                        /* 筒内噴射回数は0以上が条件のため、条件式を省略 */
                {
                    stt_minj_data2.u2_einjmod = u2g_AINJIF_MOD011;
                }
 #endif /* JEEFI */
            }
#endif /* JEEFI */
        }

        if ( (u4t_rqdat[1] & u4g_EMINJ_RQINJPTN) == (u4)0U )            /* 噴射ﾊﾟﾀｰﾝ要求無し */
        {
            stt_minj_data2.u4_einjptn = stt_minj_datdft2.u4_einjptn;
        }

#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
        if ( (u1s_eminj_estpri2 != u1s_eminj_eprisel_fix)
          && (u1s_eminj_eastpri2 != u1s_eminj_eprisel_fix)
          && (u1s_eminj_epri2 != u1s_eminj_eprisel_fix) )   /* eminjst_tbl、eminjast_tbl、eminj_tbl調停時 */
        {
            if ( ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP1) == (u4)0U )      /* ポート1回目噴射開始時期要求無し */
              && ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP) == (u4)0U ) )     /* ポート噴射開始時期要求無し */
            {
                stt_minj_data.s2_eainjp1 = stt_minj_datdft.s2_eainjp1;
                stt_minj_data2.s2_eainjpn[0] = stt_minj_data.s2_eainjp1;
            }
            if ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP2) == (u4)0U )        /* ポート2回目噴射開始時期要求無し */
            {
                stt_minj_data.s2_eainjp2 = stt_minj_datdft.s2_eainjp2;
                stt_minj_data2.s2_eainjpn[1] = stt_minj_data.s2_eainjp2;
            }
            if ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP3) == (u4)0U )        /* ポート3回目噴射開始時期要求無し */
            {
                stt_minj_data.s2_eainjp3 = stt_minj_datdft.s2_eainjp3;
                stt_minj_data2.s2_eainjpn[2] = stt_minj_data.s2_eainjp3;
            }
            if ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP4) == (u4)0U )        /* ポート4回目噴射開始時期要求無し */
            {
                stt_minj_data.s2_eainjp4 = stt_minj_datdft.s2_eainjp4;
                stt_minj_data2.s2_eainjpn[3] = stt_minj_data.s2_eainjp4;
            }
        }
        else                                                            /* eminjst_tbl2、eminjast_tbl2、eminj_tbl2調停時 */
        {
            if ( (u4t_rqdat[1] & u4g_EMINJ_RQAINJPN) == (u4)0U )        /* ポートn回目噴射開始時期要求無し */
            {
                stt_minj_data2.s2_eainjpn[0] = stt_minj_datdft2.s2_eainjpn[0];
                stt_minj_data.s2_eainjp1 = stt_minj_data2.s2_eainjpn[0];
                stt_minj_data2.s2_eainjpn[1] = stt_minj_datdft2.s2_eainjpn[1];
                stt_minj_data.s2_eainjp2 = stt_minj_data2.s2_eainjpn[1];
                stt_minj_data2.s2_eainjpn[2] = stt_minj_datdft2.s2_eainjpn[2];
                stt_minj_data.s2_eainjp3 = stt_minj_data2.s2_eainjpn[2];
                stt_minj_data2.s2_eainjpn[3] = stt_minj_datdft2.s2_eainjpn[3];
                stt_minj_data.s2_eainjp4 = stt_minj_data2.s2_eainjpn[3];
            }
        }
        if ( (u4t_rqdat[0] & u4g_EMINJ_RQINJEND) == (u4)0U )            /* ポート噴射終了時期要求無し */
        {
            stt_minj_data.s2_einjend = stt_minj_datdft.s2_einjend;
        }
        if ( (u4t_rqdat[1] & u4g_EMINJ_RQINJEND) == (u4)0U )            /* ポート噴射終了時期要求無し */
        {
            stt_minj_data2.s2_einjend = stt_minj_datdft2.s2_einjend;
        }
        if ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJCUTP) == (u4)0U )          /* ポート噴射強制カット時期要求無し */
        {
            stt_minj_data.s2_eainjcutp = stt_minj_datdft.s2_eainjcutp;
        }
        if ( (u4t_rqdat[1] & u4g_EMINJ_RQAINJCUTP) == (u4)0U )          /* ポート噴射強制カット時期要求無し */
        {
            stt_minj_data2.s2_eainjcutp = stt_minj_datdft2.s2_eainjcutp;
        }
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        if ( (u1s_eminj_estpri2 != u1s_eminj_eprisel_fix)
          && (u1s_eminj_eastpri2 != u1s_eminj_eprisel_fix)
          && (u1s_eminj_epri2 != u1s_eminj_eprisel_fix) )   /* eminjst_tbl、eminjast_tbl、eminj_tbl調停時 */
        {
            if ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJD1) == (u4)0U )        /* 筒内1回目噴射開始時期要求無し */
            {
                stt_minj_data.s2_eainjd1 = stt_minj_datdft.s2_eainjd1;
                stt_minj_data2.s2_eainjdn[0] = stt_minj_data.s2_eainjd1;
            }
            else                                                        /* 筒内1回目噴射開始時期要求有り */
            {
                if ( u2t_injmod == u2g_EMINJ_MOD0N1 )                   /* 要求が基本噴射制御反映要求あり筒内１００％時 */
                {
                    if ( ( u2t_binjmodmsk00F0 != (u2)0x0000U )          /* 基本噴射要求が直噴１００%時 */
                      && ( u2t_binjmodmsk0F0F == (u2)0x0001U ) )
                    {
                        stt_minj_data.s2_eainjd1 = stt_binjctrdat.s2_eainjd1;
                        stt_minj_data2.s2_eainjdn[0] = stt_minj_data.s2_eainjd1;
                    }

 #if JEEFI == u1g_EJCC_DUAL     /*【ﾃﾞｭｱﾙINJ】*/
                    if ( u2t_binjmodmsk0F0F == (u2)0x0101U )            /* 基本噴射要求が直噴１００％でない時 */
                                                                        /* 筒内噴射回数は0以上が条件のため、条件式を省略 */
                    {
                        stt_minj_data.s2_eainjd1 = s2t_ainjdb1;
                        stt_minj_data2.s2_eainjdn[0] = stt_minj_data.s2_eainjd1;
                    }
 #endif /* JEEFI */
                }
            }
            if ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJD2) == (u4)0U )        /* 筒内2回目噴射開始時期要求無し */
            {
                stt_minj_data.s2_eainjd2 = stt_minj_datdft.s2_eainjd2;
                stt_minj_data2.s2_eainjdn[1] = stt_minj_data.s2_eainjd2;
            }
            if ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJD3) == (u4)0U )        /* 筒内3回目噴射開始時期要求無し */
            {
                stt_minj_data.s2_eainjd3 = stt_minj_datdft.s2_eainjd3;
                stt_minj_data2.s2_eainjdn[2] = stt_minj_data.s2_eainjd3;
            }
            if ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJD4) == (u4)0U )        /* 筒内4回目噴射開始時期要求無し */
            {
                stt_minj_data.s2_eainjd4 = stt_minj_datdft.s2_eainjd4;
                stt_minj_data2.s2_eainjdn[3] = stt_minj_data.s2_eainjd4;
            }
            stt_minj_data2.s2_eainjdn[4] = s2s_EMINJ_AINJD_VD;
            stt_minj_data2.s2_eainjdn[5] = s2s_EMINJ_AINJD_VD;
        }
        else                                                            /* eminjst_tbl2、eminjast_tbl2、eminj_tbl2調停時 */
        {
            if ( (u4t_rqdat[1] & u4g_EMINJ_RQAINJDN) == (u4)0U )        /* 筒内n回目噴射開始時期要求無し */
            {
                stt_minj_data2.s2_eainjdn[0] = stt_minj_datdft2.s2_eainjdn[0];
                stt_minj_data.s2_eainjd1 = stt_minj_data2.s2_eainjdn[0];
                stt_minj_data2.s2_eainjdn[1] = stt_minj_datdft2.s2_eainjdn[1];
                stt_minj_data.s2_eainjd2 = stt_minj_data2.s2_eainjdn[1];
                stt_minj_data2.s2_eainjdn[2] = stt_minj_datdft2.s2_eainjdn[2];
                stt_minj_data.s2_eainjd3 = stt_minj_data2.s2_eainjdn[2];
                stt_minj_data2.s2_eainjdn[3] = stt_minj_datdft2.s2_eainjdn[3];
                stt_minj_data.s2_eainjd4 = stt_minj_data2.s2_eainjdn[3];
                stt_minj_data2.s2_eainjdn[4] = stt_minj_datdft2.s2_eainjdn[4];
                stt_minj_data2.s2_eainjdn[5] = stt_minj_datdft2.s2_eainjdn[5];
            }
            else                                                        /* 筒内n回目噴射開始時期要求有り */
            {
                if ( u2t_injmod2 == u2g_EMINJ_MOD0N1 )                  /* 要求が基本噴射制御反映要求あり筒内１００％時 */
                {
                    if ( ( u2t_binjmodmsk00F0 != (u2)0x0000U )          /* 基本噴射要求が直噴１００%時 */
                      && ( u2t_binjmodmsk0F0F == (u2)0x0001U ) )
                    {
                        stt_minj_data2.s2_eainjdn[0] = stt_binjctrdat.s2_eainjd1;
                        stt_minj_data.s2_eainjd1 = stt_minj_data2.s2_eainjdn[0];
                    }

 #if JEEFI == u1g_EJCC_DUAL     /*【ﾃﾞｭｱﾙINJ】*/
                    if ( u2t_binjmodmsk0F0F == (u2)0x0101U )            /* 基本噴射要求が直噴１００％でない時 */
                                                                        /* 筒内噴射回数は0以上が条件のため、条件式を省略 */
                    {
                        stt_minj_data2.s2_eainjdn[0] = s2t_ainjdb1;
                        stt_minj_data.s2_eainjd1 = stt_minj_data2.s2_eainjdn[0];
                    }
 #endif /* JEEFI */
                }
            }
        }
        if ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJCUTD) == (u4)0U )          /* 筒内噴射強制カット時期要求無し */
        {
            stt_minj_data.s2_eainjcutd = stt_minj_datdft.s2_eainjcutd;
        }
        if ( (u4t_rqdat[1] & u4g_EMINJ_RQAINJCUTD) == (u4)0U )          /* 筒内噴射強制カット時期要求無し */
        {
            stt_minj_data2.s2_eainjcutd = stt_minj_datdft2.s2_eainjcutd;
        }

#endif /* JEEFI */
        if ( (u4t_rqdat[0] & u4g_EMINJ_RQQFC) == (u4)0U )               /* FC中噴射量要求要求無し */
        {
            for ( u1t_cyl = (u1)0U; u1t_cyl < u1t_ncyl_c; u1t_cyl++ )
            {
                stt_minj_data.s4_eqfc[u1t_cyl] = stt_minj_datdft.s4_eqfc[u1t_cyl];
            }
        }
        if ( (u4t_rqdat[1] & u4g_EMINJ_RQQFC) == (u4)0U )               /* FC中噴射量要求要求無し */
        {
            for ( u1t_cyl = (u1)0U; u1t_cyl < u1t_ncyl_c; u1t_cyl++ )
            {
                stt_minj_data2.s4_eqfc[u1t_cyl] = stt_minj_datdft2.s4_eqfc[u1t_cyl];
            }
        }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E                   /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
        if ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJEXP) == (u4)0U )           /* 膨張行程噴射量要求無し */
        {
            stt_minj_data.s4_eqinjexp = stt_minj_datdft.s4_eqinjexp;
        }
        if ( (u4t_rqdat[1] & u4g_EMINJ_RQQINJEXP) == (u4)0U )           /* 膨張行程噴射量要求無し */
        {
            stt_minj_data2.s4_eqinjexp = stt_minj_datdft2.s4_eqinjexp;
        }
#endif /* JECOMBCCPT_E */
        if ( (u4t_rqdat[0] & u4g_EMINJ_RQK1FN) != (u4)0U )              /* 1回目噴射量算出係数(バンク別)要求有り */
        {
            s4t_k1f = (s4)stt_minj_data.s2_ek1fn[0];
#if JENOX == u1g_EJCC_TWIN      /*【ﾂｲﾝｾﾝｻ】*/
            s4t_k1f += (s4)stt_minj_data.s2_ek1fn[1];
            s4t_k1f = s4g_glbitcal_s4sftr_s4u1( s4t_k1f, (u1)1U );      /* 1/2 */
#endif /* JENOX */
            stt_minj_data.s2_ek1f = (s2)s4t_k1f;
        }
        else if ( (u4t_rqdat[0] & u4g_EMINJ_RQK1F) != (u4)0U )          /* 1回目噴射量算出係数要求有り */
        {
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                stt_minj_data.s2_ek1fn[u1t_mox] = stt_minj_data.s2_ek1f;
                stt_minj_data2.s2_ek1fn[u1t_mox] = stt_minj_data.s2_ek1f;
            }
        }
        else                                                            /* 1回目噴射量算出係数（バンク無/バンク別）要求無し */
        {
            stt_minj_data.s2_ek1f = stt_minj_datdft.s2_ek1f;
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                stt_minj_data.s2_ek1fn[u1t_mox] = stt_minj_datdft.s2_ek1fn[u1t_mox];
            }
        }
        if ( (u4t_rqdat[1] & u4g_EMINJ_RQK1FN) == (u4)0U )              /* 1回目噴射量算出係数(バンク別)要求無し */
        {
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                stt_minj_data2.s2_ek1fn[u1t_mox] = stt_minj_datdft2.s2_ek1fn[u1t_mox];
            }
        }

        if ( (u4t_rqdat[0] & u4g_EMINJ_RQK2FN) != (u4)0U )              /* 2回目噴射量算出係数(バンク別)要求有り */
        {
            s4t_k2f = (s4)stt_minj_data.s2_ek2fn[0];
#if JENOX == u1g_EJCC_TWIN      /*【ﾂｲﾝｾﾝｻ】*/
            s4t_k2f += (s4)stt_minj_data.s2_ek2fn[1];
            s4t_k2f = s4g_glbitcal_s4sftr_s4u1( s4t_k2f, (u1)1U );      /* 1/2 */
#endif /* JENOX */
            stt_minj_data.s2_ek2f = (s2)s4t_k2f;
        }
        else if ( (u4t_rqdat[0] & u4g_EMINJ_RQK2F) != (u4)0U )          /* 2回目噴射量算出係数要求有り */
        {
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                stt_minj_data.s2_ek2fn[u1t_mox] = stt_minj_data.s2_ek2f;
                stt_minj_data2.s2_ek2fn[u1t_mox] = stt_minj_data.s2_ek2f;
            }
        }
        else                                                            /* 2回目噴射量算出係数（バンク無/バンク別）要求無し */
        {
            stt_minj_data.s2_ek2f = stt_minj_datdft.s2_ek2f;
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                stt_minj_data.s2_ek2fn[u1t_mox] = stt_minj_datdft.s2_ek2fn[u1t_mox];
            }
        }
        if ( (u4t_rqdat[1] & u4g_EMINJ_RQK2FN) == (u4)0U )              /* 2回目噴射量算出係数(バンク別)要求無し */
        {
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                stt_minj_data2.s2_ek2fn[u1t_mox] = stt_minj_datdft2.s2_ek2fn[u1t_mox];
            }
        }

        if ( (u4t_rqdat[0] & u4g_EMINJ_RQK3FN) != (u4)0U )              /* 3回目噴射量算出係数(バンク別)要求有り */
        {
            s4t_k3f = (s4)stt_minj_data.s2_ek3fn[0];
#if JENOX == u1g_EJCC_TWIN      /*【ﾂｲﾝｾﾝｻ】*/
            s4t_k3f += (s4)stt_minj_data.s2_ek3fn[1];
            s4t_k3f = s4g_glbitcal_s4sftr_s4u1( s4t_k3f, (u1)1U );      /* 1/2 */
#endif /* JENOX */
            stt_minj_data.s2_ek3f = (s2)s4t_k3f;
        }
        else if ( (u4t_rqdat[0] & u4g_EMINJ_RQK3F) != (u4)0U )          /* 3回目噴射量算出係数要求有り */
        {
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                stt_minj_data.s2_ek3fn[u1t_mox] = stt_minj_data.s2_ek3f;
                stt_minj_data2.s2_ek3fn[u1t_mox] = stt_minj_data.s2_ek3f;
            }
        }
        else                                                            /* 3回目噴射量算出係数（バンク無/バンク別）要求無し */
        {
            stt_minj_data.s2_ek3f = stt_minj_datdft.s2_ek3f;
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                stt_minj_data.s2_ek3fn[u1t_mox] = stt_minj_datdft.s2_ek3fn[u1t_mox];
            }
        }
        if ( (u4t_rqdat[1] & u4g_EMINJ_RQK3FN) == (u4)0U )              /* 3回目噴射量算出係数(バンク別)要求無し */
        {
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                stt_minj_data2.s2_ek3fn[u1t_mox] = stt_minj_datdft2.s2_ek3fn[u1t_mox];
            }
        }

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        if ( (u4t_rqdat[0] & u4g_EMINJ_RQPRREQ) == (u4)0U )             /* 高圧ポンプ目標燃圧要求無し */
        {
            stt_minj_data.s2_eprreq = stt_minj_datdft.s2_eprreq;
        }
        else                                                            /* 高圧ポンプ目標燃圧要求有り */
        {
            if ( ( u2t_injmod == u2g_EMINJ_MOD0N1 )                     /* 要求が基本噴射制御反映要求あり筒内１００％時 */
              && ( ( u2t_binjmodmsk00F0 != (u2)0x0000U )                /* 基本噴射要求が直噴１００%時 */
                && ( u2t_binjmodmsk0F0F == (u2)0x0001U ) ) )
            {
                stt_minj_data.s2_eprreq = stt_binjctrdat.s2_eprreq;
            }
        }
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_NOT_USE    /*【可変燃圧制御無】*/
        if ( (u4t_rqdat[0] & u4g_EMINJ_RQQFREQ) == (u4)0U )             /* 燃料ポンプ吐出流量要求無し */
        {
            stt_minj_data.s2_eqfreq = stt_minj_datdft.s2_eqfreq;
        }
#else                           /*【可変燃圧制御有】*/
        if ( (u4t_rqdat[0] & u4g_EMINJ_RQPRREQL) == (u4)0U )            /* 低圧ポンプ目標燃圧要求無し */
        {
            stt_minj_data.s2_eprreql = stt_minj_datdft.s2_eprreql;
        }
#endif /* JEPRDEMAND */
        if ( (u4t_rqdat[0] & u4g_EMINJ_RQXQINJAST) == (u4)0U )          /* 始動後噴射量要求フラグ要求無し */
                                                                        /* eminj_eminj_hpri()にも同様の処理があるため変更時は合わせて見直すこと */
        {
            glbitcp_bibi( stt_minj_datdft.bi_exqinjast, stt_minj_data.bi_exqinjast );
        }
        if ( (u4t_rqdat[1] & u4g_EMINJ_RQXQINJAST) == (u4)0U )          /* 始動後噴射量要求フラグ要求無し */
                                                                        /* eminj_eminj_hpri()にも同様の処理があるため変更時は合わせて見直すこと */
        {
            glbitcp_bibi( stt_minj_datdft2.bi_exqinjast, stt_minj_data2.bi_exqinjast );
        }

        /* ekrchref[]の処理はeinjmodfix,ekpfix算出後に実施 */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        if ( (u4t_rqdat[0] & u4g_EMINJ_RQPLREQ) == (u4)0U )             /* ＰＬ噴射実施要求無し */
        {
            stt_minj_data.u1_explreq = stt_minj_datdft.u1_explreq;
        }
        if ( (u4t_rqdat[1] & u4g_EMINJ_RQPLREQ) == (u4)0U )             /* ＰＬ噴射実施要求無し */
        {
            stt_minj_data2.u1_explreq = stt_minj_datdft2.u1_explreq;
        }

#endif /* JEEFI */

        if ( (u4t_rqdat[1] & u4g_EMINJ_RQQINJFLFIX) == (u4)0U )         /* ＦＬ固定噴射量要求無し */
        {
            for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)8U; u1t_injnum++ )
            {
                stt_minj_data2.s4_eqinjflfix[u1t_injnum] = stt_minj_datdft2.s4_eqinjflfix[u1t_injnum];
            }
        }

        if ( (u4t_rqdat[1] & u4g_EMINJ_RQQINJPLFIX) == (u4)0U )         /* ＰＬ固定噴射量要求無し */
        {
            for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)8U; u1t_injnum++ )
            {
                stt_minj_data2.s4_eqinjplfix[u1t_injnum] = stt_minj_datdft2.s4_eqinjplfix[u1t_injnum];
            }
        }

        if ( u1t_xnercdfew == (u1)ON )                      /* NE同期タスクが少ない */
        {
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
            s4t_kqstmxp = (s4)s2g_eclrfld_ekqstmxp;
            if ( (u1s_eminj_estpri2 != u1s_eminj_eprisel_fix)
              && (u1s_eminj_eastpri2 != u1s_eminj_eprisel_fix)
              && (u1s_eminj_epri2 != u1s_eminj_eprisel_fix) )   /* eminjst_tbl、eminjast_tbl、eminj_tbl調停時 */
            {
                if ( ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP1) == (u4)0U )    /* ポート1回目始動時噴射量要求無し */
                  && ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP) == (u4)0U ) )   /* ポート始動時噴射量要求無し */
                {
                    stt_minj_data.s4_eqinjstp1 = stt_minj_datdft.s4_eqinjstp1;
                }
                else                                                        /* ポート1回目始動時噴射量要求有り */
                {
                    stt_minj_data.s4_eqinjstp1 = s4g_glmulst_s4s4u2( stt_minj_data.s4_eqinjstp1, s4t_kqstmxp, (u2)8U );
                                    /* lsb= (4096*1024)/128/256/256/256 * 128/128/256 -> (4096*1024)/128/256/256/256 */
                }
                if ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP2) == (u4)0U )      /* ポート2回目始動時噴射量要求無し */
                {
                    stt_minj_data.s4_eqinjstp2 = stt_minj_datdft.s4_eqinjstp2;
                }
                else                                                        /* ポート2回目始動時噴射量要求有り */
                {
                    stt_minj_data.s4_eqinjstp2 = s4g_glmulst_s4s4u2( stt_minj_data.s4_eqinjstp2, s4t_kqstmxp, (u2)8U );
                                    /* lsb= (4096*1024)/128/256/256/256 * 128/128/256 -> (4096*1024)/128/256/256/256 */
                }
                if ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP3) == (u4)0U )      /* ポート3回目始動時噴射量要求無し */
                {
                    stt_minj_data.s4_eqinjstp3 = stt_minj_datdft.s4_eqinjstp3;
                }
                else                                                        /* ポート3回目始動時噴射量要求有り */
                {
                    stt_minj_data.s4_eqinjstp3 = s4g_glmulst_s4s4u2( stt_minj_data.s4_eqinjstp3, s4t_kqstmxp, (u2)8U );
                                    /* lsb= (4096*1024)/128/256/256/256 * 128/128/256 -> (4096*1024)/128/256/256/256 */
                }
                if ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP4) == (u4)0U )      /* ポート4回目始動時噴射量要求無し */
                {
                    stt_minj_data.s4_eqinjstp4 = stt_minj_datdft.s4_eqinjstp4;
                }
                else                                                        /* ポート4回目始動時噴射量要求有り */
                {
                    stt_minj_data.s4_eqinjstp4 = s4g_glmulst_s4s4u2( stt_minj_data.s4_eqinjstp4, s4t_kqstmxp, (u2)8U );
                                    /* lsb= (4096*1024)/128/256/256/256 * 128/128/256 -> (4096*1024)/128/256/256/256 */
                }
                stt_minj_data2.s4_eqinjstpn[0] = stt_minj_data.s4_eqinjstp1;
                stt_minj_data2.s4_eqinjstpn[1] = stt_minj_data.s4_eqinjstp2;
                stt_minj_data2.s4_eqinjstpn[2] = stt_minj_data.s4_eqinjstp3;
                stt_minj_data2.s4_eqinjstpn[3] = stt_minj_data.s4_eqinjstp4;
            }
            else                                                            /* eminjst_tbl2、eminjast_tbl2、eminj_tbl2調停時 */
            {
                if ( (u4t_rqdat[1] & u4g_EMINJ_RQQINJSTPN) == (u4)0U )      /* ポートn回目始動時噴射量要求無し */
                {
                    stt_minj_data2.s4_eqinjstpn[0] = stt_minj_datdft2.s4_eqinjstpn[0];
                    stt_minj_data2.s4_eqinjstpn[1] = stt_minj_datdft2.s4_eqinjstpn[1];
                    stt_minj_data2.s4_eqinjstpn[2] = stt_minj_datdft2.s4_eqinjstpn[2];
                    stt_minj_data2.s4_eqinjstpn[3] = stt_minj_datdft2.s4_eqinjstpn[3];
                }
                else                                                        /* ポートn回目始動時噴射量要求有り */
                {
                    stt_minj_data2.s4_eqinjstpn[0] = s4g_glmulst_s4s4u2( stt_minj_data2.s4_eqinjstpn[0], s4t_kqstmxp, (u2)8U );
                    stt_minj_data2.s4_eqinjstpn[1] = s4g_glmulst_s4s4u2( stt_minj_data2.s4_eqinjstpn[1], s4t_kqstmxp, (u2)8U );
                    stt_minj_data2.s4_eqinjstpn[2] = s4g_glmulst_s4s4u2( stt_minj_data2.s4_eqinjstpn[2], s4t_kqstmxp, (u2)8U );
                    stt_minj_data2.s4_eqinjstpn[3] = s4g_glmulst_s4s4u2( stt_minj_data2.s4_eqinjstpn[3], s4t_kqstmxp, (u2)8U );
                                    /* lsb= (4096*1024)/128/256/256/256 * 128/128/256 -> (4096*1024)/128/256/256/256 */
                }
                stt_minj_data.s4_eqinjstp1 = stt_minj_data2.s4_eqinjstpn[0];
                stt_minj_data.s4_eqinjstp2 = stt_minj_data2.s4_eqinjstpn[1];
                stt_minj_data.s4_eqinjstp3 = stt_minj_data2.s4_eqinjstpn[2];
                stt_minj_data.s4_eqinjstp4 = stt_minj_data2.s4_eqinjstpn[3];
            }
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
            s4t_kqstmxd = (s4)s2g_eclrfld_ekqstmxd;
            if ( (u1s_eminj_estpri2 != u1s_eminj_eprisel_fix)
              && (u1s_eminj_eastpri2 != u1s_eminj_eprisel_fix)
              && (u1s_eminj_epri2 != u1s_eminj_eprisel_fix) )   /* eminjst_tbl、eminjast_tbl、eminj_tbl調停時 */
            {
                if ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTD1) == (u4)0U )      /* 筒内1回目始動時噴射量要求無し */
                {
                    stt_minj_data.s4_eqinjstd1 = stt_minj_datdft.s4_eqinjstd1;
                }
                else                                                        /* 筒内1回目始動時噴射量要求有り */
                {
                    stt_minj_data.s4_eqinjstd1 = s4g_glmulst_s4s4u2( stt_minj_data.s4_eqinjstd1, s4t_kqstmxd, (u2)8U );
                                    /* lsb= (4096*1024)/128/256/256/256 * 128/128/256 -> (4096*1024)/128/256/256/256 */
                }
                if ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTD2) == (u4)0U )      /* 筒内2回目始動時噴射量要求無し */
                {
                    stt_minj_data.s4_eqinjstd2 = stt_minj_datdft.s4_eqinjstd2;
                }
                else                                                        /* 筒内2回目始動時噴射量要求有り */
                {
                    stt_minj_data.s4_eqinjstd2 = s4g_glmulst_s4s4u2( stt_minj_data.s4_eqinjstd2, s4t_kqstmxd, (u2)8U );
                                    /* lsb= (4096*1024)/128/256/256/256 * 128/128/256 -> (4096*1024)/128/256/256/256 */
                }
                if ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTD3) == (u4)0U )      /* 筒内3回目始動時噴射量要求無し */
                {
                    stt_minj_data.s4_eqinjstd3 = stt_minj_datdft.s4_eqinjstd3;
                }
                else                                                        /* 筒内3回目始動時噴射量要求有り */
                {
                    stt_minj_data.s4_eqinjstd3 = s4g_glmulst_s4s4u2( stt_minj_data.s4_eqinjstd3, s4t_kqstmxd, (u2)8U );
                                    /* lsb= (4096*1024)/128/256/256/256 * 128/128/256 -> (4096*1024)/128/256/256/256 */
                }
                if ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTD4) == (u4)0U )      /* 筒内4回目始動時噴射量要求無し */
                {
                    stt_minj_data.s4_eqinjstd4 = stt_minj_datdft.s4_eqinjstd4;
                }
                else                                                        /* 筒内4回目始動時噴射量要求有り */
                {
                    stt_minj_data.s4_eqinjstd4 = s4g_glmulst_s4s4u2( stt_minj_data.s4_eqinjstd4, s4t_kqstmxd, (u2)8U );
                                    /* lsb= (4096*1024)/128/256/256/256 * 128/128/256 -> (4096*1024)/128/256/256/256 */
                }
                stt_minj_data2.s4_eqinjstdn[0] = stt_minj_data.s4_eqinjstd1;
                stt_minj_data2.s4_eqinjstdn[1] = stt_minj_data.s4_eqinjstd2;
                stt_minj_data2.s4_eqinjstdn[2] = stt_minj_data.s4_eqinjstd3;
                stt_minj_data2.s4_eqinjstdn[3] = stt_minj_data.s4_eqinjstd4;
                stt_minj_data2.s4_eqinjstdn[4] = s4s_EMINJ_QINJ_VD;
                stt_minj_data2.s4_eqinjstdn[5] = s4s_EMINJ_QINJ_VD;
            }
            else                                                            /* eminjst_tbl2、eminjast_tbl2、eminj_tbl2調停時 */
            {
                if ( (u4t_rqdat[1] & u4g_EMINJ_RQQINJSTDN) == (u4)0U )      /* 筒内n回目始動時噴射量要求無し */
                {
                    stt_minj_data2.s4_eqinjstdn[0] = stt_minj_datdft2.s4_eqinjstdn[0];
                    stt_minj_data2.s4_eqinjstdn[1] = stt_minj_datdft2.s4_eqinjstdn[1];
                    stt_minj_data2.s4_eqinjstdn[2] = stt_minj_datdft2.s4_eqinjstdn[2];
                    stt_minj_data2.s4_eqinjstdn[3] = stt_minj_datdft2.s4_eqinjstdn[3];
                    stt_minj_data2.s4_eqinjstdn[4] = stt_minj_datdft2.s4_eqinjstdn[4];
                    stt_minj_data2.s4_eqinjstdn[5] = stt_minj_datdft2.s4_eqinjstdn[5];
                }
                else                                                        /* 筒内n回目始動時噴射量要求有り */
                {
                    stt_minj_data2.s4_eqinjstdn[0] = s4g_glmulst_s4s4u2( stt_minj_data2.s4_eqinjstdn[0], s4t_kqstmxd, (u2)8U );
                    stt_minj_data2.s4_eqinjstdn[1] = s4g_glmulst_s4s4u2( stt_minj_data2.s4_eqinjstdn[1], s4t_kqstmxd, (u2)8U );
                    stt_minj_data2.s4_eqinjstdn[2] = s4g_glmulst_s4s4u2( stt_minj_data2.s4_eqinjstdn[2], s4t_kqstmxd, (u2)8U );
                    stt_minj_data2.s4_eqinjstdn[3] = s4g_glmulst_s4s4u2( stt_minj_data2.s4_eqinjstdn[3], s4t_kqstmxd, (u2)8U );
                    stt_minj_data2.s4_eqinjstdn[4] = s4g_glmulst_s4s4u2( stt_minj_data2.s4_eqinjstdn[4], s4t_kqstmxd, (u2)8U );
                    stt_minj_data2.s4_eqinjstdn[5] = s4g_glmulst_s4s4u2( stt_minj_data2.s4_eqinjstdn[5], s4t_kqstmxd, (u2)8U );
                                    /* lsb= (4096*1024)/128/256/256/256 * 128/128/256 -> (4096*1024)/128/256/256/256 */
                }
                stt_minj_data.s4_eqinjstd1 = stt_minj_data2.s4_eqinjstdn[0];
                stt_minj_data.s4_eqinjstd2 = stt_minj_data2.s4_eqinjstdn[1];
                stt_minj_data.s4_eqinjstd3 = stt_minj_data2.s4_eqinjstdn[2];
                stt_minj_data.s4_eqinjstd4 = stt_minj_data2.s4_eqinjstdn[3];
            }
#endif /* JEEFI */
        }
    }

    /* ekpfi（ポート噴射量算出係数）、ekpfin[NOX]（ポート噴射量算出係数(バンク別)）の算出 */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    u2t_injmodmsk0F00 = (stt_minj_data.u2_einjmod & (u2)0x0F00U);
    u2t_injmodmsk00F0 = (stt_minj_data.u2_einjmod & (u2)0x00F0U);
    u2t_injmodmsk000F = (stt_minj_data.u2_einjmod & (u2)0x000FU);
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
    if ( u2t_injmodmsk000F == (u2)0x0000U )                  /* 噴射停止中 */
    {
        s2t_kpfi_wk = (s2)(((0.)/((1.*4.)/128./256.))+0.5);
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            s2t_kpfin[u1t_mox] = (s2)(((0.)/((1.*4.)/128./256.))+0.5);
        }
    }
    else if ( u2t_injmodmsk00F0 == (u2)0x0000U )             /* ポート噴射時 */
    {
        s2t_kpfi_wk = (s2)(((1.)/((1.*4.)/128./256.))+0.5);
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            s2t_kpfin[u1t_mox] = (s2)(((1.)/((1.*4.)/128./256.))+0.5);
        }
    }
    else if ( u2t_injmodmsk0F00 == (u2)0x0000U )             /* 筒内噴射時 */
    {
        s2t_kpfi_wk = (s2)(((0.)/((1.*4.)/128./256.))+0.5);
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            s2t_kpfin[u1t_mox] = (s2)(((0.)/((1.*4.)/128./256.))+0.5);
        }
    }
    else if ( u2t_injmodmsk0F00 == (u2)0x0100U )             /* デュアル噴射 */
    {
        if ( stt_minj_data.bi_exqinjast == (u1)ON )          /* 始動後 */
        {
            s2t_kpfi_wk = stt_minj_data.s2_ek1fn[0];
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                s2t_kpfin[u1t_mox] = stt_minj_data.s2_ek1fn[u1t_mox];
            }
        }
        else
        {
            s4t_qinjadd = s4g_gladdst_s4s4( stt_minj_data.s4_eqinjstp1, stt_minj_data.s4_eqinjstp2 );
            s4t_qinjadd = s4g_gladdst_s4s4( s4t_qinjadd, stt_minj_data.s4_eqinjstp3 );
            s4t_qinjadd = s4g_gladdst_s4s4( s4t_qinjadd, stt_minj_data.s4_eqinjstp4 );
            s4t_qinjadd2 = s4g_gladdst_s4s4( s4t_qinjadd, stt_minj_data.s4_eqinjstd1 );
            s4t_qinjadd2 = s4g_gladdst_s4s4( s4t_qinjadd2, stt_minj_data.s4_eqinjstd2 );
            s4t_qinjadd2 = s4g_gladdst_s4s4( s4t_qinjadd2, stt_minj_data.s4_eqinjstd3 );
            s4t_qinjadd2 = s4g_gladdst_s4s4( s4t_qinjadd2, stt_minj_data.s4_eqinjstd4 );

            s4t_qinjdiv = s4g_gldiv_s4s4( (s4)(((1.)/(2./128./256./256./256.))+0.5), s4t_qinjadd2 );
                                /* lsb= 2/128/256/256/256 / (4096*1024)/128/256/256/256 -> (16*64)/128/256/256/256 */
                                /* s4t_qinjaddの左13bitシフトを避けるため、除算項の逆数を求めて乗算処理にする */
            s4t_kpfi = s4g_glmulst_s4s4u2( s4t_qinjadd, s4t_qinjdiv, (u2)17U );
                                /* lsb= (4096*1024)/128/256/256/256 * (16*64)/128/256/256/256 -> (1*4)/128/256 */

            ELIB_HILOGD2( s4t_kpfi, (s4)s2g_S2MAX, (s4)s2g_S2MIN, s4t_kpfi );
            s2t_kpfi_wk = (s2)s4t_kpfi;
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                s2t_kpfin[u1t_mox] = (s2)s4t_kpfi;
            }
        }
    }
    else
    {
        s2t_kpfi_wk = (s2)(((1.)/((1.*4.)/128./256.))+0.5);
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            s2t_kpfin[u1t_mox] = (s2)(((1.)/((1.*4.)/128./256.))+0.5);
        }
    }
#elif JEEFI == u1g_EJCC_PORT    /*【ﾎﾟｰﾄ】*/
    s2t_kpfi_wk = (s2)(((1.)/((1.*4.)/128./256.))+0.5);
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        s2t_kpfin[u1t_mox] = (s2)(((1.)/((1.*4.)/128./256.))+0.5);
    }
#else                           /* (【ﾃﾞｭｱﾙINJ】OR【ﾎﾟｰﾄ】)以外 */
    s2t_kpfi_wk = (s2)(((0.)/((1.*4.)/128./256.))+0.5);
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        s2t_kpfin[u1t_mox] = (s2)(((0.)/((1.*4.)/128./256.))+0.5);
    }
#endif /* JEEFI */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    /* 筒内噴射開始時期の制限 */
    stt_injdat.s2_eainjd1 = stt_minj_data.s2_eainjd1;
    ELIB_HILOGD2( stt_injdat.s2_eainjd1, s2s_EMINJ_AINJD_MX, s2s_EMINJ_AINJD_MN, stt_injdat.s2_eainjd1 );
    stt_injdat.f4_eainjd1 = (f4)stt_injdat.s2_eainjd1 * (f4)(1024./128./256.);
    stt_injdat.s2_eainjd2 = stt_minj_data.s2_eainjd2;
    ELIB_HILOGD2( stt_injdat.s2_eainjd2, s2s_EMINJ_AINJD_MX, s2s_EMINJ_AINJD_MN, stt_injdat.s2_eainjd2 );
    stt_injdat.f4_eainjd2 = (f4)stt_injdat.s2_eainjd2 * (f4)(1024./128./256.);
    stt_injdat.s2_eainjd3 = stt_minj_data.s2_eainjd3;
    ELIB_HILOGD2( stt_injdat.s2_eainjd3, s2s_EMINJ_AINJD_MX, s2s_EMINJ_AINJD_MN, stt_injdat.s2_eainjd3 );
    stt_injdat.f4_eainjd3 = (f4)stt_injdat.s2_eainjd3 * (f4)(1024./128./256.);
    stt_injdat.s2_eainjd4 = stt_minj_data.s2_eainjd4;
    ELIB_HILOGD2( stt_injdat.s2_eainjd4, s2s_EMINJ_AINJD_MX, s2s_EMINJ_AINJD_MN, stt_injdat.s2_eainjd4 );
    stt_injdat.f4_eainjd4 = (f4)stt_injdat.s2_eainjd4 * (f4)(1024./128./256.);
    stt_injdat2.s2_eainjdn[0] = stt_minj_data2.s2_eainjdn[0];
    ELIB_HILOGD2( stt_injdat2.s2_eainjdn[0], s2s_EMINJ_AINJD_MX, s2s_EMINJ_AINJD_MN, stt_injdat2.s2_eainjdn[0] );
    stt_injdat2.f4_eainjdn[0] = (f4)stt_injdat2.s2_eainjdn[0] * (f4)(1024./128./256.);
    stt_injdat2.s2_eainjdn[1] = stt_minj_data2.s2_eainjdn[1];
    ELIB_HILOGD2( stt_injdat2.s2_eainjdn[1], s2s_EMINJ_AINJD_MX, s2s_EMINJ_AINJD_MN, stt_injdat2.s2_eainjdn[1] );
    stt_injdat2.f4_eainjdn[1] = (f4)stt_injdat2.s2_eainjdn[1] * (f4)(1024./128./256.);
    stt_injdat2.s2_eainjdn[2] = stt_minj_data2.s2_eainjdn[2];
    ELIB_HILOGD2( stt_injdat2.s2_eainjdn[2], s2s_EMINJ_AINJD_MX, s2s_EMINJ_AINJD_MN, stt_injdat2.s2_eainjdn[2] );
    stt_injdat2.f4_eainjdn[2] = (f4)stt_injdat2.s2_eainjdn[2] * (f4)(1024./128./256.);
    stt_injdat2.s2_eainjdn[3] = stt_minj_data2.s2_eainjdn[3];
    ELIB_HILOGD2( stt_injdat2.s2_eainjdn[3], s2s_EMINJ_AINJD_MX, s2s_EMINJ_AINJD_MN, stt_injdat2.s2_eainjdn[3] );
    stt_injdat2.f4_eainjdn[3] = (f4)stt_injdat2.s2_eainjdn[3] * (f4)(1024./128./256.);
    stt_injdat2.s2_eainjdn[4] = stt_minj_data2.s2_eainjdn[4];
    ELIB_HILOGD2( stt_injdat2.s2_eainjdn[4], s2s_EMINJ_AINJD_MX, s2s_EMINJ_AINJD_MN, stt_injdat2.s2_eainjdn[4] );
    stt_injdat2.f4_eainjdn[4] = (f4)stt_injdat2.s2_eainjdn[4] * (f4)(1024./128./256.);
    stt_injdat2.s2_eainjdn[5] = stt_minj_data2.s2_eainjdn[5];
    ELIB_HILOGD2( stt_injdat2.s2_eainjdn[5], s2s_EMINJ_AINJD_MX, s2s_EMINJ_AINJD_MN, stt_injdat2.s2_eainjdn[5] );
    stt_injdat2.f4_eainjdn[5] = (f4)stt_injdat2.s2_eainjdn[5] * (f4)(1024./128./256.);
#endif /* JEEFI */

    /* einjmodfix（現在確定噴射モード）、ekpfix（ポート噴射量算出係数）の算出 */
    u2g_eminj_einjmodfix = stt_minj_data.u2_einjmod;
    s2g_eminj_ekpfix = s2t_kpfi_wk;
    f4g_eminj_ekpfix = (f4)s2t_kpfi_wk * (f4)((1.*4.)/128./256.);

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    /* eainjd1fix（確定筒内1回目噴射開始時期）、eainjd2fix（確定筒内2回目噴射開始時期）、     */
    /* eainjd3fix（確定筒内3回目噴射開始時期）、eainjd4fix（確定筒内4回目噴射開始時期）、     */
    /* eainjd5fix（確定筒内5回目噴射開始時期）、eainjd6fix（確定筒内6回目噴射開始時期）の算出 */
    if ( ( u1s_eminj_estpri2 == u1s_eminj_eprisel_fix )
      || ( u1s_eminj_eastpri2 == u1s_eminj_eprisel_fix )
      || ( u1s_eminj_epri2 == u1s_eminj_eprisel_fix ) )     /* eminjst_tbl2、eminjast_tbl2、eminj_tbl2調停時 */
    {
        f4g_eminj_eainjd1fix = stt_injdat2.f4_eainjdn[0];
        f4g_eminj_eainjd2fix = stt_injdat2.f4_eainjdn[1];
        f4g_eminj_eainjd3fix = stt_injdat2.f4_eainjdn[2];
        f4g_eminj_eainjd4fix = stt_injdat2.f4_eainjdn[3];
        f4g_eminj_eainjd5fix = stt_injdat2.f4_eainjdn[4];
        f4g_eminj_eainjd6fix = stt_injdat2.f4_eainjdn[5];
    }
    else                                                    /* eminjst_tbl、eminjast_tbl、eminj_tbl調停時 */
    {
        f4g_eminj_eainjd1fix = stt_injdat.f4_eainjd1;
        f4g_eminj_eainjd2fix = stt_injdat.f4_eainjd2;
        f4g_eminj_eainjd3fix = stt_injdat.f4_eainjd3;
        f4g_eminj_eainjd4fix = stt_injdat.f4_eainjd4;
        f4g_eminj_eainjd5fix = (f4)s2s_EMINJ_AINJD_VD * (f4)(1024./128./256.);
        f4g_eminj_eainjd6fix = (f4)s2s_EMINJ_AINJD_VD * (f4)(1024./128./256.);
    }
#endif /* JEEFI */

    /* ek1ffix（確定1回目噴射量算出係数）、ek2ffix（確定2回目噴射量算出係数）、 */
    /* ek3ffix（確定3回目噴射量算出係数）の算出                                 */
    /* ガード含む最終値と同等の中間値を使うことが可能なため、実装簡素化のために中間値参照する */
    f4g_eminj_ek1ffix = (f4)stt_minj_data.s2_ek1f * (f4)((1.*4.)/128./256.);
    f4g_eminj_ek2ffix = (f4)stt_minj_data.s2_ek2f * (f4)((1.*4.)/128./256.);
    f4g_eminj_ek3ffix = (f4)stt_minj_data.s2_ek3f * (f4)((1.*4.)/128./256.);

    /* ekrchref[NOX]（噴射量補正係数）の算出 */
    /* ekrchref[]の処理はeinjmodfix、ekpfix、eainjd1fix、eainjd2fix、eainjd3fix、eainjd4fix、ek1ffix、ek2ffix、ek3ffix算出実施後に行うこと */
    vdg_emkrichb_ekrichxb_get();                                      /* コール先でeinjmodfix,ekpfix、eainjd1fix、eainjd2fix、eainjd3fix、eainjd4fix、ek1ffix、ek2ffix、ek3ffixを参照、emkrichb_ekrichxbcrt[]を更新 */
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        s2t_krichxbcrt[u1t_mox] = s2g_emkrichb_ekrichxbcrt[u1t_mox];  /* emkrichb_ekrichxb_get()コール後に参照すること */
        stt_minj_datdft.s2_ekrchref[u1t_mox] = s2t_krichxbcrt[u1t_mox];
        stt_minj_datdft2.s2_ekrchref[u1t_mox] = s2t_krichxbcrt[u1t_mox];
    }

    if ( ( u1t_injmedislid == u1g_EMINJ_NONE_ID )               /* 優先選択要求無し時 */
      || ( ( u1t_injmedislid != u1g_EMINJ_NONE_ID )             /* 優先選択要求あり時 */
        && ( (u4t_rqdat[0] & u4g_EMINJ_RQKRCHREF) == (u4)0U ) ) )  /* 噴射量補正係数要求無し */
    {
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            stt_minj_data.s2_ekrchref[u1t_mox] = stt_minj_datdft.s2_ekrchref[u1t_mox];
        }
    }

    if ( ( u1t_injmedislid == u1g_EMINJ_NONE_ID )               /* 優先選択要求無し時 */
      || ( ( u1t_injmedislid != u1g_EMINJ_NONE_ID )             /* 優先選択要求あり時 */
        && ( (u4t_rqdat[1] & u4g_EMINJ_RQKRCHREF) == (u4)0U ) ) )  /* 噴射量補正係数要求無し */
    {
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            stt_minj_data2.s2_ekrchref[u1t_mox] = stt_minj_datdft2.s2_ekrchref[u1t_mox];
        }
    }

    /* ekrichx（噴射量補正係数）の算出 */
    s2t_krichx = s2t_krichxbcrt[0];
#if JENOX == u1g_EJCC_TWIN      /*【ﾂｲﾝｾﾝｻ】*/
    ELIB_MAXSLCT2( s2t_krichx, s2t_krichxbcrt[1], s2t_krichx );
#endif /* JENOX */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    if ( ( u1t_injmedislid == u1g_EMINJ_SJC_ID )        /* 触媒急速暖機制御噴射選択時 */
      || ( u1t_injmedislid == u1g_EMINJ_STRATIST_ID ) ) /* 成層始動制御時噴射選択時 */
    {
        s2t_krichx = stt_minj_data.s2_ekrchref[0];
                    /* ekrchref[0]は、einjmedislid＝SJC_ID時にesjc_efsjc、 */
                    /* STRATIST_ID時にestratist_efstrtが格納されているため仕様と一致する */
    }
#endif /* JEEFI */

    if ( u1t_xnercdfew == (u1)ON )                      /* NE同期タスクが少ない */
    {
        /* ポート噴射量算出係数(ekpfi)に応じた始動時噴射量のクリア */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
        if ( s2t_kpfi_wk == (s2)(((0.)/((1.*4.)/128./256.))+0.5) )    /* 筒内噴射時 */
        {
            stt_minj_data.s4_eqinjstp1 = s4s_EMINJ_QINJI;
            stt_minj_data.s4_eqinjstp2 = s4s_EMINJ_QINJI;
            stt_minj_data.s4_eqinjstp3 = s4s_EMINJ_QINJI;
            stt_minj_data.s4_eqinjstp4 = s4s_EMINJ_QINJI;
            stt_minj_data2.s4_eqinjstpn[0] = s4s_EMINJ_QINJI;
            stt_minj_data2.s4_eqinjstpn[1] = s4s_EMINJ_QINJI;
            stt_minj_data2.s4_eqinjstpn[2] = s4s_EMINJ_QINJI;
            stt_minj_data2.s4_eqinjstpn[3] = s4s_EMINJ_QINJI;
        }
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        if ( s2t_kpfi_wk == (s2)(((1.)/((1.*4.)/128./256.))+0.5) )    /* ポート噴射時 */
        {
            stt_minj_data.s4_eqinjstd1 = s4s_EMINJ_QINJI;
            stt_minj_data.s4_eqinjstd2 = s4s_EMINJ_QINJI;
            stt_minj_data.s4_eqinjstd3 = s4s_EMINJ_QINJI;
            stt_minj_data.s4_eqinjstd4 = s4s_EMINJ_QINJI;
            stt_minj_data2.s4_eqinjstdn[0] = s4s_EMINJ_QINJI;
            stt_minj_data2.s4_eqinjstdn[1] = s4s_EMINJ_QINJI;
            stt_minj_data2.s4_eqinjstdn[2] = s4s_EMINJ_QINJI;
            stt_minj_data2.s4_eqinjstdn[3] = s4s_EMINJ_QINJI;
            stt_minj_data2.s4_eqinjstdn[4] = s4s_EMINJ_QINJI;
            stt_minj_data2.s4_eqinjstdn[5] = s4s_EMINJ_QINJI;
        }
#endif /* JEEFI */
    }

#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
 #if (((JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_MEDI == ON)) \
   || ((JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_WC_MEDI == ON)) \
   || ((JEEGMG_E == u1g_EJCC_HVPLGR_E) && (JEFFV == u1g_EJCC_NOT_USE) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_STAHV_MEDI == ON)))
   /* (【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】) */
   /* OR (【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】) */
   /* OR (【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】) */
    f4t_kpfit = f4g_ebinjplctr_ekpfit;
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        f4t_kpfitn[u1t_mox] = f4g_ebinjplctr_ekpfitn[u1t_mox];
    }
 #endif /* JEPLMLT_E,EMINJ_BINJPLCTR_MEDI,JEALLHV_E,EMINJ_BINJPLCTR_WC_MEDI,JEEGMG_E,JEFFV,EMINJ_BINJPLCTR_STAHV_MEDI */

    /* ekpfit（目標ポート噴射量算出係数）、ekpfitn[NOX]（目標ポート噴射量算出係数(バンク別)）の算出 */
    if ( u1t_injmedislid == u1g_EMINJ_STRATIST_ID )      /* 成層始動制御選択時 */
    {
        s2t_kpfit_estratist = s2g_estratist_ekpfit;
        s2t_kpfit = s2t_kpfit_estratist;
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            s2t_kpfitn[u1t_mox] = s2t_kpfit_estratist;
        }
    }
    else if ( u1t_injmedislid == u1s_EMINJ_PRVDIL_ID )   /* 冷間時希釈防止制御選択時 */
    {
        s2t_kpfit_eprvdil = s2g_eprvdil_ekpfit;
        s2t_kpfit = s2t_kpfit_eprvdil;
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            s2t_kpfitn[u1t_mox] = s2t_kpfit_eprvdil;
        }
    }
 #if (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_MEDI == ON)   /*【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】*/
    else if ( u1t_injmedislid == u1g_EMINJ_BINJPLCTR_ID )  /* パーシャルリフト噴射を用いた基本噴射制御選択時 */
    {
        ELIB_FLP2FXP_S2( f4t_kpfit, (f4)((1.*4.)/128./256.), s2t_kpfitplctr );
        s2t_kpfit = s2t_kpfitplctr;
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            ELIB_FLP2FXP_S2( f4t_kpfitn[u1t_mox], (f4)((1.*4.)/128./256.), s2t_kpfitnplctr[u1t_mox] );
            s2t_kpfitn[u1t_mox] = s2t_kpfitnplctr[u1t_mox];
        }
    }
 #endif /* JEPLMLT_E,EMINJ_BINJPLCTR_MEDI */
 #if JEALLHV_E == u1g_EJCC_ALLHV_E      /*【ALL HV】*/
    else if ( u1t_injmedislid == u1g_EMINJ_WUPCAT_ID )   /* 触媒暖機制御選択時 */
    {
        ELIB_FLP2FXP_S2( f4g_ewupcat_ekpfitcat, (f4)((1.*4.)/128./256.), s2t_kpfitcat );
        s2t_kpfit = s2t_kpfitcat;
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            s2t_kpfitn[u1t_mox] = s2t_kpfitcat;
        }
    }
    else if ( u1t_injmedislid == u1g_EMINJ_RDPN_ID )     /* 始動後ＰＮ低減制御選択時 */
    {
        ELIB_FLP2FXP_S2( f4g_erdpn_ekpfit, (f4)((1.*4.)/128./256.), s2t_kpfit_erdpn );
        s2t_kpfit = s2t_kpfit_erdpn;
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            ELIB_FLP2FXP_S2( f4g_erdpn_ekpfitn[u1t_mox], (f4)((1.*4.)/128./256.), s2t_kpfitn[u1t_mox]);
        }
    }
 #endif /* JEALLHV_E */
 #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_WC_MEDI == ON)  /*【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】*/
    else if ( u1t_injmedislid == u1g_EMINJ_BINJPLCTR_WC_ID )    /* パーシャルリフト噴射を用いた基本噴射制御(触媒暖機時)選択時 */
    {
        ELIB_FLP2FXP_S2( f4t_kpfit, (f4)((1.*4.)/128./256.), s2t_kpfitplctr );
        s2t_kpfit = s2t_kpfitplctr;
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            ELIB_FLP2FXP_S2( f4t_kpfitn[u1t_mox], (f4)((1.*4.)/128./256.), s2t_kpfitnplctr[u1t_mox] );
            s2t_kpfitn[u1t_mox] = s2t_kpfitnplctr[u1t_mox];
        }
    }
 #endif /* JEALLHV_E,JEPLMLT_E,EMINJ_BINJPLCTR_WC_MEDI */
 #if (JEEGMG_E == u1g_EJCC_HVPLGR_E) && (JEFFV == u1g_EJCC_NOT_USE) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_STAHV_MEDI == ON)    /*【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】*/
    else if ( u1t_injmedislid == u1g_EMINJ_BINJPLCTR_STAHV_ID ) /* パーシャルリフト噴射を用いた基本噴射制御(HV始動制御時)選択時 */
    {
        ELIB_FLP2FXP_S2( f4t_kpfit, (f4)((1.*4.)/128./256.), s2t_kpfitplctr );
        s2t_kpfit = s2t_kpfitplctr;
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            ELIB_FLP2FXP_S2( f4t_kpfitn[u1t_mox], (f4)((1.*4.)/128./256.), s2t_kpfitnplctr[u1t_mox] );
            s2t_kpfitn[u1t_mox] = s2t_kpfitnplctr[u1t_mox];
        }
    }
 #endif /* JEEGMG_E,JEFFV,JEPLMLT_E,EMINJ_BINJPLCTR_STAHV_MEDI */
 #if JEFFV != u1g_EJCC_NOT_USE  /*【FFV制御有】*/
    else if ( u1t_injmedislid == u1s_EMINJ_ACTAREFUEL_ID )  /* 給油後の噴き分けアクティブ制御選択時 */
    {
        s2t_kpfit_eactarefuel = s2g_eactarefuel_ekpfit;
        s2t_kpfit = s2t_kpfit_eactarefuel;
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            s2t_kpfitn[u1t_mox] = s2t_kpfit_eactarefuel;
        }
    }
 #endif /* JEFFV */
    else
    {
        if ( u1t_injmedislid == u1g_EMINJ_NONE_ID )
        {
            s2t_kpfit = stt_binjctrdat.s2_ekpfit;
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                s2t_kpfitn[u1t_mox] = stt_binjctrdat.s2_ekpfit;
            }
        }
        else
        {
            s2t_kpfit = s2t_kpfi_wk;
            for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
            {
                s2t_kpfitn[u1t_mox] = s2t_kpfin[u1t_mox];
            }
        }
    }
#endif /* JEEFI */

#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    /* ek1fpt（ポート噴射のみ要求時の目標ポート1回目噴射量算出係数）の算出 */
 #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT)  /*【ALL HV】AND【ﾎﾟｰﾄ】*/
    if ( u1t_injmedislid == u1g_EMINJ_WUPCAT_ID )       /* 触媒暖機制御選択時 */
    {
        stt_injdat.f4_ek1fpt = f4t_k1fptcat;
        stt_injdat2.f4_ek1fpt = f4t_k1fptcat;
    }
    else if ( u1t_injmedislid == u1g_EMINJ_RDPN_ID )    /* ＰＮ低減制御選択時 */
    {
        stt_injdat.f4_ek1fpt = f4t_k1fpt;
        stt_injdat2.f4_ek1fpt = f4t_k1fpt;
    }
    else
 #endif /* JEALLHV_E,JEEFI */
    {
        if ( ( u2t_injmodmsk0F00 == (u2)0x0100U )        /* ポート１回噴射含む噴き分け時 */
          && ( u2t_injmodmsk000F != (u2)0x0000U ) )      /* 筒内噴射回数は0以上が条件のため、条件式を省略 */
        {
            stt_injdat.f4_ek1fpt = (f4)(1.);
            stt_injdat2.f4_ek1fpt = (f4)(1.);
        }
        else if ( ( u2t_injmodmsk0F00 == (u2)0x0000U )   /* 噴射要求が直噴１００％時 */
               && ( u2t_injmodmsk00F0 != (u2)0x0000U )
               && ( u2t_injmodmsk000F != (u2)0x0000U ) )
        {
            stt_injdat.f4_ek1fpt = (f4)s2s_EMINJ_K1F_VD * (f4)((1.*4.)/128./256.);
            stt_injdat2.f4_ek1fpt = (f4)s2s_EMINJ_K1F_VD * (f4)((1.*4.)/128./256.);
        }
        else
        {
            stt_injdat.f4_ek1fpt = stg_eminj_einj.f4_ek1fpt; /* 前回値 */
            stt_injdat2.f4_ek1fpt = stg_eminj_eminj.f4_ek1fpt; /* 前回値 */
        }
    }
    ELIB_FLP2FXP_S2( stt_injdat.f4_ek1fpt, (f4)((1.*4.)/128./256.), stt_injdat.s2_ek1fpt );
    ELIB_FLP2FXP_S2( stt_injdat2.f4_ek1fpt, (f4)((1.*4.)/128./256.), stt_injdat2.s2_ek1fpt );
#endif /* JEEFI */

#if (JEEFI == u1g_EJCC_DUAL) && (JEEGR == u1g_EJCC_USE)      /*【ﾃﾞｭｱﾙINJ】AND【EGR制御有】*/
    /* ekpfiegr（EGR-ON時の目標ポート噴射量算出係数）、ekpfiegrn[NOX]（EGR-ON時の目標ポート噴射量算出係数(バンク別)）の算出 */
    if ( u1t_injmedislid == u1g_EMINJ_NONE_ID )
    {
        stt_injdat.f4_ekpfiegr = (f4)stt_binjctrdat.s2_ekpfiegr * (f4)((1.*4.)/128./256.);
        stt_injdat2.f4_ekpfiegr = (f4)stt_binjctrdat.s2_ekpfiegr * (f4)((1.*4.)/128./256.);
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            stt_injdat.f4_ekpfiegrn[u1t_mox] = (f4)stt_binjctrdat.s2_ekpfiegr * (f4)((1.*4.)/128./256.);
            stt_injdat2.f4_ekpfiegrn[u1t_mox] = (f4)stt_binjctrdat.s2_ekpfiegr * (f4)((1.*4.)/128./256.);
        }
    }
    else
    {
        stt_injdat.f4_ekpfiegr = (f4)s2t_kpfi_wk * (f4)((1.*4.)/128./256.);
        stt_injdat2.f4_ekpfiegr = (f4)s2t_kpfi_wk * (f4)((1.*4.)/128./256.);
        for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
        {
            stt_injdat.f4_ekpfiegrn[u1t_mox] = (f4)s2t_kpfin[u1t_mox] * (f4)((1.*4.)/128./256.);
            stt_injdat2.f4_ekpfiegrn[u1t_mox] = (f4)s2t_kpfin[u1t_mox] * (f4)((1.*4.)/128./256.);
        }
    }
#endif /* JEEFI,JEEGR */

    /* 格納 */
    stt_injdat.u2_einjmod = stt_minj_data.u2_einjmod;
    stt_injdat2.u2_einjmod = stt_minj_data2.u2_einjmod;
    stt_injdat2.u4_einjptn = stt_minj_data2.u4_einjptn;
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    stt_injdat.s2_eainjp1 = stt_minj_data.s2_eainjp1;
    ELIB_HILOGD2( stt_injdat.s2_eainjp1, s2s_EMINJ_AINJP_MX, s2s_EMINJ_AINJP_MN, stt_injdat.s2_eainjp1 );
    stt_injdat.f4_eainjp1 = (f4)stt_injdat.s2_eainjp1 * (f4)(1024./128./256.);
    stt_injdat.s2_eainjp2 = stt_minj_data.s2_eainjp2;
    ELIB_HILOGD2( stt_injdat.s2_eainjp2, s2s_EMINJ_AINJP_MX, s2s_EMINJ_AINJP_MN, stt_injdat.s2_eainjp2 );
    stt_injdat.f4_eainjp2 = (f4)stt_injdat.s2_eainjp2 * (f4)(1024./128./256.);
    stt_injdat.s2_eainjp3 = stt_minj_data.s2_eainjp3;
    ELIB_HILOGD2( stt_injdat.s2_eainjp3, s2s_EMINJ_AINJP_MX, s2s_EMINJ_AINJP_MN, stt_injdat.s2_eainjp3 );
    stt_injdat.f4_eainjp3 = (f4)stt_injdat.s2_eainjp3 * (f4)(1024./128./256.);
    stt_injdat.s2_eainjp4 = stt_minj_data.s2_eainjp4;
    ELIB_HILOGD2( stt_injdat.s2_eainjp4, s2s_EMINJ_AINJP_MX, s2s_EMINJ_AINJP_MN, stt_injdat.s2_eainjp4 );
    stt_injdat.f4_eainjp4 = (f4)stt_injdat.s2_eainjp4 * (f4)(1024./128./256.);
    stt_injdat.s2_einjend = stt_minj_data.s2_einjend;
    stt_injdat.f4_einjend = (f4)stt_injdat.s2_einjend * (f4)(1024./128./256.);
    stt_injdat.s2_eainjcutp = stt_minj_data.s2_eainjcutp;
    stt_injdat.f4_eainjcutp = (f4)stt_injdat.s2_eainjcutp * (f4)(1024./128./256.);
    stt_injdat2.s2_eainjpn[0] = stt_minj_data2.s2_eainjpn[0];
    ELIB_HILOGD2( stt_injdat2.s2_eainjpn[0], s2s_EMINJ_AINJP_MX, s2s_EMINJ_AINJP_MN, stt_injdat2.s2_eainjpn[0] );
    stt_injdat2.f4_eainjpn[0] = (f4)stt_injdat2.s2_eainjpn[0] * (f4)(1024./128./256.);
    stt_injdat2.s2_eainjpn[1] = stt_minj_data2.s2_eainjpn[1];
    ELIB_HILOGD2( stt_injdat2.s2_eainjpn[1], s2s_EMINJ_AINJP_MX, s2s_EMINJ_AINJP_MN, stt_injdat2.s2_eainjpn[1] );
    stt_injdat2.f4_eainjpn[1] = (f4)stt_injdat2.s2_eainjpn[1] * (f4)(1024./128./256.);
    stt_injdat2.s2_eainjpn[2] = stt_minj_data2.s2_eainjpn[2];
    ELIB_HILOGD2( stt_injdat2.s2_eainjpn[2], s2s_EMINJ_AINJP_MX, s2s_EMINJ_AINJP_MN, stt_injdat2.s2_eainjpn[2] );
    stt_injdat2.f4_eainjpn[2] = (f4)stt_injdat2.s2_eainjpn[2] * (f4)(1024./128./256.);
    stt_injdat2.s2_eainjpn[3] = stt_minj_data2.s2_eainjpn[3];
    ELIB_HILOGD2( stt_injdat2.s2_eainjpn[3], s2s_EMINJ_AINJP_MX, s2s_EMINJ_AINJP_MN, stt_injdat2.s2_eainjpn[3] );
    stt_injdat2.f4_eainjpn[3] = (f4)stt_injdat2.s2_eainjpn[3] * (f4)(1024./128./256.);
    stt_injdat2.s2_einjend = stt_minj_data2.s2_einjend;
    stt_injdat2.f4_einjend = (f4)stt_injdat2.s2_einjend * (f4)(1024./128./256.);
    stt_injdat2.s2_eainjcutp = stt_minj_data2.s2_eainjcutp;
    stt_injdat2.f4_eainjcutp = (f4)stt_injdat2.s2_eainjcutp * (f4)(1024./128./256.);
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    stt_injdat.s2_eainjcutd = stt_minj_data.s2_eainjcutd;
    stt_injdat.f4_eainjcutd = (f4)stt_injdat.s2_eainjcutd * (f4)(1024./128./256.);
    stt_injdat2.s2_eainjcutd = stt_minj_data2.s2_eainjcutd;
    stt_injdat2.f4_eainjcutd = (f4)stt_injdat2.s2_eainjcutd * (f4)(1024./128./256.);
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_PORT      /*【ﾎﾟｰﾄ】*/
    /* stt_injdat.s2_eainjpaddの代入はデフォルト値ラッチ処理にて実施済み */
    ELIB_HILOGD2( stt_injdat.s2_eainjpadd, s2s_EMINJ_AINJPADD_MX, s2s_EMINJ_AINJPADD_MN, stt_injdat.s2_eainjpadd );
    ELIB_HILOGD2( stt_injdat2.s2_eainjpadd, s2s_EMINJ_AINJPADD_MX, s2s_EMINJ_AINJPADD_MN, stt_injdat2.s2_eainjpadd );
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    /* stt_injdat.s2_eainjdaddの代入はデフォルト値ラッチ処理にて実施済み */
    ELIB_HILOGD2( stt_injdat.s2_eainjdadd, s2s_EMINJ_AINJDADD_MX, s2s_EMINJ_AINJDADD_MN, stt_injdat.s2_eainjdadd );
    ELIB_HILOGD2( stt_injdat2.s2_eainjdadd, s2s_EMINJ_AINJDADD_MX, s2s_EMINJ_AINJDADD_MN, stt_injdat2.s2_eainjdadd );
#endif /* JEEFI */
    stt_injdat.s2_ek1f = stt_minj_data.s2_ek1f;
    ELIB_HILOGD2( stt_injdat.s2_ek1f, s2s_EMINJ_K1F_MX, s2s_EMINJ_K1F_MN, stt_injdat.s2_ek1f );
    stt_injdat.f4_ek1f = (f4)stt_injdat.s2_ek1f * (f4)((1.*4.)/128./256.);
    stt_injdat.s2_ek2f = stt_minj_data.s2_ek2f;
    ELIB_HILOGD2( stt_injdat.s2_ek2f, s2s_EMINJ_K2F_MX, s2s_EMINJ_K2F_MN, stt_injdat.s2_ek2f );
    stt_injdat.f4_ek2f = (f4)stt_injdat.s2_ek2f * (f4)((1.*4.)/128./256.);
    stt_injdat.s2_ek3f = stt_minj_data.s2_ek3f;
    ELIB_HILOGD2( stt_injdat.s2_ek3f, s2s_EMINJ_K3F_MX, s2s_EMINJ_K3F_MN, stt_injdat.s2_ek3f );
    stt_injdat.f4_ek3f = (f4)stt_injdat.s2_ek3f * (f4)((1.*4.)/128./256.);
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        stt_injdat.s2_ek1fn[u1t_mox] = stt_minj_data.s2_ek1fn[u1t_mox];
        ELIB_HILOGD2( stt_injdat.s2_ek1fn[u1t_mox], s2s_EMINJ_K1FN_MX, s2s_EMINJ_K1FN_MN, stt_injdat.s2_ek1fn[u1t_mox] );
        stt_injdat.f4_ek1fn[u1t_mox] = (f4)stt_injdat.s2_ek1fn[u1t_mox] * (f4)((1.*4.)/128./256.);
        stt_injdat.s2_ek2fn[u1t_mox] = stt_minj_data.s2_ek2fn[u1t_mox];
        ELIB_HILOGD2( stt_injdat.s2_ek2fn[u1t_mox], s2s_EMINJ_K2FN_MX, s2s_EMINJ_K2FN_MN, stt_injdat.s2_ek2fn[u1t_mox] );
        stt_injdat.f4_ek2fn[u1t_mox] = (f4)stt_injdat.s2_ek2fn[u1t_mox] * (f4)((1.*4.)/128./256.);
        stt_injdat.s2_ek3fn[u1t_mox] = stt_minj_data.s2_ek3fn[u1t_mox];
        ELIB_HILOGD2( stt_injdat.s2_ek3fn[u1t_mox], s2s_EMINJ_K3FN_MX, s2s_EMINJ_K3FN_MN, stt_injdat.s2_ek3fn[u1t_mox] );
        stt_injdat.f4_ek3fn[u1t_mox] = (f4)stt_injdat.s2_ek3fn[u1t_mox] * (f4)((1.*4.)/128./256.);
        stt_injdat.s2_ekrchref[u1t_mox] = stt_minj_data.s2_ekrchref[u1t_mox];
        ELIB_HILOGD2( stt_injdat.s2_ekrchref[u1t_mox], s2s_EMINJ_KRCHREF_MX, s2s_EMINJ_KRCHREF_MN, stt_injdat.s2_ekrchref[u1t_mox] );
        stt_injdat.f4_ekrchref[u1t_mox] = (f4)stt_injdat.s2_ekrchref[u1t_mox] * (f4)((32.*2.)/128./256.);
    }
    glbitcp_bibi( stt_minj_data.bi_exqinjast, stt_injdat.bi_exqinjast );
    stt_injdat.u1_exqinjast = (u1)stt_injdat.bi_exqinjast;
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        stt_injdat2.s2_ek1fn[u1t_mox] = stt_minj_data2.s2_ek1fn[u1t_mox];
        ELIB_HILOGD2( stt_injdat2.s2_ek1fn[u1t_mox], s2s_EMINJ_K1FN_MX, s2s_EMINJ_K1FN_MN, stt_injdat2.s2_ek1fn[u1t_mox] );
        stt_injdat2.f4_ek1fn[u1t_mox] = (f4)stt_injdat2.s2_ek1fn[u1t_mox] * (f4)((1.*4.)/128./256.);
        stt_injdat2.s2_ek2fn[u1t_mox] = stt_minj_data2.s2_ek2fn[u1t_mox];
        ELIB_HILOGD2( stt_injdat2.s2_ek2fn[u1t_mox], s2s_EMINJ_K2FN_MX, s2s_EMINJ_K2FN_MN, stt_injdat2.s2_ek2fn[u1t_mox] );
        stt_injdat2.f4_ek2fn[u1t_mox] = (f4)stt_injdat2.s2_ek2fn[u1t_mox] * (f4)((1.*4.)/128./256.);
        stt_injdat2.s2_ek3fn[u1t_mox] = stt_minj_data2.s2_ek3fn[u1t_mox];
        ELIB_HILOGD2( stt_injdat2.s2_ek3fn[u1t_mox], s2s_EMINJ_K3FN_MX, s2s_EMINJ_K3FN_MN, stt_injdat2.s2_ek3fn[u1t_mox] );
        stt_injdat2.f4_ek3fn[u1t_mox] = (f4)stt_injdat2.s2_ek3fn[u1t_mox] * (f4)((1.*4.)/128./256.);
        stt_injdat2.s2_ekrchref[u1t_mox] = stt_minj_data2.s2_ekrchref[u1t_mox];
        ELIB_HILOGD2( stt_injdat2.s2_ekrchref[u1t_mox], s2s_EMINJ_KRCHREF_MX, s2s_EMINJ_KRCHREF_MN, stt_injdat2.s2_ekrchref[u1t_mox] );
        stt_injdat2.f4_ekrchref[u1t_mox] = (f4)stt_injdat2.s2_ekrchref[u1t_mox] * (f4)((32.*2.)/128./256.);
    }
    glbitcp_bibi( stt_minj_data2.bi_exqinjast, stt_injdat2.bi_exqinjast );
    stt_injdat2.u1_exqinjast = (u1)stt_injdat2.bi_exqinjast;
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    stt_injdat.u1_explreq = stt_minj_data.u1_explreq;
    stt_injdat2.u1_explreq = stt_minj_data2.u1_explreq;
#endif /* JEEFI */
    for ( u1t_cyl = (u1)0U; u1t_cyl < u1t_ncyl_c; u1t_cyl++ )
    {
        ELIB_HILOGD2( stt_minj_data.s4_eqfc[u1t_cyl], s4s_EMINJ_QINJ_MX, s4s_EMINJ_QINJ_MN, stt_injdat.s4_eqfc[u1t_cyl] );
        stt_injdat.f4_eqfc[u1t_cyl] = (f4)stt_injdat.s4_eqfc[u1t_cyl] * (f4)((4096.*1024.)/128./256./256./256.);
        ELIB_HILOGD2( stt_minj_data2.s4_eqfc[u1t_cyl], s4s_EMINJ_QINJ_MX, s4s_EMINJ_QINJ_MN, stt_injdat2.s4_eqfc[u1t_cyl] );
        stt_injdat2.f4_eqfc[u1t_cyl] = (f4)stt_injdat2.s4_eqfc[u1t_cyl] * (f4)((4096.*1024.)/128./256./256./256.);
    }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E                   /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    stt_injdat.s4_eqinjexp = stt_minj_data.s4_eqinjexp;
    ELIB_HILOGD2( stt_injdat.s4_eqinjexp, s4s_EMINJ_QINJ_MX, s4s_EMINJ_QINJ_MN, stt_injdat.s4_eqinjexp );
    stt_injdat.f4_eqinjexp = (f4)stt_injdat.s4_eqinjexp * (f4)((4096.*1024.)/128./256./256./256.);
    stt_injdat2.s4_eqinjexp = stt_minj_data2.s4_eqinjexp;
    ELIB_HILOGD2( stt_injdat2.s4_eqinjexp, s4s_EMINJ_QINJ_MX, s4s_EMINJ_QINJ_MN, stt_injdat2.s4_eqinjexp );
    stt_injdat2.f4_eqinjexp = (f4)stt_injdat2.s4_eqinjexp * (f4)((4096.*1024.)/128./256./256./256.);
#endif /* JECOMBCCPT_E */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
    stt_injdat.s2_ekpfit = s2t_kpfit;
    stt_injdat.f4_ekpfit = (f4)s2t_kpfit * (f4)((1.*4.)/128./256.);
    stt_injdat2.s2_ekpfit = s2t_kpfit;
    stt_injdat2.f4_ekpfit = (f4)s2t_kpfit * (f4)((1.*4.)/128./256.);
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        stt_injdat.s2_ekpfitn[u1t_mox] = s2t_kpfitn[u1t_mox];
        stt_injdat.f4_ekpfitn[u1t_mox] = (f4)s2t_kpfitn[u1t_mox] * (f4)((1.*4.)/128./256.);
        stt_injdat2.s2_ekpfitn[u1t_mox] = s2t_kpfitn[u1t_mox];
        stt_injdat2.f4_ekpfitn[u1t_mox] = (f4)s2t_kpfitn[u1t_mox] * (f4)((1.*4.)/128./256.);
    }
#endif /* JEEFI */
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)8U; u1t_injnum++ )
    {
        stt_injdat2.s4_eqinjflfix[u1t_injnum] = stt_minj_data2.s4_eqinjflfix[u1t_injnum];
        ELIB_HILOGD2( stt_injdat2.s4_eqinjflfix[u1t_injnum], s4s_EMINJ_QINJ_MX, s4s_EMINJ_QINJ_MN, stt_injdat2.s4_eqinjflfix[u1t_injnum] );
        stt_injdat2.f4_eqinjflfix[u1t_injnum] = (f4)stt_injdat2.s4_eqinjflfix[u1t_injnum] * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat2.s4_eqinjplfix[u1t_injnum] = stt_minj_data2.s4_eqinjplfix[u1t_injnum];
        ELIB_HILOGD2( stt_injdat2.s4_eqinjplfix[u1t_injnum], s4s_EMINJ_QINJ_MX, s4s_EMINJ_QINJ_MN, stt_injdat2.s4_eqinjplfix[u1t_injnum] );
        stt_injdat2.f4_eqinjplfix[u1t_injnum] = (f4)stt_injdat2.s4_eqinjplfix[u1t_injnum] * (f4)((4096.*1024.)/128./256./256./256.);
    }
    if ( u1t_xnercdfew == (u1)ON )                      /* NE同期タスクが少ない */
    {
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
        stt_injdat.s4_eqinjstp1 = stt_minj_data.s4_eqinjstp1;
        ELIB_HILOGD2( stt_injdat.s4_eqinjstp1, s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat.s4_eqinjstp1 );
        stt_injdat.f4_eqinjstp1 = (f4)stt_injdat.s4_eqinjstp1 * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat.s4_eqinjstp2 = stt_minj_data.s4_eqinjstp2;
        ELIB_HILOGD2( stt_injdat.s4_eqinjstp2, s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat.s4_eqinjstp2 );
        stt_injdat.f4_eqinjstp2 = (f4)stt_injdat.s4_eqinjstp2 * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat.s4_eqinjstp3 = stt_minj_data.s4_eqinjstp3;
        ELIB_HILOGD2( stt_injdat.s4_eqinjstp3, s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat.s4_eqinjstp3 );
        stt_injdat.f4_eqinjstp3 = (f4)stt_injdat.s4_eqinjstp3 * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat.s4_eqinjstp4 = stt_minj_data.s4_eqinjstp4;
        ELIB_HILOGD2( stt_injdat.s4_eqinjstp4, s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat.s4_eqinjstp4 );
        stt_injdat.f4_eqinjstp4 = (f4)stt_injdat.s4_eqinjstp4 * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat2.s4_eqinjstpn[0] = stt_minj_data2.s4_eqinjstpn[0];
        ELIB_HILOGD2( stt_injdat2.s4_eqinjstpn[0], s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat2.s4_eqinjstpn[0] );
        stt_injdat2.f4_eqinjstpn[0] = (f4)stt_injdat2.s4_eqinjstpn[0] * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat2.s4_eqinjstpn[1] = stt_minj_data2.s4_eqinjstpn[1];
        ELIB_HILOGD2( stt_injdat2.s4_eqinjstpn[1], s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat2.s4_eqinjstpn[1] );
        stt_injdat2.f4_eqinjstpn[1] = (f4)stt_injdat2.s4_eqinjstpn[1] * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat2.s4_eqinjstpn[2] = stt_minj_data2.s4_eqinjstpn[2];
        ELIB_HILOGD2( stt_injdat2.s4_eqinjstpn[2], s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat2.s4_eqinjstpn[2] );
        stt_injdat2.f4_eqinjstpn[2] = (f4)stt_injdat2.s4_eqinjstpn[2] * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat2.s4_eqinjstpn[3] = stt_minj_data2.s4_eqinjstpn[3];
        ELIB_HILOGD2( stt_injdat2.s4_eqinjstpn[3], s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat2.s4_eqinjstpn[3] );
        stt_injdat2.f4_eqinjstpn[3] = (f4)stt_injdat2.s4_eqinjstpn[3] * (f4)((4096.*1024.)/128./256./256./256.);
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        stt_injdat.s4_eqinjstd1 = stt_minj_data.s4_eqinjstd1;
        ELIB_HILOGD2( stt_injdat.s4_eqinjstd1, s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat.s4_eqinjstd1 );
        stt_injdat.f4_eqinjstd1 = (f4)stt_injdat.s4_eqinjstd1 * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat.s4_eqinjstd2 = stt_minj_data.s4_eqinjstd2;
        ELIB_HILOGD2( stt_injdat.s4_eqinjstd2, s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat.s4_eqinjstd2 );
        stt_injdat.f4_eqinjstd2 = (f4)stt_injdat.s4_eqinjstd2 * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat.s4_eqinjstd3 = stt_minj_data.s4_eqinjstd3;
        ELIB_HILOGD2( stt_injdat.s4_eqinjstd3, s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat.s4_eqinjstd3 );
        stt_injdat.f4_eqinjstd3 = (f4)stt_injdat.s4_eqinjstd3 * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat.s4_eqinjstd4 = stt_minj_data.s4_eqinjstd4;
        ELIB_HILOGD2( stt_injdat.s4_eqinjstd4, s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat.s4_eqinjstd4 );
        stt_injdat.f4_eqinjstd4 = (f4)stt_injdat.s4_eqinjstd4 * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat2.s4_eqinjstdn[0] = stt_minj_data2.s4_eqinjstdn[0];
        ELIB_HILOGD2( stt_injdat2.s4_eqinjstdn[0], s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat2.s4_eqinjstdn[0] );
        stt_injdat2.f4_eqinjstdn[0] = (f4)stt_injdat2.s4_eqinjstdn[0] * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat2.s4_eqinjstdn[1] = stt_minj_data2.s4_eqinjstdn[1];
        ELIB_HILOGD2( stt_injdat2.s4_eqinjstdn[1], s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat2.s4_eqinjstdn[1] );
        stt_injdat2.f4_eqinjstdn[1] = (f4)stt_injdat2.s4_eqinjstdn[1] * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat2.s4_eqinjstdn[2] = stt_minj_data2.s4_eqinjstdn[2];
        ELIB_HILOGD2( stt_injdat2.s4_eqinjstdn[2], s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat2.s4_eqinjstdn[2] );
        stt_injdat2.f4_eqinjstdn[2] = (f4)stt_injdat2.s4_eqinjstdn[2] * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat2.s4_eqinjstdn[3] = stt_minj_data2.s4_eqinjstdn[3];
        ELIB_HILOGD2( stt_injdat2.s4_eqinjstdn[3], s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat2.s4_eqinjstdn[3] );
        stt_injdat2.f4_eqinjstdn[3] = (f4)stt_injdat2.s4_eqinjstdn[3] * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat2.s4_eqinjstdn[4] = stt_minj_data2.s4_eqinjstdn[4];
        ELIB_HILOGD2( stt_injdat2.s4_eqinjstdn[4], s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat2.s4_eqinjstdn[4] );
        stt_injdat2.f4_eqinjstdn[4] = (f4)stt_injdat2.s4_eqinjstdn[4] * (f4)((4096.*1024.)/128./256./256./256.);
        stt_injdat2.s4_eqinjstdn[5] = stt_minj_data2.s4_eqinjstdn[5];
        ELIB_HILOGD2( stt_injdat2.s4_eqinjstdn[5], s4s_EMINJ_QINJST_MX, s4s_EMINJ_QINJST_MN, stt_injdat2.s4_eqinjstdn[5] );
        stt_injdat2.f4_eqinjstdn[5] = (f4)stt_injdat2.s4_eqinjstdn[5] * (f4)((4096.*1024.)/128./256./256./256.);
#endif /* JEEFI */
    }

    vds_eminj_einj_dataset( &stg_eminj_einj, &stt_injdat, u1t_xnercdfew );
    vds_eminj_eminj_dataset( &stg_eminj_eminj, &stt_injdat2, u1t_xnercdfew );

#ifdef M_EMINJ       /* デバッグモード */
    u2s_eminj_einjmod_mon = stt_injdat.u2_einjmod;
    u2s_eminj_eminj_einjmod_mon = stt_injdat2.u2_einjmod;
    u4s_eminj_eminj_einjptn_mon = stt_injdat2.u4_einjptn;
 #if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    s2s_eminj_eainjp1_mon = stt_injdat.s2_eainjp1;
    f4s_eminj_eainjp1_mon = stt_injdat.f4_eainjp1;
    s2s_eminj_eainjp2_mon = stt_injdat.s2_eainjp2;
    f4s_eminj_eainjp2_mon = stt_injdat.f4_eainjp2;
    s2s_eminj_eainjp3_mon = stt_injdat.s2_eainjp3;
    f4s_eminj_eainjp3_mon = stt_injdat.f4_eainjp3;
    s2s_eminj_eainjp4_mon = stt_injdat.s2_eainjp4;
    f4s_eminj_eainjp4_mon = stt_injdat.f4_eainjp4;
    s2s_eminj_einjend_mon = stt_injdat.s2_einjend;
    s2s_eminj_eminj_einjend_mon = stt_injdat2.s2_einjend;
    s2s_eminj_eainjcutp_mon = stt_injdat.s2_eainjcutp;
    f4s_eminj_eainjcutp_mon = stt_injdat.f4_eainjcutp;
    s2s_eminj_eminj_eainjcutp_mon = stt_injdat2.s2_eainjcutp;
    f4s_eminj_eminj_eainjcutp_mon = stt_injdat2.f4_eainjcutp;
 #endif /* JEEFI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2s_eminj_eainjd1_mon = stt_injdat.s2_eainjd1;
    f4s_eminj_eainjd1_mon = stt_injdat.f4_eainjd1;
    s2s_eminj_eainjd2_mon = stt_injdat.s2_eainjd2;
    f4s_eminj_eainjd2_mon = stt_injdat.f4_eainjd2;
    s2s_eminj_eainjd3_mon = stt_injdat.s2_eainjd3;
    f4s_eminj_eainjd3_mon = stt_injdat.f4_eainjd3;
    s2s_eminj_eainjd4_mon = stt_injdat.s2_eainjd4;
    f4s_eminj_eainjd4_mon = stt_injdat.f4_eainjd4;
    s2s_eminj_eainjcutd_mon = stt_injdat.s2_eainjcutd;
    f4s_eminj_eainjcutd_mon = stt_injdat.f4_eainjcutd;
    s2s_eminj_eminj_eainjcutd_mon = stt_injdat2.s2_eainjcutd;
    f4s_eminj_eminj_eainjcutd_mon = stt_injdat2.f4_eainjcutd;
 #endif /* JEEFI */
 #if JEEFI == u1g_EJCC_PORT      /*【ﾎﾟｰﾄ】*/
    s2s_eminj_eainjpadd_mon = stt_injdat.s2_eainjpadd;
    s2s_eminj_eminj_eainjpadd_mon = stt_injdat2.s2_eainjpadd;
 #endif /* JEEFI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2s_eminj_eainjdadd_mon = stt_injdat.s2_eainjdadd;
    s2s_eminj_eminj_eainjdadd_mon = stt_injdat2.s2_eainjdadd;
 #endif /* JEEFI */
 #if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E                   /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    s4s_eminj_eqinjexp_mon = stt_injdat.s4_eqinjexp;
    f4s_eminj_eqinjexp_mon = stt_injdat.f4_eqinjexp;
    s4s_eminj_eminj_eqinjexp_mon = stt_injdat2.s4_eqinjexp;
    f4s_eminj_eminj_eqinjexp_mon = stt_injdat2.f4_eqinjexp;
 #endif /* JECOMBCCPT_E */
    s2s_eminj_ek1f_mon = stt_injdat.s2_ek1f;
    f4s_eminj_ek1f_mon = stt_injdat.f4_ek1f;
    s2s_eminj_ek2f_mon = stt_injdat.s2_ek2f;
    f4s_eminj_ek2f_mon = stt_injdat.f4_ek2f;
    s2s_eminj_ek3f_mon = stt_injdat.s2_ek3f;
    f4s_eminj_ek3f_mon = stt_injdat.f4_ek3f;
    u1s_eminj_exqinjast_mon = (u1)(stt_injdat.bi_exqinjast);
    u1s_eminj_eminj_exqinjast_mon = (u1)(stt_injdat2.bi_exqinjast);
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    u1s_eminj_explreq_mon = stt_injdat.u1_explreq;
    u1s_eminj_eminj_explreq_mon = stt_injdat2.u1_explreq;
 #endif /* JEEFI */
 #if JEEFI == u1g_EJCC_DUAL            /*【ﾃﾞｭｱﾙINJ】*/
    f4s_eminj_ekpfit_mon = stt_injdat.f4_ekpfit;
    f4s_eminj_eminj_ekpfit_mon = stt_injdat2.f4_ekpfit;
  #if JEEGR == u1g_EJCC_USE      /*【EGR制御有】*/
    f4s_eminj_ekpfiegr_mon = stt_injdat.f4_ekpfiegr;
    f4s_eminj_eminj_ekpfiegr_mon = stt_injdat2.f4_ekpfiegr;
  #endif /* JEEGR */
 #endif /* JEEFI */
 #if JEEFI != u1g_EJCC_D4              /*【D-4以外】*/
    s2s_eminj_ek1fpt_mon = stt_injdat.s2_ek1fpt;
    f4s_eminj_ek1fpt_mon = stt_injdat.f4_ek1fpt;
    s2s_eminj_eminj_ek1fpt_mon = stt_injdat2.s2_ek1fpt;
    f4s_eminj_eminj_ek1fpt_mon = stt_injdat2.f4_ek1fpt;
 #endif /* JEEFI */
    /* f4s_eminj_einjend_monは、f4g_eminj_einjendで代用可能 */
    /* s2s_eminj_ekpfit_monは、s2g_eminj_ekpfitで代用可能 */
    /* stt_injdat.u1_exqinjastのモニタ変数は、u1s_eminj_exqinjast_monで代用可能 */
    /* s4s_eminj_eqfc_mon[u1g_EJCC_NCYL]は、s4g_eminj_eqfc[u1g_EJCC_NCYL]で代用可能 */
    /* f4s_eminj_eqfc_mon[u1g_EJCC_NCYL]は、f4g_eminj_eqfc[u1g_EJCC_NCYL]で代用可能 */
    /* s2s_eminj_ek1fn_mon[u1g_EJCC_NOX]は、s2g_eminj_ek1fn[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_ek1fn_mon[u1g_EJCC_NOX]は、f4g_eminj_ek1fn[u1g_EJCC_NOX]で代用可能 */
    /* s2s_eminj_ek2fn_mon[u1g_EJCC_NOX]は、s2g_eminj_ek2fn[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_ek2fn_mon[u1g_EJCC_NOX]は、f4g_eminj_ek2fn[u1g_EJCC_NOX]で代用可能 */
    /* s2s_eminj_ek3fn_mon[u1g_EJCC_NOX]は、s2g_eminj_ek3fn[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_ek3fn_mon[u1g_EJCC_NOX]は、f4g_eminj_ek3fn[u1g_EJCC_NOX]で代用可能 */
    /* s2s_eminj_ekrchref_mon[u1g_EJCC_NOX]は、s2g_eminj_ekrchref[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_ekrchref_mon[u1g_EJCC_NOX]は、f4g_eminj_ekrchref[u1g_EJCC_NOX]で代用可能 */
    /* s2s_eminj_ekpfitn_mon[u1g_EJCC_NOX]は、s2g_eminj_ekpfitn[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_ekpfitn_mon[u1g_EJCC_NOX]は、f4g_eminj_ekpfitn[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_ekpfiegrn_mon[u1g_EJCC_NOX]は、f4g_eminj_ekpfiegrn[u1g_EJCC_NOX]で代用可能 */
    /* s2s_eminj_eminj_eainjpn_mon[5]は、s2g_eminj_eainjpn[5]で代用可能 */
    /* f4s_eminj_eminj_eainjpn_mon[5]は、f4g_eminj_eainjpn[5]で代用可能 */
    /* f4s_eminj_eminj_einjend_monは、f4g_eminj_einjendで代用可能 */
    /* s2s_eminj_eminj_eainjdn_mon[6]は、s2g_eminj_eainjdn[6]で代用可能 */
    /* f4s_eminj_eminj_eainjdn_mon[6]は、f4g_eminj_eainjdn[6]で代用可能 */
    /* s4s_eminj_eminj_eqfc_mon[u1g_EJCC_NCYL]は、s4g_eminj_eqfc[u1g_EJCC_NCYL]で代用可能 */
    /* f4s_eminj_eminj_eqfc_mon[u1g_EJCC_NCYL]は、f4g_eminj_eqfc[u1g_EJCC_NCYL]で代用可能 */
    /* s2s_eminj_eminj_ek1fn_mon[u1g_EJCC_NOX]は、s2g_eminj_ek1fn[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_eminj_ek1fn_mon[u1g_EJCC_NOX]は、f4g_eminj_ek1fn[u1g_EJCC_NOX]で代用可能 */
    /* s2s_eminj_eminj_ek2fn_mon[u1g_EJCC_NOX]は、s2g_eminj_ek2fn[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_eminj_ek2fn_mon[u1g_EJCC_NOX]は、f4g_eminj_ek2fn[u1g_EJCC_NOX]で代用可能 */
    /* s2s_eminj_eminj_ek3fn_mon[u1g_EJCC_NOX]は、s2g_eminj_ek3fn[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_eminj_ek3fn_mon[u1g_EJCC_NOX]は、f4g_eminj_ek3fn[u1g_EJCC_NOX]で代用可能 */
    /* s2s_eminj_eminj_ekrchref_mon[u1g_EJCC_NOX]は、s2g_eminj_ekrchref[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_eminj_ekrchref_mon[u1g_EJCC_NOX]は、f4g_eminj_ekrchref[u1g_EJCC_NOX]で代用可能 */
    /* stt_injdat2.u1_exqinjastのモニタ変数は、u1s_eminj_eminj_exqinjast_monで代用可能 */
    /* s2s_eminj_eminj_ekpfit_monは、s2g_eminj_ekpfitで代用可能 */
    /* s2s_eminj_eminj_ekpfitn_mon[u1g_EJCC_NOX]は、s2g_eminj_ekpfitn[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_eminj_ekpfitn_mon[u1g_EJCC_NOX]は、f4g_eminj_ekpfitn[u1g_EJCC_NOX]で代用可能 */
    /* f4s_eminj_eminj_ekpfiegrn_mon[u1g_EJCC_NOX]は、f4g_eminj_ekpfiegrn[u1g_EJCC_NOX]で代用可能 */
    /* s4s_eminj_eminj_eqinjflfix_mon[8]は、s4g_eminj_eqinjflfix[8]で代用可能 */
    /* f4s_eminj_eminj_eqinjflfix_mon[8]は、f4g_eminj_eqinjflfix[8]で代用可能 */
    /* s4s_eminj_eminj_eqinjplfix_mon[8]は、s4g_eminj_eqinjplfix[8]で代用可能 */
    /* f4s_eminj_eminj_eqinjplfix_mon[8]は、f4g_eminj_eqinjplfix[8]で代用可能 */

    if ( u1t_xnercdfew == (u1)ON )                      /* NE同期タスクが少ない */
    {
 #if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
        s4s_eminj_eqinjstp1_mon = stt_injdat.s4_eqinjstp1;
        f4s_eminj_eqinjstp1_mon = stt_injdat.f4_eqinjstp1;
        s4s_eminj_eqinjstp2_mon = stt_injdat.s4_eqinjstp2;
        f4s_eminj_eqinjstp2_mon = stt_injdat.f4_eqinjstp2;
        s4s_eminj_eqinjstp3_mon = stt_injdat.s4_eqinjstp3;
        f4s_eminj_eqinjstp3_mon = stt_injdat.f4_eqinjstp3;
        s4s_eminj_eqinjstp4_mon = stt_injdat.s4_eqinjstp4;
        f4s_eminj_eqinjstp4_mon = stt_injdat.f4_eqinjstp4;
 #endif /* JEEFI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        s4s_eminj_eqinjstd1_mon = stt_injdat.s4_eqinjstd1;
        s4s_eminj_eqinjstd2_mon = stt_injdat.s4_eqinjstd2;
        s4s_eminj_eqinjstd3_mon = stt_injdat.s4_eqinjstd3;
        s4s_eminj_eqinjstd4_mon = stt_injdat.s4_eqinjstd4;
 #endif /* JEEFI */
        /* f4s_eminj_eqinjstd1_monは、f4g_eminj_eqinjstd1で代用可能 */
        /* f4s_eminj_eqinjstd2_monは、f4g_eminj_eqinjstd2で代用可能 */
        /* f4s_eminj_eqinjstd3_monは、f4g_eminj_eqinjstd3で代用可能 */
        /* f4s_eminj_eqinjstd4_monは、f4g_eminj_eqinjstd4で代用可能 */
        /* s4s_eminj_eminj_eqinjstpn_mon[5]は、s4g_eminj_eqinjstpn[5]で代用可能 */
        /* f4s_eminj_eminj_eqinjstpn_mon[5]は、f4g_eminj_eqinjstpn[5]で代用可能 */
        /* s4s_eminj_eminj_eqinjstdn_mon[6]は、s4g_eminj_eqinjstdn[6]で代用可能 */
        /* f4s_eminj_eminj_eqinjstdn_mon[6]は、f4g_eminj_eqinjstdn[6]で代用可能 */
    }
#endif /* M_EMINJ */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    s2g_eminj_eprreq = stt_minj_data.s2_eprreq;
    f4g_eminj_eprreq = (f4)(stt_minj_data.s2_eprreq) * (f4)((32.*2.)/128./256.);
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_NOT_USE                      /*【可変燃圧制御無】*/
    s2g_eminj_eqfreq = stt_minj_data.s2_eqfreq;
#else                           /*【可変燃圧制御有】*/
    s2g_eminj_eprreql = stt_minj_data.s2_eprreql;
    f4g_eminj_eprreql = (f4)(stt_minj_data.s2_eprreql) * (f4)(1280./128./256.);
#endif /* JEPRDEMAND */
    s2g_eminj_ekrichx = s2t_krichx;
    f4g_eminj_ekrichx = (f4)s2t_krichx * (f4)((32.*2.)/128./256.);
    s2g_eminj_ekpfi = s2t_kpfi_wk;
    f4g_eminj_ekpfi = (f4)s2t_kpfi_wk * (f4)((1.*4.)/128./256.);
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        s2g_eminj_ekpfin[u1t_mox] = s2t_kpfin[u1t_mox];
        f4g_eminj_ekpfin[u1t_mox] = (f4)s2t_kpfin[u1t_mox] * (f4)((1.*4.)/128./256.);
    }

    u1s_eminj_exasto = u1t_xast;

    /* ecqinjast_8m（始動後噴射量要求後カウンタ）の操作 */
    if ( stt_injdat.u1_exqinjast == (u1)OFF )   /* 始動時 */
    {
        s2g_eminj_ecqinjast_8m = (s2)(((0.)/(268435.456/128./256.))+0.5);
    }

    /* 噴射ＳＡＣの確定前噴射要求更新処理 */
    /* ※本処理は、本部品の全ての８ｍｓ中タスク処理実施後に行うこと */
    vdg_ainjif_renew_injrq();
}

/*********************************************************************/
/*  関数名        | vdg_eminj_einj_dataget( )                        */
/*  処理内容      | 噴射情報取得処理                                 */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_retval:噴射情報取得バッファのアドレス        */
/*  戻り値        | なし                                             */
/*  注意事項      |                                                  */
/*********************************************************************/
void
vdg_eminj_einj_dataget( st_EMINJ_EINJ *ptt_retval )
{
    u1 u1t_mox;    /* lsb=1 :メインセンサ数 */
    u1 u1t_nox_c;  /* lsb=1 :メインセンサ数 */
    u1 u1t_cyl;    /* lsb=1 :気筒数 */
    u1 u1t_ncyl_c; /* lsb=1 :気筒数 */

    u1t_ncyl_c = u1g_ejcc_NCYL;
    u1t_nox_c = u1g_ejcc_NOX;

    glint_di();         /* 同時性確保 開始 */
    ptt_retval->u2_einjmod = stg_eminj_einj.u2_einjmod;
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    ptt_retval->s2_eainjp1 = stg_eminj_einj.s2_eainjp1;
    ptt_retval->f4_eainjp1 = stg_eminj_einj.f4_eainjp1;
    ptt_retval->s2_eainjp2 = stg_eminj_einj.s2_eainjp2;
    ptt_retval->f4_eainjp2 = stg_eminj_einj.f4_eainjp2;
    ptt_retval->s2_eainjp3 = stg_eminj_einj.s2_eainjp3;
    ptt_retval->f4_eainjp3 = stg_eminj_einj.f4_eainjp3;
    ptt_retval->s2_eainjp4 = stg_eminj_einj.s2_eainjp4;
    ptt_retval->f4_eainjp4 = stg_eminj_einj.f4_eainjp4;
    ptt_retval->s2_einjend = stg_eminj_einj.s2_einjend;
    ptt_retval->f4_einjend = stg_eminj_einj.f4_einjend;
    ptt_retval->s2_eainjcutp = stg_eminj_einj.s2_eainjcutp;
    ptt_retval->f4_eainjcutp = stg_eminj_einj.f4_eainjcutp;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_retval->s2_eainjd1 = stg_eminj_einj.s2_eainjd1;
    ptt_retval->f4_eainjd1 = stg_eminj_einj.f4_eainjd1;
    ptt_retval->s2_eainjd2 = stg_eminj_einj.s2_eainjd2;
    ptt_retval->f4_eainjd2 = stg_eminj_einj.f4_eainjd2;
    ptt_retval->s2_eainjd3 = stg_eminj_einj.s2_eainjd3;
    ptt_retval->f4_eainjd3 = stg_eminj_einj.f4_eainjd3;
    ptt_retval->s2_eainjd4 = stg_eminj_einj.s2_eainjd4;
    ptt_retval->f4_eainjd4 = stg_eminj_einj.f4_eainjd4;
    ptt_retval->s2_eainjcutd = stg_eminj_einj.s2_eainjcutd;
    ptt_retval->f4_eainjcutd = stg_eminj_einj.f4_eainjcutd;
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_PORT      /*【ﾎﾟｰﾄ】*/
    ptt_retval->s2_eainjpadd = stg_eminj_einj.s2_eainjpadd;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_retval->s2_eainjdadd = stg_eminj_einj.s2_eainjdadd;
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    ptt_retval->s4_eqinjstp1 = stg_eminj_einj.s4_eqinjstp1;
    ptt_retval->f4_eqinjstp1 = stg_eminj_einj.f4_eqinjstp1;
    ptt_retval->s4_eqinjstp2 = stg_eminj_einj.s4_eqinjstp2;
    ptt_retval->f4_eqinjstp2 = stg_eminj_einj.f4_eqinjstp2;
    ptt_retval->s4_eqinjstp3 = stg_eminj_einj.s4_eqinjstp3;
    ptt_retval->f4_eqinjstp3 = stg_eminj_einj.f4_eqinjstp3;
    ptt_retval->s4_eqinjstp4 = stg_eminj_einj.s4_eqinjstp4;
    ptt_retval->f4_eqinjstp4 = stg_eminj_einj.f4_eqinjstp4;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_retval->s4_eqinjstd1 = stg_eminj_einj.s4_eqinjstd1;
    ptt_retval->f4_eqinjstd1 = stg_eminj_einj.f4_eqinjstd1;
    ptt_retval->s4_eqinjstd2 = stg_eminj_einj.s4_eqinjstd2;
    ptt_retval->f4_eqinjstd2 = stg_eminj_einj.f4_eqinjstd2;
    ptt_retval->s4_eqinjstd3 = stg_eminj_einj.s4_eqinjstd3;
    ptt_retval->f4_eqinjstd3 = stg_eminj_einj.f4_eqinjstd3;
    ptt_retval->s4_eqinjstd4 = stg_eminj_einj.s4_eqinjstd4;
    ptt_retval->f4_eqinjstd4 = stg_eminj_einj.f4_eqinjstd4;
#endif /* JEEFI */
    for ( u1t_cyl = (u1)0U; u1t_cyl < u1t_ncyl_c; u1t_cyl++ )
    {
        ptt_retval->s4_eqfc[u1t_cyl] = stg_eminj_einj.s4_eqfc[u1t_cyl];
        ptt_retval->f4_eqfc[u1t_cyl] = stg_eminj_einj.f4_eqfc[u1t_cyl];
    }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E                   /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    ptt_retval->s4_eqinjexp = stg_eminj_einj.s4_eqinjexp;
    ptt_retval->f4_eqinjexp = stg_eminj_einj.f4_eqinjexp;
#endif /* JECOMBCCPT_E */
    ptt_retval->s2_ek1f = stg_eminj_einj.s2_ek1f;
    ptt_retval->f4_ek1f = stg_eminj_einj.f4_ek1f;
    ptt_retval->s2_ek2f = stg_eminj_einj.s2_ek2f;
    ptt_retval->f4_ek2f = stg_eminj_einj.f4_ek2f;
    ptt_retval->s2_ek3f = stg_eminj_einj.s2_ek3f;
    ptt_retval->f4_ek3f = stg_eminj_einj.f4_ek3f;
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        ptt_retval->s2_ek1fn[u1t_mox] = stg_eminj_einj.s2_ek1fn[u1t_mox];
        ptt_retval->f4_ek1fn[u1t_mox] = stg_eminj_einj.f4_ek1fn[u1t_mox];
        ptt_retval->s2_ek2fn[u1t_mox] = stg_eminj_einj.s2_ek2fn[u1t_mox];
        ptt_retval->f4_ek2fn[u1t_mox] = stg_eminj_einj.f4_ek2fn[u1t_mox];
        ptt_retval->s2_ek3fn[u1t_mox] = stg_eminj_einj.s2_ek3fn[u1t_mox];
        ptt_retval->f4_ek3fn[u1t_mox] = stg_eminj_einj.f4_ek3fn[u1t_mox];
        ptt_retval->s2_ekrchref[u1t_mox] = stg_eminj_einj.s2_ekrchref[u1t_mox];
        ptt_retval->f4_ekrchref[u1t_mox] = stg_eminj_einj.f4_ekrchref[u1t_mox];
    }
    glbitcp_bibi( stg_eminj_einj.bi_exqinjast, ptt_retval->bi_exqinjast );
    ptt_retval->u1_exqinjast = stg_eminj_einj.u1_exqinjast;
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_retval->u1_explreq = stg_eminj_einj.u1_explreq;
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
    ptt_retval->s2_ekpfit = stg_eminj_einj.s2_ekpfit;
    ptt_retval->f4_ekpfit = stg_eminj_einj.f4_ekpfit;
 #if JEEGR == u1g_EJCC_USE      /*【EGR制御有】*/
    ptt_retval->f4_ekpfiegr = stg_eminj_einj.f4_ekpfiegr;
 #endif /* JEEGR */
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        ptt_retval->s2_ekpfitn[u1t_mox] = stg_eminj_einj.s2_ekpfitn[u1t_mox];
        ptt_retval->f4_ekpfitn[u1t_mox] = stg_eminj_einj.f4_ekpfitn[u1t_mox];
 #if JEEGR == u1g_EJCC_USE      /*【EGR制御有】*/
        ptt_retval->f4_ekpfiegrn[u1t_mox] = stg_eminj_einj.f4_ekpfiegrn[u1t_mox];
 #endif /* JEEGR */
    }
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    ptt_retval->s2_ek1fpt = stg_eminj_einj.s2_ek1fpt;
    ptt_retval->f4_ek1fpt = stg_eminj_einj.f4_ek1fpt;
#endif /* JEEFI */
    glint_ei();       /* 同時性確保 終了 */
}

/*********************************************************************/
/*  関数名        | vdg_eminj_eminj_dataget( )                       */
/*  処理内容      | 噴射情報取得処理（構造体2）                      */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_retval:噴射情報取得バッファのアドレス        */
/*  戻り値        | なし                                             */
/*  注意事項      | 新構造体用                                       */
/*********************************************************************/
void
vdg_eminj_eminj_dataget( st_EMINJ_EMINJ *ptt_retval )
{
    u1 u1t_mox;    /* lsb=1 :メインセンサ数 */
    u1 u1t_nox_c;  /* lsb=1 :メインセンサ数 */
    u1 u1t_cyl;    /* lsb=1 :気筒数 */
    u1 u1t_ncyl_c; /* lsb=1 :気筒数 */
    u1 u1t_injnum; /* lsb=1 :噴射回数 */

    u1t_ncyl_c = u1g_ejcc_NCYL;
    u1t_nox_c = u1g_ejcc_NOX;

    glint_di();         /* 同時性確保 開始 */
    ptt_retval->u2_einjmod = stg_eminj_eminj.u2_einjmod;
    ptt_retval->u4_einjptn = stg_eminj_eminj.u4_einjptn;
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)4U; u1t_injnum++ )
    {
        ptt_retval->s2_eainjpn[u1t_injnum] = stg_eminj_eminj.s2_eainjpn[u1t_injnum];
        ptt_retval->f4_eainjpn[u1t_injnum] = stg_eminj_eminj.f4_eainjpn[u1t_injnum];
    }
    ptt_retval->s2_einjend = stg_eminj_eminj.s2_einjend;
    ptt_retval->f4_einjend = stg_eminj_eminj.f4_einjend;
    ptt_retval->s2_eainjcutp = stg_eminj_eminj.s2_eainjcutp;
    ptt_retval->f4_eainjcutp = stg_eminj_eminj.f4_eainjcutp;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)6U; u1t_injnum++ )
    {
        ptt_retval->s2_eainjdn[u1t_injnum] = stg_eminj_eminj.s2_eainjdn[u1t_injnum];
        ptt_retval->f4_eainjdn[u1t_injnum] = stg_eminj_eminj.f4_eainjdn[u1t_injnum];
    }
    ptt_retval->s2_eainjcutd = stg_eminj_eminj.s2_eainjcutd;
    ptt_retval->f4_eainjcutd = stg_eminj_eminj.f4_eainjcutd;
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_PORT      /*【ﾎﾟｰﾄ】*/
    ptt_retval->s2_eainjpadd = stg_eminj_eminj.s2_eainjpadd;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_retval->s2_eainjdadd = stg_eminj_eminj.s2_eainjdadd;
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)4U; u1t_injnum++ )
    {
        ptt_retval->s4_eqinjstpn[u1t_injnum] = stg_eminj_eminj.s4_eqinjstpn[u1t_injnum];
        ptt_retval->f4_eqinjstpn[u1t_injnum] = stg_eminj_eminj.f4_eqinjstpn[u1t_injnum];
    }
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)6U; u1t_injnum++ )
    {
        ptt_retval->s4_eqinjstdn[u1t_injnum] = stg_eminj_eminj.s4_eqinjstdn[u1t_injnum];
        ptt_retval->f4_eqinjstdn[u1t_injnum] = stg_eminj_eminj.f4_eqinjstdn[u1t_injnum];
    }
#endif /* JEEFI */
    for ( u1t_cyl = (u1)0U; u1t_cyl < u1t_ncyl_c; u1t_cyl++ )
    {
        ptt_retval->s4_eqfc[u1t_cyl] = stg_eminj_eminj.s4_eqfc[u1t_cyl];
        ptt_retval->f4_eqfc[u1t_cyl] = stg_eminj_eminj.f4_eqfc[u1t_cyl];
    }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E                   /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    ptt_retval->s4_eqinjexp = stg_eminj_eminj.s4_eqinjexp;
    ptt_retval->f4_eqinjexp = stg_eminj_eminj.f4_eqinjexp;
#endif /* JECOMBCCPT_E */
    /* 新構造体ではメンバek1f,ek2f,ek3fは準備しない */

    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        ptt_retval->s2_ek1fn[u1t_mox] = stg_eminj_eminj.s2_ek1fn[u1t_mox];
        ptt_retval->f4_ek1fn[u1t_mox] = stg_eminj_eminj.f4_ek1fn[u1t_mox];
        ptt_retval->s2_ek2fn[u1t_mox] = stg_eminj_eminj.s2_ek2fn[u1t_mox];
        ptt_retval->f4_ek2fn[u1t_mox] = stg_eminj_eminj.f4_ek2fn[u1t_mox];
        ptt_retval->s2_ek3fn[u1t_mox] = stg_eminj_eminj.s2_ek3fn[u1t_mox];
        ptt_retval->f4_ek3fn[u1t_mox] = stg_eminj_eminj.f4_ek3fn[u1t_mox];
        ptt_retval->s2_ekrchref[u1t_mox] = stg_eminj_eminj.s2_ekrchref[u1t_mox];
        ptt_retval->f4_ekrchref[u1t_mox] = stg_eminj_eminj.f4_ekrchref[u1t_mox];
    }
    glbitcp_bibi( stg_eminj_eminj.bi_exqinjast, ptt_retval->bi_exqinjast );
    ptt_retval->u1_exqinjast = stg_eminj_eminj.u1_exqinjast;
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_retval->u1_explreq = stg_eminj_eminj.u1_explreq;
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
    ptt_retval->s2_ekpfit = stg_eminj_eminj.s2_ekpfit;
    ptt_retval->f4_ekpfit = stg_eminj_eminj.f4_ekpfit;
 #if JEEGR == u1g_EJCC_USE      /*【EGR制御有】*/
    ptt_retval->f4_ekpfiegr = stg_eminj_eminj.f4_ekpfiegr;
 #endif /* JEEGR */
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        ptt_retval->s2_ekpfitn[u1t_mox] = stg_eminj_eminj.s2_ekpfitn[u1t_mox];
        ptt_retval->f4_ekpfitn[u1t_mox] = stg_eminj_eminj.f4_ekpfitn[u1t_mox];
 #if JEEGR == u1g_EJCC_USE      /*【EGR制御有】*/
        ptt_retval->f4_ekpfiegrn[u1t_mox] = stg_eminj_eminj.f4_ekpfiegrn[u1t_mox];
 #endif /* JEEGR */
    }
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    ptt_retval->s2_ek1fpt = stg_eminj_eminj.s2_ek1fpt;
    ptt_retval->f4_ek1fpt = stg_eminj_eminj.f4_ek1fpt;
#endif /* JEEFI */
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)8U; u1t_injnum++ )
    {
        ptt_retval->s4_eqinjflfix[u1t_injnum] = stg_eminj_eminj.s4_eqinjflfix[u1t_injnum];
        ptt_retval->f4_eqinjflfix[u1t_injnum] = stg_eminj_eminj.f4_eqinjflfix[u1t_injnum];
        ptt_retval->s4_eqinjplfix[u1t_injnum] = stg_eminj_eminj.s4_eqinjplfix[u1t_injnum];
        ptt_retval->f4_eqinjplfix[u1t_injnum] = stg_eminj_eminj.f4_eqinjplfix[u1t_injnum];
    }
    glint_ei();       /* 同時性確保 終了 */
}

/*-------------------------------------------------------------------*/
/* 関数（内部関数）                                                  */
/*-------------------------------------------------------------------*/
/*********************************************************************/
/*  関数名        | vds_eminj_eminj_hpri( )                          */
/*  処理内容      | 優先度選択処理                                   */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_datsel:調停データ格納先のアドレス            */
/*                | ptt_datdft:調停データデフォルト値のアドレス      */
/*                | ptt_datsel2:新調停データ格納先のアドレス         */
/*                | ptt_datdft2:新調停データデフォルト値のアドレス   */
/*  戻り値        | 無し                                             */
/*  注意事項      |                                                  */
/*********************************************************************/
static void
vds_eminj_eminj_hpri( st_EMINJ_EMINJ_DEF *ptt_datsel, const st_EMINJ_EMINJ_DEF *ptt_datdft, st_EMINJ_EMINJ_BUF *ptt_datsel2, const st_EMINJ_EMINJ_BUF *ptt_datdft2 )
{
/* 集約テーブル定義 */
#pragma ghs startdata
/*-------------------------------------------------------------------*/
/* 始動時要求優先選択テーブルの定義                                  */
/*-------------------------------------------------------------------*/
    static volatile const st_EMINJ_EMINJ_TBL sts_eminj_eminjst_tbl[] = /* 注意事項:sts_eminj_eminjst_tbl[]変更時は、以下の部分も同時変更必要  */
                                                                       /*         :ID設定,優先度設定,要求指示用データ設定                     */
                                                                       /*         :調停関数eminj_eminj_hpri()内のスタック算出部分             */
                                                                       /*         :他の優先選択テーブルと複数回参照となる要求を設定する場合は */
                                                                       /*         :rap関数を作成し設定すること                                */
    {
#if ((JERMTCTR == u1g_EJCC_USE) || (JENVCTR == u1g_EJCC_USE)) && (JEMICN_E != u1g_EJCC_SUB_E) && (EMINJ_STACM_MEDI == ON) /* (【ﾘﾓｰﾄｺﾝﾄﾛｰﾙ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】) AND【SUB-CPU以外】AND【始動時吹け上がり制御要求使用】*/
        { &vdg_estacm_emedi_dataget,        u1g_EMINJ_STACM_ID    }, /* 優先度=28 :始動時吹け上がり制御 */
#endif /* JERMTCTR,JENVCTR,JEMICN_E,EMINJ_STACM_MEDI */
#if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E)      /*【SS制御有】OR【EG-MGｸﾗｯﾁ】*/
        { &vdg_estass_emedi_dataget,        u1g_EMINJ_STASS_ID    }, /* 優先度=30 :SS始動制御 */
#endif /* JESS,JEEGMG_E */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)               /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        { &vds_eminj_erestahot_rap_dataget, u1s_EMINJ_RESTAHOT_ID }, /* 優先度=32 :高温再始動制御 */
        { &vdg_ekcst_emedi_dataget,         u1s_EMINJ_KCST_ID     }, /* 優先度=34 :始動時ﾉｯｸ防止制御 */
#endif /* JEEFI */
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT)      /*【ALL HV】AND【ﾎﾟｰﾄ】*/
        { &vds_eminj_erdpn_rap_dataget,     u1g_EMINJ_RDPN_ST_ID  }, /* 優先度=36 :PN低減制御(始動時) */
                                                                     /* 通常要求のＰＮ低減制御と取得関数が分かれた場合は、 */
                                                                     /* 始動時要求調停、通常時要求調停のＰＮ低減制御の判定、rap関数を削除すること */
#endif /* JEALLHV_E,JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)               /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        { &vdg_estratist_emedi_dataget,     u1g_EMINJ_STRATIST_ID }, /* 優先度=42 :成層始動制御 */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL                                           /*【ﾃﾞｭｱﾙINJ】*/
        { &vdg_estafrg_emedi_dataget,       u1g_EMINJ_STAFRG_ID   }, /* 優先度=44 :極低温始動制御 */
#endif /* JEEFI */
#if EMINJ_FREE4 == ON   /*【ﾌﾘｰﾎﾟｰﾄ4使用】*/
        { &vdg_eminj_efree4_emedi_dataget,  u1g_EMINJ_FREE4_ID    }, /* 優先度=204 :ﾌﾘｰﾎﾟｰﾄ4用噴射要求 */
#endif /* EMINJ_FREE4 */
#if EMINJ_FREE5 == ON   /*【ﾌﾘｰﾎﾟｰﾄ5使用】*/
        { &vdg_eminj_efree5_emedi_dataget,  u1g_EMINJ_FREE5_ID    }, /* 優先度=205 :ﾌﾘｰﾎﾟｰﾄ5用噴射要求 */
#endif /* EMINJ_FREE5 */
/* ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
        /* 必ずテーブルの終端に設定すること */
        { &vds_eminj_dummy_emedi_dataget,   u1g_EMINJ_NONE_ID     }  /* 優先度=なし :ダミー */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
    };

/*-------------------------------------------------------------------*/
/* 始動時要求優先選択テーブル２の定義                                */
/*-------------------------------------------------------------------*/
    static volatile const st_EMINJ_EMINJ_TBL2 sts_eminj_eminjst_tbl2[] = /* 注意事項:sts_eminj_eminjst_tbl2[]変更時は、以下の部分も同時変更必要  */
                                                                         /*         :ID設定,優先度設定,要求指示用データ設定                      */
                                                                         /*         :調停関数eminj_eminj_hpri()内のスタック算出部分              */
                                                                         /*         :他の優先選択テーブルと複数回参照となる要求を設定する場合は  */
                                                                         /*         :rap関数を作成し設定すること                                 */
    {
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (EMINJ_STAHV_MEDI == ON)      /*【ALL HV】AND【HV始動制御要求使用】*/
        { &vdg_estahv_emedi_dataget2,       u1g_EMINJ_STAHV_ID    }, /* 優先度=46 :HV始動制御 */
#endif /* JEALLHV_E,EMINJ_STAHV_MEDI */
#if EMINJ_FREE6 == ON   /*【ﾌﾘｰﾎﾟｰﾄ6使用】*/
        { &vdg_eminj_efree6_emedi_dataget,  u1g_EMINJ_FREE6_ID    }, /* 優先度=206 :ﾌﾘｰﾎﾟｰﾄ6用噴射要求 */
#endif /* EMINJ_FREE6 */
#if EMINJ_FREE7 == ON   /*【ﾌﾘｰﾎﾟｰﾄ7使用】*/
        { &vdg_eminj_efree7_emedi_dataget,  u1g_EMINJ_FREE7_ID    }, /* 優先度=207 :ﾌﾘｰﾎﾟｰﾄ7用噴射要求 */
#endif /* EMINJ_FREE7 */
/* ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
        /* 必ずテーブルの終端に設定すること */
        { &vds_eminj_dummy_emedi_dataget2,  u1g_EMINJ_NONE_ID     }  /* 優先度=なし :ダミー */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
    };

/*-------------------------------------------------------------------*/
/* 始動後要求優先選択テーブルの定義                                  */
/*-------------------------------------------------------------------*/
    static volatile const st_EMINJ_EMINJ_TBL sts_eminj_eminjast_tbl[] = /* 注意事項:sts_eminj_eminjast_tbl[]変更時は、以下の部分も同時変更必要 */
                                                                        /*         :ID設定,優先度設定,要求指示用データ設定                     */
                                                                        /*         :調停関数eminj_eminj_hpri()内のスタック算出部分             */
                                                                        /*         :他の優先選択テーブルと複数回参照となる要求を設定する場合は */
                                                                        /*         :rap関数を作成し設定すること                                */
    {
#if ((JERMTCTR == u1g_EJCC_USE) || (JENVCTR == u1g_EJCC_USE)) && (JEMICN_E != u1g_EJCC_SUB_E) && (EMINJ_STACM_MEDI == ON) /* (【ﾘﾓｰﾄｺﾝﾄﾛｰﾙ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】) AND【SUB-CPU以外】AND【始動時吹け上がり制御要求使用】*/
        { &vdg_estacm_emedi_dataget,        u1g_EMINJ_STACM_ID    }, /* 優先度=28 :始動時吹け上がり制御 */
#endif /* JERMTCTR,JENVCTR,JEMICN_E,EMINJ_STACM_MEDI */
#if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E)             /*【SS制御有】OR【EG-MGｸﾗｯﾁ】*/
        { &vdg_estass_emedi_dataget,        u1g_EMINJ_STASS_ID    },    /* 優先度=30 :SS始動制御 */
#endif /* JESS,JEEGMG_E */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)                      /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        { &vdg_estratist_emedi_dataget,     u1g_EMINJ_STRATIST_ID },    /* 優先度=42 :成層始動制御 */
#endif /* JEEFI */
#if EMINJ_FREE8 == ON   /*【ﾌﾘｰﾎﾟｰﾄ8使用】*/
        { &vdg_eminj_efree8_emedi_dataget,  u1g_EMINJ_FREE8_ID    },    /* 優先度=208 :ﾌﾘｰﾎﾟｰﾄ8用噴射要求 */
#endif /* EMINJ_FREE8 */
#if EMINJ_FREE9 == ON   /*【ﾌﾘｰﾎﾟｰﾄ9使用】*/
        { &vdg_eminj_efree9_emedi_dataget,  u1g_EMINJ_FREE9_ID    },    /* 優先度=209 :ﾌﾘｰﾎﾟｰﾄ9用噴射要求 */
#endif /* EMINJ_FREE9 */
/* ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
        /* 必ずテーブルの終端に設定すること */
        { &vds_eminj_dummy_emedi_dataget,   u1g_EMINJ_NONE_ID }         /* 優先度=なし :ダミー */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
    };

/*-------------------------------------------------------------------*/
/* 始動後要求優先選択テーブル２の定義                                */
/*-------------------------------------------------------------------*/
    static volatile const st_EMINJ_EMINJ_TBL2 sts_eminj_eminjast_tbl2[] = /* 注意事項:sts_eminj_eminjast_tbl2[]変更時は、以下の部分も同時変更必要 */
                                                                          /*         :ID設定,優先度設定,要求指示用データ設定                      */
                                                                          /*         :調停関数eminj_eminj_hpri()内のスタック算出部分              */
                                                                          /*         :他の優先選択テーブルと複数回参照となる要求を設定する場合は  */
                                                                          /*         :rap関数を作成し設定すること                                 */
    {
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (EMINJ_STAHV_MEDI == ON)      /*【ALL HV】AND【HV始動制御要求使用】*/
        { &vdg_estahv_emedi_dataget2,        u1g_EMINJ_STAHV_ID    },     /* 優先度=46 :HV始動制御 */
#endif /* JEALLHV_E,EMINJ_STAHV_MEDI */
#if EMINJ_FREE10 == ON   /*【ﾌﾘｰﾎﾟｰﾄ10使用】*/
        { &vdg_eminj_efree10_emedi_dataget,  u1g_EMINJ_FREE10_ID    },    /* 優先度=210 :ﾌﾘｰﾎﾟｰﾄ10用噴射要求 */
#endif /* EMINJ_FREE10 */
#if EMINJ_FREE11 == ON   /*【ﾌﾘｰﾎﾟｰﾄ11使用】*/
        { &vdg_eminj_efree11_emedi_dataget,  u1g_EMINJ_FREE11_ID    },    /* 優先度=211 :ﾌﾘｰﾎﾟｰﾄ11用噴射要求 */
#endif /* EMINJ_FREE11 */
/* ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
        /* 必ずテーブルの終端に設定すること */
        { &vds_eminj_dummy_emedi_dataget2,   u1g_EMINJ_NONE_ID }         /* 優先度=なし :ダミー */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
    };

/*-------------------------------------------------------------------*/
/* 通常優先選択テーブルの定義                                        */
/*-------------------------------------------------------------------*/

    static volatile const st_EMINJ_EMINJ_TBL sts_eminj_eminj_tbl[] = /* 注意事項:sts_eminj_eminj_tbl[]変更時は、以下の部分も同時変更必要    */
                                                                     /*         :ID設定,優先度設定,要求指示用データ設定                     */
                                                                     /*         :調停関数eminj_eminj_hpri()内のスタック算出部分             */
                                                                     /*         :他の優先選択テーブルと複数回参照となる要求を設定する場合は */
                                                                     /*         :rap関数を作成し設定すること                                */
    {
#if (JEMAT_BENCHI == u1g_EJCC_USE) || (JEMAT_BENCH_E == u1g_EJCC_USE)   /*【ﾍﾞﾝﾁ適合用ｿﾌﾄ有】OR【ﾍﾞﾝﾁ適合ﾓｰﾄﾞ有】*/
        { &vdg_ebench_emedi_dataget,        u1g_EMINJ_BENCH_ID    }, /* 優先度=2 :ﾍﾞﾝﾁ適合用噴射要求 */
#endif /* JEMAT_BENCHI,JEMAT_BENCH_E */
        { &vdg_eegstpvs_emedi_dataget,      u1g_EMINJ_EGSTPVS_ID  }, /* 優先度=4 :噴射停止 */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
        { &vdg_edeflair_emedi_dataget,      u1g_EMINJ_DEFLAIR_ID  }, /* 優先度=6 :工場ｴｱ抜き制御 */
#endif /* JEEFI */
#if (JEEGMG_E == u1g_EJCC_HVPLGR_E) || (JEEGMG_E == u1g_EJCC_HVDIRECT_E)    /*【EG-MG遊星ｷﾞｱ】OR【EG-MG直結】*/
        { &vdg_estphv_emedi_dataget,        u1g_EMINJ_STPHV_ID    }, /* 優先度=12 :HV停止制御 */
#endif /* JEEGMG_E */
#if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E)         /*【SS制御有】OR【EG-MGｸﾗｯﾁ】*/
        { &vdg_estpss_emedi_dataget,        u1g_EMINJ_STPSS_ID    }, /* 優先度=14 :SS停止制御 */
#endif /* JESS,JEEGMG_E */
#if JEALLHV_E == u1g_EJCC_ALLHV_E                                       /*【ALL HV】*/
        { &vdg_erdnves_group00_dataget,     u1g_EMINJ_RDNVES_ID   }, /* 優先度=16 :ｴﾝｼﾞﾝ停止・始動時の振動低減 */
#endif /* JEALLHV_E */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        { &vdg_esjc_emedi_dataget,          u1g_EMINJ_SJC_ID      }, /* 優先度=20 :触媒急速暖機制御 */
#endif /* JEEFI */
#if JEALLHV_E == u1g_EJCC_ALLHV_E                                       /*【ALL HV】*/
        { &vdg_ewupcat_emedi_dataget,       u1g_EMINJ_WUPCAT_ID   }, /* 優先度=24 :触媒暖機制御 */
#endif /* JEALLHV_E */
#if (JENGPF_E != u1g_EJCC_NOT_USE) && (EMINJ_FCFRCTRL_MEDI == ON)  /*【GPF有】AND【1気筒FC制御要求使用】*/
        { &vdg_efcfrctrl_emedi_dataget,     u1g_EMINJ_FCFRCTRL_ID }, /* 優先度=26 :1気筒FC制御 */
                                                                     /* ※AES対象機能であるため、AES対象仕向には使用禁止 */
#endif /* JENGPF_E,EMINJ_FCFRCTRL_MEDI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        { &vds_eminj_erestahot_rap_dataget, u1s_EMINJ_RESTAHOT_ID }, /* 優先度=32 :高温再始動制御 */
#endif /* JEEFI */
        { &vdg_efcinjctr_emedi_dataget,     u1g_EMINJ_FCINJCTR_ID }, /* 優先度=50 :FC中燃料噴射制御 */
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI != u1g_EJCC_D4)       /*【ALL HV】AND【D-4以外】*/
        { &vds_eminj_erdpn_rap_dataget,     u1g_EMINJ_RDPN_ID     }, /* 優先度=52 :PN低減制御 */
                                                                     /* 始動時要求のＰＮ低減制御と取得関数が分かれた場合は、 */
                                                                     /* 始動時要求調停、通常時要求調停のＰＮ低減制御の判定,rap関数を削除すること */
#endif /* JEALLHV_E,JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        { &vdg_ertnfc_group00_dataget,      u1s_EMINJ_RTNFC_ID    }, /* 優先度=54 :FC復帰制御 */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
        { &vdg_eclrdepi_emedi_dataget,      u1s_EMINJ_CLRDEPI_ID  }, /* 優先度=56 :ｱｲﾄﾞﾙ時ｲﾝｼﾞｪｸﾀﾃﾞﾎﾟ除去制御 */
 #if JEPRDEMAND == u1g_EJCC_NOT_USE     /*【可変燃圧制御無】*/
        { &vdg_efpldlv_emedi_dataget,       u1s_EMINJ_FPLDLV_ID   }, /* 優先度=60 :低圧ﾃﾞﾘﾊﾞﾘ内燃料脈動回避制御 */
 #endif /* JEPRDEMAND */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
        { &vdg_edthrctrl_emedi_dataget,     u1g_EMINJ_DTHRCTRL_ID }, /* 優先度=64 :気筒別ﾃﾞｨｻﾞ制御 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
 #if (JEPLMLT_E == u1g_EJCC_NOT_USE) && (EMINJ_ACTLFG_MEDI == ON)  /*【PLﾏﾙﾁ噴射無】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】*/
        { &vdg_eactlfg_emedi_dataget,       u1g_EMINJ_ACTLFG_ID   }, /* 優先度=66 :ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御 */
 #endif /* JEPLMLT_E,EMINJ_ACTLFG_MEDI */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
 #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_INJIMB_MEDI == ON)    /*【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ｲﾝﾊﾞﾗﾝｽ時の噴射制御要求使用】*/
        { &vdg_einjimb_emedi_dataget,       u1s_EMINJ_INJIMB_ID   }, /* 優先度=72 :ｲﾝﾊﾞﾗﾝｽ時の噴射制御 */
 #endif /* JEOBDAFIMB_D,EMINJ_INJIMB_MEDI */
 #if JEFFV != u1g_EJCC_NOT_USE  /*【FFV制御有】*/
        { &vdg_eactarefuel_emedi_dataget,   u1s_EMINJ_ACTAREFUEL_ID }, /* 優先度=74 :給油後の噴き分けｱｸﾃｨﾌﾞ制御 */
 #endif /* JEFFV */
 #if EMINJ_ACTOBD_MEDI == ON    /* 【OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
        { &vdg_eactobd_emedi_dataget,       u1g_EMINJ_ACTOBD_ID   }, /* 優先度=76 :OBD要求によるｱｸﾃｨﾌﾞ制御 */
 #endif /* EMINJ_ACTOBD_MEDI */
 #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_IMBRQ_MEDI == ON)  /*【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
        { &vdg_eimbrq_emedi_dataget,        u1g_EMINJ_IMBRQ_ID    }, /* 優先度=78 :ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御 */
 #endif /* JEOBDAFIMB_D,EMINJ_IMBRQ_MEDI */
 #if (JEOBDMF == u1g_EJCC_USE) && (EMINJ_MFINJRQ_MEDI == ON)  /*【失火OBD有】AND【失火OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
        { &vdg_emfinjrq_emedi_dataget,      u1g_EMINJ_MFINJRQ_ID  }, /* 優先度=80 :失火OBD要求によるｱｸﾃｨﾌﾞ制御 */
 #endif /* JEOBDMF,EMINJ_MFINJRQ_MEDI */
 #if (JEOBDFKG == u1g_EJCC_USE) && (EMINJ_FKGDRQ_MEDI == ON)  /* 【燃料OBD有】AND【燃料系OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
        { &vdg_efkgdrq_emedi_dataget,       u1g_EMINJ_FKGDRQ_ID   }, /* 優先度=82 :燃料系OBD要求によるｱｸﾃｨﾌﾞ制御 */
 #endif /* JEOBDFKG,EMINJ_FKGDRQ_MEDI */
        { &vdg_eactgaf_emedi_dataget,       u1g_EMINJ_ACTGAF_ID   }, /* 優先度=84 :A/F学習の為のｱｸﾃｨﾌﾞ制御 */
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        { &vdg_ekctrn_emedi_dataget,        u1s_EMINJ_KCTRN_ID    }, /* 優先度=86 :発進ﾉｯｸ防止制御 */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
        { &vdg_erdvap_emedi_dataget,        u1s_EMINJ_RDVAP_ID    }, /* 優先度=88 :ﾍﾞｰﾊﾟｰ抑制制御 */
        { &vdg_edwnpr_emedi_dataget,        u1s_EMINJ_DWNPR_ID    }, /* 優先度=90 :燃圧低減制御 */
#endif /* JEEFI */
        { &vdg_epwrup_emedi_dataget,        u1s_EMINJ_PWRUP_ID    }  /* 優先度=92 :出力性能向上制御 */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
       ,{ &vdg_eprvdil_emedi_dataget,       u1s_EMINJ_PRVDIL_ID   }  /* 優先度=96 :冷間希釈防止制御 */
#endif /* JEEFI */
#if EMINJ_FREE0 == ON   /*【ﾌﾘｰﾎﾟｰﾄ0使用】*/
       ,{ &vdg_eminj_efree0_emedi_dataget,  u1g_EMINJ_FREE0_ID    }  /* 優先度=200 :ﾌﾘｰﾎﾟｰﾄ0用噴射要求 */
#endif /* EMINJ_FREE0 */
#if EMINJ_FREE1 == ON   /*【ﾌﾘｰﾎﾟｰﾄ1使用】*/
       ,{ &vdg_eminj_efree1_emedi_dataget,  u1g_EMINJ_FREE1_ID    }  /* 優先度=201 :ﾌﾘｰﾎﾟｰﾄ1用噴射要求 */
#endif /* EMINJ_FREE1 */
    };

    static volatile const st_EMINJ_EMINJ_TBL2 sts_eminj_eminj_tbl2[] = /* 注意事項:sts_eminj_eminj_tbl2[]変更時は、以下の部分も同時変更必要   */
                                                                       /*         :ID設定,優先度設定,要求指示用データ設定                     */
                                                                       /*         :調停関数eminj_eminj_hpri()内のスタック算出部分             */
                                                                       /*         :他の優先選択テーブルと複数回参照となる要求を設定する場合は */
                                                                       /*         :rap関数を作成し設定すること                                */
    {
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_WC_MEDI == ON) /*【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】*/
        { &vdg_ebinjplctr_wc_emedi_dataget,  u1g_EMINJ_BINJPLCTR_WC_ID   },    /* 優先度=22 :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時) */
#endif /* JEALLHV_E,JEPLMLT_E,EMINJ_BINJPLCTR_WC_MEDI */
#if (JEEGMG_E == u1g_EJCC_HVPLGR_E) && (JEFFV == u1g_EJCC_NOT_USE) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_STAHV_MEDI == ON) /*【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】*/
        { &vdg_ebinjplctr_stahv_emedi_dataget, u1g_EMINJ_BINJPLCTR_STAHV_ID },    /* 優先度=48 :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時) */
#endif /* JEEGMG_E,JEFFV,JEPLMLT_E,EMINJ_BINJPLCTR_STAHV_MEDI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
 #if (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_ACTLFG_MEDI == ON)  /*【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】*/
        { &vdg_eactlfg_emedi_dataget2,       u1g_EMINJ_ACTLFG_ID   },    /* 優先度=66 :ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御 */
 #endif /* JEPLMLT_E,EMINJ_ACTLFG_MEDI */
#endif /* JEEFI */
#if JEPLMLT_E == u1g_EJCC_USE  /*【PLﾏﾙﾁ噴射有】*/
 #if EMINJ_BINJPLCTR_MEDI == ON   /*【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】*/
        { &vdg_ebinjplctr_emedi_dataget,    u1g_EMINJ_BINJPLCTR_ID   },  /* 優先度=98 :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御 */
 #endif /* EMINJ_BINJPLCTR_MEDI */
#endif /* JEPLMLT_E */
#if EMINJ_FREE2 == ON   /*【ﾌﾘｰﾎﾟｰﾄ2使用】*/
        { &vdg_eminj_efree2_emedi_dataget,  u1g_EMINJ_FREE2_ID    },     /* 優先度=202 :ﾌﾘｰﾎﾟｰﾄ2用噴射要求 */
#endif /* EMINJ_FREE2 */
#if EMINJ_FREE3 == ON   /*【ﾌﾘｰﾎﾟｰﾄ3使用】*/
        { &vdg_eminj_efree3_emedi_dataget,  u1g_EMINJ_FREE3_ID    },     /* 優先度=203 :ﾌﾘｰﾎﾟｰﾄ3用噴射要求 */
#endif /* EMINJ_FREE3 */
/* ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
        /* 必ずテーブルの終端に設定すること */
        { &vds_eminj_dummy_emedi_dataget2,  u1g_EMINJ_NONE_ID }         /* 優先度=なし :ダミー */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
    };

#pragma ghs enddata

    u1 u1t_prisel;                              /* lsb=1 :最高優先度 */
    u1 u1t_idsel;                               /* lsb=1 :要求噴射方式優先度選択反映識別子 */
    u1 u1t_did;                                 /* lsb=1 :集約テーブルインデックス */
    u1 u1t_pri;                                 /* lsb=1 :優先度 */
    u4 u4t_rqdat[2];                            /* lsb=1 :要求指示データ 0:旧構造体、1:新構造体ワーク */
    st_EMINJ_EMINJ_DEF stt_minj_data = { 0 };   /* 集約データワーク(一括初期化) */
    u1 u1t_prisel2;                             /* lsb=1 :最高優先度 */
    u1 u1t_prisel_fix;                          /* lsb=1 :最高優先度 */
    u1 u1t_prifix;                              /* lsb=1 :確定優先度 */
    st_EMINJ_EMINJ_BUF stt_minj_data2 = { 0 };  /* 集約データワーク(一括初期化) */
    u1 u1t_stprisel;                            /* lsb=1 :選択された優先度(始動時) */
    u1 u1t_stprisel2;                           /* lsb=1 :選択された優先度(始動時2) */
    u1 u1t_stdid;                               /* lsb=1 :始動時要求集約テーブルインデックス */
    u1 u1t_stpri;                               /* lsb=1 :始動時要求の優先度 */
    u1 u1t_stpri2;                              /* lsb=1 :始動時要求2の優先度 */
    u4 u4t_strqdat;                             /* lsb=1 :要求指示データ */
    u4 u4t_strqdat2;                            /* lsb=1 :要求指示データ2 */
    u1 u1t_astprisel;                           /* lsb=1 :選択された優先度(始動後) */
    u1 u1t_astprisel2;                          /* lsb=1 :選択された優先度(始動後2) */
    u1 u1t_astdid;                              /* lsb=1 :始動後要求集約テーブルインデックス */
    u1 u1t_astpri;                              /* lsb=1 :始動後要求の優先度 */
    u1 u1t_astpri2;                             /* lsb=1 :始動後要求2の優先度 */
    u1 u1t_xast_edge;                           /* lsb=1 :ON->OFFエッジ成立フラグ */
    u1 u1t_xastmedi;                            /* lsb=1 :始動後要求調停許可フラグ  */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    st_EMINJ_EMINJ_DEF stt_minjst_data = { 0 }; /* 集約データ退避用：始動時(一括初期化) */
    st_EMINJ_EMINJ_BUF stt_minjst_data2 = { 0 }; /* 集約データ退避用：始動時2(一括初期化) */
    u1 u1t_stidsel;                             /* lsb=1 :要求噴射方式優先度選択反映識別子 */
    u1 u1t_stprisel_fix;                        /* lsb=1 :始動時の最高優先度 */
    u1 u1t_sjc_pri_c;                           /* lsb=1 :触媒急速暖機制御の優先度 */
#endif /* JEEFI */
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT)     /*【ALL HV】AND【ﾎﾟｰﾄ】*/
    u1 u1t_rdpn_pri_c;                          /* lsb=1 :PN低減制御の優先度 */
    u1 u1t_rdpn_st_pri_c;                       /* lsb=1 :PN低減制御(始動時)の優先度 */
#endif /* JEALLHV_E,JEEFI */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    u1t_sjc_pri_c = u1g_eminj_SJC_PRI;
    u1t_stidsel = u1g_EMINJ_NONE_ID;   /* 要求噴射方式反映識別子初期化 */
    u1t_stprisel_fix = u1g_EMINJ_PRINORQ;   /* 優先度初期化 */
#endif /* JEEFI */
    u4t_strqdat  = u4s_EMINJ_NORQDAT;   /* 要求噴射方式要求有識別子初期化 */
    u4t_strqdat2 = u4s_EMINJ_NORQDAT;   /* 要求噴射方式要求有識別子初期化 */
    u1t_prisel = u1g_EMINJ_PRINORQ;    /* 優先度初期化 */
    u1t_idsel = u1g_EMINJ_NONE_ID;     /* 要求噴射方式反映識別子初期化 */
    u4t_rqdat[0] = u4s_EMINJ_NORQDAT;  /* 要求噴射方式要求有識別子初期化 */
    u1t_prisel2 = u1g_EMINJ_PRINORQ;   /* 優先度初期化 */
    u1t_prisel_fix = u1g_EMINJ_PRINORQ;    /* 優先度初期化 */
    u1t_prifix = u1g_EMINJ_PRINORQ;    /* 優先度初期化 */

    /* 集約対象部品のdataget関数が複数回参照となるものをNRAMに退避 */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)              /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    vds_eminj_einj_datacopy( &sts_eminj_erestahot_data, ptt_datdft );
    vdg_erestahot_emedi_dataget(&sts_eminj_erestahot_data);     /* 同一周期内でのみ参照するため複数回書き込み問題無 */
#endif /* JEEFI */
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI != u1g_EJCC_D4)       /*【ALL HV】AND【D-4以外】*/
    vds_eminj_einj_datacopy( &sts_eminj_erdpn_data, ptt_datdft );
    vdg_erdpn_emedi_dataget( &sts_eminj_erdpn_data );           /* 同一周期内でのみ参照するため複数回書き込み問題無 */
#endif /* JEALLHV_E,JEEFI */

    /* exastmedi（始動後要求調停許可フラグ）のクリア処理 */
    u1t_xast_edge = (u1)OFF;
    u1t_xastmedi = u1s_eminj_exastmedi;
    if ( ( u1s_eminj_exasto == (u1)ON )             /* 始動判定時 */
      && ( u1s_eminj_exast_lch == (u1)OFF ) )
    {
        u1t_xast_edge = (u1)ON; /* ON->OFFエッジ成立 */
        u1t_xastmedi = (u1)OFF;
    }

    /* eminjst_tblとeminjast_tbl、eminjst_tbl2とeminjast_tbl2を使う要求の調停 */
    if ( u1t_xastmedi == (u1)OFF )  /* 始動時要求調停時 */
    {
        /* 始動時,始動後の調停は背反条件のためif~else実装としているが */
        /* if~if実装を行う場合はestpri、estpri2、eastpri、eastpri2、einjmedislidのラッチが必要になるため注意すること */
        /* 優先度の比較を行う場合は、要求なし時にu1g_EMINJ_PRINORQ(0)となり高優先と誤って判定するため注意すること */
        u1t_stprisel   = u1g_EMINJ_PRINORQ;
        u1t_stprisel2  = u1g_EMINJ_PRINORQ;
        u1t_astprisel  = u1g_EMINJ_PRINORQ; /* 無効化 */ /* temp:仕様確認の内容反映(DENG-STD-25017②) */
        u1t_astprisel2 = u1g_EMINJ_PRINORQ; /* 無効化 */ /* temp:仕様確認の内容反映(DENG-STD-25017②) */

        /* 始動時要求テーブル調停 */
        for ( u1t_stdid = (u1)0U; u1t_stdid < u1s_EMINJ_EMINJST_NUM; u1t_stdid++ )
        {
            vds_eminj_einj_datacopy( &stt_minj_data, ptt_datdft );
            sts_eminj_eminjst_tbl[u1t_stdid].pt_dataget( &stt_minj_data );
#ifdef JGXSTACK         /* スタック算出用 */
 #if ((JERMTCTR == u1g_EJCC_USE) || (JENVCTR == u1g_EJCC_USE)) && (JEMICN_E != u1g_EJCC_SUB_E) && (EMINJ_STACM_MEDI == ON) /* (【ﾘﾓｰﾄｺﾝﾄﾛｰﾙ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】) AND【SUB-CPU以外】AND【始動時吹け上がり制御要求使用】*/
            vdg_estacm_emedi_dataget(&stt_minj_data);
 #endif /* JERMTCTR,JENVCTR,JEMICN_E,EMINJ_STACM_MEDI */
 #if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E)    /*【SS制御有】OR【EG-MGｸﾗｯﾁ】*/
            vdg_estass_emedi_dataget(&stt_minj_data);
 #endif /* JESS,JEEGMG_E */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)             /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
            vds_eminj_erestahot_rap_dataget(&stt_minj_data);
            vdg_ekcst_emedi_dataget(&stt_minj_data);
 #endif /* JEEFI */
 #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT)    /*【ALL HV】AND【ﾎﾟｰﾄ】*/
            vds_eminj_erdpn_rap_dataget(&stt_minj_data);
 #endif /* JEALLHV_E,JEEFI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)             /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
            vdg_estratist_emedi_dataget(&stt_minj_data);
 #endif /* JEEFI */
 #if JEEFI == u1g_EJCC_DUAL                                         /*【ﾃﾞｭｱﾙINJ】*/
            vdg_estafrg_emedi_dataget(&stt_minj_data);
 #endif /* JEEFI */
 #if EMINJ_FREE4 == ON   /*【ﾌﾘｰﾎﾟｰﾄ4使用】*/
            vdg_eminj_efree4_emedi_dataget(&stt_minj_data);
 #endif /* EMINJ_FREE4 */
 #if EMINJ_FREE5 == ON   /*【ﾌﾘｰﾎﾟｰﾄ5使用】*/
            vdg_eminj_efree5_emedi_dataget(&stt_minj_data);
 #endif /* EMINJ_FREE5 */

#endif  /* JGXSTACK */
            u1t_stpri = stt_minj_data.u1_pri;      /* 優先度取得 */

#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT)     /*【ALL HV】AND【ﾎﾟｰﾄ】*/
            u1t_rdpn_pri_c = u1g_eminj_RDPN_PRI;
#endif /* JEALLHV_E,JEEFI */

            if ( ( u1t_stpri != u1g_EMINJ_PRINORQ )     /* 調停許可時 */
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT)     /*【ALL HV】AND【ﾎﾟｰﾄ】*/
              && ( u1t_stpri != u1t_rdpn_pri_c )        /* ＰＮ低減制御要求でない */
                                                        /* ＰＮ低減制御要求のdataget関数が始動時と通常時で共通のため、通常時の要求でないことを判定する */
#endif /* JEALLHV_E,JEEFI */
               )
            {
                if ( ( u1t_idsel == u1g_EMINJ_NONE_ID )     /* 初回更新条件 */
                  || ( u1t_stprisel > u1t_stpri ) )         /* 優先選択(優先度のMINセレクト) */
                {
                    u1t_stprisel = u1t_stpri;                                             /* 優先度更新 */
                    u1t_prisel_fix = u1t_stpri;                                           /* 優先度更新 */
                    u1t_prifix = u1t_stpri;                                               /* 確定優先度更新 */
                    u1t_idsel = sts_eminj_eminjst_tbl[u1t_stdid].u1_id;                   /* 識別子更新 */
                    u4t_rqdat[0] = stt_minj_data.u4_einjrq_dat;                           /* 要求有識別子更新 */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
                    if ( ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP) != (u4)0U )                 /* ポート噴射開始時期要求有り */
                      && ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP1) == (u4)0U ) )              /* ポート1回目噴射開始時期要求無し */
                    {
                        stt_minj_data.s2_eainjp1 = stt_minj_data.s2_eainjp;               /* ポート1回目噴射開始時期更新 */
                    }
                    if ( ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP) != (u4)0U )               /* ポート始動時噴射量要求有り */
                      && ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP1) == (u4)0U ) )            /* ポート1回目始動時噴射量要求無し */
                    {
                        stt_minj_data.s4_eqinjstp1 = stt_minj_data.s4_eqinjstp;           /* ポート1回目始動時噴射量更新 */
                    }
#endif /* JEEFI */
                    vds_eminj_einj_datacopy( ptt_datsel, &stt_minj_data );

                    /* 始動時の調停結果を退避 */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
                    vds_eminj_einj_datacopy( &stt_minjst_data, &stt_minj_data );
                    u1t_stprisel_fix = u1t_stpri;
                    u1t_stidsel = u1t_idsel;
#endif /* JEEFI */
                    u4t_strqdat = u4t_rqdat[0];
                }
            }
        } /* 始動時要求テーブル調停ループ終了 */

        if ( u1t_stprisel != u1g_EMINJ_PRINORQ )   /* 始動時優先選択要求がある時 */
        {
            if ( (u4t_strqdat & u4g_EMINJ_RQXQINJAST) == (u4)0U )   /* 始動後噴射量要求フラグ要求無し */
                                                                    /* eminj_8msm()にも同様の処理があるため変更時は合わせて見直すこと */
            {
                glbitcp_bibi( ptt_datdft->bi_exqinjast, ptt_datsel->bi_exqinjast ); /* stt_minjst_data.bi_exqinjastは更新しないため */
                                                                                    /* exqinjast は ptt_datsel->bi_exqinjastを参照すること */
            }
            /* exastmedi（始動後要求調停許可フラグ）のセット処理 */
            if ( ptt_datsel->bi_exqinjast == (u1)ON )   /* 始動制御による始動後噴射量要求時 */
            {
                if ( u1t_xast_edge == (u1)OFF )         /* クリア優先のため、クリア条件の逆条件で判定 */
                {
                    u1t_xastmedi = (u1)ON;
                }
                u1s_eminj_estprir = u1t_stprisel;
            }
        }

        /* ここまでの旧構造体情報をデフォルトとして新構造体に移植 */
        vds_eminj_einj_dataconv( ptt_datsel2, ptt_datsel );
        u4t_rqdat[1] = ptt_datsel2->u4_einjrq_dat;
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        vds_eminj_einj_dataconv( &stt_minjst_data2, &stt_minjst_data );
#endif /* JEEFI */

        /* 始動時要求テーブル2調停 */
        for ( u1t_stdid = (u1)0U; u1t_stdid < u1s_EMINJ_EMINJST_NUM2; u1t_stdid++ )
        {
            vds_eminj_einj_datacopy2( &stt_minj_data2, ptt_datdft2 );
            sts_eminj_eminjst_tbl2[u1t_stdid].pt_dataget2( &stt_minj_data2 );
#ifdef JGXSTACK         /* スタック算出用 */
 #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (EMINJ_STAHV_MEDI == ON)    /*【ALL HV】AND【HV始動制御要求使用】*/
            vdg_estahv_emedi_dataget2(&stt_minj_data2);
 #endif /* JEALLHV_E,EMINJ_STAHV_MEDI */
 #if EMINJ_FREE6 == ON   /*【ﾌﾘｰﾎﾟｰﾄ6使用】*/
            vdg_eminj_efree6_emedi_dataget(&stt_minj_data2);
 #endif /* EMINJ_FREE6 */
 #if EMINJ_FREE7 == ON   /*【ﾌﾘｰﾎﾟｰﾄ7使用】*/
            vdg_eminj_efree7_emedi_dataget(&stt_minj_data2);
 #endif /* EMINJ_FREE7 */
#endif  /* JGXSTACK */

            u1t_stpri2 = stt_minj_data2.u1_pri; /* 優先度取得 */

            if ( u1t_stpri2 != u1g_EMINJ_PRINORQ )  /* 始動時優先選択要求２がある時 */
            {
                if ( ( u1t_stprisel2 == u1g_EMINJ_PRINORQ ) /* 初回更新条件 */
                  || ( u1t_stprisel2 > u1t_stpri2 ) )       /* 優先選択(優先度のMINセレクト) */
                {
                    u1t_stprisel2 = u1t_stpri2;     /* 優先度更新 */

                    if ( ( u1t_stpri2 < u1t_stprisel )            /* 始動時優先要求（旧構造体）より高優先度の時 */
                      || ( u1t_stprisel == u1g_EMINJ_PRINORQ ) )  /* 始動時優先要求（旧構造体）に優先度要求なし */
                    {
                        u1t_prisel_fix = u1t_stpri2;                            /* 優先度更新 */
                        u1t_prifix = u1t_stpri2;                                /* 確定優先度更新 */
                        u1t_idsel = sts_eminj_eminjst_tbl2[u1t_stdid].u1_id;    /* 識別子更新 */
                        u4t_rqdat[1] = stt_minj_data2.u4_einjrq_dat;            /* 要求有識別子更新 */
                        u4t_strqdat2 = u4t_rqdat[1];
                        vds_eminj_einj_datacopy2( ptt_datsel2, &stt_minj_data2 );
                        /* 始動時の調停結果を退避 */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
                        vds_eminj_einj_datacopy2( &stt_minjst_data2, &stt_minj_data2 );
                        u1t_stprisel_fix = u1t_stpri2;
                        u1t_stidsel = u1t_idsel;
#endif /* JEEFI */
                    }
                }
            }
        } /* 始動時要求テーブル2調停ループ終了 */

        if ( ( u1t_stprisel2 != u1g_EMINJ_PRINORQ )
          && ( ( u1t_stprisel == u1g_EMINJ_PRINORQ )
            || ( u1t_stprisel2 < u1t_stprisel ) ) ) /* 始動時優先選択要求２がある時、かつ、始動時優先要求より高優先度の時 */
        {
            if ( (u4t_strqdat2 & u4g_EMINJ_RQXQINJAST) == (u4)0U )  /* 始動後噴射量要求フラグ要求無し */
                                                                    /* eminj_8msm()にも同様の処理があるため変更時は合わせて見直すこと */
            {
                glbitcp_bibi( ptt_datdft2->bi_exqinjast, ptt_datsel2->bi_exqinjast );   /* stt_minjst_data2.bi_exqinjastは更新していないため */
                                                                                        /* exqinjast は ptt_datsel2->bi_exqinjastを参照する  */
            }
            /* exastmedi（始動後要求調停許可フラグ）のセット処理 */
            if ( ptt_datsel2->bi_exqinjast == (u1)ON )  /* 始動制御による始動後噴射量要求時 */
            {
                if ( u1t_xast_edge == (u1)OFF )         /* クリア優先のため、クリア条件の逆条件で判定 */
                {
                    u1t_xastmedi = (u1)ON;
                }
                u1s_eminj_estprir = u1t_stprisel2;
            }
            /* ここまでの新構造体情報を旧構造体に移植 */
            vds_eminj_einj_dataconv_rev( ptt_datsel, ptt_datsel2 );
            u4t_rqdat[0] = ptt_datsel->u4_einjrq_dat;
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
            vds_eminj_einj_dataconv_rev( &stt_minjst_data, &stt_minjst_data2 );
#endif /* JEEFI */
        }

    }
    else            /* 始動後要求調停時 */
    {
        /* 始動時,始動後の調停は背反条件のためif~else実装としているが */
        /* if~if実装を行う場合はestpri、eastpri、einjmedislidのラッチが必要になるため注意すること */
        /* 優先度の比較を行う場合は、要求なし時にu1g_EMINJ_PRINORQ(0)となり高優先と誤って判定するため注意すること */
        u1t_stprisel   = u1g_EMINJ_PRINORQ; /* 無効化 */ /* temp:仕様確認の内容反映(DENG-STD-25017②) */
        u1t_stprisel2  = u1g_EMINJ_PRINORQ; /* 無効化 */ /* temp:仕様確認の内容反映(DENG-STD-25017②) */
        u1t_astprisel  = u1g_EMINJ_PRINORQ; /* 変更時はeminj_eminjlmt_hpri()もあわせて見直すこと */
        u1t_astprisel2 = u1g_EMINJ_PRINORQ;

        /* 始動後要求テーブル調停 */
        for ( u1t_astdid = (u1)0U; u1t_astdid < u1s_EMINJ_EMINJAST_NUM; u1t_astdid++ )
        {
            vds_eminj_einj_datacopy( &stt_minj_data, ptt_datdft );
            sts_eminj_eminjast_tbl[u1t_astdid].pt_dataget( &stt_minj_data );
#ifdef JGXSTACK         /* スタック算出用 */
 #if ((JERMTCTR == u1g_EJCC_USE) || (JENVCTR == u1g_EJCC_USE)) && (JEMICN_E != u1g_EJCC_SUB_E) && (EMINJ_STACM_MEDI == ON) /* (【ﾘﾓｰﾄｺﾝﾄﾛｰﾙ有】OR【ﾅﾋﾞｺﾝﾄﾛｰﾙ有】) AND【SUB-CPU以外】AND【始動時吹け上がり制御要求使用】*/
            vdg_estacm_emedi_dataget(&stt_minj_data);
 #endif /* JERMTCTR,JENVCTR,JEMICN_E,EMINJ_STACM_MEDI */
 #if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E)    /*【SS制御有】OR【EG-MGｸﾗｯﾁ】*/
            vdg_estass_emedi_dataget(&stt_minj_data);
 #endif /* JESS,JEEGMG_E */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)             /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
            vdg_estratist_emedi_dataget(&stt_minj_data);
 #endif /* JEEFI */
 #if EMINJ_FREE8 == ON   /*【ﾌﾘｰﾎﾟｰﾄ8使用】*/
            vdg_eminj_efree8_emedi_dataget(&stt_minj_data);
 #endif /* EMINJ_FREE8 */
 #if EMINJ_FREE9 == ON   /*【ﾌﾘｰﾎﾟｰﾄ9使用】*/
            vdg_eminj_efree9_emedi_dataget(&stt_minj_data);
 #endif /* EMINJ_FREE9 */
#endif  /* JGXSTACK */

            u1t_astpri = stt_minj_data.u1_pri;
            if ( u1t_astpri != u1g_EMINJ_PRINORQ )      /* 調停許可時 */
            {
                if ( u1t_astpri == u1s_eminj_estprir )  /* 始動時から継承された始動後要求がある場合 */
                                                        /* 継承された機能を探索するのみのため優先度の比較は不要 */
                {
                    u1t_astprisel = u1t_astpri;                                           /* 優先度更新 */
                    u1t_prisel_fix = u1t_astpri;                                          /* 優先度更新 */
                    u1t_prifix = u1t_astpri;                                              /* 確定優先度更新 */
                    u1t_idsel = sts_eminj_eminjast_tbl[u1t_astdid].u1_id;                 /* 識別子更新 */
                    u4t_rqdat[0] = stt_minj_data.u4_einjrq_dat;                           /* 要求有識別子更新 */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
                    if ( ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP) != (u4)0U )                 /* ポート噴射開始時期要求有り */
                      && ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP1) == (u4)0U ) )              /* ポート1回目噴射開始時期要求無し */
                    {
                        stt_minj_data.s2_eainjp1 = stt_minj_data.s2_eainjp;               /* ポート1回目噴射開始時期更新 */
                    }
                    if ( ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP) != (u4)0U )               /* ポート始動時噴射量要求有り */
                      && ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP1) == (u4)0U ) )            /* ポート1回目始動時噴射量要求無し */
                    {
                        stt_minj_data.s4_eqinjstp1 = stt_minj_data.s4_eqinjstp;           /* ポート1回目始動時噴射量更新 */
                    }
#endif /* JEEFI */
                    vds_eminj_einj_datacopy( ptt_datsel, &stt_minj_data );
                }
            }
        } /* 始動後要求テーブル調停ループ終了 */

        vds_eminj_einj_dataconv( ptt_datsel2, ptt_datsel ); /* ここまでの旧構造体情報をデフォルトとして新構造体に移植 */
        u4t_rqdat[1] = ptt_datsel2->u4_einjrq_dat;          /* 要求有識別子更新 */

        /* 始動後要求テーブル2調停 */
        for ( u1t_astdid = (u1)0U; u1t_astdid < u1s_EMINJ_EMINJAST_NUM2; u1t_astdid++ )
        {
            vds_eminj_einj_datacopy2( &stt_minj_data2, ptt_datdft2 );
            sts_eminj_eminjast_tbl2[u1t_astdid].pt_dataget2( &stt_minj_data2 );
#ifdef JGXSTACK         /* スタック算出用 */
 #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (EMINJ_STAHV_MEDI == ON)    /*【ALL HV】AND【HV始動制御要求使用】*/
            vdg_estahv_emedi_dataget2(&stt_minj_data2);
 #endif /* JEALLHV_E,EMINJ_STAHV_MEDI */
 #if EMINJ_FREE10 == ON     /*【ﾌﾘｰﾎﾟｰﾄ10使用】*/
            vdg_eminj_efree10_emedi_dataget(&stt_minj_data2);
 #endif /* EMINJ_FREE10 */
 #if EMINJ_FREE11 == ON     /*【ﾌﾘｰﾎﾟｰﾄ11使用】*/
            vdg_eminj_efree11_emedi_dataget(&stt_minj_data2);
 #endif /* EMINJ_FREE11 */
#endif  /* JGXSTACK */

            u1t_astpri2 = stt_minj_data2.u1_pri; /* 優先度取得 */

            if ( u1t_astpri2 != u1g_EMINJ_PRINORQ )     /* 始動時優先選択要求２がある時 */
            {
                if ( u1t_astpri2 == u1s_eminj_estprir ) /* 始動時から継承された始動後要求がある場合 */
                                                        /* 継承された機能を探索するのみのため優先度の比較は不要 */
                {
                    u1t_astprisel2 = u1t_astpri2;                           /* 優先度更新 */
                    u1t_prisel_fix = u1t_astpri2;                           /* 優先度更新 */
                    u1t_prifix = u1t_astpri2;                               /* 確定優先度更新 */
                    u1t_idsel = sts_eminj_eminjast_tbl2[u1t_astdid].u1_id;  /* 識別子更新 */
                    u4t_rqdat[1] = stt_minj_data2.u4_einjrq_dat;            /* 要求有識別子更新 */
                    vds_eminj_einj_datacopy2( ptt_datsel2, &stt_minj_data2 );
                    vds_eminj_einj_dataconv_rev( ptt_datsel, ptt_datsel2 ); /* ここまでの新構造体情報を旧構造体に移植 */
                    u4t_rqdat[0] = ptt_datsel->u4_einjrq_dat;               /* 要求有識別子更新 */
                }
            }
        } /* 始動後要求テーブル2調停ループ終了 */

    }

    u1s_eminj_estpri = u1t_stprisel;
    u1s_eminj_estpri2 = u1t_stprisel2;
    u1s_eminj_eastpri = u1t_astprisel;
    u1s_eminj_eastpri2 = u1t_astprisel2;
    u1s_eminj_exastmedi = u1t_xastmedi;

    /* 優先度要素の調停 */
    for ( u1t_did = (u1)0U; u1t_did < u1s_EMINJ_EMINJ_NUM; u1t_did++ )
    {
        vds_eminj_einj_datacopy( &stt_minj_data, ptt_datdft );
        sts_eminj_eminj_tbl[u1t_did].pt_dataget( &stt_minj_data );
#ifdef JGXSTACK         /* スタック算出用 */
 #if (JEMAT_BENCHI == u1g_EJCC_USE) || (JEMAT_BENCH_E == u1g_EJCC_USE)   /*【ﾍﾞﾝﾁ適合用ｿﾌﾄ有】OR【ﾍﾞﾝﾁ適合ﾓｰﾄﾞ有】*/
        vdg_ebench_emedi_dataget(&stt_minj_data);
 #endif /* JEMAT_BENCHI,JEMAT_BENCH_E */
        vdg_eegstpvs_emedi_dataget(&stt_minj_data);
 #if JEEFI == u1g_EJCC_DUAL     /*【ﾃﾞｭｱﾙINJ】*/
        vdg_edeflair_emedi_dataget(&stt_minj_data);
 #endif /* JEEFI */
 #if (JEEGMG_E == u1g_EJCC_HVPLGR_E) || (JEEGMG_E == u1g_EJCC_HVDIRECT_E)    /*【EG-MG遊星ｷﾞｱ】OR【EG-MG直結】*/
        vdg_estphv_emedi_dataget(&stt_minj_data);
 #endif /* JEEGMG_E */
 #if (JESS == u1g_EJCC_USE) || (JEEGMG_E == u1g_EJCC_HVCLUTCH_E)         /*【SS制御有】OR【EG-MGｸﾗｯﾁ】*/
        vdg_estpss_emedi_dataget(&stt_minj_data);
 #endif /* JESS,JEEGMG_E */
 #if JEALLHV_E == u1g_EJCC_ALLHV_E                                       /*【ALL HV】*/
        vdg_erdnves_group00_dataget(&stt_minj_data);
 #endif /* JEALLHV_E */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        vdg_esjc_emedi_dataget(&stt_minj_data);
 #endif /* JEEFI */
 #if JEALLHV_E == u1g_EJCC_ALLHV_E                                       /*【ALL HV】*/
        vdg_ewupcat_emedi_dataget(&stt_minj_data);
 #endif /* JEALLHV_E */
 #if (JENGPF_E != u1g_EJCC_NOT_USE) && (EMINJ_FCFRCTRL_MEDI == ON)  /*【GPF有】AND【1気筒FC制御要求使用】*/
        vdg_efcfrctrl_emedi_dataget(&stt_minj_data);
 #endif /* JENGPF_E,EMINJ_FCFRCTRL_MEDI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        vds_eminj_erestahot_rap_dataget(&stt_minj_data);
 #endif /* JEEFI */
        vdg_efcinjctr_emedi_dataget(&stt_minj_data);
 #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI != u1g_EJCC_D4)      /*【ALL HV】AND【D-4以外】*/
        vds_eminj_erdpn_rap_dataget(&stt_minj_data);
 #endif /* JEALLHV_E,JEEFI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        vdg_ertnfc_group00_dataget(&stt_minj_data);
 #endif /* JEEFI */
 #if JEEFI == u1g_EJCC_DUAL     /*【ﾃﾞｭｱﾙINJ】*/
        vdg_eclrdepi_emedi_dataget(&stt_minj_data);
  #if JEPRDEMAND == u1g_EJCC_NOT_USE    /*【可変燃圧制御無】*/
        vdg_efpldlv_emedi_dataget(&stt_minj_data);
  #endif /* JEPRDEMAND */
 #endif /* JEEFI */
 #if JEEFI == u1g_EJCC_DUAL     /*【ﾃﾞｭｱﾙINJ】*/
        vdg_edthrctrl_emedi_dataget(&stt_minj_data);
 #endif /* JEEFI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
  #if (JEPLMLT_E == u1g_EJCC_NOT_USE) && (EMINJ_ACTLFG_MEDI == ON)  /*【PLﾏﾙﾁ噴射無】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】*/
        vdg_eactlfg_emedi_dataget(&stt_minj_data);
  #endif /* JEPLMLT_E,EMINJ_ACTLFG_MEDI */
 #endif /* JEEFI */
 #if JEEFI == u1g_EJCC_DUAL     /*【ﾃﾞｭｱﾙINJ】*/
  #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_INJIMB_MEDI == ON)   /*【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ｲﾝﾊﾞﾗﾝｽ時の噴射制御要求使用】*/
        vdg_einjimb_emedi_dataget(&stt_minj_data);
  #endif /* JEOBDAFIMB_D,EMINJ_INJIMB_MEDI */
  #if JEFFV != u1g_EJCC_NOT_USE     /*【FFV制御有】*/
        vdg_eactarefuel_emedi_dataget(&stt_minj_data);
  #endif /* JEFFV */
  #if EMINJ_ACTOBD_MEDI == ON    /* 【OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
        vdg_eactobd_emedi_dataget(&stt_minj_data);
  #endif /* EMINJ_ACTOBD_MEDI */
  #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_IMBRQ_MEDI == ON)  /*【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
        vdg_eimbrq_emedi_dataget(&stt_minj_data);
  #endif /* JEOBDAFIMB_D,EMINJ_IMBRQ_MEDI */
  #if (JEOBDMF == u1g_EJCC_USE) && (EMINJ_MFINJRQ_MEDI == ON)  /*【失火OBD有】AND【失火OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
        vdg_emfinjrq_emedi_dataget(&stt_minj_data);
  #endif /* JEOBDMF,EMINJ_MFINJRQ_MEDI */
  #if (JEOBDFKG == u1g_EJCC_USE) && (EMINJ_FKGDRQ_MEDI == ON)  /* 【燃料OBD有】AND【燃料系OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
        vdg_efkgdrq_emedi_dataget(&stt_minj_data);
  #endif /* JEOBDFKG,EMINJ_FKGDRQ_MEDI */
        vdg_eactgaf_emedi_dataget(&stt_minj_data);
 #endif /* JEEFI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        vdg_ekctrn_emedi_dataget(&stt_minj_data);
 #endif /* JEEFI */
 #if JEEFI == u1g_EJCC_DUAL     /*【ﾃﾞｭｱﾙINJ】*/
        vdg_erdvap_emedi_dataget(&stt_minj_data);
        vdg_edwnpr_emedi_dataget(&stt_minj_data);
 #endif /* JEEFI */
        vdg_epwrup_emedi_dataget(&stt_minj_data);
 #if JEEFI == u1g_EJCC_DUAL     /*【ﾃﾞｭｱﾙINJ】*/
        vdg_eprvdil_emedi_dataget(&stt_minj_data);
 #endif /* JEEFI */
 #if EMINJ_FREE0 == ON   /*【ﾌﾘｰﾎﾟｰﾄ0使用】*/
        vdg_eminj_efree0_emedi_dataget(&stt_minj_data);
 #endif /* EMINJ_FREE0 */
 #if EMINJ_FREE1 == ON   /*【ﾌﾘｰﾎﾟｰﾄ1使用】*/
        vdg_eminj_efree1_emedi_dataget(&stt_minj_data);
 #endif /* EMINJ_FREE1 */
#endif  /* JGXSTACK */
        u1t_pri = stt_minj_data.u1_pri;      /* 優先度取得 */

#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT)     /*【ALL HV】AND【ﾎﾟｰﾄ】*/
        u1t_rdpn_st_pri_c = u1g_eminj_RDPN_ST_PRI;
#endif /* JEALLHV_E,JEEFI */

        if ( ( u1t_pri != u1g_EMINJ_PRINORQ )       /* 通常噴射制御要求有の時 */
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI == u1g_EJCC_PORT)     /*【ALL HV】AND【ﾎﾟｰﾄ】*/
          && ( u1t_pri != u1t_rdpn_st_pri_c )       /* ＰＮ低減制御(始動時)要求でない */
                                                    /* ＰＮ低減制御要求のdataget関数が始動時と通常時で共通のため、始動時の要求でないことを判定する */
#endif /* JEALLHV_E,JEEFI */
           )
        {
            if ( ( u1t_prisel == u1g_EMINJ_PRINORQ )    /* 初回更新条件 */
              || ( u1t_prisel > u1t_pri ) )             /* 優先選択(優先度のMINセレクト) */
            {
                u1t_prisel = u1t_pri;   /* 優先度更新 */

                if ( ( ( u1t_stprisel == u1g_EMINJ_PRINORQ )    /* 始動時要求（旧構造体）に優先度要求なし */
                    || ( u1t_pri < u1t_stprisel ) )             /* 始動時要求（旧構造体）より高優先度要求あり */
                  && ( ( u1t_astprisel == u1g_EMINJ_PRINORQ )   /* 始動後要求（旧構造体）に優先度要求なし */
                    || ( u1t_pri < u1t_astprisel ) )            /* 始動後要求（旧構造体）より高優先度要求あり */
                  && ( ( u1t_stprisel2 == u1g_EMINJ_PRINORQ )   /* 始動時要求2（新構造体）に優先度要求なし */
                    || ( u1t_pri < u1t_stprisel2 ) )            /* 始動時要求2（新構造体）より高優先度要求あり */
                  && ( ( u1t_astprisel2 == u1g_EMINJ_PRINORQ )  /* 始動後要求2（新構造体）に優先度要求なし */
                    || ( u1t_pri < u1t_astprisel2 ) ) )         /* 始動後要求2（新構造体）より高優先度要求あり */
                {
                    u1t_prisel_fix = u1t_pri;                                           /* 優先度更新 */
                    u1t_prifix = u1t_pri;                                               /* 確定優先度更新 */
                    u1t_idsel = sts_eminj_eminj_tbl[u1t_did].u1_id;                     /* 識別子更新 */
                    u4t_rqdat[0] = stt_minj_data.u4_einjrq_dat;                         /* 要求有識別子更新 */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
                    if ( ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP) != (u4)0U )               /* ポート噴射開始時期要求有り */
                      && ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP1) == (u4)0U ) )            /* ポート1回目噴射開始時期要求無し */
                    {
                        stt_minj_data.s2_eainjp1 = stt_minj_data.s2_eainjp;             /* ポート1回目噴射開始時期更新 */
                    }
                    if ( ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP) != (u4)0U )             /* ポート始動時噴射量要求有り */
                      && ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP1) == (u4)0U ) )          /* ポート1回目始動時噴射量要求無し */
                    {
                        stt_minj_data.s4_eqinjstp1 = stt_minj_data.s4_eqinjstp;         /* ポート1回目始動時噴射量更新 */
                    }
#endif /* JEEFI */
                    vds_eminj_einj_datacopy( ptt_datsel, &stt_minj_data );
                    vds_eminj_einj_dataconv( ptt_datsel2, ptt_datsel ); /* ここまでの旧構造体情報を新構造体に移植 */
                    u4t_rqdat[1] = ptt_datsel2->u4_einjrq_dat;          /* 要求有識別子更新 */
                }
            }
        }
    }

    u1s_eminj_epri = u1t_prisel;

    /* 優先度要素の調停 */
    /* 新構造体要求専用 */
    for ( u1t_did = (u1)0U; u1t_did < u1s_EMINJ_EMINJ_NUM2; u1t_did++ )
    {
        vds_eminj_einj_datacopy2( &stt_minj_data2, ptt_datdft2 );
        sts_eminj_eminj_tbl2[u1t_did].pt_dataget2( &stt_minj_data2 );
#ifdef JGXSTACK         /* スタック算出用 */
 #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_WC_MEDI == ON) /*【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】*/
        vdg_ebinjplctr_wc_emedi_dataget(&stt_minj_data2);
 #endif /* JEALLHV_E,JEPLMLT_E,EMINJ_BINJPLCTR_WC_MEDI */
 #if (JEEGMG_E == u1g_EJCC_HVPLGR_E) && (JEFFV == u1g_EJCC_NOT_USE) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_STAHV_MEDI == ON) /*【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】*/
        vdg_ebinjplctr_stahv_emedi_dataget(&stt_minj_data2);
 #endif /* JEEGMG_E,JEFFV,JEPLMLT_E,EMINJ_BINJPLCTR_STAHV_MEDI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
  #if (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_ACTLFG_MEDI == ON)  /*【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】*/
        vdg_eactlfg_emedi_dataget2(&stt_minj_data2);
  #endif /* JEPLMLT_E,EMINJ_ACTLFG_MEDI */
 #endif /* JEEFI */
 #if JEPLMLT_E == u1g_EJCC_USE  /*【PLﾏﾙﾁ噴射有】*/
  #if EMINJ_BINJPLCTR_MEDI == ON   /*【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】*/
        vdg_ebinjplctr_emedi_dataget(&stt_minj_data2);
  #endif /* EMINJ_BINJPLCTR_MEDI */
 #endif /* JEPLMLT_E */
 #if EMINJ_FREE2 == ON   /*【ﾌﾘｰﾎﾟｰﾄ2使用】*/
        vdg_eminj_efree2_emedi_dataget(&stt_minj_data2);
 #endif /* EMINJ_FREE2 */
 #if EMINJ_FREE3 == ON   /*【ﾌﾘｰﾎﾟｰﾄ3使用】*/
        vdg_eminj_efree3_emedi_dataget(&stt_minj_data2);
 #endif /* EMINJ_FREE3 */
#endif  /* JGXSTACK */

        u1t_pri = stt_minj_data2.u1_pri;    /* 優先度取得 */

        if ( u1t_pri != u1g_EMINJ_PRINORQ )                 /* 通常要求2の噴射制御要求有の時 */
        {
            if ( ( u1t_prisel2 == u1g_EMINJ_PRINORQ )      /* 初回更新条件 */
              || ( u1t_prisel2 > u1t_pri ) )               /* 優先選択(優先度のMINセレクト) */
            {
                u1t_prisel2 = u1t_pri;  /* 優先度更新 */

                if ( ( ( u1t_stprisel == u1g_EMINJ_PRINORQ )    /* 始動時要求（旧構造体）に優先度要求なし */
                    || ( u1t_pri < u1t_stprisel ) )             /* 始動時要求（旧構造体）より高優先度要求あり */
                  && ( ( u1t_astprisel == u1g_EMINJ_PRINORQ )   /* 始動後要求（旧構造体）に優先度要求なし */
                    || ( u1t_pri < u1t_astprisel ) )            /* 始動後要求（旧構造体）より高優先度要求あり */
                  && ( ( u1t_stprisel2 == u1g_EMINJ_PRINORQ )   /* 始動時要求2（新構造体）に優先度要求なし */
                    || ( u1t_pri < u1t_stprisel2 ) )            /* 始動時要求2（新構造体）より高優先度要求あり */
                  && ( ( u1t_astprisel2 == u1g_EMINJ_PRINORQ )  /* 始動後要求2（新構造体）に優先度要求なし */
                    || ( u1t_pri < u1t_astprisel2 ) )           /* 始動後要求2（新構造体）より高優先度要求あり */
                  && ( ( u1t_prisel == u1g_EMINJ_PRINORQ )      /* 通常要求（旧構造体）に優先度要求なし */
                    || ( u1t_pri < u1t_prisel ) ) )             /* 通常要求（旧構造体）より高優先度要求あり */ /* 通常要求（旧構造体）より低優先度要求の場合は調停処理しない */
                {
                    u1t_prisel_fix = u1t_pri;                                   /* 優先度更新 */
                    u1t_prifix = u1t_pri;                                       /* 確定優先度更新 */
                    u1t_idsel = sts_eminj_eminj_tbl2[u1t_did].u1_id;            /* 識別子更新 */
                    u4t_rqdat[1] = stt_minj_data2.u4_einjrq_dat;                /* 要求有識別子更新 */

                    vds_eminj_einj_datacopy2( ptt_datsel2, &stt_minj_data2 );
                    vds_eminj_einj_dataconv_rev( ptt_datsel, &stt_minj_data2 ); /* ここまでの新構造体情報を旧構造体に移植 */
                    u4t_rqdat[0] = ptt_datsel->u4_einjrq_dat;                   /* 要求有識別子更新 */
                }
            }

        }
    }

    u1s_eminj_epri2 = u1t_prisel2;                  /* 変更時はeminj_eminjlmt_hpri()もあわせて見直すこと */

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    if ( ( ( u1t_prisel == u1t_sjc_pri_c )
        && ( u1t_prisel_fix >= u1t_prisel ) )
      && ( ( u1t_stprisel > u1t_sjc_pri_c )
        || ( u1t_stprisel2 > u1t_sjc_pri_c ) ) )    /* 始動時テーブルまたは始動時テーブル２の要求より通常テーブルの触媒急速暖機要求が高優先になった場合 */ /* temp:仕様確認の内容反映(DENG-STD-25013③) */
                                                    /* (estpri > eminj_SJC_PRI)条件成立時、(estpri ≠ EMINJ_PRINORQ)は必ず成立するため条件から省略      */
                                                    /* (estpri2 > eminj_SJC_PRI)条件成立時、(estpri2 ≠ EMINJ_PRINORQ)は必ず成立するため条件から省略    */
    {
        vds_eminj_einj_datacopy( ptt_datsel, &stt_minjst_data );    /* 触媒急速暖機要求をマスク */
        vds_eminj_einj_datacopy2( ptt_datsel2, &stt_minjst_data2 ); /* 触媒急速暖機要求をマスク */
        u1t_idsel = u1t_stidsel;
        u4t_rqdat[0] = ptt_datsel->u4_einjrq_dat;
        u1t_prisel_fix = u1t_stprisel_fix;
        u1t_prifix = u1t_stprisel_fix;
        u4t_rqdat[1] = ptt_datsel2->u4_einjrq_dat;
    }
#endif /* JEEFI */

    u1g_eminj_einjmedislid = u1t_idsel;
    u1s_eminj_eprisel_fix = u1t_prisel_fix;
    u1s_eminj_eprifix = u1t_prifix;
    u4s_eminj_erqdat[0] = u4t_rqdat[0];             /* 要求噴射方式要求有識別子格納 */
    u4s_eminj_erqdat[1] = u4t_rqdat[1];             /* 要求噴射方式要求有識別子格納 */

}

/*********************************************************************/
/*  関数名        | vds_eminj_eminjlmt_hpri( )                       */
/*  処理内容      | 調停制約時の優先度選択処理                       */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_datsel:調停データ格納先のアドレス            */
/*                | ptt_datdft:調停データデフォルト値のアドレス      */
/*                | ptt_datsel2:新調停データ格納先のアドレス         */
/*                | ptt_datdft2:新調停データデフォルト値のアドレス   */
/*  戻り値        | 無し                                             */
/*  注意事項      |                                                  */
/*********************************************************************/
static void
vds_eminj_eminjlmt_hpri( st_EMINJ_EMINJ_DEF *ptt_datsel, const st_EMINJ_EMINJ_DEF *ptt_datdft, st_EMINJ_EMINJ_BUF *ptt_datsel2, const st_EMINJ_EMINJ_BUF *ptt_datdft2 )
{
/* 集約テーブル定義 */
#pragma ghs startdata
    static volatile const st_EMINJ_EMINJ_TBL sts_eminj_eminjlmt_tbl[] = /* 注意事項:sts_eminj_eminjlmt_tbl[]変更時は、以下の部分も同時変更必要 */
                                                                        /*         :ID設定,優先度設定,要求指示用データ設定                     */
                                                                        /*         :調停関数eminj_eminjlmt_hpri()内のスタック算出部分          */
                                                                        /*         :他の優先選択テーブルと複数回参照となる要求を設定する場合は */
                                                                        /*         :rap関数を作成し設定すること                                */
    {
#if (JEMAT_BENCHI == u1g_EJCC_USE) || (JEMAT_BENCH_E == u1g_EJCC_USE)   /*【ﾍﾞﾝﾁ適合用ｿﾌﾄ有】OR【ﾍﾞﾝﾁ適合ﾓｰﾄﾞ有】*/
        { &vdg_ebench_emedi_dataget,        u1g_EMINJ_BENCH_ID    }, /* 優先度=2 :ﾍﾞﾝﾁ適合用噴射要求 */
#endif /* JEMAT_BENCHI,JEMAT_BENCH_E */
        { &vdg_eegstpvs_emedi_dataget,      u1g_EMINJ_EGSTPVS_ID  }, /* 優先度=4 :噴射停止 */
#if (JEEGMG_E == u1g_EJCC_HVPLGR_E) || (JEEGMG_E == u1g_EJCC_HVDIRECT_E)    /*【EG-MG遊星ｷﾞｱ】OR【EG-MG直結】*/
        { &vdg_estphv_emedi_dataget,        u1g_EMINJ_STPHV_ID    }, /* 優先度=12 :HV停止制御 */
#endif /* JEEGMG_E */
        { &vdg_efcinjctr_emedi_dataget,     u1g_EMINJ_FCINJCTR_ID }, /* 優先度=50 :FC中燃料噴射制御 */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
 #if (JEPLMLT_E == u1g_EJCC_NOT_USE) && (EMINJ_ACTLFG_MEDI == ON)  /*【PLﾏﾙﾁ噴射無】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】*/
        { &vdg_eactlfg_emedi_dataget,       u1g_EMINJ_ACTLFG_ID   }, /* 優先度=66 :ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御 */
 #endif /* JEPLMLT_E,EMINJ_ACTLFG_MEDI */
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
 #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_INJIMB_MEDI == ON)    /*【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ｲﾝﾊﾞﾗﾝｽ時の噴射制御要求使用】*/
        { &vdg_einjimb_emedi_dataget,       u1s_EMINJ_INJIMB_ID   }, /* 優先度=72 :ｲﾝﾊﾞﾗﾝｽ時の噴射制御 */
 #endif /* JEOBDAFIMB_D,EMINJ_INJIMB_MEDI */
 #if JEFFV != u1g_EJCC_NOT_USE  /*【FFV制御有】*/
        { &vdg_eactarefuel_emedi_dataget,   u1s_EMINJ_ACTAREFUEL_ID }, /* 優先度=74 :給油後の噴き分けｱｸﾃｨﾌﾞ制御 */
 #endif /* JEFFV */
 #if EMINJ_ACTOBD_MEDI == ON    /* 【OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
        { &vdg_eactobd_emedi_dataget,       u1g_EMINJ_ACTOBD_ID   }, /* 優先度=76 :OBD要求によるｱｸﾃｨﾌﾞ制御 */
 #endif /* EMINJ_ACTOBD_MEDI */
 #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_IMBRQ_MEDI == ON)  /*【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
        { &vdg_eimbrq_emedi_dataget,        u1g_EMINJ_IMBRQ_ID    }, /* 優先度=78 :ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御 */
 #endif /* JEOBDAFIMB_D,EMINJ_IMBRQ_MEDI */
 #if (JEOBDMF == u1g_EJCC_USE) && (EMINJ_MFINJRQ_MEDI == ON)  /*【失火OBD有】AND【失火OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
        { &vdg_emfinjrq_emedi_dataget,      u1g_EMINJ_MFINJRQ_ID  }, /* 優先度=80 :失火OBD要求によるｱｸﾃｨﾌﾞ制御 */
 #endif /* JEOBDMF,EMINJ_MFINJRQ_MEDI */
 #if (JEOBDFKG == u1g_EJCC_USE) && (EMINJ_FKGDRQ_MEDI == ON)  /* 【燃料OBD有】AND【燃料系OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
        { &vdg_efkgdrq_emedi_dataget,       u1g_EMINJ_FKGDRQ_ID   }, /* 優先度=82 :燃料系OBD要求によるｱｸﾃｨﾌﾞ制御 */
 #endif /* JEOBDFKG,EMINJ_FKGDRQ_MEDI */
        { &vdg_eactgaf_emedi_dataget,       u1g_EMINJ_ACTGAF_ID   }, /* 優先度=84 :A/F学習の為のｱｸﾃｨﾌﾞ制御 */
        { &vdg_erdvap_emedi_dataget,        u1s_EMINJ_RDVAP_ID    }, /* 優先度=88 :ﾍﾞｰﾊﾟｰ抑制制御 */
        { &vdg_edwnpr_emedi_dataget,        u1s_EMINJ_DWNPR_ID    }, /* 優先度=90 :燃圧低減制御 */
#endif /* JEEFI */
        { &vdg_epwrup_emedi_dataget,        u1s_EMINJ_PWRUP_ID    }  /* 優先度=92 :出力性能向上制御 */
#if EMINJ_FREE0 == ON   /*【ﾌﾘｰﾎﾟｰﾄ0使用】*/
       ,{ &vdg_eminj_efree0_emedi_dataget,  u1g_EMINJ_FREE0_ID    }  /* 優先度=200 :ﾌﾘｰﾎﾟｰﾄ0用噴射要求 */
#endif /* EMINJ_FREE0 */
#if EMINJ_FREE1 == ON   /*【ﾌﾘｰﾎﾟｰﾄ1使用】*/
       ,{ &vdg_eminj_efree1_emedi_dataget,  u1g_EMINJ_FREE1_ID    }  /* 優先度=201 :ﾌﾘｰﾎﾟｰﾄ1用噴射要求 */
#endif /* EMINJ_FREE1 */
    };

    static volatile const st_EMINJ_EMINJ_TBL2 sts_eminj_eminjlmt_tbl2[] = /* 注意事項:sts_eminj_eminjlmt_tbl2[]変更時は、以下の部分も同時変更必要 */
                                                                          /*         :ID設定,優先度設定,要求指示用データ設定                      */
                                                                          /*         :調停関数eminj_eminjlmt_hpri()内のスタック算出部分           */
                                                                          /*         :他の優先選択テーブルと複数回参照となる要求を設定する場合は  */
                                                                          /*         :rap関数を作成し設定すること                                 */
    {
#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_WC_MEDI == ON) /*【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】*/
        { &vdg_ebinjplctr_wc_emedi_dataget,  u1g_EMINJ_BINJPLCTR_WC_ID   },    /* 優先度=22 :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時) */
#endif /* JEALLHV_E,JEPLMLT_E,EMINJ_BINJPLCTR_WC_MEDI */
#if (JEEGMG_E == u1g_EJCC_HVPLGR_E) && (JEFFV == u1g_EJCC_NOT_USE) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_STAHV_MEDI == ON) /*【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】*/
        { &vdg_ebinjplctr_stahv_emedi_dataget, u1g_EMINJ_BINJPLCTR_STAHV_ID },    /* 優先度=48 :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時) */
#endif /* JEEGMG_E,JEFFV,JEPLMLT_E,EMINJ_BINJPLCTR_STAHV_MEDI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
 #if (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_ACTLFG_MEDI == ON)  /*【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】*/
        { &vdg_eactlfg_emedi_dataget2,       u1g_EMINJ_ACTLFG_ID   },    /* 優先度=66 :ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御 */
 #endif /* JEPLMLT_E,EMINJ_ACTLFG_MEDI */
#endif /* JEEFI */
#if JEPLMLT_E == u1g_EJCC_USE  /*【PLﾏﾙﾁ噴射有】*/
 #if EMINJ_BINJPLCTR_MEDI == ON   /*【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】*/
        { &vdg_ebinjplctr_emedi_dataget,    u1g_EMINJ_BINJPLCTR_ID   },  /* 優先度=98 :ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御 */
 #endif /* EMINJ_BINJPLCTR_MEDI */
#endif /* JEPLMLT_E */
#if EMINJ_FREE2 == ON   /*【ﾌﾘｰﾎﾟｰﾄ2使用】*/
        { &vdg_eminj_efree2_emedi_dataget,  u1g_EMINJ_FREE2_ID    },     /* 優先度=202 :ﾌﾘｰﾎﾟｰﾄ2用噴射要求 */
#endif /* EMINJ_FREE2 */
#if EMINJ_FREE3 == ON   /*【ﾌﾘｰﾎﾟｰﾄ3使用】*/
        { &vdg_eminj_efree3_emedi_dataget,  u1g_EMINJ_FREE3_ID    },     /* 優先度=203 :ﾌﾘｰﾎﾟｰﾄ3用噴射要求 */
#endif /* EMINJ_FREE3 */
/* ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
        /* 必ずテーブルの終端に設定すること */
        { &vds_eminj_dummy_emedi_dataget2,   u1g_EMINJ_NONE_ID }         /* 優先度=なし :ダミー */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */
    };

#pragma ghs enddata

    u1 u1t_prisel;                              /* lsb=1 :最高優先度 */
    u1 u1t_idsel;                               /* lsb=1 :要求噴射方式優先度選択反映識別子 */
    u1 u1t_did;                                 /* lsb=1 :集約テーブルインデックス */
    u1 u1t_pri;                                 /* lsb=1 :優先度 */
    u4 u4t_rqdat[2];                            /* lsb=1 :要求指示データ 0:旧構造体、1:新構造体ワーク */
    st_EMINJ_EMINJ_DEF stt_minj_data = { 0 };   /* 集約データワーク(一括初期化) */
    u1 u1t_prisel2;                             /* lsb=1 :最高優先度 */
    u1 u1t_prisel_fix;                          /* lsb=1 :最高優先度 */
    u1 u1t_prifix;                              /* lsb=1 :確定優先度 */
    st_EMINJ_EMINJ_BUF stt_minj_data2 = { 0 };  /* 集約データワーク(一括初期化) */

    u1t_prisel = u1g_EMINJ_PRINORQ;    /* 優先度初期化 */
    u1t_idsel = u1g_EMINJ_NONE_ID;     /* 要求噴射方式反映識別子初期化 */
    u4t_rqdat[0] = u4s_EMINJ_NORQDAT;  /* 要求噴射方式要求有識別子初期化 */
    u1t_prisel2 = u1g_EMINJ_PRINORQ;   /* 優先度初期化 */

    /* eminjst_tbl,eminjst_tbl2,eminjast_tbl,eminjast_tbl2に調停制約有の要求がないため */
    /* 始動時、始動時2、始動後、始動後2の調停と要求値の更新処理を省略する */
    u1s_eminj_estpri = u1g_EMINJ_PRINORQ;   /* 変更時はeminj_eminj_hpri()もあわせて見直すこと */ /* temp:仕様確認の内容反映(DENG-STD-25017②) */
    u1s_eminj_estpri2 = u1g_EMINJ_PRINORQ;  /* 変更時はeminj_eminj_hpri()もあわせて見直すこと */ /* temp:仕様確認の内容反映(DENG-STD-25017②) */
    u1s_eminj_eastpri = u1g_EMINJ_PRINORQ;  /* 変更時はeminj_eminj_hpri()もあわせて見直すこと */ /* temp:仕様確認の内容反映(DENG-STD-25017②) */
    u1s_eminj_eastpri2 = u1g_EMINJ_PRINORQ; /* 変更時はeminj_eminj_hpri()もあわせて見直すこと */ /* temp:仕様確認の内容反映(DENG-STD-25017②) */

    /* 優先度要素の調停 */
    for ( u1t_did = (u1)0U; u1t_did < u1s_EMINJ_EMINJLMT_NUM; u1t_did++ )
    {
        vds_eminj_einj_datacopy( &stt_minj_data, ptt_datdft );
        sts_eminj_eminjlmt_tbl[u1t_did].pt_dataget( &stt_minj_data );
#ifdef JGXSTACK         /* スタック算出用 */
 #if (JEMAT_BENCHI == u1g_EJCC_USE) || (JEMAT_BENCH_E == u1g_EJCC_USE)   /*【ﾍﾞﾝﾁ適合用ｿﾌﾄ有】OR【ﾍﾞﾝﾁ適合ﾓｰﾄﾞ有】*/
        vdg_ebench_emedi_dataget(&stt_minj_data);
 #endif /* JEMAT_BENCHI,JEMAT_BENCH_E */
        vdg_eegstpvs_emedi_dataget(&stt_minj_data);
 #if (JEEGMG_E == u1g_EJCC_HVPLGR_E) || (JEEGMG_E == u1g_EJCC_HVDIRECT_E)    /*【EG-MG遊星ｷﾞｱ】OR【EG-MG直結】*/
        vdg_estphv_emedi_dataget(&stt_minj_data);
 #endif /* JEEGMG_E */
        vdg_efcinjctr_emedi_dataget(&stt_minj_data);
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4) /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
  #if (JEPLMLT_E == u1g_EJCC_NOT_USE) && (EMINJ_ACTLFG_MEDI == ON)   /*【PLﾏﾙﾁ噴射無】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】*/
        vdg_eactlfg_emedi_dataget(&stt_minj_data);
  #endif /* JEPLMLT_E,EMINJ_ACTLFG_MEDI */
 #endif /* JEEFI */
 #if JEEFI == u1g_EJCC_DUAL     /*【ﾃﾞｭｱﾙINJ】*/
  #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_INJIMB_MEDI == ON)    /*【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ｲﾝﾊﾞﾗﾝｽ時の噴射制御要求使用】*/
        vdg_einjimb_emedi_dataget(&stt_minj_data);
  #endif /* JEOBDAFIMB_D,EMINJ_INJIMB_MEDI */
  #if JEFFV != u1g_EJCC_NOT_USE     /*【FFV制御有】*/
        vdg_eactarefuel_emedi_dataget(&stt_minj_data);
  #endif /* JEFFV */
  #if EMINJ_ACTOBD_MEDI == ON    /* 【OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
        vdg_eactobd_emedi_dataget(&stt_minj_data);
  #endif /* EMINJ_ACTOBD_MEDI */
  #if (JEOBDAFIMB_D == u1g_EJCC_USE) && (EMINJ_IMBRQ_MEDI == ON)  /*【AF気筒間ｲﾝﾊﾞﾗﾝｽ有】AND【ｲﾝﾊﾞﾗﾝｽOBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
        vdg_eimbrq_emedi_dataget(&stt_minj_data);
  #endif /* JEOBDAFIMB_D,EMINJ_IMBRQ_MEDI */
  #if (JEOBDMF == u1g_EJCC_USE) && (EMINJ_MFINJRQ_MEDI == ON)  /*【失火OBD有】AND【失火OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】*/
        vdg_emfinjrq_emedi_dataget(&stt_minj_data);
  #endif /* JEOBDMF,EMINJ_MFINJRQ_MEDI */
  #if (JEOBDFKG == u1g_EJCC_USE) && (EMINJ_FKGDRQ_MEDI == ON)  /* 【燃料OBD有】AND【燃料系OBD要求によるｱｸﾃｨﾌﾞ制御要求使用】 */
        vdg_efkgdrq_emedi_dataget(&stt_minj_data);
  #endif /* JEOBDFKG,EMINJ_FKGDRQ_MEDI */
        vdg_eactgaf_emedi_dataget(&stt_minj_data);
        vdg_erdvap_emedi_dataget(&stt_minj_data);
        vdg_edwnpr_emedi_dataget(&stt_minj_data);
 #endif /* JEEFI */
        vdg_epwrup_emedi_dataget(&stt_minj_data);
 #if EMINJ_FREE0 == ON   /*【ﾌﾘｰﾎﾟｰﾄ0使用】*/
        vdg_eminj_efree0_emedi_dataget(&stt_minj_data);
 #endif /* EMINJ_FREE0 */
 #if EMINJ_FREE1 == ON   /*【ﾌﾘｰﾎﾟｰﾄ1使用】*/
        vdg_eminj_efree1_emedi_dataget(&stt_minj_data);
 #endif /* EMINJ_FREE1 */
#endif  /* JGXSTACK */
        u1t_pri = stt_minj_data.u1_pri;      /* 優先度取得 */

        if ( u1t_pri != u1g_EMINJ_PRINORQ )  /* 調停許可時 */
        {
            if ( ( u1t_idsel == u1g_EMINJ_NONE_ID )     /* 初回更新条件 */
              || ( u1t_prisel > u1t_pri ) )             /* 優先選択(優先度のMINセレクト) */
            {
                u1t_prisel = u1t_pri;                                                 /* 優先度更新 */
                u1t_idsel = sts_eminj_eminjlmt_tbl[u1t_did].u1_id;                    /* 識別子更新 */
                u4t_rqdat[0] = stt_minj_data.u4_einjrq_dat;                           /* 要求有識別子更新 */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
                if ( ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP) != (u4)0U )                 /* ポート噴射開始時期要求有り */
                  && ( (u4t_rqdat[0] & u4g_EMINJ_RQAINJP1) == (u4)0U ) )              /* ポート1回目噴射開始時期要求無し */
                {
                    stt_minj_data.s2_eainjp1 = stt_minj_data.s2_eainjp;               /* ポート1回目噴射開始時期更新 */
                }
                if ( ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP) != (u4)0U )               /* ポート始動時噴射量要求有り */
                  && ( (u4t_rqdat[0] & u4g_EMINJ_RQQINJSTP1) == (u4)0U ) )            /* ポート1回目始動時噴射量要求無し */
                {
                    stt_minj_data.s4_eqinjstp1 = stt_minj_data.s4_eqinjstp;           /* ポート1回目始動時噴射量更新 */
                }
#endif /* JEEFI */
                vds_eminj_einj_datacopy( ptt_datsel, &stt_minj_data );

            }
        }
    }

    u1s_eminj_epri = u1t_prisel;
    u1t_prisel_fix = u1t_prisel;
    u1t_prifix = u1t_prisel; /* 確定優先度更新 */

    /* 優先度要素の調停 */
    /* 新構造体要求専用 */
    vds_eminj_einj_dataconv( ptt_datsel2, ptt_datsel ); /* ここまでの旧構造体情報をデフォルトとして新構造体に移植 */

    u4t_rqdat[1] = ptt_datsel2->u4_einjrq_dat;  /* 初期化 */

    for ( u1t_did = (u1)0U; u1t_did < u1s_EMINJ_EMINJLMT_NUM2; u1t_did++ )
    {
        vds_eminj_einj_datacopy2( &stt_minj_data2, ptt_datdft2 );
        sts_eminj_eminjlmt_tbl2[u1t_did].pt_dataget2( &stt_minj_data2 );
#ifdef JGXSTACK         /* スタック算出用 */
 #if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_WC_MEDI == ON) /*【ALL HV】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(触媒暖機時)要求使用】*/
        vdg_ebinjplctr_wc_emedi_dataget(&stt_minj_data2);
 #endif /* JEALLHV_E,JEPLMLT_E,EMINJ_BINJPLCTR_WC_MEDI */
 #if (JEEGMG_E == u1g_EJCC_HVPLGR_E) && (JEFFV == u1g_EJCC_NOT_USE) && (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_BINJPLCTR_STAHV_MEDI == ON) /*【EG-MG遊星ｷﾞｱ】AND【FFV制御無】AND【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御(HV始動制御時)要求使用】*/
        vdg_ebinjplctr_stahv_emedi_dataget(&stt_minj_data2);
 #endif /* JEEGMG_E,JEFFV,JEPLMLT_E,EMINJ_BINJPLCTR_STAHV_MEDI */
 #if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
  #if (JEPLMLT_E == u1g_EJCC_USE) && (EMINJ_ACTLFG_MEDI == ON)  /*【PLﾏﾙﾁ噴射有】AND【ﾊﾟｰｼｬﾙﾘﾌﾄ学習の為のｱｸﾃｨﾌﾞ制御要求使用】*/
        vdg_eactlfg_emedi_dataget2(&stt_minj_data2);
  #endif /* JEPLMLT_E,EMINJ_ACTLFG_MEDI */
 #endif /* JEEFI */
 #if JEPLMLT_E == u1g_EJCC_USE  /*【PLﾏﾙﾁ噴射有】*/
  #if EMINJ_BINJPLCTR_MEDI == ON   /*【ﾊﾟｰｼｬﾙﾘﾌﾄ噴射を用いた基本噴射制御要求使用】*/
        vdg_ebinjplctr_emedi_dataget(&stt_minj_data2);
  #endif /* EMINJ_BINJPLCTR_MEDI */
 #endif /* JEPLMLT_E */
 #if EMINJ_FREE2 == ON   /*【ﾌﾘｰﾎﾟｰﾄ2使用】*/
        vdg_eminj_efree2_emedi_dataget(&stt_minj_data2);
 #endif /* EMINJ_FREE2 */
 #if EMINJ_FREE3 == ON   /*【ﾌﾘｰﾎﾟｰﾄ3使用】*/
        vdg_eminj_efree3_emedi_dataget(&stt_minj_data2);
 #endif /* EMINJ_FREE3 */
#endif  /* JGXSTACK */

        u1t_pri = stt_minj_data2.u1_pri;       /* 優先度取得 */

        if ( u1t_pri != u1g_EMINJ_PRINORQ )    /* 調停許可時 */
        {
            if ( ( u1t_prisel2 == u1g_EMINJ_PRINORQ )    /* 初回更新条件 */
              || ( u1t_prisel2 > u1t_pri ) )             /* 優先選択(優先度のMINセレクト) */
            {
                u1t_prisel2 = u1t_pri;  /* 優先度更新 */

                if ( ( u1t_prisel == u1g_EMINJ_PRINORQ )    /* 通常要求（旧構造体）に優先度要求なし */
                  || ( u1t_pri < u1t_prisel ) )             /* 通常要求（旧構造体）より高優先度要求あり */ /* 通常要求（旧構造体）より低優先度要求の場合は調停処理しない */
                {
                    u1t_prisel_fix = u1t_pri;                                   /* 優先度更新 */
                    u1t_prifix = u1t_pri;                                       /* 確定優先度更新 */
                    u1t_idsel = sts_eminj_eminjlmt_tbl2[u1t_did].u1_id;         /* 識別子更新 */
                    u4t_rqdat[1] = stt_minj_data2.u4_einjrq_dat;                /* 要求有識別子更新 */

                    vds_eminj_einj_datacopy2( ptt_datsel2, &stt_minj_data2 );
                    vds_eminj_einj_dataconv_rev( ptt_datsel, &stt_minj_data2 ); /* ここまでの新構造体情報を旧構造体に移植 */
                    u4t_rqdat[0] = ptt_datsel->u4_einjrq_dat;                   /* 要求有識別子更新 */
                }
            }
        }
    }

    u1s_eminj_epri2 = u1t_prisel2;                  /* 変更時はeminj_eminjlmt_hpri()もあわせて見直すこと */

    u1g_eminj_einjmedislid = u1t_idsel;
    u1s_eminj_eprisel_fix = u1t_prisel_fix;
    u1s_eminj_eprifix= u1t_prifix;
    u4s_eminj_erqdat[0] = u4t_rqdat[0];             /* 要求噴射方式要求有識別子格納 */
    u4s_eminj_erqdat[1] = u4t_rqdat[1];             /* 要求噴射方式要求有識別子格納 */

}

/*********************************************************************/
/*  関数名        | vds_eminj_einj_dataset( )                        */
/*  処理内容      | データ更新処理                                   */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_store     : 集約用構造体のアドレス           */
/*                | ptt_data      : 更新データのアドレス             */
/*                | u1t_xnercdfew : lsb=1 :NEタスク少判定フラグ      */
/*  戻り値        | なし                                             */
/*  注意事項      |                                                  */
/*********************************************************************/
static void
vds_eminj_einj_dataset( st_EMINJ_EINJ *ptt_store, const st_EMINJ_EINJ *ptt_data, u1 u1t_xnercdfew )
{
    u1 u1t_mox;    /* lsb=1 :メインセンサ数 */
    u1 u1t_nox_c;  /* lsb=1 :メインセンサ数 */
    u1 u1t_cyl;    /* lsb=1 :気筒数 */
    u1 u1t_ncyl_c; /* lsb=1 :気筒数 */

    u1t_ncyl_c = u1g_ejcc_NCYL;
    u1t_nox_c = u1g_ejcc_NOX;

    glint_di();       /* 同時性確保 開始 */
    ptt_store->u2_einjmod   = ptt_data->u2_einjmod;
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    ptt_store->s2_eainjp1   = ptt_data->s2_eainjp1;
    ptt_store->f4_eainjp1   = ptt_data->f4_eainjp1;
    ptt_store->s2_eainjp2   = ptt_data->s2_eainjp2;
    ptt_store->f4_eainjp2   = ptt_data->f4_eainjp2;
    ptt_store->s2_eainjp3   = ptt_data->s2_eainjp3;
    ptt_store->f4_eainjp3   = ptt_data->f4_eainjp3;
    ptt_store->s2_eainjp4   = ptt_data->s2_eainjp4;
    ptt_store->f4_eainjp4   = ptt_data->f4_eainjp4;
    ptt_store->s2_einjend   = ptt_data->s2_einjend;
    ptt_store->f4_einjend   = ptt_data->f4_einjend;
    f4g_eminj_einjend = ptt_data->f4_einjend;
    ptt_store->s2_eainjcutp = ptt_data->s2_eainjcutp;
    ptt_store->f4_eainjcutp = ptt_data->f4_eainjcutp;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_store->s2_eainjd1   = ptt_data->s2_eainjd1;
    ptt_store->f4_eainjd1   = ptt_data->f4_eainjd1;
    ptt_store->s2_eainjd2   = ptt_data->s2_eainjd2;
    ptt_store->f4_eainjd2   = ptt_data->f4_eainjd2;
    ptt_store->s2_eainjd3   = ptt_data->s2_eainjd3;
    ptt_store->f4_eainjd3   = ptt_data->f4_eainjd3;
    ptt_store->s2_eainjd4   = ptt_data->s2_eainjd4;
    ptt_store->f4_eainjd4   = ptt_data->f4_eainjd4;
    ptt_store->s2_eainjcutd = ptt_data->s2_eainjcutd;
    ptt_store->f4_eainjcutd = ptt_data->f4_eainjcutd;
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_PORT      /*【ﾎﾟｰﾄ】*/
    ptt_store->s2_eainjpadd = ptt_data->s2_eainjpadd;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_store->s2_eainjdadd = ptt_data->s2_eainjdadd;
#endif /* JEEFI */
    for ( u1t_cyl = (u1)0U; u1t_cyl < u1t_ncyl_c; u1t_cyl++ )
    {
        ptt_store->s4_eqfc[u1t_cyl] = ptt_data->s4_eqfc[u1t_cyl];
        ptt_store->f4_eqfc[u1t_cyl] = ptt_data->f4_eqfc[u1t_cyl];
        s4g_eminj_eqfc[u1t_cyl] = ptt_data->s4_eqfc[u1t_cyl];
        f4g_eminj_eqfc[u1t_cyl] = ptt_data->f4_eqfc[u1t_cyl];
    }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E                   /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    ptt_store->s4_eqinjexp  = ptt_data->s4_eqinjexp;
    ptt_store->f4_eqinjexp  = ptt_data->f4_eqinjexp;
#endif /* JECOMBCCPT_E */
    ptt_store->s2_ek1f      = ptt_data->s2_ek1f;
    ptt_store->f4_ek1f      = ptt_data->f4_ek1f;
    ptt_store->s2_ek2f      = ptt_data->s2_ek2f;
    ptt_store->f4_ek2f      = ptt_data->f4_ek2f;
    ptt_store->s2_ek3f      = ptt_data->s2_ek3f;
    ptt_store->f4_ek3f      = ptt_data->f4_ek3f;
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        ptt_store->s2_ek1fn[u1t_mox] = ptt_data->s2_ek1fn[u1t_mox];
        ptt_store->f4_ek1fn[u1t_mox] = ptt_data->f4_ek1fn[u1t_mox];
        s2g_eminj_ek1fn[u1t_mox] = ptt_data->s2_ek1fn[u1t_mox];
        f4g_eminj_ek1fn[u1t_mox] = ptt_data->f4_ek1fn[u1t_mox];
        ptt_store->s2_ek2fn[u1t_mox] = ptt_data->s2_ek2fn[u1t_mox];
        ptt_store->f4_ek2fn[u1t_mox] = ptt_data->f4_ek2fn[u1t_mox];
        s2g_eminj_ek2fn[u1t_mox] = ptt_data->s2_ek2fn[u1t_mox];
        f4g_eminj_ek2fn[u1t_mox] = ptt_data->f4_ek2fn[u1t_mox];
        ptt_store->s2_ek3fn[u1t_mox] = ptt_data->s2_ek3fn[u1t_mox];
        ptt_store->f4_ek3fn[u1t_mox] = ptt_data->f4_ek3fn[u1t_mox];
        s2g_eminj_ek3fn[u1t_mox] = ptt_data->s2_ek3fn[u1t_mox];
        f4g_eminj_ek3fn[u1t_mox] = ptt_data->f4_ek3fn[u1t_mox];
        ptt_store->s2_ekrchref[u1t_mox] = ptt_data->s2_ekrchref[u1t_mox];
        ptt_store->f4_ekrchref[u1t_mox] = ptt_data->f4_ekrchref[u1t_mox];
        s2g_eminj_ekrchref[u1t_mox] = ptt_data->s2_ekrchref[u1t_mox];
        f4g_eminj_ekrchref[u1t_mox] = ptt_data->f4_ekrchref[u1t_mox];
    }
    glbitcp_bibi( ptt_data->bi_exqinjast, ptt_store->bi_exqinjast );
    ptt_store->u1_exqinjast = ptt_data->u1_exqinjast;
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_store->u1_explreq = ptt_data->u1_explreq;
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
    ptt_store->s2_ekpfit = ptt_data->s2_ekpfit;
    ptt_store->f4_ekpfit = ptt_data->f4_ekpfit;
    s2g_eminj_ekpfit = ptt_data->s2_ekpfit;
 #if JEEGR == u1g_EJCC_USE      /*【EGR制御有】*/
    ptt_store->f4_ekpfiegr = ptt_data->f4_ekpfiegr;
 #endif /* JEEGR */
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        ptt_store->s2_ekpfitn[u1t_mox] = ptt_data->s2_ekpfitn[u1t_mox];
        ptt_store->f4_ekpfitn[u1t_mox] = ptt_data->f4_ekpfitn[u1t_mox];
        f4g_eminj_ekpfitn[u1t_mox] = ptt_data->f4_ekpfitn[u1t_mox];
        s2g_eminj_ekpfitn[u1t_mox] = ptt_data->s2_ekpfitn[u1t_mox];
 #if JEEGR == u1g_EJCC_USE      /*【EGR制御有】*/
        ptt_store->f4_ekpfiegrn[u1t_mox] = ptt_data->f4_ekpfiegrn[u1t_mox];
        f4g_eminj_ekpfiegrn[u1t_mox] = ptt_data->f4_ekpfiegrn[u1t_mox];
 #endif /* JEEGR */
    }
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    ptt_store->s2_ek1fpt = ptt_data->s2_ek1fpt;
    ptt_store->f4_ek1fpt = ptt_data->f4_ek1fpt;
#endif /* JEEFI */
    if ( u1t_xnercdfew == (u1)ON )                      /* NE同期タスクが少ない */
    {
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
        ptt_store->s4_eqinjstp1  = ptt_data->s4_eqinjstp1;
        ptt_store->f4_eqinjstp1  = ptt_data->f4_eqinjstp1;
        ptt_store->s4_eqinjstp2  = ptt_data->s4_eqinjstp2;
        ptt_store->f4_eqinjstp2  = ptt_data->f4_eqinjstp2;
        ptt_store->s4_eqinjstp3  = ptt_data->s4_eqinjstp3;
        ptt_store->f4_eqinjstp3  = ptt_data->f4_eqinjstp3;
        ptt_store->s4_eqinjstp4  = ptt_data->s4_eqinjstp4;
        ptt_store->f4_eqinjstp4  = ptt_data->f4_eqinjstp4;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        ptt_store->s4_eqinjstd1 = ptt_data->s4_eqinjstd1;
        ptt_store->f4_eqinjstd1 = ptt_data->f4_eqinjstd1;
        f4g_eminj_eqinjstd1 = ptt_data->f4_eqinjstd1;
        ptt_store->s4_eqinjstd2 = ptt_data->s4_eqinjstd2;
        ptt_store->f4_eqinjstd2 = ptt_data->f4_eqinjstd2;
        f4g_eminj_eqinjstd2 = ptt_data->f4_eqinjstd2;
        ptt_store->s4_eqinjstd3 = ptt_data->s4_eqinjstd3;
        ptt_store->f4_eqinjstd3 = ptt_data->f4_eqinjstd3;
        f4g_eminj_eqinjstd3 = ptt_data->f4_eqinjstd3;
        ptt_store->s4_eqinjstd4 = ptt_data->s4_eqinjstd4;
        ptt_store->f4_eqinjstd4 = ptt_data->f4_eqinjstd4;
        f4g_eminj_eqinjstd4 = ptt_data->f4_eqinjstd4;
#endif /* JEEFI */
    }
    glint_ei();     /* 同時性確保 終了 */
}

/*********************************************************************/
/*  関数名        | vds_eminj_einj_datacopy( )                       */
/*  処理内容      | 集約対象用構造体データコピー処理                 */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_data : 更新データのアドレス                  */
/*                | ptt_copy  : コピー元データのアドレス             */
/*  戻り値        | なし                                             */
/*  注意事項      |                                                  */
/*********************************************************************/
static void
vds_eminj_einj_datacopy( st_EMINJ_EMINJ_DEF *ptt_data, const st_EMINJ_EMINJ_DEF *ptt_copy )
{
    u1 u1t_mox;    /* lsb=1 :メインセンサ数 */
    u1 u1t_nox_c;  /* lsb=1 :メインセンサ数 */
    u1 u1t_cyl;    /* lsb=1 :気筒数 */
    u1 u1t_ncyl_c; /* lsb=1 :気筒数 */

    u1t_ncyl_c = u1g_ejcc_NCYL;
    u1t_nox_c = u1g_ejcc_NOX;

    ptt_data->u1_pri        = ptt_copy->u1_pri;
    ptt_data->u4_einjrq_dat = ptt_copy->u4_einjrq_dat;
    ptt_data->u2_einjmod    = ptt_copy->u2_einjmod;
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    ptt_data->s2_eainjp1    = ptt_copy->s2_eainjp1;
    ptt_data->s2_eainjp2    = ptt_copy->s2_eainjp2;
    ptt_data->s2_eainjp3    = ptt_copy->s2_eainjp3;
    ptt_data->s2_eainjp4    = ptt_copy->s2_eainjp4;
    ptt_data->s2_einjend    = ptt_copy->s2_einjend;
    ptt_data->s2_eainjcutp  = ptt_copy->s2_eainjcutp;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_data->s2_eainjd1    = ptt_copy->s2_eainjd1;
    ptt_data->s2_eainjd2    = ptt_copy->s2_eainjd2;
    ptt_data->s2_eainjd3    = ptt_copy->s2_eainjd3;
    ptt_data->s2_eainjd4    = ptt_copy->s2_eainjd4;
    ptt_data->s2_eainjcutd  = ptt_copy->s2_eainjcutd;
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    ptt_data->s4_eqinjstp1  = ptt_copy->s4_eqinjstp1;
    ptt_data->s4_eqinjstp2  = ptt_copy->s4_eqinjstp2;
    ptt_data->s4_eqinjstp3  = ptt_copy->s4_eqinjstp3;
    ptt_data->s4_eqinjstp4  = ptt_copy->s4_eqinjstp4;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_data->s4_eqinjstd1  = ptt_copy->s4_eqinjstd1;
    ptt_data->s4_eqinjstd2  = ptt_copy->s4_eqinjstd2;
    ptt_data->s4_eqinjstd3  = ptt_copy->s4_eqinjstd3;
    ptt_data->s4_eqinjstd4  = ptt_copy->s4_eqinjstd4;
#endif /* JEEFI */
    for ( u1t_cyl = (u1)0U; u1t_cyl < u1t_ncyl_c; u1t_cyl++ )
    {
        ptt_data->s4_eqfc[u1t_cyl] = ptt_copy->s4_eqfc[u1t_cyl];
    }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    ptt_data->s4_eqinjexp   = ptt_copy->s4_eqinjexp;
#endif /* JECOMBCCPT_E */
    ptt_data->s2_ek1f       = ptt_copy->s2_ek1f;
    ptt_data->s2_ek2f       = ptt_copy->s2_ek2f;
    ptt_data->s2_ek3f       = ptt_copy->s2_ek3f;
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        ptt_data->s2_ek1fn[u1t_mox] = ptt_copy->s2_ek1fn[u1t_mox];
        ptt_data->s2_ek2fn[u1t_mox] = ptt_copy->s2_ek2fn[u1t_mox];
        ptt_data->s2_ek3fn[u1t_mox] = ptt_copy->s2_ek3fn[u1t_mox];
        ptt_data->s2_ekrchref[u1t_mox]   = ptt_copy->s2_ekrchref[u1t_mox];
    }
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_data->s2_eprreq     = ptt_copy->s2_eprreq;
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_NOT_USE                      /*【可変燃圧制御無】*/
    ptt_data->s2_eqfreq     = ptt_copy->s2_eqfreq;
#else                           /*【可変燃圧制御有】*/
    ptt_data->s2_eprreql    = ptt_copy->s2_eprreql;
#endif /* JEPRDEMAND */
    glbitcp_bibi( ptt_copy->bi_exqinjast, ptt_data->bi_exqinjast );
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_data->u1_explreq    = ptt_copy->u1_explreq;
#endif /* JEEFI */
}

/*********************************************************************/
/*  関数名        | vds_eminj_eminj_dataset( )                       */
/*  処理内容      | データ更新処理                                   */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_store     : 集約用構造体のアドレス           */
/*                | ptt_data      : 更新データのアドレス             */
/*                | u1t_xnercdfew : lsb=1 :NEタスク少判定フラグ      */
/*  戻り値        | なし                                             */
/*  注意事項      | 新構造体用                                       */
/*********************************************************************/
static void
vds_eminj_eminj_dataset( st_EMINJ_EMINJ *ptt_store, const st_EMINJ_EMINJ *ptt_data, u1 u1t_xnercdfew )
{
    u1 u1t_mox;    /* lsb=1 :メインセンサ数 */
    u1 u1t_nox_c;  /* lsb=1 :メインセンサ数 */
    u1 u1t_cyl;    /* lsb=1 :気筒数 */
    u1 u1t_ncyl_c; /* lsb=1 :気筒数 */
    u1 u1t_injnum; /* lsb=1 :噴射回数 */

    u1t_ncyl_c = u1g_ejcc_NCYL;
    u1t_nox_c = u1g_ejcc_NOX;

    glint_di();       /* 同時性確保 開始 */
    ptt_store->u2_einjmod   = ptt_data->u2_einjmod;
    ptt_store->u4_einjptn   = ptt_data->u4_einjptn;
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)4U; u1t_injnum++ )
    {
        ptt_store->s2_eainjpn[u1t_injnum]   = ptt_data->s2_eainjpn[u1t_injnum];
        ptt_store->f4_eainjpn[u1t_injnum]   = ptt_data->f4_eainjpn[u1t_injnum];
        s2g_eminj_eainjpn[u1t_injnum] = ptt_data->s2_eainjpn[u1t_injnum];
        f4g_eminj_eainjpn[u1t_injnum] = ptt_data->f4_eainjpn[u1t_injnum];
    }
    ptt_store->s2_einjend   = ptt_data->s2_einjend;
    ptt_store->f4_einjend   = ptt_data->f4_einjend;
    ptt_store->s2_eainjcutp = ptt_data->s2_eainjcutp;
    ptt_store->f4_eainjcutp = ptt_data->f4_eainjcutp;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)6U; u1t_injnum++ )
    {
        ptt_store->s2_eainjdn[u1t_injnum]   = ptt_data->s2_eainjdn[u1t_injnum];
        ptt_store->f4_eainjdn[u1t_injnum]   = ptt_data->f4_eainjdn[u1t_injnum];
        s2g_eminj_eainjdn[u1t_injnum] = ptt_data->s2_eainjdn[u1t_injnum];
        f4g_eminj_eainjdn[u1t_injnum] = ptt_data->f4_eainjdn[u1t_injnum];
    }
    ptt_store->s2_eainjcutd = ptt_data->s2_eainjcutd;
    ptt_store->f4_eainjcutd = ptt_data->f4_eainjcutd;
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_PORT      /*【ﾎﾟｰﾄ】*/
    ptt_store->s2_eainjpadd = ptt_data->s2_eainjpadd;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_store->s2_eainjdadd = ptt_data->s2_eainjdadd;
#endif /* JEEFI */
    for ( u1t_cyl = (u1)0U; u1t_cyl < u1t_ncyl_c; u1t_cyl++ )
    {
        ptt_store->s4_eqfc[u1t_cyl] = ptt_data->s4_eqfc[u1t_cyl];
        ptt_store->f4_eqfc[u1t_cyl] = ptt_data->f4_eqfc[u1t_cyl];
    }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E                   /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    ptt_store->s4_eqinjexp  = ptt_data->s4_eqinjexp;
    ptt_store->f4_eqinjexp  = ptt_data->f4_eqinjexp;
#endif /* JECOMBCCPT_E */

    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        ptt_store->s2_ek1fn[u1t_mox] = ptt_data->s2_ek1fn[u1t_mox];
        ptt_store->f4_ek1fn[u1t_mox] = ptt_data->f4_ek1fn[u1t_mox];
        ptt_store->s2_ek2fn[u1t_mox] = ptt_data->s2_ek2fn[u1t_mox];
        ptt_store->f4_ek2fn[u1t_mox] = ptt_data->f4_ek2fn[u1t_mox];
        ptt_store->s2_ek3fn[u1t_mox] = ptt_data->s2_ek3fn[u1t_mox];
        ptt_store->f4_ek3fn[u1t_mox] = ptt_data->f4_ek3fn[u1t_mox];
        ptt_store->s2_ekrchref[u1t_mox] = ptt_data->s2_ekrchref[u1t_mox];
        ptt_store->f4_ekrchref[u1t_mox] = ptt_data->f4_ekrchref[u1t_mox];
    }
    glbitcp_bibi( ptt_data->bi_exqinjast, ptt_store->bi_exqinjast );
    ptt_store->u1_exqinjast = ptt_data->u1_exqinjast;
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_store->u1_explreq = ptt_data->u1_explreq;
#endif /* JEEFI */
#if JEEFI == u1g_EJCC_DUAL      /*【ﾃﾞｭｱﾙINJ】*/
    ptt_store->s2_ekpfit = ptt_data->s2_ekpfit;
    ptt_store->f4_ekpfit = ptt_data->f4_ekpfit;
 #if JEEGR == u1g_EJCC_USE      /*【EGR制御有】*/
    ptt_store->f4_ekpfiegr = ptt_data->f4_ekpfiegr;
 #endif /* JEEGR */
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        ptt_store->s2_ekpfitn[u1t_mox] = ptt_data->s2_ekpfitn[u1t_mox];
        ptt_store->f4_ekpfitn[u1t_mox] = ptt_data->f4_ekpfitn[u1t_mox];
 #if JEEGR == u1g_EJCC_USE      /*【EGR制御有】*/
        ptt_store->f4_ekpfiegrn[u1t_mox] = ptt_data->f4_ekpfiegrn[u1t_mox];
 #endif /* JEEGR */
    }
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    ptt_store->s2_ek1fpt = ptt_data->s2_ek1fpt;
    ptt_store->f4_ek1fpt = ptt_data->f4_ek1fpt;
#endif /* JEEFI */
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)8U; u1t_injnum++ )
    {
        ptt_store->s4_eqinjflfix[u1t_injnum] = ptt_data->s4_eqinjflfix[u1t_injnum];
        ptt_store->f4_eqinjflfix[u1t_injnum] = ptt_data->f4_eqinjflfix[u1t_injnum];
        s4g_eminj_eqinjflfix[u1t_injnum] = ptt_data->s4_eqinjflfix[u1t_injnum];
        f4g_eminj_eqinjflfix[u1t_injnum] = ptt_data->f4_eqinjflfix[u1t_injnum];
        ptt_store->s4_eqinjplfix[u1t_injnum] = ptt_data->s4_eqinjplfix[u1t_injnum];
        ptt_store->f4_eqinjplfix[u1t_injnum] = ptt_data->f4_eqinjplfix[u1t_injnum];
        s4g_eminj_eqinjplfix[u1t_injnum] = ptt_data->s4_eqinjplfix[u1t_injnum];
        f4g_eminj_eqinjplfix[u1t_injnum] = ptt_data->f4_eqinjplfix[u1t_injnum];
    }

    if ( u1t_xnercdfew == (u1)ON )                      /* NE同期タスクが少ない */
    {
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
        for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)4U; u1t_injnum++ )
        {
            ptt_store->s4_eqinjstpn[u1t_injnum]  = ptt_data->s4_eqinjstpn[u1t_injnum];
            ptt_store->f4_eqinjstpn[u1t_injnum]  = ptt_data->f4_eqinjstpn[u1t_injnum];
            s4g_eminj_eqinjstpn[u1t_injnum] = ptt_data->s4_eqinjstpn[u1t_injnum];
            f4g_eminj_eqinjstpn[u1t_injnum] = ptt_data->f4_eqinjstpn[u1t_injnum];
        }
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)6U; u1t_injnum++ )
        {
            ptt_store->s4_eqinjstdn[u1t_injnum] = ptt_data->s4_eqinjstdn[u1t_injnum];
            ptt_store->f4_eqinjstdn[u1t_injnum] = ptt_data->f4_eqinjstdn[u1t_injnum];
            s4g_eminj_eqinjstdn[u1t_injnum] = ptt_data->s4_eqinjstdn[u1t_injnum];
            f4g_eminj_eqinjstdn[u1t_injnum] = ptt_data->f4_eqinjstdn[u1t_injnum];
        }
#endif /* JEEFI */
    }
    glint_ei();     /* 同時性確保 終了 */
}

/*********************************************************************/
/*  関数名        | vds_eminj_einj_datacopy2( )                      */
/*  処理内容      | 集約対象用新構造体データコピー処理               */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_data : 更新データのアドレス                  */
/*                | ptt_copy  : コピー元データのアドレス             */
/*  戻り値        | なし                                             */
/*  注意事項      |                                                  */
/*********************************************************************/
static void
vds_eminj_einj_datacopy2( st_EMINJ_EMINJ_BUF *ptt_data, const st_EMINJ_EMINJ_BUF *ptt_copy )
{
    u1 u1t_mox;    /* lsb=1 :メインセンサ数 */
    u1 u1t_nox_c;  /* lsb=1 :メインセンサ数 */
    u1 u1t_cyl;    /* lsb=1 :気筒数 */
    u1 u1t_ncyl_c; /* lsb=1 :気筒数 */
    u1 u1t_injnum; /* lsb=1 :噴射回数 */

    u1t_ncyl_c = u1g_ejcc_NCYL;
    u1t_nox_c = u1g_ejcc_NOX;

    ptt_data->u1_pri        = ptt_copy->u1_pri;
    ptt_data->u4_einjrq_dat = ptt_copy->u4_einjrq_dat;
    ptt_data->u2_einjmod    = ptt_copy->u2_einjmod;
    ptt_data->u4_einjptn    = ptt_copy->u4_einjptn;
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)4U; u1t_injnum++ )
    {
        ptt_data->s2_eainjpn[u1t_injnum] = ptt_copy->s2_eainjpn[u1t_injnum];
    }
    ptt_data->s2_einjend    = ptt_copy->s2_einjend;
    ptt_data->s2_eainjcutp  = ptt_copy->s2_eainjcutp;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)6U; u1t_injnum++ )
    {
        ptt_data->s2_eainjdn[u1t_injnum] = ptt_copy->s2_eainjdn[u1t_injnum];
    }
    ptt_data->s2_eainjcutd  = ptt_copy->s2_eainjcutd;
#endif /* JEEFI */
    if ( u1s_eminj_exnercdfew == (u1)ON )               /* NE同期タスクが少ない */
    {
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
        for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)4U; u1t_injnum++ )
        {
            ptt_data->s4_eqinjstpn[u1t_injnum] = ptt_copy->s4_eqinjstpn[u1t_injnum];
        }
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)6U; u1t_injnum++ )
        {
            ptt_data->s4_eqinjstdn[u1t_injnum] = ptt_copy->s4_eqinjstdn[u1t_injnum];
        }
#endif /* JEEFI */
    }
    for ( u1t_cyl = (u1)0U; u1t_cyl < u1t_ncyl_c; u1t_cyl++ )
    {
        ptt_data->s4_eqfc[u1t_cyl] = ptt_copy->s4_eqfc[u1t_cyl];
    }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    ptt_data->s4_eqinjexp   = ptt_copy->s4_eqinjexp;
#endif /* JECOMBCCPT_E */
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        ptt_data->s2_ek1fn[u1t_mox] = ptt_copy->s2_ek1fn[u1t_mox];
        ptt_data->s2_ek2fn[u1t_mox] = ptt_copy->s2_ek2fn[u1t_mox];
        ptt_data->s2_ek3fn[u1t_mox] = ptt_copy->s2_ek3fn[u1t_mox];
        ptt_data->s2_ekrchref[u1t_mox]   = ptt_copy->s2_ekrchref[u1t_mox];
    }
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_data->s2_eprreq     = ptt_copy->s2_eprreq;
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_NOT_USE                      /*【可変燃圧制御無】*/
    ptt_data->s2_eqfreq     = ptt_copy->s2_eqfreq;
#else                           /*【可変燃圧制御有】*/
    ptt_data->s2_eprreql    = ptt_copy->s2_eprreql;
#endif /* JEPRDEMAND */
    glbitcp_bibi( ptt_copy->bi_exqinjast, ptt_data->bi_exqinjast );
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_data->u1_explreq    = ptt_copy->u1_explreq;
#endif /* JEEFI */
    for ( u1t_injnum = (u1)0U; u1t_injnum < (u1)8U; u1t_injnum++ )
    {
        ptt_data->s4_eqinjflfix[u1t_injnum]  = ptt_copy->s4_eqinjflfix[u1t_injnum];
        ptt_data->s4_eqinjplfix[u1t_injnum]  = ptt_copy->s4_eqinjplfix[u1t_injnum];
    }

}

/*********************************************************************/
/*  関数名        | vds_eminj_einj_dataconv( )                       */
/*  処理内容      | 集約対象用旧→新構造体データ移行処理             */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_data_new  : 新構造体データのアドレス         */
/*                | ptt_data_old  : 旧構造体データのアドレス         */
/*  戻り値        | なし                                             */
/*  注意事項      |                                                  */
/*********************************************************************/
static void
vds_eminj_einj_dataconv( st_EMINJ_EMINJ_BUF *ptt_data_new, const st_EMINJ_EMINJ_DEF *ptt_data_old )
{
    u1 u1t_mox;    /* lsb=1 :メインセンサ数 */
    u1 u1t_nox_c;  /* lsb=1 :メインセンサ数 */
    u1 u1t_cyl;    /* lsb=1 :気筒数 */
    u1 u1t_ncyl_c; /* lsb=1 :気筒数 */
    u4 u4t_rqdat;  /* lsb=1 :要求指示データ */

    u1t_ncyl_c = u1g_ejcc_NCYL;
    u1t_nox_c = u1g_ejcc_NOX;

    ptt_data_new->u1_pri        = ptt_data_old->u1_pri;

    u4t_rqdat = u4s_EMINJ_NORQDAT;
    if ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQINJMODE ) != (u4)0U )      /* 噴射ﾓｰﾄﾞ要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQINJMODE );
    }
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    if ( ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQAINJP )  != (u4)0U )     /* ﾎﾟｰﾄ噴射開始時期要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQAINJP1 ) != (u4)0U )     /* ﾎﾟｰﾄ1回目噴射開始時期要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQAINJP2 ) != (u4)0U )     /* ﾎﾟｰﾄ2回目噴射開始時期要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQAINJP3 ) != (u4)0U )     /* ﾎﾟｰﾄ3回目噴射開始時期要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQAINJP4 ) != (u4)0U ) )   /* ﾎﾟｰﾄ4回目噴射開始時期要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJPN );
    }
    if ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQINJEND ) != (u4)0U )       /* ﾎﾟｰﾄ噴射終了時期要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQINJEND );
    }
    if ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQAINJCUTP ) != (u4)0U )     /* ﾎﾟｰﾄ噴射強制ｶｯﾄ時期要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJCUTP );
    }
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    if ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQAINJCUTD ) != (u4)0U )     /* 筒内噴射強制ｶｯﾄ時期要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJCUTD );
    }
    if ( ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQAINJD1 ) != (u4)0U )     /* 筒内1回目噴射開始時期要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQAINJD2 ) != (u4)0U )     /* 筒内2回目噴射開始時期要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQAINJD3 ) != (u4)0U )     /* 筒内3回目噴射開始時期要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQAINJD4 ) != (u4)0U ) )   /* 筒内4回目噴射開始時期要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJDN );
    }
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    if ( ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQQINJSTP )  != (u4)0U )   /* ﾎﾟｰﾄ始動時噴射量要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQQINJSTP1 ) != (u4)0U )   /* ﾎﾟｰﾄ1回目始動時噴射量要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQQINJSTP2 ) != (u4)0U )   /* ﾎﾟｰﾄ2回目始動時噴射量要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQQINJSTP3 ) != (u4)0U )   /* ﾎﾟｰﾄ3回目始動時噴射量要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQQINJSTP4 ) != (u4)0U ) ) /* ﾎﾟｰﾄ4回目始動時噴射量要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQINJSTPN );
    }
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    if ( ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQQINJSTD1 ) != (u4)0U )   /* 筒内1回目始動時噴射量要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQQINJSTD2 ) != (u4)0U )   /* 筒内2回目始動時噴射量要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQQINJSTD3 ) != (u4)0U )   /* 筒内3回目始動時噴射量要求有 */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQQINJSTD4 ) != (u4)0U ) ) /* 筒内4回目始動時噴射量要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQINJSTDN );
    }
#endif /* JEEFI */
    if ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQQFC ) != (u4)0U )          /* FC中噴射量要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQFC );
    }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E                   /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    if ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQQINJEXP ) != (u4)0U )      /* 膨張行程噴射量要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQINJEXP );
    }
#endif /* JECOMBCCPT_E */
    if ( ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQK1FN ) != (u4)0U )       /* 1回目噴射量算出係数要求有(ﾊﾞﾝｸ別) */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQK1F )  != (u4)0U ) )     /* 1回目噴射量算出係数要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQK1FN );
    }
    if ( ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQK2FN ) != (u4)0U )       /* 2回目噴射量算出係数要求有(ﾊﾞﾝｸ別) */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQK2F )  != (u4)0U ) )     /* 2回目噴射量算出係数要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQK2FN );
    }
    if ( ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQK3FN ) != (u4)0U )       /* 3回目噴射量算出係数要求有(ﾊﾞﾝｸ別) */
      || ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQK3F )  != (u4)0U ) )     /* 3回目噴射量算出係数要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQK3FN );
    }
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    if ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQPRREQ ) != (u4)0U )        /* 高圧ﾎﾟﾝﾌﾟ目標燃圧要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQPRREQ );
    }
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_NOT_USE                      /*【可変燃圧制御無】*/
    if ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQQFREQ ) != (u4)0U )        /* 燃料ﾎﾟﾝﾌﾟ吐出量要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQFREQ );
    }
#else                                                   /*【可変燃圧制御有】*/
    if ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQPRREQL ) != (u4)0U )       /* 低圧ﾎﾟﾝﾌﾟ目標燃圧要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQPRREQL );
    }
#endif /* JEPRDEMAND */
    if ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQXQINJAST ) != (u4)0U )     /* 始動後噴射量要求ﾌﾗｸﾞ要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQXQINJAST );
    }
    if ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQKRCHREF ) != (u4)0U )      /* 噴射量補正係数要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQKRCHREF );
    }
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    if ( ( ptt_data_old->u4_einjrq_dat & u4g_EMINJ_RQPLREQ ) != (u4)0U )        /* PL噴射実施要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQPLREQ );
    }
#endif /* JEEFI */

    ptt_data_new->u4_einjrq_dat = u4t_rqdat;

    ptt_data_new->u2_einjmod    = ptt_data_old->u2_einjmod;
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    ptt_data_new->s2_eainjpn[0] = ptt_data_old->s2_eainjp1;
    ptt_data_new->s2_eainjpn[1] = ptt_data_old->s2_eainjp2;
    ptt_data_new->s2_eainjpn[2] = ptt_data_old->s2_eainjp3;
    ptt_data_new->s2_eainjpn[3] = ptt_data_old->s2_eainjp4;
    ptt_data_new->s2_einjend    = ptt_data_old->s2_einjend;
    ptt_data_new->s2_eainjcutp  = ptt_data_old->s2_eainjcutp;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_data_new->s2_eainjdn[0] = ptt_data_old->s2_eainjd1;
    ptt_data_new->s2_eainjdn[1] = ptt_data_old->s2_eainjd2;
    ptt_data_new->s2_eainjdn[2] = ptt_data_old->s2_eainjd3;
    ptt_data_new->s2_eainjdn[3] = ptt_data_old->s2_eainjd4;
    ptt_data_new->s2_eainjcutd  = ptt_data_old->s2_eainjcutd;
#endif /* JEEFI */
    if ( u1s_eminj_exnercdfew == (u1)ON )               /* NE同期タスクが少ない */
    {
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
        ptt_data_new->s4_eqinjstpn[0] = ptt_data_old->s4_eqinjstp1;
        ptt_data_new->s4_eqinjstpn[1] = ptt_data_old->s4_eqinjstp2;
        ptt_data_new->s4_eqinjstpn[2] = ptt_data_old->s4_eqinjstp3;
        ptt_data_new->s4_eqinjstpn[3] = ptt_data_old->s4_eqinjstp4;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        ptt_data_new->s4_eqinjstdn[0] = ptt_data_old->s4_eqinjstd1;
        ptt_data_new->s4_eqinjstdn[1] = ptt_data_old->s4_eqinjstd2;
        ptt_data_new->s4_eqinjstdn[2] = ptt_data_old->s4_eqinjstd3;
        ptt_data_new->s4_eqinjstdn[3] = ptt_data_old->s4_eqinjstd4;
#endif /* JEEFI */
    }
    for ( u1t_cyl = (u1)0U; u1t_cyl < u1t_ncyl_c; u1t_cyl++ )
    {
        ptt_data_new->s4_eqfc[u1t_cyl] = ptt_data_old->s4_eqfc[u1t_cyl];
    }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    ptt_data_new->s4_eqinjexp   = ptt_data_old->s4_eqinjexp;
#endif /* JECOMBCCPT_E */
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        ptt_data_new->s2_ek1fn[u1t_mox] = ptt_data_old->s2_ek1fn[u1t_mox];
        ptt_data_new->s2_ek2fn[u1t_mox] = ptt_data_old->s2_ek2fn[u1t_mox];
        ptt_data_new->s2_ek3fn[u1t_mox] = ptt_data_old->s2_ek3fn[u1t_mox];
        ptt_data_new->s2_ekrchref[u1t_mox]   = ptt_data_old->s2_ekrchref[u1t_mox];
    }
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_data_new->s2_eprreq     = ptt_data_old->s2_eprreq;
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_NOT_USE                      /*【可変燃圧制御無】*/
    ptt_data_new->s2_eqfreq     = ptt_data_old->s2_eqfreq;
#else                           /*【可変燃圧制御有】*/
    ptt_data_new->s2_eprreql    = ptt_data_old->s2_eprreql;
#endif /* JEPRDEMAND */
    glbitcp_bibi( ptt_data_old->bi_exqinjast, ptt_data_new->bi_exqinjast );
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_data_new->u1_explreq    = ptt_data_old->u1_explreq;
#endif /* JEEFI */
}

/**********************************************************************/
/*  関数名        | vds_eminj_einj_dataconv_rev( )                    */
/*  処理内容      | 集約対象用新→旧構造体データ移行処理              */
/*  制御タイミング| 処理要求時                                        */
/*  引数          | ptt_data_old  : 旧構造体データのアドレス          */
/*                | ptt_data_new  : 新構造体データのアドレス          */
/*  戻り値        | なし                                              */
/*  注意事項      | 新構造体でのみ新たに存在するメンバ(u4_einjptn     */
/*                | ,s4_eqinjflfix[],s4_eqinjplfix[]                  */
/*                | ,s2_eainjdn[4],s2_eainjdn[5]                      */
/*                | ,s4_eqinjstdn[4],s4_eqinjstdn[5])は移行していない */
/**********************************************************************/
static void
vds_eminj_einj_dataconv_rev( st_EMINJ_EMINJ_DEF *ptt_data_old, const st_EMINJ_EMINJ_BUF *ptt_data_new )
{
    u1 u1t_mox;    /* lsb=1 :メインセンサ数 */
    u1 u1t_nox_c;  /* lsb=1 :メインセンサ数 */
    u1 u1t_cyl;    /* lsb=1 :気筒数 */
    u1 u1t_ncyl_c; /* lsb=1 :気筒数 */
    u4 u4t_rqdat;  /* lsb=1 :要求指示データ */

    u1t_ncyl_c = u1g_ejcc_NCYL;
    u1t_nox_c = u1g_ejcc_NOX;

    ptt_data_old->u1_pri        = ptt_data_new->u1_pri;

    u4t_rqdat = u4s_EMINJ_NORQDAT;
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQINJMODE ) != (u4)0U )      /* 噴射ﾓｰﾄﾞ要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQINJMODE );
    }
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQAINJPN ) != (u4)0U )       /* ﾎﾟｰﾄn回目噴射開始時期要求有 */
    {
        if ( ptt_data_new->s2_eainjpn[0]  != s2s_EMINJ_AINJP_VD )               /* ﾎﾟｰﾄ1回目噴射開始時期要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJP1 );
        }
        if ( ptt_data_new->s2_eainjpn[1]  != s2s_EMINJ_AINJP_VD )               /* ﾎﾟｰﾄ2回目噴射開始時期要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJP2 );
        }
        if ( ptt_data_new->s2_eainjpn[2]  != s2s_EMINJ_AINJP_VD )               /* ﾎﾟｰﾄ3回目噴射開始時期要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJP3 );
        }
        if ( ptt_data_new->s2_eainjpn[3]  != s2s_EMINJ_AINJP_VD )               /* ﾎﾟｰﾄ4回目噴射開始時期要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJP4 );
        }
    }
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQINJEND ) != (u4)0U )       /* ﾎﾟｰﾄ噴射終了時期要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQINJEND );
    }
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQAINJCUTP ) != (u4)0U )     /* ﾎﾟｰﾄ噴射強制ｶｯﾄ時期要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJCUTP );
    }
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQAINJCUTD ) != (u4)0U )     /* 筒内噴射強制ｶｯﾄ時期要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJCUTD );
    }
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQAINJDN ) != (u4)0U )       /* 筒内n回目噴射開始時期要求有 */
    {
        if ( ptt_data_new->s2_eainjdn[0]  != s2s_EMINJ_AINJD_VD )               /* 筒内1回目噴射開始時期要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJD1 );
        }
        if ( ptt_data_new->s2_eainjdn[1]  != s2s_EMINJ_AINJD_VD )               /* 筒内2回目噴射開始時期要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJD2 );
        }
        if ( ptt_data_new->s2_eainjdn[2]  != s2s_EMINJ_AINJD_VD )               /* 筒内3回目噴射開始時期要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJD3 );
        }
        if ( ptt_data_new->s2_eainjdn[3]  != s2s_EMINJ_AINJD_VD )               /* 筒内4回目噴射開始時期要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQAINJD4 );
        }
    }
#endif /* JEEFI */
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQQINJSTPN ) != (u4)0U )     /* ﾎﾟｰﾄn回目噴射開始時期要求有 */
    {
        if ( ptt_data_new->s4_eqinjstpn[0]  != s4s_EMINJ_QINJ_VD )              /* ﾎﾟｰﾄ1回目始動時噴射量要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQINJSTP1 );
        }
        if ( ptt_data_new->s4_eqinjstpn[1]  != s4s_EMINJ_QINJ_VD )              /* ﾎﾟｰﾄ2回目始動時噴射量要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQINJSTP2 );
        }
        if ( ptt_data_new->s4_eqinjstpn[2]  != s4s_EMINJ_QINJ_VD )              /* ﾎﾟｰﾄ3回目始動時噴射量要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQINJSTP3 );
        }
        if ( ptt_data_new->s4_eqinjstpn[3]  != s4s_EMINJ_QINJ_VD )              /* ﾎﾟｰﾄ4回目始動時噴射量要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQINJSTP4 );
        }
    }
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQQINJSTDN ) != (u4)0U )     /* 筒内n回目噴射開始時期要求有 */
    {
        if ( ptt_data_new->s4_eqinjstdn[0]  != s4s_EMINJ_QINJ_VD )              /* 筒内1回目始動時噴射量要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQINJSTD1 );
        }
        if ( ptt_data_new->s4_eqinjstdn[1]  != s4s_EMINJ_QINJ_VD )              /* 筒内2回目始動時噴射量要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQINJSTD2 );
        }
        if ( ptt_data_new->s4_eqinjstdn[2]  != s4s_EMINJ_QINJ_VD )              /* 筒内3回目始動時噴射量要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQINJSTD3 );
        }
        if ( ptt_data_new->s4_eqinjstdn[3]  != s4s_EMINJ_QINJ_VD )              /* 筒内4回目始動時噴射量要求有 */
        {
            u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQINJSTD4 );
        }
    }
#endif /* JEEFI */
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQQFC ) != (u4)0U )          /* FC中噴射量要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQFC );
    }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E                   /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQQINJEXP ) != (u4)0U )      /* 膨張行程噴射量要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQINJEXP );
    }
#endif /* JECOMBCCPT_E */
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQK1FN ) != (u4)0U )         /* 1回目噴射量算出係数要求有(ﾊﾞﾝｸ別) */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQK1FN );
    }
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQK2FN ) != (u4)0U )         /* 2回目噴射量算出係数要求有(ﾊﾞﾝｸ別) */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQK2FN );
    }
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQK3FN ) != (u4)0U )         /* 3回目噴射量算出係数要求有(ﾊﾞﾝｸ別) */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQK3FN );
    }
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQPRREQ ) != (u4)0U )        /* 高圧ﾎﾟﾝﾌﾟ目標燃圧要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQPRREQ );
    }
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_NOT_USE                      /*【可変燃圧制御無】*/
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQQFREQ ) != (u4)0U )        /* 燃料ﾎﾟﾝﾌﾟ吐出量要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQQFREQ );
    }
#else                                                   /*【可変燃圧制御有】*/
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQPRREQL ) != (u4)0U )       /* 低圧ﾎﾟﾝﾌﾟ目標燃圧要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQPRREQL );
    }
#endif /* JEPRDEMAND */
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQXQINJAST ) != (u4)0U )     /* 始動後噴射量要求ﾌﾗｸﾞ要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQXQINJAST );
    }
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQKRCHREF ) != (u4)0U )      /* 噴射量補正係数要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQKRCHREF );
    }
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    if ( ( ptt_data_new->u4_einjrq_dat & u4g_EMINJ_RQPLREQ ) != (u4)0U )        /* PL噴射実施要求有 */
    {
        u4t_rqdat = ( u4t_rqdat | u4g_EMINJ_RQPLREQ );
    }
#endif /* JEEFI */
    ptt_data_old->u4_einjrq_dat = u4t_rqdat;

    ptt_data_old->u2_einjmod    = ptt_data_new->u2_einjmod;
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
    ptt_data_old->s2_eainjp1 = ptt_data_new->s2_eainjpn[0];
    ptt_data_old->s2_eainjp2 = ptt_data_new->s2_eainjpn[1];
    ptt_data_old->s2_eainjp3 = ptt_data_new->s2_eainjpn[2];
    ptt_data_old->s2_eainjp4 = ptt_data_new->s2_eainjpn[3];
    ptt_data_old->s2_einjend = ptt_data_new->s2_einjend;
    ptt_data_old->s2_eainjcutp = ptt_data_new->s2_eainjcutp;
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_data_old->s2_eainjd1 = ptt_data_new->s2_eainjdn[0];
    ptt_data_old->s2_eainjd2 = ptt_data_new->s2_eainjdn[1];
    ptt_data_old->s2_eainjd3 = ptt_data_new->s2_eainjdn[2];
    ptt_data_old->s2_eainjd4 = ptt_data_new->s2_eainjdn[3];
    ptt_data_old->s2_eainjcutd = ptt_data_new->s2_eainjcutd;
#endif /* JEEFI */
    if ( u1s_eminj_exnercdfew == (u1)ON )               /* NE同期タスクが少ない */
    {
#if JEEFI != u1g_EJCC_D4        /*【D-4以外】*/
        ptt_data_old->s4_eqinjstp1 = ptt_data_new->s4_eqinjstpn[0];
        ptt_data_old->s4_eqinjstp2 = ptt_data_new->s4_eqinjstpn[1];
        ptt_data_old->s4_eqinjstp3 = ptt_data_new->s4_eqinjstpn[2];
        ptt_data_old->s4_eqinjstp4 = ptt_data_new->s4_eqinjstpn[3];
#endif /* JEEFI */
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
        ptt_data_old->s4_eqinjstd1 = ptt_data_new->s4_eqinjstdn[0];
        ptt_data_old->s4_eqinjstd2 = ptt_data_new->s4_eqinjstdn[1];
        ptt_data_old->s4_eqinjstd3 = ptt_data_new->s4_eqinjstdn[2];
        ptt_data_old->s4_eqinjstd4 = ptt_data_new->s4_eqinjstdn[3];
#endif /* JEEFI */
    }
    for ( u1t_cyl = (u1)0U; u1t_cyl < u1t_ncyl_c; u1t_cyl++ )
    {
        ptt_data_old->s4_eqfc[u1t_cyl] = ptt_data_new->s4_eqfc[u1t_cyl];
    }
#if JECOMBCCPT_E == u1g_EJCC_SPRAYG_E /*【ｽﾌﾟﾚｰｶﾞｲﾄﾞ】*/
    ptt_data_old->s4_eqinjexp   = ptt_data_new->s4_eqinjexp;
#endif /* JECOMBCCPT_E */
    for ( u1t_mox = (u1)0U; u1t_mox < u1t_nox_c; u1t_mox++ )
    {
        ptt_data_old->s2_ek1fn[u1t_mox] = ptt_data_new->s2_ek1fn[u1t_mox];
        ptt_data_old->s2_ek2fn[u1t_mox] = ptt_data_new->s2_ek2fn[u1t_mox];
        ptt_data_old->s2_ek3fn[u1t_mox] = ptt_data_new->s2_ek3fn[u1t_mox];
        ptt_data_old->s2_ekrchref[u1t_mox] = ptt_data_new->s2_ekrchref[u1t_mox];
    }
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_data_old->s2_eprreq     = ptt_data_new->s2_eprreq;
#endif /* JEEFI */
#if JEPRDEMAND == u1g_EJCC_NOT_USE                      /*【可変燃圧制御無】*/
    ptt_data_old->s2_eqfreq     = ptt_data_new->s2_eqfreq;
#else                           /*【可変燃圧制御有】*/
    ptt_data_old->s2_eprreql    = ptt_data_new->s2_eprreql;
#endif /* JEPRDEMAND */
    glbitcp_bibi( ptt_data_new->bi_exqinjast, ptt_data_old->bi_exqinjast );
#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)  /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
    ptt_data_old->u1_explreq    = ptt_data_new->u1_explreq;
#endif /* JEEFI */
}

#if (JEEFI == u1g_EJCC_DUAL) || (JEEFI == u1g_EJCC_D4)              /*【ﾃﾞｭｱﾙINJ】OR【D-4】*/
/*********************************************************************/
/*  関数名        | vds_eminj_erestahot_rap_dataget( )               */
/*  処理内容      | 高温再始動制御ﾃﾞｰﾀ取得処理(ラッパー関数)         */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_store :優先選択調停ﾊﾞｯﾌｧのｱﾄﾞﾚｽ              */
/*  戻り値        | なし                                             */
/*  注意事項      |【ﾃﾞｭｱﾙINJ】OR【D-4】                             */
/*********************************************************************/
static void
vds_eminj_erestahot_rap_dataget( st_EMINJ_EMINJ_DEF *ptt_store )
{
    vds_eminj_einj_datacopy( ptt_store, &sts_eminj_erestahot_data );        /* 下記理由よりs2_eainjp、s4_eqinjstpの更新を省略 */
                                                                            /* erestahotは初版からs2_eainjp、s4_eqinjstpを使用しておらず、 */
                                                                            /* 廃止予定のメンバなので今後も使用されないため */
}
#endif /* JEEFI */

#if (JEALLHV_E == u1g_EJCC_ALLHV_E) && (JEEFI != u1g_EJCC_D4)       /*【ALL HV】AND【D-4以外】*/
/*********************************************************************/
/*  関数名        | vds_eminj_erdpn_rap_dataget( )                   */
/*  処理内容      | PN低減制御ﾃﾞｰﾀ取得処理(ラッパー関数)             */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_store :優先選択調停ﾊﾞｯﾌｧのｱﾄﾞﾚｽ              */
/*  戻り値        | なし                                             */
/*  注意事項      | 【ALL HV】AND【D-4以外】                         */
/*********************************************************************/
static void
vds_eminj_erdpn_rap_dataget( st_EMINJ_EMINJ_DEF *ptt_store )
{
    vds_eminj_einj_datacopy( ptt_store, &sts_eminj_erdpn_data );            /* 下記理由よりs2_eainjp、s4_eqinjstpの更新を省略 */
                                                                            /* erdpnは初版からs2_eainjp、s4_eqinjstpを使用しておらず、 */
                                                                            /* 廃止予定のメンバなので今後も使用されないため */
}
#endif /* JEALLHV_E,JEEFI */

/*********************************************************************/
/*  関数名        | vds_eminj_dummy_emedi_dataget( )                 */
/*  処理内容      | ダミー関数                                       */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_store :優先選択調停ﾊﾞｯﾌｧのｱﾄﾞﾚｽ              */
/*  戻り値        | なし                                             */
/*  注意事項      |                                                  */
/*********************************************************************/
static void
vds_eminj_dummy_emedi_dataget( st_EMINJ_EMINJ_DEF *ptt_store )
{
    /* ダミーのため処理なし */
}

/*********************************************************************/
/*  関数名        | vds_eminj_dummy_emedi_dataget2( )                */
/*  処理内容      | ダミー関数                                       */
/*  制御タイミング| 処理要求時                                       */
/*  引数          | ptt_store :優先選択調停ﾊﾞｯﾌｧのｱﾄﾞﾚｽ              */
/*  戻り値        | なし                                             */
/*  注意事項      |                                                  */
/*********************************************************************/
static void
vds_eminj_dummy_emedi_dataget2( st_EMINJ_EMINJ_BUF *ptt_store )
{
    /* ダミーのため処理なし */
}

/**** End of File ****************************************************/
