/* for version < 1.0.0 */

#if !defined(MPC_RND)
#define MPC_RND RNDC
#endif

/* word size */

#define WSIZE_32_C (WSIZE_32_FR * 2)
#define WSIZE_64_C (WSIZE_64_FR * 2)

/* conversions */

static inline mpc_ptr C_val(value x)
{
	return Data_custom_val(x);
}

static inline void c_check_fr_rnd(mpfr_rnd_t rnd)
{
	switch(rnd){
	case MPFR_RNDN:
	case MPFR_RNDZ:
	case MPFR_RNDU:
	case MPFR_RNDD:
		break;
	case MPFR_RNDA:
#if MPC_VERSION >= 0x010300
		break;
#endif
	case MPFR_RNDF:
	case MPFR_RNDNA:
	default:
		caml_failwith(__FUNCTION__);
	}
}

static inline mpc_rnd_t Crnd_val(value x)
{
	mpfr_rnd_t real_rnd = Rnd_val(Field(x, 0));
	mpfr_rnd_t imag_rnd = Rnd_val(Field(x, 1));
	c_check_fr_rnd(real_rnd);
	c_check_fr_rnd(imag_rnd);
	return MPC_RND(real_rnd, imag_rnd);
}

/* hash */

static inline long c_hash(mpc_ptr x)
{
	return fr_hash(mpc_realref(x)) ^ fr_hash(mpc_imagref(x));
}

/* serialize */

static inline void c_serialize(mpc_ptr x)
{
	fr_serialize(mpc_realref(x));
	fr_serialize(mpc_imagref(x));
}

static inline void c_deserialize(mpc_ptr x)
{
	fr_deserialize(mpc_realref(x));
	fr_deserialize(mpc_imagref(x));
}

/* custom-operations */

extern struct custom_operations mlmpc_c_ops;

/* allocators */

CAMLextern value mlmpc_alloc_c_init3(mpfr_prec_t prec_r, mpfr_prec_t prec_i);
