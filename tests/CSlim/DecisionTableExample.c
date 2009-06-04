#include <stdlib.h>
#include <memory.h>
#include "StatementExecutor.h"
#include "SlimList.h"
#include <stdio.h>

void Division_Register(StatementExecutor*);


typedef struct Division
{
    float numerator;
    float denominator;
    char result[32];
} Division;

void* Division_Create(StatementExecutor* executor, SlimList* args)
{
	Division* self = malloc(sizeof(Division));
	memset(self, 0, sizeof(Division));
	return self;
}

void Division_Destroy(void* void_self)
{
    free(void_self);
}

static char* setNumerator(void* void_self, SlimList* args) {
	Division* self = (Division*)void_self;
	self->numerator = atof(SlimList_GetStringAt(args, 0));
	return "OK";
}

static char* setDenominator(void* void_self, SlimList* args) {
	Division* self = (Division*)void_self;
	self->denominator = atof(SlimList_GetStringAt(args, 0));
	return "OK";
}

static char* getQuotient(void* void_self, SlimList* args) {
	Division* self = (Division*)void_self;
  float quotient = self->numerator / self->denominator;
  snprintf(self->result, 32, "%f", quotient);
	return self->result;
}

void Division_Register(StatementExecutor* executor)
{
	StatementExecutor_RegisterFixture(executor, "Division", Division_Create, Division_Destroy);
	StatementExecutor_RegisterMethod(executor, "TestSlim", "setNumerator", setNumerator);	
	StatementExecutor_RegisterMethod(executor, "TestSlim", "setdenominator", setDenominator);
}