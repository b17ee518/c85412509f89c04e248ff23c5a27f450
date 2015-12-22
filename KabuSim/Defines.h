#pragma once

#include <stdio.h>

enum class BoardSide
{
	Sell,
	Buy,
};

enum class ExchangeMethod
{
	BuyNew,
	SellNew,
	BuybackOccupied,
	SelloutPurchased,
};

#define FW_SYNTHESIZE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: varType get##funName(void) const { return varName; }

#define FW_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: varType get##funName(void) const { return varName; }\
public: void set##funName(varType var){ varName = var; }

#define FW_SYNTHESIZE_WITHINIT(varType, varName, funName, initVal)\
protected: varType varName = initVal;\
public: varType get##funName(void) const { return varName; }\
public: void set##funName(varType var){ varName = var; }

#define FW_SYNTHESIZE_STATIC(varType, varName, funName)\
protected: static varType varName;\
public: static varType get##funName(void) { return varName; }\
public: static void set##funName(varType var){ varName = var; }

#define FW_SYNTHESIZE_STATIC_REFERENCE(varType, varName, funName)\
protected: static varType varName;\
public: static varType& get##funName(void) { return varName; }\
public: static void set##funName(const varType& var){ varName = var; }

#define FW_SYNTHESIZE_STATIC_READONLY(varType, varName, funName)\
protected: static varType varName;\
public: static varType get##funName(void) { return varName; }

#define FW_SYNTHESIZE_REFERENCE(varType, varName, funName)\
protected: varType varName;\
public: varType& get##funName(void) { return varName; }\
public: void set##funName(varType var){ varName = var; }

#define FW_SYNTHESIZE_REFERENCE_READONLY(varType, varName, funName)\
protected: varType varName;\
public: varType& get##funName(void) { return varName; }