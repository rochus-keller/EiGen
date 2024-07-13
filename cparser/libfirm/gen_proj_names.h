/* Warning: Automatically generated file */

static const pns_lookup_t ASM_lut[] = {
	{ pn_ASM_M, "M" },
	{ pn_ASM_X_regular, "X_regular" },
	{ pn_ASM_first_out, "first_out" },
};

static const pns_lookup_t Alloc_lut[] = {
	{ pn_Alloc_M, "M" },
	{ pn_Alloc_res, "res" },
};

static const pns_lookup_t Builtin_lut[] = {
	{ pn_Builtin_M, "M" },
};

static const pns_lookup_t Call_lut[] = {
	{ pn_Call_M, "M" },
	{ pn_Call_T_result, "T_result" },
	{ pn_Call_X_regular, "X_regular" },
	{ pn_Call_X_except, "X_except" },
};

static const pns_lookup_t Cond_lut[] = {
	{ pn_Cond_false, "false" },
	{ pn_Cond_true, "true" },
};

static const pns_lookup_t Div_lut[] = {
	{ pn_Div_M, "M" },
	{ pn_Div_res, "res" },
	{ pn_Div_X_regular, "X_regular" },
	{ pn_Div_X_except, "X_except" },
};

static const pns_lookup_t Load_lut[] = {
	{ pn_Load_M, "M" },
	{ pn_Load_res, "res" },
	{ pn_Load_X_regular, "X_regular" },
	{ pn_Load_X_except, "X_except" },
};

static const pns_lookup_t Mod_lut[] = {
	{ pn_Mod_M, "M" },
	{ pn_Mod_res, "res" },
	{ pn_Mod_X_regular, "X_regular" },
	{ pn_Mod_X_except, "X_except" },
};

static const pns_lookup_t Raise_lut[] = {
	{ pn_Raise_M, "M" },
	{ pn_Raise_X, "X" },
};

static const pns_lookup_t Start_lut[] = {
	{ pn_Start_M, "M" },
	{ pn_Start_P_frame_base, "P_frame_base" },
	{ pn_Start_T_args, "T_args" },
};

static const pns_lookup_t Store_lut[] = {
	{ pn_Store_M, "M" },
	{ pn_Store_X_regular, "X_regular" },
	{ pn_Store_X_except, "X_except" },
};

static const pns_lookup_t Switch_lut[] = {
	{ pn_Switch_default, "default" },
};


static const proj_lookup_t proj_lut[] = {
	{ iro_ASM, ARRAY_SIZE(ASM_lut), ASM_lut },
	{ iro_Alloc, ARRAY_SIZE(Alloc_lut), Alloc_lut },
	{ iro_Builtin, ARRAY_SIZE(Builtin_lut), Builtin_lut },
	{ iro_Call, ARRAY_SIZE(Call_lut), Call_lut },
	{ iro_Cond, ARRAY_SIZE(Cond_lut), Cond_lut },
	{ iro_Div, ARRAY_SIZE(Div_lut), Div_lut },
	{ iro_Load, ARRAY_SIZE(Load_lut), Load_lut },
	{ iro_Mod, ARRAY_SIZE(Mod_lut), Mod_lut },
	{ iro_Raise, ARRAY_SIZE(Raise_lut), Raise_lut },
	{ iro_Start, ARRAY_SIZE(Start_lut), Start_lut },
	{ iro_Store, ARRAY_SIZE(Store_lut), Store_lut },
	{ iro_Switch, ARRAY_SIZE(Switch_lut), Switch_lut },
};
