/* Warning: Automatically generated file */
#ifndef FIRM_IR_NODES_H
#define FIRM_IR_NODES_H

#ifndef FIRM_IR_IRNODE_H
#error Do not include nodes.h directly; include irnode.h instead.
#endif




/** The opcodes of the libFirm predefined operations.
 * @ingroup ir_op
 */
typedef enum ir_opcode {
	iro_ASM,
	iro_Add,
	iro_Address,
	iro_Align,
	iro_Alloc,
	iro_Anchor,
	iro_And,
	iro_Bad,
	iro_Bitcast,
	iro_Block,
	iro_Builtin,
	iro_Call,
	iro_Cmp,
	iro_Cond,
	iro_Confirm,
	iro_Const,
	iro_Conv,
	iro_CopyB,
	iro_Deleted,
	iro_Div,
	iro_Dummy,
	iro_End,
	iro_Eor,
	iro_Free,
	iro_IJmp,
	iro_Id,
	iro_Jmp,
	iro_Load,
	iro_Member,
	iro_Minus,
	iro_Mod,
	iro_Mul,
	iro_Mulh,
	iro_Mux,
	iro_NoMem,
	iro_Not,
	iro_Offset,
	iro_Or,
	iro_Phi,
	iro_Pin,
	iro_Proj,
	iro_Raise,
	iro_Return,
	iro_Sel,
	iro_Shl,
	iro_Shr,
	iro_Shrs,
	iro_Size,
	iro_Start,
	iro_Store,
	iro_Sub,
	iro_Switch,
	iro_Sync,
	iro_Tuple,
	iro_Unknown,
	iro_first = iro_ASM,
	iro_last  = iro_Unknown,
} ir_opcode;

/**
 * @addtogroup ir_node
 * @{
 */



/**
 * @defgroup ASM ASM node
 *
 * executes assembler fragments of the target machine.

The node contains a template for an assembler snippet. The compiler will
replace occurrences of %0, %1, ... with input/output operands, %% with a
single % char. Some backends allow additional specifiers (for example %w3,
%b3, %h3 on x86 to get a 16bit, 8hit low, 8bit high part of a register).
After the replacements the text is emitted into the final assembly.

The clobber list contains names of registers which have an undefined value
after the assembler instruction is executed; it may also contain 'memory'
or 'cc' if global state/memory changes or the condition code registers
(some backends implicitly set cc on all ASM statements).

Example (an i386 instruction):

    ASM(text="btsl %1, %0",
        constraints = ["+m", "r"],
        clobbers = ["cc"])

%0 references a memory reference which the operation both reads and writes.
For this the node has an address input operand.  %1 references an input
which is passed as a register. The condition code register has an unknown
value after the instruction.

(This format is inspired by the gcc extended asm syntax)
 * @{
 */

/**
 * Input numbers for ASM node
 */
typedef enum {
	n_ASM_mem, /**< memory dependency */
	n_ASM_max = n_ASM_mem
} n_ASM;

/**
 * Projection numbers for result of ASM node (use for Proj nodes)
 */
typedef enum {
	pn_ASM_M, /**< memory result */
	pn_ASM_X_regular, /**< control flow when no jump occurs */
	pn_ASM_first_out, /**< first output */
	pn_ASM_max = pn_ASM_first_out
} pn_ASM;

/**
 * Construct an ASM node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param text      assembler text
 * @param n_constraints number of constraints
 * @param constraints constraints
 * @param n_clobbers number of clobbered registers/memory
 * @param clobbers  list of clobbered registers/memory
 * @param flags     specifies alignment, volatility and pin state
*/
FIRM_API  ir_node *new_rd_ASM(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, int arity, ir_node *const * in, ident* text, size_t n_constraints, ir_asm_constraint* constraints, size_t n_clobbers, ident** clobbers, ir_cons_flags flags);

/**
 * Construct an ASM node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param text      assembler text
 * @param n_constraints number of constraints
 * @param constraints constraints
 * @param n_clobbers number of clobbered registers/memory
 * @param clobbers  list of clobbered registers/memory
 * @param flags     specifies alignment, volatility and pin state
*/
FIRM_API  ir_node *new_r_ASM(ir_node *block, ir_node * irn_mem, int arity, ir_node *const * in, ident* text, size_t n_constraints, ir_asm_constraint* constraints, size_t n_clobbers, ident** clobbers, ir_cons_flags flags);

/**
 * Construct an ASM node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_mem   mem
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param text      assembler text
 * @param n_constraints number of constraints
 * @param constraints constraints
 * @param n_clobbers number of clobbered registers/memory
 * @param clobbers  list of clobbered registers/memory
 * @param flags     specifies alignment, volatility and pin state
*/
FIRM_API  ir_node *new_d_ASM(dbg_info *dbgi, ir_node * irn_mem, int arity, ir_node *const * in, ident* text, size_t n_constraints, ir_asm_constraint* constraints, size_t n_clobbers, ident** clobbers, ir_cons_flags flags);

/**
 * Construct an ASM node.
 *
 * @param irn_mem   mem
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param text      assembler text
 * @param n_constraints number of constraints
 * @param constraints constraints
 * @param n_clobbers number of clobbered registers/memory
 * @param clobbers  list of clobbered registers/memory
 * @param flags     specifies alignment, volatility and pin state
*/
FIRM_API  ir_node *new_ASM(ir_node * irn_mem, int arity, ir_node *const * in, ident* text, size_t n_constraints, ir_asm_constraint* constraints, size_t n_clobbers, ident** clobbers, ir_cons_flags flags);

/**
 * Test if node is a ASM
 * @returns 1 if the node is a ASM node, 0 otherwise
 */
FIRM_API  int is_ASM(const ir_node *node);

/** Returns mem input of an ASM node. */
FIRM_API  ir_node *get_ASM_mem(const ir_node *node);
/** Sets mem input of an ASM node. */
FIRM_API  void set_ASM_mem(ir_node *node, ir_node *mem);
/** Get the number of ASM inputs. */
FIRM_API  int get_ASM_n_inputs(ir_node const *node);
/** Get the ASM input with index @p pos. */
FIRM_API  ir_node *get_ASM_input(ir_node const *node, int pos);
/** Set the ASM input with index @p pos. */
FIRM_API  void set_ASM_input(ir_node *node, int pos, ir_node *input);
/** Get an array of all ASM inputs. */
ir_node **get_ASM_input_arr(ir_node *node);

/** Returns constraints attribute of an ASM node. */
FIRM_API  ir_asm_constraint* get_ASM_constraints(const ir_node *node);
/** Sets constraints attribute of an ASM node. */
FIRM_API  void set_ASM_constraints(ir_node *node, ir_asm_constraint* constraints);

/** Returns clobbers attribute of an ASM node. */
FIRM_API  ident** get_ASM_clobbers(const ir_node *node);
/** Sets clobbers attribute of an ASM node. */
FIRM_API  void set_ASM_clobbers(ir_node *node, ident** clobbers);

/** Returns text attribute of an ASM node. */
FIRM_API  ident* get_ASM_text(const ir_node *node);
/** Sets text attribute of an ASM node. */
FIRM_API  void set_ASM_text(ir_node *node, ident* text);
/** ASM opcode */
FIRM_API  ir_op *op_ASM;

/** Returns opcode for ASM nodes. */
FIRM_API  ir_op *get_op_ASM(void);

/** @} */

/**
 * @defgroup Add Add node
 *
 * returns the sum of its operands
 * @{
 */

/**
 * Input numbers for Add node
 */
typedef enum {
	n_Add_left, /**< first operand */
	n_Add_right, /**< second operand */
	n_Add_max = n_Add_right
} n_Add;

/**
 * Construct an Add node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_rd_Add(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct an Add node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_r_Add(ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct an Add node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_d_Add(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct an Add node.
 *
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_Add(ir_node * irn_left, ir_node * irn_right);

/**
 * Test if node is a Add
 * @returns 1 if the node is a Add node, 0 otherwise
 */
FIRM_API  int is_Add(const ir_node *node);

/** Returns left input of an Add node. */
FIRM_API  ir_node *get_Add_left(const ir_node *node);
/** Sets left input of an Add node. */
FIRM_API  void set_Add_left(ir_node *node, ir_node *left);
/** Returns right input of an Add node. */
FIRM_API  ir_node *get_Add_right(const ir_node *node);
/** Sets right input of an Add node. */
FIRM_API  void set_Add_right(ir_node *node, ir_node *right);
/** Add opcode */
FIRM_API  ir_op *op_Add;

/** Returns opcode for Add nodes. */
FIRM_API  ir_op *get_op_Add(void);

/** @} */

/**
 * @defgroup Address Address node
 *
 * Symbolic constant that represents the address of an entity (variable or
method)
 * @{
 */

/**
 * Construct an Address node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irg       The IR graph the node belongs to.
 * @param entity    entity to operate on
*/
FIRM_API  ir_node *new_rd_Address(dbg_info *dbgi, ir_graph *irg, ir_entity* entity);

/**
 * Construct an Address node.
 *
 * @param irg       The IR graph the node belongs to.
 * @param entity    entity to operate on
*/
FIRM_API  ir_node *new_r_Address(ir_graph *irg, ir_entity* entity);

/**
 * Construct an Address node.
 *
 * @param dbgi      A pointer to debug information.
 * @param entity    entity to operate on
*/
FIRM_API  ir_node *new_d_Address(dbg_info *dbgi, ir_entity* entity);

/**
 * Construct an Address node.
 *
 * @param entity    entity to operate on
*/
FIRM_API  ir_node *new_Address(ir_entity* entity);

/**
 * Test if node is a Address
 * @returns 1 if the node is a Address node, 0 otherwise
 */
FIRM_API  int is_Address(const ir_node *node);


/** Returns entity attribute of an Address node. */
FIRM_API  ir_entity* get_Address_entity(const ir_node *node);
/** Sets entity attribute of an Address node. */
FIRM_API  void set_Address_entity(ir_node *node, ir_entity* entity);
/** Address opcode */
FIRM_API  ir_op *op_Address;

/** Returns opcode for Address nodes. */
FIRM_API  ir_op *get_op_Address(void);

/** @} */

/**
 * @defgroup Align Align node
 *
 * A symbolic constant that represents the alignment of a type
 * @{
 */

/**
 * Construct an Align node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irg       The IR graph the node belongs to.
 * @param mode      mode of the operations result
 * @param type      type to operate on
*/
FIRM_API  ir_node *new_rd_Align(dbg_info *dbgi, ir_graph *irg, ir_mode * mode, ir_type* type);

/**
 * Construct an Align node.
 *
 * @param irg       The IR graph the node belongs to.
 * @param mode      mode of the operations result
 * @param type      type to operate on
*/
FIRM_API  ir_node *new_r_Align(ir_graph *irg, ir_mode * mode, ir_type* type);

/**
 * Construct an Align node.
 *
 * @param dbgi      A pointer to debug information.
 * @param mode      mode of the operations result
 * @param type      type to operate on
*/
FIRM_API  ir_node *new_d_Align(dbg_info *dbgi, ir_mode * mode, ir_type* type);

/**
 * Construct an Align node.
 *
 * @param mode      mode of the operations result
 * @param type      type to operate on
*/
FIRM_API  ir_node *new_Align(ir_mode * mode, ir_type* type);

/**
 * Test if node is a Align
 * @returns 1 if the node is a Align node, 0 otherwise
 */
FIRM_API  int is_Align(const ir_node *node);


/** Returns type attribute of an Align node. */
FIRM_API  ir_type* get_Align_type(const ir_node *node);
/** Sets type attribute of an Align node. */
FIRM_API  void set_Align_type(ir_node *node, ir_type* type);
/** Align opcode */
FIRM_API  ir_op *op_Align;

/** Returns opcode for Align nodes. */
FIRM_API  ir_op *get_op_Align(void);

/** @} */

/**
 * @defgroup Alloc Alloc node
 *
 * Allocates a block of memory on the stack.
 * @{
 */

/**
 * Input numbers for Alloc node
 */
typedef enum {
	n_Alloc_mem, /**< memory dependency */
	n_Alloc_size, /**< size of the block in bytes */
	n_Alloc_max = n_Alloc_size
} n_Alloc;

/**
 * Projection numbers for result of Alloc node (use for Proj nodes)
 */
typedef enum {
	pn_Alloc_M, /**< memory result */
	pn_Alloc_res, /**< pointer to newly allocated memory */
	pn_Alloc_max = pn_Alloc_res
} pn_Alloc;

/**
 * Construct an Alloc node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_size  size
 * @param alignment alignment of the memory block (must be a power of 2)
*/
FIRM_API  ir_node *new_rd_Alloc(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_size, unsigned alignment);

/**
 * Construct an Alloc node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_size  size
 * @param alignment alignment of the memory block (must be a power of 2)
*/
FIRM_API  ir_node *new_r_Alloc(ir_node *block, ir_node * irn_mem, ir_node * irn_size, unsigned alignment);

/**
 * Construct an Alloc node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_mem   mem
 * @param irn_size  size
 * @param alignment alignment of the memory block (must be a power of 2)
*/
FIRM_API  ir_node *new_d_Alloc(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_size, unsigned alignment);

/**
 * Construct an Alloc node.
 *
 * @param irn_mem   mem
 * @param irn_size  size
 * @param alignment alignment of the memory block (must be a power of 2)
*/
FIRM_API  ir_node *new_Alloc(ir_node * irn_mem, ir_node * irn_size, unsigned alignment);

/**
 * Test if node is a Alloc
 * @returns 1 if the node is a Alloc node, 0 otherwise
 */
FIRM_API  int is_Alloc(const ir_node *node);

/** Returns mem input of an Alloc node. */
FIRM_API  ir_node *get_Alloc_mem(const ir_node *node);
/** Sets mem input of an Alloc node. */
FIRM_API  void set_Alloc_mem(ir_node *node, ir_node *mem);
/** Returns size input of an Alloc node. */
FIRM_API  ir_node *get_Alloc_size(const ir_node *node);
/** Sets size input of an Alloc node. */
FIRM_API  void set_Alloc_size(ir_node *node, ir_node *size);

/** Returns alignment attribute of an Alloc node. */
FIRM_API  unsigned get_Alloc_alignment(const ir_node *node);
/** Sets alignment attribute of an Alloc node. */
FIRM_API  void set_Alloc_alignment(ir_node *node, unsigned alignment);
/** Alloc opcode */
FIRM_API  ir_op *op_Alloc;

/** Returns opcode for Alloc nodes. */
FIRM_API  ir_op *get_op_Alloc(void);

/** @} */

/**
 * @defgroup Anchor Anchor node
 *
 * Utility node used to "hold" nodes in a graph that might possibly not be
reachable by other means or which should be reachable immediately without
searching through the graph.
Each firm-graph contains exactly one anchor node whose address is always
known. All other well-known graph-nodes like Start, End, NoMem, ...
are found by looking at the respective Anchor operand.
 * @{
 */

/**
 * Input numbers for Anchor node
 */
typedef enum {
	n_Anchor_end_block, /**< block the end node belongs to */
	n_Anchor_start_block, /**< block the start node belongs to */
	n_Anchor_end, /**< end node of this ir_graph */
	n_Anchor_start, /**< start node of this ir_graph */
	n_Anchor_frame, /**< frame of this ir_graph */
	n_Anchor_initial_mem, /**< initial memory of this ir_graph */
	n_Anchor_args, /**< argument proj of the start node */
	n_Anchor_no_mem, /**< the only NoMem node of this ir_graph */
	n_Anchor_max = n_Anchor_no_mem
} n_Anchor;


/**
 * Test if node is a Anchor
 * @returns 1 if the node is a Anchor node, 0 otherwise
 */
FIRM_API  int is_Anchor(const ir_node *node);

/** Returns end_block input of an Anchor node. */
FIRM_API  ir_node *get_Anchor_end_block(const ir_node *node);
/** Sets end_block input of an Anchor node. */
FIRM_API  void set_Anchor_end_block(ir_node *node, ir_node *end_block);
/** Returns start_block input of an Anchor node. */
FIRM_API  ir_node *get_Anchor_start_block(const ir_node *node);
/** Sets start_block input of an Anchor node. */
FIRM_API  void set_Anchor_start_block(ir_node *node, ir_node *start_block);
/** Returns end input of an Anchor node. */
FIRM_API  ir_node *get_Anchor_end(const ir_node *node);
/** Sets end input of an Anchor node. */
FIRM_API  void set_Anchor_end(ir_node *node, ir_node *end);
/** Returns start input of an Anchor node. */
FIRM_API  ir_node *get_Anchor_start(const ir_node *node);
/** Sets start input of an Anchor node. */
FIRM_API  void set_Anchor_start(ir_node *node, ir_node *start);
/** Returns frame input of an Anchor node. */
FIRM_API  ir_node *get_Anchor_frame(const ir_node *node);
/** Sets frame input of an Anchor node. */
FIRM_API  void set_Anchor_frame(ir_node *node, ir_node *frame);
/** Returns initial_mem input of an Anchor node. */
FIRM_API  ir_node *get_Anchor_initial_mem(const ir_node *node);
/** Sets initial_mem input of an Anchor node. */
FIRM_API  void set_Anchor_initial_mem(ir_node *node, ir_node *initial_mem);
/** Returns args input of an Anchor node. */
FIRM_API  ir_node *get_Anchor_args(const ir_node *node);
/** Sets args input of an Anchor node. */
FIRM_API  void set_Anchor_args(ir_node *node, ir_node *args);
/** Returns no_mem input of an Anchor node. */
FIRM_API  ir_node *get_Anchor_no_mem(const ir_node *node);
/** Sets no_mem input of an Anchor node. */
FIRM_API  void set_Anchor_no_mem(ir_node *node, ir_node *no_mem);
/** Anchor opcode */
FIRM_API  ir_op *op_Anchor;

/** Returns opcode for Anchor nodes. */
FIRM_API  ir_op *get_op_Anchor(void);

/** @} */

/**
 * @defgroup And And node
 *
 * returns the result of a bitwise and operation of its operands
 * @{
 */

/**
 * Input numbers for And node
 */
typedef enum {
	n_And_left, /**< first operand */
	n_And_right, /**< second operand */
	n_And_max = n_And_right
} n_And;

/**
 * Construct an And node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_rd_And(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct an And node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_r_And(ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct an And node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_d_And(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct an And node.
 *
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_And(ir_node * irn_left, ir_node * irn_right);

/**
 * Test if node is a And
 * @returns 1 if the node is a And node, 0 otherwise
 */
FIRM_API  int is_And(const ir_node *node);

/** Returns left input of an And node. */
FIRM_API  ir_node *get_And_left(const ir_node *node);
/** Sets left input of an And node. */
FIRM_API  void set_And_left(ir_node *node, ir_node *left);
/** Returns right input of an And node. */
FIRM_API  ir_node *get_And_right(const ir_node *node);
/** Sets right input of an And node. */
FIRM_API  void set_And_right(ir_node *node, ir_node *right);
/** And opcode */
FIRM_API  ir_op *op_And;

/** Returns opcode for And nodes. */
FIRM_API  ir_op *get_op_And(void);

/** @} */

/**
 * @defgroup Bad Bad node
 *
 * Bad nodes indicate invalid input, which is values which should never be
computed.

The typical use case for the Bad node is removing unreachable code.
Frontends should set the current_block to Bad when it is clear that
following code must be unreachable (i.e. after a goto or return statement).
Optimizations also set block predecessors to Bad when it becomes clear,
that a control flow edge can never be executed.

The gigo optimizations ensures that nodes with Bad as their block, get
replaced by Bad themselves. Nodes with at least 1 Bad input get exchanged
with Bad too. Exception to this rule are Block, Phi, Tuple and End node;
This is because removing inputs from a Block is hairy operation (requiring,
Phis to be shortened too for example). So instead of removing block inputs
they are set to Bad, and the actual removal is left to the control flow
optimization phase. Block, Phi, Tuple with only Bad inputs however are
replaced by Bad right away.

In the future we may use the Bad node to model poison values that arise
from undefined behaviour like reading uninitialized local variables in C.
 * @{
 */

/**
 * Construct a Bad node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irg       The IR graph the node belongs to.
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_rd_Bad(dbg_info *dbgi, ir_graph *irg, ir_mode * mode);

/**
 * Construct a Bad node.
 *
 * @param irg       The IR graph the node belongs to.
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_r_Bad(ir_graph *irg, ir_mode * mode);

/**
 * Construct a Bad node.
 *
 * @param dbgi      A pointer to debug information.
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_d_Bad(dbg_info *dbgi, ir_mode * mode);

/**
 * Construct a Bad node.
 *
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_Bad(ir_mode * mode);

/**
 * Test if node is a Bad
 * @returns 1 if the node is a Bad node, 0 otherwise
 */
FIRM_API  int is_Bad(const ir_node *node);

/** Bad opcode */
FIRM_API  ir_op *op_Bad;

/** Returns opcode for Bad nodes. */
FIRM_API  ir_op *get_op_Bad(void);

/** @} */

/**
 * @defgroup Bitcast Bitcast node
 *
 * Converts a value between modes with different arithmetics but same
number of bits by reinterpreting the bits in the new mode
 * @{
 */

/**
 * Input numbers for Bitcast node
 */
typedef enum {
	n_Bitcast_op, /**< operand */
	n_Bitcast_max = n_Bitcast_op
} n_Bitcast;

/**
 * Construct a Bitcast node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_op    op
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_rd_Bitcast(dbg_info *dbgi, ir_node *block, ir_node * irn_op, ir_mode * mode);

/**
 * Construct a Bitcast node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_op    op
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_r_Bitcast(ir_node *block, ir_node * irn_op, ir_mode * mode);

/**
 * Construct a Bitcast node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_op    op
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_d_Bitcast(dbg_info *dbgi, ir_node * irn_op, ir_mode * mode);

/**
 * Construct a Bitcast node.
 *
 * @param irn_op    op
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_Bitcast(ir_node * irn_op, ir_mode * mode);

/**
 * Test if node is a Bitcast
 * @returns 1 if the node is a Bitcast node, 0 otherwise
 */
FIRM_API  int is_Bitcast(const ir_node *node);

/** Returns op input of a Bitcast node. */
FIRM_API  ir_node *get_Bitcast_op(const ir_node *node);
/** Sets op input of a Bitcast node. */
FIRM_API  void set_Bitcast_op(ir_node *node, ir_node *op);
/** Bitcast opcode */
FIRM_API  ir_op *op_Bitcast;

/** Returns opcode for Bitcast nodes. */
FIRM_API  ir_op *get_op_Bitcast(void);

/** @} */

/**
 * @defgroup Block Block node
 *
 * A basic block
 * @{
 */

/**
 * Construct a Block node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irg       The IR graph the node belongs to.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_rd_Block(dbg_info *dbgi, ir_graph *irg, int arity, ir_node *const * in);

/**
 * Construct a Block node.
 *
 * @param irg       The IR graph the node belongs to.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_r_Block(ir_graph *irg, int arity, ir_node *const * in);

/**
 * Construct a Block node.
 *
 * @param dbgi      A pointer to debug information.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_d_Block(dbg_info *dbgi, int arity, ir_node *const * in);

/**
 * Construct a Block node.
 *
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_Block(int arity, ir_node *const * in);

/**
 * Test if node is a Block
 * @returns 1 if the node is a Block node, 0 otherwise
 */
FIRM_API  int is_Block(const ir_node *node);

/** Get the number of Block cfgpreds. */
FIRM_API  int get_Block_n_cfgpreds(ir_node const *node);
/** Get the Block cfgpred with index @p pos. */
FIRM_API  ir_node *get_Block_cfgpred(ir_node const *node, int pos);
/** Set the Block cfgpred with index @p pos. */
FIRM_API  void set_Block_cfgpred(ir_node *node, int pos, ir_node *cfgpred);
/** Get an array of all Block cfgpreds. */
ir_node **get_Block_cfgpred_arr(ir_node *node);

/** Returns entity attribute of a Block node. */
FIRM_API  ir_entity* get_Block_entity(const ir_node *node);
/** Sets entity attribute of a Block node. */
FIRM_API  void set_Block_entity(ir_node *node, ir_entity* entity);
/** Block opcode */
FIRM_API  ir_op *op_Block;

/** Returns opcode for Block nodes. */
FIRM_API  ir_op *get_op_Block(void);

/** @} */

/**
 * @defgroup Builtin Builtin node
 *
 * performs a backend-specific builtin.
 * @{
 */

/**
 * Input numbers for Builtin node
 */
typedef enum {
	n_Builtin_mem, /**< memory dependency */
	n_Builtin_max = n_Builtin_mem
} n_Builtin;

/**
 * Projection numbers for result of Builtin node (use for Proj nodes)
 */
typedef enum {
	pn_Builtin_M, /**< memory result */
	pn_Builtin_max = pn_Builtin_M
} pn_Builtin;

/**
 * Construct a Builtin node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param kind      kind of builtin
 * @param type      method type for the builtin call
*/
FIRM_API  ir_node *new_rd_Builtin(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, int arity, ir_node *const * in, ir_builtin_kind kind, ir_type* type);

/**
 * Construct a Builtin node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param kind      kind of builtin
 * @param type      method type for the builtin call
*/
FIRM_API  ir_node *new_r_Builtin(ir_node *block, ir_node * irn_mem, int arity, ir_node *const * in, ir_builtin_kind kind, ir_type* type);

/**
 * Construct a Builtin node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_mem   mem
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param kind      kind of builtin
 * @param type      method type for the builtin call
*/
FIRM_API  ir_node *new_d_Builtin(dbg_info *dbgi, ir_node * irn_mem, int arity, ir_node *const * in, ir_builtin_kind kind, ir_type* type);

/**
 * Construct a Builtin node.
 *
 * @param irn_mem   mem
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param kind      kind of builtin
 * @param type      method type for the builtin call
*/
FIRM_API  ir_node *new_Builtin(ir_node * irn_mem, int arity, ir_node *const * in, ir_builtin_kind kind, ir_type* type);

/**
 * Test if node is a Builtin
 * @returns 1 if the node is a Builtin node, 0 otherwise
 */
FIRM_API  int is_Builtin(const ir_node *node);

/** Returns mem input of a Builtin node. */
FIRM_API  ir_node *get_Builtin_mem(const ir_node *node);
/** Sets mem input of a Builtin node. */
FIRM_API  void set_Builtin_mem(ir_node *node, ir_node *mem);
/** Get the number of Builtin params. */
FIRM_API  int get_Builtin_n_params(ir_node const *node);
/** Get the Builtin param with index @p pos. */
FIRM_API  ir_node *get_Builtin_param(ir_node const *node, int pos);
/** Set the Builtin param with index @p pos. */
FIRM_API  void set_Builtin_param(ir_node *node, int pos, ir_node *param);
/** Get an array of all Builtin params. */
ir_node **get_Builtin_param_arr(ir_node *node);

/** Returns kind attribute of a Builtin node. */
FIRM_API  ir_builtin_kind get_Builtin_kind(const ir_node *node);
/** Sets kind attribute of a Builtin node. */
FIRM_API  void set_Builtin_kind(ir_node *node, ir_builtin_kind kind);

/** Returns type attribute of a Builtin node. */
FIRM_API  ir_type* get_Builtin_type(const ir_node *node);
/** Sets type attribute of a Builtin node. */
FIRM_API  void set_Builtin_type(ir_node *node, ir_type* type);
/** Builtin opcode */
FIRM_API  ir_op *op_Builtin;

/** Returns opcode for Builtin nodes. */
FIRM_API  ir_op *get_op_Builtin(void);

/** @} */

/**
 * @defgroup Call Call node
 *
 * Calls other code. Control flow is transferred to ptr, additional
operands are passed to the called code. Called code usually performs a
return operation. The operands of this return operation are the result
of the Call node.
 * @{
 */

/**
 * Input numbers for Call node
 */
typedef enum {
	n_Call_mem, /**< memory dependency */
	n_Call_ptr, /**< pointer to called code */
	n_Call_max = n_Call_ptr
} n_Call;

/**
 * Projection numbers for result of Call node (use for Proj nodes)
 */
typedef enum {
	pn_Call_M, /**< memory result */
	pn_Call_T_result, /**< tuple containing all results */
	pn_Call_X_regular, /**< control flow when no exception occurs */
	pn_Call_X_except, /**< control flow when exception occurred */
	pn_Call_max = pn_Call_X_except
} pn_Call;

/**
 * Construct a Call node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_ptr   ptr
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param type      type of the call (usually type of the called procedure)
*/
FIRM_API  ir_node *new_rd_Call(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_ptr, int arity, ir_node *const * in, ir_type* type);

/**
 * Construct a Call node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_ptr   ptr
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param type      type of the call (usually type of the called procedure)
*/
FIRM_API  ir_node *new_r_Call(ir_node *block, ir_node * irn_mem, ir_node * irn_ptr, int arity, ir_node *const * in, ir_type* type);

/**
 * Construct a Call node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_mem   mem
 * @param irn_ptr   ptr
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param type      type of the call (usually type of the called procedure)
*/
FIRM_API  ir_node *new_d_Call(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_ptr, int arity, ir_node *const * in, ir_type* type);

/**
 * Construct a Call node.
 *
 * @param irn_mem   mem
 * @param irn_ptr   ptr
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param type      type of the call (usually type of the called procedure)
*/
FIRM_API  ir_node *new_Call(ir_node * irn_mem, ir_node * irn_ptr, int arity, ir_node *const * in, ir_type* type);

/**
 * Test if node is a Call
 * @returns 1 if the node is a Call node, 0 otherwise
 */
FIRM_API  int is_Call(const ir_node *node);

/** Returns mem input of a Call node. */
FIRM_API  ir_node *get_Call_mem(const ir_node *node);
/** Sets mem input of a Call node. */
FIRM_API  void set_Call_mem(ir_node *node, ir_node *mem);
/** Returns ptr input of a Call node. */
FIRM_API  ir_node *get_Call_ptr(const ir_node *node);
/** Sets ptr input of a Call node. */
FIRM_API  void set_Call_ptr(ir_node *node, ir_node *ptr);
/** Get the number of Call params. */
FIRM_API  int get_Call_n_params(ir_node const *node);
/** Get the Call param with index @p pos. */
FIRM_API  ir_node *get_Call_param(ir_node const *node, int pos);
/** Set the Call param with index @p pos. */
FIRM_API  void set_Call_param(ir_node *node, int pos, ir_node *param);
/** Get an array of all Call params. */
ir_node **get_Call_param_arr(ir_node *node);

/** Returns type attribute of a Call node. */
FIRM_API  ir_type* get_Call_type(const ir_node *node);
/** Sets type attribute of a Call node. */
FIRM_API  void set_Call_type(ir_node *node, ir_type* type);
/** Call opcode */
FIRM_API  ir_op *op_Call;

/** Returns opcode for Call nodes. */
FIRM_API  ir_op *get_op_Call(void);

/** @} */

/**
 * @defgroup Cmp Cmp node
 *
 * Compares its two operands and checks whether a specified
relation (like less or equal) is fulfilled.
 * @{
 */

/**
 * Input numbers for Cmp node
 */
typedef enum {
	n_Cmp_left, /**< first operand */
	n_Cmp_right, /**< second operand */
	n_Cmp_max = n_Cmp_right
} n_Cmp;

/**
 * Construct a Cmp node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
 * @param relation  Comparison relation
*/
FIRM_API  ir_node *new_rd_Cmp(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right, ir_relation relation);

/**
 * Construct a Cmp node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
 * @param relation  Comparison relation
*/
FIRM_API  ir_node *new_r_Cmp(ir_node *block, ir_node * irn_left, ir_node * irn_right, ir_relation relation);

/**
 * Construct a Cmp node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_left  left
 * @param irn_right right
 * @param relation  Comparison relation
*/
FIRM_API  ir_node *new_d_Cmp(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right, ir_relation relation);

/**
 * Construct a Cmp node.
 *
 * @param irn_left  left
 * @param irn_right right
 * @param relation  Comparison relation
*/
FIRM_API  ir_node *new_Cmp(ir_node * irn_left, ir_node * irn_right, ir_relation relation);

/**
 * Test if node is a Cmp
 * @returns 1 if the node is a Cmp node, 0 otherwise
 */
FIRM_API  int is_Cmp(const ir_node *node);

/** Returns left input of a Cmp node. */
FIRM_API  ir_node *get_Cmp_left(const ir_node *node);
/** Sets left input of a Cmp node. */
FIRM_API  void set_Cmp_left(ir_node *node, ir_node *left);
/** Returns right input of a Cmp node. */
FIRM_API  ir_node *get_Cmp_right(const ir_node *node);
/** Sets right input of a Cmp node. */
FIRM_API  void set_Cmp_right(ir_node *node, ir_node *right);

/** Returns relation attribute of a Cmp node. */
FIRM_API  ir_relation get_Cmp_relation(const ir_node *node);
/** Sets relation attribute of a Cmp node. */
FIRM_API  void set_Cmp_relation(ir_node *node, ir_relation relation);
/** Cmp opcode */
FIRM_API  ir_op *op_Cmp;

/** Returns opcode for Cmp nodes. */
FIRM_API  ir_op *get_op_Cmp(void);

/** @} */

/**
 * @defgroup Cond Cond node
 *
 * Conditionally change control flow.
 * @{
 */

/**
 * Input numbers for Cond node
 */
typedef enum {
	n_Cond_selector, /**< condition parameter */
	n_Cond_max = n_Cond_selector
} n_Cond;

/**
 * Projection numbers for result of Cond node (use for Proj nodes)
 */
typedef enum {
	pn_Cond_false, /**< control flow if operand is "false" */
	pn_Cond_true, /**< control flow if operand is "true" */
	pn_Cond_max = pn_Cond_true
} pn_Cond;

/**
 * Construct a Cond node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_selector selector
*/
FIRM_API  ir_node *new_rd_Cond(dbg_info *dbgi, ir_node *block, ir_node * irn_selector);

/**
 * Construct a Cond node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_selector selector
*/
FIRM_API  ir_node *new_r_Cond(ir_node *block, ir_node * irn_selector);

/**
 * Construct a Cond node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_selector selector
*/
FIRM_API  ir_node *new_d_Cond(dbg_info *dbgi, ir_node * irn_selector);

/**
 * Construct a Cond node.
 *
 * @param irn_selector selector
*/
FIRM_API  ir_node *new_Cond(ir_node * irn_selector);

/**
 * Test if node is a Cond
 * @returns 1 if the node is a Cond node, 0 otherwise
 */
FIRM_API  int is_Cond(const ir_node *node);

/** Returns selector input of a Cond node. */
FIRM_API  ir_node *get_Cond_selector(const ir_node *node);
/** Sets selector input of a Cond node. */
FIRM_API  void set_Cond_selector(ir_node *node, ir_node *selector);

/** Returns jmp_pred attribute of a Cond node. */
FIRM_API  cond_jmp_predicate get_Cond_jmp_pred(const ir_node *node);
/** Sets jmp_pred attribute of a Cond node. */
FIRM_API  void set_Cond_jmp_pred(ir_node *node, cond_jmp_predicate jmp_pred);
/** Cond opcode */
FIRM_API  ir_op *op_Cond;

/** Returns opcode for Cond nodes. */
FIRM_API  ir_op *get_op_Cond(void);

/** @} */

/**
 * @defgroup Confirm Confirm node
 *
 * Specifies constraints for a value. This allows explicit representation
of path-sensitive properties. (Example: This value is always >= 0 on 1
if-branch then all users within that branch are rerouted to a confirm-node
specifying this property).

A constraint is specified for the relation between value and bound.
value is always returned.
Note that this node does NOT check or assert the constraint, it merely
specifies it.
 * @{
 */

/**
 * Input numbers for Confirm node
 */
typedef enum {
	n_Confirm_value, /**< value to express a constraint for */
	n_Confirm_bound, /**< value to compare against */
	n_Confirm_max = n_Confirm_bound
} n_Confirm;

/**
 * Construct a Confirm node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_value value
 * @param irn_bound bound
 * @param relation  relation of value to bound
*/
FIRM_API  ir_node *new_rd_Confirm(dbg_info *dbgi, ir_node *block, ir_node * irn_value, ir_node * irn_bound, ir_relation relation);

/**
 * Construct a Confirm node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_value value
 * @param irn_bound bound
 * @param relation  relation of value to bound
*/
FIRM_API  ir_node *new_r_Confirm(ir_node *block, ir_node * irn_value, ir_node * irn_bound, ir_relation relation);

/**
 * Construct a Confirm node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_value value
 * @param irn_bound bound
 * @param relation  relation of value to bound
*/
FIRM_API  ir_node *new_d_Confirm(dbg_info *dbgi, ir_node * irn_value, ir_node * irn_bound, ir_relation relation);

/**
 * Construct a Confirm node.
 *
 * @param irn_value value
 * @param irn_bound bound
 * @param relation  relation of value to bound
*/
FIRM_API  ir_node *new_Confirm(ir_node * irn_value, ir_node * irn_bound, ir_relation relation);

/**
 * Test if node is a Confirm
 * @returns 1 if the node is a Confirm node, 0 otherwise
 */
FIRM_API  int is_Confirm(const ir_node *node);

/** Returns value input of a Confirm node. */
FIRM_API  ir_node *get_Confirm_value(const ir_node *node);
/** Sets value input of a Confirm node. */
FIRM_API  void set_Confirm_value(ir_node *node, ir_node *value);
/** Returns bound input of a Confirm node. */
FIRM_API  ir_node *get_Confirm_bound(const ir_node *node);
/** Sets bound input of a Confirm node. */
FIRM_API  void set_Confirm_bound(ir_node *node, ir_node *bound);

/** Returns relation attribute of a Confirm node. */
FIRM_API  ir_relation get_Confirm_relation(const ir_node *node);
/** Sets relation attribute of a Confirm node. */
FIRM_API  void set_Confirm_relation(ir_node *node, ir_relation relation);
/** Confirm opcode */
FIRM_API  ir_op *op_Confirm;

/** Returns opcode for Confirm nodes. */
FIRM_API  ir_op *get_op_Confirm(void);

/** @} */

/**
 * @defgroup Const Const node
 *
 * Returns a constant value.
 * @{
 */

/**
 * Construct a Const node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irg       The IR graph the node belongs to.
 * @param tarval    constant value (a tarval object)
*/
FIRM_API  ir_node *new_rd_Const(dbg_info *dbgi, ir_graph *irg, ir_tarval* tarval);

/**
 * Construct a Const node.
 *
 * @param irg       The IR graph the node belongs to.
 * @param tarval    constant value (a tarval object)
*/
FIRM_API  ir_node *new_r_Const(ir_graph *irg, ir_tarval* tarval);

/**
 * Construct a Const node.
 *
 * @param dbgi      A pointer to debug information.
 * @param tarval    constant value (a tarval object)
*/
FIRM_API  ir_node *new_d_Const(dbg_info *dbgi, ir_tarval* tarval);

/**
 * Construct a Const node.
 *
 * @param tarval    constant value (a tarval object)
*/
FIRM_API  ir_node *new_Const(ir_tarval* tarval);

/**
 * Test if node is a Const
 * @returns 1 if the node is a Const node, 0 otherwise
 */
FIRM_API  int is_Const(const ir_node *node);


/** Returns tarval attribute of a Const node. */
FIRM_API  ir_tarval* get_Const_tarval(const ir_node *node);
/** Sets tarval attribute of a Const node. */
FIRM_API  void set_Const_tarval(ir_node *node, ir_tarval* tarval);
/** Const opcode */
FIRM_API  ir_op *op_Const;

/** Returns opcode for Const nodes. */
FIRM_API  ir_op *get_op_Const(void);

/** @} */

/**
 * @defgroup Conv Conv node
 *
 * Converts values between modes
 * @{
 */

/**
 * Input numbers for Conv node
 */
typedef enum {
	n_Conv_op, /**< operand */
	n_Conv_max = n_Conv_op
} n_Conv;

/**
 * Construct a Conv node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_op    op
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_rd_Conv(dbg_info *dbgi, ir_node *block, ir_node * irn_op, ir_mode * mode);

/**
 * Construct a Conv node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_op    op
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_r_Conv(ir_node *block, ir_node * irn_op, ir_mode * mode);

/**
 * Construct a Conv node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_op    op
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_d_Conv(dbg_info *dbgi, ir_node * irn_op, ir_mode * mode);

/**
 * Construct a Conv node.
 *
 * @param irn_op    op
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_Conv(ir_node * irn_op, ir_mode * mode);

/**
 * Test if node is a Conv
 * @returns 1 if the node is a Conv node, 0 otherwise
 */
FIRM_API  int is_Conv(const ir_node *node);

/** Returns op input of a Conv node. */
FIRM_API  ir_node *get_Conv_op(const ir_node *node);
/** Sets op input of a Conv node. */
FIRM_API  void set_Conv_op(ir_node *node, ir_node *op);
/** Conv opcode */
FIRM_API  ir_op *op_Conv;

/** Returns opcode for Conv nodes. */
FIRM_API  ir_op *get_op_Conv(void);

/** @} */

/**
 * @defgroup CopyB CopyB node
 *
 * Copies a block of memory with statically known size/type.
 * @{
 */

/**
 * Input numbers for CopyB node
 */
typedef enum {
	n_CopyB_mem, /**< memory dependency */
	n_CopyB_dst, /**< destination address */
	n_CopyB_src, /**< source address */
	n_CopyB_max = n_CopyB_src
} n_CopyB;

/**
 * Construct a CopyB node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_dst   dst
 * @param irn_src   src
 * @param type      type of copied data
 * @param flags     specifies volatility
*/
FIRM_API  ir_node *new_rd_CopyB(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_dst, ir_node * irn_src, ir_type* type, ir_cons_flags flags);

/**
 * Construct a CopyB node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_dst   dst
 * @param irn_src   src
 * @param type      type of copied data
 * @param flags     specifies volatility
*/
FIRM_API  ir_node *new_r_CopyB(ir_node *block, ir_node * irn_mem, ir_node * irn_dst, ir_node * irn_src, ir_type* type, ir_cons_flags flags);

/**
 * Construct a CopyB node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_mem   mem
 * @param irn_dst   dst
 * @param irn_src   src
 * @param type      type of copied data
 * @param flags     specifies volatility
*/
FIRM_API  ir_node *new_d_CopyB(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_dst, ir_node * irn_src, ir_type* type, ir_cons_flags flags);

/**
 * Construct a CopyB node.
 *
 * @param irn_mem   mem
 * @param irn_dst   dst
 * @param irn_src   src
 * @param type      type of copied data
 * @param flags     specifies volatility
*/
FIRM_API  ir_node *new_CopyB(ir_node * irn_mem, ir_node * irn_dst, ir_node * irn_src, ir_type* type, ir_cons_flags flags);

/**
 * Test if node is a CopyB
 * @returns 1 if the node is a CopyB node, 0 otherwise
 */
FIRM_API  int is_CopyB(const ir_node *node);

/** Returns mem input of a CopyB node. */
FIRM_API  ir_node *get_CopyB_mem(const ir_node *node);
/** Sets mem input of a CopyB node. */
FIRM_API  void set_CopyB_mem(ir_node *node, ir_node *mem);
/** Returns dst input of a CopyB node. */
FIRM_API  ir_node *get_CopyB_dst(const ir_node *node);
/** Sets dst input of a CopyB node. */
FIRM_API  void set_CopyB_dst(ir_node *node, ir_node *dst);
/** Returns src input of a CopyB node. */
FIRM_API  ir_node *get_CopyB_src(const ir_node *node);
/** Sets src input of a CopyB node. */
FIRM_API  void set_CopyB_src(ir_node *node, ir_node *src);

/** Returns type attribute of a CopyB node. */
FIRM_API  ir_type* get_CopyB_type(const ir_node *node);
/** Sets type attribute of a CopyB node. */
FIRM_API  void set_CopyB_type(ir_node *node, ir_type* type);

/** Returns volatility attribute of a CopyB node. */
FIRM_API  ir_volatility get_CopyB_volatility(const ir_node *node);
/** Sets volatility attribute of a CopyB node. */
FIRM_API  void set_CopyB_volatility(ir_node *node, ir_volatility volatility);
/** CopyB opcode */
FIRM_API  ir_op *op_CopyB;

/** Returns opcode for CopyB nodes. */
FIRM_API  ir_op *get_op_CopyB(void);

/** @} */

/**
 * @defgroup Deleted Deleted node
 *
 * Internal node which is temporary set to nodes which are already removed
from the graph.
 * @{
 */


/**
 * Test if node is a Deleted
 * @returns 1 if the node is a Deleted node, 0 otherwise
 */
FIRM_API  int is_Deleted(const ir_node *node);

/** Deleted opcode */
FIRM_API  ir_op *op_Deleted;

/** Returns opcode for Deleted nodes. */
FIRM_API  ir_op *get_op_Deleted(void);

/** @} */

/**
 * @defgroup Div Div node
 *
 * returns the quotient of its 2 operands
 * @{
 */

/**
 * Input numbers for Div node
 */
typedef enum {
	n_Div_mem, /**< memory dependency */
	n_Div_left, /**< first operand */
	n_Div_right, /**< second operand */
	n_Div_max = n_Div_right
} n_Div;

/**
 * Projection numbers for result of Div node (use for Proj nodes)
 */
typedef enum {
	pn_Div_M, /**< memory result */
	pn_Div_res, /**< result of computation */
	pn_Div_X_regular, /**< control flow when no exception occurs */
	pn_Div_X_except, /**< control flow when exception occurred */
	pn_Div_max = pn_Div_X_except
} pn_Div;

/**
 * Construct a Div node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_left  left
 * @param irn_right right
 * @param pinned    pinned state
*/
FIRM_API  ir_node *new_rd_Div(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned);

/**
 * Construct a Div node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_left  left
 * @param irn_right right
 * @param pinned    pinned state
*/
FIRM_API  ir_node *new_r_Div(ir_node *block, ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned);

/**
 * Construct a Div node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_mem   mem
 * @param irn_left  left
 * @param irn_right right
 * @param pinned    pinned state
*/
FIRM_API  ir_node *new_d_Div(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned);

/**
 * Construct a Div node.
 *
 * @param irn_mem   mem
 * @param irn_left  left
 * @param irn_right right
 * @param pinned    pinned state
*/
FIRM_API  ir_node *new_Div(ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned);

/**
 * Test if node is a Div
 * @returns 1 if the node is a Div node, 0 otherwise
 */
FIRM_API  int is_Div(const ir_node *node);

/** Returns mem input of a Div node. */
FIRM_API  ir_node *get_Div_mem(const ir_node *node);
/** Sets mem input of a Div node. */
FIRM_API  void set_Div_mem(ir_node *node, ir_node *mem);
/** Returns left input of a Div node. */
FIRM_API  ir_node *get_Div_left(const ir_node *node);
/** Sets left input of a Div node. */
FIRM_API  void set_Div_left(ir_node *node, ir_node *left);
/** Returns right input of a Div node. */
FIRM_API  ir_node *get_Div_right(const ir_node *node);
/** Sets right input of a Div node. */
FIRM_API  void set_Div_right(ir_node *node, ir_node *right);

/** Returns resmode attribute of a Div node. */
FIRM_API  ir_mode* get_Div_resmode(const ir_node *node);
/** Sets resmode attribute of a Div node. */
FIRM_API  void set_Div_resmode(ir_node *node, ir_mode* resmode);

/** Returns no_remainder attribute of a Div node. */
FIRM_API  int get_Div_no_remainder(const ir_node *node);
/** Sets no_remainder attribute of a Div node. */
FIRM_API  void set_Div_no_remainder(ir_node *node, int no_remainder);
/** Div opcode */
FIRM_API  ir_op *op_Div;

/** Returns opcode for Div nodes. */
FIRM_API  ir_op *get_op_Div(void);

/** @} */

/**
 * @defgroup Dummy Dummy node
 *
 * A placeholder value. This is used when constructing cyclic graphs where
you have cases where not all predecessors of a phi-node are known. Dummy
nodes are used for the unknown predecessors and replaced later.
 * @{
 */

/**
 * Construct a Dummy node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irg       The IR graph the node belongs to.
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_rd_Dummy(dbg_info *dbgi, ir_graph *irg, ir_mode * mode);

/**
 * Construct a Dummy node.
 *
 * @param irg       The IR graph the node belongs to.
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_r_Dummy(ir_graph *irg, ir_mode * mode);

/**
 * Construct a Dummy node.
 *
 * @param dbgi      A pointer to debug information.
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_d_Dummy(dbg_info *dbgi, ir_mode * mode);

/**
 * Construct a Dummy node.
 *
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_Dummy(ir_mode * mode);

/**
 * Test if node is a Dummy
 * @returns 1 if the node is a Dummy node, 0 otherwise
 */
FIRM_API  int is_Dummy(const ir_node *node);

/** Dummy opcode */
FIRM_API  ir_op *op_Dummy;

/** Returns opcode for Dummy nodes. */
FIRM_API  ir_op *get_op_Dummy(void);

/** @} */

/**
 * @defgroup End End node
 *
 * Last node of a graph. It references nodes in endless loops (so called
keepalive edges)
 * @{
 */

/**
 * Construct an End node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irg       The IR graph the node belongs to.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_rd_End(dbg_info *dbgi, ir_graph *irg, int arity, ir_node *const * in);

/**
 * Construct an End node.
 *
 * @param irg       The IR graph the node belongs to.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_r_End(ir_graph *irg, int arity, ir_node *const * in);

/**
 * Construct an End node.
 *
 * @param dbgi      A pointer to debug information.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_d_End(dbg_info *dbgi, int arity, ir_node *const * in);

/**
 * Construct an End node.
 *
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_End(int arity, ir_node *const * in);

/**
 * Test if node is a End
 * @returns 1 if the node is a End node, 0 otherwise
 */
FIRM_API  int is_End(const ir_node *node);

/** Get the number of End keepalives. */
FIRM_API  int get_End_n_keepalives(ir_node const *node);
/** Get the End keepalive with index @p pos. */
FIRM_API  ir_node *get_End_keepalive(ir_node const *node, int pos);
/** Set the End keepalive with index @p pos. */
FIRM_API  void set_End_keepalive(ir_node *node, int pos, ir_node *keepalive);
/** Get an array of all End keepalives. */
ir_node **get_End_keepalive_arr(ir_node *node);
/** End opcode */
FIRM_API  ir_op *op_End;

/** Returns opcode for End nodes. */
FIRM_API  ir_op *get_op_End(void);

/** @} */

/**
 * @defgroup Eor Eor node
 *
 * returns the result of a bitwise exclusive or operation of its operands.

This is also known as the Xor operation.
 * @{
 */

/**
 * Input numbers for Eor node
 */
typedef enum {
	n_Eor_left, /**< first operand */
	n_Eor_right, /**< second operand */
	n_Eor_max = n_Eor_right
} n_Eor;

/**
 * Construct an Eor node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_rd_Eor(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct an Eor node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_r_Eor(ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct an Eor node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_d_Eor(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct an Eor node.
 *
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_Eor(ir_node * irn_left, ir_node * irn_right);

/**
 * Test if node is a Eor
 * @returns 1 if the node is a Eor node, 0 otherwise
 */
FIRM_API  int is_Eor(const ir_node *node);

/** Returns left input of an Eor node. */
FIRM_API  ir_node *get_Eor_left(const ir_node *node);
/** Sets left input of an Eor node. */
FIRM_API  void set_Eor_left(ir_node *node, ir_node *left);
/** Returns right input of an Eor node. */
FIRM_API  ir_node *get_Eor_right(const ir_node *node);
/** Sets right input of an Eor node. */
FIRM_API  void set_Eor_right(ir_node *node, ir_node *right);
/** Eor opcode */
FIRM_API  ir_op *op_Eor;

/** Returns opcode for Eor nodes. */
FIRM_API  ir_op *get_op_Eor(void);

/** @} */

/**
 * @defgroup Free Free node
 *
 * Frees a block of memory previously allocated by an Alloc node
 * @{
 */

/**
 * Input numbers for Free node
 */
typedef enum {
	n_Free_mem, /**< memory dependency */
	n_Free_ptr, /**< pointer to the object to free */
	n_Free_max = n_Free_ptr
} n_Free;

/**
 * Construct a Free node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_ptr   ptr
*/
FIRM_API  ir_node *new_rd_Free(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_ptr);

/**
 * Construct a Free node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_ptr   ptr
*/
FIRM_API  ir_node *new_r_Free(ir_node *block, ir_node * irn_mem, ir_node * irn_ptr);

/**
 * Construct a Free node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_mem   mem
 * @param irn_ptr   ptr
*/
FIRM_API  ir_node *new_d_Free(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_ptr);

/**
 * Construct a Free node.
 *
 * @param irn_mem   mem
 * @param irn_ptr   ptr
*/
FIRM_API  ir_node *new_Free(ir_node * irn_mem, ir_node * irn_ptr);

/**
 * Test if node is a Free
 * @returns 1 if the node is a Free node, 0 otherwise
 */
FIRM_API  int is_Free(const ir_node *node);

/** Returns mem input of a Free node. */
FIRM_API  ir_node *get_Free_mem(const ir_node *node);
/** Sets mem input of a Free node. */
FIRM_API  void set_Free_mem(ir_node *node, ir_node *mem);
/** Returns ptr input of a Free node. */
FIRM_API  ir_node *get_Free_ptr(const ir_node *node);
/** Sets ptr input of a Free node. */
FIRM_API  void set_Free_ptr(ir_node *node, ir_node *ptr);
/** Free opcode */
FIRM_API  ir_op *op_Free;

/** Returns opcode for Free nodes. */
FIRM_API  ir_op *get_op_Free(void);

/** @} */

/**
 * @defgroup IJmp IJmp node
 *
 * Jumps to the code in its argument. The code has to be in the same
function and the destination must be one of the blocks reachable
by the tuple results
 * @{
 */

/**
 * Input numbers for IJmp node
 */
typedef enum {
	n_IJmp_target, /**< target address of the jump */
	n_IJmp_max = n_IJmp_target
} n_IJmp;

/**
 * Construct an IJmp node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_target target
*/
FIRM_API  ir_node *new_rd_IJmp(dbg_info *dbgi, ir_node *block, ir_node * irn_target);

/**
 * Construct an IJmp node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_target target
*/
FIRM_API  ir_node *new_r_IJmp(ir_node *block, ir_node * irn_target);

/**
 * Construct an IJmp node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_target target
*/
FIRM_API  ir_node *new_d_IJmp(dbg_info *dbgi, ir_node * irn_target);

/**
 * Construct an IJmp node.
 *
 * @param irn_target target
*/
FIRM_API  ir_node *new_IJmp(ir_node * irn_target);

/**
 * Test if node is a IJmp
 * @returns 1 if the node is a IJmp node, 0 otherwise
 */
FIRM_API  int is_IJmp(const ir_node *node);

/** Returns target input of an IJmp node. */
FIRM_API  ir_node *get_IJmp_target(const ir_node *node);
/** Sets target input of an IJmp node. */
FIRM_API  void set_IJmp_target(ir_node *node, ir_node *target);
/** IJmp opcode */
FIRM_API  ir_op *op_IJmp;

/** Returns opcode for IJmp nodes. */
FIRM_API  ir_op *get_op_IJmp(void);

/** @} */

/**
 * @defgroup Id Id node
 *
 * Returns its operand unchanged.

This is mainly used when exchanging nodes. Usually you shouldn't see Id
nodes since the getters/setters for node inputs skip them automatically.
 * @{
 */

/**
 * Input numbers for Id node
 */
typedef enum {
	n_Id_pred, /**< the value which is returned unchanged */
	n_Id_max = n_Id_pred
} n_Id;


/**
 * Test if node is a Id
 * @returns 1 if the node is a Id node, 0 otherwise
 */
FIRM_API  int is_Id(const ir_node *node);

/** Returns pred input of an Id node. */
FIRM_API  ir_node *get_Id_pred(const ir_node *node);
/** Sets pred input of an Id node. */
FIRM_API  void set_Id_pred(ir_node *node, ir_node *pred);
/** Id opcode */
FIRM_API  ir_op *op_Id;

/** Returns opcode for Id nodes. */
FIRM_API  ir_op *get_op_Id(void);

/** @} */

/**
 * @defgroup Jmp Jmp node
 *
 * Jumps to the block connected through the out-value
 * @{
 */

/**
 * Construct a Jmp node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
*/
FIRM_API  ir_node *new_rd_Jmp(dbg_info *dbgi, ir_node *block);

/**
 * Construct a Jmp node.
 *
 * @param block     The IR block the node belongs to.
*/
FIRM_API  ir_node *new_r_Jmp(ir_node *block);

/**
 * Construct a Jmp node.
 *
 * @param dbgi      A pointer to debug information.
*/
FIRM_API  ir_node *new_d_Jmp(dbg_info *dbgi);

/**
 * Construct a Jmp node.
 *
*/
FIRM_API  ir_node *new_Jmp(void);

/**
 * Test if node is a Jmp
 * @returns 1 if the node is a Jmp node, 0 otherwise
 */
FIRM_API  int is_Jmp(const ir_node *node);

/** Jmp opcode */
FIRM_API  ir_op *op_Jmp;

/** Returns opcode for Jmp nodes. */
FIRM_API  ir_op *get_op_Jmp(void);

/** @} */

/**
 * @defgroup Load Load node
 *
 * Loads a value from memory (heap or stack).
 * @{
 */

/**
 * Input numbers for Load node
 */
typedef enum {
	n_Load_mem, /**< memory dependency */
	n_Load_ptr, /**< address to load from */
	n_Load_max = n_Load_ptr
} n_Load;

/**
 * Projection numbers for result of Load node (use for Proj nodes)
 */
typedef enum {
	pn_Load_M, /**< memory result */
	pn_Load_res, /**< result of load operation */
	pn_Load_X_regular, /**< control flow when no exception occurs */
	pn_Load_X_except, /**< control flow when exception occurred */
	pn_Load_max = pn_Load_X_except
} pn_Load;

/**
 * Construct a Load node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_ptr   ptr
 * @param mode      mode of the value to be loaded
 * @param type      The type of the object which is stored at ptr (need not match with mode)
 * @param flags     specifies alignment, volatility and pin state
*/
FIRM_API  ir_node *new_rd_Load(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_ptr, ir_mode* mode, ir_type* type, ir_cons_flags flags);

/**
 * Construct a Load node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_ptr   ptr
 * @param mode      mode of the value to be loaded
 * @param type      The type of the object which is stored at ptr (need not match with mode)
 * @param flags     specifies alignment, volatility and pin state
*/
FIRM_API  ir_node *new_r_Load(ir_node *block, ir_node * irn_mem, ir_node * irn_ptr, ir_mode* mode, ir_type* type, ir_cons_flags flags);

/**
 * Construct a Load node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_mem   mem
 * @param irn_ptr   ptr
 * @param mode      mode of the value to be loaded
 * @param type      The type of the object which is stored at ptr (need not match with mode)
 * @param flags     specifies alignment, volatility and pin state
*/
FIRM_API  ir_node *new_d_Load(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_ptr, ir_mode* mode, ir_type* type, ir_cons_flags flags);

/**
 * Construct a Load node.
 *
 * @param irn_mem   mem
 * @param irn_ptr   ptr
 * @param mode      mode of the value to be loaded
 * @param type      The type of the object which is stored at ptr (need not match with mode)
 * @param flags     specifies alignment, volatility and pin state
*/
FIRM_API  ir_node *new_Load(ir_node * irn_mem, ir_node * irn_ptr, ir_mode* mode, ir_type* type, ir_cons_flags flags);

/**
 * Test if node is a Load
 * @returns 1 if the node is a Load node, 0 otherwise
 */
FIRM_API  int is_Load(const ir_node *node);

/** Returns mem input of a Load node. */
FIRM_API  ir_node *get_Load_mem(const ir_node *node);
/** Sets mem input of a Load node. */
FIRM_API  void set_Load_mem(ir_node *node, ir_node *mem);
/** Returns ptr input of a Load node. */
FIRM_API  ir_node *get_Load_ptr(const ir_node *node);
/** Sets ptr input of a Load node. */
FIRM_API  void set_Load_ptr(ir_node *node, ir_node *ptr);

/** Returns mode attribute of a Load node. */
FIRM_API  ir_mode* get_Load_mode(const ir_node *node);
/** Sets mode attribute of a Load node. */
FIRM_API  void set_Load_mode(ir_node *node, ir_mode* mode);

/** Returns type attribute of a Load node. */
FIRM_API  ir_type* get_Load_type(const ir_node *node);
/** Sets type attribute of a Load node. */
FIRM_API  void set_Load_type(ir_node *node, ir_type* type);

/** Returns volatility attribute of a Load node. */
FIRM_API  ir_volatility get_Load_volatility(const ir_node *node);
/** Sets volatility attribute of a Load node. */
FIRM_API  void set_Load_volatility(ir_node *node, ir_volatility volatility);

/** Returns unaligned attribute of a Load node. */
FIRM_API  ir_align get_Load_unaligned(const ir_node *node);
/** Sets unaligned attribute of a Load node. */
FIRM_API  void set_Load_unaligned(ir_node *node, ir_align unaligned);
/** Load opcode */
FIRM_API  ir_op *op_Load;

/** Returns opcode for Load nodes. */
FIRM_API  ir_op *get_op_Load(void);

/** @} */

/**
 * @defgroup Member Member node
 *
 * Computes the address of a compound type member given the base address
of an instance of the compound type.

A Member node must only produce a NULL pointer if the ptr input is NULL.
 * @{
 */

/**
 * Input numbers for Member node
 */
typedef enum {
	n_Member_ptr, /**< pointer to object to select from */
	n_Member_max = n_Member_ptr
} n_Member;

/**
 * Construct a Member node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_ptr   ptr
 * @param entity    entity which is selected
*/
FIRM_API  ir_node *new_rd_Member(dbg_info *dbgi, ir_node *block, ir_node * irn_ptr, ir_entity* entity);

/**
 * Construct a Member node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_ptr   ptr
 * @param entity    entity which is selected
*/
FIRM_API  ir_node *new_r_Member(ir_node *block, ir_node * irn_ptr, ir_entity* entity);

/**
 * Construct a Member node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_ptr   ptr
 * @param entity    entity which is selected
*/
FIRM_API  ir_node *new_d_Member(dbg_info *dbgi, ir_node * irn_ptr, ir_entity* entity);

/**
 * Construct a Member node.
 *
 * @param irn_ptr   ptr
 * @param entity    entity which is selected
*/
FIRM_API  ir_node *new_Member(ir_node * irn_ptr, ir_entity* entity);

/**
 * Test if node is a Member
 * @returns 1 if the node is a Member node, 0 otherwise
 */
FIRM_API  int is_Member(const ir_node *node);

/** Returns ptr input of a Member node. */
FIRM_API  ir_node *get_Member_ptr(const ir_node *node);
/** Sets ptr input of a Member node. */
FIRM_API  void set_Member_ptr(ir_node *node, ir_node *ptr);

/** Returns entity attribute of a Member node. */
FIRM_API  ir_entity* get_Member_entity(const ir_node *node);
/** Sets entity attribute of a Member node. */
FIRM_API  void set_Member_entity(ir_node *node, ir_entity* entity);
/** Member opcode */
FIRM_API  ir_op *op_Member;

/** Returns opcode for Member nodes. */
FIRM_API  ir_op *get_op_Member(void);

/** @} */

/**
 * @defgroup Minus Minus node
 *
 * returns the additive inverse of its operand
 * @{
 */

/**
 * Input numbers for Minus node
 */
typedef enum {
	n_Minus_op, /**< operand */
	n_Minus_max = n_Minus_op
} n_Minus;

/**
 * Construct a Minus node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_op    op
*/
FIRM_API  ir_node *new_rd_Minus(dbg_info *dbgi, ir_node *block, ir_node * irn_op);

/**
 * Construct a Minus node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_op    op
*/
FIRM_API  ir_node *new_r_Minus(ir_node *block, ir_node * irn_op);

/**
 * Construct a Minus node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_op    op
*/
FIRM_API  ir_node *new_d_Minus(dbg_info *dbgi, ir_node * irn_op);

/**
 * Construct a Minus node.
 *
 * @param irn_op    op
*/
FIRM_API  ir_node *new_Minus(ir_node * irn_op);

/**
 * Test if node is a Minus
 * @returns 1 if the node is a Minus node, 0 otherwise
 */
FIRM_API  int is_Minus(const ir_node *node);

/** Returns op input of a Minus node. */
FIRM_API  ir_node *get_Minus_op(const ir_node *node);
/** Sets op input of a Minus node. */
FIRM_API  void set_Minus_op(ir_node *node, ir_node *op);
/** Minus opcode */
FIRM_API  ir_op *op_Minus;

/** Returns opcode for Minus nodes. */
FIRM_API  ir_op *get_op_Minus(void);

/** @} */

/**
 * @defgroup Mod Mod node
 *
 * returns the remainder of its operands from an implied division.

Examples:

* mod(5,3)   produces 2
* mod(5,-3)  produces 2
* mod(-5,3)  produces -2
* mod(-5,-3) produces -2
 * @{
 */

/**
 * Input numbers for Mod node
 */
typedef enum {
	n_Mod_mem, /**< memory dependency */
	n_Mod_left, /**< first operand */
	n_Mod_right, /**< second operand */
	n_Mod_max = n_Mod_right
} n_Mod;

/**
 * Projection numbers for result of Mod node (use for Proj nodes)
 */
typedef enum {
	pn_Mod_M, /**< memory result */
	pn_Mod_res, /**< result of computation */
	pn_Mod_X_regular, /**< control flow when no exception occurs */
	pn_Mod_X_except, /**< control flow when exception occurred */
	pn_Mod_max = pn_Mod_X_except
} pn_Mod;

/**
 * Construct a Mod node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_left  left
 * @param irn_right right
 * @param pinned    pinned state
*/
FIRM_API  ir_node *new_rd_Mod(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned);

/**
 * Construct a Mod node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_left  left
 * @param irn_right right
 * @param pinned    pinned state
*/
FIRM_API  ir_node *new_r_Mod(ir_node *block, ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned);

/**
 * Construct a Mod node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_mem   mem
 * @param irn_left  left
 * @param irn_right right
 * @param pinned    pinned state
*/
FIRM_API  ir_node *new_d_Mod(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned);

/**
 * Construct a Mod node.
 *
 * @param irn_mem   mem
 * @param irn_left  left
 * @param irn_right right
 * @param pinned    pinned state
*/
FIRM_API  ir_node *new_Mod(ir_node * irn_mem, ir_node * irn_left, ir_node * irn_right, int pinned);

/**
 * Test if node is a Mod
 * @returns 1 if the node is a Mod node, 0 otherwise
 */
FIRM_API  int is_Mod(const ir_node *node);

/** Returns mem input of a Mod node. */
FIRM_API  ir_node *get_Mod_mem(const ir_node *node);
/** Sets mem input of a Mod node. */
FIRM_API  void set_Mod_mem(ir_node *node, ir_node *mem);
/** Returns left input of a Mod node. */
FIRM_API  ir_node *get_Mod_left(const ir_node *node);
/** Sets left input of a Mod node. */
FIRM_API  void set_Mod_left(ir_node *node, ir_node *left);
/** Returns right input of a Mod node. */
FIRM_API  ir_node *get_Mod_right(const ir_node *node);
/** Sets right input of a Mod node. */
FIRM_API  void set_Mod_right(ir_node *node, ir_node *right);

/** Returns resmode attribute of a Mod node. */
FIRM_API  ir_mode* get_Mod_resmode(const ir_node *node);
/** Sets resmode attribute of a Mod node. */
FIRM_API  void set_Mod_resmode(ir_node *node, ir_mode* resmode);
/** Mod opcode */
FIRM_API  ir_op *op_Mod;

/** Returns opcode for Mod nodes. */
FIRM_API  ir_op *get_op_Mod(void);

/** @} */

/**
 * @defgroup Mul Mul node
 *
 * returns the product of its operands
 * @{
 */

/**
 * Input numbers for Mul node
 */
typedef enum {
	n_Mul_left, /**< first operand */
	n_Mul_right, /**< second operand */
	n_Mul_max = n_Mul_right
} n_Mul;

/**
 * Construct a Mul node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_rd_Mul(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Mul node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_r_Mul(ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Mul node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_d_Mul(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Mul node.
 *
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_Mul(ir_node * irn_left, ir_node * irn_right);

/**
 * Test if node is a Mul
 * @returns 1 if the node is a Mul node, 0 otherwise
 */
FIRM_API  int is_Mul(const ir_node *node);

/** Returns left input of a Mul node. */
FIRM_API  ir_node *get_Mul_left(const ir_node *node);
/** Sets left input of a Mul node. */
FIRM_API  void set_Mul_left(ir_node *node, ir_node *left);
/** Returns right input of a Mul node. */
FIRM_API  ir_node *get_Mul_right(const ir_node *node);
/** Sets right input of a Mul node. */
FIRM_API  void set_Mul_right(ir_node *node, ir_node *right);
/** Mul opcode */
FIRM_API  ir_op *op_Mul;

/** Returns opcode for Mul nodes. */
FIRM_API  ir_op *get_op_Mul(void);

/** @} */

/**
 * @defgroup Mulh Mulh node
 *
 * returns the upper word of the product of its operands (the part which
would not fit into the result mode of a normal Mul anymore)
 * @{
 */

/**
 * Input numbers for Mulh node
 */
typedef enum {
	n_Mulh_left, /**< first operand */
	n_Mulh_right, /**< second operand */
	n_Mulh_max = n_Mulh_right
} n_Mulh;

/**
 * Construct a Mulh node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_rd_Mulh(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Mulh node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_r_Mulh(ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Mulh node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_d_Mulh(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Mulh node.
 *
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_Mulh(ir_node * irn_left, ir_node * irn_right);

/**
 * Test if node is a Mulh
 * @returns 1 if the node is a Mulh node, 0 otherwise
 */
FIRM_API  int is_Mulh(const ir_node *node);

/** Returns left input of a Mulh node. */
FIRM_API  ir_node *get_Mulh_left(const ir_node *node);
/** Sets left input of a Mulh node. */
FIRM_API  void set_Mulh_left(ir_node *node, ir_node *left);
/** Returns right input of a Mulh node. */
FIRM_API  ir_node *get_Mulh_right(const ir_node *node);
/** Sets right input of a Mulh node. */
FIRM_API  void set_Mulh_right(ir_node *node, ir_node *right);
/** Mulh opcode */
FIRM_API  ir_op *op_Mulh;

/** Returns opcode for Mulh nodes. */
FIRM_API  ir_op *get_op_Mulh(void);

/** @} */

/**
 * @defgroup Mux Mux node
 *
 * returns the false or true operand depending on the value of the sel
operand
 * @{
 */

/**
 * Input numbers for Mux node
 */
typedef enum {
	n_Mux_sel, /**< value making the output selection */
	n_Mux_false, /**< selected if sel input is false */
	n_Mux_true, /**< selected if sel input is true */
	n_Mux_max = n_Mux_true
} n_Mux;

/**
 * Construct a Mux node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_sel   sel
 * @param irn_false false
 * @param irn_true  true
*/
FIRM_API  ir_node *new_rd_Mux(dbg_info *dbgi, ir_node *block, ir_node * irn_sel, ir_node * irn_false, ir_node * irn_true);

/**
 * Construct a Mux node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_sel   sel
 * @param irn_false false
 * @param irn_true  true
*/
FIRM_API  ir_node *new_r_Mux(ir_node *block, ir_node * irn_sel, ir_node * irn_false, ir_node * irn_true);

/**
 * Construct a Mux node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_sel   sel
 * @param irn_false false
 * @param irn_true  true
*/
FIRM_API  ir_node *new_d_Mux(dbg_info *dbgi, ir_node * irn_sel, ir_node * irn_false, ir_node * irn_true);

/**
 * Construct a Mux node.
 *
 * @param irn_sel   sel
 * @param irn_false false
 * @param irn_true  true
*/
FIRM_API  ir_node *new_Mux(ir_node * irn_sel, ir_node * irn_false, ir_node * irn_true);

/**
 * Test if node is a Mux
 * @returns 1 if the node is a Mux node, 0 otherwise
 */
FIRM_API  int is_Mux(const ir_node *node);

/** Returns sel input of a Mux node. */
FIRM_API  ir_node *get_Mux_sel(const ir_node *node);
/** Sets sel input of a Mux node. */
FIRM_API  void set_Mux_sel(ir_node *node, ir_node *sel);
/** Returns false input of a Mux node. */
FIRM_API  ir_node *get_Mux_false(const ir_node *node);
/** Sets false input of a Mux node. */
FIRM_API  void set_Mux_false(ir_node *node, ir_node *false_);
/** Returns true input of a Mux node. */
FIRM_API  ir_node *get_Mux_true(const ir_node *node);
/** Sets true input of a Mux node. */
FIRM_API  void set_Mux_true(ir_node *node, ir_node *true_);
/** Mux opcode */
FIRM_API  ir_op *op_Mux;

/** Returns opcode for Mux nodes. */
FIRM_API  ir_op *get_op_Mux(void);

/** @} */

/**
 * @defgroup NoMem NoMem node
 *
 * Placeholder node for cases where you don't need any memory input
 * @{
 */

/**
 * Construct a NoMem node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irg       The IR graph the node belongs to.
*/
FIRM_API  ir_node *new_rd_NoMem(dbg_info *dbgi, ir_graph *irg);

/**
 * Construct a NoMem node.
 *
 * @param irg       The IR graph the node belongs to.
*/
FIRM_API  ir_node *new_r_NoMem(ir_graph *irg);

/**
 * Construct a NoMem node.
 *
 * @param dbgi      A pointer to debug information.
*/
FIRM_API  ir_node *new_d_NoMem(dbg_info *dbgi);

/**
 * Construct a NoMem node.
 *
*/
FIRM_API  ir_node *new_NoMem(void);

/**
 * Test if node is a NoMem
 * @returns 1 if the node is a NoMem node, 0 otherwise
 */
FIRM_API  int is_NoMem(const ir_node *node);

/** NoMem opcode */
FIRM_API  ir_op *op_NoMem;

/** Returns opcode for NoMem nodes. */
FIRM_API  ir_op *get_op_NoMem(void);

/** @} */

/**
 * @defgroup Not Not node
 *
 * returns the bitwise complement of a value. Works for boolean values, too.
 * @{
 */

/**
 * Input numbers for Not node
 */
typedef enum {
	n_Not_op, /**< operand */
	n_Not_max = n_Not_op
} n_Not;

/**
 * Construct a Not node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_op    op
*/
FIRM_API  ir_node *new_rd_Not(dbg_info *dbgi, ir_node *block, ir_node * irn_op);

/**
 * Construct a Not node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_op    op
*/
FIRM_API  ir_node *new_r_Not(ir_node *block, ir_node * irn_op);

/**
 * Construct a Not node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_op    op
*/
FIRM_API  ir_node *new_d_Not(dbg_info *dbgi, ir_node * irn_op);

/**
 * Construct a Not node.
 *
 * @param irn_op    op
*/
FIRM_API  ir_node *new_Not(ir_node * irn_op);

/**
 * Test if node is a Not
 * @returns 1 if the node is a Not node, 0 otherwise
 */
FIRM_API  int is_Not(const ir_node *node);

/** Returns op input of a Not node. */
FIRM_API  ir_node *get_Not_op(const ir_node *node);
/** Sets op input of a Not node. */
FIRM_API  void set_Not_op(ir_node *node, ir_node *op);
/** Not opcode */
FIRM_API  ir_op *op_Not;

/** Returns opcode for Not nodes. */
FIRM_API  ir_op *get_op_Not(void);

/** @} */

/**
 * @defgroup Offset Offset node
 *
 * Symbolic constant that represents the offset of an entity in its owner type.
 * @{
 */

/**
 * Construct an Offset node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irg       The IR graph the node belongs to.
 * @param mode      mode of the operations result
 * @param entity    entity to operate on
*/
FIRM_API  ir_node *new_rd_Offset(dbg_info *dbgi, ir_graph *irg, ir_mode * mode, ir_entity* entity);

/**
 * Construct an Offset node.
 *
 * @param irg       The IR graph the node belongs to.
 * @param mode      mode of the operations result
 * @param entity    entity to operate on
*/
FIRM_API  ir_node *new_r_Offset(ir_graph *irg, ir_mode * mode, ir_entity* entity);

/**
 * Construct an Offset node.
 *
 * @param dbgi      A pointer to debug information.
 * @param mode      mode of the operations result
 * @param entity    entity to operate on
*/
FIRM_API  ir_node *new_d_Offset(dbg_info *dbgi, ir_mode * mode, ir_entity* entity);

/**
 * Construct an Offset node.
 *
 * @param mode      mode of the operations result
 * @param entity    entity to operate on
*/
FIRM_API  ir_node *new_Offset(ir_mode * mode, ir_entity* entity);

/**
 * Test if node is a Offset
 * @returns 1 if the node is a Offset node, 0 otherwise
 */
FIRM_API  int is_Offset(const ir_node *node);


/** Returns entity attribute of an Offset node. */
FIRM_API  ir_entity* get_Offset_entity(const ir_node *node);
/** Sets entity attribute of an Offset node. */
FIRM_API  void set_Offset_entity(ir_node *node, ir_entity* entity);
/** Offset opcode */
FIRM_API  ir_op *op_Offset;

/** Returns opcode for Offset nodes. */
FIRM_API  ir_op *get_op_Offset(void);

/** @} */

/**
 * @defgroup Or Or node
 *
 * returns the result of a bitwise or operation of its operands
 * @{
 */

/**
 * Input numbers for Or node
 */
typedef enum {
	n_Or_left, /**< first operand */
	n_Or_right, /**< second operand */
	n_Or_max = n_Or_right
} n_Or;

/**
 * Construct an Or node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_rd_Or(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct an Or node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_r_Or(ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct an Or node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_d_Or(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct an Or node.
 *
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_Or(ir_node * irn_left, ir_node * irn_right);

/**
 * Test if node is a Or
 * @returns 1 if the node is a Or node, 0 otherwise
 */
FIRM_API  int is_Or(const ir_node *node);

/** Returns left input of an Or node. */
FIRM_API  ir_node *get_Or_left(const ir_node *node);
/** Sets left input of an Or node. */
FIRM_API  void set_Or_left(ir_node *node, ir_node *left);
/** Returns right input of an Or node. */
FIRM_API  ir_node *get_Or_right(const ir_node *node);
/** Sets right input of an Or node. */
FIRM_API  void set_Or_right(ir_node *node, ir_node *right);
/** Or opcode */
FIRM_API  ir_op *op_Or;

/** Returns opcode for Or nodes. */
FIRM_API  ir_op *get_op_Or(void);

/** @} */

/**
 * @defgroup Phi Phi node
 *
 * Choose a value based on control flow. A phi node has 1 input for each
predecessor of its block. If a block is entered from its nth predecessor
all phi nodes produce their nth input as result.
 * @{
 */

/**
 * Construct a Phi node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_rd_Phi(dbg_info *dbgi, ir_node *block, int arity, ir_node *const * in, ir_mode * mode);

/**
 * Construct a Phi node.
 *
 * @param block     The IR block the node belongs to.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_r_Phi(ir_node *block, int arity, ir_node *const * in, ir_mode * mode);

/**
 * Construct a Phi node.
 *
 * @param dbgi      A pointer to debug information.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_d_Phi(dbg_info *dbgi, int arity, ir_node *const * in, ir_mode * mode);

/**
 * Construct a Phi node.
 *
 * @param arity     size of additional inputs array
 * @param in        additional inputs
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_Phi(int arity, ir_node *const * in, ir_mode * mode);

/**
 * Test if node is a Phi
 * @returns 1 if the node is a Phi node, 0 otherwise
 */
FIRM_API  int is_Phi(const ir_node *node);

/** Get the number of Phi preds. */
FIRM_API  int get_Phi_n_preds(ir_node const *node);
/** Get the Phi pred with index @p pos. */
FIRM_API  ir_node *get_Phi_pred(ir_node const *node, int pos);
/** Set the Phi pred with index @p pos. */
FIRM_API  void set_Phi_pred(ir_node *node, int pos, ir_node *pred);
/** Get an array of all Phi preds. */
ir_node **get_Phi_pred_arr(ir_node *node);

/** Returns loop attribute of a Phi node. */
FIRM_API  int get_Phi_loop(const ir_node *node);
/** Sets loop attribute of a Phi node. */
FIRM_API  void set_Phi_loop(ir_node *node, int loop);
/** Phi opcode */
FIRM_API  ir_op *op_Phi;

/** Returns opcode for Phi nodes. */
FIRM_API  ir_op *get_op_Phi(void);

/** @} */

/**
 * @defgroup Pin Pin node
 *
 * Pin the value of the node node in the current block. No users of the Pin
node can float above the Block of the Pin. The node cannot float behind
this block. Often used to Pin the NoMem node.
 * @{
 */

/**
 * Input numbers for Pin node
 */
typedef enum {
	n_Pin_op, /**< value which is pinned */
	n_Pin_max = n_Pin_op
} n_Pin;

/**
 * Construct a Pin node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_op    op
*/
FIRM_API  ir_node *new_rd_Pin(dbg_info *dbgi, ir_node *block, ir_node * irn_op);

/**
 * Construct a Pin node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_op    op
*/
FIRM_API  ir_node *new_r_Pin(ir_node *block, ir_node * irn_op);

/**
 * Construct a Pin node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_op    op
*/
FIRM_API  ir_node *new_d_Pin(dbg_info *dbgi, ir_node * irn_op);

/**
 * Construct a Pin node.
 *
 * @param irn_op    op
*/
FIRM_API  ir_node *new_Pin(ir_node * irn_op);

/**
 * Test if node is a Pin
 * @returns 1 if the node is a Pin node, 0 otherwise
 */
FIRM_API  int is_Pin(const ir_node *node);

/** Returns op input of a Pin node. */
FIRM_API  ir_node *get_Pin_op(const ir_node *node);
/** Sets op input of a Pin node. */
FIRM_API  void set_Pin_op(ir_node *node, ir_node *op);
/** Pin opcode */
FIRM_API  ir_op *op_Pin;

/** Returns opcode for Pin nodes. */
FIRM_API  ir_op *get_op_Pin(void);

/** @} */

/**
 * @defgroup Proj Proj node
 *
 * returns an entry of a tuple value
 * @{
 */

/**
 * Input numbers for Proj node
 */
typedef enum {
	n_Proj_pred, /**< the tuple value from which a part is extracted */
	n_Proj_max = n_Proj_pred
} n_Proj;

/**
 * Construct a Proj node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_pred  pred
 * @param mode      mode of the operations result
 * @param num       number of tuple component to be extracted
*/
FIRM_API  ir_node *new_rd_Proj(dbg_info *dbgi, ir_node * irn_pred, ir_mode * mode, unsigned num);

/**
 * Construct a Proj node.
 *
 * @param irn_pred  pred
 * @param mode      mode of the operations result
 * @param num       number of tuple component to be extracted
*/
FIRM_API  ir_node *new_r_Proj(ir_node * irn_pred, ir_mode * mode, unsigned num);

/**
 * Construct a Proj node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_pred  pred
 * @param mode      mode of the operations result
 * @param num       number of tuple component to be extracted
*/
FIRM_API  ir_node *new_d_Proj(dbg_info *dbgi, ir_node * irn_pred, ir_mode * mode, unsigned num);

/**
 * Construct a Proj node.
 *
 * @param irn_pred  pred
 * @param mode      mode of the operations result
 * @param num       number of tuple component to be extracted
*/
FIRM_API  ir_node *new_Proj(ir_node * irn_pred, ir_mode * mode, unsigned num);

/**
 * Test if node is a Proj
 * @returns 1 if the node is a Proj node, 0 otherwise
 */
FIRM_API  int is_Proj(const ir_node *node);

/** Returns pred input of a Proj node. */
FIRM_API  ir_node *get_Proj_pred(const ir_node *node);
/** Sets pred input of a Proj node. */
FIRM_API  void set_Proj_pred(ir_node *node, ir_node *pred);

/** Returns num attribute of a Proj node. */
FIRM_API  unsigned get_Proj_num(const ir_node *node);
/** Sets num attribute of a Proj node. */
FIRM_API  void set_Proj_num(ir_node *node, unsigned num);
/** Proj opcode */
FIRM_API  ir_op *op_Proj;

/** Returns opcode for Proj nodes. */
FIRM_API  ir_op *get_op_Proj(void);

/** @} */

/**
 * @defgroup Raise Raise node
 *
 * Raises an exception. Unconditional change of control flow. Writes an
explicit Except variable to memory to pass it to the exception handler.
Must be lowered to a Call to a runtime check function.
 * @{
 */

/**
 * Input numbers for Raise node
 */
typedef enum {
	n_Raise_mem, /**< memory dependency */
	n_Raise_exo_ptr, /**< pointer to exception object to be thrown */
	n_Raise_max = n_Raise_exo_ptr
} n_Raise;

/**
 * Projection numbers for result of Raise node (use for Proj nodes)
 */
typedef enum {
	pn_Raise_M, /**< memory result */
	pn_Raise_X, /**< control flow to exception handler */
	pn_Raise_max = pn_Raise_X
} pn_Raise;

/**
 * Construct a Raise node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_exo_ptr exo_ptr
*/
FIRM_API  ir_node *new_rd_Raise(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_exo_ptr);

/**
 * Construct a Raise node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_exo_ptr exo_ptr
*/
FIRM_API  ir_node *new_r_Raise(ir_node *block, ir_node * irn_mem, ir_node * irn_exo_ptr);

/**
 * Construct a Raise node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_mem   mem
 * @param irn_exo_ptr exo_ptr
*/
FIRM_API  ir_node *new_d_Raise(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_exo_ptr);

/**
 * Construct a Raise node.
 *
 * @param irn_mem   mem
 * @param irn_exo_ptr exo_ptr
*/
FIRM_API  ir_node *new_Raise(ir_node * irn_mem, ir_node * irn_exo_ptr);

/**
 * Test if node is a Raise
 * @returns 1 if the node is a Raise node, 0 otherwise
 */
FIRM_API  int is_Raise(const ir_node *node);

/** Returns mem input of a Raise node. */
FIRM_API  ir_node *get_Raise_mem(const ir_node *node);
/** Sets mem input of a Raise node. */
FIRM_API  void set_Raise_mem(ir_node *node, ir_node *mem);
/** Returns exo_ptr input of a Raise node. */
FIRM_API  ir_node *get_Raise_exo_ptr(const ir_node *node);
/** Sets exo_ptr input of a Raise node. */
FIRM_API  void set_Raise_exo_ptr(ir_node *node, ir_node *exo_ptr);
/** Raise opcode */
FIRM_API  ir_op *op_Raise;

/** Returns opcode for Raise nodes. */
FIRM_API  ir_op *get_op_Raise(void);

/** @} */

/**
 * @defgroup Return Return node
 *
 * Returns from the current function. Takes memory and return values as
operands.
 * @{
 */

/**
 * Input numbers for Return node
 */
typedef enum {
	n_Return_mem, /**< memory dependency */
	n_Return_max = n_Return_mem
} n_Return;

/**
 * Construct a Return node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_rd_Return(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, int arity, ir_node *const * in);

/**
 * Construct a Return node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_r_Return(ir_node *block, ir_node * irn_mem, int arity, ir_node *const * in);

/**
 * Construct a Return node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_mem   mem
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_d_Return(dbg_info *dbgi, ir_node * irn_mem, int arity, ir_node *const * in);

/**
 * Construct a Return node.
 *
 * @param irn_mem   mem
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_Return(ir_node * irn_mem, int arity, ir_node *const * in);

/**
 * Test if node is a Return
 * @returns 1 if the node is a Return node, 0 otherwise
 */
FIRM_API  int is_Return(const ir_node *node);

/** Returns mem input of a Return node. */
FIRM_API  ir_node *get_Return_mem(const ir_node *node);
/** Sets mem input of a Return node. */
FIRM_API  void set_Return_mem(ir_node *node, ir_node *mem);
/** Get the number of Return ress. */
FIRM_API  int get_Return_n_ress(ir_node const *node);
/** Get the Return res with index @p pos. */
FIRM_API  ir_node *get_Return_res(ir_node const *node, int pos);
/** Set the Return res with index @p pos. */
FIRM_API  void set_Return_res(ir_node *node, int pos, ir_node *res);
/** Get an array of all Return ress. */
ir_node **get_Return_res_arr(ir_node *node);
/** Return opcode */
FIRM_API  ir_op *op_Return;

/** Returns opcode for Return nodes. */
FIRM_API  ir_op *get_op_Return(void);

/** @} */

/**
 * @defgroup Sel Sel node
 *
 * Computes the address of an array element from the array base pointer and
an index.

A Sel node must only produce a NULL pointer if the ptr input is NULL.
 * @{
 */

/**
 * Input numbers for Sel node
 */
typedef enum {
	n_Sel_ptr, /**< pointer to array to select from */
	n_Sel_index, /**< index to select */
	n_Sel_max = n_Sel_index
} n_Sel;

/**
 * Construct a Sel node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_ptr   ptr
 * @param irn_index index
 * @param type      array type
*/
FIRM_API  ir_node *new_rd_Sel(dbg_info *dbgi, ir_node *block, ir_node * irn_ptr, ir_node * irn_index, ir_type* type);

/**
 * Construct a Sel node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_ptr   ptr
 * @param irn_index index
 * @param type      array type
*/
FIRM_API  ir_node *new_r_Sel(ir_node *block, ir_node * irn_ptr, ir_node * irn_index, ir_type* type);

/**
 * Construct a Sel node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_ptr   ptr
 * @param irn_index index
 * @param type      array type
*/
FIRM_API  ir_node *new_d_Sel(dbg_info *dbgi, ir_node * irn_ptr, ir_node * irn_index, ir_type* type);

/**
 * Construct a Sel node.
 *
 * @param irn_ptr   ptr
 * @param irn_index index
 * @param type      array type
*/
FIRM_API  ir_node *new_Sel(ir_node * irn_ptr, ir_node * irn_index, ir_type* type);

/**
 * Test if node is a Sel
 * @returns 1 if the node is a Sel node, 0 otherwise
 */
FIRM_API  int is_Sel(const ir_node *node);

/** Returns ptr input of a Sel node. */
FIRM_API  ir_node *get_Sel_ptr(const ir_node *node);
/** Sets ptr input of a Sel node. */
FIRM_API  void set_Sel_ptr(ir_node *node, ir_node *ptr);
/** Returns index input of a Sel node. */
FIRM_API  ir_node *get_Sel_index(const ir_node *node);
/** Sets index input of a Sel node. */
FIRM_API  void set_Sel_index(ir_node *node, ir_node *index);

/** Returns type attribute of a Sel node. */
FIRM_API  ir_type* get_Sel_type(const ir_node *node);
/** Sets type attribute of a Sel node. */
FIRM_API  void set_Sel_type(ir_node *node, ir_type* type);
/** Sel opcode */
FIRM_API  ir_op *op_Sel;

/** Returns opcode for Sel nodes. */
FIRM_API  ir_op *get_op_Sel(void);

/** @} */

/**
 * @defgroup Shl Shl node
 *
 * Returns its first operands bits shifted left by the amount of the 2nd
operand.
The right input (shift amount) must be an unsigned integer value.
If the result mode has modulo_shift!=0, then the effective shift amount is
the right input modulo this modulo_shift amount.
 * @{
 */

/**
 * Input numbers for Shl node
 */
typedef enum {
	n_Shl_left, /**< first operand */
	n_Shl_right, /**< second operand */
	n_Shl_max = n_Shl_right
} n_Shl;

/**
 * Construct a Shl node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_rd_Shl(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Shl node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_r_Shl(ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Shl node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_d_Shl(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Shl node.
 *
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_Shl(ir_node * irn_left, ir_node * irn_right);

/**
 * Test if node is a Shl
 * @returns 1 if the node is a Shl node, 0 otherwise
 */
FIRM_API  int is_Shl(const ir_node *node);

/** Returns left input of a Shl node. */
FIRM_API  ir_node *get_Shl_left(const ir_node *node);
/** Sets left input of a Shl node. */
FIRM_API  void set_Shl_left(ir_node *node, ir_node *left);
/** Returns right input of a Shl node. */
FIRM_API  ir_node *get_Shl_right(const ir_node *node);
/** Sets right input of a Shl node. */
FIRM_API  void set_Shl_right(ir_node *node, ir_node *right);
/** Shl opcode */
FIRM_API  ir_op *op_Shl;

/** Returns opcode for Shl nodes. */
FIRM_API  ir_op *get_op_Shl(void);

/** @} */

/**
 * @defgroup Shr Shr node
 *
 * Returns its first operands bits shifted right by the amount of the 2nd
operand. No special handling for the sign bit is performed (zero extension).
The right input (shift amount) must be an unsigned integer value.
If the result mode has modulo_shift!=0, then the effective shift amount is
the right input modulo this modulo_shift amount.
 * @{
 */

/**
 * Input numbers for Shr node
 */
typedef enum {
	n_Shr_left, /**< first operand */
	n_Shr_right, /**< second operand */
	n_Shr_max = n_Shr_right
} n_Shr;

/**
 * Construct a Shr node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_rd_Shr(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Shr node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_r_Shr(ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Shr node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_d_Shr(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Shr node.
 *
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_Shr(ir_node * irn_left, ir_node * irn_right);

/**
 * Test if node is a Shr
 * @returns 1 if the node is a Shr node, 0 otherwise
 */
FIRM_API  int is_Shr(const ir_node *node);

/** Returns left input of a Shr node. */
FIRM_API  ir_node *get_Shr_left(const ir_node *node);
/** Sets left input of a Shr node. */
FIRM_API  void set_Shr_left(ir_node *node, ir_node *left);
/** Returns right input of a Shr node. */
FIRM_API  ir_node *get_Shr_right(const ir_node *node);
/** Sets right input of a Shr node. */
FIRM_API  void set_Shr_right(ir_node *node, ir_node *right);
/** Shr opcode */
FIRM_API  ir_op *op_Shr;

/** Returns opcode for Shr nodes. */
FIRM_API  ir_op *get_op_Shr(void);

/** @} */

/**
 * @defgroup Shrs Shrs node
 *
 * Returns its first operands bits shifted right by the amount of the 2nd
operand. The leftmost bit (usually the sign bit) stays the same
(sign extension).
The right input (shift amount) must be an unsigned integer value.
If the result mode has modulo_shift!=0, then the effective shift amount is
the right input modulo this modulo_shift amount.
 * @{
 */

/**
 * Input numbers for Shrs node
 */
typedef enum {
	n_Shrs_left, /**< first operand */
	n_Shrs_right, /**< second operand */
	n_Shrs_max = n_Shrs_right
} n_Shrs;

/**
 * Construct a Shrs node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_rd_Shrs(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Shrs node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_r_Shrs(ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Shrs node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_d_Shrs(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Shrs node.
 *
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_Shrs(ir_node * irn_left, ir_node * irn_right);

/**
 * Test if node is a Shrs
 * @returns 1 if the node is a Shrs node, 0 otherwise
 */
FIRM_API  int is_Shrs(const ir_node *node);

/** Returns left input of a Shrs node. */
FIRM_API  ir_node *get_Shrs_left(const ir_node *node);
/** Sets left input of a Shrs node. */
FIRM_API  void set_Shrs_left(ir_node *node, ir_node *left);
/** Returns right input of a Shrs node. */
FIRM_API  ir_node *get_Shrs_right(const ir_node *node);
/** Sets right input of a Shrs node. */
FIRM_API  void set_Shrs_right(ir_node *node, ir_node *right);
/** Shrs opcode */
FIRM_API  ir_op *op_Shrs;

/** Returns opcode for Shrs nodes. */
FIRM_API  ir_op *get_op_Shrs(void);

/** @} */

/**
 * @defgroup Size Size node
 *
 * A symbolic constant that represents the size of a type
 * @{
 */

/**
 * Construct a Size node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irg       The IR graph the node belongs to.
 * @param mode      mode of the operations result
 * @param type      type to operate on
*/
FIRM_API  ir_node *new_rd_Size(dbg_info *dbgi, ir_graph *irg, ir_mode * mode, ir_type* type);

/**
 * Construct a Size node.
 *
 * @param irg       The IR graph the node belongs to.
 * @param mode      mode of the operations result
 * @param type      type to operate on
*/
FIRM_API  ir_node *new_r_Size(ir_graph *irg, ir_mode * mode, ir_type* type);

/**
 * Construct a Size node.
 *
 * @param dbgi      A pointer to debug information.
 * @param mode      mode of the operations result
 * @param type      type to operate on
*/
FIRM_API  ir_node *new_d_Size(dbg_info *dbgi, ir_mode * mode, ir_type* type);

/**
 * Construct a Size node.
 *
 * @param mode      mode of the operations result
 * @param type      type to operate on
*/
FIRM_API  ir_node *new_Size(ir_mode * mode, ir_type* type);

/**
 * Test if node is a Size
 * @returns 1 if the node is a Size node, 0 otherwise
 */
FIRM_API  int is_Size(const ir_node *node);


/** Returns type attribute of a Size node. */
FIRM_API  ir_type* get_Size_type(const ir_node *node);
/** Sets type attribute of a Size node. */
FIRM_API  void set_Size_type(ir_node *node, ir_type* type);
/** Size opcode */
FIRM_API  ir_op *op_Size;

/** Returns opcode for Size nodes. */
FIRM_API  ir_op *get_op_Size(void);

/** @} */

/**
 * @defgroup Start Start node
 *
 * The first node of a graph. Execution starts with this node.
 * @{
 */

/**
 * Projection numbers for result of Start node (use for Proj nodes)
 */
typedef enum {
	pn_Start_M, /**< initial memory */
	pn_Start_P_frame_base, /**< frame base pointer */
	pn_Start_T_args, /**< function arguments */
	pn_Start_max = pn_Start_T_args
} pn_Start;

/**
 * Construct a Start node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irg       The IR graph the node belongs to.
*/
FIRM_API  ir_node *new_rd_Start(dbg_info *dbgi, ir_graph *irg);

/**
 * Construct a Start node.
 *
 * @param irg       The IR graph the node belongs to.
*/
FIRM_API  ir_node *new_r_Start(ir_graph *irg);

/**
 * Construct a Start node.
 *
 * @param dbgi      A pointer to debug information.
*/
FIRM_API  ir_node *new_d_Start(dbg_info *dbgi);

/**
 * Construct a Start node.
 *
*/
FIRM_API  ir_node *new_Start(void);

/**
 * Test if node is a Start
 * @returns 1 if the node is a Start node, 0 otherwise
 */
FIRM_API  int is_Start(const ir_node *node);

/** Start opcode */
FIRM_API  ir_op *op_Start;

/** Returns opcode for Start nodes. */
FIRM_API  ir_op *get_op_Start(void);

/** @} */

/**
 * @defgroup Store Store node
 *
 * Stores a value into memory (heap or stack).
 * @{
 */

/**
 * Input numbers for Store node
 */
typedef enum {
	n_Store_mem, /**< memory dependency */
	n_Store_ptr, /**< address to store to */
	n_Store_value, /**< value to store */
	n_Store_max = n_Store_value
} n_Store;

/**
 * Projection numbers for result of Store node (use for Proj nodes)
 */
typedef enum {
	pn_Store_M, /**< memory result */
	pn_Store_X_regular, /**< control flow when no exception occurs */
	pn_Store_X_except, /**< control flow when exception occurred */
	pn_Store_max = pn_Store_X_except
} pn_Store;

/**
 * Construct a Store node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_ptr   ptr
 * @param irn_value value
 * @param type      The type of the object which is stored at ptr (need not match with value's type)
 * @param flags     specifies alignment, volatility and pin state
*/
FIRM_API  ir_node *new_rd_Store(dbg_info *dbgi, ir_node *block, ir_node * irn_mem, ir_node * irn_ptr, ir_node * irn_value, ir_type* type, ir_cons_flags flags);

/**
 * Construct a Store node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_mem   mem
 * @param irn_ptr   ptr
 * @param irn_value value
 * @param type      The type of the object which is stored at ptr (need not match with value's type)
 * @param flags     specifies alignment, volatility and pin state
*/
FIRM_API  ir_node *new_r_Store(ir_node *block, ir_node * irn_mem, ir_node * irn_ptr, ir_node * irn_value, ir_type* type, ir_cons_flags flags);

/**
 * Construct a Store node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_mem   mem
 * @param irn_ptr   ptr
 * @param irn_value value
 * @param type      The type of the object which is stored at ptr (need not match with value's type)
 * @param flags     specifies alignment, volatility and pin state
*/
FIRM_API  ir_node *new_d_Store(dbg_info *dbgi, ir_node * irn_mem, ir_node * irn_ptr, ir_node * irn_value, ir_type* type, ir_cons_flags flags);

/**
 * Construct a Store node.
 *
 * @param irn_mem   mem
 * @param irn_ptr   ptr
 * @param irn_value value
 * @param type      The type of the object which is stored at ptr (need not match with value's type)
 * @param flags     specifies alignment, volatility and pin state
*/
FIRM_API  ir_node *new_Store(ir_node * irn_mem, ir_node * irn_ptr, ir_node * irn_value, ir_type* type, ir_cons_flags flags);

/**
 * Test if node is a Store
 * @returns 1 if the node is a Store node, 0 otherwise
 */
FIRM_API  int is_Store(const ir_node *node);

/** Returns mem input of a Store node. */
FIRM_API  ir_node *get_Store_mem(const ir_node *node);
/** Sets mem input of a Store node. */
FIRM_API  void set_Store_mem(ir_node *node, ir_node *mem);
/** Returns ptr input of a Store node. */
FIRM_API  ir_node *get_Store_ptr(const ir_node *node);
/** Sets ptr input of a Store node. */
FIRM_API  void set_Store_ptr(ir_node *node, ir_node *ptr);
/** Returns value input of a Store node. */
FIRM_API  ir_node *get_Store_value(const ir_node *node);
/** Sets value input of a Store node. */
FIRM_API  void set_Store_value(ir_node *node, ir_node *value);

/** Returns type attribute of a Store node. */
FIRM_API  ir_type* get_Store_type(const ir_node *node);
/** Sets type attribute of a Store node. */
FIRM_API  void set_Store_type(ir_node *node, ir_type* type);

/** Returns volatility attribute of a Store node. */
FIRM_API  ir_volatility get_Store_volatility(const ir_node *node);
/** Sets volatility attribute of a Store node. */
FIRM_API  void set_Store_volatility(ir_node *node, ir_volatility volatility);

/** Returns unaligned attribute of a Store node. */
FIRM_API  ir_align get_Store_unaligned(const ir_node *node);
/** Sets unaligned attribute of a Store node. */
FIRM_API  void set_Store_unaligned(ir_node *node, ir_align unaligned);
/** Store opcode */
FIRM_API  ir_op *op_Store;

/** Returns opcode for Store nodes. */
FIRM_API  ir_op *get_op_Store(void);

/** @} */

/**
 * @defgroup Sub Sub node
 *
 * returns the difference of its operands
 * @{
 */

/**
 * Input numbers for Sub node
 */
typedef enum {
	n_Sub_left, /**< first operand */
	n_Sub_right, /**< second operand */
	n_Sub_max = n_Sub_right
} n_Sub;

/**
 * Construct a Sub node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_rd_Sub(dbg_info *dbgi, ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Sub node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_r_Sub(ir_node *block, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Sub node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_d_Sub(dbg_info *dbgi, ir_node * irn_left, ir_node * irn_right);

/**
 * Construct a Sub node.
 *
 * @param irn_left  left
 * @param irn_right right
*/
FIRM_API  ir_node *new_Sub(ir_node * irn_left, ir_node * irn_right);

/**
 * Test if node is a Sub
 * @returns 1 if the node is a Sub node, 0 otherwise
 */
FIRM_API  int is_Sub(const ir_node *node);

/** Returns left input of a Sub node. */
FIRM_API  ir_node *get_Sub_left(const ir_node *node);
/** Sets left input of a Sub node. */
FIRM_API  void set_Sub_left(ir_node *node, ir_node *left);
/** Returns right input of a Sub node. */
FIRM_API  ir_node *get_Sub_right(const ir_node *node);
/** Sets right input of a Sub node. */
FIRM_API  void set_Sub_right(ir_node *node, ir_node *right);
/** Sub opcode */
FIRM_API  ir_op *op_Sub;

/** Returns opcode for Sub nodes. */
FIRM_API  ir_op *get_op_Sub(void);

/** @} */

/**
 * @defgroup Switch Switch node
 *
 * Change control flow. The destination is chosen based on an integer
input value which is looked up in a table.

Backends can implement this efficiently using a jump table.
 * @{
 */

/**
 * Input numbers for Switch node
 */
typedef enum {
	n_Switch_selector, /**< input selector */
	n_Switch_max = n_Switch_selector
} n_Switch;

/**
 * Projection numbers for result of Switch node (use for Proj nodes)
 */
typedef enum {
	pn_Switch_default, /**< control flow if no other case matches */
	pn_Switch_max = pn_Switch_default
} pn_Switch;

/**
 * Construct a Switch node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param irn_selector selector
 * @param n_outs    number of outputs (including pn_Switch_default)
 * @param table     table describing mapping from input values to Proj numbers
*/
FIRM_API  ir_node *new_rd_Switch(dbg_info *dbgi, ir_node *block, ir_node * irn_selector, unsigned n_outs, ir_switch_table* table);

/**
 * Construct a Switch node.
 *
 * @param block     The IR block the node belongs to.
 * @param irn_selector selector
 * @param n_outs    number of outputs (including pn_Switch_default)
 * @param table     table describing mapping from input values to Proj numbers
*/
FIRM_API  ir_node *new_r_Switch(ir_node *block, ir_node * irn_selector, unsigned n_outs, ir_switch_table* table);

/**
 * Construct a Switch node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irn_selector selector
 * @param n_outs    number of outputs (including pn_Switch_default)
 * @param table     table describing mapping from input values to Proj numbers
*/
FIRM_API  ir_node *new_d_Switch(dbg_info *dbgi, ir_node * irn_selector, unsigned n_outs, ir_switch_table* table);

/**
 * Construct a Switch node.
 *
 * @param irn_selector selector
 * @param n_outs    number of outputs (including pn_Switch_default)
 * @param table     table describing mapping from input values to Proj numbers
*/
FIRM_API  ir_node *new_Switch(ir_node * irn_selector, unsigned n_outs, ir_switch_table* table);

/**
 * Test if node is a Switch
 * @returns 1 if the node is a Switch node, 0 otherwise
 */
FIRM_API  int is_Switch(const ir_node *node);

/** Returns selector input of a Switch node. */
FIRM_API  ir_node *get_Switch_selector(const ir_node *node);
/** Sets selector input of a Switch node. */
FIRM_API  void set_Switch_selector(ir_node *node, ir_node *selector);

/** Returns n_outs attribute of a Switch node. */
FIRM_API  unsigned get_Switch_n_outs(const ir_node *node);
/** Sets n_outs attribute of a Switch node. */
FIRM_API  void set_Switch_n_outs(ir_node *node, unsigned n_outs);

/** Returns table attribute of a Switch node. */
FIRM_API  ir_switch_table* get_Switch_table(const ir_node *node);
/** Sets table attribute of a Switch node. */
FIRM_API  void set_Switch_table(ir_node *node, ir_switch_table* table);
/** Switch opcode */
FIRM_API  ir_op *op_Switch;

/** Returns opcode for Switch nodes. */
FIRM_API  ir_op *get_op_Switch(void);

/** @} */

/**
 * @defgroup Sync Sync node
 *
 * The Sync operation unifies several partial memory blocks. These blocks
have to be pairwise disjunct or the values in common locations have to
be identical.  This operation allows to specify all operations that
eventually need several partial memory blocks as input with a single
entrance by unifying the memories with a preceding Sync operation.
 * @{
 */

/**
 * Construct a Sync node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_rd_Sync(dbg_info *dbgi, ir_node *block, int arity, ir_node *const * in);

/**
 * Construct a Sync node.
 *
 * @param block     The IR block the node belongs to.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_r_Sync(ir_node *block, int arity, ir_node *const * in);

/**
 * Construct a Sync node.
 *
 * @param dbgi      A pointer to debug information.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_d_Sync(dbg_info *dbgi, int arity, ir_node *const * in);

/**
 * Construct a Sync node.
 *
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_Sync(int arity, ir_node *const * in);

/**
 * Test if node is a Sync
 * @returns 1 if the node is a Sync node, 0 otherwise
 */
FIRM_API  int is_Sync(const ir_node *node);

/** Get the number of Sync preds. */
FIRM_API  int get_Sync_n_preds(ir_node const *node);
/** Get the Sync pred with index @p pos. */
FIRM_API  ir_node *get_Sync_pred(ir_node const *node, int pos);
/** Set the Sync pred with index @p pos. */
FIRM_API  void set_Sync_pred(ir_node *node, int pos, ir_node *pred);
/** Get an array of all Sync preds. */
ir_node **get_Sync_pred_arr(ir_node *node);
/** Sync opcode */
FIRM_API  ir_op *op_Sync;

/** Returns opcode for Sync nodes. */
FIRM_API  ir_op *get_op_Sync(void);

/** @} */

/**
 * @defgroup Tuple Tuple node
 *
 * Builds a Tuple from single values.

This is needed to implement optimizations that remove a node that produced
a tuple.  The node can be replaced by the Tuple operation so that the
following Proj nodes have not to be changed. (They are hard to find due to
the implementation with pointers in only one direction.) The Tuple node is
smaller than any other node, so that a node can be changed into a Tuple by
just changing its opcode and giving it a new in array.
 * @{
 */

/**
 * Construct a Tuple node.
 *
 * @param dbgi      A pointer to debug information.
 * @param block     The IR block the node belongs to.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_rd_Tuple(dbg_info *dbgi, ir_node *block, int arity, ir_node *const * in);

/**
 * Construct a Tuple node.
 *
 * @param block     The IR block the node belongs to.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_r_Tuple(ir_node *block, int arity, ir_node *const * in);

/**
 * Construct a Tuple node.
 *
 * @param dbgi      A pointer to debug information.
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_d_Tuple(dbg_info *dbgi, int arity, ir_node *const * in);

/**
 * Construct a Tuple node.
 *
 * @param arity     size of additional inputs array
 * @param in        additional inputs
*/
FIRM_API  ir_node *new_Tuple(int arity, ir_node *const * in);

/**
 * Test if node is a Tuple
 * @returns 1 if the node is a Tuple node, 0 otherwise
 */
FIRM_API  int is_Tuple(const ir_node *node);

/** Get the number of Tuple preds. */
FIRM_API  int get_Tuple_n_preds(ir_node const *node);
/** Get the Tuple pred with index @p pos. */
FIRM_API  ir_node *get_Tuple_pred(ir_node const *node, int pos);
/** Set the Tuple pred with index @p pos. */
FIRM_API  void set_Tuple_pred(ir_node *node, int pos, ir_node *pred);
/** Get an array of all Tuple preds. */
ir_node **get_Tuple_pred_arr(ir_node *node);
/** Tuple opcode */
FIRM_API  ir_op *op_Tuple;

/** Returns opcode for Tuple nodes. */
FIRM_API  ir_op *get_op_Tuple(void);

/** @} */

/**
 * @defgroup Unknown Unknown node
 *
 * Returns an unknown (at compile- and runtime) value. It is a valid
optimization to replace an Unknown by any other constant value.

Be careful when optimising Unknown values, you cannot simply replace
Unknown+x or Unknown<x with a new Unknown node if there are multiple
users of the original unknown node!
 * @{
 */

/**
 * Construct an Unknown node.
 *
 * @param dbgi      A pointer to debug information.
 * @param irg       The IR graph the node belongs to.
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_rd_Unknown(dbg_info *dbgi, ir_graph *irg, ir_mode * mode);

/**
 * Construct an Unknown node.
 *
 * @param irg       The IR graph the node belongs to.
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_r_Unknown(ir_graph *irg, ir_mode * mode);

/**
 * Construct an Unknown node.
 *
 * @param dbgi      A pointer to debug information.
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_d_Unknown(dbg_info *dbgi, ir_mode * mode);

/**
 * Construct an Unknown node.
 *
 * @param mode      mode of the operations result
*/
FIRM_API  ir_node *new_Unknown(ir_mode * mode);

/**
 * Test if node is a Unknown
 * @returns 1 if the node is a Unknown node, 0 otherwise
 */
FIRM_API  int is_Unknown(const ir_node *node);

/** Unknown opcode */
FIRM_API  ir_op *op_Unknown;

/** Returns opcode for Unknown nodes. */
FIRM_API  ir_op *get_op_Unknown(void);

/** @} */

/**
 * Test if node is a binop
 * @returns 1 if the node is a binop node, 0 otherwise
 */
FIRM_API  int is_binop(const ir_node *node);/**
 * Test if node is a entconst
 * @returns 1 if the node is a entconst node, 0 otherwise
 */
FIRM_API  int is_entconst(const ir_node *node);
/** Returns entity attribute of an entconst node. */
FIRM_API  ir_entity* get_entconst_entity(const ir_node *node);
/** Sets entity attribute of an entconst node. */
FIRM_API  void set_entconst_entity(ir_node *node, ir_entity* entity);
/**
 * Test if node is a typeconst
 * @returns 1 if the node is a typeconst node, 0 otherwise
 */
FIRM_API  int is_typeconst(const ir_node *node);
/** Returns type attribute of a typeconst node. */
FIRM_API  ir_type* get_typeconst_type(const ir_node *node);
/** Sets type attribute of a typeconst node. */
FIRM_API  void set_typeconst_type(ir_node *node, ir_type* type);


/** @} */

#endif
