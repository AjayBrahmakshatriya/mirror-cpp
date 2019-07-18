#ifndef EXPR_H
#define EXPR_H

#include "blocks/block.h"
#include "blocks/var.h"

#include <string>
#include <memory>
namespace block{
class expr: public block {
public:
	typedef std::shared_ptr<expr> Ptr; 	
};


class unary_expr: public expr {
public:
	typedef std::shared_ptr<unary_expr> Ptr;
	expr::Ptr expr1;
	
};

class binary_expr: public expr {
public:
	typedef std::shared_ptr<binary_expr> Ptr;
	
	expr::Ptr expr1;
	expr::Ptr expr2;
};

// For the logical not operator
class not_expr: public unary_expr {
public:
	typedef std::shared_ptr<not_expr> Ptr;
};


class and_expr: public binary_expr {
public: 
	typedef std::shared_ptr<and_expr> Ptr;
};

class or_expr: public binary_expr {
public:
	typedef std::shared_ptr<or_expr> Ptr;
};

class plus_expr: public binary_expr {
public: 
	typedef std::shared_ptr<plus_expr> Ptr;
};

class minus_expr: public binary_expr {
public:
	typedef std::shared_ptr<minus_expr> Ptr;
};

class mul_expr: public binary_expr {
public: 
	typedef std::shared_ptr<mul_expr> Ptr;
};

class div_expr: public binary_expr {
public: 
	typedef std::shared_ptr<div_expr> Ptr;
};

class var_expr: public expr {
public:
	typedef std::shared_ptr<var_expr> Ptr;

	var::Ptr var1;	
};

class const_expr: public expr {
public:
	typedef std::shared_ptr<const_expr> Ptr;
};

class int_const: public const_expr {
public:
	typedef std::shared_ptr<int_const> Ptr;
	
	long long value;
};

class assign_expr: public expr {
public:
	typedef std::shared_ptr<assign_expr> Ptr;
	
	var::Ptr var1;	
	expr::Ptr expr1;

};
}
#endif
