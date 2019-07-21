#ifndef BUILDER_H
#define BUILDER_H
#include <memory>
#include <string>
#include "blocks/var.h"
#include "builder/builder_context.h"

namespace builder {
// Builder objects are always alive only for duration of the RUN/SEQUENCE. 
// Never store pointers to these objects (across runs) or heap allocate them.
class var;
class builder {
public:
	builder_context* context;
	builder() = default;
	builder(builder_context* context_): context(context_) {}	
	
	block::expr::Ptr block_expr;
	template <typename T>	
	builder builder_binary_op(const builder &);
	builder operator && (const builder &);	
	builder operator || (const builder &);
	builder operator + (const builder &);
	builder operator - (const builder &);
	builder operator * (const builder &);
	builder operator / (const builder &);
	
	operator bool();
};


class var {
public:
	builder_context* context;	
	// Optional var name
	std::string var_name;
	block::var::Ptr block_var;
	
	
	operator builder() const;

	operator bool();
	builder operator && (const builder &);
	builder operator || (const builder &);
	builder operator + (const builder &);
	builder operator - (const builder &);
	builder operator * (const builder &);
	builder operator / (const builder &);
	
	builder operator = (const builder &);
};


class int_var: public var {
public:
	int_var(builder_context* context_);
	using var::operator =;
};
}

#endif
