#define MMU_VARDECL( type, var ) type _enc_##var[ size ];

typedef struct
{
	EncState   _local_st;

	spx_coef_t	 _lpc[ NB_LPC_SIZE ];
	spx_coef_t	 _bw_lpc1[ NB_LPC_SIZE ];
	spx_coef_t	 _bw_lpc2[ NB_LPC_SIZE ];
	spx_lsp_t	 _lsp[ NB_LPC_SIZE ];
	spx_lsp_t	 _qlsp[ NB_LPC_SIZE ];
	spx_lsp_t	 _interp_lsp[ NB_LPC_SIZE ];
	spx_lsp_t	 _interp_qlsp[ NB_LPC_SIZE ];
	spx_coef_t	 _interp_lpc[ NB_LPC_SIZE ];
	spx_coef_t	 _interp_qlpc[ NB_LPC_SIZE ];
	spx_mem_t	 _mem[ NB_LPC_SIZE ];

	spx_word16_t _w_sig[ NB_FRAME_SIZE + NB_SUBFRAME_SIZE ];

	spx_word16_t _autocorr[ NB_LPC_SIZE + 1 ];

	spx_sig_t    _innov[ NB_SUBFRAME_SIZE ];
	spx_sig_t    _innov2[ NB_SUBFRAME_SIZE ];

	spx_word16_t _target[ NB_SUBFRAME_SIZE ];
	spx_word16_t _ringing[ NB_SUBFRAME_SIZE ];
    spx_word16_t _syn_resp[ NB_SUBFRAME_SIZE ];
    spx_word16_t _real_exc[ NB_SUBFRAME_SIZE ];
    spx_word32_t _exc32[ NB_SUBFRAME_SIZE ];

} tEncodeMMU;


tEncodeMMU enc_mmu;

// enc_mmu._