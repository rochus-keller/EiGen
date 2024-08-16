

/**
 * Visibility classes for entities.
 */
typedef enum {
	/**
	 * The entity is visible across compilation units. It might have an
	 * initializer/graph.
	 * Note that entities with visibility_external without initializer are
	 * assumed to be defined in another compilation unit (not like C variables
	 * which are considered 'uninitialized' in this case).
	 */
	ir_visibility_external,
	/**
	 * The entity is visible across compilation units, but not across modules.
	 * This is equivalent to __attribute__((visibility("hidden"))) in gcc.
	 */
	ir_visibility_external_private,
	/**
	 * The entity is visible across compilation units and modules and cannot be
	 * overridden by other modules.
	 * Equivalent to __attribute__((visible("protected"))) in gcc.
	 */
	ir_visibility_external_protected,
	/**
	 * The entity is local to the compilation unit.
	 * A local entity is not visible in other compilation units.
	 * Note that the entity might still be accessed indirectly from other units
	 * through pointers.
	 */
	ir_visibility_local,
	/**
	 * This has the same semantic as visibility_local. Additionally the symbol
	 * is completely hidden from the linker (it only appears in the assembly).
	 * While visibility_local is probably still visible to debuggers,
	 * visibility_private symbols aren't and probably won't appear in the object
	 * files
	 */
	ir_visibility_private,
} ir_visibility;

/**
 * linkage specifies how the linker treats symbols
 */
typedef enum ir_linkage {
    IR_LINKAGE_DEFAULT         = 0,
    /**
     * A symbol whose definition won't change in a program.
     * Optimization might replace loads from this entity with constants.
     * Also most linkers put such data in a constant segment which is shared
     * between multiple running instances of the same application.
     */
    IR_LINKAGE_CONSTANT        = 1 << 0,
    /**
     * The entity is a weak symbol.
     * A weak symbol is overridden by a non-weak symbol if one exists.
     * Most linkers only support the IR_LINKAGE_WEAK in combination with
     * IR_LINKAGE_MERGE.
     */
    IR_LINKAGE_WEAK            = 1 << 1,
    /**
     * The entity may be removed when it isn't referenced anywhere in the
     * compilation unit even if it is exported (non-local).
     * Typically used for C++ instantiated template code (,,COMDAT'' section).
     */
    IR_LINKAGE_GARBAGE_COLLECT = 1 << 2,
    /**
     * The linker will try to merge entities with same name from different
     * compilation units. This is the usual behaviour for global variables
     * without explicit initialisation in C (``COMMON'' symbols). It's also
     * typically used in C++ for instantiated template code (,,COMDAT'' section)
     */
    IR_LINKAGE_MERGE           = 1 << 3,
    /**
     * Some entity uses are potentially hidden from the compiler.
     * (For example because they happen in an asm("") statement. This flag
     *  should be set for __attribute__((used)) in C code).
     * Setting this flag prohibits that the compiler making assumptions about
     * read/write behaviour to global variables or changing calling conventions
     * from cdecl to fastcall.
     */
    IR_LINKAGE_HIDDEN_USER     = 1 << 4,
    /**
     * Do not generate code even if the entity has a graph or
     * initialization data attached.  The graph/data is only used for
     * inlining.  Otherwise the entity is regarded as a declaration of
     * an externally defined entity.
     * This linkage flag can be used to implement C99 "inline" or GNU89
     * "extern inline".
     */
    IR_LINKAGE_NO_CODEGEN      = 1 << 5,
    /**
     * The entity does not need to have an address that is different from other
     * entities. When this property is set the entity may be safely merged with
     * entities with the same content.
     */
    IR_LINKAGE_NO_IDENTITY     = 1 << 6,
} ir_linkage;
