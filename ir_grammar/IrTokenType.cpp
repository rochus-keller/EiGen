// This file was automatically generated by EbnfStudio; don't modify it!
#include "IrTokenType.h"

namespace Ir {
	const char* tokenTypeString( int r ) {
		switch(r) {
			case Tok_Invalid: return "<invalid>";
			case Tok_Plus: return "+";
			case Tok_Comma: return ",";
			case Tok_Minus: return "-";
			case Tok_Semi: return ";";
			case Tok_At: return "@";
			case Tok_Lbrack: return "[";
			case Tok_Rbrack: return "]";
			case Tok_dlr_0: return "$0";
			case Tok_dlr_1: return "$1";
			case Tok_dlr_2: return "$2";
			case Tok_dlr_3: return "$3";
			case Tok_dlr_4: return "$4";
			case Tok_dlr_5: return "$5";
			case Tok_dlr_6: return "$6";
			case Tok_dlr_7: return "$7";
			case Tok_dlr_fp: return "$fp";
			case Tok_dlr_lnk: return "$lnk";
			case Tok_dlr_res: return "$res";
			case Tok_dlr_sp: return "$sp";
			case Tok_dot_alignment: return ".alignment";
			case Tok_dot_code: return ".code";
			case Tok_dot_const: return ".const";
			case Tok_dot_data: return ".data";
			case Tok_dot_duplicable: return ".duplicable";
			case Tok_dot_initcode: return ".initcode";
			case Tok_dot_initdata: return ".initdata";
			case Tok_dot_replaceable: return ".replaceable";
			case Tok_dot_required: return ".required";
			case Tok_dot_type: return ".type";
			case Tok_add: return "add";
			case Tok_alias: return "alias";
			case Tok_and: return "and";
			case Tok_array: return "array";
			case Tok_br: return "br";
			case Tok_break: return "break";
			case Tok_breq: return "breq";
			case Tok_brge: return "brge";
			case Tok_brlt: return "brlt";
			case Tok_brne: return "brne";
			case Tok_call: return "call";
			case Tok_conv: return "conv";
			case Tok_copy: return "copy";
			case Tok_def: return "def";
			case Tok_div: return "div";
			case Tok_enter: return "enter";
			case Tok_enum: return "enum";
			case Tok_f4: return "f4";
			case Tok_f8: return "f8";
			case Tok_field: return "field";
			case Tok_fill: return "fill";
			case Tok_fix: return "fix";
			case Tok_fun: return "fun";
			case Tok_func: return "func";
			case Tok_jump: return "jump";
			case Tok_leave: return "leave";
			case Tok_loc: return "loc";
			case Tok_lsh: return "lsh";
			case Tok_mod: return "mod";
			case Tok_mov: return "mov";
			case Tok_mul: return "mul";
			case Tok_neg: return "neg";
			case Tok_nop: return "nop";
			case Tok_not: return "not";
			case Tok_or: return "or";
			case Tok_pop: return "pop";
			case Tok_ptr: return "ptr";
			case Tok_push: return "push";
			case Tok_rec: return "rec";
			case Tok_ref: return "ref";
			case Tok_req: return "req";
			case Tok_res: return "res";
			case Tok_ret: return "ret";
			case Tok_rsh: return "rsh";
			case Tok_s1: return "s1";
			case Tok_s2: return "s2";
			case Tok_s4: return "s4";
			case Tok_s8: return "s8";
			case Tok_sub: return "sub";
			case Tok_sym: return "sym";
			case Tok_trap: return "trap";
			case Tok_type: return "type";
			case Tok_u1: return "u1";
			case Tok_u2: return "u2";
			case Tok_u4: return "u4";
			case Tok_u8: return "u8";
			case Tok_unfix: return "unfix";
			case Tok_value: return "value";
			case Tok_void: return "void";
			case Tok_xor: return "xor";
			case Tok_string: return "string";
			case Tok_identifier: return "identifier";
			case Tok_binary_integer: return "binary_integer";
			case Tok_octal_integer: return "octal_integer";
			case Tok_decimal_integer: return "decimal_integer";
			case Tok_hex_integer: return "hex_integer";
			case Tok_real: return "real";
			case Tok_Comment: return "Comment";
			case Tok_Eof: return "<eof>";
			default: return "";
		}
	}
	const char* tokenTypeName( int r ) {
		switch(r) {
			case Tok_Invalid: return "Tok_Invalid";
			case Tok_Plus: return "Tok_Plus";
			case Tok_Comma: return "Tok_Comma";
			case Tok_Minus: return "Tok_Minus";
			case Tok_Semi: return "Tok_Semi";
			case Tok_At: return "Tok_At";
			case Tok_Lbrack: return "Tok_Lbrack";
			case Tok_Rbrack: return "Tok_Rbrack";
			case Tok_dlr_0: return "Tok_dlr_0";
			case Tok_dlr_1: return "Tok_dlr_1";
			case Tok_dlr_2: return "Tok_dlr_2";
			case Tok_dlr_3: return "Tok_dlr_3";
			case Tok_dlr_4: return "Tok_dlr_4";
			case Tok_dlr_5: return "Tok_dlr_5";
			case Tok_dlr_6: return "Tok_dlr_6";
			case Tok_dlr_7: return "Tok_dlr_7";
			case Tok_dlr_fp: return "Tok_dlr_fp";
			case Tok_dlr_lnk: return "Tok_dlr_lnk";
			case Tok_dlr_res: return "Tok_dlr_res";
			case Tok_dlr_sp: return "Tok_dlr_sp";
			case Tok_dot_alignment: return "Tok_dot_alignment";
			case Tok_dot_code: return "Tok_dot_code";
			case Tok_dot_const: return "Tok_dot_const";
			case Tok_dot_data: return "Tok_dot_data";
			case Tok_dot_duplicable: return "Tok_dot_duplicable";
			case Tok_dot_initcode: return "Tok_dot_initcode";
			case Tok_dot_initdata: return "Tok_dot_initdata";
			case Tok_dot_replaceable: return "Tok_dot_replaceable";
			case Tok_dot_required: return "Tok_dot_required";
			case Tok_dot_type: return "Tok_dot_type";
			case Tok_add: return "Tok_add";
			case Tok_alias: return "Tok_alias";
			case Tok_and: return "Tok_and";
			case Tok_array: return "Tok_array";
			case Tok_br: return "Tok_br";
			case Tok_break: return "Tok_break";
			case Tok_breq: return "Tok_breq";
			case Tok_brge: return "Tok_brge";
			case Tok_brlt: return "Tok_brlt";
			case Tok_brne: return "Tok_brne";
			case Tok_call: return "Tok_call";
			case Tok_conv: return "Tok_conv";
			case Tok_copy: return "Tok_copy";
			case Tok_def: return "Tok_def";
			case Tok_div: return "Tok_div";
			case Tok_enter: return "Tok_enter";
			case Tok_enum: return "Tok_enum";
			case Tok_f4: return "Tok_f4";
			case Tok_f8: return "Tok_f8";
			case Tok_field: return "Tok_field";
			case Tok_fill: return "Tok_fill";
			case Tok_fix: return "Tok_fix";
			case Tok_fun: return "Tok_fun";
			case Tok_func: return "Tok_func";
			case Tok_jump: return "Tok_jump";
			case Tok_leave: return "Tok_leave";
			case Tok_loc: return "Tok_loc";
			case Tok_lsh: return "Tok_lsh";
			case Tok_mod: return "Tok_mod";
			case Tok_mov: return "Tok_mov";
			case Tok_mul: return "Tok_mul";
			case Tok_neg: return "Tok_neg";
			case Tok_nop: return "Tok_nop";
			case Tok_not: return "Tok_not";
			case Tok_or: return "Tok_or";
			case Tok_pop: return "Tok_pop";
			case Tok_ptr: return "Tok_ptr";
			case Tok_push: return "Tok_push";
			case Tok_rec: return "Tok_rec";
			case Tok_ref: return "Tok_ref";
			case Tok_req: return "Tok_req";
			case Tok_res: return "Tok_res";
			case Tok_ret: return "Tok_ret";
			case Tok_rsh: return "Tok_rsh";
			case Tok_s1: return "Tok_s1";
			case Tok_s2: return "Tok_s2";
			case Tok_s4: return "Tok_s4";
			case Tok_s8: return "Tok_s8";
			case Tok_sub: return "Tok_sub";
			case Tok_sym: return "Tok_sym";
			case Tok_trap: return "Tok_trap";
			case Tok_type: return "Tok_type";
			case Tok_u1: return "Tok_u1";
			case Tok_u2: return "Tok_u2";
			case Tok_u4: return "Tok_u4";
			case Tok_u8: return "Tok_u8";
			case Tok_unfix: return "Tok_unfix";
			case Tok_value: return "Tok_value";
			case Tok_void: return "Tok_void";
			case Tok_xor: return "Tok_xor";
			case Tok_string: return "Tok_string";
			case Tok_identifier: return "Tok_identifier";
			case Tok_binary_integer: return "Tok_binary_integer";
			case Tok_octal_integer: return "Tok_octal_integer";
			case Tok_decimal_integer: return "Tok_decimal_integer";
			case Tok_hex_integer: return "Tok_hex_integer";
			case Tok_real: return "Tok_real";
			case Tok_Comment: return "Tok_Comment";
			case Tok_Eof: return "Tok_Eof";
			default: return "";
		}
	}
	bool tokenTypeIsLiteral( int r ) {
		return r > TT_Literals && r < TT_Keywords;
	}
	bool tokenTypeIsKeyword( int r ) {
		return r > TT_Keywords && r < TT_Specials;
	}
	bool tokenTypeIsSpecial( int r ) {
		return r > TT_Specials && r < TT_Max;
	}
	static inline char at( const char* str, quint32 len, int i ){
		return ( i < len ? str[i] : 0 );
	}
	TokenType tokenTypeFromString( const QByteArray& str, int* pos ) {
		return tokenTypeFromString(str.constData(),str.size(),pos);
	}
	TokenType tokenTypeFromString( const char* str, quint32 len, int* pos ) {
		int i = ( pos != 0 ? *pos: 0 );
		TokenType res = Tok_Invalid;
		switch( at(str,len,i) ){
		case '$':
			switch( at(str,len,i+1) ){
			case '0':
				res = Tok_dlr_0; i += 2;
				break;
			case '1':
				res = Tok_dlr_1; i += 2;
				break;
			case '2':
				res = Tok_dlr_2; i += 2;
				break;
			case '3':
				res = Tok_dlr_3; i += 2;
				break;
			case '4':
				res = Tok_dlr_4; i += 2;
				break;
			case '5':
				res = Tok_dlr_5; i += 2;
				break;
			case '6':
				res = Tok_dlr_6; i += 2;
				break;
			case '7':
				res = Tok_dlr_7; i += 2;
				break;
			case 'f':
				if( at(str,len,i+2) == 'p' ){
					res = Tok_dlr_fp; i += 3;
				}
				break;
			case 'l':
				if( at(str,len,i+2) == 'n' ){
					if( at(str,len,i+3) == 'k' ){
						res = Tok_dlr_lnk; i += 4;
					}
				}
				break;
			case 'r':
				if( at(str,len,i+2) == 'e' ){
					if( at(str,len,i+3) == 's' ){
						res = Tok_dlr_res; i += 4;
					}
				}
				break;
			case 's':
				if( at(str,len,i+2) == 'p' ){
					res = Tok_dlr_sp; i += 3;
				}
				break;
			}
			break;
		case '+':
			res = Tok_Plus; i += 1;
			break;
		case ',':
			res = Tok_Comma; i += 1;
			break;
		case '-':
			res = Tok_Minus; i += 1;
			break;
		case '.':
			switch( at(str,len,i+1) ){
			case 'a':
				if( at(str,len,i+2) == 'l' ){
					if( at(str,len,i+3) == 'i' ){
						if( at(str,len,i+4) == 'g' ){
							if( at(str,len,i+5) == 'n' ){
								if( at(str,len,i+6) == 'm' ){
									if( at(str,len,i+7) == 'e' ){
										if( at(str,len,i+8) == 'n' ){
											if( at(str,len,i+9) == 't' ){
												res = Tok_dot_alignment; i += 10;
											}
										}
									}
								}
							}
						}
					}
				}
				break;
			case 'c':
				if( at(str,len,i+2) == 'o' ){
					switch( at(str,len,i+3) ){
					case 'd':
						if( at(str,len,i+4) == 'e' ){
							res = Tok_dot_code; i += 5;
						}
						break;
					case 'n':
						if( at(str,len,i+4) == 's' ){
							if( at(str,len,i+5) == 't' ){
								res = Tok_dot_const; i += 6;
							}
						}
						break;
					}
				}
				break;
			case 'd':
				switch( at(str,len,i+2) ){
				case 'a':
					if( at(str,len,i+3) == 't' ){
						if( at(str,len,i+4) == 'a' ){
							res = Tok_dot_data; i += 5;
						}
					}
					break;
				case 'u':
					if( at(str,len,i+3) == 'p' ){
						if( at(str,len,i+4) == 'l' ){
							if( at(str,len,i+5) == 'i' ){
								if( at(str,len,i+6) == 'c' ){
									if( at(str,len,i+7) == 'a' ){
										if( at(str,len,i+8) == 'b' ){
											if( at(str,len,i+9) == 'l' ){
												if( at(str,len,i+10) == 'e' ){
													res = Tok_dot_duplicable; i += 11;
												}
											}
										}
									}
								}
							}
						}
					}
					break;
				}
				break;
			case 'i':
				if( at(str,len,i+2) == 'n' ){
					if( at(str,len,i+3) == 'i' ){
						if( at(str,len,i+4) == 't' ){
							switch( at(str,len,i+5) ){
							case 'c':
								if( at(str,len,i+6) == 'o' ){
									if( at(str,len,i+7) == 'd' ){
										if( at(str,len,i+8) == 'e' ){
											res = Tok_dot_initcode; i += 9;
										}
									}
								}
								break;
							case 'd':
								if( at(str,len,i+6) == 'a' ){
									if( at(str,len,i+7) == 't' ){
										if( at(str,len,i+8) == 'a' ){
											res = Tok_dot_initdata; i += 9;
										}
									}
								}
								break;
							}
						}
					}
				}
				break;
			case 'r':
				if( at(str,len,i+2) == 'e' ){
					switch( at(str,len,i+3) ){
					case 'p':
						if( at(str,len,i+4) == 'l' ){
							if( at(str,len,i+5) == 'a' ){
								if( at(str,len,i+6) == 'c' ){
									if( at(str,len,i+7) == 'e' ){
										if( at(str,len,i+8) == 'a' ){
											if( at(str,len,i+9) == 'b' ){
												if( at(str,len,i+10) == 'l' ){
													if( at(str,len,i+11) == 'e' ){
														res = Tok_dot_replaceable; i += 12;
													}
												}
											}
										}
									}
								}
							}
						}
						break;
					case 'q':
						if( at(str,len,i+4) == 'u' ){
							if( at(str,len,i+5) == 'i' ){
								if( at(str,len,i+6) == 'r' ){
									if( at(str,len,i+7) == 'e' ){
										if( at(str,len,i+8) == 'd' ){
											res = Tok_dot_required; i += 9;
										}
									}
								}
							}
						}
						break;
					}
				}
				break;
			case 't':
				if( at(str,len,i+2) == 'y' ){
					if( at(str,len,i+3) == 'p' ){
						if( at(str,len,i+4) == 'e' ){
							res = Tok_dot_type; i += 5;
						}
					}
				}
				break;
			}
			break;
		case ';':
			res = Tok_Semi; i += 1;
			break;
		case '@':
			res = Tok_At; i += 1;
			break;
		case '[':
			res = Tok_Lbrack; i += 1;
			break;
		case ']':
			res = Tok_Rbrack; i += 1;
			break;
		case 'a':
			switch( at(str,len,i+1) ){
			case 'd':
				if( at(str,len,i+2) == 'd' ){
					res = Tok_add; i += 3;
				}
				break;
			case 'l':
				if( at(str,len,i+2) == 'i' ){
					if( at(str,len,i+3) == 'a' ){
						if( at(str,len,i+4) == 's' ){
							res = Tok_alias; i += 5;
						}
					}
				}
				break;
			case 'n':
				if( at(str,len,i+2) == 'd' ){
					res = Tok_and; i += 3;
				}
				break;
			case 'r':
				if( at(str,len,i+2) == 'r' ){
					if( at(str,len,i+3) == 'a' ){
						if( at(str,len,i+4) == 'y' ){
							res = Tok_array; i += 5;
						}
					}
				}
				break;
			}
			break;
		case 'b':
			if( at(str,len,i+1) == 'r' ){
				switch( at(str,len,i+2) ){
				case 'e':
					switch( at(str,len,i+3) ){
					case 'a':
						if( at(str,len,i+4) == 'k' ){
							res = Tok_break; i += 5;
						}
						break;
					case 'q':
						res = Tok_breq; i += 4;
						break;
					}
					break;
				case 'g':
					if( at(str,len,i+3) == 'e' ){
						res = Tok_brge; i += 4;
					}
					break;
				case 'l':
					if( at(str,len,i+3) == 't' ){
						res = Tok_brlt; i += 4;
					}
					break;
				case 'n':
					if( at(str,len,i+3) == 'e' ){
						res = Tok_brne; i += 4;
					}
					break;
				default:
					res = Tok_br; i += 2;
					break;
				}
			}
			break;
		case 'c':
			switch( at(str,len,i+1) ){
			case 'a':
				if( at(str,len,i+2) == 'l' ){
					if( at(str,len,i+3) == 'l' ){
						res = Tok_call; i += 4;
					}
				}
				break;
			case 'o':
				switch( at(str,len,i+2) ){
				case 'n':
					if( at(str,len,i+3) == 'v' ){
						res = Tok_conv; i += 4;
					}
					break;
				case 'p':
					if( at(str,len,i+3) == 'y' ){
						res = Tok_copy; i += 4;
					}
					break;
				}
				break;
			}
			break;
		case 'd':
			switch( at(str,len,i+1) ){
			case 'e':
				if( at(str,len,i+2) == 'f' ){
					res = Tok_def; i += 3;
				}
				break;
			case 'i':
				if( at(str,len,i+2) == 'v' ){
					res = Tok_div; i += 3;
				}
				break;
			}
			break;
		case 'e':
			if( at(str,len,i+1) == 'n' ){
				switch( at(str,len,i+2) ){
				case 't':
					if( at(str,len,i+3) == 'e' ){
						if( at(str,len,i+4) == 'r' ){
							res = Tok_enter; i += 5;
						}
					}
					break;
				case 'u':
					if( at(str,len,i+3) == 'm' ){
						res = Tok_enum; i += 4;
					}
					break;
				}
			}
			break;
		case 'f':
			switch( at(str,len,i+1) ){
			case '4':
				res = Tok_f4; i += 2;
				break;
			case '8':
				res = Tok_f8; i += 2;
				break;
			case 'i':
				switch( at(str,len,i+2) ){
				case 'e':
					if( at(str,len,i+3) == 'l' ){
						if( at(str,len,i+4) == 'd' ){
							res = Tok_field; i += 5;
						}
					}
					break;
				case 'l':
					if( at(str,len,i+3) == 'l' ){
						res = Tok_fill; i += 4;
					}
					break;
				case 'x':
					res = Tok_fix; i += 3;
					break;
				}
				break;
			case 'u':
				if( at(str,len,i+2) == 'n' ){
					if( at(str,len,i+3) == 'c' ){
						res = Tok_func; i += 4;
					} else {
						res = Tok_fun; i += 3;
					}
				}
				break;
			}
			break;
		case 'j':
			if( at(str,len,i+1) == 'u' ){
				if( at(str,len,i+2) == 'm' ){
					if( at(str,len,i+3) == 'p' ){
						res = Tok_jump; i += 4;
					}
				}
			}
			break;
		case 'l':
			switch( at(str,len,i+1) ){
			case 'e':
				if( at(str,len,i+2) == 'a' ){
					if( at(str,len,i+3) == 'v' ){
						if( at(str,len,i+4) == 'e' ){
							res = Tok_leave; i += 5;
						}
					}
				}
				break;
			case 'o':
				if( at(str,len,i+2) == 'c' ){
					res = Tok_loc; i += 3;
				}
				break;
			case 's':
				if( at(str,len,i+2) == 'h' ){
					res = Tok_lsh; i += 3;
				}
				break;
			}
			break;
		case 'm':
			switch( at(str,len,i+1) ){
			case 'o':
				switch( at(str,len,i+2) ){
				case 'd':
					res = Tok_mod; i += 3;
					break;
				case 'v':
					res = Tok_mov; i += 3;
					break;
				}
				break;
			case 'u':
				if( at(str,len,i+2) == 'l' ){
					res = Tok_mul; i += 3;
				}
				break;
			}
			break;
		case 'n':
			switch( at(str,len,i+1) ){
			case 'e':
				if( at(str,len,i+2) == 'g' ){
					res = Tok_neg; i += 3;
				}
				break;
			case 'o':
				switch( at(str,len,i+2) ){
				case 'p':
					res = Tok_nop; i += 3;
					break;
				case 't':
					res = Tok_not; i += 3;
					break;
				}
				break;
			}
			break;
		case 'o':
			if( at(str,len,i+1) == 'r' ){
				res = Tok_or; i += 2;
			}
			break;
		case 'p':
			switch( at(str,len,i+1) ){
			case 'o':
				if( at(str,len,i+2) == 'p' ){
					res = Tok_pop; i += 3;
				}
				break;
			case 't':
				if( at(str,len,i+2) == 'r' ){
					res = Tok_ptr; i += 3;
				}
				break;
			case 'u':
				if( at(str,len,i+2) == 's' ){
					if( at(str,len,i+3) == 'h' ){
						res = Tok_push; i += 4;
					}
				}
				break;
			}
			break;
		case 'r':
			switch( at(str,len,i+1) ){
			case 'e':
				switch( at(str,len,i+2) ){
				case 'c':
					res = Tok_rec; i += 3;
					break;
				case 'f':
					res = Tok_ref; i += 3;
					break;
				case 'q':
					res = Tok_req; i += 3;
					break;
				case 's':
					res = Tok_res; i += 3;
					break;
				case 't':
					res = Tok_ret; i += 3;
					break;
				}
				break;
			case 's':
				if( at(str,len,i+2) == 'h' ){
					res = Tok_rsh; i += 3;
				}
				break;
			}
			break;
		case 's':
			switch( at(str,len,i+1) ){
			case '1':
				res = Tok_s1; i += 2;
				break;
			case '2':
				res = Tok_s2; i += 2;
				break;
			case '4':
				res = Tok_s4; i += 2;
				break;
			case '8':
				res = Tok_s8; i += 2;
				break;
			case 'u':
				if( at(str,len,i+2) == 'b' ){
					res = Tok_sub; i += 3;
				}
				break;
			case 'y':
				if( at(str,len,i+2) == 'm' ){
					res = Tok_sym; i += 3;
				}
				break;
			}
			break;
		case 't':
			switch( at(str,len,i+1) ){
			case 'r':
				if( at(str,len,i+2) == 'a' ){
					if( at(str,len,i+3) == 'p' ){
						res = Tok_trap; i += 4;
					}
				}
				break;
			case 'y':
				if( at(str,len,i+2) == 'p' ){
					if( at(str,len,i+3) == 'e' ){
						res = Tok_type; i += 4;
					}
				}
				break;
			}
			break;
		case 'u':
			switch( at(str,len,i+1) ){
			case '1':
				res = Tok_u1; i += 2;
				break;
			case '2':
				res = Tok_u2; i += 2;
				break;
			case '4':
				res = Tok_u4; i += 2;
				break;
			case '8':
				res = Tok_u8; i += 2;
				break;
			case 'n':
				if( at(str,len,i+2) == 'f' ){
					if( at(str,len,i+3) == 'i' ){
						if( at(str,len,i+4) == 'x' ){
							res = Tok_unfix; i += 5;
						}
					}
				}
				break;
			}
			break;
		case 'v':
			switch( at(str,len,i+1) ){
			case 'a':
				if( at(str,len,i+2) == 'l' ){
					if( at(str,len,i+3) == 'u' ){
						if( at(str,len,i+4) == 'e' ){
							res = Tok_value; i += 5;
						}
					}
				}
				break;
			case 'o':
				if( at(str,len,i+2) == 'i' ){
					if( at(str,len,i+3) == 'd' ){
						res = Tok_void; i += 4;
					}
				}
				break;
			}
			break;
		case 'x':
			if( at(str,len,i+1) == 'o' ){
				if( at(str,len,i+2) == 'r' ){
					res = Tok_xor; i += 3;
				}
			}
			break;
		}
		if(pos) *pos = i;
		return res;
	}
}
